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

class ExampleWindow : public Gtk::Window
{
public:
    ExampleWindow();
    virtual ~ExampleWindow();

protected:
    //Signal handlers:
    virtual void on_button_clicked();

    //Child widgets:
    Gtk::CheckButton m_button;
};

ExampleWindow::ExampleWindow()
  : m_button("click me")
{
    set_title("Logging example");
    set_border_width(10);

    m_button.signal_clicked().connect(
        sigc::mem_fun(*this,
                      &ExampleWindow::on_button_clicked));

    add(m_button);

    show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_clicked()
{
    LOG_FUNCTION_SCOPE_NORMAL_DD;
    LOG_DD("The Button was clicked: state="
           << (m_button.get_active() ? "true" : "false")); // << std::endl);
}

int main(int argc, char** argv)
{
    Gtk::Main kit(argc, argv);
    Glib::Util::Initializer::do_init();

    ExampleWindow window;

    Gtk::Main::run(window);

    return 0;
}
