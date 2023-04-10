import csv
import re
import collections
import operator

HEADER = """
#pragma once
namespace cor3ntin::encoding::details {{
        enum class id {{
            other = 1,
            unknown = 2,
{}
        }};
        struct enc_data {{
            int mib;
            const char* name;
        }};
        constexpr inline enc_data data[] = {{
{}
        }};
    template <id id_>
    constexpr bool encoding_is(const char* name) noexcept {{
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
    if e == "Unicode":
        e = "UCS2"
    if e == "IBBM904":
        e = "IBM904"
    return e

def get_encoding():
    encodings = []
    with open('character-sets-1.csv', newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            aliases = list(set([x for x in row['Aliases'].splitlines() if x != '' and x[0] != '(']))
            aliases.sort()
            mime = row['Preferred MIME Name']
            name = row['Name']
            if name in aliases:
                aliases.remove(name)
            aliases = [name] + aliases

            if mime != '':
                if mime in aliases:
                    aliases.remove(mime)
                aliases = [mime] + aliases

            #aliases = list(set([name.replace('-', '').replace('_', '').upper() for name in aliases]))


            n = row['MIBenum']
            e = get_enum_name(aliases, name)

            # mib==33 and mib==34 are the excluded NATS-DANO and NATS-DANO-ADD, respectively
            if int(n) > 1 and int(n) != 33 and int(n) != 34 and len(e) > 1 :
                encodings.append((n, e, aliases))

    return encodings

if __name__ == "__main__":
    encodings = get_encoding()
    enum_format = ""
    data_format = "";
    template_formats = "";


    max = 0
    names = []

    for enc in sorted(encodings, key=lambda tup: int(tup[0])):
        enum_format = enum_format + "            {} = {},\n".format(enc[1], enc[0])
        #names.append(enc[1])
        if len(enc[1]) > max: max = len(enc[1])
        lst = "{" + ",".join(['"' + n + '"' for n in enc[2]]) + "}"
        for alias in enc[2]:
            if len(alias) > max: max = len(alias)
            names.append(alias)
            data_format = data_format + "            {{ {}, \"{}\" }},\n".format(enc[0], alias)
        template_formats = template_formats + """
        if constexpr(id_ == details::id::{}) {{
            return details::do_compare({}, name);
        }}
        """.format(enc[1], lst)

    #print(max)

    #names = [name.replace('-', '').replace('_', '').upper() for name in names]
    #print([(item, count) for item, count in collections.Counter(names).items() if count > 1])



    print(HEADER.format(enum_format, data_format, template_formats))





