#include <cor3ntin/encodings_detection.hpp>
#include <cstdlib>
#include <iostream>

void print(const cor3ntin::encoding::text_encoding& c) {
    if(c.name()) {
        std::cout << c.name() << " (iana mib: " << int(c.mib()) << ")\n"
                  << "Aliases:\n";
    } else {
        std::cout << "Not implemented\n";
    }
    for(auto&& a : c.aliases()) {
        std::cout << '\t' << a << '\n';
    }
}

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
}