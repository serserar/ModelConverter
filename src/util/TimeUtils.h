/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  <copyright holder> <email>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef TIMEUTILS_H
#define TIMEUTILS_H
#include <chrono>

class TimeUtils
{
public:
    TimeUtils();
    ~TimeUtils();
    static std::uint64_t currentTimeMillis();
    static std::uint64_t currentTimeSeconds();
};

class TimerClock {
public:
    void update () {
        last_time = current_time;
        current_time = static_cast<std::uint64_t>(TimeUtils::currentTimeSeconds()) / 1000.0;
    }

    std::uint64_t deltaTime () const {
        return (current_time - last_time);
    }
    std::uint64_t current_time;
    std::uint64_t last_time;
};
#endif // TIMEUTILS_H
