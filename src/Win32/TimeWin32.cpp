/**
 * @file TimeWin32.cpp
 *
 * This module contains the Win32 specific part of the 
 * implementation of the SystemAbstractions::Time class.
 *
 * Copyright (c) 2016 by Richard Walters
 */

/**
 * Windows.h should always be included first because other Windows header
 * files, such as KnownFolders.h, don't always define things properly if
 * you don't include Windows.h first.
 */
#include <Windows.h>

#include <SystemAbstractions/Time.hpp>

namespace SystemAbstractions {

    /**
     * This is the Win32-specific state for the Time class.
     */
    struct TimeImpl {
        double scale = 0.0;
    };

    Time::Time()
        : _impl(new TimeImpl())
    {
    }

    Time::~Time() {
    }

    double Time::GetTime() {
        if (_impl->scale == 0.0) {
            LARGE_INTEGER freq;
            (void)QueryPerformanceFrequency(&freq);
            _impl->scale = 1.0 / (double)freq.QuadPart;
        }
        LARGE_INTEGER now;
        (void)QueryPerformanceCounter(&now);
        return (double)now.QuadPart * _impl->scale;
    }

    struct tm Time::localtime(time_t time) {
        if (time == 0) {
            (void)::time(&time);
        }
        struct tm timeStruct;
        (void)localtime_s(&timeStruct, &time);
        return timeStruct;
    }

    struct tm Time::gmtime(time_t time) {
        if (time == 0) {
            (void)::time(&time);
        }
        struct tm timeStruct;
        (void)gmtime_s(&timeStruct, &time);
        return timeStruct;
    }

}
