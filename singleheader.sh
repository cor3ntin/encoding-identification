#!/bin/bash


echo -e "#ifndef H_COR3NTIN_ENCODINGS_HPP\n" > single.hpp
echo -e "#define H_COR3NTIN_ENCODINGS_HPP\n" >> single.hpp

cat {encodings_base,encodings_generated,encodings}.hpp | sed -e's/#pragma once//g' >> single.hpp

echo -e "\n#endif" >> single.hpp