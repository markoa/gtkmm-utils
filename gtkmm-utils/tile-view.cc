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

#include <gtkmm/stock.h>
#include "tile-view.hh"

namespace Gtk {

namespace Util {

static const int TILES_PER_PAGE_DEFAULT = 50;

class TileView::Navigator : public Gtk::HBox
{
public:
    explicit Navigator()
        :
        align_box_(0.0, 1.0, 1.0, 1.0),
        label_hbox_(false, 0),
        label_("I am the title"),
        button_previous_(),
        image_previous_(Gtk::Stock::GO_BACK, Gtk::ICON_SIZE_SMALL_TOOLBAR),
        button_next_(),
        image_next_(Gtk::Stock::GO_FORWARD, Gtk::ICON_SIZE_SMALL_TOOLBAR)
        {
            align_box_.set_padding(18, 3, 0, 0);
            pack_start(align_box_, false, true, 0);

            align_box_.add(label_hbox_);
            label_hbox_.pack_start(label_, false, true, 0);
            label_.set_justify(Gtk::JUSTIFY_LEFT);

            button_next_.set_relief(Gtk::RELIEF_NONE);
            button_next_.add(image_next_);
            pack_end(button_next_, false, true, 0);

            button_previous_.set_relief(Gtk::RELIEF_NONE);
            button_previous_.add(image_previous_);
            pack_end(button_previous_, false, true, 0);
            
            show_all();
        }

    ~Navigator() {}
    
protected:
    Gtk::Alignment align_box_;
    Gtk::HBox      label_hbox_;
    Gtk::Label     label_;
    Gtk::Button    button_previous_;
    Gtk::Image     image_previous_;
    Gtk::Button    button_next_;
    Gtk::Image     image_next_;

private:
    Navigator(const Navigator& );
    Navigator& operator=(const Navigator& );
};


TileView::TileView()
    :
    tiles_per_page_(TILES_PER_PAGE_DEFAULT),
    scrolled_window_(),
    hadjustment_(0, 0, 0, 0),
    vadjustment_(0, 0, 0, 0),
    viewport_(hadjustment_, vadjustment_),
    whitebox_(),
    selected_tile_(0)
{
    navigator_.reset(new Navigator());
    pack_start(*navigator_, false, true, 0);

    scrolled_window_.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled_window_.set_shadow_type(Gtk::SHADOW_IN);
    pack_start(scrolled_window_, true, true, 0);

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
    add_tile(&tile);
}

void
TileView::add_tile(Tile* tile)
{
    tile->show();

    Gtk::Box& wb_box = whitebox_.get_root_vbox();
    wb_box.pack_start(*tile, false, false, 0);

    tile->signal_selected().connect(
        sigc::mem_fun(*this, &TileView::on_tile_selected));

    tile->signal_activated().connect(
        sigc::mem_fun(*this, &TileView::on_tile_activated));

    tiles_.push_back(tile);
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

TileView::SignalTileActivated&
TileView::signal_tile_activated()
{
    return signal_tile_activated_;
}

void
TileView::on_tile_selected(Tile& tile)
{
    selected_tile_ = &tile;
}

void
TileView::on_tile_activated(Tile& tile)
{
    signal_tile_activated_.emit(tile);
}

} // namespace Util

} // namespace Gtk
