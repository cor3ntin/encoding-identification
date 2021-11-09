#pragma once
#include <cstddef>
#include <cstring>
#include <iterator>
#ifndef _WIN32
#include <unistd.h>
#else
#define NOMINMAX
#endif

#include <algorithm>
#include <array>
#include <locale>
#include <string_view>
#include <fstream>
#include <span>
#include <ranges>

#ifndef H_COR3NTIN_ENCODINGS_HPP
#    include "encodings_generated.hpp"
#    include "encodings_base.hpp"
#endif

#ifdef __unix__
#    include <langinfo.h>
#endif

#ifdef _WIN32
#    include "windows.h"
#    ifndef H_COR3NTIN_ENCODINGS_HPP
#        include "encodings_windows.hpp"
#    endif
#endif

#ifdef __APPLE__
#    include <sys/sysctl.h>
#    include <sys/types.h>
#endif

namespace cor3ntin::encoding {

namespace details {

    constexpr const char* normalize_utf(const char* name) {
        if(!name)
            return nullptr;
        if (compare_name(name, "UTF-16LE") || compare_name(name, "UTF-16BE"))
            return "UTF-16";
        if (compare_name(name, "UTF-32LE") || compare_name(name, "UTF-32BE"))
            return "UTF-32";
        return name;
    }

    constexpr details::id find_encoding(std::string_view name) {
        if(name.empty())
            return details::id::unknown;
        for(auto&& e = std::begin(details::data); e != std::end(details::data); e++) {
            if(compare_name(e->name, name))
                return details::id(e->mib);
        }
        return details::id::unknown;
    }

    struct encoding_alias_view : public std::ranges::view_interface<encoding_alias_view>{

        // TODO: remove
        constexpr encoding_alias_view() = default;
        constexpr encoding_alias_view(int mib) : mib(mib){};
        struct iterator {
            using value_type = const char*;
            using reference = const char*;
            using iterator_category = std::random_access_iterator_tag;
            using difference_type = std::ptrdiff_t;

            constexpr iterator() = default;
            constexpr iterator(const iterator&) = default;

            constexpr iterator(int mib) : mib(mib) {
                d = std::lower_bound(std::begin(details::data), std::end(details::data), mib,
                                     [](const enc_data& d, int mib) { return d.mib < mib; });
            }

            constexpr const char* operator*() const {
                return d->name;
            }

            constexpr const char* operator[](difference_type n) const {
                return (d + n)->name;
            }

            constexpr iterator& operator++() {
                d++;
                return *this;
            }

            constexpr iterator operator++(int) {
                auto c = *this;
                d++;
                return c;
            }

            constexpr iterator& operator--() {
                d--;
                return *this;
            }

            constexpr iterator operator--(int) {
                auto c = *this;
                d--;
                return c;
            }

            constexpr iterator& operator+=(difference_type n) {
                d+=n;
                return *this;
            }
            constexpr iterator& operator-=(difference_type n) {
                d-=n;
                return *this;

            }

            constexpr bool operator==(iterator it) const {
                return mib == it.mib && d == it.d;
            }

            constexpr auto operator<=>(iterator it) const {
                if(mib <=> it.mib == 0)
                    return mib <=> it.mib;
                return d <=> it.d;
            }

            friend constexpr iterator operator+(const iterator& it, difference_type n) {
                return iterator{it} += n;
            }
            friend constexpr iterator operator+(difference_type n, const iterator& it) {
                return iterator{it} += n;
            }
            friend constexpr iterator operator-(const iterator& it, difference_type n) {
                return iterator{it} -= n;
            }

            friend constexpr difference_type operator-(const iterator& a, const iterator& b) {
                return a.d - b.d;
            }

        private:
            const enc_data* d = nullptr;
            int mib = -1;
            friend class encoding_alias_view;
        };

        constexpr iterator begin() const {
            return iterator{mib};
        }
        constexpr iterator end() const {
            auto it = iterator{mib};
            while(it.d && it.d->mib == mib)
                ++it;
            return it;
        }

    private:
        int mib = -1;
    };
}    // namespace details


struct text_encoding {
    using id = details::id;
    using alias_view = details::encoding_alias_view;


    constexpr text_encoding(std::string_view name) noexcept :
        text_encoding(name, details::find_encoding(name)) {}
    constexpr text_encoding(id mib) noexcept : text_encoding({}, mib) {}

