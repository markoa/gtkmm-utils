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

class BadConversion : public std::runtime_error
{
public:
    BadConversion(const std::string& s) : std::runtime_error(s) {}
};

static double
string_to_double(const std::string& str)
{
    std::istringstream is(str);
    double res;

    if (! (is >> res))
    {
        LOG_ERROR("Cannot convert " << str << " to double");
        throw BadConversion("string_to_double(\"" + str + "\")");
    }

    return res;
}

static std::string
double_to_string(double num)
{
    std::ostringstream os;

    if (! (os << num))
    {
        LOG_ERROR("Cannot convert " << num << " to string");
        throw BadConversion("double_to_string() error");
    }

    return os.str();
}

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

    LOG_DD("Performing addition");

    try
    {
        double a = string_to_double(entry_operand_a.get_text());
        double b = string_to_double(entry_operand_b.get_text());
        calculator->update(a, b, OPERATION_ADDITION);
        std::string res = double_to_string(calculator->get_last_result());

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
    LOG_FUNCTION_SCOPE_NORMAL_DD;

    LOG_DD("Performing subtraction");

    try
    {
        double a = string_to_double(entry_operand_a.get_text());
        double b = string_to_double(entry_operand_b.get_text());
        calculator->update(a, b, OPERATION_SUBTRACTION);
        std::string res = double_to_string(calculator->get_last_result());

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

    Glib::Util::Initializer::do_init();

    ExampleWindow window;

    Gtk::Main::run(window);

    return 0;
}
