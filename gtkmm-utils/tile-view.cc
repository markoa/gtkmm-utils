/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - tile-view.cc
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

#include "tile-view.hh"

namespace Gtk {

namespace Util {

TileView::TileView()
    :
    scrolled_window_(),
    hadjustment_(0, 0, 0, 0),
    vadjustment_(0, 0, 0, 0),
    viewport_(hadjustment_, vadjustment_),
    whitebox_(),
    selected_tile_(0)
{
    scrolled_window_.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled_window_.set_shadow_type(Gtk::SHADOW_IN);
    add(scrolled_window_);

    viewport_.set_resize_mode(Gtk::RESIZE_PARENT);
    viewport_.set_shadow_type(Gtk::SHADOW_IN);
    scrolled_window_.add(viewport_);
    viewport_.show();

    viewport_.add(whitebox_);
}

TileView::~TileView()
{
}

void
TileView::add_tile(Tile& tile)
{
    tile.show();

    Gtk::Box& wb_box = whitebox_.get_root_vbox();
    wb_box.pack_start(tile, false, false, 0);

    Tile* ptile = &tile;

    ptile->signal_selected().connect(
        sigc::mem_fun(*this, &TileView::on_tile_selected));

    ptile->signal_double_click().connect(
        sigc::mem_fun(*this, &TileView::on_tile_double_clicked));

    tiles_.push_back(ptile);
}

TileView::iterator
TileView::begin()
{
    return tiles_.begin();
}

TileView::const_iterator
TileView::begin() const
{
    return tiles_.begin();
}

TileView::iterator
TileView::end()
{
    return tiles_.end();
}

TileView::const_iterator
TileView::end() const
{
    return tiles_.end();
}

Tile*
TileView::get_selection()
{
    return selected_tile_;
}

TileView::SignalDoubleClick&
TileView::signal_double_click()
{
    return signal_double_click_;
}

void
TileView::on_tile_selected(Tile& tile)
{
    selected_tile_ = &tile;
}

void
TileView::on_tile_double_clicked(Tile& tile)
{
    signal_double_click_.emit(tile);
}

} // namespace Util

} // namespace Gtk
