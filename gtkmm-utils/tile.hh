/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - tile.hh
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

#ifndef __GTKMM_UTILS_TILE_H__
#define __GTKMM_UTILS_TILE_H__

#include <gtkmm/box.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>

namespace Gtk {

namespace Util {

class Tile : public Gtk::EventBox
{
public:
    explicit Tile(const Glib::ustring& title = Glib::ustring(),
                  const Glib::ustring& summary = Glib::ustring(),
                  bool paint_white = true);
    virtual ~Tile();

    Gtk::HBox& get_root_hbox();
    Gtk::Image& get_image();
    Gtk::VBox& get_content_vbox();

    typedef sigc::signal<void> SignalTileSelected;

    SignalTileSelected& get_signal_tile_selected();

protected:
    // Gtk::Widget overrides
    virtual bool on_expose_event(GdkEventExpose* event);
    virtual bool on_button_press_event(GdkEventButton* event);

    // Child widgets
    Gtk::HBox root_hbox_;
    Gtk::Image image_;
    Gtk::VBox content_vbox_;
    Gtk::Label title_label_;
    Gtk::Label summary_label_;

    // Data members
    Glib::ustring title_;
    Glib::ustring summary_;
    bool paint_white_;

private:
    // Non-copyable
    Tile(const Tile& other);
    Tile& operator=(const Tile&);

    SignalTileSelected signal_tile_selected_;
};

} // namespace Util

} // namespace Gtk

#endif // __GTKMM_UTILS_TILE_H__
