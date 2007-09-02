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

#include "gtkmm-utils/tile-template.hh"
#include "tiles-simple.hh"

ExampleWindow::ExampleWindow()
{
    set_border_width(10);

    Gtk::Util::TileTemplate* tile1 =
        Gtk::manage(new Gtk::Util::TileTemplate(
                        "Tile One",
                        "A very useful widget for everyone"));
    vbox.pack_start(*tile1);

    add(vbox);

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
