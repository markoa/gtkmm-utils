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

#include "glibmm-utils/ustring.hh"
#include "tile-view.hh"

namespace Gtk {

namespace Util {

using std::list;
using std::tr1::shared_ptr;

/* TileView::TileData */

class TileView::TileData
{
public:
    TileData() : tile(0), page(1) {}
    ~TileData() {}

    Tile* tile;
    int   page;
};

typedef list<shared_ptr<TileView::TileData> >::iterator tile_data_iter;

/* TileView */

TileView::TileView(bool use_page_view)
    :
    scrolled_window_(),
    hadjustment_(0, 0, 0, 0),
    vadjustment_(0, 0, 0, 0),
    viewport_(hadjustment_, vadjustment_),
    whitebox_(),
    selected_tile_(0),
    paginate_(use_page_view),
    tiles_per_page_(TILES_PER_PAGE_DEFAULT),
    current_page_(1)
{
    navigator_.reset(new PageNavigator());
    pack_start(*navigator_, false, true, 0);

    scrolled_window_.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled_window_.set_shadow_type(Gtk::SHADOW_IN);
    pack_start(scrolled_window_, true, true, 0);

    viewport_.set_resize_mode(Gtk::RESIZE_PARENT);
    viewport_.set_shadow_type(Gtk::SHADOW_IN);
    scrolled_window_.add(viewport_);
    viewport_.show();

    viewport_.add(whitebox_);

    connect_signals();
}

TileView::~TileView()
{
}

void
TileView::connect_signals()
{
    navigator_->signal_clicked_next().connect(
        sigc::mem_fun(*this, &TileView::on_show_next_page));

    navigator_->signal_clicked_previous().connect(
        sigc::mem_fun(*this, &TileView::on_show_previous_page));
}

void
TileView::add_tile(Tile& tile)
{
    shared_ptr<TileData> tdata(new TileData());
    tdata->tile = &tile;
    tiles_.push_back(tdata);

    int tile_count = tiles_.size();

    if (paginate_) {
        tdata->page = tile_count / tiles_per_page_;

        int modulo = tile_count % tiles_per_page_;
        if (modulo > 0)
            tdata->page++;
    }
    else
        tdata->page = 1;

    if (tdata->page == current_page_)
        add_tile_widget(&tile);

    update_navigator_page_info_label();
}

void
TileView::add_tile(Tile* tile)
{
    add_tile(*tile);
}

void
TileView::add_tile_widget(Tile* tile)
{
    Gtk::Box& wb_box = whitebox_.get_root_vbox();
    wb_box.pack_start(*tile, false, false, 0);

    tile->signal_selected().connect(
        sigc::mem_fun(*this, &TileView::on_tile_selected));

    tile->signal_activated().connect(
        sigc::mem_fun(*this, &TileView::on_tile_activated));

    show_all();
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
    tile_data_iter it(tiles_.begin());
    tile_data_iter end(tiles_.end());

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

    if (! paginate_) current_page_ = 1;

    update_tile_data();
    reload_container();

    if (! paginate_)
        show_page_navigator(false);
    else
        update_navigator_page_info_label();
}

void
TileView::set_tiles_per_page(int tiles_per_page)
{
    if (tiles_per_page <= 0) return;

    tiles_per_page_ = tiles_per_page;

    if (tiles_per_page_ * current_page_ > static_cast<int>(tiles_.size())) {
        // In case when the current page number wouldn't exist under new
        // tiles_per_page_ (increased) value, just go back to the first page.
        current_page_ = 1;
    }

    update_tile_data();
    reload_container();
    update_navigator_page_info_label();
}

int
TileView::get_tiles_per_page() const
{
    return tiles_per_page_;
}

void
TileView::update_tile_data()
{
    if (tiles_.empty()) return;

    tile_data_iter it(tiles_.begin());
    tile_data_iter end(tiles_.end());

    if (! paginate_) {
        for ( ; it != end; ++it)
            (*it)->page = 1;
        return;
    }

    int counter = 0;
    int page = 1;

    for ( ; it != end; ++it) {
        (*it)->page = page;

        if (++counter == tiles_per_page_) {
            counter = 0;
            ++page;
        }
    }
}

void
TileView::reload_container()
{
    if (tiles_.empty()) return;

    // Remove all currently shown tiles
    list<Gtk::Widget*> children = whitebox_.get_root_vbox().get_children();

    list<Gtk::Widget*>::iterator child_it(children.begin());
    list<Gtk::Widget*>::iterator child_end(children.end());

    for ( ; child_it != child_end; ++child_it)
        whitebox_.get_root_vbox().remove(*(*child_it));

    // Show the tiles which belong to the currently requested page
    tile_data_iter td_iter(tiles_.begin());
    tile_data_iter td_end(tiles_.end());

    while (td_iter != td_end && (*td_iter)->page < current_page_)
        ++td_iter;

    while (td_iter != td_end && (*td_iter)->page == current_page_) {
        add_tile_widget((*td_iter)->tile);
        ++td_iter;
    }
}

void
TileView::update_navigator_page_info_label()
{
    int show_start = (current_page_ - 1) * tiles_per_page_ + 1;
    int show_end = 0;

    // get the number of tiles in the current page
    tile_data_iter td_iter(tiles_.begin());
    tile_data_iter td_end(tiles_.end());

    int tiles_in_page = 0;
    for ( ; td_iter != td_end; ++td_iter)
        if ((*td_iter)->page == current_page_) ++tiles_in_page; 
    
    show_end = show_start + tiles_in_page - 1;

    navigator_->set_page_info(
        Glib::Util::uprintf("%d - %d of %d",
                            show_start,
                            show_end,
                            static_cast<int>(tiles_.size())));
}

void
TileView::on_show_next_page()
{
    if (! paginate_) return;

    if ((current_page_ + 1) > get_page_count()) return;

    ++current_page_;
    reload_container();
    update_navigator_page_info_label();
}

void
TileView::on_show_previous_page()
{
    if ((! paginate_) || (current_page_ == 1)) return;

    --current_page_;
    reload_container();
    update_navigator_page_info_label();
}

int
TileView::get_page_count() const
{
    int page_count = 1;

    if (! paginate_) return page_count;

    int tile_count = tiles_.size();
    page_count = tile_count / tiles_per_page_;

    int modulo = tile_count % tiles_per_page_;
    if (modulo > 0)
        ++page_count;

    return page_count;
}

} // namespace Util

} // namespace Gtk
