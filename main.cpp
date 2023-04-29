#include <cor3ntin/encodings_detection.hpp>
#include <cstdlib>
#include <cassert>
#include <iostream>

constexpr cor3ntin::encoding::text_encoding def{};
static_assert(def.mib() == cor3ntin::encoding::text_encoding::id::unknown);
static_assert(def.name() == nullptr);
static_assert(def == def);

constexpr cor3ntin::encoding::text_encoding other{cor3ntin::encoding::text_encoding::id::other};
static_assert(other.mib() == cor3ntin::encoding::text_encoding::id::other);
static_assert(other.name() == nullptr);

constexpr cor3ntin::encoding::text_encoding unknown{cor3ntin::encoding::text_encoding::id::unknown};
static_assert(unknown.mib() == cor3ntin::encoding::text_encoding::id::unknown);
static_assert(unknown.name() == nullptr);

constexpr cor3ntin::encoding::text_encoding empty{""};
static_assert(empty.mib() == cor3ntin::encoding::text_encoding::id::other);
static_assert(empty.name() == nullptr);

void print(const cor3ntin::encoding::text_encoding& c) {
    if(c.name()) {
        std::cout << c.name() << " (iana mib: " << int(c.mib()) << ")\n"
                  << "Aliases:\n";
    } else {
        std::cout << "<No name>\n";
    }
    for(auto&& a : c.aliases()) {
        std::cout << '\t' << a << '\n';
    }
}

void runtime_tests();

int main() {
    putenv("LC_CTYPE=en_US");
    std::cout << "Literal Encoding: ";
    print(cor3ntin::encoding::text_encoding::literal());
    std::cout << "Wide Literal Encoding: ";
    print(cor3ntin::encoding::text_encoding::wide_literal());
    std::cout << "Runtime Encoding: ";
    print(cor3ntin::encoding::text_encoding::environment());
    std::cout << "Wide runtime Encoding: ";
    print(cor3ntin::encoding::text_encoding::wide_environment());

    runtime_tests();
}

using namespace std::literals;

void runtime_tests() {
    cor3ntin::encoding::text_encoding def1{}, def2{};
    assert(def1 == def2);
    cor3ntin::encoding::text_encoding wtf8("WTF-8");
    print(wtf8);
    assert(wtf8.name() != nullptr && wtf8.name() == "WTF-8"sv);
    assert(wtf8.mib() == cor3ntin::encoding::text_encoding::id::other);
    cor3ntin::encoding::text_encoding wtf8_2("WTF8");
    print(wtf8_2);
    assert(wtf8_2.name() != nullptr && wtf8_2.name() == "WTF8"sv);
    assert(wtf8_2.mib() == cor3ntin::encoding::text_encoding::id::other);
    assert(wtf8 == wtf8_2);
#if __cpp_lib_ranges_contains
    assert(!std::ranges::contains(wtf8.aliases(), std::string_view(wtf8.name())));
#else
    assert(std::ranges::find(std::ranges::begin(wtf8.aliases()), 
                             std::ranges::end(wtf8.aliases()),
                             std::string_view(wtf8.name())) == std::ranges::end(wtf8.aliases()));
#endif
    { 
      cor3ntin::encoding::text_encoding utf8_1("u.t.f-008");
      cor3ntin::encoding::text_encoding utf8_2("utf8");
      cor3ntin::encoding::text_encoding utf8_3("UTF-8");
      cor3ntin::encoding::text_encoding not_utf8("UTF-80");

      assert(utf8_1 == utf8_2);
      assert(utf8_1 == utf8_3);
      assert(utf8_2 == utf8_3);
      assert(utf8_1.mib() == cor3ntin::encoding::text_encoding::id::UTF8);
      assert(utf8_2.mib() == cor3ntin::encoding::text_encoding::id::UTF8);
      assert(utf8_3.mib() == cor3ntin::encoding::text_encoding::id::UTF8);
      assert(utf8_1 != not_utf8);
      assert(utf8_2 != not_utf8);
      assert(utf8_3 != not_utf8);
    }
    {
      cor3ntin::encoding::text_encoding t1("1-0");
      cor3ntin::encoding::text_encoding t2("1-");
      assert(t1 != t2);
    }
    { 
      const bool data_is_sorted = std::is_sorted(std::begin(cor3ntin::encoding::details::data),
                                                 std::end(cor3ntin::encoding::details::data), 
                                                 [](const auto& a, const auto& b) { return a.mib < b.mib; });
      assert(data_is_sorted);
    }
#if defined(_WIN32)
    {
      const bool win_mapping_is_sorted =
          std::is_sorted(std::begin(cor3ntin::encoding::details::win_mapping),
                         std::end(cor3ntin::encoding::details::win_mapping),
                         [](const auto& a, const auto& b) { return a.cp < b.cp; });
      assert(win_mapping_is_sorted);
    }
#endif
}
