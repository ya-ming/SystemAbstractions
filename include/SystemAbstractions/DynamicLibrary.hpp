#ifndef SYSTEM_ABSTRACTIONS_DYNAMIC_LIBRARY_HPP
#define SYSTEM_ABSTRACTIONS_DYNAMIC_LIBRARY_HPP

/**
 * @file DynamicLibrary.hpp
 *
 * This module declares the SystemAbstractions::DynamicLibrary class.
 *
 * Copyright (c) 2016 by Richard Walters
 */

#include <memory>
#include <string>

namespace SystemAbstractions {

    /**
     * This class represents a dynamically loaded library.
     */
    class DynamicLibrary {
        // Public methods
    public:
        /**
         * This is an instance constructor.
         */
        DynamicLibrary();

        /**
         * This is an instance constructor.
         *
         * @param impl
         *     This is an existing set of properties to encapsulate
         *     into a new object.
         */
        DynamicLibrary(std::unique_ptr< struct DynamicLibraryImpl >&& impl) noexcept;

        /**
         * This is the instance move constructor.
         */
        DynamicLibrary(DynamicLibrary&& other) noexcept;

        /**
         * This is the instance destructor.
         */
        ~DynamicLibrary();

        /**
         * This is the move assignment operator.
         */
        DynamicLibrary& operator=(DynamicLibrary&& other) noexcept;

        /**
         * @todo Needs documentation
         */
        bool Load(const std::string& path, const std::string& name);

        /**
         * @todo Needs documentation
         */
        void Unload();

        /**
         * @todo Needs documentation
         */
        void* GetProcedure(const std::string& name);

        /**
         * This method returns a human-readable string describing
         * the last error that occurred calling another
         * method on the object.
         *
         * @return
         *     A human-readable string describing the last error
         *     that occurred calling another method of the
         *     object is returned.
         */
        std::string GetLastError();

        // Disable copy constructor and assignment operator.
        DynamicLibrary(const DynamicLibrary&) = delete;
        DynamicLibrary& operator=(const DynamicLibrary&) = delete;

        // Private properties
    private:
        std::unique_ptr< struct DynamicLibraryImpl > _impl;
    };

}

#endif /* SYSTEM_ABSTRACTIONS_DYNAMIC_LIBRARY_HPP */
