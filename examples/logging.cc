/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/**
 * You can compile from command line with:
 * g++ -Wall -g -O0 `pkg-config --cflags --libs gtkmm-utils` -o logging logging.cc
 *
 * Run the program with:
 *   $ application_log_domains="all" ./logging
 * or:
 *   $ application_log_domains="logging.cc (other files...)" ./logging
 */

#include "glibmm-utils/glibmm-utils.hh"
#include <gtkmm.h>

#include <sstream>
#include <stdexcept>
#include <string>

#include "logging.hh"

enum Operation
{
    OPERATION_ADDITION,
    OPERATION_SUBTRACTION
};


class Calculator
{
public:
    explicit Calculator() : _last_result(0) {}
    ~Calculator() {}

    double update(double a, double b, Operation op);
    double get_last_result() const { return _last_result; }

private:
    double _last_result;
};

double
Calculator::update(double a, double b, Operation op)
{
    switch (op)
    {
    case OPERATION_ADDITION:
        _last_result = a + b;
        break;
    case OPERATION_SUBTRACTION:
        _last_result = a - b;
        break;
    default:
        break;
    }

    return _last_result;
}


ExampleWindow::ExampleWindow()
    :
    label_operand_a("Operand a"),
    label_operand_b("Operand b"),
    button_add("Add"),
    button_subtract("Subtract"),
    label_result("Result")
{
    calculator.reset(new Calculator());

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
ExampleWindow::on_delete_event(GdkEventAny* /* event */)
{
    LOG_D("Closing the application window", "destructor-domain");
    return false;
}

void
ExampleWindow::on_button_add_clicked()
{
    using namespace Glib::Util::String;

    // Setting LOG_FUNCTION_SCOPE_NORMAL_DD will result in more verbose
    // logging output: your messages will be surrounded by braces,
    // the opening one referencing the function of origin and by the closing
    // the elapsed time of execution will be printed.

    LOG_FUNCTION_SCOPE_NORMAL_DD;

    LOG_DD("Performing addition");

    try
    {
        double a = convert_to<double>(entry_operand_a.get_text());
        double b = convert_to<double>(entry_operand_b.get_text());

        LOG_DD("Operands: " << a << ", " << b);

        calculator->update(a, b, OPERATION_ADDITION);
        std::string res = stringify(calculator->get_last_result());

        entry_result.set_text(res);
    }
    catch (BadConversion& ex)
    {
        LOG_EXCEPTION_DD("Number conversion failed");
        entry_result.set_text("0");
    }
}

void
ExampleWindow::on_button_subtract_clicked()
{
    using namespace Glib::Util::String;

    LOG_FUNCTION_SCOPE_NORMAL_DD;

    LOG_DD("Performing subtraction");

    try
    {
        double a = convert_to<double>(entry_operand_a.get_text());
        double b = convert_to<double>(entry_operand_b.get_text());

        LOG_DD("Operands: " << a << ", " << b);

        calculator->update(a, b, OPERATION_SUBTRACTION);
        std::string res = stringify(calculator->get_last_result());

        entry_result.set_text(res);
    }
    catch (BadConversion& ex)
    {
        LOG_EXCEPTION_DD("Number conversion failed");
        entry_result.set_text("0");
    }
}

int
main(int argc, char** argv)
{
    Gtk::Main kit(argc, argv);

    // Initializations necessary for gtkmm-utils.
    Glib::Util::Initializer::do_init();

    ExampleWindow window;

    Gtk::Main::run(window);

    return 0;
}
