#pragma once
#include <algorithm>
#include <locale>
#include <langinfo.h>

#include "encodings_generated.hpp"

namespace cor3ntin::encoding {

namespace details {
    constexpr bool compare_name(const char* a, const char* b) noexcept {
        auto la = a;
        auto lb = b;
        for(; *la != '\0', *lb != '\0'; la++, lb++) {
            while(*la == '-' || *la == '_') {
                la ++;
                if(*la == '\0') return false;
            }
            while(*lb == '-' || *lb == '_') {
                lb ++;
                if(*lb == '\0') return false;
            }
            if(tolower(*la) != tolower(*lb))
                return false;
        }
        return *la == *lb;
    }

    constexpr int find_encoding(const char* name) {
        if(!name)
            return unknown;
        for(auto && e = std::begin(data); e != std::end(data); e++) {
            if(compare_name(e->name, name))
                    return e->mib;
        }
        return other;
    }

    const char* locale_name(locale_t loc) {
        return nl_langinfo_l(CODESET, loc);
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

    /*constexpr*/ text_encoding() noexcept : mib_(2) {}
    /*constexpr*/ text_encoding(std::string name, int mib = id::other) noexcept
    : name_(name), mib_(mib) {}

    constexpr int mib() const noexcept{
        return mib_;
    }

    const char* name() const noexcept{
        return name_.c_str();
    }

    details::encoding_alias_view aliases() const noexcept{
        return details::encoding_alias_view(mib_);
    }

    static /*consteval*/ text_encoding literal();
    static /*consteval*/ text_encoding wide_literal();

    static text_encoding current();
    static text_encoding wide_current();

    static text_encoding for_locale(const std::locale&);
    static text_encoding wide_for_locale(const std::locale&);

    bool operator==(const text_encoding & other) {
        if(mib() < 3 && other.mib() < 3) {
            return other.name() == name();
        }
        return other.mib() == mib();
    }


private:
    std::string name_;
    int mib_;
};


text_encoding text_encoding::current() {
    const char* saved = std::setlocale(LC_ALL, "");
    locale_t loc = duplocale(LC_GLOBAL_LOCALE);
    const char* name = details::locale_name(loc);
    const int mib = details::find_encoding(name);
    freelocale(loc);
    std::setlocale(LC_ALL, saved);
    return text_encoding(name, mib);
}

text_encoding text_encoding::wide_current() {
    // GLIBC is always UCS4
    return text_encoding("ISO-10646-UCS-4", details::id::UCS4);
}

text_encoding text_encoding::for_locale(const std::locale& l) {
    locale_t loc = newlocale(LC_CTYPE, l.name().c_str(), 0);
    const char* name = details::locale_name(loc);
    const int mib = details::find_encoding(name);
    freelocale(loc);
    return text_encoding(name, mib);
}

text_encoding text_encoding::wide_for_locale(const std::locale& l) {
    return wide_current();
}

text_encoding text_encoding::literal() {
    return text_encoding("UTF-8", details::id::UTF8);
}

text_encoding text_encoding::wide_literal() {
    return text_encoding("ISO-10646-UCS-4", details::id::UCS4);
}


}