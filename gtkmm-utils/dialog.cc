/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - dialog.cc
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

#include "dialog.hh"

#include <gtkmm.h>

namespace Gtk
{

namespace Util
{

namespace Dialog
{

namespace
{

static int
display_dialog_simple(Gtk::MessageType message_type,
                      const Glib::ustring& message,
                      const Glib::ustring& title,
                      const Glib::ustring& secondary_text)
{
    Gtk::MessageDialog dialog(message,
                              false /* no markup */,
                              message_type,
                              Gtk::BUTTONS_OK,
                              true /* modal */);

    if (title.size())
        dialog.set_title(title);
  
    if (secondary_text.size())
        dialog.set_secondary_text(secondary_text, false /* no markup */);

    dialog.set_default_response(Gtk::RESPONSE_OK);

    return dialog.run();
}

} // anonymous namespace

int
display_info(const Glib::ustring& message,
             const Glib::ustring& title,
             const Glib::ustring& secondary_text)
{
    return display_dialog_simple(Gtk::MESSAGE_INFO,
                                 message, title, secondary_text);
}

int
display_warning(const Glib::ustring& message,
                const Glib::ustring& title,
                const Glib::ustring& secondary_text)
{
    return display_dialog_simple(Gtk::MESSAGE_WARNING,
                                 message, title, secondary_text);
}

int
display_error(const Glib::ustring& message,
              const Glib::ustring& title,
              const Glib::ustring& secondary_text)
{
    return display_dialog_simple(Gtk::MESSAGE_ERROR,
                                 message, title, secondary_text);
}

int
ask_yes_no_question(const Glib::ustring& message,
                    const Glib::ustring& title,
                    const Glib::ustring& secondary_text)
{
    Gtk::MessageDialog dialog(message,
                              false /* no markup */,
                              Gtk::MESSAGE_QUESTION,
                              Gtk::BUTTONS_YES_NO,
                              true /* modal */);

    if (title.size())
        dialog.set_title(title);

    if (secondary_text.size())
        dialog.set_secondary_text(secondary_text, false /* no markup */);

    dialog.set_default_response(Gtk::RESPONSE_YES);

    return dialog.run();
}

int
ask_yes_no_cancel_question(const Glib::ustring& message,
                           const Glib::ustring& title,
                           const Glib::ustring& secondary_text)
{
    Gtk::MessageDialog dialog(message,
                              false /* no markup */,
                              Gtk::MESSAGE_QUESTION,
                              Gtk::BUTTONS_NONE,
                              true /* modal */);

    if (title.size())
        dialog.set_title(title);

    if (secondary_text.size())
        dialog.set_secondary_text(secondary_text, false /* no markup */);

    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::NO, Gtk::RESPONSE_NO);
    dialog.add_button(Gtk::Stock::YES, Gtk::RESPONSE_YES);

    dialog.set_default_response(Gtk::RESPONSE_CANCEL);

    return dialog.run();
}

} // namespace Dialog

} // namespace Util

} // namespace Gtk
