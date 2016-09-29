#include "appwindow.hpp"

AppWindow::AppWindow()
{
  set_title("Advanced Ergonomics Laboratory");

  // A utility class for constructing things that go into menus, which
  // we'll set up next.
  using Gtk::Menu_Helpers::MenuElem;
  
  // Set up the application menu
  // The slot we use here just causes AppWindow::hide() on this,
  // which shuts down the application.

	sigc::slot1<void, Viewer::App> app_slot = 
  	sigc::mem_fun(m_viewer, &Viewer::setApp);
	sigc::slot1<void, Viewer::Mode> mode_slot = 
  	sigc::mem_fun(m_viewer, &Viewer::setMode);
	sigc::slot1<void, Viewer::Edit> edit_slot = 
  	sigc::mem_fun(m_viewer, &Viewer::setEdit);
	sigc::slot1<void, Viewer::Option> option_slot = 
  	sigc::mem_fun(m_viewer, &Viewer::setOption);

	m_menu_app.items().push_back(MenuElem("_Reset Position",
															Gtk::AccelKey("i"),
    													sigc::bind( app_slot, Viewer::R_POS)));
	m_menu_app.items().push_back(MenuElem("_Reset Orientation", 
															Gtk::AccelKey("o"), 
															sigc::bind( app_slot, Viewer::R_ORI)));
  m_menu_app.items().push_back(MenuElem("_Reset Joints",
															Gtk::AccelKey("n"),
    													sigc::bind( app_slot, Viewer::R_JOINTS)));
  m_menu_app.items().push_back(MenuElem("_Reset All",
															Gtk::AccelKey("a"),
    													sigc::bind( app_slot, Viewer::R_ALL)));
  m_menu_app.items().push_back(MenuElem("_Quit", 
															Gtk::AccelKey("q"),
    													sigc::mem_fun(*this, &AppWindow::hide)));

	Gtk::RadioButtonGroup radioModeGroup;  

	m_menu_mode.items().push_back(Gtk::Menu_Helpers::RadioMenuElem(
															 radioModeGroup,
															 "Position/Orientation",
															 Gtk::AccelKey("p"),
    													 sigc::bind(mode_slot, Viewer::POS_ORI)));
	m_menu_mode.items().push_back(Gtk::Menu_Helpers::RadioMenuElem(
															 radioModeGroup,
															 "Joints",
															 Gtk::AccelKey("j"),
    													 sigc::bind(mode_slot, Viewer::JOINTS)));

	m_menu_edit.items().push_back(MenuElem("_Undo",
															Gtk::AccelKey("u"),
    													sigc::bind( edit_slot, Viewer::UNDO)));
	m_menu_edit.items().push_back(MenuElem("_Redo",
															Gtk::AccelKey("r"),
    													sigc::bind( edit_slot, Viewer::REDO)));
	

	m_menu_options.items().push_back(Gtk::Menu_Helpers::CheckMenuElem
																	("_Circle", 
																	Gtk::AccelKey("c"), 
																	sigc::bind(option_slot, Viewer::CIRCLE)));
	m_menu_options.items().push_back(Gtk::Menu_Helpers::CheckMenuElem
																	("_Z-buffer", 
																	Gtk::AccelKey("z"), 
																	sigc::bind(option_slot, Viewer::Z_BUFFER)));
	m_menu_options.items().push_back(Gtk::Menu_Helpers::CheckMenuElem
																	("_Backface cull", 
																	Gtk::AccelKey("b"), 
																	sigc::bind(option_slot, Viewer::BACKF)));
	m_menu_options.items().push_back(Gtk::Menu_Helpers::CheckMenuElem
																	("_Frontface cull", 
																	Gtk::AccelKey("f"), 
																	sigc::bind(option_slot, Viewer::FRONTF)));


  // Set up the menu bar
  m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Application", m_menu_app));
	m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Mode", m_menu_mode));
  m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Edit", m_menu_edit));
  m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Options", m_menu_options));
  // Pack in our widgets



  
  // First add the vertical box as our single "top" widget
  add(m_vbox);

	labelBox.pack_start(information, Gtk::PACK_SHRINK);

  // Put the menubar on the top, and make it as small as possible
  m_vbox.pack_start(m_menubar, Gtk::PACK_SHRINK);
	m_vbox.pack_start(labelBox, Gtk::PACK_SHRINK);

  // Put the viewer below the menubar. pack_start "grows" the widget
  // by default, so it'll take up the rest of the window.
  m_viewer.set_size_request(300, 300);
  m_vbox.pack_start(m_viewer);

  show_all();

	sigc::slot0<bool> slow_tick_slot = sigc::mem_fun(*this, &AppWindow::refreshLabels);
	sigc::connection sGameConn = Glib::signal_timeout().connect(slow_tick_slot, 50);
}

bool AppWindow::refreshLabels(){

	if (m_viewer.status == 0) information.set_text("");
	else if (m_viewer.status == 1) information.set_text("Can't undo");
	else if (m_viewer.status == 2) information.set_text("Can't redo");
	
	return 1;
}
