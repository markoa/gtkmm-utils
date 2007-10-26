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

#include <gdk/gdkkeysyms.h>
#include "glibmm-utils/ustring.h"
#include "tile-view.h"

namespace Gtk {

namespace Util {

using std::auto_ptr;
using std::list;
using std::tr1::shared_ptr;

/* TileData */

class TileData
{
public:
    TileData() : tile(0), page(1), plugged_in(false) {}
    ~TileData() {}

    Tile* tile;
    int   page;
    int   position;   // position (index) in page
    bool  plugged_in; // whether we've already connected to its' signals
};

typedef list<shared_ptr<TileData> >::iterator tile_data_iter;

/* TileView::Private */

class TileView::Private
{
public:
    explicit Private(bool use_page_view);
    ~Private() {}

    void connect_signals();

    void add_tile(shared_ptr<TileData> td);
    void add_tile_widget(shared_ptr<TileData> tile);

    TileData* find_tile_data(Tile* ptile);
    void      for_each_tile(const SlotForEachTile& slot);

    void set_page_view(bool use_page_view);
    void set_tiles_per_page(int tiles_per_page);

    void update_tile_data();
    void reload_container();

    void show_page_navigator(bool show);
    void update_navigator_page_info_label();

    int get_page_count() const;
    int get_last_tile_pos() const;

    // Tile signal handlers
    void on_tile_focus_in(Tile& tile);
    void on_tile_activated(Tile& tile);

    // TilePageNavigator signal handlers
    void on_show_next_page();
    void on_show_previous_page();

    // Child widgets
    auto_ptr<PageNavigator> navigator_;

    Gtk::ScrolledWindow scrolled_window_;
    Gtk::Adjustment     hadjustment_;
    Gtk::Adjustment     vadjustment_;
    Gtk::Viewport       viewport_;
    WhiteBox            whitebox_;

    // Tile content internals
    std::list<shared_ptr<TileData> > tiles_;
    TileData* selected_tile_;

    bool paginate_;
    int  tiles_per_page_;
    int  current_page_;

    // zero-based, the index of the next-inserted tile in the TV;
    // helps as an indicator we check against for (dis)allowing moving up
    // and down in the view.
    int  next_tile_position_;

    // Signals
    SignalTileActivated signal_tile_activated_;
    sigc::signal<void>  signal_show_request_;
};

TileView::Private::Private(bool use_page_view)
    :
    scrolled_window_(),
    hadjustment_(0, 0, 0, 0),
    vadjustment_(0, 0, 0, 0),
    viewport_(hadjustment_, vadjustment_),
    whitebox_(),
    selected_tile_(0),
    paginate_(use_page_view),
    tiles_per_page_(TILES_PER_PAGE_DEFAULT),
    current_page_(1),
    next_tile_position_(0)
{
    navigator_.reset(new PageNavigator());

    scrolled_window_.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled_window_.set_shadow_type(Gtk::SHADOW_IN);

    viewport_.set_resize_mode(Gtk::RESIZE_PARENT);
    viewport_.set_shadow_type(Gtk::SHADOW_IN);
    scrolled_window_.add(viewport_);
    viewport_.show();

    viewport_.add(whitebox_);

    connect_signals();
}

void
TileView::Private::connect_signals()
{
    navigator_->signal_next().connect(
        sigc::mem_fun(*this, &TileView::Private::on_show_next_page));

    navigator_->signal_previous().connect(
        sigc::mem_fun(*this, &TileView::Private::on_show_previous_page));
}

// Registers the tile data in our internal data structure, determines
// the page it belongs to. The "high-level private add_tile function".
void
TileView::Private::add_tile(shared_ptr<TileData> tdata)
{
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
        add_tile_widget(tdata);

    tdata->position = next_tile_position_++;
    if (next_tile_position_ == tiles_per_page_) next_tile_position_ = 0;

    update_navigator_page_info_label();
}

// Packs a tile via TileData in the WhiteBox.
void
TileView::Private::add_tile_widget(shared_ptr<TileData> tdata)
{
    Tile* tile = tdata->tile;
    Gtk::Box& wb_box = whitebox_.get_root_vbox();
    wb_box.pack_start(*tile, false, false, 0);

    if (! tdata->plugged_in) { // don't connect multiple times
        tile->signal_focus_in().connect(
            sigc::mem_fun(*this, &TileView::Private::on_tile_focus_in));

        tile->signal_activated().connect(
            sigc::mem_fun(*this, &TileView::Private::on_tile_activated));

        tdata->plugged_in = true;
    }

    signal_show_request_.emit();
}

TileData*
TileView::Private::find_tile_data(Tile* ptile)
{
    tile_data_iter it(tiles_.begin());
    tile_data_iter end(tiles_.end());

    for ( ; it != end; ++it)
        if ((*it)->tile == ptile)
            return it->get();

    return 0;
}

void
TileView::Private::on_tile_focus_in(Tile& tile)
{
    if (selected_tile_ && (selected_tile_->tile == &tile)) return;

    if (selected_tile_) { // is 0 before anything is selected
        selected_tile_->tile->signal_unselected().emit(*(selected_tile_->tile));
        selected_tile_->tile->on_unselected();
    }

    tile.signal_selected().emit(tile);
    tile.on_selected();

    selected_tile_ = find_tile_data(&tile);
}

void
TileView::Private::on_tile_activated(Tile& tile)
{
    signal_tile_activated_.emit(tile);
}

void
TileView::Private::for_each_tile(const SlotForEachTile& slot)
{
    tile_data_iter it(tiles_.begin());
    tile_data_iter end(tiles_.end());

    for ( ; it != end; ++it) {
        slot(*((*it)->tile));
    }
}

void
TileView::Private::set_page_view(bool use_page_view)
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
TileView::Private::set_tiles_per_page(int tiles_per_page)
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

void
TileView::Private::update_tile_data()
{
    if (tiles_.empty()) return;

    tile_data_iter it(tiles_.begin());
    tile_data_iter end(tiles_.end());

    next_tile_position_ = 0;

    if (! paginate_) {
        for ( ; it != end; ++it) {
            (*it)->page = 1;
            (*it)->position = next_tile_position_++;
        }
        return;
    }

    int counter = 0;
    int page = 1;

    for ( ; it != end; ++it) {
        (*it)->page = page;
        (*it)->position = next_tile_position_++;

        if (++counter == tiles_per_page_) {
            counter = 0;
            ++page;
            next_tile_position_ = 0;
        }
    }
}

void
TileView::Private::reload_container()
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
        add_tile_widget(*td_iter);
        ++td_iter;
    }
}

