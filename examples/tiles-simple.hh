/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils example - tile-simple.hh
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

#include <list>
#include <tr1/memory>
#include <gtkmm.h>
#include "gtkmm-utils/tile.hh"
#include "gtkmm-utils/tile-view.hh"

class ExampleWindow : public Gtk::Window
{
public:
    ExampleWindow();
    virtual ~ExampleWindow();

protected:
    void connect_signals();

    // Widget signal handlers
    void on_show_navigation_clicked();
    void on_tiles_per_page_changed();
    void on_tile_activated(Gtk::Util::Tile& tile);

    Gtk::VBox vbox_;
    Gtk::Util::TileView tile_view_;
    std::list<std::tr1::shared_ptr<Gtk::Util::Tile> > tiles_;

    Gtk::CheckButton show_navigation_;
    // tpp = tiles per page
    Gtk::HBox       tpp_box_;
    Gtk::Label      tpp_label_;
    Gtk::SpinButton tpp_spin_;
};
