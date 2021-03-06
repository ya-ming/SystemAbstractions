#ifndef SYSTEM_ABSTRACTIONS_FILE_IMPL_HPP
#define SYSTEM_ABSTRACTIONS_FILE_IMPL_HPP

/**
 *
 * This module contains the platform-independent part of the
 * implementation of the SystemAbstractions::File class.
 */

#include <memory>
#include <SystemAbstractions/File.hpp>

namespace SystemAbstractions {
    struct File::Impl {
        // properties

        /**
         * This is the path to the file in the file system.
         */
        std::string path;

        /**
         * This contains any platform-specific private properties
         * of the class.
         */
        std::unique_ptr<Platform> platform;

        // Lifecycle Management

        ~Impl();
        Impl(Impl&&);
        Impl& operator = (Impl&&);

        // Methods

        Impl();

        /**
         * This is a helper function which creates all the directories
         * in the given path that don't already exist.
         *
         * @param[in] path
         *     This is the path for which to ensure all the directories
         *     in it are created if they don't already exist.
         */
        static bool CreatePath(std::string path);
    };
}

#endif
