/* editor menu definitions and initialisation

   Copyright (C) 1996, 1998, 2001, 2002, 2003, 2005, 2007
   Free Software Foundation, Inc.

   Authors: 1996, 1997 Paul Sheer

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.
*/

/** \file
 *  \brief Source: editor menu definitions and initialisation
 *  \author Paul Sheer
 *  \date 1996, 1997
 */

#include <config.h>

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "../src/global.h"

#include "edit-impl.h"
#include "edit-widget.h"

#include "../src/tty/tty.h"	/* KEY_F */
#include "../src/tty/key.h"	/* XCTRL */

#include "../src/cmd.h"		/* save_setup_cmd() */
#include "../src/wtools.h"	/* query_dialog() */
#include "../src/menu.h"	/* menu_entry */
#include "../src/main.h"	/* drop_menus */
#include "../src/learn.h"	/* learn_keys */

#include "edit-widget.h"
#include "../src/cmddef.h"

static void
menu_cmd (int command)
{
    edit_execute_key_command (wedit, command, -1);
    edit_update_screen (wedit);
}

static void menu_key (int i)
{
    send_message ((Widget *) wedit, WIDGET_KEY, i);
}

static void
edit_about_cmd (void)
{
    query_dialog (_(" About "),
		  _("\n                Cooledit  v3.11.5\n\n"
		    " Copyright (C) 1996 the Free Software Foundation\n\n"
		    "       A user friendly text editor written\n"
		    "           for the Midnight Commander.\n"), D_NORMAL,
		  1, _("&OK"));
}

static void
menu_mail_cmd (void)
{
    menu_cmd (CK_Mail);
}

static void
menu_load_cmd (void)
{
    menu_cmd (CK_Load);
}

static void
menu_new_cmd (void)
{
    menu_cmd (CK_New);
}

static void
menu_save_cmd (void)
{
    menu_cmd (CK_Save);
}

static void
menu_save_as_cmd (void)
{
    menu_cmd (CK_Save_As);
}

static void
menu_insert_file_cmd (void)
{
    menu_cmd (CK_Insert_File);
}

static void
menu_quit_cmd (void)
{
    menu_cmd (CK_Exit);
}

static void
menu_mark_cmd (void)
{
    menu_cmd (CK_Mark);
}

static void
menu_markcol_cmd (void)
{
    menu_cmd (CK_Column_Mark);
}

static void
menu_ins_cmd (void)
{
    menu_cmd (CK_Toggle_Insert);
}

static void
menu_copy_cmd (void)
{
    menu_cmd (CK_Copy);
}

static void
menu_move_cmd (void)
{
    menu_cmd (CK_Move);
}

static void
menu_delete_cmd (void)
{
    menu_cmd (CK_Remove);
}

static void
menu_xstore_cmd (void)
{
    menu_cmd (CK_XStore);
}

static void
menu_xcut_cmd (void)
{
    menu_cmd (CK_XCut);
}

static void
menu_xpaste_cmd (void)
{
    menu_cmd (CK_XPaste);
}

static void
menu_toggle_bookmark_cmd (void)
{
    menu_cmd (CK_Toggle_Bookmark);
}

static void
menu_flush_bookmark_cmd (void)
{
    menu_cmd (CK_Flush_Bookmarks);
}

static void
menu_next_bookmark_cmd (void)
{
    menu_cmd (CK_Next_Bookmark);
}

static void
menu_prev_bookmark_cmd (void)
{
    menu_cmd (CK_Prev_Bookmark);
}

static void
menu_cut_cmd (void)
{
    menu_cmd (CK_Save_Block);
}

static void
menu_search_cmd (void)
{
    menu_cmd (CK_Find);
}

static void
menu_search_again_cmd (void)
{
    menu_cmd (CK_Find_Again);
}

static void
menu_replace_cmd (void)
{
    menu_cmd (CK_Replace);
}

static void
menu_select_codepage_cmd (void)
{
    menu_cmd (CK_SelectCodepage);
}

