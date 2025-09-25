cmake_minimum_required(VERSION 3.10.2) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++ -fpermissive -Wfatal-errors -Wall -lws2_32 -lssl -s")

# BNM
add_library(BNM 
                "bnm/src/bnm.cpp"
                "bnm/src/dumper.cpp"
                "bnm/src/array.cpp"
                "bnm/src/string.cpp"
                "bnm/src/domain.cpp"
                "bnm/src/assembly.cpp" 
                "bnm/src/image.cpp" 
                "bnm/src/class.cpp" 
                "bnm/src/object.cpp" 
                "bnm/src/method.cpp" 
                "bnm/src/field.cpp" 
                "bnm/src/type.cpp" 
                "bnm/src/exports.cpp")