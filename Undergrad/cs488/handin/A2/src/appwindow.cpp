#include "appwindow.hpp"

AppWindow::AppWindow()
{
  set_title("CS488 Assignment Two");

  // A utility class for constructing things that go into menus, which
  // we'll set up next.
  using Gtk::Menu_Helpers::MenuElem;
  
	


  // Set up the application menu
  // The slot we use here just causes AppWindow::hide() on this,
  // which shuts down the application.
  m_menu_app.items().push_back(MenuElem("_Quit", Gtk::AccelKey("q"),
    sigc::mem_fun(*this, &AppWindow::hide)));

	m_menu_app.items().push_back(MenuElem("_Reset", Gtk::AccelKey("a"),
    sigc::mem_fun(m_viewer, &Viewer::reset_view)));
  
	

	sigc::slot1<void, Viewer::Mode> mode_slot = 
  	sigc::mem_fun(m_viewer, &Viewer::setMode);
	
	Gtk::RadioButtonGroup radioModeGroup;  

	m_menu_mode.items().push_back(Gtk::Menu_Helpers::RadioMenuElem(radioModeGroup, "_Model rotate", Gtk::AccelKey("r"),
    sigc::bind( mode_slot, Viewer::M_ROTATE )));
	m_menu_mode.items().push_back(Gtk::Menu_Helpers::RadioMenuElem(radioModeGroup, "_Model translate", Gtk::AccelKey("t"),
    sigc::bind( mode_slot, Viewer::M_TRANSLATE )));
	m_menu_mode.items().push_back(Gtk::Menu_Helpers::RadioMenuElem(radioModeGroup, "_Model scale", Gtk::AccelKey("s"),
    sigc::bind( mode_slot, Viewer::M_SCALE )));
	m_menu_mode.items().push_back(Gtk::Menu_Helpers::RadioMenuElem(radioModeGroup, "_View rotate", Gtk::AccelKey("o"),
    sigc::bind( mode_slot, Viewer::V_ROTATE )));
	m_menu_mode.items().push_back(Gtk::Menu_Helpers::RadioMenuElem(radioModeGroup, "_View translate", Gtk::AccelKey("n"),
    sigc::bind( mode_slot, Viewer::V_TRANSLATE )));
	m_menu_mode.items().push_back(Gtk::Menu_Helpers::RadioMenuElem(radioModeGroup, "_Perspective", Gtk::AccelKey("p"),
    sigc::bind( mode_slot, Viewer::V_PERSPECTIVE )));
	m_menu_mode.items().push_back(Gtk::Menu_Helpers::RadioMenuElem(radioModeGroup, "_Viewport", Gtk::AccelKey("v"),
    sigc::bind( mode_slot, Viewer::VIEWPORT )));



  // Set up the menu bar
  m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Application", m_menu_app));
	 m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Mode", m_menu_mode));
  
  // Pack in our widgets
  
  // First add the vertical box as our single "top" widget
  add(m_vbox);

  // Put the menubar on the top, and make it as small as possible

	labelBox.pack_start(nearPlane, Gtk::PACK_SHRINK);
	labelBox.pack_start(farPlane, Gtk::PACK_SHRINK);
	labelBox.pack_start(modeLabel, Gtk::PACK_SHRINK);

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

	int im = m_viewer.interactionMode;
	std::string interactionMode;

	switch(im){

	case 0:
		interactionMode = "Model rotate";
		break;
	case 1:
		interactionMode = "Model translate";
		break;
	case 2:
		interactionMode = "Model scale";
		break;
	case 3:
		interactionMode = "View rotate";
		break;
	case 4:
		interactionMode = "View translate";
		break;
	case 5:
		interactionMode = "Perspective";
		break;
	case 6:
		interactionMode = "Viewport";
		break;

}


	std::string np = static_cast<std::ostringstream*>
								( &(std::ostringstream() << m_viewer.nearPlane) )->str();
	std::string fp = static_cast<std::ostringstream*>
								( &(std::ostringstream() << m_viewer.farPlane) )->str();
	nearPlane.set_text("Near : " + np + "    ");
	farPlane.set_text("Far : " + fp + "    ");
	modeLabel.set_text("Mode: " + interactionMode);
	
	return 1;
}


bool AppWindow::on_key_press_event( GdkEventKey *ev )
{
		
	if( ev->keyval == 'a' ) {
		m_menu_mode.items()[0].activate();					
  }

	return Gtk::Window::on_key_press_event( ev );		

}



