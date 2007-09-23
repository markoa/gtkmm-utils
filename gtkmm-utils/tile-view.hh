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
#include <gtkmm/adjustment.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/viewport.h>
#include "tile.hh"
#include "tile-page-navigator.hh"
#include "white-box.hh"

namespace Gtk {

namespace Util {

/**
 * The Tile container.
 */
class TileView : public Gtk::VBox
{
public:
    typedef std::list<Tile*>::iterator       iterator;
    typedef std::list<Tile*>::const_iterator const_iterator;

    /**
     * \brief Signal emmitted when user double-clicks, or pressed the Return
     * key on a Tile in the container.
     *
     * The signal passes a reference to the Tile that has been activated.
     */
    typedef sigc::signal<void, Tile&> SignalTileActivated;

    /**
     * \brief Constructs a new TileView.
     */
    explicit TileView();
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
     * \brief Returns an iterator to the first Tile in the container.
     * Use it for traversing all packed Tiles.
     *
     * \return a Tile iterator.
     */
    virtual iterator       begin();

    /**
     * \brief Returns an iterator to the first Tile in the container.
     * Use it for traversing all packed Tiles.
     *
     * \return a Tile const iterator.
     */
    virtual const_iterator begin() const;

    /**
     * \brief Returns an iterator to the last Tile in the container.
     * Use it for traversing all packed Tiles.
     *
     * \return a Tile iterator.
     */
    virtual iterator       end();

    /**
     * \brief Returns an iterator to the last Tile in the container.
     * Use it for traversing all packed Tiles.
     *
     * \return a Tile const iterator.
     */
    virtual const_iterator end() const;

    /**
     * \brief Returns the last selected Tile.
     *
     * \return a pointer to Tile.
     */
    virtual Tile* get_selection();

    /**
     * \brief Returns the SignalActivated, which you can connect to.
     *
     * \return a reference to the TileView's SignalActivated.
     */
    SignalTileActivated& signal_tile_activated();

protected:
    // Tile signal handlers
    void on_tile_selected(Tile& tile);
    void on_tile_activated(Tile& tile);

    // Child widgets
    int   tiles_per_page_;
    std::auto_ptr<TilePageNavigator> navigator_;

    Gtk::ScrolledWindow scrolled_window_;
    Gtk::Adjustment     hadjustment_;
    Gtk::Adjustment     vadjustment_;
    Gtk::Viewport       viewport_;
    WhiteBox            whitebox_;

    // Tile content internals
    std::list<Tile*> tiles_;
    Tile* selected_tile_;

    // Signals
    SignalTileActivated signal_tile_activated_;

private:
    // Non-copyable
    TileView(const TileView&);
    TileView& operator=(const TileView&);
};

} // namespace Util

} // namespace Gtk

#endif // __GTKMM_UTILS_TILE_VIEW_H__
