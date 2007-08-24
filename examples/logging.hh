/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

#include <tr1/memory>

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

    Gtk::HBox hbox_result;
    Gtk::Label label_result;
    Gtk::Entry entry_result;

    Gtk::HBox hbox_buttons;
    Gtk::Button button_add;
    Gtk::Button button_subtract;

    std::tr1::shared_ptr<Calculator> calculator;
};
