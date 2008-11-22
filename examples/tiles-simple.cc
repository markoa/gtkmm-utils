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
#include "tiles-simple.h"

using std::tr1::shared_ptr;

ExampleWindow::ExampleWindow()
    :
    show_navigation_("Show navigation bar"),
    tpp_label_("Tiles per page"),
    tpp_spin_(1.0, 0)
{
    set_border_width(10);
    set_default_size(300, 300);

    add(vbox_);

    tile_view_.set_navigator_title_markup(
        "<span weight=\"bold\">Showing items</span>");
    tile_view_.set_tiles_per_page(2);
    Gtk::Util::PageNavigator& navigator = tile_view_.get_page_navigator();
    navigator.get_button_first().set_tooltip_text("First");
    navigator.get_button_previous().set_tooltip_text("Previous");
    navigator.get_button_next().set_tooltip_text("Next");
    navigator.get_button_last().set_tooltip_text("Last");

    shared_ptr<Gtk::Util::Tile> tile;

    tile.reset(new Gtk::Util::Tile("Tile", "Read my subheader", false));
    Gtk::Image& image = tile->get_image();
    image.set(Gtk::Stock::DIRECTORY, Gtk::ICON_SIZE_DIALOG);
    tiles_.push_back(tile);
    tile_view_.add_tile(*tile);

    tile.reset(new Gtk::Util::Tile("Second tile", "Eggs and bacon", true, false));
    tile->get_image().set(Gtk::Stock::CDROM, Gtk::ICON_SIZE_DIALOG);
    tiles_.push_back(tile);
    tile_view_.add_tile(*tile);

    tile.reset(new Gtk::Util::Tile("Interactive piece",
                "With a clickable button below"));
    tile->get_image().set(Gtk::Stock::NETWORK, Gtk::ICON_SIZE_DIALOG);
    Gtk::VBox& tile_vbox = tile->get_content_vbox();
    Gtk::Button& inside_button = *(Gtk::manage(new Gtk::Button("Use me")));
    inside_button.signal_clicked().connect(
            sigc::mem_fun(*this, &ExampleWindow::on_inside_button_clicked));
    tile_vbox.pack_start(inside_button, false, false, 0);
    tiles_.push_back(tile);
    tile_view_.add_tile(*tile);

    tile.reset(new Gtk::Util::Tile("Doublemoon",
                "Music that I remember", true, false));
    tile->get_image().set(Gtk::Stock::ABOUT, Gtk::ICON_SIZE_DIALOG);
    tiles_.push_back(tile);
    tile_view_.add_tile(*tile);

    tile.reset(new Gtk::Util::Tile("Sunset",
                "Oye like you're va", true, false));
    tile->get_image().set(Gtk::Stock::APPLY, Gtk::ICON_SIZE_DIALOG);
    tiles_.push_back(tile);
    tile_view_.add_tile(*tile);

    tile.reset(new Gtk::Util::Tile("The Lab",
                "Beyond the sound barrier", true, false));
    tile->get_image().set(Gtk::Stock::CLEAR, Gtk::ICON_SIZE_DIALOG);
    tiles_.push_back(tile);
    tile_view_.add_tile(*tile);

    tile.reset(new Gtk::Util::Tile("Video Zone",
                "Production and editing", true, false));
    tile->get_image().set(Gtk::Stock::MEDIA_PLAY, Gtk::ICON_SIZE_DIALOG);
    tiles_.push_back(tile);
    tile_view_.add_tile(*tile);

    vbox_.pack_start(tile_view_);

    show_navigation_.set_active(true);
    vbox_.pack_start(show_navigation_, false, false, 0);

    Gtk::Adjustment* adj = tpp_spin_.get_adjustment();
    adj->set_value(2);
    adj->set_lower(1);
    adj->set_upper(50);
    adj->set_step_increment(1);

    tpp_spin_.set_value(2.0);

    tpp_box_.pack_start(tpp_label_);
    tpp_box_.pack_start(tpp_spin_);
    vbox_.pack_start(tpp_box_, false, false, 0);

    show_all_children();

    connect_signals();
}

ExampleWindow::~ExampleWindow()
{
}

void
ExampleWindow::connect_signals()
{
    show_navigation_.signal_clicked().connect(
        sigc::mem_fun(*this, &ExampleWindow::on_show_navigation_clicked));

    tpp_spin_.signal_value_changed().connect(
        sigc::mem_fun(*this, &ExampleWindow::on_tiles_per_page_changed));

    tile_view_.signal_tile_activated().connect(
        sigc::mem_fun(*this, &ExampleWindow::on_tile_activated));
}

void
ExampleWindow::on_show_navigation_clicked()
{
    if (show_navigation_.get_active())
        tile_view_.show_page_navigator(true);
    else
        tile_view_.show_page_navigator(false);
}

void
ExampleWindow::on_tiles_per_page_changed()
{
    int count = tpp_spin_.get_value_as_int();
    tile_view_.set_tiles_per_page(count);
}

void
ExampleWindow::on_tile_activated(Gtk::Util::Tile& tile)
{
    std::cout << "Activated tile with title " << tile.get_title() << std::endl;
    g_assert(&tile == tile_view_.get_selection());
}

void
ExampleWindow::on_inside_button_clicked()
{
    std::cout << "Inside button clicked" << std::endl;
}

int
main(int argc, char** argv)
{
    Gtk::Main kit(argc, argv);

    ExampleWindow window;

    Gtk::Main::run(window);

    return 0;
}
