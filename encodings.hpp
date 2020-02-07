#pragma once
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

#ifndef H_COR3NTIN_ENCODINGS_HPP
#include "encodings_generated.hpp"
#include "encodings_base.hpp"
#endif

#ifdef __unix__
#include <langinfo.h>
#endif

#ifdef _WIN32
#include "windows.h"
#ifndef H_COR3NTIN_ENCODINGS_HPP
#include "encodings_windows.hpp"
#endif
#endif

namespace cor3ntin::encoding {

namespace details {

#ifdef _MSC_VER
    // FUNCTION TEMPLATE lower_bound
    template <class _FwdIt, class _Ty, class _Pr>
    _NODISCARD constexpr _FwdIt lower_bound(_FwdIt _First, const _FwdIt _Last, const _Ty& _Val, _Pr _Pred) {
        using namespace std;
        // find first element not before _Val, using _Pred
        _Adl_verify_range(_First, _Last);
        auto _UFirst = _Get_unwrapped(_First);
        std::_Iter_diff_t<_FwdIt> _Count = _STD distance(_UFirst, _Get_unwrapped(_Last));

        while (0 < _Count) { // divide and conquer, find half that contains answer
            const _Iter_diff_t<_FwdIt> _Count2 = _Count >> 1; // TRANSITION, VSO#433486
            const auto _UMid = _STD next(_UFirst, _Count2);
            if (_Pred(*_UMid, _Val)) { // try top half
                _UFirst = _Next_iter(_UMid);
                _Count -= _Count2 + 1;
            }
            else {
                _Count = _Count2;
            }
        }

        _Seek_wrapped(_First, _UFirst);
        return _First;
    }
    template <class _InIt, class _Diff, class _OutIt>
    constexpr _OutIt copy_n(_InIt _First, _Diff _Count_raw, _OutIt _Dest) { // copy [_First, _First + _Count) to [_Dest, ...)
        using namespace std;
        _Algorithm_int_t<_Diff> _Count = _Count_raw;
        if (0 < _Count) {
            auto _UFirst = _Get_unwrapped_n(_First, _Count);
            auto _UDest = _Get_unwrapped_n(_Dest, _Count);
            for (;;) {
                *_UDest = *_UFirst;
                ++_UDest;
                --_Count;
                if (_Count == 0) { // note that we avoid an extra ++_First here to allow istream_iterator to work,
                                   // see LWG#2471
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
#endif // def _MSC_VER


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
           d = alg::lower_bound(std::begin(data), std::end(data), mib, [] (const enc_data& d, int mib) {
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
    constexpr text_encoding(const char* name) : text_encoding(name, details::find_encoding(name)) {
    }
    constexpr text_encoding() noexcept : mib_(details::id::unknown) {}
private:
    constexpr text_encoding(const char* name, id mib)
        : mib_(mib == id::unknown ? details::id::other : mib)
     {

        std::size_t s = std::min(strlen(name), std::size_t(63));
        details::alg::copy_n(name, s, std::begin(name_));
        name_[s] = '\0';
    }
public:
    constexpr id mib() const noexcept{
        return mib_;
    }

    constexpr const char* name() const noexcept{
        if(name_[0] != '\0') {
            return name_.data();
        }
        const auto a = aliases();
        if(a.begin() != a.end()) {
            return *a.begin();
        }
        return nullptr;
    }

    constexpr details::encoding_alias_view aliases() const noexcept{
        return details::encoding_alias_view(int(mib_));
    }

#ifdef __cpp_consteval
    static consteval text_encoding literal();
    static consteval text_encoding wide_literal();
#endif

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
    std::array<char, 30> name_ = {0};
    id mib_ = id::unknown;
#ifdef _MSC_VER
    int m_code_page = 0;
#endif
};


inline text_encoding text_encoding::system() {
#ifdef _WIN32
    auto cp = GetACP();
    text_encoding e;
    e.mib_ = details::mib_from_page(cp);
    e.m_code_page = cp;
    return e;
#else
    details::scoped_locale loc = newlocale(LC_CTYPE_MASK, "", (locale_t)0);
    const char* name = nl_langinfo_l(CODESET, loc);
    const id mib = details::find_encoding(name);
    return text_encoding(name, mib);
#endif
}

inline text_encoding text_encoding::wide_system() {
#ifdef _WIN32
    // windows is always UTF-16LE
    return text_encoding("UTF-16LE", details::id::UTF16LE);
#else
    // GLIBC is always UCS4
    return
        sizeof(wchar_t) == 2 ?
    text_encoding("ISO-10646-UCS-2", details::id::Unicode):
    text_encoding("ISO-10646-UCS-4", details::id::UCS4);
#endif
}


template<text_encoding::id id_>
bool text_encoding::system_is() {
#ifdef _WIN32
    return system().mib() == id_;
#else
    details::scoped_locale loc = newlocale(LC_CTYPE_MASK, "", (locale_t)0);
    const char* name = nl_langinfo_l(CODESET, loc);
    return details::encoding_is<id_>(name);
#endif
}

template<text_encoding::id id_>
bool text_encoding::wide_system_is() {
    return wide_system().mib() == id_;
}

inline text_encoding text_encoding::for_locale(const std::locale& l) {
#ifdef _WIN32
#else
    details::scoped_locale loc = newlocale(LC_CTYPE, l.name().c_str(), 0);
    const char* name = nl_langinfo_l(CODESET, loc);
    const id mib = details::find_encoding(name);
    return text_encoding(name, mib);
#endif
}

inline text_encoding text_encoding::wide_for_locale(const std::locale& l) {
    return wide_system();
}

#ifdef __cpp_consteval
consteval text_encoding text_encoding::literal() {
#ifdef __GXX_PRESUMED_EXECUTION_ENCODING
    return text_encoding(__GXX_PRESUMED_EXECUTION_ENCODING,
        details::find_encoding(__GXX_PRESUMED_EXECUTION_ENCODING));
#else
    return text_encoding("UTF-8", details::id::UTF8);
#endif
}

consteval text_encoding text_encoding::wide_literal() {
#ifdef _WIN32
    // windOWS is always UTF-16LE ?
    return text_encoding("UTF-16LE", details::id::UTF16LE);
#elif defined(__GXX_PRESUMED_WIDE_EXECUTION_ENCODING)
    return text_encoding(__GXX_PRESUMED_WIDE_EXECUTION_ENCODING,
        details::find_encoding(__GXX_PRESUMED_WIDE_EXECUTION_ENCODING));
#else
    return text_encoding("UTF-16", details::id::UTF16);
#endif
}
#endif


}