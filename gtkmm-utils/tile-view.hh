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

#include <list>
#include <memory>
#include <tr1/memory>
#include <gtkmm/adjustment.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/viewport.h>
#include "tile.hh"
#include "page-navigator.hh"
#include "white-box.hh"

namespace Gtk {

namespace Util {

const int TILES_PER_PAGE_DEFAULT = 20;

/**
 * The Tile container.
 */
class TileView : public Gtk::VBox
{
public:
    /**
     * \brief Signal emmitted when user double-clicks, or pressed the Return
     * key on a Tile in the container.
     *
     * The signal passes a reference to the Tile that has been activated.
     */
    typedef sigc::signal<void, Tile&> SignalTileActivated;

    /**
     * \brief Slot used to iterate over child Tile widgets.
     *
     * \see for_each_tile()
     */
    typedef sigc::slot<void, Tile&> SlotForEachTile;

    /**
     * \brief Constructs a new TileView.
     *
     * \param use_page_view  when <tt>true</tt>, indicates that tiles should be
     * separated into pages; when <tt>false</tt>, all tiles will be displayed
     * at once.
     */
    explicit TileView(bool use_page_view = true);

    /**
     * TileView destructor.
     */
    virtual ~TileView();

    /**
     * \brief Adds and shows a Tile in the container.
     *
     * \param tile a Tile reference
     */
    virtual void add_tile(Tile& tile);

    /**
     * \brief Adds and shows a Tile in the container.
     *
     * \param tile a Tile pointer
     */
    virtual void add_tile(Tile* tile);

    /**
     * \brief Returns the last selected Tile.
     *
     * \return a pointer to Tile.
     */
    virtual Tile* get_selection();

    /**
     * \brief Calls a supplied function for each child Tile.
     *
     * \param slot  user function to call
     */
    virtual void for_each_tile(const SlotForEachTile& slot);

    /**
     * \brief Shows or hides a TilePageNavigator above the content.
     *
     * \param show  indicates whether to show or hide the navigation bar
     */
    virtual void show_page_navigator(bool show = true);

    /**
     * \brief Sets a custom title in the TilePageNavigator above the content.
     *
     * \param title  a string
     */
    virtual void set_navigator_title(const Glib::ustring& title);

    /**
     * \brief Sets a custom markup on the title in the TilePageNavigator
     * above the content.
     *
     * \param marked_up_title  escaped markup string; escape strings with
     * Glib::Markup::escape_text()
     */
    virtual void set_navigator_title_markup(const Glib::ustring& marked_up_title);

    /**
     * \brief Sets the display style.
     *
     * \param use_page_view  when <tt>true</tt>, indicates that tiles should be
     * separated into pages; when <tt>false</tt>, all tiles will be displayed
     * at once
     */
    virtual void set_page_view(bool use_page_view = true);

    /**
     * \brief Sets the number of tiles displayed in one page.
     *
     * \param tiles_per_page  a new number of tiles to be displayed in one page
     */
    virtual void set_tiles_per_page(int tiles_per_page);

    /**
     * \brief Gets the current number of tiles displayed in one page.
     *
     * \return  the number of tiles displayed in one page
     */
    virtual int  get_tiles_per_page() const;

    /**
     * \brief Returns the SignalActivated, which you can connect to.
     *
     * \return a reference to the TileView's SignalActivated.
     */
    SignalTileActivated& signal_tile_activated();

protected:
    struct Private;
    std::auto_ptr<Private> priv_;

    void on_show_request();

private:
    // Non-copyable
    TileView(const TileView&);
    TileView& operator=(const TileView&);
};

} // namespace Util

} // namespace Gtk

#endif // __GTKMM_UTILS_TILE_VIEW_H__