void
TileView::Private::show_page_navigator(bool show)
{
    if (show)
        navigator_->show();
    else
        navigator_->hide();
}

void
TileView::Private::update_navigator_page_info_label()
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
TileView::Private::on_show_next_page()
{
    if (! paginate_) return;

    if ((current_page_ + 1) > get_page_count()) return;

    ++current_page_;
    reload_container();
    update_navigator_page_info_label();
}

void
TileView::Private::on_show_previous_page()
{
    if ((! paginate_) || (current_page_ == 1)) return;

    --current_page_;
    reload_container();
    update_navigator_page_info_label();
}

int
TileView::Private::get_page_count() const
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

// Returns the index of last tile on current page.
int
TileView::Private::get_last_tile_pos() const
{
    if ((static_cast<int>(tiles_.size()) -
         (current_page_ * tiles_per_page_)) < 0) {
        // last page, less then maximum number of tiles present
        return ((tiles_.size() - (current_page_ - 1) * tiles_per_page_) - 1);
    }
    else
        return (tiles_per_page_ - 1);
}

/* TileView */

TileView::TileView(bool use_page_view)
{
    priv_.reset(new Private(use_page_view));

    pack_start(*(priv_->navigator_), false, true, 0);
    pack_start(priv_->scrolled_window_, true, true, 0);

    priv_->signal_show_request_.connect(
        sigc::mem_fun(*this, &TileView::on_show_request));

    show_all();
}

TileView::~TileView()
{
}

void
TileView::add_tile(Tile& tile)
{
    shared_ptr<TileData> tdata(new TileData());
    tdata->tile = &tile;
    priv_->add_tile(tdata);
}

void
TileView::add_tile(Tile* tile)
{
    // We cannot write add_tile(*tile), because if this is a subclass,
    // then the overriden method will be called and it will invoke the
    // base class method again (most probably, if it calls it),
    // and so on in an infinite loop.

    shared_ptr<TileData> tdata(new TileData());
    tdata->tile = tile;
    priv_->add_tile(tdata);
}

Tile*
TileView::get_selection()
{
    return priv_->selected_tile_->tile;
}

TileView::SignalTileActivated&
TileView::signal_tile_activated()
{
    return priv_->signal_tile_activated_;
}

void
TileView::for_each_tile(const SlotForEachTile& slot)
{
    priv_->for_each_tile(slot);
}

void
TileView::show_page_navigator(bool show)
{
    priv_->show_page_navigator(show);
}

void
TileView::set_navigator_title(const Glib::ustring& title)
{
    priv_->navigator_->set_title(title);
}

void
TileView::set_navigator_title_markup(const Glib::ustring& marked_up_title)
{
    priv_->navigator_->set_title_markup(marked_up_title);
}

void
TileView::set_page_view(bool use_page_view)
{
    priv_->set_page_view(use_page_view);
}

void
TileView::set_tiles_per_page(int tiles_per_page)
{
    priv_->set_tiles_per_page(tiles_per_page);
}

int
TileView::get_tiles_per_page() const
{
    return priv_->tiles_per_page_;
}

void
TileView::on_show_request()
{
    show_all();
}

bool
TileView::on_key_press_event(GdkEventKey* event)
{
    if ((event->keyval == GDK_Up) && (priv_->selected_tile_->position == 0))
        return true;
    else if ((event->keyval == GDK_Down) &&
             (priv_->selected_tile_) &&
             (priv_->selected_tile_->position == priv_->get_last_tile_pos()))
        return true;

    return false;
}

} // namespace Util

} // namespace Gtk
