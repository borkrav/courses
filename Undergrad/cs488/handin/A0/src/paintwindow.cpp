#include "paintwindow.hpp"

PaintWindow::PaintWindow()
{
  set_title("488 Paint");

  // A utility class for constructing things that go into menus, which
  // we'll set up next.
  using Gtk::Menu_Helpers::MenuElem;
  
  // Set up the application menu
  // The slot we use here just causes PaintWindow::hide() on this,
  // which shuts down the application.
  m_menu_app.items().push_back(MenuElem("_Quit", Gtk::AccelKey("Q"),
    sigc::mem_fun(*this, &PaintWindow::hide)));
  m_menu_app.items().push_back(MenuElem("_Clear", Gtk::AccelKey("C"),
    sigc::mem_fun(&m_canvas, &PaintCanvas::clearShapes)));
  
  
  quitButton = new Gtk::Button("_Quit", true);
  (*quitButton).signal_clicked().connect(sigc::mem_fun(*this,
              &PaintWindow::on_button_clicked));
  
  
  m_canvas.set_colour(0,0,0);
  
  // Set up the tools menu

  // We're going to be connecting a bunch of menu entries to the same
  // function. So, we put a slot corresponding to that function in
  // mode_slot.
  //
  // The type shows that this slot returns void (nothing, and takes
  // one argument, a PaintCanvas::Mode.
  sigc::slot1<void, PaintCanvas::Mode> mode_slot = 
  	sigc::mem_fun(m_canvas, &PaintCanvas::set_mode);
	
  sigc::slot3<void, float, float, float> colour_slot = 
  	sigc::mem_fun(m_canvas, &PaintCanvas::set_colour);

  // Now we set up the actual tools. SigC::bind takes a slot and makes
  // a new slot with one fewer parameter than the one passed to it,
  // and "binds in" the constant value passed.
  //
  // In our case we take the reference to PaintCanvas::set_mode we
  // declared above, and bind in the appropriate mode, making a slot
  // that calls set_mode with the given mode (line/oval/rectangle).

    
  Gtk::RadioButtonGroup radioToolsGroup;  
  Gtk::RadioButtonGroup radioColoursGroup;  
    
    

  m_menu_tools.items().push_back( Gtk::Menu_Helpers::RadioMenuElem(radioToolsGroup, "_Line", Gtk::AccelKey("l"), sigc::bind( mode_slot, PaintCanvas::DRAW_LINE ) ) );
  m_menu_tools.items().push_back( Gtk::Menu_Helpers::RadioMenuElem(radioToolsGroup, "_Oval", Gtk::AccelKey("o"), sigc::bind( mode_slot, PaintCanvas::DRAW_OVAL ) ) );
  m_menu_tools.items().push_back( Gtk::Menu_Helpers::RadioMenuElem(radioToolsGroup, "_Rectangle", Gtk::AccelKey("r"), sigc::bind( mode_slot, PaintCanvas::DRAW_RECTANGLE ) ) );
	
	
	
  m_menu_colour.items().push_back(Gtk::Menu_Helpers::RadioMenuElem(radioColoursGroup,"_Black", 
  	sigc::bind( colour_slot, 0,0,0 ) ) );
  m_menu_colour.items().push_back( Gtk::Menu_Helpers::RadioMenuElem(radioColoursGroup,"_Red", 
  	sigc::bind( colour_slot, 1,0,0 ) ) );
  m_menu_colour.items().push_back( Gtk::Menu_Helpers::RadioMenuElem(radioColoursGroup,"_Green", 
  	sigc::bind( colour_slot, 0,1,0 ) ) );
  m_menu_colour.items().push_back( Gtk::Menu_Helpers::RadioMenuElem(radioColoursGroup,"_Blue", 
  	sigc::bind( colour_slot, 0,0,1 ) ) ); 

  // Set up the help menu
  m_menu_help.items().push_back(MenuElem("_Line Help",
    sigc::mem_fun(*this, &PaintWindow::help_line)));
  m_menu_help.items().push_back(MenuElem("_Oval Help",
    sigc::mem_fun(*this, &PaintWindow::help_oval)));
  m_menu_help.items().push_back(MenuElem("_Rectangle Help",
    sigc::mem_fun(*this, &PaintWindow::help_rectangle)));  
    

  // Set up the menu bar
  m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Application", m_menu_app));
  m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Tools", m_menu_tools));
  m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Colour", m_menu_colour));
  m_menubar.items().push_back(Gtk::Menu_Helpers::MenuElem("_Help", m_menu_help));
  m_menubar.items().back().set_right_justified(true);
  
  
  // Pack in our widgets
  
  // First add the vertical box as our single "top" widget
  add(m_vbox);

  // Put the menubar on the top, and make it as small as possible
  m_vbox.pack_start(m_menubar, Gtk::PACK_SHRINK);

  // Put the canvas below the menubar. pack_start "grows" the widget
  // by default, so it'll take up the rest of the window.
  m_canvas.set_size_request(300, 300);
  m_vbox.pack_start(m_canvas);
  
  m_vbox.pack_start(*quitButton, Gtk::PACK_SHRINK);


  show_all();
}

void PaintWindow::help_line()
{
  const char* message =
    "Drawing a Line\n"
    "\n"
    "To draw a line, press the left mouse button to mark the beginning of the line.  Drag the mouse to the end of the line and release the button.";
  
  Gtk::MessageDialog dialog(*this, message, true, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);

  dialog.run();
}

void PaintWindow::help_oval()
{
    const char* message =
    "Drawing an Oval\n"
    "\n"
    "To draw an oval, press the left mouse button to mark an initial point of the oval.  Drag the mouse to specify the second point on the oval and release the button.";
    
    Gtk::MessageDialog dialog(*this, message, true, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    
    dialog.run();
}

void PaintWindow::help_rectangle()
{
    const char* message =
    "Drawing a Rectangle\n"
    "\n"
    "To draw a rectangle, press the left mouse button to mark a vertex of the rectangle.  Drag the mouse to where you want your diagonal to end and release the button.";
    
    Gtk::MessageDialog dialog(*this, message, true, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    
    dialog.run();
}

void PaintWindow::on_button_clicked()
{
  PaintWindow::hide();
}
