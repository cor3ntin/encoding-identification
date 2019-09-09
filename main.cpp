#include <encodings.hpp>
#include <iostream>

int main() {
    //std::setlocale(LC_ALL, "");
    auto c = cor3ntin::encoding::text_encoding::current();
    std::cout << c.name() << "\n";
    for(auto && a : c.aliases()) {
        std::cout << a << '\n';
    }
}