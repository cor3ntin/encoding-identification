project(encoding-detection)
set (CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.18)


find_package (Python3 COMPONENTS Interpreter REQUIRED)

add_custom_command(OUTPUT src/encodings_generated.hpp
    COMMAND
        ${Python3_EXECUTABLE} generate.py > encodings_generated.hpp
    WORKING_DIRECTORY
        ${CMAKE_SOURCE_DIR}/src
    COMMENT
        "Generating encoding list"
    DEPENDS
        src/generate.py src/character-sets-1.csv)

IF (WIN32)
add_custom_command(OUTPUT ${CMAKE_SOURCE_DIR}/generated_include/cor3ntin/encodings_detection.hpp
    COMMAND
        ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/generated_include/cor3ntin/
    COMMAND
        ${CMAKE_SOURCE_DIR}/singleheader.bat >> ${CMAKE_SOURCE_DIR}/generated_include/cor3ntin/encodings_detection.hpp
    COMMAND
         ${CMAKE_SOURCE_DIR}/simplesed.bat "${CMAKE_SOURCE_DIR}/generated_include/cor3ntin/encodings_detection.hpp"
    WORKING_DIRECTORY
        ${CMAKE_SOURCE_DIR}/src
    COMMENT
        "Building single header"
    DEPENDS
        src/encodings_base.hpp src/encodings_windows.hpp src/encodings.hpp
)
ELSE()
add_custom_command(OUTPUT ${CMAKE_SOURCE_DIR}/generated_include/cor3ntin/encodings_detection.hpp
    COMMAND
        ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/generated_include/cor3ntin/
    COMMAND
        ${CMAKE_SOURCE_DIR}/singleheader.sh >> ${CMAKE_SOURCE_DIR}/generated_include/cor3ntin/encodings_detection.hpp
    WORKING_DIRECTORY
        ${CMAKE_SOURCE_DIR}/src
    COMMENT
        "Building single header"
    DEPENDS
        src/encodings_base.hpp src/encodings_windows.hpp src/encodings.hpp
)
ENDIF()

add_library(encoding-detection INTERFACE)
target_sources(encoding-detection INTERFACE ${CMAKE_SOURCE_DIR}/generated_include/cor3ntin/encodings_detection.hpp)
target_include_directories(encoding-detection INTERFACE ${CMAKE_SOURCE_DIR}/generated_include/)

add_executable(encoding-detection-demo main.cpp)
target_link_libraries(encoding-detection-demo PUBLIC encoding-detection)