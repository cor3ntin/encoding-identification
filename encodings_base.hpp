#pragma once
#include <initializer_list>
#include <algorithm>
#include <locale.h>
#include <cstring>

namespace cor3ntin::encoding::details {


class scoped_locale {
public:
    scoped_locale(locale_t loc): loc(loc) {}
    operator locale_t() const {return loc;}
    ~scoped_locale() {
        freelocale(loc);
    }
private:
    locale_t loc;
};

constexpr char tolower(const char c) {
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}





inline constexpr bool compare_name(const char* a, const char* b) noexcept {
    if(!a || !b)
        return false;
    auto la = a;
    auto lb = b;
    for(; *la != '\0' && *lb != '\0'; la++, lb++) {
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