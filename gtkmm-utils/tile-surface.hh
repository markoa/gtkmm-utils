/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - tile-surface.hh
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

#ifndef __GTKMM_UTILS_TILE_SURFACE_H__
#define __GTKMM_UTILS_TILE_SURFACE_H__

#include <gtkmm/box.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/image.h>

namespace Gtk {

namespace Util {

class TileSurface : public Gtk::EventBox
{
public:
    explicit TileSurface();
    virtual ~TileSurface();

    Gtk::HBox* get_root_hbox();
    Gtk::Image* get_image();

    typedef sigc::signal<void> SignalTileSelected;

    SignalTileSelected& get_signal_tile_selected();

protected:
    // Gtk::Widget overrides
    virtual void on_size_request(Gtk::Requisition* requisition);
    virtual void on_size_allocate(Gtk::Allocation& allocation);
    virtual bool on_expose_event(GdkEventExpose* event);
    virtual bool on_button_press_event(GdkEventButton* event);
    virtual bool on_focus_in_event(GdkEventFocus* event);

    Gtk::HBox* hbox_;
    Gtk::Image* image_;

private:
    // TODO: make copyable?
    TileSurface(const TileSurface& other);
    TileSurface& operator=(const TileSurface&);

    SignalTileSelected signal_tile_selected_;
};

//

inline Gtk::HBox*
TileSurface::get_root_hbox()
{
    return hbox_;
}

inline Gtk::Image*
TileSurface::get_image()
{
    return image_;
}

inline TileSurface::SignalTileSelected&
TileSurface::get_signal_tile_selected()
{
    return signal_tile_selected_;
}

} // namespace Util

} // namespace Gtk

#endif // __GTKMM_UTILS_TILE_SURFACE_H__
