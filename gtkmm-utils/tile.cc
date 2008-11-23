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

#include <gdk/gdkkeysyms.h>
#include "tile.h"

namespace Gtk {

namespace Util {

/* Tile::Private */

class Tile::Private
{
public:
    explicit Private(const Glib::ustring& title,
                     const Glib::ustring& summary,
                     bool pack_center,
                     bool paint_white);
    ~Private() {}

    void set_title(const Glib::ustring& title);
    void set_summary(const Glib::ustring& summary);

    // Signals
    SignalSelection signal_focus_in_;
    SignalSelection signal_focus_out_;
    SignalSelection signal_selected_;
    SignalSelection signal_unselected_;
    SignalActivated signal_activated_;

    // Widgets
    Gtk::HBox  root_hbox_;
    Gtk::Image image_;
    Gtk::VBox  content_vbox_;
    Gtk::HBox  title_hbox_;
    Gtk::Label title_label_;
    Gtk::HBox  summary_hbox_;
    Gtk::Label summary_label_;

    // Data members
    Glib::ustring title_;
    Glib::ustring summary_;
    bool          pack_center_;
    bool          paint_white_;

private:
    Private(const Private& );
    Private& operator=(const Private& );
};

Tile::Private::Private(const Glib::ustring& title,
                       const Glib::ustring& summary,
                       bool pack_center,
                       bool paint_white)
    :
    root_hbox_(false, 10),
    image_(),
    content_vbox_(),
    title_hbox_(),
    title_label_(),
    summary_hbox_(),
    summary_label_(),
    pack_center_(pack_center),
    paint_white_(paint_white)
{
    // set up root hbox
    root_hbox_.set_border_width(5);

    // pack illustration image
    image_.show();
    root_hbox_.pack_start(image_, false, false);

    // prepare vbox to appear on the right hand side of the image
    content_vbox_.set_border_width(5);
    content_vbox_.set_spacing(4);

    // set up the title label
    set_title(title);

    title_label_.set_alignment(0.0);
    title_label_.modify_fg(Gtk::STATE_NORMAL,
                           root_hbox_.get_style()->get_fg(
                               Gtk::STATE_INSENSITIVE));

    if (pack_center_) {
        content_vbox_.pack_start(title_label_, false, false);
     }
     else {
         // We achieve left-alignedness by packing a widget in a HBox.
         content_vbox_.pack_start(title_hbox_, false, false);
         title_hbox_.pack_start(title_label_, false, false);
     }

    // set up the summary label
    set_summary(summary);
    summary_label_.set_alignment(0.0);
    summary_label_.modify_fg(Gtk::STATE_NORMAL,
                             root_hbox_.get_style()->get_fg(
                                 Gtk::STATE_INSENSITIVE));
    if (pack_center_) {
        content_vbox_.pack_start(summary_label_, false, false);
    }
    else {
        content_vbox_.pack_start(summary_hbox_, false, false);
        summary_hbox_.pack_start(summary_label_, false, false);
     }

    // wrap up
    content_vbox_.show_all();
    root_hbox_.pack_start(content_vbox_, pack_center_, pack_center_);
}

void
Tile::Private::set_title(const Glib::ustring& title)
{
    title_ = title;
    title_label_.set_markup("<span weight=\"bold\">" +
                            Glib::Markup::escape_text(title_) +
                            "</span>");
}

void
Tile::Private::set_summary(const Glib::ustring& summary)
{
    summary_ = summary;
    summary_label_.set_markup("<small>" +
                              Glib::Markup::escape_text(summary_) +
                              "</small>");
}

/* Tile */

Tile::Tile(const Glib::ustring& title,
           const Glib::ustring& summary,
           bool pack_center,
           bool paint_white)
{
    set_flags(Gtk::CAN_FOCUS);

    priv_.reset(new Private(title, summary, pack_center, paint_white));
    add(priv_->root_hbox_);
}

Tile::~Tile()
{
}

Gtk::HBox&
Tile::get_root_hbox()
{
    return priv_->root_hbox_;
}

Gtk::Image&
Tile::get_image()
{
    return priv_->image_;
}

Gtk::VBox&
Tile::get_content_vbox()
{
    return priv_->content_vbox_;
}

Glib::ustring
Tile::get_title() const
{
    return priv_->title_;
}

void
Tile::set_title(const Glib::ustring& title)
{
    priv_->set_title(title);
}

Gtk::Label&
Tile::get_title_label()
{
    return priv_->title_label_;
}

Glib::ustring
Tile::get_summary() const
{
    return priv_->summary_;
}

void
Tile::set_summary(const Glib::ustring& summary)
{
    priv_->set_summary(summary);
}

Gtk::Label&
Tile::get_summary_label()
{
    return priv_->summary_label_;
}

Tile::SignalSelection&
Tile::signal_selected()
{
    return priv_->signal_selected_;
}

Tile::SignalSelection&
Tile::signal_unselected()
{
    return priv_->signal_unselected_;
}

Tile::SignalActivated&
Tile::signal_activated()
{
    return priv_->signal_activated_;
}

Tile::SignalActivated&
Tile::signal_focus_in()
{
    return priv_->signal_focus_in_;
}

Tile::SignalActivated&
Tile::signal_focus_out()
{
    return priv_->signal_focus_out_;
}

bool
Tile::on_expose_event(GdkEventExpose* event)
{
    if (! is_visible())
        return false;

    GdkWindow* event_window = event->window;

    if (priv_->paint_white_ &&
        (gdk_window_get_window_type(event_window) == GDK_WINDOW_CHILD))
    {
        // Paint white background on the widget.

        Glib::RefPtr<Gdk::Window> window = get_window();
        Glib::RefPtr<Gdk::GC> gc = get_style()->get_base_gc(get_state());

        window->draw_rectangle(gc,
                               true, // fill
                               event->area.x, event->area.y,
                               event->area.width, event->area.height);
    }

    if (get_flags() & Gtk::HAS_FOCUS)
    {
        int focus_pad, width, height;

        Glib::RefPtr<Gdk::Window> window = get_window();
        Gdk::Rectangle alloc = get_allocation();

        Glib::RefPtr<Gtk::Style> style = get_style();
        get_style_property<int>("focus_padding", focus_pad);

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

        style->paint_box(priv_->root_hbox_.get_window(),
                         Gtk::STATE_SELECTED,
                         Gtk::SHADOW_NONE,
                         Gdk::Rectangle(&(event->area)),
                         priv_->root_hbox_,
                         "TileSelectionBox",
                         0, 0,
                         width, height);

        // Change the label state to selected, so that the theme
        // engine changes the font color appropriately to contrast
        // the colour of the box.

        priv_->title_label_.set_state(Gtk::STATE_SELECTED);
        priv_->summary_label_.set_state(Gtk::STATE_SELECTED);

        // Also paint the the little line border around the widget,
        // another usual focus indicator.
        
        style->paint_focus(window,
                           get_state(),
                           Gdk::Rectangle(&(event->area)),
                           *this,
                           "TileFocus",
                           0, 0,
                           width, height);
    }
    else
    {
        priv_->title_label_.set_state(Gtk::STATE_NORMAL);
        priv_->summary_label_.set_state(Gtk::STATE_NORMAL);
    }

    Gtk::Widget* child_widget = get_child(); // Gtk::Bin method
    if (child_widget)
        propagate_expose(*child_widget, event);

    return false;
}

bool
Tile::on_button_press_event(GdkEventButton* event)
{
    grab_focus();

    if (event->type == GDK_2BUTTON_PRESS) {
        priv_->signal_activated_.emit(*this);
        on_activated();
    }

    return false;
}

bool
Tile::on_key_press_event(GdkEventKey* event)
{
    if ((event->type == GDK_KEY_PRESS) &&
        ((event->keyval == GDK_Return) || (event->keyval == GDK_KP_Enter))) {
        priv_->signal_activated_.emit(*this);
        on_activated();
    }

    return false;
}

bool
Tile::on_focus_in_event(GdkEventFocus* event)
{
    priv_->signal_focus_in_.emit(*this);

    return Gtk::EventBox::on_focus_in_event(event);
}

bool
Tile::on_focus_out_event(GdkEventFocus* event)
{
    priv_->signal_focus_out_.emit(*this);

    return Gtk::EventBox::on_focus_out_event(event);
}

void
Tile::on_activated()
{
}

void
Tile::on_selected()
{
}

void
Tile::on_unselected()
{
}

} // namespace Util

} // namespace Gtk
