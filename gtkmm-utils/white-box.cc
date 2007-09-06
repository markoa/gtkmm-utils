/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - white-box.cc
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

#include "white-box.hh"

namespace Gtk {

namespace Util {

WhiteBox::WhiteBox()
    :
    root_vbox_()
{
    root_vbox_.set_border_width(5);
    root_vbox_.show_all();
    add(root_vbox_);
}

WhiteBox::~WhiteBox()
{
}

Gtk::VBox&
WhiteBox::get_root_vbox()
{
    return root_vbox_;
}

bool
WhiteBox::on_expose_event(GdkEventExpose* event)
{
    if (! this->is_visible())
        return false;

    GdkWindow* event_window = event->window;

    if (gdk_window_get_window_type(event_window) == GDK_WINDOW_CHILD)
    {
        Glib::RefPtr<Gdk::Window> window = this->get_window();
        Glib::RefPtr<Gdk::GC> gc =
            this->get_style()->get_base_gc(this->get_state());

        window->draw_rectangle(gc,
                               true, // fill
                               event->area.x, event->area.y,
                               event->area.width, event->area.height);
    }

    Gtk::Widget* child_widget = this->get_child(); // Gtk::Bin
    if (child_widget)
        propagate_expose(*child_widget, event);

    return false;
}

} // namespace Util

} // namespace Gtk
