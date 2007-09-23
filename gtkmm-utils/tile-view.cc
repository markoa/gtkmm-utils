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

using std::list;
using std::tr1::shared_ptr;

static const int TILES_PER_PAGE_DEFAULT = 50;

/* TileView::TileData */

class TileView::TileData
{
public:
    TileData() : tile(0), member_page(1) {}
    ~TileData() {}

    Tile* tile;
    int   member_page;
};

/* TileView */

TileView::TileView()
    :
    scrolled_window_(),
    hadjustment_(0, 0, 0, 0),
    vadjustment_(0, 0, 0, 0),
    viewport_(hadjustment_, vadjustment_),
    whitebox_(),
    selected_tile_(0),
    paginate_(true),
    tiles_per_page_(TILES_PER_PAGE_DEFAULT)
{
    navigator_.reset(new TilePageNavigator());
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
    shared_ptr<TileData> tdata(new TileData());
    tdata->tile = &tile;
    // TODO: calculate which page a tile belongs to, based on tiles_per_page_
    // and ...
    tdata->member_page = 1;

    tiles_.push_back(tdata);

    add_tile_widget(&tile);
}

void
TileView::add_tile(Tile* tile)
{
    add_tile(*tile);
}

void
TileView::add_tile_widget(Tile* tile)
{
    tile->show();

    Gtk::Box& wb_box = whitebox_.get_root_vbox();
    wb_box.pack_start(*tile, false, false, 0);

    tile->signal_selected().connect(
        sigc::mem_fun(*this, &TileView::on_tile_selected));

    tile->signal_activated().connect(
        sigc::mem_fun(*this, &TileView::on_tile_activated));
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

void
TileView::for_each_tile(const SlotForEachTile& slot)
{
    list<shared_ptr<TileData> >::iterator it(tiles_.begin());
    list<shared_ptr<TileData> >::iterator end(tiles_.begin());

    for ( ; it != end; ++it) {
        slot(*((*it)->tile));
    }
}

void
TileView::show_page_navigator(bool show)
{
    if (show)
        navigator_->show();
    else
        navigator_->hide();
}

void
TileView::set_navigator_title(const Glib::ustring& title)
{
    navigator_->set_title(title);
}

void
TileView::set_navigator_title_markup(const Glib::ustring& marked_up_title)
{
    navigator_->set_title_markup(marked_up_title);
}

void
TileView::set_page_view(bool use_page_view)
{
    paginate_ = use_page_view;
    // TODO: perform (de)pagination
}

void
TileView::set_tiles_per_page(int tiles_per_page)
{
    if (tiles_per_page == 0) return;

    tiles_per_page = tiles_per_page;
    // TODO: perform (de)pagination
}

int
TileView::get_tiles_per_page() const
{
    return tiles_per_page_;
}

} // namespace Util

} // namespace Gtk