static void
menu_begin_record_cmd (void)
{
    menu_cmd (CK_Begin_Record_Macro);
}

static void
menu_end_record_cmd (void)
{
    menu_cmd (CK_End_Record_Macro);
}

static void
menu_exec_macro_cmd (void)
{
    menu_key (XCTRL ('a'));
}

static void
menu_exec_macro_delete_cmd (void)
{
    menu_cmd (CK_Delete_Macro);
}

static void
menu_c_form_cmd (void)
{
    menu_key (KEY_F (19));
}

static void
menu_ispell_cmd (void)
{
    menu_cmd (CK_Pipe_Block (1));
}

static void
menu_sort_cmd (void)
{
    menu_cmd (CK_Sort);
}

static void
menu_ext_cmd (void)
{
    menu_cmd (CK_ExtCmd);
}

static void
menu_date_cmd (void)
{
    menu_cmd (CK_Date);
}

static void
menu_undo_cmd (void)
{
    menu_cmd (CK_Undo);
}

static void
menu_beginning_cmd (void)
{
    menu_cmd (CK_Beginning_Of_Text);
}

static void
menu_end_cmd (void)
{
    menu_cmd (CK_End_Of_Text);
}

static void
menu_refresh_cmd (void)
{
    menu_cmd (CK_Refresh);
}

static void
menu_goto_line (void)
{
    menu_cmd (CK_Goto);
}

static void
menu_toggle_line_state (void)
{
    menu_cmd (CK_Toggle_Line_State);
}

static void
menu_goto_bracket (void)
{
    menu_cmd (CK_Match_Bracket);
}

static void
menu_lit_cmd (void)
{
    menu_key (XCTRL ('q'));
}

static void
menu_format_paragraph (void)
{
    menu_cmd (CK_Paragraph_Format);
}

static void
menu_edit_syntax_file_cmd (void)
{
    menu_cmd (CK_Load_Syntax_File);
}

static void
menu_edit_menu_file_cmd (void)
{
    menu_cmd (CK_Load_Menu_File);
}

static void
menu_user_menu_cmd (void)
{
    menu_key (KEY_F (11));
}

static void
menu_find_declare (void)
{
    menu_cmd (CK_Find_Definition);
}

static void
menu_declare_back (void)
{
    menu_cmd (CK_Load_Prev_File);
}

static void
menu_declare_forward (void)
{
    menu_cmd (CK_Load_Next_File);
}

