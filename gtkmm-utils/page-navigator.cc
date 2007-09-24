/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - page-navigator.cc
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
#include "page-navigator.hh"

namespace Gtk {

namespace Util {

/* PageNavigator::Private */

class PageNavigator::Private
{
public:
    Private();
    ~Private() {}

    void connect_signals();
    void on_button_next_clicked();
    void on_button_previous_clicked();

    PageNavigator::SignalClickedNext     signal_clicked_next;
    PageNavigator::SignalClickedPrevious signal_clicked_previous;

    Glib::ustring  title;

    Gtk::Alignment align_box;
    Gtk::HBox      label_box;
    Gtk::Label     label_title;
    Gtk::Label     label_page_info;
    Gtk::Button    button_previous;
    Gtk::Image     image_previous;
    Gtk::Button    button_next;
    Gtk::Image     image_next;
};

PageNavigator::Private::Private()
    :
    title(),
    align_box(0.0, 1.0, 1.0, 1.0),
    label_box(false, 0),
    label_title(title),
    label_page_info(),
    button_previous(),
    image_previous(Gtk::Stock::GO_BACK, Gtk::ICON_SIZE_SMALL_TOOLBAR),
    button_next(),
    image_next(Gtk::Stock::GO_FORWARD, Gtk::ICON_SIZE_SMALL_TOOLBAR)
{
    align_box.set_padding(18, 3, 0, 0);
    
    align_box.add(label_box);
    label_box.set_spacing(5);
    label_box.pack_start(label_title, false, true, 0);
    label_title.set_justify(Gtk::JUSTIFY_LEFT);
    label_box.pack_start(label_page_info, false, true, 0);
    label_page_info.set_justify(Gtk::JUSTIFY_LEFT);
    
    button_next.set_relief(Gtk::RELIEF_NONE);
    button_next.add(image_next);
    
    button_previous.set_relief(Gtk::RELIEF_NONE);
    button_previous.add(image_previous);

    connect_signals();
}

void
PageNavigator::Private::on_button_next_clicked()
{
    signal_clicked_next.emit();
}

void
PageNavigator::Private::on_button_previous_clicked()
{
    signal_clicked_previous.emit();
}

void
PageNavigator::Private::connect_signals()
{
    button_next.signal_clicked().connect(
        sigc::mem_fun(*this,
                      &PageNavigator::Private::on_button_next_clicked));

    button_previous.signal_clicked().connect(
        sigc::mem_fun(*this,
                      &PageNavigator::Private::on_button_previous_clicked));
}

/* PageNavigator */

PageNavigator::PageNavigator()
{
    priv_.reset(new Private());

    pack_start(priv_->align_box, false, true, 0);
    pack_end(priv_->button_next, false, true, 0);
    pack_end(priv_->button_previous, false, true, 0);
    
    show_all();
}

PageNavigator::~PageNavigator()
{
}

void
PageNavigator::set_title(const Glib::ustring& title)
{
    priv_->label_title.set_text(title);
}

void
PageNavigator::set_title_markup(const Glib::ustring& marked_up_title)
{
    priv_->label_title.set_markup(marked_up_title);
}

void
PageNavigator::set_page_info(const Glib::ustring& info)
{
    priv_->label_page_info.set_text(info);
}

PageNavigator::SignalClickedNext&
PageNavigator::signal_clicked_next()
{
    return priv_->signal_clicked_next;
}

PageNavigator::SignalClickedPrevious&
PageNavigator::signal_clicked_previous()
{
    return priv_->signal_clicked_previous;
}

} // namespace Util

} // namespace Gtk
