/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - tile-surface.cc
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

#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/object.h>
#include "tile-surface.hh"

namespace Gtk {

namespace Util {

TileSurface::TileSurface()
    :
    hbox_(0),
    image_(0)
{
    // Event-trapping window of the eventbox is above
    // the window of the child widget:
    set_above_child(true);

    // The application will paint directly on the widget:
    set_app_paintable(true);

    // We need to be able to handle key_press events:
    set_flags(Gtk::CAN_FOCUS);

    // Construct child widgets:
    hbox_ = Gtk::manage(new Gtk::HBox());
    hbox_->set_border_width(2);
    hbox_->show();

    image_ = Gtk::manage(new Gtk::Image());
    image_->show();
    hbox_->pack_start(*image_, false, false, 0);

    add(*hbox_);
}

TileSurface::~TileSurface()
{
}

void
TileSurface::on_size_request(Gtk::Requisition* requisition)
{
    int req_width, req_height;
    int pad = 0;
    int focus_line_width, focus_padding;

    // Ask our child for its desired size:
    hbox_->get_size_request(req_width, req_height);

    this->get_style_property<int>("focus-line-width", focus_line_width);
    this->get_style_property<int>("focus-padding", focus_padding);

    pad = focus_line_width + focus_padding + 1;

    Glib::RefPtr<Gtk::Style> style = get_style();

    requisition->width = req_width + 2 * (pad + style->get_xthickness());
    requisition->height = req_height + 2 * (pad + style->get_ythickness());
}

void
TileSurface::on_size_allocate(Gtk::Allocation& allocation)
{
    int pad = 0;
    int focus_line_width, focus_padding;

    this->get_style_property<int>("focus-line-width", focus_line_width);
    this->get_style_property<int>("focus-padding", focus_padding);

    pad = focus_line_width + focus_padding + 1;

    int alloc_x, alloc_y, alloc_width, alloc_height;
    
    alloc_x = allocation.get_x();
    alloc_y = allocation.get_y();
    alloc_width = allocation.get_width();
    alloc_height = allocation.get_height();

    Glib::RefPtr<Gtk::Style> style = get_style();

    allocation.set_x(alloc_x + pad + style->get_xthickness());
    allocation.set_y(alloc_y + pad + style->get_ythickness());
    allocation.set_width(alloc_width - (pad + style->get_xthickness()));
    allocation.set_height(alloc_height - (pad + style->get_ythickness()));

    Gtk::EventBox::on_size_allocate(allocation);
}

bool
TileSurface::on_expose_event(GdkEventExpose* event)
{
    Glib::RefPtr<Gdk::Window> window = this->get_window();
    Glib::RefPtr<Gdk::GC> gc = get_style()->get_base_gc(this->get_state());

    window->draw_rectangle(gc,
                           true /* fill */,
                           event->area.x, event->area.y,
                           event->area.width, event->area.height);

    if (Gtk::EventBox::on_expose_event(event))
        return true;

    if (this->get_flags() & Gtk::HAS_FOCUS)
    {
        int focus_pad, x, y, width, height;
        Gdk::Rectangle alloc = this->get_allocation();

        this->get_style_property<int>("focus_padding", focus_pad);

        Glib::RefPtr<Gtk::Style> style = get_style();

        x = focus_pad + style->get_xthickness();
        y = focus_pad + style->get_ythickness();

        width =
            alloc.get_width() - 2 * (focus_pad + style->get_xthickness());

        height =
            alloc.get_height() - 2 * (focus_pad + style->get_ythickness());

        style->paint_focus(window,
                           this->get_state(),
                           Gdk::Rectangle(&(event->area)),
                           *this,
                           "TileSurface",
                           x, y,
                           width, height);
    }

    return false;
}

bool
TileSurface::on_button_press_event(GdkEventButton* event)
{
    grab_focus();
    return Gtk::EventBox::on_button_press_event(event);
}

bool
TileSurface::on_focus_in_event(GdkEventFocus* event)
{
    signal_tile_selected_.emit();
    return Gtk::EventBox::on_focus_in_event(event);
}

} // namespace Util

} // namespace Gtk
