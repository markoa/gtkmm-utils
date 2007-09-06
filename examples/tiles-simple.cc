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

//#include "gtkmm-utils/tile-template.hh"
#include "gtkmm-utils/tile-view.hh"
#include "tiles-simple.hh"

ExampleWindow::ExampleWindow()
{
    set_border_width(10);
    set_default_size(300, 200);

/*
    Gtk::Util::TileTemplate* tile1 =
        Gtk::manage(new Gtk::Util::TileTemplate(
                        "Tile One",
                        "A very useful widget for everyone"));
    Gtk::Image& image = tile1->get_image();
    image.set(Gtk::Stock::DIRECTORY, Gtk::ICON_SIZE_DIALOG);
    vbox.pack_start(*tile1);
*/

    add(vbox);

    Gtk::Util::TileView* tv = Gtk::manage(new Gtk::Util::TileView());

    Gtk::Util::Tile* tile1 = Gtk::manage(
        new Gtk::Util::Tile("Tile", "Read my subheader", false));
    Gtk::Image& image = tile1->get_image();
    image.set(Gtk::Stock::DIRECTORY, Gtk::ICON_SIZE_DIALOG);

    Gtk::Util::Tile* tile2 = Gtk::manage(
        new Gtk::Util::Tile("Second tile", "Eggs and bacon"));
    tile2->get_image().set(Gtk::Stock::CDROM, Gtk::ICON_SIZE_DIALOG);

    Gtk::Util::Tile* tile3 = Gtk::manage(
        new Gtk::Util::Tile("Interactive piece", "A clickable button below"));
    tile3->get_image().set(Gtk::Stock::NETWORK, Gtk::ICON_SIZE_DIALOG);
    Gtk::VBox& tile3_vbox = tile3->get_content_vbox();
    tile3_vbox.pack_start(* (Gtk::manage(new Gtk::Button("Use me"))), false, false, 0);

    tv->add_tile(*tile1);
    tv->add_tile(*tile2);
    tv->add_tile(*tile3);

    vbox.pack_start(*tv);

    show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

int
main(int argc, char** argv)
{
    Gtk::Main kit(argc, argv);

    ExampleWindow window;

    Gtk::Main::run(window);

    return 0;
}
