/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/**
 * You can compile from command line with:
 * g++ -Wall -g -O0 `pkg-config --cflags --libs gtkmm-utils` -o logging logging.cc
 *
 * Run the program with:
 *   $ application_log_domains="all" ./logging
 * or:
 *   $ application_log_domains="main.cc (other files...)" ./logging
 */

#include <glibmm-utils/glibmm-utils.hh>
#include <gtkmm.h>
#include "logging.hh"

ExampleWindow::ExampleWindow()
    :
    label_operand_a("Operand a"),
    label_operand_b("Operand b"),
    button_add("Add"),
    button_subtract("Subtract"),
    label_result("Result")
{
    set_title("gtkmm-utils logging example");
    set_border_width(6);

    connect_signals();

    hbox_operand_a.pack_start(label_operand_a);
    hbox_operand_a.pack_start(entry_operand_a);

    hbox_operand_b.pack_start(label_operand_b);
    hbox_operand_b.pack_start(entry_operand_b);

    entry_result.set_editable(false);
    hbox_result.set_border_width(5);
    hbox_result.pack_start(label_result);
    hbox_result.pack_start(entry_result);

    hbox_buttons.pack_start(button_add);
    hbox_buttons.pack_start(button_subtract);

    vbox.pack_start(hbox_operand_a);
    vbox.pack_start(hbox_operand_b);
    vbox.pack_start(hbox_result);
    vbox.pack_start(hbox_buttons);

    add(vbox);

    show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void
ExampleWindow::connect_signals()
{
    button_add.signal_clicked().connect(
        sigc::mem_fun(*this, &ExampleWindow::on_button_add_clicked));

    button_subtract.signal_clicked().connect(
        sigc::mem_fun(*this, &ExampleWindow::on_button_subtract_clicked));
}

bool
ExampleWindow::on_delete_event(GdkEventAny* event)
{
    // Setting LOG_FUNCTION_SCOPE_NORMAL_DD will result in more verbose
    // logging output: your messages will be surrounded by braces,
    // the opening one referencing the function of origin and the closing
    // will print elapsed time of execution.

    LOG_FUNCTION_SCOPE_NORMAL_DD;

    LOG_DD("Closing the application window");
    return false;
}

void
ExampleWindow::on_button_add_clicked()
{
    LOG_FUNCTION_SCOPE_NORMAL_DD;

    LOG_DD("adding");
}

void
ExampleWindow::on_button_subtract_clicked()
{
    LOG_FUNCTION_SCOPE_NORMAL_DD;

    LOG_DD("subtracting");
}

int
main(int argc, char** argv)
{
    Gtk::Main kit(argc, argv);

    Glib::Util::Initializer::do_init();

    ExampleWindow window;

    Gtk::Main::run(window);

    return 0;
}
