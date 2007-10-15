/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils example - logging.h
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

#ifndef __GTKMM_UTILS_LOGGING_EXAMPLE_H__
#define __GTKMM_UTILS_LOGGING_EXAMPLE_H__

#include <tr1/memory>
#include <gtkmm.h>

class Calculator;

class ExampleWindow : public Gtk::Window
{
public:
    ExampleWindow();
    virtual ~ExampleWindow();

protected:
    virtual bool on_delete_event(GdkEventAny* event);

    virtual void on_button_add_clicked();
    virtual void on_button_subtract_clicked();

    void connect_signals();

    Gtk::VBox vbox;

    Gtk::HBox hbox_operand_a;
    Gtk::Label label_operand_a;
    Gtk::Entry entry_operand_a;

    Gtk::HBox hbox_operand_b;
    Gtk::Label label_operand_b;
    Gtk::Entry entry_operand_b;

    Gtk::HBox hbox_buttons;
    Gtk::Button button_add;
    Gtk::Button button_subtract;

    Gtk::HBox hbox_result;
    Gtk::Label label_result;
    Gtk::Entry entry_result;

    std::tr1::shared_ptr<Calculator> calculator;
};

#endif // __GTKMM_UTILS_LOGGING_EXAMPLE_H__
