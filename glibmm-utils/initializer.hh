/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  Copyright (C) 2006 Dodji Seketeli
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef __GLIBMM_UTILS_INITIALIZER_H__
#define __GLIBMM_UTILS_INITIALIZER_H__

namespace Glib {
namespace Util {

/// \brief Initialization worker, necessary if you need thread-safety.
class Initializer {
public:
    /// \brief Optional initialization function for gtkmm-utils.
    /// Sets the entire default locale and initializes Glib threading.
    /// It is safe to call this function multiple times. You can of
    /// course initialize Glib threading yourself; in any case, this
    /// should most probably be the first thing in your main().
    /// \note
    /// If you're using the gtkmm-utils logging framework, and from
    /// multiple threads, make sure you call this function before 
    /// using any logging facilities, so that the internal mutex can
    /// be initialized correctly.
    static void do_init() ;

private:
    //non copyable
    Initializer();
    Initializer(const Initializer &);
    ~Initializer();
    Initializer& operator=(const Initializer &);

};

} // namespace Util
} // namespace Glib

#endif //__GLIBMM_UTILS_INITIALIZER_H__
