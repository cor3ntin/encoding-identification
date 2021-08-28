#!/bin/bash


echo -e "#ifndef H_COR3NTIN_ENCODINGS_HPP\n"
echo -e "#define H_COR3NTIN_ENCODINGS_HPP\n"

cat {encodings_base,encodings_generated,encodings_windows,encodings}.hpp | sed -e's/#pragma once//g'

echo -e "\n#endif"