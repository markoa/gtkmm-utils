/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils example - multi-completion.cc
 *
 *  Copyright (C) 2008 Marko Anastasov
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

#include "multi-completion.h"

ExampleWindow::ExampleWindow() :
    label_("Press a or b to see a list of possible completions."),
    button_close_("Close")
{
    set_title("Gtk::Util::EntryMultiCompletion demo");

    add(vbox_);
    vbox_.pack_start(entry_);
    vbox_.pack_start(label_, Gtk::PACK_SHRINK);

    button_close_.signal_clicked().connect(
            sigc::mem_fun(*this, &ExampleWindow::on_button_close));
    vbox_.pack_start(button_close_, Gtk::PACK_SHRINK);
    button_close_.set_flags(Gtk::CAN_DEFAULT);
    button_close_.grab_default();

    std::list<Glib::ustring> suggestions;
    suggestions.push_back("art");
    suggestions.push_back("animation");
    suggestions.push_back("block");
    suggestions.push_back("blaze");

    Glib::RefPtr<Gtk::Util::EntryMultiCompletion> completion =
        Gtk::Util::EntryMultiCompletion::create(suggestions);

    entry_.set_completion(completion);

    show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void
ExampleWindow::on_button_close()
{
    hide();
}

int
main(int argc, char** argv)
{
    Gtk::Main kit(argc, argv);
    ExampleWindow window;
    Gtk::Main::run(window);
    return 0;
}
