/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - entry-multi-complete.h
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

#ifndef __GTKMM_UTILS_ENTRY_MULTI_COMPLETE_H__
#define __GTKMM_UTILS_ENTRY_MULTI_COMPLETE_H__

#include <list>
#include <gtkmm/entrycompletion.h>
#include <gtkmm/liststore.h>

namespace Gtk {

namespace Util {

class EntryMultiCompletionModelColumns : public Gtk::TreeModel::ColumnRecord
{
public:
    EntryMultiCompletionModelColumns() { add(col_id); add(col_title); }

    Gtk::TreeModelColumn<int> col_id; // not displayed
    Gtk::TreeModelColumn<Glib::ustring> col_title;
};
    
class EntryMultiCompletion : public Gtk::EntryCompletion
{
public:
    static Glib::RefPtr<EntryMultiCompletion> create();

    static Glib::RefPtr<EntryMultiCompletion> create(const std::list<Glib::ustring>& items);

    virtual ~EntryMultiCompletion();

protected:
    EntryMultiCompletion();
    EntryMultiCompletion(const std::list<Glib::ustring>& items);

    virtual void init();
    virtual void add_items(const std::list<Glib::ustring>& items);

    // Gtk::EntryCompletion override
    virtual bool on_match_selected(const Gtk::TreeModel::iterator& iter);

    virtual bool on_completion_match(const Glib::ustring& key,
            const Gtk::TreeModel::const_iterator& iter);

    int next_id_;
    Glib::RefPtr<Gtk::ListStore> model_;
    EntryMultiCompletionModelColumns columns_;

private:
    // noncopyable
    EntryMultiCompletion(const EntryMultiCompletion&);
    EntryMultiCompletion& operator=(const EntryMultiCompletion&);
};

} // namespace Util

} // namespace Gtk

#endif // __GTKMM_UTILS_ENTRY_MULTI_COMPLETE_H__
