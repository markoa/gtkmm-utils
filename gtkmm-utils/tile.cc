/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - tile.cc
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

#include "tile.hh"

namespace Gtk {

namespace Util {

Tile::Tile(const Glib::ustring& title,
           const Glib::ustring& summary,
           bool paint_white)
    :
    title_(title),
    summary_(summary),
    paint_white_(paint_white)
{
    set_flags(Gtk::CAN_FOCUS);
}

Tile::~Tile()
{
}

Gtk::HBox&
Tile::get_root_hbox()
{
    return hbox_;
}

Gtk::Image&
Tile::get_image()
{
    return image_;
}

Tile::SignalTileSelected&
Tile::get_signal_tile_selected()
{
    return signal_tile_selected_;
}

bool
Tile::on_expose_event(GdkEventExpose* event)
{
    if (event) {}
    return false;
}

bool
Tile::on_button_press_event(GdkEventButton* /* event */)
{
    grab_focus();
    return false;
}

} // namespace Util

} // namespace Gtk
