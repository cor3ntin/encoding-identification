#ifndef H_COR3NTIN_ENCODINGS_HPP

#define H_COR3NTIN_ENCODINGS_HPP


#include <initializer_list>
#include <algorithm>
#include <locale.h>
#include <cstring>

namespace cor3ntin::encoding::details {


#ifndef _WIN32
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
#endif


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

namespace cor3ntin::encoding::details {
        enum class id {
            other = 1,
            unknown = 2,
            ASCII = 3,
            ISOLatin1 = 4,
            ISOLatin2 = 5,
            ISOLatin3 = 6,
            ISOLatin4 = 7,
            ISOLatinCyrillic = 8,
            ISOLatinArabic = 9,
            ISOLatinGreek = 10,
            ISOLatinHebrew = 11,
            ISOLatin5 = 12,
            ISOLatin6 = 13,
            ISOTextComm = 14,
            HalfWidthKatakana = 15,
            JISEncoding = 16,
            ShiftJIS = 17,
            EUCPkdFmtJapanese = 18,
            EUCFixWidJapanese = 19,
            ISO4UnitedKingdom = 20,
            ISO11SwedishForNames = 21,
            ISO15Italian = 22,
            ISO17Spanish = 23,
            ISO21German = 24,
            ISO60DanishNorwegian = 25,
            ISO69French = 26,
            ISO10646UTF1 = 27,
            ISO646basic1983 = 28,
            INVARIANT = 29,
            ISO2IntlRefVersion = 30,
            NATSSEFI = 31,
            NATSSEFIADD = 32,
            NATSDANO = 33,
            NATSDANOADD = 34,
            ISO10Swedish = 35,
            KSC56011987 = 36,
            ISO2022KR = 37,
            EUCKR = 38,
            ISO2022JP = 39,
            ISO2022JP2 = 40,
            ISO13JISC6220jp = 41,
            ISO14JISC6220ro = 42,
            ISO16Portuguese = 43,
            ISO18Greek7Old = 44,
            ISO19LatinGreek = 45,
            ISO25French = 46,
            ISO27LatinGreek1 = 47,
            ISO5427Cyrillic = 48,
            ISO42JISC62261978 = 49,
            ISO47BSViewdata = 50,
            ISO49INIS = 51,
            ISO50INIS8 = 52,
            ISO51INISCyrillic = 53,
            ISO54271981 = 54,
            ISO5428Greek = 55,
            ISO57GB1988 = 56,
            ISO58GB231280 = 57,
            ISO61Norwegian2 = 58,
            ISO70VideotexSupp1 = 59,
            ISO84Portuguese2 = 60,
            ISO85Spanish2 = 61,
            ISO86Hungarian = 62,
            ISO87JISX0208 = 63,
            ISO88Greek7 = 64,
            ISO89ASMO449 = 65,
            ISO90 = 66,
            ISO91JISC62291984a = 67,
            ISO92JISC62991984b = 68,
            ISO93JIS62291984badd = 69,
            ISO94JIS62291984hand = 70,
            ISO95JIS62291984handadd = 71,
            ISO96JISC62291984kana = 72,
            ISO2033 = 73,
            ISO99NAPLPS = 74,
            ISO102T617bit = 75,
            ISO103T618bit = 76,
            ISO111ECMACyrillic = 77,
            ISO121Canadian1 = 78,
            ISO122Canadian2 = 79,
            ISO123CSAZ24341985gr = 80,
            ISO88596E = 81,
            ISO88596I = 82,
            ISO128T101G2 = 83,
            ISO88598E = 84,
            ISO88598I = 85,
            ISO139CSN369103 = 86,
            ISO141JUSIB1002 = 87,
            ISO143IECP271 = 88,
            ISO146Serbian = 89,
            ISO147Macedonian = 90,
            ISO150 = 91,
            ISO151Cuba = 92,
            ISO6937Add = 93,
            ISO153GOST1976874 = 94,
            ISO8859Supp = 95,
            ISO10367Box = 96,
            ISO158Lap = 97,
            ISO159JISX02121990 = 98,
            ISO646Danish = 99,
            USDK = 100,
            DKUS = 101,
            KSC5636 = 102,
            Unicode11UTF7 = 103,
            ISO2022CN = 104,
            ISO2022CNEXT = 105,
            UTF8 = 106,
            ISO885913 = 109,
            ISO885914 = 110,
            ISO885915 = 111,
            ISO885916 = 112,
            GBK = 113,
            GB18030 = 114,
            OSDEBCDICDF0415 = 115,
            OSDEBCDICDF03IRV = 116,
            OSDEBCDICDF041 = 117,
            ISO115481 = 118,
            KZ1048 = 119,
            Unicode = 1000,
            UCS4 = 1001,
            UnicodeASCII = 1002,
            UnicodeLatin1 = 1003,
            UnicodeJapanese = 1004,
            UnicodeIBM1261 = 1005,
            UnicodeIBM1268 = 1006,
            UnicodeIBM1276 = 1007,
            UnicodeIBM1264 = 1008,
            UnicodeIBM1265 = 1009,
            Unicode11 = 1010,
            SCSU = 1011,
            UTF7 = 1012,
            UTF16BE = 1013,
            UTF16LE = 1014,
            UTF16 = 1015,
            CESU8 = 1016,
            UTF32 = 1017,
            UTF32BE = 1018,
            UTF32LE = 1019,
            BOCU1 = 1020,
            Windows30Latin1 = 2000,
            Windows31Latin1 = 2001,
            Windows31Latin2 = 2002,
            Windows31Latin5 = 2003,
            HPRoman8 = 2004,
            AdobeStandardEncoding = 2005,
            VenturaUS = 2006,
            VenturaInternational = 2007,
            DECMCS = 2008,
            PC850Multilingual = 2009,
            PC8DanishNorwegian = 2012,
            PC862LatinHebrew = 2013,
            PC8Turkish = 2014,
            IBMSymbols = 2015,
            IBMThai = 2016,
            HPLegal = 2017,
            HPPiFont = 2018,
            HPMath8 = 2019,
            HPPSMath = 2020,
            HPDesktop = 2021,
            VenturaMath = 2022,
            MicrosoftPublishing = 2023,
            Windows31J = 2024,
            GB2312 = 2025,
            Big5 = 2026,
            Macintosh = 2027,
            IBM037 = 2028,
            IBM038 = 2029,
            IBM273 = 2030,
            IBM274 = 2031,
            IBM275 = 2032,
            IBM277 = 2033,
            IBM278 = 2034,
            IBM280 = 2035,
            IBM281 = 2036,
            IBM284 = 2037,
            IBM285 = 2038,
            IBM290 = 2039,
            IBM297 = 2040,
            IBM420 = 2041,
            IBM423 = 2042,
            IBM424 = 2043,
            PC8CodePage437 = 2011,
            IBM500 = 2044,
            IBM851 = 2045,
            PCp852 = 2010,
            IBM855 = 2046,
            IBM857 = 2047,
            IBM860 = 2048,
            IBM861 = 2049,
            IBM863 = 2050,
            IBM864 = 2051,
            IBM865 = 2052,
            IBM868 = 2053,
            IBM869 = 2054,
            IBM870 = 2055,
            IBM871 = 2056,
            IBM880 = 2057,
            IBM891 = 2058,
            IBM903 = 2059,
            IBBM904 = 2060,
            IBM905 = 2061,
            IBM918 = 2062,
            IBM1026 = 2063,
            IBMEBCDICATDE = 2064,
            EBCDICATDEA = 2065,
            EBCDICCAFR = 2066,
            EBCDICDKNO = 2067,
            EBCDICDKNOA = 2068,
            EBCDICFISE = 2069,
            EBCDICFISEA = 2070,
            EBCDICFR = 2071,
            EBCDICIT = 2072,
            EBCDICPT = 2073,
            EBCDICES = 2074,
            EBCDICESA = 2075,
            EBCDICESS = 2076,
            EBCDICUK = 2077,
            EBCDICUS = 2078,
            Unknown8BiT = 2079,
            Mnemonic = 2080,
            Mnem = 2081,
            VISCII = 2082,
            VIQR = 2083,
            KOI8R = 2084,
            HZGB2312 = 2085,
            IBM866 = 2086,
            PC775Baltic = 2087,
            KOI8U = 2088,
            IBM00858 = 2089,
            IBM00924 = 2090,
            IBM01140 = 2091,
            IBM01141 = 2092,
            IBM01142 = 2093,
            IBM01143 = 2094,
            IBM01144 = 2095,
            IBM01145 = 2096,
            IBM01146 = 2097,
            IBM01147 = 2098,
            IBM01148 = 2099,
            IBM01149 = 2100,
            Big5HKSCS = 2101,
            IBM1047 = 2102,
            PTCP154 = 2103,
            Amiga1251 = 2104,
            KOI7switched = 2105,
            BRF = 2106,
            TSCII = 2107,
            CP51932 = 2108,
            windows874 = 2109,
            windows1250 = 2250,
            windows1251 = 2251,
            windows1252 = 2252,
            windows1253 = 2253,
            windows1254 = 2254,
            windows1255 = 2255,
            windows1256 = 2256,
            windows1257 = 2257,
            windows1258 = 2258,
            TIS620 = 2259,
            CP50220 = 2260,

