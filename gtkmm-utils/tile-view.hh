/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - tile-view.hh
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

#ifndef __GTKMM_UTILS_TILE_VIEW_H__
#define __GTKMM_UTILS_TILE_VIEW_H__

#include <gtkmm/adjustment.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/viewport.h>
#include "white-box.hh"

namespace Gtk {

namespace Util {

class TileView : public Gtk::VBox
{
public:
    explicit TileView();
    virtual ~TileView();

protected:
    Gtk::ScrolledWindow scrolled_window_;
    Gtk::Adjustment hadjustment_;
    Gtk::Adjustment vadjustment_;
    Gtk::Viewport viewport_;
    WhiteBox whitebox_;

private:
    // Non-copyable.
    TileView(const TileView&);
    TileView& operator=(const TileView&);
};

} // namespace Util

} // namespace Gtk

#endif // __GTKMM_UTILS_TILE_VIEW_H__
