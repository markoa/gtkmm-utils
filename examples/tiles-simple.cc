/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils example - tile-simple.cc
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

#include <iostream>
#include "tiles-simple.hh"

using std::tr1::shared_ptr;

ExampleWindow::ExampleWindow()
{
    set_border_width(10);
    set_default_size(300, 200);

    add(vbox_);

    tile_view_.signal_tile_activated().connect(
        sigc::mem_fun(*this, &ExampleWindow::on_tile_activated));

    tile_view_.set_navigator_title_markup(
        "<span weight=\"bold\">Showing tiles</span>");
    tile_view_.set_tiles_per_page(2);

    shared_ptr<Gtk::Util::Tile> tile1(
        new Gtk::Util::Tile("Tile", "Read my subheader", false));
    Gtk::Image& image = tile1->get_image();
    image.set(Gtk::Stock::DIRECTORY, Gtk::ICON_SIZE_DIALOG);

    shared_ptr<Gtk::Util::Tile> tile2(
        new Gtk::Util::Tile("Second tile", "Eggs and bacon"));
    tile2->get_image().set(Gtk::Stock::CDROM, Gtk::ICON_SIZE_DIALOG);

    shared_ptr<Gtk::Util::Tile> tile3(
        new Gtk::Util::Tile("Interactive piece",
                            "With a clickable button below"));
    tile3->get_image().set(Gtk::Stock::NETWORK, Gtk::ICON_SIZE_DIALOG);
    Gtk::VBox& tile3_vbox = tile3->get_content_vbox();
    tile3_vbox.pack_start(*(Gtk::manage(new Gtk::Button("Use me"))),
                          false, false, 0);


    tiles_.push_back(tile1);
    tiles_.push_back(tile2);
    tiles_.push_back(tile3);

    tile_view_.add_tile(*tile1);
    tile_view_.add_tile(*tile2);
    tile_view_.add_tile(*tile3);

    vbox_.pack_start(tile_view_);

    show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void
ExampleWindow::on_tile_activated(Gtk::Util::Tile& tile)
{
    std::cout << "Activated tile with title " << tile.get_title() << std::endl;
    g_assert(&tile == tile_view_.get_selection());
}

int
main(int argc, char** argv)
{
    Gtk::Main kit(argc, argv);

    ExampleWindow window;

    Gtk::Main::run(window);

    return 0;
}
