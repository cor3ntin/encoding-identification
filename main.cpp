#include <encodings.hpp>
#include <iostream>

void print(const cor3ntin::encoding::text_encoding & c) {
    std::cout << c.name()
             << " (iana mib: " << c.mib() << ")\n"
             << "Aliases:\n";
    for(auto && a : c.aliases()) {
        std::cout << '\t' << a << '\n';
    }
}

int main() {
    std::cout << "Literal Encoding: ";
    print(cor3ntin::encoding::text_encoding::literal());
    std::cout << "Wide Literal Encoding: ";
    print(cor3ntin::encoding::text_encoding::wide_literal());
    std::cout << "Runtime Encoding: ";
    print(cor3ntin::encoding::text_encoding::current());
    std::cout << "Wide runtime Encoding: ";
    print(cor3ntin::encoding::text_encoding::wide_current());
}