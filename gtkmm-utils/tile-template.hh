/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - tile-template.hh
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

#ifndef __GTKMM_UTILS_TILE_TEMPLATE_H__
#define __GTKMM_UTILS_TILE_TEMPLATE_H__

#include <gtkmm/alignment.h>
#include <gtkmm/box.h>
#include "tile-surface.hh"

namespace Gtk {

namespace Util {

class TileTemplate : public TileSurface
{
public:
    explicit TileTemplate();
    explicit TileTemplate(const Glib::ustring& title,
                          const Glib::ustring& summary);
    virtual ~TileTemplate();

    virtual Gtk::VBox* get_content_vbox();

    virtual void set_title(const Glib::ustring& title);
    virtual Glib::ustring get_title() const;

    virtual void set_summary(const Glib::ustring& summary);
    virtual Glib::ustring get_summary() const;

protected:
    void init_widgets();

    virtual void update_title();
    virtual void update_summary();

    // Gtk::Widget overrides
    virtual void on_realize();

    Gtk::Alignment* alignment_;
    Gtk::VBox* content_vbox_;
    Gtk::Label* title_label_;
    Gtk::Label* summary_label_;

    Glib::ustring title_;
    Glib::ustring summary_;
};

} // namespace Util

} // namespace Gtk

#endif // __GTKMM_UTILS_TILE_TEMPLATE_H__
