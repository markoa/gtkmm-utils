/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - tile.cc
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

#include "tile.hh"

namespace Gtk {

namespace Util {

Tile::Tile(const Glib::ustring& title,
           const Glib::ustring& summary,
           bool paint_white)
    :
    root_hbox_(),
    image_(),
    content_vbox_(),
    title_label_(),
    summary_label_(),
    title_(title),
    summary_(summary),
    paint_white_(paint_white)
{
    set_flags(Gtk::CAN_FOCUS);

    // set up root hbox
    root_hbox_.set_border_width(5);
    root_hbox_.set_spacing(2);
    add(root_hbox_);

    // pack illustration image
    image_.show();
    root_hbox_.pack_start(image_, false, false, 0);

    // prepare vbox to appear on the right hand side of the image
    content_vbox_.set_border_width(5);
    content_vbox_.set_spacing(2);

    // set up the title label
    title_label_.set_markup("<span weight=\"bold\">" +
                            Glib::Markup::escape_text(title_) +
                            "</span>");
    title_label_.set_ellipsize(Pango::ELLIPSIZE_END);
    title_label_.set_max_width_chars(30);
    title_label_.modify_fg(Gtk::STATE_NORMAL,
                           this->get_style()->get_fg(Gtk::STATE_INSENSITIVE));
    content_vbox_.pack_start(title_label_, false, false, 0);

    // set up the summary label
    summary_label_.set_markup("<small>" +
                              Glib::Markup::escape_text(summary_) +
                              "</small>");
    summary_label_.set_ellipsize(Pango::ELLIPSIZE_END);
    summary_label_.set_max_width_chars(30);
    summary_label_.modify_fg(Gtk::STATE_NORMAL,
                             this->get_style()->get_fg(Gtk::STATE_INSENSITIVE));
    content_vbox_.pack_start(summary_label_, false, false, 0);

    // wrap up
    content_vbox_.show_all();
    root_hbox_.pack_start(content_vbox_);
}

Tile::~Tile()
{
}

Gtk::HBox&
Tile::get_root_hbox()
{
    return root_hbox_;
}

Gtk::Image&
Tile::get_image()
{
    return image_;
}

Gtk::VBox&
Tile::get_content_vbox()
{
    return content_vbox_;
}

Tile::SignalTileSelected&
Tile::get_signal_tile_selected()
{
    return signal_tile_selected_;
}

bool
Tile::on_expose_event(GdkEventExpose* event)
{
    if (! is_visible())
        return false;

    GdkWindow* event_window = event->window;

    if (paint_white_ &&
        (gdk_window_get_window_type(event_window) == GDK_WINDOW_CHILD))
    {
        // Paint white background on the widget.

        Glib::RefPtr<Gdk::Window> window = this->get_window();
        Glib::RefPtr<Gdk::GC> gc =
            this->get_style()->get_base_gc(this->get_state());

        window->draw_rectangle(gc,
                               true, // fill
                               event->area.x, event->area.y,
                               event->area.width, event->area.height);
    }

    if (this->get_flags() & Gtk::HAS_FOCUS)
    {
        int focus_pad, width, height;

        Glib::RefPtr<Gdk::Window> window = this->get_window();
        Gdk::Rectangle alloc = this->get_allocation();

        Glib::RefPtr<Gtk::Style> style = get_style();
        this->get_style_property<int>("focus_padding", focus_pad);

        // We do not need to calculate x and y origins of the box
        // for pain_* functions - just starting from (0,0) will
        // do the right thing.

        width =
            alloc.get_width() - 2 * (focus_pad + style->get_xthickness());

        height =
            alloc.get_height() - 2 * (focus_pad + style->get_ythickness());

        // Paint a backround box, the usual selection indicator
        // which is usually blue. It is important to paint on the
        // container box's window, otherwise if we'd, for instance,
        // paint on the widget itself, the box would completely cover it.

        style->paint_box(root_hbox_.get_window(),
                         Gtk::STATE_SELECTED,
                         Gtk::SHADOW_NONE,
                         Gdk::Rectangle(&(event->area)),
                         root_hbox_,
                         "TileSelectionBox",
                         0, 0,
                         width, height);

        // Change the label state to selected, so that the theme
        // engine changes the font color appropriately to contrast
        // the colour of the box.

        title_label_.set_state(Gtk::STATE_SELECTED);
        summary_label_.set_state(Gtk::STATE_SELECTED);

        // Also paint the the little line border around the widget,
        // another usual focus indicator.
        
        style->paint_focus(window,
                           this->get_state(),
                           Gdk::Rectangle(&(event->area)),
                           *this,
                           "TileFocus",
                           0, 0,
                           width, height);
    }
    else
    {
        title_label_.set_state(Gtk::STATE_NORMAL);
        summary_label_.set_state(Gtk::STATE_NORMAL);
    }

    Gtk::Widget* child_widget = this->get_child(); // Gtk::Bin method
    if (child_widget)
        propagate_expose(*child_widget, event);

    return false;
}

bool
Tile::on_button_press_event(GdkEventButton* /* event */)
{
    grab_focus();
    return false;
}

bool
Tile::on_focus_in_event(GdkEventFocus* event)
{
    signal_tile_selected_.emit();
    return Gtk::EventBox::on_focus_in_event(event);
}

} // namespace Util

} // namespace Gtk