            reserved = 3000
        };
        struct enc_data {
            int mib;
            const char* name;
        };
        constexpr bool compare_name(const char* a, const char* b) noexcept;
        constexpr inline enc_data data[] = {
            { 3, "US-ASCII" },
            { 3, "ANSI_X3.4-1968" },
            { 3, "ANSI_X3.4-1986" },
            { 3, "IBM367" },
            { 3, "ISO646-US" },
            { 3, "ISO_646.irv:1991" },
            { 3, "cp367" },
            { 3, "csASCII" },
            { 3, "iso-ir-6" },
            { 3, "us" },
            { 4, "ISO-8859-1" },
            { 4, "ISO_8859-1:1987" },
            { 4, "CP819" },
            { 4, "IBM819" },
            { 4, "ISO_8859-1" },
            { 4, "csISOLatin1" },
            { 4, "iso-ir-100" },
            { 4, "l1" },
            { 4, "latin1" },
            { 5, "ISO-8859-2" },
            { 5, "ISO_8859-2:1987" },
            { 5, "ISO_8859-2" },
            { 5, "csISOLatin2" },
            { 5, "iso-ir-101" },
            { 5, "l2" },
            { 5, "latin2" },
            { 6, "ISO-8859-3" },
            { 6, "ISO_8859-3:1988" },
            { 6, "ISO_8859-3" },
            { 6, "csISOLatin3" },
            { 6, "iso-ir-109" },
            { 6, "l3" },
            { 6, "latin3" },
            { 7, "ISO-8859-4" },
            { 7, "ISO_8859-4:1988" },
            { 7, "ISO_8859-4" },
            { 7, "csISOLatin4" },
            { 7, "iso-ir-110" },
            { 7, "l4" },
            { 7, "latin4" },
            { 8, "ISO-8859-5" },
            { 8, "ISO_8859-5:1988" },
            { 8, "ISO_8859-5" },
            { 8, "csISOLatinCyrillic" },
            { 8, "cyrillic" },
            { 8, "iso-ir-144" },
            { 9, "ISO-8859-6" },
            { 9, "ISO_8859-6:1987" },
            { 9, "ASMO-708" },
            { 9, "ECMA-114" },
            { 9, "ISO_8859-6" },
            { 9, "arabic" },
            { 9, "csISOLatinArabic" },
            { 9, "iso-ir-127" },
            { 10, "ISO-8859-7" },
            { 10, "ISO_8859-7:1987" },
            { 10, "ECMA-118" },
            { 10, "ELOT_928" },
            { 10, "ISO_8859-7" },
            { 10, "csISOLatinGreek" },
            { 10, "greek" },
            { 10, "greek8" },
            { 10, "iso-ir-126" },
            { 11, "ISO-8859-8" },
            { 11, "ISO_8859-8:1988" },
            { 11, "ISO_8859-8" },
            { 11, "csISOLatinHebrew" },
            { 11, "hebrew" },
            { 11, "iso-ir-138" },
            { 12, "ISO-8859-9" },
            { 12, "ISO_8859-9:1989" },
            { 12, "ISO_8859-9" },
            { 12, "csISOLatin5" },
            { 12, "iso-ir-148" },
            { 12, "l5" },
            { 12, "latin5" },
            { 13, "ISO-8859-10" },
            { 13, "ISO_8859-10:1992" },
            { 13, "csISOLatin6" },
            { 13, "iso-ir-157" },
            { 13, "l6" },
            { 13, "latin6" },
            { 14, "ISO_6937-2-add" },
            { 14, "csISOTextComm" },
            { 14, "iso-ir-142" },
            { 15, "JIS_X0201" },
            { 15, "X0201" },
            { 15, "csHalfWidthKatakana" },
            { 16, "JIS_Encoding" },
            { 16, "csJISEncoding" },
            { 17, "Shift_JIS" },
            { 17, "MS_Kanji" },
            { 17, "csShiftJIS" },
            { 18, "EUC-JP" },
            { 18, "Extended_UNIX_Code_Packed_Format_for_Japanese" },
            { 18, "csEUCPkdFmtJapanese" },
            { 19, "Extended_UNIX_Code_Fixed_Width_for_Japanese" },
            { 19, "csEUCFixWidJapanese" },
            { 20, "BS_4730" },
            { 20, "ISO646-GB" },
            { 20, "csISO4UnitedKingdom" },
            { 20, "gb" },
            { 20, "iso-ir-4" },
            { 20, "uk" },
            { 21, "SEN_850200_C" },
            { 21, "ISO646-SE2" },
            { 21, "csISO11SwedishForNames" },
            { 21, "iso-ir-11" },
            { 21, "se2" },
            { 22, "IT" },
            { 22, "ISO646-IT" },
            { 22, "csISO15Italian" },
            { 22, "iso-ir-15" },
            { 23, "ES" },
            { 23, "ISO646-ES" },
            { 23, "csISO17Spanish" },
            { 23, "iso-ir-17" },
            { 24, "DIN_66003" },
            { 24, "ISO646-DE" },
            { 24, "csISO21German" },
            { 24, "de" },
            { 24, "iso-ir-21" },
            { 25, "NS_4551-1" },
            { 25, "ISO646-NO" },
            { 25, "csISO60DanishNorwegian" },
            { 25, "csISO60Norwegian1" },
            { 25, "iso-ir-60" },
            { 25, "no" },
            { 26, "NF_Z_62-010" },
            { 26, "ISO646-FR" },
            { 26, "csISO69French" },
            { 26, "fr" },
            { 26, "iso-ir-69" },
            { 27, "ISO-10646-UTF-1" },
            { 27, "csISO10646UTF1" },
            { 28, "ISO_646.basic:1983" },
            { 28, "csISO646basic1983" },
            { 28, "ref" },
            { 29, "INVARIANT" },
            { 29, "csINVARIANT" },
            { 30, "ISO_646.irv:1983" },
            { 30, "csISO2IntlRefVersion" },
            { 30, "irv" },
            { 30, "iso-ir-2" },
            { 31, "NATS-SEFI" },
            { 31, "csNATSSEFI" },
            { 31, "iso-ir-8-1" },
            { 32, "NATS-SEFI-ADD" },
            { 32, "csNATSSEFIADD" },
            { 32, "iso-ir-8-2" },
            { 33, "NATS-DANO" },
            { 33, "csNATSDANO" },
            { 33, "iso-ir-9-1" },
            { 34, "NATS-DANO-ADD" },
            { 34, "csNATSDANOADD" },
            { 34, "iso-ir-9-2" },
            { 35, "SEN_850200_B" },
            { 35, "FI" },
            { 35, "ISO646-FI" },
            { 35, "ISO646-SE" },
            { 35, "csISO10Swedish" },
            { 35, "iso-ir-10" },
            { 35, "se" },
            { 36, "KS_C_5601-1987" },
            { 36, "KSC_5601" },
            { 36, "KS_C_5601-1989" },
            { 36, "csKSC56011987" },
            { 36, "iso-ir-149" },
            { 36, "korean" },
            { 37, "ISO-2022-KR" },
            { 37, "csISO2022KR" },
            { 38, "EUC-KR" },
            { 38, "csEUCKR" },
            { 39, "ISO-2022-JP" },
            { 39, "csISO2022JP" },
            { 40, "ISO-2022-JP-2" },
            { 40, "csISO2022JP2" },
            { 41, "JIS_C6220-1969-jp" },
            { 41, "JIS_C6220-1969" },
            { 41, "csISO13JISC6220jp" },
            { 41, "iso-ir-13" },
            { 41, "katakana" },
            { 41, "x0201-7" },
            { 42, "JIS_C6220-1969-ro" },
            { 42, "ISO646-JP" },
            { 42, "csISO14JISC6220ro" },
            { 42, "iso-ir-14" },
            { 42, "jp" },
            { 43, "PT" },
            { 43, "ISO646-PT" },
            { 43, "csISO16Portuguese" },
            { 43, "iso-ir-16" },
            { 44, "greek7-old" },
            { 44, "csISO18Greek7Old" },
            { 44, "iso-ir-18" },
            { 45, "latin-greek" },
            { 45, "csISO19LatinGreek" },
            { 45, "iso-ir-19" },
            { 46, "NF_Z_62-010_(1973)" },
            { 46, "ISO646-FR1" },
            { 46, "csISO25French" },
            { 46, "iso-ir-25" },
            { 47, "Latin-greek-1" },
            { 47, "csISO27LatinGreek1" },
            { 47, "iso-ir-27" },
            { 48, "ISO_5427" },
            { 48, "csISO5427Cyrillic" },
            { 48, "iso-ir-37" },
            { 49, "JIS_C6226-1978" },
            { 49, "csISO42JISC62261978" },
            { 49, "iso-ir-42" },
            { 50, "BS_viewdata" },
            { 50, "csISO47BSViewdata" },
            { 50, "iso-ir-47" },
            { 51, "INIS" },
            { 51, "csISO49INIS" },
            { 51, "iso-ir-49" },
            { 52, "INIS-8" },
            { 52, "csISO50INIS8" },
            { 52, "iso-ir-50" },
            { 53, "INIS-cyrillic" },
            { 53, "csISO51INISCyrillic" },
            { 53, "iso-ir-51" },
            { 54, "ISO_5427:1981" },
            { 54, "ISO5427Cyrillic1981" },
            { 54, "csISO54271981" },
            { 54, "iso-ir-54" },
            { 55, "ISO_5428:1980" },
            { 55, "csISO5428Greek" },
            { 55, "iso-ir-55" },
            { 56, "GB_1988-80" },
            { 56, "ISO646-CN" },
            { 56, "cn" },
            { 56, "csISO57GB1988" },
            { 56, "iso-ir-57" },
            { 57, "GB_2312-80" },
            { 57, "chinese" },
            { 57, "csISO58GB231280" },
            { 57, "iso-ir-58" },
            { 58, "NS_4551-2" },
            { 58, "ISO646-NO2" },
            { 58, "csISO61Norwegian2" },
            { 58, "iso-ir-61" },
            { 58, "no2" },
            { 59, "videotex-suppl" },
            { 59, "csISO70VideotexSupp1" },
            { 59, "iso-ir-70" },
            { 60, "PT2" },
            { 60, "ISO646-PT2" },
            { 60, "csISO84Portuguese2" },
            { 60, "iso-ir-84" },
            { 61, "ES2" },
            { 61, "ISO646-ES2" },
            { 61, "csISO85Spanish2" },
            { 61, "iso-ir-85" },
            { 62, "MSZ_7795.3" },
            { 62, "ISO646-HU" },
            { 62, "csISO86Hungarian" },
            { 62, "hu" },
            { 62, "iso-ir-86" },
            { 63, "JIS_C6226-1983" },
            { 63, "JIS_X0208-1983" },
            { 63, "csISO87JISX0208" },
            { 63, "iso-ir-87" },
            { 63, "x0208" },
            { 64, "greek7" },
            { 64, "csISO88Greek7" },
            { 64, "iso-ir-88" },
            { 65, "ASMO_449" },
            { 65, "ISO_9036" },
            { 65, "arabic7" },
            { 65, "csISO89ASMO449" },
            { 65, "iso-ir-89" },
            { 66, "iso-ir-90" },
            { 66, "csISO90" },
            { 67, "JIS_C6229-1984-a" },
            { 67, "csISO91JISC62291984a" },
            { 67, "iso-ir-91" },
            { 67, "jp-ocr-a" },
            { 68, "JIS_C6229-1984-b" },
            { 68, "ISO646-JP-OCR-B" },
            { 68, "csISO92JISC62991984b" },
            { 68, "iso-ir-92" },
            { 68, "jp-ocr-b" },
            { 69, "JIS_C6229-1984-b-add" },
            { 69, "csISO93JIS62291984badd" },
            { 69, "iso-ir-93" },
            { 69, "jp-ocr-b-add" },
            { 70, "JIS_C6229-1984-hand" },
            { 70, "csISO94JIS62291984hand" },
            { 70, "iso-ir-94" },
            { 70, "jp-ocr-hand" },
            { 71, "JIS_C6229-1984-hand-add" },
            { 71, "csISO95JIS62291984handadd" },
            { 71, "iso-ir-95" },
            { 71, "jp-ocr-hand-add" },
            { 72, "JIS_C6229-1984-kana" },
            { 72, "csISO96JISC62291984kana" },
            { 72, "iso-ir-96" },
            { 73, "ISO_2033-1983" },
            { 73, "csISO2033" },
            { 73, "e13b" },
            { 73, "iso-ir-98" },
            { 74, "ANSI_X3.110-1983" },
            { 74, "CSA_T500-1983" },
            { 74, "NAPLPS" },
            { 74, "csISO99NAPLPS" },
            { 74, "iso-ir-99" },
            { 75, "T.61-7bit" },
            { 75, "csISO102T617bit" },
            { 75, "iso-ir-102" },
            { 76, "T.61-8bit" },
            { 76, "T.61" },
            { 76, "csISO103T618bit" },
            { 76, "iso-ir-103" },
            { 77, "ECMA-cyrillic" },
            { 77, "KOI8-E" },
            { 77, "csISO111ECMACyrillic" },
            { 77, "iso-ir-111" },
            { 78, "CSA_Z243.4-1985-1" },
            { 78, "ISO646-CA" },
            { 78, "ca" },
            { 78, "csISO121Canadian1" },
            { 78, "csa7-1" },
            { 78, "csa71" },
            { 78, "iso-ir-121" },
            { 79, "CSA_Z243.4-1985-2" },
            { 79, "ISO646-CA2" },
            { 79, "csISO122Canadian2" },
            { 79, "csa7-2" },
            { 79, "csa72" },
            { 79, "iso-ir-122" },
            { 80, "CSA_Z243.4-1985-gr" },
            { 80, "csISO123CSAZ24341985gr" },
            { 80, "iso-ir-123" },
            { 81, "ISO-8859-6-E" },
            { 81, "ISO_8859-6-E" },
            { 81, "csISO88596E" },
            { 82, "ISO-8859-6-I" },
            { 82, "ISO_8859-6-I" },
            { 82, "csISO88596I" },
            { 83, "T.101-G2" },
            { 83, "csISO128T101G2" },
            { 83, "iso-ir-128" },
            { 84, "ISO-8859-8-E" },
            { 84, "ISO_8859-8-E" },
            { 84, "csISO88598E" },
            { 85, "ISO-8859-8-I" },
            { 85, "ISO_8859-8-I" },
            { 85, "csISO88598I" },
            { 86, "CSN_369103" },
            { 86, "csISO139CSN369103" },
            { 86, "iso-ir-139" },
            { 87, "JUS_I.B1.002" },
            { 87, "ISO646-YU" },
            { 87, "csISO141JUSIB1002" },
            { 87, "iso-ir-141" },
            { 87, "js" },
            { 87, "yu" },
            { 88, "IEC_P27-1" },
            { 88, "csISO143IECP271" },
            { 88, "iso-ir-143" },
            { 89, "JUS_I.B1.003-serb" },
            { 89, "csISO146Serbian" },
            { 89, "iso-ir-146" },
            { 89, "serbian" },
            { 90, "JUS_I.B1.003-mac" },
            { 90, "csISO147Macedonian" },
            { 90, "iso-ir-147" },
            { 90, "macedonian" },
            { 91, "greek-ccitt" },
            { 91, "csISO150" },
            { 91, "csISO150GreekCCITT" },
            { 91, "iso-ir-150" },
            { 92, "NC_NC00-10:81" },
            { 92, "ISO646-CU" },
            { 92, "csISO151Cuba" },
            { 92, "cuba" },
            { 92, "iso-ir-151" },
            { 93, "ISO_6937-2-25" },
            { 93, "csISO6937Add" },
            { 93, "iso-ir-152" },
            { 94, "GOST_19768-74" },
            { 94, "ST_SEV_358-88" },
            { 94, "csISO153GOST1976874" },
            { 94, "iso-ir-153" },
            { 95, "ISO_8859-supp" },
            { 95, "csISO8859Supp" },
            { 95, "iso-ir-154" },
            { 95, "latin1-2-5" },
            { 96, "ISO_10367-box" },
            { 96, "csISO10367Box" },
            { 96, "iso-ir-155" },
            { 97, "latin-lap" },
            { 97, "csISO158Lap" },
            { 97, "iso-ir-158" },
            { 97, "lap" },
            { 98, "JIS_X0212-1990" },
            { 98, "csISO159JISX02121990" },
            { 98, "iso-ir-159" },
            { 98, "x0212" },
            { 99, "DS_2089" },
            { 99, "DS2089" },
            { 99, "ISO646-DK" },
            { 99, "csISO646Danish" },
            { 99, "dk" },
            { 100, "us-dk" },
            { 100, "csUSDK" },
            { 101, "dk-us" },
            { 101, "csDKUS" },
            { 102, "KSC5636" },
            { 102, "ISO646-KR" },
            { 102, "csKSC5636" },
            { 103, "UNICODE-1-1-UTF-7" },
            { 103, "csUnicode11UTF7" },
            { 104, "ISO-2022-CN" },
            { 104, "csISO2022CN" },
            { 105, "ISO-2022-CN-EXT" },
            { 105, "csISO2022CNEXT" },
            { 106, "UTF-8" },
            { 106, "csUTF8" },
            { 109, "ISO-8859-13" },
            { 109, "csISO885913" },
            { 110, "ISO-8859-14" },
            { 110, "ISO_8859-14" },
            { 110, "ISO_8859-14:1998" },
            { 110, "csISO885914" },
            { 110, "iso-celtic" },
            { 110, "iso-ir-199" },
            { 110, "l8" },
            { 110, "latin8" },
            { 111, "ISO-8859-15" },
            { 111, "ISO_8859-15" },
            { 111, "Latin-9" },
            { 111, "csISO885915" },
            { 112, "ISO-8859-16" },
            { 112, "ISO_8859-16" },
            { 112, "ISO_8859-16:2001" },
            { 112, "csISO885916" },
            { 112, "iso-ir-226" },
            { 112, "l10" },
            { 112, "latin10" },
            { 113, "GBK" },
            { 113, "CP936" },
            { 113, "MS936" },
            { 113, "csGBK" },
            { 113, "windows-936" },
            { 114, "GB18030" },
            { 114, "csGB18030" },
            { 115, "OSD_EBCDIC_DF04_15" },
            { 115, "csOSDEBCDICDF0415" },
            { 116, "OSD_EBCDIC_DF03_IRV" },
            { 116, "csOSDEBCDICDF03IRV" },
            { 117, "OSD_EBCDIC_DF04_1" },
            { 117, "csOSDEBCDICDF041" },
            { 118, "ISO-11548-1" },
            { 118, "ISO_11548-1" },
            { 118, "ISO_TR_11548-1" },
            { 118, "csISO115481" },
            { 119, "KZ-1048" },
            { 119, "RK1048" },
            { 119, "STRK1048-2002" },
            { 119, "csKZ1048" },
            { 1000, "ISO-10646-UCS-2" },
            { 1000, "csUnicode" },
            { 1001, "ISO-10646-UCS-4" },
            { 1001, "csUCS4" },
            { 1002, "ISO-10646-UCS-Basic" },
            { 1002, "csUnicodeASCII" },
            { 1003, "ISO-10646-Unicode-Latin1" },
            { 1003, "ISO-10646" },
            { 1003, "csUnicodeLatin1" },
            { 1004, "ISO-10646-J-1" },
            { 1004, "csUnicodeJapanese" },
            { 1005, "ISO-Unicode-IBM-1261" },
            { 1005, "csUnicodeIBM1261" },
            { 1006, "ISO-Unicode-IBM-1268" },
            { 1006, "csUnicodeIBM1268" },
            { 1007, "ISO-Unicode-IBM-1276" },
            { 1007, "csUnicodeIBM1276" },
            { 1008, "ISO-Unicode-IBM-1264" },
            { 1008, "csUnicodeIBM1264" },
            { 1009, "ISO-Unicode-IBM-1265" },
            { 1009, "csUnicodeIBM1265" },
            { 1010, "UNICODE-1-1" },
            { 1010, "csUnicode11" },
            { 1011, "SCSU" },
            { 1011, "csSCSU" },
            { 1012, "UTF-7" },
            { 1012, "csUTF7" },
            { 1013, "UTF-16BE" },
            { 1013, "csUTF16BE" },
            { 1014, "UTF-16LE" },
            { 1014, "csUTF16LE" },
            { 1015, "UTF-16" },
            { 1015, "csUTF16" },
            { 1016, "CESU-8" },
            { 1016, "csCESU-8" },
            { 1016, "csCESU8" },
            { 1017, "UTF-32" },
            { 1017, "csUTF32" },
            { 1018, "UTF-32BE" },
            { 1018, "csUTF32BE" },
            { 1019, "UTF-32LE" },
            { 1019, "csUTF32LE" },
            { 1020, "BOCU-1" },
            { 1020, "csBOCU-1" },
            { 1020, "csBOCU1" },
            { 2000, "ISO-8859-1-Windows-3.0-Latin-1" },
            { 2000, "csWindows30Latin1" },
            { 2001, "ISO-8859-1-Windows-3.1-Latin-1" },
            { 2001, "csWindows31Latin1" },
            { 2002, "ISO-8859-2-Windows-Latin-2" },
            { 2002, "csWindows31Latin2" },
            { 2003, "ISO-8859-9-Windows-Latin-5" },
            { 2003, "csWindows31Latin5" },
            { 2004, "hp-roman8" },
            { 2004, "csHPRoman8" },
            { 2004, "r8" },
            { 2004, "roman8" },
            { 2005, "Adobe-Standard-Encoding" },
            { 2005, "csAdobeStandardEncoding" },
            { 2006, "Ventura-US" },
            { 2006, "csVenturaUS" },
            { 2007, "Ventura-International" },
            { 2007, "csVenturaInternational" },
            { 2008, "DEC-MCS" },
            { 2008, "csDECMCS" },
            { 2008, "dec" },
            { 2009, "IBM850" },
            { 2009, "850" },
            { 2009, "cp850" },
            { 2009, "csPC850Multilingual" },
            { 2012, "PC8-Danish-Norwegian" },
            { 2012, "csPC8DanishNorwegian" },
            { 2013, "IBM862" },
            { 2013, "862" },
            { 2013, "cp862" },
            { 2013, "csPC862LatinHebrew" },
            { 2014, "PC8-Turkish" },
            { 2014, "csPC8Turkish" },
            { 2015, "IBM-Symbols" },
            { 2015, "csIBMSymbols" },
            { 2016, "IBM-Thai" },
            { 2016, "csIBMThai" },
            { 2017, "HP-Legal" },
            { 2017, "csHPLegal" },
            { 2018, "HP-Pi-font" },
            { 2018, "csHPPiFont" },
            { 2019, "HP-Math8" },
            { 2019, "csHPMath8" },
            { 2020, "Adobe-Symbol-Encoding" },
            { 2020, "csHPPSMath" },
            { 2021, "HP-DeskTop" },
            { 2021, "csHPDesktop" },
            { 2022, "Ventura-Math" },
            { 2022, "csVenturaMath" },
            { 2023, "Microsoft-Publishing" },
            { 2023, "csMicrosoftPublishing" },
            { 2024, "Windows-31J" },
            { 2024, "csWindows31J" },
            { 2025, "GB2312" },
            { 2025, "csGB2312" },
            { 2026, "Big5" },
            { 2026, "csBig5" },
            { 2027, "macintosh" },
            { 2027, "csMacintosh" },
            { 2027, "mac" },
            { 2028, "IBM037" },
            { 2028, "cp037" },
            { 2028, "csIBM037" },
            { 2028, "ebcdic-cp-ca" },
            { 2028, "ebcdic-cp-nl" },
            { 2028, "ebcdic-cp-us" },
            { 2028, "ebcdic-cp-wt" },
            { 2029, "IBM038" },
            { 2029, "EBCDIC-INT" },
            { 2029, "cp038" },
            { 2029, "csIBM038" },
            { 2030, "IBM273" },
            { 2030, "CP273" },
            { 2030, "csIBM273" },
            { 2031, "IBM274" },
            { 2031, "CP274" },
            { 2031, "EBCDIC-BE" },
            { 2031, "csIBM274" },
            { 2032, "IBM275" },
            { 2032, "EBCDIC-BR" },
            { 2032, "cp275" },
            { 2032, "csIBM275" },
            { 2033, "IBM277" },
            { 2033, "EBCDIC-CP-DK" },
            { 2033, "EBCDIC-CP-NO" },
            { 2033, "csIBM277" },
            { 2034, "IBM278" },
            { 2034, "CP278" },
            { 2034, "csIBM278" },
            { 2034, "ebcdic-cp-fi" },
            { 2034, "ebcdic-cp-se" },
            { 2035, "IBM280" },
            { 2035, "CP280" },
            { 2035, "csIBM280" },
            { 2035, "ebcdic-cp-it" },
            { 2036, "IBM281" },
            { 2036, "EBCDIC-JP-E" },
            { 2036, "cp281" },
            { 2036, "csIBM281" },
            { 2037, "IBM284" },
            { 2037, "CP284" },
            { 2037, "csIBM284" },
            { 2037, "ebcdic-cp-es" },
            { 2038, "IBM285" },
            { 2038, "CP285" },
            { 2038, "csIBM285" },
            { 2038, "ebcdic-cp-gb" },
            { 2039, "IBM290" },
            { 2039, "EBCDIC-JP-kana" },
            { 2039, "cp290" },
            { 2039, "csIBM290" },
            { 2040, "IBM297" },
            { 2040, "cp297" },
            { 2040, "csIBM297" },
            { 2040, "ebcdic-cp-fr" },
            { 2041, "IBM420" },
            { 2041, "cp420" },
            { 2041, "csIBM420" },
            { 2041, "ebcdic-cp-ar1" },
            { 2042, "IBM423" },
            { 2042, "cp423" },
            { 2042, "csIBM423" },
            { 2042, "ebcdic-cp-gr" },
            { 2043, "IBM424" },
            { 2043, "cp424" },
            { 2043, "csIBM424" },
            { 2043, "ebcdic-cp-he" },
            { 2011, "IBM437" },
            { 2011, "437" },
            { 2011, "cp437" },
            { 2011, "csPC8CodePage437" },
            { 2044, "IBM500" },
            { 2044, "CP500" },
            { 2044, "csIBM500" },
            { 2044, "ebcdic-cp-be" },
            { 2044, "ebcdic-cp-ch" },
            { 2045, "IBM851" },
            { 2045, "851" },
            { 2045, "cp851" },
            { 2045, "csIBM851" },
            { 2010, "IBM852" },
            { 2010, "852" },
            { 2010, "cp852" },
            { 2010, "csPCp852" },
            { 2046, "IBM855" },
            { 2046, "855" },
            { 2046, "cp855" },
            { 2046, "csIBM855" },
            { 2047, "IBM857" },
            { 2047, "857" },
            { 2047, "cp857" },
            { 2047, "csIBM857" },
            { 2048, "IBM860" },
            { 2048, "860" },
            { 2048, "cp860" },
            { 2048, "csIBM860" },
            { 2049, "IBM861" },
            { 2049, "861" },
            { 2049, "cp-is" },
            { 2049, "cp861" },
            { 2049, "csIBM861" },
            { 2050, "IBM863" },
            { 2050, "863" },
            { 2050, "cp863" },
            { 2050, "csIBM863" },
            { 2051, "IBM864" },
            { 2051, "cp864" },
            { 2051, "csIBM864" },
            { 2052, "IBM865" },
            { 2052, "865" },
            { 2052, "cp865" },
            { 2052, "csIBM865" },
            { 2053, "IBM868" },
            { 2053, "CP868" },
            { 2053, "cp-ar" },
            { 2053, "csIBM868" },
            { 2054, "IBM869" },
            { 2054, "869" },
            { 2054, "cp-gr" },
            { 2054, "cp869" },
            { 2054, "csIBM869" },
            { 2055, "IBM870" },
            { 2055, "CP870" },
            { 2055, "csIBM870" },
            { 2055, "ebcdic-cp-roece" },
            { 2055, "ebcdic-cp-yu" },
            { 2056, "IBM871" },
            { 2056, "CP871" },
            { 2056, "csIBM871" },
            { 2056, "ebcdic-cp-is" },
            { 2057, "IBM880" },
            { 2057, "EBCDIC-Cyrillic" },
            { 2057, "cp880" },
            { 2057, "csIBM880" },
            { 2058, "IBM891" },
            { 2058, "cp891" },
            { 2058, "csIBM891" },
            { 2059, "IBM903" },
            { 2059, "cp903" },
            { 2059, "csIBM903" },
            { 2060, "IBM904" },
            { 2060, "904" },
            { 2060, "cp904" },
            { 2060, "csIBBM904" },
            { 2061, "IBM905" },
            { 2061, "CP905" },
            { 2061, "csIBM905" },
            { 2061, "ebcdic-cp-tr" },
            { 2062, "IBM918" },
            { 2062, "CP918" },
            { 2062, "csIBM918" },
            { 2062, "ebcdic-cp-ar2" },
            { 2063, "IBM1026" },
            { 2063, "CP1026" },
            { 2063, "csIBM1026" },
            { 2064, "EBCDIC-AT-DE" },
            { 2064, "csIBMEBCDICATDE" },
            { 2065, "EBCDIC-AT-DE-A" },
            { 2065, "csEBCDICATDEA" },
            { 2066, "EBCDIC-CA-FR" },
            { 2066, "csEBCDICCAFR" },
            { 2067, "EBCDIC-DK-NO" },
            { 2067, "csEBCDICDKNO" },
            { 2068, "EBCDIC-DK-NO-A" },
            { 2068, "csEBCDICDKNOA" },
            { 2069, "EBCDIC-FI-SE" },
            { 2069, "csEBCDICFISE" },
            { 2070, "EBCDIC-FI-SE-A" },
            { 2070, "csEBCDICFISEA" },
            { 2071, "EBCDIC-FR" },
            { 2071, "csEBCDICFR" },
            { 2072, "EBCDIC-IT" },
            { 2072, "csEBCDICIT" },
            { 2073, "EBCDIC-PT" },
            { 2073, "csEBCDICPT" },
            { 2074, "EBCDIC-ES" },
            { 2074, "csEBCDICES" },
            { 2075, "EBCDIC-ES-A" },
            { 2075, "csEBCDICESA" },
            { 2076, "EBCDIC-ES-S" },
            { 2076, "csEBCDICESS" },
            { 2077, "EBCDIC-UK" },
            { 2077, "csEBCDICUK" },
            { 2078, "EBCDIC-US" },
            { 2078, "csEBCDICUS" },
            { 2079, "UNKNOWN-8BIT" },
            { 2079, "csUnknown8BiT" },
            { 2080, "MNEMONIC" },
            { 2080, "csMnemonic" },
            { 2081, "MNEM" },
            { 2081, "csMnem" },
            { 2082, "VISCII" },
            { 2082, "csVISCII" },
            { 2083, "VIQR" },
            { 2083, "csVIQR" },
            { 2084, "KOI8-R" },
            { 2084, "csKOI8R" },
            { 2085, "HZ-GB-2312" },
            { 2086, "IBM866" },
            { 2086, "866" },
            { 2086, "cp866" },
            { 2086, "csIBM866" },
            { 2087, "IBM775" },
            { 2087, "cp775" },
            { 2087, "csPC775Baltic" },
            { 2088, "KOI8-U" },
            { 2088, "csKOI8U" },
            { 2089, "IBM00858" },
            { 2089, "CCSID00858" },
            { 2089, "CP00858" },
            { 2089, "PC-Multilingual-850+euro" },
            { 2089, "csIBM00858" },
            { 2090, "IBM00924" },
            { 2090, "CCSID00924" },
            { 2090, "CP00924" },
            { 2090, "csIBM00924" },
            { 2090, "ebcdic-Latin9--euro" },
            { 2091, "IBM01140" },
            { 2091, "CCSID01140" },
            { 2091, "CP01140" },
            { 2091, "csIBM01140" },
            { 2091, "ebcdic-us-37+euro" },
            { 2092, "IBM01141" },
            { 2092, "CCSID01141" },
            { 2092, "CP01141" },
            { 2092, "csIBM01141" },
            { 2092, "ebcdic-de-273+euro" },
            { 2093, "IBM01142" },
            { 2093, "CCSID01142" },
            { 2093, "CP01142" },
            { 2093, "csIBM01142" },
            { 2093, "ebcdic-dk-277+euro" },
            { 2093, "ebcdic-no-277+euro" },
            { 2094, "IBM01143" },
            { 2094, "CCSID01143" },
            { 2094, "CP01143" },
            { 2094, "csIBM01143" },
            { 2094, "ebcdic-fi-278+euro" },
            { 2094, "ebcdic-se-278+euro" },
            { 2095, "IBM01144" },
            { 2095, "CCSID01144" },
            { 2095, "CP01144" },
            { 2095, "csIBM01144" },
            { 2095, "ebcdic-it-280+euro" },
            { 2096, "IBM01145" },
            { 2096, "CCSID01145" },
            { 2096, "CP01145" },
            { 2096, "csIBM01145" },
            { 2096, "ebcdic-es-284+euro" },
            { 2097, "IBM01146" },
            { 2097, "CCSID01146" },
            { 2097, "CP01146" },
            { 2097, "csIBM01146" },
            { 2097, "ebcdic-gb-285+euro" },
            { 2098, "IBM01147" },
            { 2098, "CCSID01147" },
            { 2098, "CP01147" },
            { 2098, "csIBM01147" },
            { 2098, "ebcdic-fr-297+euro" },
            { 2099, "IBM01148" },
            { 2099, "CCSID01148" },
            { 2099, "CP01148" },
            { 2099, "csIBM01148" },
            { 2099, "ebcdic-international-500+euro" },
            { 2100, "IBM01149" },
            { 2100, "CCSID01149" },
            { 2100, "CP01149" },
            { 2100, "csIBM01149" },
            { 2100, "ebcdic-is-871+euro" },
            { 2101, "Big5-HKSCS" },
            { 2101, "csBig5HKSCS" },
            { 2102, "IBM1047" },
            { 2102, "IBM-1047" },
            { 2102, "csIBM1047" },
            { 2103, "PTCP154" },
            { 2103, "CP154" },
            { 2103, "Cyrillic-Asian" },
            { 2103, "PT154" },
            { 2103, "csPTCP154" },
            { 2104, "Amiga-1251" },
            { 2104, "Ami-1251" },
            { 2104, "Ami1251" },
            { 2104, "Amiga1251" },
            { 2104, "csAmiga1251" },
            { 2105, "KOI7-switched" },
            { 2105, "csKOI7switched" },
            { 2106, "BRF" },
            { 2106, "csBRF" },
            { 2107, "TSCII" },
            { 2107, "csTSCII" },
            { 2108, "CP51932" },
            { 2108, "csCP51932" },
            { 2109, "windows-874" },
            { 2109, "cswindows874" },
            { 2250, "windows-1250" },
            { 2250, "cswindows1250" },
            { 2251, "windows-1251" },
            { 2251, "cswindows1251" },
            { 2252, "windows-1252" },
            { 2252, "cswindows1252" },
            { 2253, "windows-1253" },
            { 2253, "cswindows1253" },
            { 2254, "windows-1254" },
            { 2254, "cswindows1254" },
            { 2255, "windows-1255" },
            { 2255, "cswindows1255" },
            { 2256, "windows-1256" },
            { 2256, "cswindows1256" },
            { 2257, "windows-1257" },
            { 2257, "cswindows1257" },
            { 2258, "windows-1258" },
            { 2258, "cswindows1258" },
            { 2259, "TIS-620" },
            { 2259, "ISO-8859-11" },
            { 2259, "csTIS620" },
            { 2260, "CP50220" },
            { 2260, "csCP50220" },
            { 0, nullptr }
        };
    template <id id_>
    constexpr bool encoding_is(const char* name) {

        if constexpr(id_ == details::id::ASCII) {
            return do_compare({"US-ASCII","ANSI_X3.4-1968","ANSI_X3.4-1986","IBM367","ISO646-US","ISO_646.irv:1991","cp367","csASCII","iso-ir-6","us"}, name);
        }

        if constexpr(id_ == details::id::ISOLatin1) {
            return do_compare({"ISO-8859-1","ISO_8859-1:1987","CP819","IBM819","ISO_8859-1","csISOLatin1","iso-ir-100","l1","latin1"}, name);
        }

        if constexpr(id_ == details::id::ISOLatin2) {
            return do_compare({"ISO-8859-2","ISO_8859-2:1987","ISO_8859-2","csISOLatin2","iso-ir-101","l2","latin2"}, name);
        }

        if constexpr(id_ == details::id::ISOLatin3) {
            return do_compare({"ISO-8859-3","ISO_8859-3:1988","ISO_8859-3","csISOLatin3","iso-ir-109","l3","latin3"}, name);
        }

        if constexpr(id_ == details::id::ISOLatin4) {
            return do_compare({"ISO-8859-4","ISO_8859-4:1988","ISO_8859-4","csISOLatin4","iso-ir-110","l4","latin4"}, name);
        }

        if constexpr(id_ == details::id::ISOLatinCyrillic) {
            return do_compare({"ISO-8859-5","ISO_8859-5:1988","ISO_8859-5","csISOLatinCyrillic","cyrillic","iso-ir-144"}, name);
        }

        if constexpr(id_ == details::id::ISOLatinArabic) {
            return do_compare({"ISO-8859-6","ISO_8859-6:1987","ASMO-708","ECMA-114","ISO_8859-6","arabic","csISOLatinArabic","iso-ir-127"}, name);
        }

        if constexpr(id_ == details::id::ISOLatinGreek) {
            return do_compare({"ISO-8859-7","ISO_8859-7:1987","ECMA-118","ELOT_928","ISO_8859-7","csISOLatinGreek","greek","greek8","iso-ir-126"}, name);
        }

        if constexpr(id_ == details::id::ISOLatinHebrew) {
            return do_compare({"ISO-8859-8","ISO_8859-8:1988","ISO_8859-8","csISOLatinHebrew","hebrew","iso-ir-138"}, name);
        }

        if constexpr(id_ == details::id::ISOLatin5) {
            return do_compare({"ISO-8859-9","ISO_8859-9:1989","ISO_8859-9","csISOLatin5","iso-ir-148","l5","latin5"}, name);
        }

        if constexpr(id_ == details::id::ISOLatin6) {
            return do_compare({"ISO-8859-10","ISO_8859-10:1992","csISOLatin6","iso-ir-157","l6","latin6"}, name);
        }

        if constexpr(id_ == details::id::ISOTextComm) {
            return do_compare({"ISO_6937-2-add","csISOTextComm","iso-ir-142"}, name);
        }

        if constexpr(id_ == details::id::HalfWidthKatakana) {
            return do_compare({"JIS_X0201","X0201","csHalfWidthKatakana"}, name);
        }

        if constexpr(id_ == details::id::JISEncoding) {
            return do_compare({"JIS_Encoding","csJISEncoding"}, name);
        }

        if constexpr(id_ == details::id::ShiftJIS) {
            return do_compare({"Shift_JIS","MS_Kanji","csShiftJIS"}, name);
        }

        if constexpr(id_ == details::id::EUCPkdFmtJapanese) {
            return do_compare({"EUC-JP","Extended_UNIX_Code_Packed_Format_for_Japanese","csEUCPkdFmtJapanese"}, name);
        }

        if constexpr(id_ == details::id::EUCFixWidJapanese) {
            return do_compare({"Extended_UNIX_Code_Fixed_Width_for_Japanese","csEUCFixWidJapanese"}, name);
        }

        if constexpr(id_ == details::id::ISO4UnitedKingdom) {
            return do_compare({"BS_4730","ISO646-GB","csISO4UnitedKingdom","gb","iso-ir-4","uk"}, name);
        }

        if constexpr(id_ == details::id::ISO11SwedishForNames) {
            return do_compare({"SEN_850200_C","ISO646-SE2","csISO11SwedishForNames","iso-ir-11","se2"}, name);
        }

        if constexpr(id_ == details::id::ISO15Italian) {
            return do_compare({"IT","ISO646-IT","csISO15Italian","iso-ir-15"}, name);
        }

        if constexpr(id_ == details::id::ISO17Spanish) {
            return do_compare({"ES","ISO646-ES","csISO17Spanish","iso-ir-17"}, name);
        }

        if constexpr(id_ == details::id::ISO21German) {
            return do_compare({"DIN_66003","ISO646-DE","csISO21German","de","iso-ir-21"}, name);
        }

        if constexpr(id_ == details::id::ISO60DanishNorwegian) {
            return do_compare({"NS_4551-1","ISO646-NO","csISO60DanishNorwegian","csISO60Norwegian1","iso-ir-60","no"}, name);
        }

        if constexpr(id_ == details::id::ISO69French) {
            return do_compare({"NF_Z_62-010","ISO646-FR","csISO69French","fr","iso-ir-69"}, name);
        }

        if constexpr(id_ == details::id::ISO10646UTF1) {
            return do_compare({"ISO-10646-UTF-1","csISO10646UTF1"}, name);
        }

        if constexpr(id_ == details::id::ISO646basic1983) {
            return do_compare({"ISO_646.basic:1983","csISO646basic1983","ref"}, name);
        }

        if constexpr(id_ == details::id::INVARIANT) {
            return do_compare({"INVARIANT","csINVARIANT"}, name);
        }

        if constexpr(id_ == details::id::ISO2IntlRefVersion) {
            return do_compare({"ISO_646.irv:1983","csISO2IntlRefVersion","irv","iso-ir-2"}, name);
        }

        if constexpr(id_ == details::id::NATSSEFI) {
            return do_compare({"NATS-SEFI","csNATSSEFI","iso-ir-8-1"}, name);
        }

        if constexpr(id_ == details::id::NATSSEFIADD) {
            return do_compare({"NATS-SEFI-ADD","csNATSSEFIADD","iso-ir-8-2"}, name);
        }

        if constexpr(id_ == details::id::NATSDANO) {
            return do_compare({"NATS-DANO","csNATSDANO","iso-ir-9-1"}, name);
        }

        if constexpr(id_ == details::id::NATSDANOADD) {
            return do_compare({"NATS-DANO-ADD","csNATSDANOADD","iso-ir-9-2"}, name);
        }

        if constexpr(id_ == details::id::ISO10Swedish) {
            return do_compare({"SEN_850200_B","FI","ISO646-FI","ISO646-SE","csISO10Swedish","iso-ir-10","se"}, name);
        }

        if constexpr(id_ == details::id::KSC56011987) {
            return do_compare({"KS_C_5601-1987","KSC_5601","KS_C_5601-1989","csKSC56011987","iso-ir-149","korean"}, name);
        }

        if constexpr(id_ == details::id::ISO2022KR) {
            return do_compare({"ISO-2022-KR","csISO2022KR"}, name);
        }

        if constexpr(id_ == details::id::EUCKR) {
            return do_compare({"EUC-KR","csEUCKR"}, name);
        }

        if constexpr(id_ == details::id::ISO2022JP) {
            return do_compare({"ISO-2022-JP","csISO2022JP"}, name);
        }

        if constexpr(id_ == details::id::ISO2022JP2) {
            return do_compare({"ISO-2022-JP-2","csISO2022JP2"}, name);
        }

        if constexpr(id_ == details::id::ISO13JISC6220jp) {
            return do_compare({"JIS_C6220-1969-jp","JIS_C6220-1969","csISO13JISC6220jp","iso-ir-13","katakana","x0201-7"}, name);
        }

        if constexpr(id_ == details::id::ISO14JISC6220ro) {
            return do_compare({"JIS_C6220-1969-ro","ISO646-JP","csISO14JISC6220ro","iso-ir-14","jp"}, name);
        }

        if constexpr(id_ == details::id::ISO16Portuguese) {
            return do_compare({"PT","ISO646-PT","csISO16Portuguese","iso-ir-16"}, name);
        }

        if constexpr(id_ == details::id::ISO18Greek7Old) {
            return do_compare({"greek7-old","csISO18Greek7Old","iso-ir-18"}, name);
        }

        if constexpr(id_ == details::id::ISO19LatinGreek) {
            return do_compare({"latin-greek","csISO19LatinGreek","iso-ir-19"}, name);
        }

        if constexpr(id_ == details::id::ISO25French) {
            return do_compare({"NF_Z_62-010_(1973)","ISO646-FR1","csISO25French","iso-ir-25"}, name);
        }

        if constexpr(id_ == details::id::ISO27LatinGreek1) {
            return do_compare({"Latin-greek-1","csISO27LatinGreek1","iso-ir-27"}, name);
        }

        if constexpr(id_ == details::id::ISO5427Cyrillic) {
            return do_compare({"ISO_5427","csISO5427Cyrillic","iso-ir-37"}, name);
        }

        if constexpr(id_ == details::id::ISO42JISC62261978) {
            return do_compare({"JIS_C6226-1978","csISO42JISC62261978","iso-ir-42"}, name);
        }

        if constexpr(id_ == details::id::ISO47BSViewdata) {
            return do_compare({"BS_viewdata","csISO47BSViewdata","iso-ir-47"}, name);
        }

        if constexpr(id_ == details::id::ISO49INIS) {
            return do_compare({"INIS","csISO49INIS","iso-ir-49"}, name);
        }

        if constexpr(id_ == details::id::ISO50INIS8) {
            return do_compare({"INIS-8","csISO50INIS8","iso-ir-50"}, name);
        }

        if constexpr(id_ == details::id::ISO51INISCyrillic) {
            return do_compare({"INIS-cyrillic","csISO51INISCyrillic","iso-ir-51"}, name);
        }

        if constexpr(id_ == details::id::ISO54271981) {
            return do_compare({"ISO_5427:1981","ISO5427Cyrillic1981","csISO54271981","iso-ir-54"}, name);
        }

        if constexpr(id_ == details::id::ISO5428Greek) {
            return do_compare({"ISO_5428:1980","csISO5428Greek","iso-ir-55"}, name);
        }

        if constexpr(id_ == details::id::ISO57GB1988) {
            return do_compare({"GB_1988-80","ISO646-CN","cn","csISO57GB1988","iso-ir-57"}, name);
        }

        if constexpr(id_ == details::id::ISO58GB231280) {
            return do_compare({"GB_2312-80","chinese","csISO58GB231280","iso-ir-58"}, name);
        }

        if constexpr(id_ == details::id::ISO61Norwegian2) {
            return do_compare({"NS_4551-2","ISO646-NO2","csISO61Norwegian2","iso-ir-61","no2"}, name);
        }

        if constexpr(id_ == details::id::ISO70VideotexSupp1) {
            return do_compare({"videotex-suppl","csISO70VideotexSupp1","iso-ir-70"}, name);
        }

        if constexpr(id_ == details::id::ISO84Portuguese2) {
            return do_compare({"PT2","ISO646-PT2","csISO84Portuguese2","iso-ir-84"}, name);
        }

        if constexpr(id_ == details::id::ISO85Spanish2) {
            return do_compare({"ES2","ISO646-ES2","csISO85Spanish2","iso-ir-85"}, name);
        }

        if constexpr(id_ == details::id::ISO86Hungarian) {
            return do_compare({"MSZ_7795.3","ISO646-HU","csISO86Hungarian","hu","iso-ir-86"}, name);
        }

        if constexpr(id_ == details::id::ISO87JISX0208) {
            return do_compare({"JIS_C6226-1983","JIS_X0208-1983","csISO87JISX0208","iso-ir-87","x0208"}, name);
        }

        if constexpr(id_ == details::id::ISO88Greek7) {
            return do_compare({"greek7","csISO88Greek7","iso-ir-88"}, name);
        }

        if constexpr(id_ == details::id::ISO89ASMO449) {
            return do_compare({"ASMO_449","ISO_9036","arabic7","csISO89ASMO449","iso-ir-89"}, name);
        }

        if constexpr(id_ == details::id::ISO90) {
            return do_compare({"iso-ir-90","csISO90"}, name);
        }

        if constexpr(id_ == details::id::ISO91JISC62291984a) {
            return do_compare({"JIS_C6229-1984-a","csISO91JISC62291984a","iso-ir-91","jp-ocr-a"}, name);
        }

        if constexpr(id_ == details::id::ISO92JISC62991984b) {
            return do_compare({"JIS_C6229-1984-b","ISO646-JP-OCR-B","csISO92JISC62991984b","iso-ir-92","jp-ocr-b"}, name);
        }

        if constexpr(id_ == details::id::ISO93JIS62291984badd) {
            return do_compare({"JIS_C6229-1984-b-add","csISO93JIS62291984badd","iso-ir-93","jp-ocr-b-add"}, name);
        }

        if constexpr(id_ == details::id::ISO94JIS62291984hand) {
            return do_compare({"JIS_C6229-1984-hand","csISO94JIS62291984hand","iso-ir-94","jp-ocr-hand"}, name);
        }

        if constexpr(id_ == details::id::ISO95JIS62291984handadd) {
            return do_compare({"JIS_C6229-1984-hand-add","csISO95JIS62291984handadd","iso-ir-95","jp-ocr-hand-add"}, name);
        }

        if constexpr(id_ == details::id::ISO96JISC62291984kana) {
            return do_compare({"JIS_C6229-1984-kana","csISO96JISC62291984kana","iso-ir-96"}, name);
        }

        if constexpr(id_ == details::id::ISO2033) {
            return do_compare({"ISO_2033-1983","csISO2033","e13b","iso-ir-98"}, name);
        }

        if constexpr(id_ == details::id::ISO99NAPLPS) {
            return do_compare({"ANSI_X3.110-1983","CSA_T500-1983","NAPLPS","csISO99NAPLPS","iso-ir-99"}, name);
        }

        if constexpr(id_ == details::id::ISO102T617bit) {
            return do_compare({"T.61-7bit","csISO102T617bit","iso-ir-102"}, name);
        }

        if constexpr(id_ == details::id::ISO103T618bit) {
            return do_compare({"T.61-8bit","T.61","csISO103T618bit","iso-ir-103"}, name);
        }

        if constexpr(id_ == details::id::ISO111ECMACyrillic) {
            return do_compare({"ECMA-cyrillic","KOI8-E","csISO111ECMACyrillic","iso-ir-111"}, name);
        }

        if constexpr(id_ == details::id::ISO121Canadian1) {
            return do_compare({"CSA_Z243.4-1985-1","ISO646-CA","ca","csISO121Canadian1","csa7-1","csa71","iso-ir-121"}, name);
        }

        if constexpr(id_ == details::id::ISO122Canadian2) {
            return do_compare({"CSA_Z243.4-1985-2","ISO646-CA2","csISO122Canadian2","csa7-2","csa72","iso-ir-122"}, name);
        }

        if constexpr(id_ == details::id::ISO123CSAZ24341985gr) {
            return do_compare({"CSA_Z243.4-1985-gr","csISO123CSAZ24341985gr","iso-ir-123"}, name);
        }

        if constexpr(id_ == details::id::ISO88596E) {
            return do_compare({"ISO-8859-6-E","ISO_8859-6-E","csISO88596E"}, name);
        }

        if constexpr(id_ == details::id::ISO88596I) {
            return do_compare({"ISO-8859-6-I","ISO_8859-6-I","csISO88596I"}, name);
        }

        if constexpr(id_ == details::id::ISO128T101G2) {
            return do_compare({"T.101-G2","csISO128T101G2","iso-ir-128"}, name);
        }

        if constexpr(id_ == details::id::ISO88598E) {
            return do_compare({"ISO-8859-8-E","ISO_8859-8-E","csISO88598E"}, name);
        }

        if constexpr(id_ == details::id::ISO88598I) {
            return do_compare({"ISO-8859-8-I","ISO_8859-8-I","csISO88598I"}, name);
        }

        if constexpr(id_ == details::id::ISO139CSN369103) {
            return do_compare({"CSN_369103","csISO139CSN369103","iso-ir-139"}, name);
        }

        if constexpr(id_ == details::id::ISO141JUSIB1002) {
            return do_compare({"JUS_I.B1.002","ISO646-YU","csISO141JUSIB1002","iso-ir-141","js","yu"}, name);
        }

        if constexpr(id_ == details::id::ISO143IECP271) {
            return do_compare({"IEC_P27-1","csISO143IECP271","iso-ir-143"}, name);
        }

        if constexpr(id_ == details::id::ISO146Serbian) {
            return do_compare({"JUS_I.B1.003-serb","csISO146Serbian","iso-ir-146","serbian"}, name);
        }

        if constexpr(id_ == details::id::ISO147Macedonian) {
            return do_compare({"JUS_I.B1.003-mac","csISO147Macedonian","iso-ir-147","macedonian"}, name);
        }

        if constexpr(id_ == details::id::ISO150) {
            return do_compare({"greek-ccitt","csISO150","csISO150GreekCCITT","iso-ir-150"}, name);
        }

        if constexpr(id_ == details::id::ISO151Cuba) {
            return do_compare({"NC_NC00-10:81","ISO646-CU","csISO151Cuba","cuba","iso-ir-151"}, name);
        }

        if constexpr(id_ == details::id::ISO6937Add) {
            return do_compare({"ISO_6937-2-25","csISO6937Add","iso-ir-152"}, name);
        }

        if constexpr(id_ == details::id::ISO153GOST1976874) {
            return do_compare({"GOST_19768-74","ST_SEV_358-88","csISO153GOST1976874","iso-ir-153"}, name);
        }

        if constexpr(id_ == details::id::ISO8859Supp) {
            return do_compare({"ISO_8859-supp","csISO8859Supp","iso-ir-154","latin1-2-5"}, name);
        }

        if constexpr(id_ == details::id::ISO10367Box) {
            return do_compare({"ISO_10367-box","csISO10367Box","iso-ir-155"}, name);
        }

        if constexpr(id_ == details::id::ISO158Lap) {
            return do_compare({"latin-lap","csISO158Lap","iso-ir-158","lap"}, name);
        }

        if constexpr(id_ == details::id::ISO159JISX02121990) {
            return do_compare({"JIS_X0212-1990","csISO159JISX02121990","iso-ir-159","x0212"}, name);
        }

        if constexpr(id_ == details::id::ISO646Danish) {
            return do_compare({"DS_2089","DS2089","ISO646-DK","csISO646Danish","dk"}, name);
        }

        if constexpr(id_ == details::id::USDK) {
            return do_compare({"us-dk","csUSDK"}, name);
        }

        if constexpr(id_ == details::id::DKUS) {
            return do_compare({"dk-us","csDKUS"}, name);
        }

        if constexpr(id_ == details::id::KSC5636) {
            return do_compare({"KSC5636","ISO646-KR","csKSC5636"}, name);
        }

        if constexpr(id_ == details::id::Unicode11UTF7) {
            return do_compare({"UNICODE-1-1-UTF-7","csUnicode11UTF7"}, name);
        }

        if constexpr(id_ == details::id::ISO2022CN) {
            return do_compare({"ISO-2022-CN","csISO2022CN"}, name);
        }

        if constexpr(id_ == details::id::ISO2022CNEXT) {
            return do_compare({"ISO-2022-CN-EXT","csISO2022CNEXT"}, name);
        }

        if constexpr(id_ == details::id::UTF8) {
            return do_compare({"UTF-8","csUTF8"}, name);
        }

        if constexpr(id_ == details::id::ISO885913) {
            return do_compare({"ISO-8859-13","csISO885913"}, name);
        }

        if constexpr(id_ == details::id::ISO885914) {
            return do_compare({"ISO-8859-14","ISO_8859-14","ISO_8859-14:1998","csISO885914","iso-celtic","iso-ir-199","l8","latin8"}, name);
        }

        if constexpr(id_ == details::id::ISO885915) {
            return do_compare({"ISO-8859-15","ISO_8859-15","Latin-9","csISO885915"}, name);
        }

        if constexpr(id_ == details::id::ISO885916) {
            return do_compare({"ISO-8859-16","ISO_8859-16","ISO_8859-16:2001","csISO885916","iso-ir-226","l10","latin10"}, name);
        }

        if constexpr(id_ == details::id::GBK) {
            return do_compare({"GBK","CP936","MS936","csGBK","windows-936"}, name);
        }

        if constexpr(id_ == details::id::GB18030) {
            return do_compare({"GB18030","csGB18030"}, name);
        }

        if constexpr(id_ == details::id::OSDEBCDICDF0415) {
            return do_compare({"OSD_EBCDIC_DF04_15","csOSDEBCDICDF0415"}, name);
        }

        if constexpr(id_ == details::id::OSDEBCDICDF03IRV) {
            return do_compare({"OSD_EBCDIC_DF03_IRV","csOSDEBCDICDF03IRV"}, name);
        }

        if constexpr(id_ == details::id::OSDEBCDICDF041) {
            return do_compare({"OSD_EBCDIC_DF04_1","csOSDEBCDICDF041"}, name);
        }

        if constexpr(id_ == details::id::ISO115481) {
            return do_compare({"ISO-11548-1","ISO_11548-1","ISO_TR_11548-1","csISO115481"}, name);
        }

        if constexpr(id_ == details::id::KZ1048) {
            return do_compare({"KZ-1048","RK1048","STRK1048-2002","csKZ1048"}, name);
        }

        if constexpr(id_ == details::id::Unicode) {
            return do_compare({"ISO-10646-UCS-2","csUnicode"}, name);
        }

        if constexpr(id_ == details::id::UCS4) {
            return do_compare({"ISO-10646-UCS-4","csUCS4"}, name);
        }

        if constexpr(id_ == details::id::UnicodeASCII) {
            return do_compare({"ISO-10646-UCS-Basic","csUnicodeASCII"}, name);
        }

        if constexpr(id_ == details::id::UnicodeLatin1) {
            return do_compare({"ISO-10646-Unicode-Latin1","ISO-10646","csUnicodeLatin1"}, name);
        }

        if constexpr(id_ == details::id::UnicodeJapanese) {
            return do_compare({"ISO-10646-J-1","csUnicodeJapanese"}, name);
        }

        if constexpr(id_ == details::id::UnicodeIBM1261) {
            return do_compare({"ISO-Unicode-IBM-1261","csUnicodeIBM1261"}, name);
        }

        if constexpr(id_ == details::id::UnicodeIBM1268) {
            return do_compare({"ISO-Unicode-IBM-1268","csUnicodeIBM1268"}, name);
        }

        if constexpr(id_ == details::id::UnicodeIBM1276) {
            return do_compare({"ISO-Unicode-IBM-1276","csUnicodeIBM1276"}, name);
        }

        if constexpr(id_ == details::id::UnicodeIBM1264) {
            return do_compare({"ISO-Unicode-IBM-1264","csUnicodeIBM1264"}, name);
        }

        if constexpr(id_ == details::id::UnicodeIBM1265) {
            return do_compare({"ISO-Unicode-IBM-1265","csUnicodeIBM1265"}, name);
        }

        if constexpr(id_ == details::id::Unicode11) {
            return do_compare({"UNICODE-1-1","csUnicode11"}, name);
        }

        if constexpr(id_ == details::id::SCSU) {
            return do_compare({"SCSU","csSCSU"}, name);
        }

        if constexpr(id_ == details::id::UTF7) {
            return do_compare({"UTF-7","csUTF7"}, name);
        }

        if constexpr(id_ == details::id::UTF16BE) {
            return do_compare({"UTF-16BE","csUTF16BE"}, name);
        }

        if constexpr(id_ == details::id::UTF16LE) {
            return do_compare({"UTF-16LE","csUTF16LE"}, name);
        }

        if constexpr(id_ == details::id::UTF16) {
            return do_compare({"UTF-16","csUTF16"}, name);
        }

        if constexpr(id_ == details::id::CESU8) {
            return do_compare({"CESU-8","csCESU-8","csCESU8"}, name);
        }

        if constexpr(id_ == details::id::UTF32) {
            return do_compare({"UTF-32","csUTF32"}, name);
        }

        if constexpr(id_ == details::id::UTF32BE) {
            return do_compare({"UTF-32BE","csUTF32BE"}, name);
        }

        if constexpr(id_ == details::id::UTF32LE) {
            return do_compare({"UTF-32LE","csUTF32LE"}, name);
        }

        if constexpr(id_ == details::id::BOCU1) {
            return do_compare({"BOCU-1","csBOCU-1","csBOCU1"}, name);
        }

        if constexpr(id_ == details::id::Windows30Latin1) {
            return do_compare({"ISO-8859-1-Windows-3.0-Latin-1","csWindows30Latin1"}, name);
        }

        if constexpr(id_ == details::id::Windows31Latin1) {
            return do_compare({"ISO-8859-1-Windows-3.1-Latin-1","csWindows31Latin1"}, name);
        }

        if constexpr(id_ == details::id::Windows31Latin2) {
            return do_compare({"ISO-8859-2-Windows-Latin-2","csWindows31Latin2"}, name);
        }

        if constexpr(id_ == details::id::Windows31Latin5) {
            return do_compare({"ISO-8859-9-Windows-Latin-5","csWindows31Latin5"}, name);
        }

        if constexpr(id_ == details::id::HPRoman8) {
            return do_compare({"hp-roman8","csHPRoman8","r8","roman8"}, name);
        }

        if constexpr(id_ == details::id::AdobeStandardEncoding) {
            return do_compare({"Adobe-Standard-Encoding","csAdobeStandardEncoding"}, name);
        }

        if constexpr(id_ == details::id::VenturaUS) {
            return do_compare({"Ventura-US","csVenturaUS"}, name);
        }

        if constexpr(id_ == details::id::VenturaInternational) {
            return do_compare({"Ventura-International","csVenturaInternational"}, name);
        }

        if constexpr(id_ == details::id::DECMCS) {
            return do_compare({"DEC-MCS","csDECMCS","dec"}, name);
        }

        if constexpr(id_ == details::id::PC850Multilingual) {
            return do_compare({"IBM850","850","cp850","csPC850Multilingual"}, name);
        }

        if constexpr(id_ == details::id::PC8DanishNorwegian) {
            return do_compare({"PC8-Danish-Norwegian","csPC8DanishNorwegian"}, name);
        }

        if constexpr(id_ == details::id::PC862LatinHebrew) {
            return do_compare({"IBM862","862","cp862","csPC862LatinHebrew"}, name);
        }

        if constexpr(id_ == details::id::PC8Turkish) {
            return do_compare({"PC8-Turkish","csPC8Turkish"}, name);
        }

        if constexpr(id_ == details::id::IBMSymbols) {
            return do_compare({"IBM-Symbols","csIBMSymbols"}, name);
        }

        if constexpr(id_ == details::id::IBMThai) {
            return do_compare({"IBM-Thai","csIBMThai"}, name);
        }

        if constexpr(id_ == details::id::HPLegal) {
            return do_compare({"HP-Legal","csHPLegal"}, name);
        }

        if constexpr(id_ == details::id::HPPiFont) {
            return do_compare({"HP-Pi-font","csHPPiFont"}, name);
        }

        if constexpr(id_ == details::id::HPMath8) {
            return do_compare({"HP-Math8","csHPMath8"}, name);
        }

        if constexpr(id_ == details::id::HPPSMath) {
            return do_compare({"Adobe-Symbol-Encoding","csHPPSMath"}, name);
        }

        if constexpr(id_ == details::id::HPDesktop) {
            return do_compare({"HP-DeskTop","csHPDesktop"}, name);
        }

        if constexpr(id_ == details::id::VenturaMath) {
            return do_compare({"Ventura-Math","csVenturaMath"}, name);
        }

        if constexpr(id_ == details::id::MicrosoftPublishing) {
            return do_compare({"Microsoft-Publishing","csMicrosoftPublishing"}, name);
        }

        if constexpr(id_ == details::id::Windows31J) {
            return do_compare({"Windows-31J","csWindows31J"}, name);
        }

        if constexpr(id_ == details::id::GB2312) {
            return do_compare({"GB2312","csGB2312"}, name);
        }

        if constexpr(id_ == details::id::Big5) {
            return do_compare({"Big5","csBig5"}, name);
        }

        if constexpr(id_ == details::id::Macintosh) {
            return do_compare({"macintosh","csMacintosh","mac"}, name);
        }

        if constexpr(id_ == details::id::IBM037) {
            return do_compare({"IBM037","cp037","csIBM037","ebcdic-cp-ca","ebcdic-cp-nl","ebcdic-cp-us","ebcdic-cp-wt"}, name);
        }

        if constexpr(id_ == details::id::IBM038) {
            return do_compare({"IBM038","EBCDIC-INT","cp038","csIBM038"}, name);
        }

        if constexpr(id_ == details::id::IBM273) {
            return do_compare({"IBM273","CP273","csIBM273"}, name);
        }

        if constexpr(id_ == details::id::IBM274) {
            return do_compare({"IBM274","CP274","EBCDIC-BE","csIBM274"}, name);
        }

        if constexpr(id_ == details::id::IBM275) {
            return do_compare({"IBM275","EBCDIC-BR","cp275","csIBM275"}, name);
        }

        if constexpr(id_ == details::id::IBM277) {
            return do_compare({"IBM277","EBCDIC-CP-DK","EBCDIC-CP-NO","csIBM277"}, name);
        }

        if constexpr(id_ == details::id::IBM278) {
            return do_compare({"IBM278","CP278","csIBM278","ebcdic-cp-fi","ebcdic-cp-se"}, name);
        }

        if constexpr(id_ == details::id::IBM280) {
            return do_compare({"IBM280","CP280","csIBM280","ebcdic-cp-it"}, name);
        }

        if constexpr(id_ == details::id::IBM281) {
            return do_compare({"IBM281","EBCDIC-JP-E","cp281","csIBM281"}, name);
        }

        if constexpr(id_ == details::id::IBM284) {
            return do_compare({"IBM284","CP284","csIBM284","ebcdic-cp-es"}, name);
        }

        if constexpr(id_ == details::id::IBM285) {
            return do_compare({"IBM285","CP285","csIBM285","ebcdic-cp-gb"}, name);
        }

        if constexpr(id_ == details::id::IBM290) {
            return do_compare({"IBM290","EBCDIC-JP-kana","cp290","csIBM290"}, name);
        }

        if constexpr(id_ == details::id::IBM297) {
            return do_compare({"IBM297","cp297","csIBM297","ebcdic-cp-fr"}, name);
        }

        if constexpr(id_ == details::id::IBM420) {
            return do_compare({"IBM420","cp420","csIBM420","ebcdic-cp-ar1"}, name);
        }

        if constexpr(id_ == details::id::IBM423) {
            return do_compare({"IBM423","cp423","csIBM423","ebcdic-cp-gr"}, name);
        }

        if constexpr(id_ == details::id::IBM424) {
            return do_compare({"IBM424","cp424","csIBM424","ebcdic-cp-he"}, name);
        }

        if constexpr(id_ == details::id::PC8CodePage437) {
            return do_compare({"IBM437","437","cp437","csPC8CodePage437"}, name);
        }

        if constexpr(id_ == details::id::IBM500) {
            return do_compare({"IBM500","CP500","csIBM500","ebcdic-cp-be","ebcdic-cp-ch"}, name);
        }

        if constexpr(id_ == details::id::IBM851) {
            return do_compare({"IBM851","851","cp851","csIBM851"}, name);
        }

        if constexpr(id_ == details::id::PCp852) {
            return do_compare({"IBM852","852","cp852","csPCp852"}, name);
        }

        if constexpr(id_ == details::id::IBM855) {
            return do_compare({"IBM855","855","cp855","csIBM855"}, name);
        }

        if constexpr(id_ == details::id::IBM857) {
            return do_compare({"IBM857","857","cp857","csIBM857"}, name);
        }

        if constexpr(id_ == details::id::IBM860) {
            return do_compare({"IBM860","860","cp860","csIBM860"}, name);
        }

        if constexpr(id_ == details::id::IBM861) {
            return do_compare({"IBM861","861","cp-is","cp861","csIBM861"}, name);
        }

        if constexpr(id_ == details::id::IBM863) {
            return do_compare({"IBM863","863","cp863","csIBM863"}, name);
        }

        if constexpr(id_ == details::id::IBM864) {
            return do_compare({"IBM864","cp864","csIBM864"}, name);
        }

        if constexpr(id_ == details::id::IBM865) {
            return do_compare({"IBM865","865","cp865","csIBM865"}, name);
        }

        if constexpr(id_ == details::id::IBM868) {
            return do_compare({"IBM868","CP868","cp-ar","csIBM868"}, name);
        }

        if constexpr(id_ == details::id::IBM869) {
            return do_compare({"IBM869","869","cp-gr","cp869","csIBM869"}, name);
        }

        if constexpr(id_ == details::id::IBM870) {
            return do_compare({"IBM870","CP870","csIBM870","ebcdic-cp-roece","ebcdic-cp-yu"}, name);
        }

        if constexpr(id_ == details::id::IBM871) {
            return do_compare({"IBM871","CP871","csIBM871","ebcdic-cp-is"}, name);
        }

        if constexpr(id_ == details::id::IBM880) {
            return do_compare({"IBM880","EBCDIC-Cyrillic","cp880","csIBM880"}, name);
        }

        if constexpr(id_ == details::id::IBM891) {
            return do_compare({"IBM891","cp891","csIBM891"}, name);
        }

        if constexpr(id_ == details::id::IBM903) {
            return do_compare({"IBM903","cp903","csIBM903"}, name);
        }

        if constexpr(id_ == details::id::IBBM904) {
            return do_compare({"IBM904","904","cp904","csIBBM904"}, name);
        }

        if constexpr(id_ == details::id::IBM905) {
            return do_compare({"IBM905","CP905","csIBM905","ebcdic-cp-tr"}, name);
        }

        if constexpr(id_ == details::id::IBM918) {
            return do_compare({"IBM918","CP918","csIBM918","ebcdic-cp-ar2"}, name);
        }

        if constexpr(id_ == details::id::IBM1026) {
            return do_compare({"IBM1026","CP1026","csIBM1026"}, name);
        }

        if constexpr(id_ == details::id::IBMEBCDICATDE) {
            return do_compare({"EBCDIC-AT-DE","csIBMEBCDICATDE"}, name);
        }

        if constexpr(id_ == details::id::EBCDICATDEA) {
            return do_compare({"EBCDIC-AT-DE-A","csEBCDICATDEA"}, name);
        }

        if constexpr(id_ == details::id::EBCDICCAFR) {
            return do_compare({"EBCDIC-CA-FR","csEBCDICCAFR"}, name);
        }

        if constexpr(id_ == details::id::EBCDICDKNO) {
            return do_compare({"EBCDIC-DK-NO","csEBCDICDKNO"}, name);
        }

        if constexpr(id_ == details::id::EBCDICDKNOA) {
            return do_compare({"EBCDIC-DK-NO-A","csEBCDICDKNOA"}, name);
        }

        if constexpr(id_ == details::id::EBCDICFISE) {
            return do_compare({"EBCDIC-FI-SE","csEBCDICFISE"}, name);
        }

        if constexpr(id_ == details::id::EBCDICFISEA) {
            return do_compare({"EBCDIC-FI-SE-A","csEBCDICFISEA"}, name);
        }

        if constexpr(id_ == details::id::EBCDICFR) {
            return do_compare({"EBCDIC-FR","csEBCDICFR"}, name);
        }

        if constexpr(id_ == details::id::EBCDICIT) {
            return do_compare({"EBCDIC-IT","csEBCDICIT"}, name);
        }

        if constexpr(id_ == details::id::EBCDICPT) {
            return do_compare({"EBCDIC-PT","csEBCDICPT"}, name);
        }

        if constexpr(id_ == details::id::EBCDICES) {
            return do_compare({"EBCDIC-ES","csEBCDICES"}, name);
        }

        if constexpr(id_ == details::id::EBCDICESA) {
            return do_compare({"EBCDIC-ES-A","csEBCDICESA"}, name);
        }

        if constexpr(id_ == details::id::EBCDICESS) {
            return do_compare({"EBCDIC-ES-S","csEBCDICESS"}, name);
        }

        if constexpr(id_ == details::id::EBCDICUK) {
            return do_compare({"EBCDIC-UK","csEBCDICUK"}, name);
        }

        if constexpr(id_ == details::id::EBCDICUS) {
            return do_compare({"EBCDIC-US","csEBCDICUS"}, name);
        }

        if constexpr(id_ == details::id::Unknown8BiT) {
            return do_compare({"UNKNOWN-8BIT","csUnknown8BiT"}, name);
        }

        if constexpr(id_ == details::id::Mnemonic) {
            return do_compare({"MNEMONIC","csMnemonic"}, name);
        }

        if constexpr(id_ == details::id::Mnem) {
            return do_compare({"MNEM","csMnem"}, name);
        }

        if constexpr(id_ == details::id::VISCII) {
            return do_compare({"VISCII","csVISCII"}, name);
        }

        if constexpr(id_ == details::id::VIQR) {
            return do_compare({"VIQR","csVIQR"}, name);
        }

        if constexpr(id_ == details::id::KOI8R) {
            return do_compare({"KOI8-R","csKOI8R"}, name);
        }

        if constexpr(id_ == details::id::HZGB2312) {
            return do_compare({"HZ-GB-2312"}, name);
        }

        if constexpr(id_ == details::id::IBM866) {
            return do_compare({"IBM866","866","cp866","csIBM866"}, name);
        }

        if constexpr(id_ == details::id::PC775Baltic) {
            return do_compare({"IBM775","cp775","csPC775Baltic"}, name);
        }

        if constexpr(id_ == details::id::KOI8U) {
            return do_compare({"KOI8-U","csKOI8U"}, name);
        }

        if constexpr(id_ == details::id::IBM00858) {
            return do_compare({"IBM00858","CCSID00858","CP00858","PC-Multilingual-850+euro","csIBM00858"}, name);
        }

        if constexpr(id_ == details::id::IBM00924) {
            return do_compare({"IBM00924","CCSID00924","CP00924","csIBM00924","ebcdic-Latin9--euro"}, name);
        }

        if constexpr(id_ == details::id::IBM01140) {
            return do_compare({"IBM01140","CCSID01140","CP01140","csIBM01140","ebcdic-us-37+euro"}, name);
        }

        if constexpr(id_ == details::id::IBM01141) {
            return do_compare({"IBM01141","CCSID01141","CP01141","csIBM01141","ebcdic-de-273+euro"}, name);
        }

        if constexpr(id_ == details::id::IBM01142) {
            return do_compare({"IBM01142","CCSID01142","CP01142","csIBM01142","ebcdic-dk-277+euro","ebcdic-no-277+euro"}, name);
        }

        if constexpr(id_ == details::id::IBM01143) {
            return do_compare({"IBM01143","CCSID01143","CP01143","csIBM01143","ebcdic-fi-278+euro","ebcdic-se-278+euro"}, name);
        }

        if constexpr(id_ == details::id::IBM01144) {
            return do_compare({"IBM01144","CCSID01144","CP01144","csIBM01144","ebcdic-it-280+euro"}, name);
        }

        if constexpr(id_ == details::id::IBM01145) {
            return do_compare({"IBM01145","CCSID01145","CP01145","csIBM01145","ebcdic-es-284+euro"}, name);
        }

        if constexpr(id_ == details::id::IBM01146) {
            return do_compare({"IBM01146","CCSID01146","CP01146","csIBM01146","ebcdic-gb-285+euro"}, name);
        }

        if constexpr(id_ == details::id::IBM01147) {
            return do_compare({"IBM01147","CCSID01147","CP01147","csIBM01147","ebcdic-fr-297+euro"}, name);
        }

        if constexpr(id_ == details::id::IBM01148) {
            return do_compare({"IBM01148","CCSID01148","CP01148","csIBM01148","ebcdic-international-500+euro"}, name);
        }

        if constexpr(id_ == details::id::IBM01149) {
            return do_compare({"IBM01149","CCSID01149","CP01149","csIBM01149","ebcdic-is-871+euro"}, name);
        }

        if constexpr(id_ == details::id::Big5HKSCS) {
            return do_compare({"Big5-HKSCS","csBig5HKSCS"}, name);
        }

        if constexpr(id_ == details::id::IBM1047) {
            return do_compare({"IBM1047","IBM-1047","csIBM1047"}, name);
        }

        if constexpr(id_ == details::id::PTCP154) {
            return do_compare({"PTCP154","CP154","Cyrillic-Asian","PT154","csPTCP154"}, name);
        }

        if constexpr(id_ == details::id::Amiga1251) {
            return do_compare({"Amiga-1251","Ami-1251","Ami1251","Amiga1251","csAmiga1251"}, name);
        }

        if constexpr(id_ == details::id::KOI7switched) {
            return do_compare({"KOI7-switched","csKOI7switched"}, name);
        }

        if constexpr(id_ == details::id::BRF) {
            return do_compare({"BRF","csBRF"}, name);
        }

        if constexpr(id_ == details::id::TSCII) {
            return do_compare({"TSCII","csTSCII"}, name);
        }

        if constexpr(id_ == details::id::CP51932) {
            return do_compare({"CP51932","csCP51932"}, name);
        }

        if constexpr(id_ == details::id::windows874) {
            return do_compare({"windows-874","cswindows874"}, name);
        }

        if constexpr(id_ == details::id::windows1250) {
            return do_compare({"windows-1250","cswindows1250"}, name);
        }

        if constexpr(id_ == details::id::windows1251) {
            return do_compare({"windows-1251","cswindows1251"}, name);
        }

        if constexpr(id_ == details::id::windows1252) {
            return do_compare({"windows-1252","cswindows1252"}, name);
        }

        if constexpr(id_ == details::id::windows1253) {
            return do_compare({"windows-1253","cswindows1253"}, name);
        }

        if constexpr(id_ == details::id::windows1254) {
            return do_compare({"windows-1254","cswindows1254"}, name);
        }

        if constexpr(id_ == details::id::windows1255) {
            return do_compare({"windows-1255","cswindows1255"}, name);
        }

        if constexpr(id_ == details::id::windows1256) {
            return do_compare({"windows-1256","cswindows1256"}, name);
        }

        if constexpr(id_ == details::id::windows1257) {
            return do_compare({"windows-1257","cswindows1257"}, name);
        }

        if constexpr(id_ == details::id::windows1258) {
            return do_compare({"windows-1258","cswindows1258"}, name);
        }

        if constexpr(id_ == details::id::TIS620) {
            return do_compare({"TIS-620","ISO-8859-11","csTIS620"}, name);
        }

        if constexpr(id_ == details::id::CP50220) {
            return do_compare({"CP50220","csCP50220"}, name);
        }

        return false;
    }
}


#ifndef H_COR3NTIN_ENCODINGS_HPP
#include "encodings_generated.hpp"
#endif

#ifdef _WIN32
namespace cor3ntin::encoding::details {
    struct encoding_windows_data
    {
        int cp;
        id  id;
    };
    constexpr encoding_windows_data win_mapping[] = {
        {037, id::IBM037},
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
        {932, id::ShiftJIS},
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
        {65001, id::UTF8}
    };

    inline id mib_from_page(int page) {
        for (const auto& e : win_mapping) {
            if (e.cp == page)
                return e.id;
        }
        return id::other;
    }
}
#endif
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

    static consteval text_encoding literal();
    static consteval text_encoding wide_literal();

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


}
#endif
