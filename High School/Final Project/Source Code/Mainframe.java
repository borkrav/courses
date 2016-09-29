import java.awt.*;
import java.awt.event.*;
import javax.swing.*; 




public class Mainframe extends JFrame implements ActionListener { 
	
	
	public final int width=800; //The width of the frame
	public final int height=650; //The height of the frame
	
	boolean looser; //value that holds whether or not the player lost
	boolean winner; //value that holds whether or not the player won

    int levelCounter; //value that holds the current level number
    Paints set = new Paints(); //instantiates the paint class, holds various colour types
	Board game =new Board(width,height); //instantiates a new board object, using the width and height arguments. Game extends JPanel, so it can be used as a swing component
	JPanel menu = new JPanel (); //creates a panel for the menu
	//creates labels
    JLabel lost; 
	JLabel instructions = new JLabel("Arrow keys to move. Bricks: Red - bad, Blue - good, Green - special, Gray - life, Black - indestructable", JLabel.CENTER);
	JLabel title = new JLabel("Breakout",JLabel.CENTER);
	JLabel win = new JLabel ("You win",JLabel.CENTER);
	JLabel pressStart = new JLabel ("Press Start",JLabel.CENTER);
	JButton start = new JButton("Start game"); //creates the start button

	
    public Mainframe() {
    	
    	super ("Breakout"); // calls the JFrame constructor, sets title of the window
    	
    	
    	
    	setSize (width,height); //sets the size of the JFrame
    	setVisible (true); //sets the JFrame to be visible
    	setDefaultCloseOperation (EXIT_ON_CLOSE); //stops program when window is closed    	
    	setResizable (false); //doesn't allow resizing
    	setLocationRelativeTo (null); //puts the window in the middle of screen
    	
    	game.origin=this; //passes the current instance of mainframe to the game object
    	
   	
    	Font a = new Font("Comic Sans Ms", Font.BOLD, 20); //creates a new font
    	
   
    	start.setFont(a); //sets the font of the start button
    	start.setBackground(Color.RED); //sets the color of the start button

    	
    	start.addActionListener (this); //adds an action listener to the button
  
    	title.setFont(new Font("Comic Sans Ms", Font.BOLD, 125)); //sets the font of the title
    	
    	instructions.setFont(new Font("Comic Sans Ms", Font.BOLD, 15)); //sets the font for the instruction line
    	instructions.setForeground(set.lightYellow); //sets the colour of the instruction line

    	win.setFont(new Font("Comic Sans Ms", Font.BOLD, 20)); //sets the font for the win line
    	win.setForeground(Color.WHITE); //sets the colour of the win line
    	pressStart.setFont(new Font("Comic Sans Ms", Font.BOLD, 20)); //sets the font of the start line
    	pressStart.setForeground(Color.WHITE); // sets the color of the start line
 	
    	add(game); //adds the game component to the JFrame 
    	
    	menu(); //runs the menu method
	   	
    }
    
    public void menu(){
	    
    	menu = new JPanel (); //creates a JPanel for the menu
    	menu.setLayout (new BoxLayout(menu, BoxLayout.PAGE_AXIS)); //sets the layout of the menu panel to box layout, using the center of the panel as the y axis.
    	menu.setBackground (set.darkSilver); //sets the background color
    	
        menu.add(title);  //adds the title component to the panel
  

        menu.add(Box.createRigidArea(new Dimension(0,50))); //adds a blank component to serve as blank space between the components
        lost = new JLabel ("You Lost at level " + levelCounter,JLabel.CENTER); //creates the lose component
        
        lost.setFont(new Font("Comic Sans Ms", Font.BOLD, 20)); //sets the font of the lose text
    	lost.setForeground(Color.WHITE); //sets the color of the lose text
    	
    	
        if (!winner &&!looser){ //if the player didn't lose or win
        	menu.add(pressStart); //adds the start text to the frame   
        }
        
        
        
    	if (winner){ //if the player won
        	menu.add (win); //adds the win text to the panel
        }
    	if (looser){ //if the player lost
    	menu.add(lost);} //adds the lose text to the panel
    	menu.add(Box.createRigidArea(new Dimension(0,50))); //adds blank space
   

    	menu.add(instructions); //adds the instruction line to the panel
    	menu.add(Box.createRigidArea(new Dimension(0,150))); //adds blank space
    	menu.add (start); //adds the start button to the panel
    	
    	//centers all of the component
    	title.setAlignmentX(CENTER_ALIGNMENT);
    	lost.setAlignmentX(CENTER_ALIGNMENT);
    	win.setAlignmentX(CENTER_ALIGNMENT);
    	pressStart.setAlignmentX(CENTER_ALIGNMENT);
    	instructions.setAlignmentX(CENTER_ALIGNMENT);
    	start.setAlignmentX(CENTER_ALIGNMENT);
    	
    	// if the player lost or won
    	if (winner || looser){
    	game.setVisible(false);
		remove(game); //remove the game panel from the JFrame		
		}
    	menu.setVisible(true); //sets the menu panel to be visible
    	add(menu); //adds the menu panel to the JFrame
    }
    
    public void runTheGame(){
    	game.masterReset(); //resets the game
    	add (game); //adds the game panel to the JFrame
    	game.run(); //runs the game
    	game.setVisible(true); //sets the game panel to be visible
		menu.setVisible(false); //sets the menu panel to the invisible
		remove(menu); //removes the menu panel from the JFrame
    }
    
    
    
     
    public void actionPerformed(ActionEvent e){   
    	
	String buttonReader = e.getActionCommand(); //gets the action command
    	
    	if (buttonReader.equals ("Start game")){ //if the user presses the start button
    		runTheGame(); //run the game
    	}
    	
    	
    }
    
    
    public static void main (String args[]){
    	new Mainframe (); //creates a new mainframe
    }
    
    
    
}
