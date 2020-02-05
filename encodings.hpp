#pragma once
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
#include <locale>
#include <langinfo.h>

namespace cor3ntin::encoding {

namespace details {

    constexpr details::id find_encoding(const char* name) {
        if(!name)
            return details::id::unknown;
        for(auto && e = std::begin(data); e != std::end(data); e++) {
            if(compare_name(e->name, name))
                    return details::id(e->mib);
        }
        return details::id::unknown;
    }

    struct encoding_alias_view {

    constexpr encoding_alias_view(int mib) : mib(mib){};
    struct sentinel {};
    struct iterator {
        using iterator_category = std::forward_iterator_tag;

        constexpr iterator(int mib ) : mib(mib) {
            d = std::lower_bound(std::begin(data), std::end(data), mib, [] (const enc_data& d, int mib) {
                return d.mib < mib;
            });
        }

        constexpr const char* operator*() const {
            return d->name;
        }

        constexpr iterator& operator++(int) {
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
}


struct text_encoding {
    using id = details::id;

    constexpr text_encoding() noexcept : mib_(details::id::unknown) {}
private:
    constexpr text_encoding(const char* name, id mib = id::other)
    : mib_(mib) {
        std::size_t s = std::min(strlen(name), std::size_t(63));
        std::copy_n(name, s, std::begin(name_));
        name_[s] = '\0';
    }
public:
    constexpr id mib() const noexcept{
        return mib_;
    }

    const char* name() const noexcept{
        if(!name_.empty()) {
            return name_.data();
        }
        const auto a = aliases();
        if(a.begin() != a.end()) {
            return *a.begin();
        }
        return nullptr;
    }

    details::encoding_alias_view aliases() const noexcept{
        return details::encoding_alias_view(int(mib_));
    }

    static consteval text_encoding literal();
    static consteval text_encoding wide_literal();

    static inline text_encoding system();
    static inline text_encoding wide_system();

    template<id id>
    static bool system_is();

    template<id id>
    static bool wide_system_is();

    static inline text_encoding for_locale(const std::locale&);
    static inline text_encoding wide_for_locale(const std::locale&);

    constexpr bool operator==(const text_encoding & other) {
        if(mib() <= id::unknown && other.mib() <= id::unknown) {
            return other.name() == name();
        }
        return other.mib() == mib();
    }


private:
    //poor man constexpr string
    std::array<char, 30> name_ = {};
    id mib_ = id::unknown;
};


inline text_encoding text_encoding::system() {
    details::scoped_locale loc = newlocale(LC_CTYPE_MASK, "", (locale_t)0);
    const char* name = nl_langinfo_l(CODESET, loc);
    const id mib = details::find_encoding(name);
    return text_encoding(name, mib);
}

inline text_encoding text_encoding::wide_system() {
#ifdef WIN32
    // windows is always UTF-16LE
    return text_encoding("UTF-16LE", details::id::UTF16LE);
#else
    // GLIBC is always UCS4
    return text_encoding("ISO-10646-UCS-4", details::id::UCS4);
#endif
}


template<text_encoding::id id_>
bool text_encoding::system_is() {
#ifdef WIN32
    //TODO
#else
    details::scoped_locale loc = newlocale(LC_CTYPE_MASK, "", (locale_t)0);
    const char* name = nl_langinfo_l(CODESET, loc);
    return details::encoding_is<id_>(name);
#endif
}

template<text_encoding::id id_>
bool text_encoding::wide_system_is() {
#ifdef WIN32
    //TODO
#else
    // GLIBC is always UCS4
    return id_ == details::id::UCS4;
#endif
}

inline text_encoding text_encoding::for_locale(const std::locale& l) {
    details::scoped_locale loc = newlocale(LC_CTYPE, l.name().c_str(), 0);
    const char* name = nl_langinfo_l(CODESET, loc);
    const id mib = details::find_encoding(name);
    return text_encoding(name, mib);
}

inline text_encoding text_encoding::wide_for_locale(const std::locale& l) {
    return wide_system();
}

consteval text_encoding text_encoding::literal() {
#ifdef __GXX_PRESUMED_EXECUTION_ENCODING
    return text_encoding(__GXX_PRESUMED_EXECUTION_ENCODING,
        details::find_encoding(__GXX_PRESUMED_EXECUTION_ENCODING));
#else
    return text_encoding("UTF-8", details::id::UTF8);
#endif
}

consteval text_encoding text_encoding::wide_literal() {
#ifdef WIN32
    // windOWS is always UTF-16LE ?
    return text_encoding("UTF-16LE", details::id::UTF16LE);
#elif defined(__GXX_PRESUMED_WIDE_EXECUTION_ENCODING)
    return text_encoding(__GXX_PRESUMED_WIDE_EXECUTION_ENCODING,
        details::find_encoding(__GXX_PRESUMED_WIDE_EXECUTION_ENCODING));
#else
    return text_encoding("UTF-16", details::id::UTF16);
#endif
}


}