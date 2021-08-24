#pragma once
#include <cstddef>
#include <cstring>
#include <unistd.h>
#define NOMINMAX
/*
struct text_encoding {
    enum id {
        other = 1,
        unknown = 2,
        ASCII = 3,
        //...
        reserved = 3000
    }

    constexpr text_encoding() noexcept;
    constexpr text_encoding(std::string name, int mib = id::other);

    constexpr int mib() const noexcept;
    const char* name() const noexcept;
    auto aliases() const noexcept;

    static consteval text_encoding literal();
    static consteval text_encoding wide_literal();

    static text_encoding system();
    static text_encoding wide_system();

    static text_encoding for_locale(const std::locale&);
    static text_encoding wide_for_locale(const std::locale&);

    bool operator==(const text_encoding & other);
};
*/


#include <algorithm>
#include <array>
#include <locale>
#include <string_view>
#include <fstream>
#include <streambuf>
#include <span>

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

#ifdef _MSC_VER
    // FUNCTION TEMPLATE lower_bound
    template<class _FwdIt, class _Ty, class _Pr>
    _NODISCARD constexpr _FwdIt lower_bound(_FwdIt _First, const _FwdIt _Last, const _Ty& _Val,
                                            _Pr _Pred) {
        using namespace std;
        // find first element not before _Val, using _Pred
        _Adl_verify_range(_First, _Last);
        auto _UFirst = _Get_unwrapped(_First);
        std::_Iter_diff_t<_FwdIt> _Count = _STD distance(_UFirst, _Get_unwrapped(_Last));

        while(0 < _Count) {    // divide and conquer, find half that contains answer
            const _Iter_diff_t<_FwdIt> _Count2 = _Count >> 1;    // TRANSITION, VSO#433486
            const auto _UMid = _STD next(_UFirst, _Count2);
            if(_Pred(*_UMid, _Val)) {    // try top half
                _UFirst = _Next_iter(_UMid);
                _Count -= _Count2 + 1;
            } else {
                _Count = _Count2;
            }
        }

        _Seek_wrapped(_First, _UFirst);
        return _First;
    }
    template<class _InIt, class _Diff, class _OutIt>
    constexpr _OutIt copy_n(_InIt _First, _Diff _Count_raw,
                            _OutIt _Dest) {    // copy [_First, _First + _Count) to [_Dest, ...)
        using namespace std;
        _Algorithm_int_t<_Diff> _Count = _Count_raw;
        if(0 < _Count) {
            auto _UFirst = _Get_unwrapped_n(_First, _Count);
            auto _UDest = _Get_unwrapped_n(_Dest, _Count);
            for(;;) {
                *_UDest = *_UFirst;
                ++_UDest;
                --_Count;
                if(_Count == 0) {    // note that we avoid an extra ++_First here to allow
                                     // istream_iterator to work, see LWG#2471
                    break;
                }

                ++_UFirst;
            }
            _Seek_wrapped(_Dest, _UDest);
        }

        return _Dest;
    }
    namespace alg = details;
#else
    namespace alg = std;
#endif    // def _MSC_VER


    constexpr details::id find_encoding(std::string_view name) {
        if(name.empty())
            return details::id::unknown;
        for(auto&& e = std::begin(data); e != std::end(data); e++) {
            if(compare_name(e->name, name))
                return details::id(e->mib);
        }
        return details::id::unknown;
    }

    struct encoding_alias_view {

        constexpr encoding_alias_view(int mib) : mib(mib){};
        struct sentinel {};
        struct iterator {
            using value_type = const char*;
            using reference = const char*;
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;

            constexpr iterator() = default;

            constexpr iterator(int mib) : mib(mib) {
                d = alg::lower_bound(std::begin(data), std::end(data), mib,
                                     [](const enc_data& d, int mib) { return d.mib < mib; });
            }

            constexpr const char* operator*() const {
                return d->name;
            }

            constexpr iterator& operator++(int) {
                d++;
                return *this;
            }

            constexpr iterator operator++() {
                auto c = *this;
                d++;
                return c;
            }

            constexpr bool operator==(sentinel) const {
                return !d || d->mib != mib;
            }
            constexpr bool operator!=(sentinel) const {
                return d && d->mib == mib;
            }
            constexpr bool operator==(iterator it) const {
                return d == it.d;
            }
            constexpr bool operator!=(iterator it) const {
                return !(*this == it);
            }

        private:
            const enc_data* d = nullptr;

        private:
            int mib = 0;
        };

        constexpr iterator begin() const {
            return iterator{mib};
        }
        constexpr sentinel end() const {
            return {};
        }

    private:
        int mib;
    };
}    // namespace details


struct text_encoding {
    using id = details::id;
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
            details::alg::copy_n(name.data(), s, std::begin(name_));
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

    constexpr details::encoding_alias_view aliases() const noexcept {
        return details::encoding_alias_view(int(mib_));
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
        const char* name = nl_langinfo_l(CODESET, loc);
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
    return text_encoding("UTF-16LE", details::id::UTF16LE);
#else
    // GLIBC is always UCS4
    return sizeof(wchar_t) == 2 ? text_encoding("ISO-10646-UCS-2", details::id::UCS2)
                                : text_encoding("ISO-10646-UCS-4", details::id::UCS4);
#endif
}


template<text_encoding::id id_>
bool text_encoding::environment_is() noexcept {
#ifdef _WIN32
    return system().mib() == id_;
#else
    details::scoped_locale loc = newlocale(LC_CTYPE_MASK, "", (locale_t)0);
    const char* name = nl_langinfo_l(CODESET, loc);
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
    const char* name = nl_langinfo_l(CODESET, loc);
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
    return text_encoding(__GNUC_EXECUTION_CHARSET_NAME,
                         details::find_encoding(__GNUC_EXECUTION_CHARSET_NAME));
#elif defined(__clang_literal_encoding__)
    return text_encoding(__clang_literal_encoding__,
                         details::find_encoding(__clang_literal_encoding__));
#elif defined(__clang__)
    return text_encoding("UTF-8", details::id::UTF8);
#else
    return {};
#endif
}

consteval text_encoding text_encoding::wide_literal() {
#ifdef _WIN32
    // WINDOWS is always UTF-16
    return text_encoding("UTF-16", details::id::UTF16);
#elif defined(__GNUC_WIDE_EXECUTION_CHARSET_NAME)
    return text_encoding(__GNUC_WIDE_EXECUTION_CHARSET_NAME,
                         details::find_encoding(__GNUC_WIDE_EXECUTION_CHARSET_NAME));
#elif defined(__clang_wide_literal_encoding__)
    return text_encoding(__clang_wide_literal_encoding__,
                         details::find_encoding(__clang_wide_literal_encoding__));
#elif defined(__GNUC__) || defined(__clang__)
    return sizeof(wchar_t) == 2 ? text_encoding("ISO-10646-UCS-2", details::id::UCS2)
                                : text_encoding("ISO-10646-UCS-4", details::id::UCS4);
#else
    return {};
#endif
}
//#endif


}    // namespace cor3ntin::encoding