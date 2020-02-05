import csv
import re

HEADER = """
#pragma once
namespace cor3ntin::encoding::details {{
        enum class id {{
            other = 1,
            unknown = 2,
{}
            reserved = 3000
        }};
        struct enc_data {{
            int mib;
            const char* name;
        }};
        constexpr bool compare_name(const char* a, const char* b) noexcept;
        const enc_data data[] = {{
{}            {{ 0, nullptr }}
        }};
    template <id id_>
    constexpr bool encoding_is(const char* name) {{
        {}
        return false;
    }}
}}
""";

def get_enum_name(lst, name):
    e = [x for x in lst if x.startswith("cs")]
    if len(e) == 0:
        e = "".join(filter(lambda c : str.isalnum(c) and c != '-', name))
    else:
        e = e[0][2:]
        e = "".join(filter(lambda c : c != '-', e))
    return e

def get_encoding():
    encodings = []
    with open('character-sets-1.csv', newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            aliases = list(set([x for x in row['Aliases'].splitlines() if x is not '' and x[0] != '(']))
            aliases.sort()
            mime = row['Preferred MIME Name']
            name = row['Name']
            if name in aliases:
                aliases.remove(name)
            aliases = [name] + aliases

            if mime is not '':
                if mime in aliases:
                    aliases.remove(mime)
                aliases = [mime] + aliases


            n = row['MIBenum']
            e = get_enum_name(aliases, name)

            if int(n) > 1 and len(e) > 1 :
                encodings.append((n, e, aliases))

    return encodings

if __name__ == "__main__":
    encodings = get_encoding()
    enum_format = ""
    data_format = "";
    template_formats = "";


    for enc in encodings:
        enum_format = enum_format + "            {} = {},\n".format(enc[1], enc[0])
        lst = "{" + ",".join(['"' + n + '"' for n in enc[2]]) + "}"
        for alias in enc[2]:
            data_format = data_format + "            {{ {}, \"{}\" }},\n".format(enc[0], alias)
        template_formats = template_formats + """
        if constexpr(id_ == details::id::{}) {{
            return do_compare({}, name);
        }}
        """.format(enc[1], lst)


    print(HEADER.format(enum_format, data_format, template_formats))