static menu_entry FileMenu[] =
{
    {' ', N_("&Open file..."),         NULL_HOTKEY, menu_load_cmd},
    {' ', N_("&New              C-n"), NULL_HOTKEY, menu_new_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Save              F2"), NULL_HOTKEY, menu_save_cmd},
    {' ', N_("Save &as...       F12"), NULL_HOTKEY, menu_save_as_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Insert file...   F15"), NULL_HOTKEY, menu_insert_file_cmd},
    {' ', N_("Copy to &file...  C-f"), NULL_HOTKEY, menu_cut_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&User menu...     F11"), NULL_HOTKEY, menu_user_menu_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("A&bout...            "), NULL_HOTKEY, edit_about_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Quit             F10"), NULL_HOTKEY, menu_quit_cmd}
 };

static menu_entry FileMenuEmacs[] =
{
    {' ', N_("&Open file..."),         NULL_HOTKEY, menu_load_cmd},
    {' ', N_("&New            C-x k"), NULL_HOTKEY, menu_new_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Save              F2"), NULL_HOTKEY, menu_save_cmd},
    {' ', N_("Save &as...       F12"), NULL_HOTKEY, menu_save_as_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Insert file...   F15"), NULL_HOTKEY, menu_insert_file_cmd},
    {' ', N_("Copy to &file...     "), NULL_HOTKEY, menu_cut_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&User menu...     F11"), NULL_HOTKEY, menu_user_menu_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("A&bout...            "), NULL_HOTKEY, edit_about_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Quit             F10"), NULL_HOTKEY, menu_quit_cmd}
};

static menu_entry EditMenu[] =
{
    {' ', N_("&Toggle mark                 F3"), NULL_HOTKEY, menu_mark_cmd},
    {' ', N_("Mar&k columns              S-F3"), NULL_HOTKEY, menu_markcol_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("Toggle &ins/overw           Ins"), NULL_HOTKEY, menu_ins_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Copy                        F5"), NULL_HOTKEY, menu_copy_cmd},
    {' ', N_("&Move                        F6"), NULL_HOTKEY, menu_move_cmd},
    {' ', N_("&Delete                      F8"), NULL_HOTKEY, menu_delete_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("C&opy to clipfile         C-Ins"), NULL_HOTKEY, menu_xstore_cmd},
    {' ', N_("C&ut to clipfile          S-Del"), NULL_HOTKEY, menu_xcut_cmd},
    {' ', N_("&Paste from clipfile      S-Ins"), NULL_HOTKEY, menu_xpaste_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("Toggle bookmar&k            M-k"), NULL_HOTKEY, menu_toggle_bookmark_cmd},
    {' ', N_("&Next bookmark              M-j"), NULL_HOTKEY, menu_next_bookmark_cmd},
    {' ', N_("Pre&v bookmark              M-i"), NULL_HOTKEY, menu_prev_bookmark_cmd},
    {' ', N_("&Flush bookmark             M-o"), NULL_HOTKEY, menu_flush_bookmark_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Undo                       C-u"), NULL_HOTKEY, menu_undo_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Beginning               C-PgUp"), NULL_HOTKEY, menu_beginning_cmd},
    {' ', N_("&End                     C-PgDn"), NULL_HOTKEY, menu_end_cmd}
};

static menu_entry EditMenuEmacs[] =
{
    {' ', N_("&Toggle mark                 F3"), NULL_HOTKEY, menu_mark_cmd},
    {' ', N_("Mar&k columns              S-F3"), NULL_HOTKEY, menu_markcol_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("Toggle &ins/overw           Ins"), NULL_HOTKEY, menu_ins_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Copy                        F5"), NULL_HOTKEY, menu_copy_cmd},
    {' ', N_("&Move                        F6"), NULL_HOTKEY, menu_move_cmd},
    {' ', N_("&Delete                      F8"), NULL_HOTKEY, menu_delete_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("C&opy to clipfile           M-w"), NULL_HOTKEY, menu_xstore_cmd},
    {' ', N_("C&ut to clipfile            C-w"), NULL_HOTKEY, menu_xcut_cmd},
    {' ', N_("&Paste from clipfile        C-y"), NULL_HOTKEY, menu_xpaste_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("Toggle bookmar&k               "), NULL_HOTKEY, menu_toggle_bookmark_cmd},
    {' ', N_("&Next bookmark                 "), NULL_HOTKEY, menu_next_bookmark_cmd},
    {' ', N_("Pre&v bookmark                 "), NULL_HOTKEY, menu_prev_bookmark_cmd},
    {' ', N_("&Flush bookmark                "), NULL_HOTKEY, menu_flush_bookmark_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Undo                       C-u"), NULL_HOTKEY, menu_undo_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Beginning               C-PgUp"), NULL_HOTKEY, menu_beginning_cmd},
    {' ', N_("&End                     C-PgDn"), NULL_HOTKEY, menu_end_cmd}
};

static menu_entry SearReplMenu[] =
{
    {' ', N_("&Search...         F7"), NULL_HOTKEY, menu_search_cmd},
    {' ', N_("Search &again     F17"), NULL_HOTKEY, menu_search_again_cmd},
    {' ', N_("&Replace...        F4"), NULL_HOTKEY, menu_replace_cmd}
};

#define SearReplMenuEmacs SearReplMenu

static menu_entry CmdMenu[] =
{
    {' ', N_("&Go to line...            M-l"), NULL_HOTKEY, menu_goto_line},
    {' ', N_("Toggle li&ne state        M-n"), NULL_HOTKEY, menu_toggle_line_state},
    {' ', N_("Go to matching &bracket   M-b"), NULL_HOTKEY, menu_goto_bracket},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("Find declaration      A-Enter"), NULL_HOTKEY, menu_find_declare},
    {' ', N_("Back from declaration     M--"), NULL_HOTKEY, menu_declare_back},
    {' ', N_("Forward to declaration    M-+"), NULL_HOTKEY, menu_declare_forward},
#ifdef HAVE_CHARSET
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("Encod&ing...             M-e"), NULL_HOTKEY, menu_select_codepage_cmd},
#endif
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("Insert &literal...       C-q"), NULL_HOTKEY, menu_lit_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Refresh screen          C-l"), NULL_HOTKEY, menu_refresh_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Start record macro      C-r"), NULL_HOTKEY, menu_begin_record_cmd},
    {' ', N_("&Finish record macro...  C-r"), NULL_HOTKEY, menu_end_record_cmd},
    {' ', N_("&Execute macro...   C-a, KEY"), NULL_HOTKEY, menu_exec_macro_cmd},
    {' ', N_("Delete macr&o...            "), NULL_HOTKEY, menu_exec_macro_delete_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("Insert &date/time           "), NULL_HOTKEY, menu_date_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("Format p&aragraph        M-p"), NULL_HOTKEY, menu_format_paragraph},
    {' ', N_("'ispell' s&pell check    C-p"), NULL_HOTKEY, menu_ispell_cmd},
    {' ', N_("Sor&t...                 M-t"), NULL_HOTKEY, menu_sort_cmd},
    {' ', N_("Paste o&utput of...      M-u"), NULL_HOTKEY, menu_ext_cmd},
    {' ', N_("E&xternal Formatter      F19"), NULL_HOTKEY, menu_c_form_cmd},
    {' ', N_("&Mail...                    "), NULL_HOTKEY, menu_mail_cmd}
};

