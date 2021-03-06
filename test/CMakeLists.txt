# CMakeLists.txt for SystemAbstractionsTests

cmake_minimum_required(VERSION 3.8)
set(This SystemAbstractionsTests)

set(Sources
    src/ClipboardTests.cpp
    src/DiagnosticsStreamReporterTests.cpp
    src/DiagnosticsContextTests.cpp
    src/DiagnosticsSenderTests.cpp
    src/DirectoryMonitorTests.cpp
    src/DynamicLibraryTests.cpp
    src/FileTests.cpp
    src/NetworkConnectionTests.cpp
    src/NetworkEndpointTests.cpp
    src/StringExtensionsTests.cpp
    src/StringFileTests.cpp
    src/SubprocessTests.cpp
)

add_executable(${This} ${Sources})

set_target_properties(${This} PROPERTIES
    FOLDER Tests
)

target_include_directories(${This} PRIVATE ..)

target_compile_definitions(${This} PRIVATE CLIPBOARD_REVEAL_OS_API)

target_link_libraries(${This} PUBLIC
    gtest_main
    SystemAbstractions
)

add_subdirectory(MockDynamicLibrary)
add_custom_command(TARGET ${This} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:MockDynamicLibrary> $<TARGET_FILE_DIR:${This}>
)

add_subdirectory(MockSubprocess)
add_custom_command(TARGET ${This} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:MockSubprocess> $<TARGET_FILE_DIR:${This}>
)


add_test(
    NAME ${This}
    COMMAND ${This}
)
