#pragma once
#include <initializer_list>
#include <algorithm>
#include <locale.h>
#include <cstring>
#include <string_view>

#ifdef __APPLE__
#include <xlocale.h>
#include <langinfo.h>
#endif

namespace cor3ntin::encoding::details {


#if !defined(_WIN32)
class scoped_locale {
public:
    scoped_locale(locale_t loc): loc(loc) {}
    operator locale_t() const {return loc;}
    ~scoped_locale() {
        if(loc)
            freelocale(loc);
    }
    operator bool() const {
        return loc;
    }

private:
    locale_t loc;
};
#endif


constexpr char tolower(const char c) {
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}





inline constexpr bool compare_name(std::string_view a, std::string_view b) noexcept {
    if(a.empty() || b.empty())
        return false;
    auto la = a.begin();
    auto lb = b.begin();
    for(; la != a.end()  && lb != b.end(); la++, lb++) {
        while(*la == '-' || *la == '_') {
            la ++;
        }
        while(*lb == '-' || *lb == '_') {
            lb ++;
        }
        if(details::tolower(*la) != details::tolower(*lb))
            return false;
    }
    return *la == *lb;
}

constexpr bool do_compare(std::initializer_list<const char*> names, const char* name) {
    for(const char* n: names) {
        if(compare_name(n, name))
            return true;
    }
    return false;
}

}