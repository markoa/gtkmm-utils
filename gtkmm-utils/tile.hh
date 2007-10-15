/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - tile.hh
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

#ifndef __GTKMM_UTILS_TILE_H__
#define __GTKMM_UTILS_TILE_H__

#include <gtkmm/box.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <memory>

namespace Gtk {

namespace Util {

/**
 * \brief Extensible widget providing a highlighted title, summary
 * and an image on the left-hand side.
 *
 * The widget is designed as a more user-friendly alternative to
 * Gtk::TreeView-based lists and tabular business-like view.
 * Another advantage is that it is widget-based, so any additional GTK+
 * widget, be it static or interactive, may be added.
 */
class Tile : public Gtk::EventBox
{
public:
    /**
     * \brief Signature of signal emitted to indicate that the Tile has been
     * selected (gained focus) or unselected (lost focus).
     *
     * \see TileView::get_selection()
     */
    typedef sigc::signal<void, Tile&> SignalSelection;

    /**
     * \brief Signature of signal emmitted when user double-clicks
     * or presses the Return key on a Tile.
     *
     * \see TileView::signal_tile_activated()
     */ 
    typedef sigc::signal<void, Tile&> SignalActivated;

    friend class TileView;

    /**
     * \brief Tile constructor.
     *
     * \param title  The title text on the widget.
     * \param summary  The text below the title.
     * \param pack_center  <tt>true</tt> when labels should be packed
     * in the center of the description area, or <tt>false</tt> when
     * the labels should be aligned next to the image.
     * \param paint_white  Whether to paint the background of the widget white,
     * according to the current Gtk::Style settings.
     */
    explicit Tile(const Glib::ustring& title = Glib::ustring(),
                  const Glib::ustring& summary = Glib::ustring(),
                  bool pack_center = true,
                  bool paint_white = true);
    virtual ~Tile();

    /**
     * \brief Returns the Gtk::HBox that contains the image and Gtk::VBox
     * with all the labels and any other additional widgets.
     *
     * \return a reference to the root horizontal box.
     */
    virtual Gtk::HBox& get_root_hbox();

    /**
     * \brief Returns the image for the Tile, so that its content can be set.
     *
     * \return a reference to the Tile's image.
     */
    virtual Gtk::Image& get_image();

    /**
     * \brief Returns the Gtk::VBox holding the "content" widgets of the tile.
     * Use this box when you want to pack more widgets to the Tile.
     *
     * \return a reference to the content vbox.
     */
    virtual Gtk::VBox& get_content_vbox();

    /**
     * \brief Returns Tile title, ie the top-first, highlighted text.
     *
     * \return Tile title string.
     */
    virtual Glib::ustring get_title() const;

    /**
     * \brief Escapes and sets a new title on the Tile.
     *
     * \param title new title string.
     */
    virtual void set_title(const Glib::ustring& title);

    /**
     * \brief Returns the "summary" of the Tile, ie the smaller text
     * below the title.
     *
     * \return Tile summary string
     */
    virtual Glib::ustring get_summary() const;

    /**
     * \brief Escapes and sets a new summary on the Tile.
     *
     * \param summary new summary string.
     */
    virtual void set_summary(const Glib::ustring& summary);

    /**
     * \brief Returns the SignalSelection indicating that
     * the tile has been selected.
     *
     * This signal is controlled by TileView. It is emitted after the
     * selection has been changed between the packed Tiles. If you are
     * not using TileView, use signals provided by signal_focus_in()
     * and signal_focus_out().
     *
     * The signal can be useful for subclasses that need to implement
     * some special behaviour on this event, such as updating the content
     * layout.
     *
     * \return a reference to SignalSelection.
     */
    SignalSelection& signal_selected();

    /**
     * \brief Returns the SignalSelection indicating that
     * the tile has been unselected in favour of another one.
     *
     * This signal is controlled by TileView. It is emitted after the
     * selection has been changed between the packed Tiles. If you are
     * not using TileView, use signals provided by signal_focus_in()
     * and signal_focus_out().
     *
     * The signal can be useful for subclasses that need to implement
     * some special behaviour on this event, such as updating the content
     * layout.
     *
     * \return a reference to SignalSelection.
     */
    SignalSelection& signal_unselected();

    /**
     * \brief Returns the SignalActivated.
     *
     * \return a reference to Tile's SignalActivated.
     */
    SignalActivated& signal_activated();

    /** \brief Returns the widget's focus-in proxy signal. */
    SignalSelection& signal_focus_in();

    /** \brief Returns the widget's focus-out proxy signal. */
    SignalSelection& signal_focus_out();

protected:
    // Gtk::Widget overrides
    virtual bool on_expose_event(GdkEventExpose* event);
    virtual bool on_button_press_event(GdkEventButton* event);
    virtual bool on_key_press_event(GdkEventKey* event);
    virtual bool on_focus_in_event(GdkEventFocus* event);
    virtual bool on_focus_out_event(GdkEventFocus* event);

    // Default signal handlers
    virtual void on_activated();
    virtual void on_selected();
    virtual void on_unselected();

    struct Private;
    std::auto_ptr<Private> priv_;

private:
    // Non-copyable
    Tile(const Tile& other);
    Tile& operator=(const Tile&);
};

} // namespace Util

} // namespace Gtk

#endif // __GTKMM_UTILS_TILE_H__
