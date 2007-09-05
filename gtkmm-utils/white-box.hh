/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - white-box.hh
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

#ifndef __GTKMM_UTILS_WHITE_BOX_H__
#define __GTKMM_UTILS_WHITE_BOX_H__

#include <gtkmm/box.h>
#include <gtkmm/eventbox.h>

namespace Gtk {

namespace Util {

class WhiteBox : public Gtk::EventBox
{
public:
    explicit WhiteBox();
    virtual ~WhiteBox();

    Gtk::VBox& get_root_vbox();

protected:
    virtual bool on_expose_event(GdkEventExpose* event);

    Gtk::VBox root_vbox_;

private:
    // Non-copyable.
    WhiteBox(const WhiteBox&);
    WhiteBox& operator=(const WhiteBox&);
};

} // namespace Util

} // namespace Gtk

#endif // __GTKMM_UTILS_WHITE_BOX_H__