static menu_entry CmdMenuEmacs[] =
{
    {' ', N_("&Go to line...            M-l"), NULL_HOTKEY, menu_goto_line},
    {' ', N_("Toggle li&ne state        M-n"), NULL_HOTKEY, menu_toggle_line_state},
    {' ', N_("Go to matching &bracket   M-b"), NULL_HOTKEY, menu_goto_bracket},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("Insert &literal...       C-q"), NULL_HOTKEY, menu_lit_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Refresh screen          C-l"), NULL_HOTKEY, menu_refresh_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("&Start record macro      C-r"), NULL_HOTKEY, menu_begin_record_cmd},
    {' ', N_("&Finish record macro...  C-r"), NULL_HOTKEY, menu_end_record_cmd},
    {' ', N_("&Execute macro... C-x e, KEY"), NULL_HOTKEY, menu_exec_macro_cmd},
    {' ', N_("Delete macr&o...            "), NULL_HOTKEY, menu_exec_macro_delete_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("Insert &date/time           "), NULL_HOTKEY, menu_date_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("Format p&aragraph        M-p"), NULL_HOTKEY, menu_format_paragraph},
    {' ', N_("'ispell' s&pell check    M-$"), NULL_HOTKEY, menu_ispell_cmd},
    {' ', N_("Sor&t...                 M-t"), NULL_HOTKEY, menu_sort_cmd},
    {' ', N_("Paste o&utput of...      M-u"), NULL_HOTKEY, menu_ext_cmd},
    {' ', N_("E&xternal Formatter      F19"), NULL_HOTKEY, menu_c_form_cmd},
    {' ', N_("&Mail...                    "), NULL_HOTKEY, menu_mail_cmd}
};

static menu_entry OptMenu[] =
{
    {' ', N_("&General...  "), NULL_HOTKEY, edit_options_dialog},
    {' ', N_("&Save mode..."), NULL_HOTKEY, menu_save_mode_cmd},
    {' ', N_("Learn &Keys..."), NULL_HOTKEY, learn_keys},
    {' ', N_("Syntax &Highlighting..."), NULL_HOTKEY, edit_syntax_dialog},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("S&yntax file"), NULL_HOTKEY, menu_edit_syntax_file_cmd},
    {' ', N_("&Menu file"), NULL_HOTKEY, menu_edit_menu_file_cmd},
    {' ', "", NULL_HOTKEY, 0},
    {' ', N_("Save setu&p"), NULL_HOTKEY, save_setup_cmd}
};

