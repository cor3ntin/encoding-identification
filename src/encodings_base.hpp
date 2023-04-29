#pragma once
#include <initializer_list>
#include <algorithm>
#include <locale.h>
#include <cstring>
#include <string_view>

#ifdef __APPLE__
#    include <xlocale.h>
#    include <langinfo.h>
#endif

namespace cor3ntin::encoding::details {

#if !defined(_WIN32)
class scoped_locale {
public:
    explicit scoped_locale(locale_t loc) noexcept : loc(loc) {}
    scoped_locale(const scoped_locale&) = delete;
    scoped_locale& operator=(const scoped_locale&) = delete;
    operator locale_t() const noexcept {
        return loc;
    }
    ~scoped_locale() {
        if(loc)
            freelocale(loc);
    }
    explicit operator bool() const noexcept {
        return loc;
    }
private:
    locale_t loc;
};
#endif

constexpr char tolower(const char c) noexcept {
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

constexpr bool isnonzerodigit(const char c) noexcept {
  return (c >= '1' && c <= '9');
}

constexpr bool isalnum(const char c) noexcept {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

constexpr bool compare_name(std::string_view a, std::string_view b) noexcept {
    const auto ba = a.begin();
    const auto bb = b.begin();
    const auto ea = a.end();
    const auto eb = b.end();
    auto la = ba;
    auto lb = bb;
    bool numprefix_a = false;
    bool numprefix_b = false;
    for (;; ++la, ++lb) {
        while (la != ea && !details::isalnum(*la)) {
            ++la;
        }
        if (!numprefix_a) {
            while (la != ea && *la == '0') {
                ++la;
            }
        }
        while (lb != eb && !details::isalnum(*lb)) {
            ++lb;
        }
        if (!numprefix_b) {
            while (lb != eb && *lb == '0') {
                ++lb;
            }
        }
        if (la == ea) {
            return lb == eb;
        }
        if (lb == eb) {
            return false;
        }
        if (details::tolower(*la) != details::tolower(*lb)) {
            return false;
        }
        numprefix_a = details::isnonzerodigit(*la);
        numprefix_b = details::isnonzerodigit(*lb);
    }
}

constexpr bool do_compare(std::initializer_list<const char*> names, const char* name) noexcept {
    for(const char* n : names) {
        if(compare_name(n, name))
            return true;
    }
    return false;
}

}    // namespace cor3ntin::encoding::details