    constexpr text_encoding() noexcept : text_encoding({}, details::id::unknown) {}

private:
    constexpr text_encoding(std::string_view name, id mib) :
        mib_(mib == id::unknown ? details::id::other : mib) {
        if(name.empty()) {
            const auto a = details::encoding_alias_view(int(mib));
            if(a.begin() != a.end()) {
                name = *a.begin();
            }
        }
        if(!name.empty()) {
            std::size_t s = std::min(name.size(), std::size_t(63));
            std::copy_n(name.data(), s, std::begin(name_));
            name_[s] = '\0';
        }
    }

public:
    constexpr id mib() const noexcept {
        return mib_;
    }

    constexpr const char* name() const noexcept {
        if(name_[0] != '\0') {
            return name_.data();
        }
        return nullptr;
    }

    constexpr alias_view aliases() const noexcept {
        return alias_view(int(mib_));
    }


    //#ifdef __cpp_consteval
    static consteval text_encoding literal();
    static consteval text_encoding wide_literal();
    //#endif

    static inline text_encoding environment() noexcept;
    static inline text_encoding wide_environment() noexcept;

    template<id id>
    static bool environment_is() noexcept;

    template<id id>
    static bool wide_environment_is() noexcept;

    static inline text_encoding for_locale(const std::locale&) noexcept;
    static inline text_encoding wide_for_locale(const std::locale&) noexcept;

    constexpr bool operator==(const text_encoding& other) noexcept {
        if(mib() <= id::unknown && other.mib() <= id::unknown) {
            return other.name() == name();
        }
        return other.mib() == mib();
    }

