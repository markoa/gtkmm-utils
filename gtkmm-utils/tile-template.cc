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
#include <gtkmm/label.h>
#include "tile-template.hh"

namespace Gtk {

namespace Util {

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

    content_vbox_ = Gtk::manage(new Gtk::VBox());
    alignment_->add(*content_vbox_);

    content_vbox_->set_border_width(2);
    content_vbox_->show();

    // Labels. In case of lack of space, we ellipsize the end of the text.
    title_label_ = Gtk::manage(new Gtk::Label());
    title_label_->set_alignment(0, 0.5);
    title_label_->set_selectable();
    title_label_->set_markup("<span weight=\"bold\">" +
                             Glib::strescape(title_) +
                             "</span>");
    title_label_->set_ellipsize(Pango::ELLIPSIZE_END);
    title_label_->set_max_width_chars(30);
    title_label_->modify_fg(Gtk::STATE_NORMAL,
                            this->get_style()->get_fg(Gtk::STATE_INSENSITIVE));

    content_vbox_->pack_start(*title_label_, false, false, 0);

    summary_label_ = Gtk::manage(new Gtk::Label());
    summary_label_->set_alignment(0, 0.5);
    summary_label_->set_selectable();
    summary_label_->set_line_wrap();
    summary_label_->set_markup("<small>" +
                               Glib::strescape(summary_) +
                               "</small>");
    summary_label_->set_ellipsize(Pango::ELLIPSIZE_END);
    summary_label_->set_max_width_chars(30);
    summary_label_->modify_fg(Gtk::STATE_NORMAL,
                              this->get_style()->get_fg(
                                  Gtk::STATE_INSENSITIVE));

    content_vbox_->pack_start(*summary_label_, false, false, 0);

    alignment_->show_all();
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
    update_title();
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
    update_summary();
}

Glib::ustring
TileTemplate::get_summary() const
{
    return summary_;
}

void
TileTemplate::update_title()
{
    if (! title_.size())
        return;

    title_label_->set_markup("<span weight=\"bold\">" +
                             Glib::strescape(title_) +
                             "</span>");
    title_label_->show();
}


void
TileTemplate::update_summary()
{
    if (! summary_.size())
        return;

    summary_label_->set_markup("<small>" +
                               Glib::strescape(summary_) +
                               "</small>");
    summary_label_->show();
}

void
TileTemplate::on_realize()
{
    TileSurface::on_realize();
}

} // namespace Util

} // namespace Gtk
