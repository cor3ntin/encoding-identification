#pragma once
#ifndef H_COR3NTIN_ENCODINGS_HPP
#    include "encodings_generated.hpp"
#endif

#ifdef _WIN32
namespace cor3ntin::encoding::details {
struct encoding_windows_data {
    int cp;
    id id;
};
constexpr inline encoding_windows_data win_mapping[] = 
                                                {{ 37, id::IBM037},
                                                 {437, id::PC8CodePage437},
                                                 {500, id::IBM500},
                                                 {708, id::ISOLatinArabic},
                                                 {709, id::ISO89ASMO449},
                                                 //      {710, id::other},
                                                 //      {720, id::other},
                                                 //      {737, id::other},
                                                 {775, id::PC775Baltic},
                                                 {850, id::PC850Multilingual},
                                                 {852, id::PCp852},
                                                 {855, id::IBM855},
                                                 {857, id::IBM857},
                                                 {858, id::IBM00858},
                                                 {860, id::IBM860},
                                                 {861, id::IBM861},
                                                 {862, id::PC862LatinHebrew},
                                                 {863, id::IBM863},
                                                 {864, id::IBM864},
                                                 {865, id::IBM865},
                                                 {865, id::IBM865},
                                                 {866, id::IBM866},
                                                 {869, id::IBM869},
                                                 {870, id::IBM870},
                                                 {874, id::windows874},
                                                 //      {875, id::other},
                                                 {932, id::Windows31J},
                                                 {936, id::GB2312},
                                                 {949, id::KSC56011987},
                                                 {950, id::Big5},
                                                 {1026, id::IBM1026},
                                                 {1047, id::IBM1047},
                                                 {1140, id::IBM01140},
                                                 {1141, id::IBM01141},
                                                 {1142, id::IBM01142},
                                                 {1143, id::IBM01143},
                                                 {1144, id::IBM01144},
                                                 {1145, id::IBM01145},
                                                 {1146, id::IBM01146},
                                                 {1146, id::IBM01146},
                                                 {1147, id::IBM01147},
                                                 {1148, id::IBM01148},
                                                 {1149, id::IBM01149},
                                                 {1200, id::UTF16LE},
                                                 {1201, id::UTF16BE},
                                                 {1250, id::windows1250},
                                                 {1251, id::windows1251},
                                                 {1252, id::windows1252},
                                                 {1253, id::windows1253},
                                                 {1254, id::windows1254},
                                                 {1255, id::windows1255},
                                                 {1256, id::windows1256},
                                                 {1257, id::windows1257},
                                                 {1258, id::windows1258},
                                                 //      {1361, id::other},
                                                 {10000, id::Macintosh},
                                                 {12000, id::UTF32LE},
                                                 {12001, id::UTF32BE},
                                                 {20127, id::ASCII},

                                                 {20273, id::IBM273},
                                                 {20277, id::IBM277},
                                                 {20278, id::IBM278},
                                                 {20280, id::IBM280},
                                                 {20284, id::IBM284},
                                                 {20285, id::IBM285},
                                                 {20290, id::IBM290},
                                                 {20297, id::IBM297},
                                                 {20420, id::IBM420},
                                                 {20423, id::IBM423},
                                                 {20424, id::IBM424},

                                                 {20838, id::IBMThai},
                                                 {20866, id::KOI8R},
                                                 {20871, id::IBM871},
                                                 {20880, id::IBM880},
                                                 {20905, id::IBM905},
                                                 {20924, id::IBM00924},
                                                 {20932, id::EUCPkdFmtJapanese},
                                                 {21866, id::KOI8U},

                                                 {28591, id::ISOLatin1},
                                                 {28592, id::ISOLatin2},
                                                 {28593, id::ISOLatin3},
                                                 {28594, id::ISOLatin4},
                                                 {28595, id::ISOLatin5},
                                                 {28596, id::ISOLatin6},
                                                 {28597, id::ISOLatinGreek},
                                                 {28598, id::ISOLatinHebrew},
                                                 {28599, id::Windows31Latin5},
                                                 {28603, id::ISO885913},
                                                 {28605, id::ISO885915},

                                                 {38598, id::ISO88598I},
                                                 {50220, id::ISO2022JP},
                                                 {50221, id::ISO2022JP},
                                                 {50222, id::ISO2022JP},

                                                 {51932, id::EUCPkdFmtJapanese},
                                                 {51936, id::GB2312},
                                                 {51949, id::EUCKR},
                                                 {52936, id::HZGB2312},
                                                 {54936, id::GB18030},
                                                 {65000, id::UTF7},
                                                 {65001, id::UTF8}};

constexpr id mib_from_page(int page) noexcept {
    const auto end = std::end(win_mapping);
    const auto it = std::lower_bound(std::begin(win_mapping), end, page,
        [](const encoding_windows_data& d, int page) { return d.cp < page; });
    if(it != end && it->cp == page) {
        return it->id;        
    }
    return id::other;
}
}    // namespace cor3ntin::encoding::details
#endif
