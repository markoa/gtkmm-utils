/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - dialog.h
 *
 *  Copyright (C) 2007 Marko Anastasov
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

#ifndef __GTKMM_UTILS_DIALOG_H__
#define __GTKMM_UTILS_DIALOG_H__

#include <glibmm/ustring.h>

namespace Gtk
{

namespace Util
{

    int display_dialog_info(const Glib::ustring& message,
                            const Glib::ustring& title = Glib::ustring(),
                            const Glib::ustring& secondary_text = Glib::ustring());

    int display_dialog_warning(const Glib::ustring& message,
                               const Glib::ustring& title = Glib::ustring(),
                               const Glib::ustring& secondary_text = Glib::ustring());

    int display_dialog_error(const Glib::ustring& message,
                             const Glib::ustring& title = Glib::ustring(),
                             const Glib::ustring& secondary_text = Glib::ustring());

    int ask_yes_no_question(const Glib::ustring& message,
                            const Glib::ustring& title = Glib::ustring(),
                            const Glib::ustring& secondary_text = Glib::ustring());

    int ask_yes_no_cancel_question(const Glib::ustring& message,
                                   const Glib::ustring& title = Glib::ustring(),
                                   const Glib::ustring& secondary_text = Glib::ustring());

} // namespace Util

} // namespace Gtk

#endif // __GTKMM_UTILS_DIALOG_H__
