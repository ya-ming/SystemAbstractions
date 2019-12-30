# CMakeLists.txt for MockDynamicLibrary
#

cmake_minimum_required(VERSION 3.8)
set(This MockDynamicLibrary)

set(Sources
    src/MockDynamicLibrary.cpp
)

add_library(${This} SHARED ${Sources})
set_target_properties(${This} PROPERTIES
    FOLDER TestHelpers
)

target_link_libraries(${This} PUBLIC
)