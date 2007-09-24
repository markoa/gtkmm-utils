/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - page-navigator.hh
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

#ifndef __GTKMM_UTILS_PAGE_NAVIGATOR_HH__
#define __GTKMM_UTILS_PAGE_NAVIGATOR_HH__

#include <memory>
#include <gtkmm/box.h>

namespace Gtk {

namespace Util {

/**
 * \brief Navigation bar.
 */
class PageNavigator : public Gtk::HBox
{
public:
    typedef sigc::signal<void> SignalClickedNext;
    typedef sigc::signal<void> SignalClickedPrevious;

    explicit PageNavigator();
    ~PageNavigator();

    void set_title(const Glib::ustring& title);
    void set_title_markup(const Glib::ustring& marked_up_title);

    void set_page_info(const Glib::ustring& info);

    SignalClickedNext& signal_clicked_next();
    SignalClickedPrevious& signal_clicked_previous();
    
protected:
    struct Private;
    std::auto_ptr<Private> priv_;

private:
    // Non-copyable:
    PageNavigator(const PageNavigator& );
    PageNavigator& operator=(const PageNavigator& );
};

} // namespace Util

} // namespace Gtk

#endif // __GTKMM_UTILS_PAGE_NAVIGATOR_HH__
