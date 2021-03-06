# CMakeLists.txt for SystemAbstractions
#
# © 2018 by Richard Walters

cmake_minimum_required(VERSION 3.8)
set(This SystemAbstractions)

set(Headers
    include/SystemAbstractions/Clipboard.hpp
    include/SystemAbstractions/DiagnosticsContext.hpp
    include/SystemAbstractions/DiagnosticsSender.hpp
    include/SystemAbstractions/DiagnosticsStreamReporter.hpp
    include/SystemAbstractions/DirectoryMonitor.hpp
    include/SystemAbstractions/DynamicLibrary.hpp
    include/SystemAbstractions/File.hpp
    include/SystemAbstractions/IFile.hpp
    include/SystemAbstractions/IFileCollection.hpp
    include/SystemAbstractions/NetworkConnection.hpp
    include/SystemAbstractions/NetworkEndpoint.hpp
    include/SystemAbstractions/StringExtensions.hpp
    include/SystemAbstractions/StringFile.hpp
    include/SystemAbstractions/Subprocess.hpp
    include/SystemAbstractions/TargetInfo.hpp
    include/SystemAbstractions/Time.hpp
)

set(Sources
    src/DiagnosticsContext.cpp
    src/DiagnosticsSender.cpp
    src/DiagnosticsStreamReporter.cpp
    src/File.cpp
    src/FileImpl.hpp
    src/NetworkConnection.cpp
    src/NetworkConnectionImpl.hpp
    src/NetworkEndpoint.cpp
    src/NetworkEndpointImpl.hpp
    src/StringExtensions.cpp
    src/StringFile.cpp
)

if(MSVC)
    list(APPEND Sources
        src/Win32/ClipboardWin32.cpp
        src/Win32/DirectoryMonitorWin32.cpp
        src/Win32/DynamicLibraryWin32.cpp
        src/Win32/FileWin32.cpp
        src/Win32/NetworkConnectionWin32.cpp
        src/Win32/NetworkConnectionWin32.hpp
        src/Win32/NetworkEndpointWin32.cpp
        src/Win32/NetworkEndpointWin32.hpp
        src/Win32/SubprocessWin32.cpp
        src/Win32/TargetInfoWin32.cpp
        src/Win32/TimeWin32.cpp
    )
    set(TargetFolders Win32)
    add_definitions(
        -DUNICODE -D_UNICODE
        -D_CRT_SECURE_NO_WARNINGS
    )
elseif(APPLE)
elseif(UNIX)
endif()

add_library(${This} STATIC ${Sources} ${Headers})
set_target_properties(${This} PROPERTIES
    FOLDER Libraries
)

if(APPLE)
    find_library(CF CoreFoundation)
    target_link_libraries(${This} ${CF})
endif(APPLE)
if(UNIX)
    target_link_libraries(${This}
        pthread
        dl
    )
endif(UNIX)

target_compile_definitions(${This} PRIVATE CLIPBOARD_REVEAL_OS_API)

target_include_directories(${This} PUBLIC include)

add_subdirectory(test)
