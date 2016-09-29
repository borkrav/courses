#include "appwindow.hpp"
#include <iostream>

AppWindow::AppWindow()
{
  set_title("488 Tetrominoes on the Wall");

  // A utility class for constructing things that go into menus, which
  // we'll set up next.
  using Gtk::Menu_Helpers::MenuElem;
  
  // Set up the application menu
  // The slot we use here just causes AppWindow::hide() on this,
  // which shuts down the application.

	m_menu_app.items().push_back(MenuElem("_New Game", Gtk::AccelKey("n"),
    sigc::mem_fun(m_viewer, &Viewer::newGame)));
		
	m_menu_app.items().push_back(MenuElem("_Reset Game", Gtk::AccelKey("r"),
    sigc::mem_fun(m_viewer, &Viewer::resetGame)));
		
	m_menu_app.items().push_back(MenuElem("_Quit", Gtk::AccelKey("q"),
    sigc::mem_fun(*this, &AppWindow::hide)));
	
	sigc::slot1<void, Viewer::Mode> mode_slot = 
  	sigc::mem_fun(m_viewer, &Viewer::setMode);
	
	
	sigc::slot1<void, int> speed_slot = 
  	sigc::mem_fun(m_viewer, &Viewer::setSpeed);
	
	Gtk::RadioButtonGroup radioSpeedGroup;  
    
  m_menu_speed.items().push_back( Gtk::Menu_Helpers::RadioMenuElem(radioSpeedGroup, "_Slow", Gtk::AccelKey("1"), sigc::bind( speed_slot, 1 ) ) );
  m_menu_speed.items().push_back( Gtk::Menu_Helpers::RadioMenuElem(radioSpeedGroup, "_Medium", Gtk::AccelKey("2"), sigc::bind( speed_slot, 2 ) ) );
  m_menu_speed.items().push_back( Gtk::Menu_Helpers::RadioMenuElem(radioSpeedGroup, "_Fast", Gtk::AccelKey("3"), sigc::bind( speed_slot, 3 ) ) );
	
	m_menu_buffering.items().push_back( Gtk::Menu_Helpers::CheckMenuElem("_Double buffer", Gtk::AccelKey("B"), sigc::mem_fun(m_viewer, &Viewer::toggleBuffering) ) );

	
	// sets up the Draw Mode menu bar
	m_menu_drawMode.items().push_back(MenuElem("_Wire-frame", Gtk::AccelKey("w"),
    sigc::bind( mode_slot, Viewer::WIREFRAME )));
	m_menu_drawMode.items().push_back(MenuElem("_Face", Gtk::AccelKey("f"),
    sigc::bind( mode_slot, Viewer::FACE )));
	m_menu_drawMode.items().push_back(MenuElem("_Multicoloured", Gtk::AccelKey("m"),
    sigc::bind( mode_slot, Viewer::MULTICOLOURED )));

  // Set up the menu bar
  m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Application", m_menu_app));
	m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Draw Mode", m_menu_drawMode));
  m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Speed", m_menu_speed));
	m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Buffering", m_menu_buffering));

	
  // Pack in our widgets
  
  // First add the vertical box as our single "top" widget
  add(m_vbox);

  // Put the menubar on the top, and make it as small as possible
  m_vbox.pack_start(m_menubar, Gtk::PACK_SHRINK);

  // Put the viewer below the menubar. pack_start "grows" the widget
  // by default, so it'll take up the rest of the window.
  m_viewer.set_size_request(300, 600);
  m_vbox.pack_start(m_viewer);

  show_all();
}

bool AppWindow::on_key_press_event( GdkEventKey *ev )
{
        // This is a convenient place to handle non-shortcut
        // keys.  You'll want to look at ev->keyval.

	// An example key; delete and replace with the
	// keys you want to process
	
			//left is 65361
			//up is 65362
			//right is 65363
			//down is 65364
			//space is 32
			

        if( ev->keyval == 65361 ) {
								m_viewer.controls(1);
								return Gtk::Window::on_key_press_event( ev );						
        }
				
				if( ev->keyval == 65362 ) {
								m_viewer.controls(2);
                return Gtk::Window::on_key_press_event( ev );							
        }
				
				if( ev->keyval == 65363 ) {
								m_viewer.controls(3);
                return Gtk::Window::on_key_press_event( ev );
               
								
        }
				
				if( ev->keyval == 65364 ) {
								m_viewer.controls(4);
                return Gtk::Window::on_key_press_event( ev );
               
								
        }
				
				if( ev->keyval == 32 ) {
								m_viewer.controls(5);
                return Gtk::Window::on_key_press_event( ev );
                
								
        }
				
				else {
                return Gtk::Window::on_key_press_event( ev );
        }
}
