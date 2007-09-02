/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - tile-template.cc
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
#include "tile-template.hh"

namespace Gtk
{

namespace Util
{

TileTemplate::TileTemplate()
{
    init_widgets();
}

TileTemplate::TileTemplate(const Glib::ustring& title,
                           const Glib::ustring& summary)
    :
    title_(title),
    summary_(summary)
{
    init_widgets();
}

TileTemplate::~TileTemplate()
{
}

void
TileTemplate::init_widgets()
{
    alignment_ = Gtk::manage(new Gtk::Alignment(0.0, 0.5, 1.0, 0.0));

    Gtk::HBox* root_hbox = this->get_root_hbox();
    root_hbox->pack_start(*alignment_, true, true, 0);
}

Gtk::VBox*
TileTemplate::get_content_vbox()
{
    return content_vbox_;
}

void
TileTemplate::set_title(const Glib::ustring& title)
{
    title_ = title;
}

Glib::ustring
TileTemplate::get_title() const
{
    return title_;
}

void
TileTemplate::set_summary(const Glib::ustring& summary)
{
    summary_ = summary;
}

Glib::ustring
TileTemplate::get_summary() const
{
    return summary_;
}

void
TileTemplate::on_realize()
{
}

} // namespace Util

} // namespace Gtk
