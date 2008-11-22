/*
 *  gtkmm-utils - page-navigator.h
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
#include <gtkmm/button.h>
#include <gtkmm/eventbox.h>

namespace Gtk {

namespace Util {

/**
 * \brief Navigation bar.
 *
 * Used for composing a TileView, otherwise it is completely generic
 * and can be used to display navigation of any kind of page-like view. <p>
 *
 * The widget is composed of a title label, page information label, and
 * buttons which should lead the user to a next or previous page in the view.
 * Use of labels is optional. The title label should describe the information
 * being displayed in a view using this navigation bar. The page information
 * label should inform the user of the current position, ie its value should
 * be dynamically updated to something like 'x - y of z'.
 */
class PageNavigator : public Gtk::EventBox
{
public:
    /** \brief Signal emmitted when a page navigation request has been made.
     *
     * This could be when a corresponding button has been clicked on,
     * or when a mouse wheel is scrolled down within the navigation bar.
     */
    typedef sigc::signal<void> SignalNavigation;

    /// \brief Constructs a new PageNavigator.
    explicit PageNavigator();

    /// \brief PageNavigator destructor.
    virtual ~PageNavigator();

    /**
     * \brief Sets a title for the navigation bar.
     *
     * \param title  a string
     */
    virtual void set_title(const Glib::ustring& title);

    /**
     * \brief Sets a custom markup on the title in the bar.
     *
     * \param marked_up_title  escaped markup string; escape strings with
     * Glib::Markup::escape_text()
     */
    virtual void set_title_markup(const Glib::ustring& marked_up_title);

    /**
     * \brief Sets text on a lable which is meant to display page information.
     * This label appears next to the label containing the title.
     * Compose a string such as '11 - 20 / 23' and pass it here.
     *
     * \param info a string to describe current location in a page view
     */
    virtual void set_page_info(const Glib::ustring& info);

    /**
     * \brief Returns a SignalNavigation for requests to the first page,
     * which you can connect to.
     *
     * \return a SignalNavigation reference
     */
    SignalNavigation& signal_first();

    /**
     * \brief Returns a SignalNavigation for requests to a previous page,
     * which you can connect to.
     *
     * \return a SignalPrevious reference
     */
    SignalNavigation& signal_previous();
    
    /**
     * \brief Returns a SignalNavigation for requests to a next page,
     * which you can connect to.
     *
     * \return a SignalNavigation reference
     */
    SignalNavigation& signal_next();

    /**
     * \brief Returns a SignalNavigation for requests to the last page,
     * which you can connect to.
     *
     * \return a SignalNavigation reference
     */
    SignalNavigation& signal_last();

    /**
     * \brief Returns a button for navigating to the first page.
     *
     * \return a Gtk::Button reference
     */
    virtual Gtk::Button& get_button_first();

    /**
     * \brief Returns a button for navigating to the previous page.
     *
     * \return a Gtk::Button reference
     */
    virtual Gtk::Button& get_button_previous();
    
    /**
     * \brief Returns a button for navigating to the next page.
     *
     * \return a Gtk::Button reference
     */
    virtual Gtk::Button& get_button_next();
    
    /**
     * \brief Returns a button for navigating to the last page.
     *
     * \return a Gtk::Button reference
     */
    virtual Gtk::Button& get_button_last();

protected:
    virtual bool on_scroll_event(GdkEventScroll* event);

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
