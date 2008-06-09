/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  gtkmm-utils - entry-multi-complete.cc
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

#include <gtkmm/entry.h>
#include "entry-multi-completion.h"

namespace Gtk {

namespace Util {

using std::list;
using Glib::ustring;

EntryMultiCompletion::EntryMultiCompletion()
{
    init();
}

EntryMultiCompletion::EntryMultiCompletion(const list<ustring>& items)
{
    init();
    add_items(items);
}

EntryMultiCompletion::~EntryMultiCompletion()
{
}

Glib::RefPtr<EntryMultiCompletion>
EntryMultiCompletion::create()
{
    return Glib::RefPtr<EntryMultiCompletion>(new EntryMultiCompletion());
}
    
Glib::RefPtr<EntryMultiCompletion>
EntryMultiCompletion::create(const list<ustring>& items)
{
    return Glib::RefPtr<EntryMultiCompletion>(new EntryMultiCompletion(items));
}

void
EntryMultiCompletion::init()
{
    next_id_ = 1;

    model_ = Gtk::ListStore::create(columns_);
    set_model(model_);
    set_text_column(columns_.col_title);

    set_match_func(sigc::mem_fun(*this,
                &EntryMultiCompletion::on_completion_match));
}

void
EntryMultiCompletion::add_items(const list<ustring>& items)
{
    list<ustring>::const_iterator it(items.begin());
    list<ustring>::const_iterator end(items.end());
    for ( ; it != end; ++it) {
        Gtk::TreeModel::Row row = *(model_->append());
        row[columns_.col_id] = next_id_++;
        row[columns_.col_title] = *it;
    }
}

bool
EntryMultiCompletion::on_match_selected(const Gtk::TreeModel::iterator& iter)
{
    Gtk::TreeModel::Row row = *iter;
    ustring inserting_item = row[columns_.col_title];
    
    Gtk::Entry* entry = get_entry();
    g_assert(entry);

    ustring old_text = entry->get_text();

    if (old_text.size() > 0) {
        int start = old_text.rfind(' ');
        old_text = old_text.substr(0, start + 1);
    }
    
    ustring new_value = old_text + inserting_item + ' ';
    entry->set_text(new_value);
    entry->set_position(new_value.size());

    return true;
}

bool
EntryMultiCompletion::on_completion_match(const Glib::ustring& key,
        const Gtk::TreeModel::const_iterator& iter)
{
    if (! iter) return false;

    Gtk::TreeModel::Row row = *iter;

    Glib::ustring filter_string = row[columns_.col_title];
    Glib::ustring word(key);
    int start = key.rfind(' ');
    if (start > 0)
        word = word.substr(start+1, word.size());

    ustring filter_string_start = filter_string.substr(0, word.size());
    //The key is lower-case, even if the user input is not.
    filter_string_start = filter_string_start.lowercase();

    if (word == filter_string_start)
        return true; //A match was found.
    else return false;
}

} // namespace Util

} // namespace Gtk