#define OptMenuEmacs OptMenu

#define menu_entries(x) sizeof(x)/sizeof(menu_entry)

#define N_menus 5

static Menu *EditMenuBar [N_menus];

static void
edit_init_menu_normal (void)
{
    EditMenuBar[0] = create_menu (_(" File "), FileMenu, menu_entries (FileMenu),
				    "[Internal File Editor]");
    EditMenuBar[1] = create_menu (_(" Edit "), EditMenu, menu_entries (EditMenu),
				    "[Internal File Editor]");
    EditMenuBar[2] = create_menu (_(" Sear/Repl "), SearReplMenu, menu_entries (SearReplMenu),
				    "[Internal File Editor]");
    EditMenuBar[3] = create_menu (_(" Command "), CmdMenu, menu_entries (CmdMenu),
				    "[Internal File Editor]");
    EditMenuBar[4] = create_menu (_(" Options "), OptMenu, menu_entries (OptMenu),
				    "[Internal File Editor]");
}

static void
edit_init_menu_emacs (void)
{
    EditMenuBar[0] = create_menu (_(" File "), FileMenuEmacs, menu_entries (FileMenuEmacs),
				    "[Internal File Editor]");
    EditMenuBar[1] = create_menu (_(" Edit "), EditMenuEmacs, menu_entries (EditMenuEmacs),
				    "[Internal File Editor]");
    EditMenuBar[2] = create_menu (_(" Sear/Repl "), SearReplMenuEmacs, menu_entries (SearReplMenuEmacs),
				    "[Internal File Editor]");
    EditMenuBar[3] = create_menu (_(" Command "), CmdMenuEmacs, menu_entries (CmdMenuEmacs),
				    "[Internal File Editor]");
    EditMenuBar[4] = create_menu (_(" Options "), OptMenuEmacs, menu_entries (OptMenuEmacs),
				    "[Internal File Editor]");
}

static void
edit_init_menu (void)
{
    switch (edit_key_emulation) {
    default:
    case EDIT_KEY_EMULATION_NORMAL:
	edit_init_menu_normal ();
	break;
    case EDIT_KEY_EMULATION_EMACS:
	edit_init_menu_emacs ();
	break;
    }
}

struct WMenu *
edit_create_menu (void)
{
    edit_init_menu ();
    return menubar_new (0, 0, COLS, EditMenuBar, N_menus);
}

void
edit_done_menu (struct WMenu *wmenu)
{
    int i;
    for (i = 0; i < N_menus; i++)
	destroy_menu (wmenu->menu[i]);
}


void
edit_reload_menu (void)
{
    edit_done_menu (edit_menubar);
    edit_init_menu ();
    menubar_arrange (edit_menubar);
}


static void
edit_drop_menu_cmd (WEdit *e, int which)
{
    if (edit_menubar->active)
	return;
    edit_menubar->active = 1;
    edit_menubar->dropped = drop_menus;
    if (which >= 0) {
	edit_menubar->selected = which;
    }

    edit_menubar->previous_widget = e->widget.parent->current->dlg_id;
    dlg_select_widget (edit_menubar);
}


void edit_menu_cmd (WEdit * e)
{
    edit_drop_menu_cmd (e, -1);
}


int edit_drop_hotkey_menu (WEdit * e, int key)
{
    int m = 0;
    switch (key) {
    case ALT ('f'):
	if (edit_key_emulation == EDIT_KEY_EMULATION_EMACS)
	    return 0;
	m = 0;
	break;
    case ALT ('e'):
	m = 1;
	break;
    case ALT ('s'):
	m = 2;
	break;
    case ALT ('c'):
	m = 3;
	break;
    case ALT ('o'):
	m = 4;
	break;
    default:
	return 0;
    }

    edit_drop_menu_cmd (e, m);
    return 1;
}