    constexpr bool operator==(text_encoding::id i) noexcept {
        return i == mib();
    }


private:
    // poor man constexpr string
    std::array<char, 30> name_ = {0};
    id mib_ = id::unknown;
#ifdef _MSC_VER
    int m_code_page = 0;
#endif
};


inline text_encoding text_encoding::environment() noexcept {
    static text_encoding encoding = []() -> text_encoding {
#if defined(_WIN32)
        auto cp = GetACP();
        text_encoding e;
        e.mib_ = details::mib_from_page(cp);
        e.m_code_page = cp;
        return e;
#else
        auto make_locale = [](const char* name) {
            return newlocale(LC_CTYPE_MASK, name, (locale_t)0);
        };

        auto extract_locale = [&](std::span<const char> buffer) {
            // https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap08.html#tag_08_02
            for(auto KEY : {"LC_ALL=", "LC_CTYPE=", "LANG="}) {
                const auto n = strlen(KEY);
                for(std::size_t pos = 0; pos < buffer.size();) {
                    const char* entry = buffer.data() + pos;
                    if(!entry || !*entry)
                        break;
                    auto entry_size = strlen(entry);
                    if(entry_size > n && strncmp(KEY, entry, n) == 0) {
                        auto loc = make_locale(entry + n);
                        if(loc)
                            return loc;
                    }
                    pos += entry_size + 1;
                }
            }
            return make_locale("");
        };

        auto __get_locale = [&]() {
            std::string buffer;
#    ifdef __APPLE__
            int mib[] = {CTL_KERN, KERN_PROCARGS2, getpid()};
            std::size_t args_size;
            int res = sysctl(mib, 3, nullptr, &args_size, nullptr, 0);
            if(res)
                return make_locale("");
            args_size++;
            buffer.resize(args_size);
            res = sysctl(mib, 3, buffer.data(), &args_size, nullptr, 0);
            if(res)
                return make_locale("");
            if(args_size < sizeof(int))
                return make_locale("");
            int argc;
            memcpy(&argc, buffer.data(), sizeof(argc));
            std::string_view args(buffer.data(), buffer.size());
            // Get rid of argc
            args.remove_prefix(sizeof(int));
            // Get rid of the process name and all the args
            for(int i = 0; i < argc; ++i) {
                auto pos = args.find('\0');
                if(pos == std::string::npos)
                    return make_locale("");
                args.remove_prefix(pos + 1);
            }
            auto pos = args.find_first_not_of('\0');
            args.remove_prefix(pos);
            return extract_locale(std::span{args.data(), args.size()});
#    endif
            std::string filename = "/proc/self/environ";
            std::ifstream file(filename);
            if(!file)
                return make_locale("");
            buffer =
                std::string{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
            return extract_locale(buffer);
        };
        details::scoped_locale loc = __get_locale();
        if(!loc)
            return {};
        const char* name = details::normalize_utf(nl_langinfo_l(CODESET, loc));
        if(!name)
            return {};
        const id mib = details::find_encoding(name);
        return text_encoding(name, mib);
#endif    // _WIN32
    }();
    return encoding;
}

inline text_encoding text_encoding::wide_environment() noexcept {
#ifdef _WIN32
    // windows is always UTF-16LE
    return text_encoding("UTF-16", details::id::UTF16);
#else
    // GLIBC is always UCS4
    return sizeof(wchar_t) == 2 ? text_encoding("ISO-10646-UCS-2", details::id::UCS2)
                                : text_encoding("ISO-10646-UCS-4", details::id::UCS4);
#endif
}


template<text_encoding::id id_>
bool text_encoding::environment_is() noexcept {
#ifdef _WIN32
    return environment().mib() == id_;
#else
    details::scoped_locale loc = newlocale(LC_CTYPE_MASK, "", (locale_t)0);
    const char* name = details::normalize_utf(nl_langinfo_l(CODESET, loc));
    return details::encoding_is<id_>(name);
#endif
}

template<text_encoding::id id_>
bool text_encoding::wide_environment_is() noexcept {
    return wide_environment().mib() == id_;
}

inline text_encoding text_encoding::for_locale(const std::locale& l) noexcept {
#ifdef _WIN32
#else
    details::scoped_locale loc = newlocale(LC_CTYPE, l.name().c_str(), 0);
    const char* name = details::normalize_utf(nl_langinfo_l(CODESET, loc));
    const id mib = details::find_encoding(name);
    return text_encoding(name, mib);
#endif
}

inline text_encoding text_encoding::wide_for_locale(const std::locale&) noexcept {
    return wide_environment();
}

//#ifdef __cpp_consteval
consteval text_encoding text_encoding::literal() {
#ifdef __GNUC_EXECUTION_CHARSET_NAME
    return text_encoding(details::normalize_utf(__GNUC_EXECUTION_CHARSET_NAME),
                         details::find_encoding(details::normalize_utf(__GNUC_EXECUTION_CHARSET_NAME)));
#elif defined(__clang_literal_encoding__)
    return text_encoding(details::normalize_utf(__clang_literal_encoding__),
                         details::find_encoding(details::normalize_utf(__clang_literal_encoding__)));
#elif defined(__clang__)
    return text_encoding("UTF-8", details::id::UTF8);
#elif defined(_MSVC_EXECUTION_CHARACTER_SET)
    text_encoding e;
    e.mib_ = details::mib_from_page(_MSVC_EXECUTION_CHARACTER_SET);
    e.m_code_page = _MSVC_EXECUTION_CHARACTER_SET;
    return e;
#else
    return {};
#endif
}

consteval text_encoding text_encoding::wide_literal() {
#ifdef _WIN32
    // WINDOWS is always UTF-16
    return text_encoding("UTF-16", details::id::UTF16);
#elif defined(__GNUC_WIDE_EXECUTION_CHARSET_NAME)
    return text_encoding(details::normalize_utf(__GNUC_WIDE_EXECUTION_CHARSET_NAME),
                         details::find_encoding(details::normalize_utf(__GNUC_WIDE_EXECUTION_CHARSET_NAME)));
#elif defined(__clang_wide_literal_encoding__)
    return text_encoding(details::normalize_utf(__clang_wide_literal_encoding__),
                         details::find_encoding(details::normalize_utf(__clang_wide_literal_encoding__)));
#elif defined(__GNUC__) || defined(__clang__)
    return sizeof(wchar_t) == 2 ? text_encoding("UTF-16", details::id::UTF16)
                                : text_encoding("UTF-32", details::id::UTF32);
#else
    return {};
#endif
}
//#endif


}    // namespace cor3ntin::encoding

namespace std::ranges {
template <>
inline constexpr bool enable_borrowed_range<cor3ntin::encoding::text_encoding::alias_view> = true;
}

static_assert(std::ranges::common_range<cor3ntin::encoding::text_encoding::alias_view>);
static_assert(std::ranges::view<cor3ntin::encoding::text_encoding::alias_view>);
static_assert(std::ranges::random_access_range<cor3ntin::encoding::text_encoding::alias_view>);
