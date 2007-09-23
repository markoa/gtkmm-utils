/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - tile-page-navigator.cc
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

#include <gtkmm/alignment.h>
#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/stock.h>
#include "tile-page-navigator.hh"

namespace Gtk {

namespace Util {

class TilePageNavigator::Private
{
public:
    Private();
    ~Private() {}

    Gtk::Alignment align_box;
    Gtk::HBox      label_hbox;
    Gtk::Label     label;
    Gtk::Button    button_previous;
    Gtk::Image     image_previous;
    Gtk::Button    button_next;
    Gtk::Image     image_next;
};

TilePageNavigator::Private::Private()
    :
    align_box(0.0, 1.0, 1.0, 1.0),
    label_hbox(false, 0),
    label("I am the title"),
    button_previous(),
    image_previous(Gtk::Stock::GO_BACK, Gtk::ICON_SIZE_SMALL_TOOLBAR),
    button_next(),
    image_next(Gtk::Stock::GO_FORWARD, Gtk::ICON_SIZE_SMALL_TOOLBAR)
{
    align_box.set_padding(18, 3, 0, 0);
    
    align_box.add(label_hbox);
    label_hbox.pack_start(label, false, true, 0);
    label.set_justify(Gtk::JUSTIFY_LEFT);
    
    button_next.set_relief(Gtk::RELIEF_NONE);
    button_next.add(image_next);
    
    button_previous.set_relief(Gtk::RELIEF_NONE);
    button_previous.add(image_previous);
}

TilePageNavigator::TilePageNavigator()
{
    priv_.reset(new Private());

    pack_start(priv_->align_box, false, true, 0);
    pack_end(priv_->button_next, false, true, 0);
    pack_end(priv_->button_previous, false, true, 0);
    
    show_all();
}

TilePageNavigator::~TilePageNavigator()
{
}

} // namespace Util

} // namespace Gtk
