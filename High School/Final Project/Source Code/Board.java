// see readme.txt and documentation files for more information
// This is the level value legend. Each of these numbers represent the block type

/*Brick 00 = iron brick
 *Brick 01 = big paddle
 *Brick 02 = small paddle
 *Brick 03 = big ball
 *Brick 04 = small ball
 *Brick 05 = speed ball X
 *Brick 06 = speed ball Y
 *Brick 07 = triple split
 *Brick 08 = +1 life
 *Brick 10 = white
 *Brick 11 = lightYellow
 *Brick 12 = lightOrange
 *Brick 13 = lightred
 *Brick 14 = lightGreen
 *Brick 15 = lightBlue
 *Brick 16 = yellowGreen
*/


import javax.swing.*; 
import java.awt.*; 
import java.awt.event.*; 
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;


public class Board extends JPanel implements ActionListener{

Timer sleep; //creates a timer variable, used for the animation
int width, height; //creates the width and height variables
int key; // holds keys

//these are booleans that indicate whether or not the player activated a powerup
boolean powerup1,powerup2,powerup3,powerup4,powerup5,powerup6,powerup7,powerup8 = false;

Paints set = new Paints(); //instantiates the paint class

boolean ballsplit = false; //this boolean indicates whether or not the ball was split into 3

 
Mainframe origin; //this holds there reference to the original JFrame object

Piece ball = new Piece (500,450,-5,-5,15,15); //creates a piece object that will hold all the ball information
Piece paddle= new Piece (375,540,0,0,100,10); //piece object that holds all the paddle information
Particle [][] particles; //an array of particle objects
Brick [][] bricks = new Brick [10][9]; //an array of brick objects
Random intGen = new Random(); //a random integer generator
Particle create = new Particle (0,0,0,Color.black); // instantiates the particle class

//these objects are used when the split powerup is used

Piece ballPwr1; //piece object that will hold information on ball 2
Piece ballPwr2; //piece object that will hold information on ball 3

int brickWide=9; //sets the width of the brick segment
int brickHigh=10; //sets the height of the brick segment
int levelCount=1; //the current level that the player is on
int lifeCounter = 3; //the amount of lives that the payer has
String levelTag; //the name of the level
String powerupTag = "none"; //the name of the powerup

//GetKeys reader = new GetKeys (); //a keyboard reader, instantiates the getKeys class



    public Board(int w, int h) { // constructor for the board class, takes in width and height parameters.
    
    createPieces(); // creates the pieces
    addKeyListener(new GetKeys()); //adds a key listener to the panel
	setFocusable(true); //sets the panel to be focusable
    setDoubleBuffered (true); //sets the panel to use double buffering
    sleep = new Timer(1, this); //sets the timer to run every 1ms
    
    width =w; 
    height = h;
        
    }
    
    public void run (){ //the method that runs the game
    sleep.start(); //starts the timer
    
   if (lifeCounter ==0){ //if the player runs out of lives
    	sleep.stop(); //stops the timer
        origin.levelCounter = levelCount; //passes the level counter to the JFrame
        origin.looser = true; //passes a lose = true value to the JFrame
    	origin.menu(); //opens the menu
    }
   
   if (levelCount ==9){ //if the player reaches level 9 (there are only 8 levels)
	   sleep.stop(); //stop the timer
	   origin.winner = true; // passes a win = true value to the JFrame
	   origin.menu(); //opens the menu
   }
  
    
    }
    
   
    //action performed class, as long as the timer is running, this code will be executed every 1ms. Used for animation 
    public void actionPerformed(ActionEvent e){  
    	
        doPowerup(); //does the powerup
        paddle.moveX(); //moves the paddle along the X axis
        readCollision (); //reads the collisions
        ball.moveX(); //moves the ball among the X and Y axis
        ball.moveY();  
       if (powerup7){ //if powerup 7 is enabled - ball is split
        ballPwr1.moveX(); //moves the 2 balls
        ballPwr1.moveY();
        ballPwr2.moveX();
        ballPwr2.moveY();
        }  
        if (winCheck()){ //if the level win check returns true
        	levelCount++; //adds 1 to the level counter - goes to the next level
          	if (levelCount==9){run();} //if the level count reaches 9 - the player wins, and the run code is executed     		
        	if (levelCount<9){createPieces();} //creates a new set of pieces, as long as the level counter is below 9
        	resetGame(); //resets the game
        }
    
        if (lifeCounter ==0){ //if the life counter reaches zero
        	run(); //run code is executed
        	
        }
        
        repaint (); //repaints the graphics   	
        }
    
    public void createPieces(){ //method that creates the pieces
       
     for (int i=0; i<brickHigh; i++){  //double forloop that runs though rows and the columns of the 2d brick array
    	for (int j=0; j<brickWide; j++){
    		int [][] level = getLevel(); //gets the level information using file.IO
       		int power = level [i][j]; //gets the powerup value from level info array   		
    		particles = create.createExplosion(80, 2, j*80, i*20); //creates a particle array = holds 360 particles
    		bricks [i][j] = new Brick (j*80+40, i*20, 80,20, particles); //creates a brick object using the forloop coordinates, and using the created particle array
    		bricks [i][j].powerup = power;	//sets the powerup value of the brick	 		 
       	}
    }
     	
    }
    
    public int [][] getLevel (){ //get level method, gets the level info
    	int [][] level = new int [brickHigh][brickWide]; //creates an 2d array, holds the level information
    	Scanner fileReader = null; //creates and initializes a file scanner
    	
		try{fileReader = new Scanner (new File ("Levels//"+levelCount+".txt"));} //sets the target file for the file reader to be the "Levels/levelCounter.txt"	
		catch(FileNotFoundException a){System.out.println("Error, level not found");} //if the file doesnt exist, the error message is printed
		
		int letter=0; //the letter that is being read
		int line=-1; //the line that is being read
		
	    while (fileReader.hasNext ()){ 
	    	
	    	if (line == -1){ //gets the first line of the file, which holds the level tag
	    		levelTag = fileReader.nextLine();
	    		line ++;
	    	}
	    	
	    	if (letter >8){ //if the letter reaches nine, the reader goes to the next line
	    		line ++; 
	    		letter =0; //sets the letter read to zero
	        	}
	    	
	    	
	    	level [line][letter] = fileReader.nextInt(); //fills in the information array
	    	letter++;
	    	
	    }
	
	    fileReader.close();	//closes the reader
		return level; //returns the level array
	    }
    
    
    public boolean winCheck(){ //method that checks if the player won
    	int winCounter = 0; //initial block counter
    	 for (int i=0; i<brickHigh; i++){ //double loop that goes though all the elements in the brick array
    	    	for (int j=0; j<brickWide; j++){
    	    		if (bricks [i][j].destroyed){ //if the brick has been destroyed
    	    			winCounter ++; //adds to the win counter
    	    		}
    	    	
    	    	}
    	 }
    	 if (winCounter ==brickWide*brickHigh){ //if the counter reaches 90, the player won
    		return true;
    	 }
    	 else return false; //if the counter doesn't reach 90, the player hasn't won yet
    	
    }
    
        
    public void paint (Graphics g){ //paint method, paints all the stuff to screen
    
    super.paint (g);
    Graphics2D g2d = (Graphics2D)g; //sets the paint method to 2d mode  
    g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, //turns on antialiasing - this sharpens the edges on everything, makes the game look better
            RenderingHints.VALUE_ANTIALIAS_ON);
    
    g.setFont(new Font("Comic Sans Ms", Font.BOLD, 15)); //creates a new font
   
    g.drawString ("Lives: " + Integer.toString(lifeCounter), 100,600); //draws the life counter to screen
    g.drawString ("Level " + levelCount+ " - " + levelTag, 225,600); // draws the level counter and the level title 
    g.drawString ("Powerup - "+ powerupTag, 550,600); //draws the powerup title
    
    if (powerup7){ //if the ball split powerup is active
    	g.fillOval (ballPwr1.positionX,ballPwr1.positionY,ballPwr1.sizeX,ballPwr1.sizeY); //draws ball 2 and ball3
    	g.fillOval (ballPwr2.positionX,ballPwr2.positionY,ballPwr2.sizeX,ballPwr2.sizeY);
    }
    
    g.fillOval (ball.positionX,ball.positionY,ball.sizeX,ball.sizeY); //draws the ball
    g2d.setPaint (Color.black); //sets the paint to black
    
    g.fillRect (paddle.positionX,paddle.positionY,paddle.sizeX,paddle.sizeY); //draws the paddle
    
    
    
    
    for (int i=0; i<brickHigh; i++){ //double forloop that runs through all the elements of the 2d block array (90 times)
    	for (int j=0; j<brickWide; j++){
    		
    	
    	if (bricks[i][j].destroyed && bricks[i][j].powerup!=0){ //if the brick is destroyed, and is not set to indestructable
    		
    		for (int k=0; k<80; k++){ //double forloop that runs trough all the elements of the 2d particle array (360 times)
    			for (int l=0; l<2; l++){
    				if (bricks [i][j].particles[k][l].boundryCheck() ){ //if the particle is within the screen boundaries
    		g2d.setPaint (bricks [i][j].particles[k][l].color); //sets the draw color to the particles color
    		
    		if (bricks[i][j].powerup == 1 ||bricks[i][j].powerup== 3 ||bricks[i][j].powerup==5){ //if the power up is beneficial
    		g2d.setPaint(set.darkBlue);	 // sets the draw color to blue
    		}
    		if (bricks[i][j].powerup == 2 ||bricks[i][j].powerup== 4 ||bricks[i][j].powerup==6){ //if the power up is bad
        		g2d.setPaint(set.darkRed);	//sets the draw color to red
        	}
    		if (bricks[i][j].powerup == 7){ // if the power up is the special 3-ball spit type
        		g2d.setPaint(set.darkGreen); //sets the draw color to green	
        	}
    		
    		if (bricks[i][j].powerup ==8){ //if its a life power up
    			g2d.setPaint(set.darkSilver); //sets the draw color to silver
    		}
    		g.drawRect (bricks [i][j].particles[k][l].xCoord, bricks [i][j].particles[k][l].yCoord,2,2); //draws the particle as a small square
       		bricks [i][j].particles[k][l].animate(); //animates the particle
    		
    				}
    		}
   		}
    		
    		
    		bricks[i][j].positionX= -1000; //sets the destroyed bricks position to be off screen
    		bricks[i][j].positionY= -1000;
    		bricks[i][j].sizeX = 0; //sets the size of the destroyed brick to zero
    		bricks[i][j].sizeY = 0;
    		
    		
    	} 
    			
       	if (bricks[i][j].powerup==0){ // if the brick is indistructable
    	g2d.setPaint (set.darkGrey); // sets the color to dark gray
    	}
    	
       	
       	
    	else if (bricks [i][j].powerup == 1 ||bricks [i][j].powerup == 3 ||bricks [i][j].powerup == 5){ // if the power up brick is good
    		g2d.setPaint (set.darkBlue); //sets the color of the brick to blue
    		
    		//the following code runs if the powerup brick has been destroyed and if the powerup has not been used yet
    		//the powerup boolean is activated, and the powerup is set to used
    		
    		if (bricks [i][j].powerup == 1 &&bricks[i][j].destroyed == true && bricks[i][j].powerupUsed == false){ 
    			powerup1 = true;
    			bricks[i][j].usePowerup();
    		}
    		if (bricks [i][j].powerup == 3 &&bricks[i][j].destroyed == true && bricks[i][j].powerupUsed == false){
    			powerup3 = true;
    			bricks[i][j].usePowerup();
    		}
    		if (bricks [i][j].powerup == 5 &&bricks[i][j].destroyed == true && bricks[i][j].powerupUsed == false){
    			powerup5 = true;
    			bricks[i][j].usePowerup();
    		}
    		
    	}
    	       	   	
    	else if (bricks [i][j].powerup == 2||bricks [i][j].powerup == 4||bricks [i][j].powerup == 6){ // if the power up brick is bad
    		g2d.setPaint (set.darkRed);	//sets the color of the brick to red
    		
    		//the following code runs if the powerup brick has been destroyed and if the powerup has not been used yet
    		//the powerup boolean is activated, and the powerup is set to used
    		
        		if (bricks [i][j].powerup == 2 &&bricks[i][j].destroyed == true && bricks[i][j].powerupUsed == false){
        			powerup2 = true;
        			bricks[i][j].usePowerup();
        		}
        		if (bricks [i][j].powerup == 4 &&bricks[i][j].destroyed == true && bricks[i][j].powerupUsed == false){
        			powerup4 = true;
        			bricks[i][j].usePowerup();
        		}
        		if (bricks [i][j].powerup == 6 &&bricks[i][j].destroyed == true && bricks[i][j].powerupUsed == false){
        			powerup6 = true;
        			bricks[i][j].usePowerup();
        		}

        	}
    	
    	else if (bricks [i][j].powerup == 7){ // if the power up brick is special ball split type
    		g2d.setPaint (set.darkGreen); //sets the brick color to green	
    		
    		//the following code runs if the powerup brick has been destroyed and if the powerup has not been used yet
    		//the powerup boolean is activated, and the powerup is set to used
    		
        		if (bricks[i][j].destroyed == true && bricks[i][j].powerupUsed == false){
        			powerup7 = true;
        			bricks[i][j].usePowerup();
        		}

        	}
    	else if (bricks [i][j].powerup == 8){ // if the brick contains a life powerup
    		g2d.setPaint (set.darkSilver);	//sets the color of the brick to silver
    		
    		//the following code runs if the powerup brick has been destroyed and if the powerup has not been used yet
    		//the powerup boolean is activated, and the powerup is set to used
    		
        		if (bricks[i][j].destroyed == true && bricks[i][j].powerupUsed == false){
        			powerup8 = true;
        			bricks[i][j].usePowerup();
        		}

        	}
       	
       	
       	// if the brick contains one of the these powerup numbers, it is a regular brick, and it's color is set accordingly
       	
    	else if (bricks [i][j].powerup == 10){g2d.setPaint (Color.white);}
    	else if (bricks [i][j].powerup == 11){g2d.setPaint (set.lightYellow);}
    	else if (bricks [i][j].powerup == 12){g2d.setPaint (set.lightOrange);}
    	else if (bricks [i][j].powerup == 13){g2d.setPaint (set.lightRed);}
    	else if (bricks [i][j].powerup == 14){g2d.setPaint (set.lightGreen);}
    	else if (bricks [i][j].powerup == 15){g2d.setPaint (set.lightBlue);}
    	else if (bricks [i][j].powerup == 16){g2d.setPaint (set.lightAqua);}
       	
    	
    	g.fillRect (bricks[i][j].positionX,bricks[i][j].positionY,bricks[i][j].sizeX,bricks[i][j].sizeY); //draws the brick
    	g2d.setPaint (Color.black); //sets the color to black
    	g.drawRect (bricks[i][j].positionX,bricks[i][j].positionY,bricks[i][j].sizeX,bricks[i][j].sizeY); //draws the outline of the brick
    	
    	
    	//if the brick contains any powerup
    	if (bricks [i][j].powerup==1||bricks [i][j].powerup==2 ||bricks [i][j].powerup==3||bricks [i][j].powerup==4||bricks [i][j].powerup==5||bricks [i][j].powerup==6 ||bricks [i][j].powerup==7||bricks [i][j].powerup==8 ||bricks [i][j].powerup==0){
    		g2d.setColor(set.white); //sets the color to white
    		
    		//this code draws a white cross on top of the powerup brick. This is used to indicate which bricks have poweups
    		
    		g.drawLine (bricks[i][j].positionX,bricks[i][j].positionY,bricks[i][j].positionX+80,bricks[i][j].positionY+20);
    		g.drawLine (bricks[i][j].positionX,bricks[i][j].positionY+20,bricks[i][j].positionX+80,bricks[i][j].positionY);
    	}
    	
      }
    }	
   }
    
    
    
   public void readCollision (){ //this class reads the collisions
	   
	   
	   // these three variables hold the status of the balls - in play or destroyed
	   boolean ballLost = false;
	   boolean ballPwr1Lost = false;
	   boolean ballPwr2Lost = false;
	  
	  ballLost= ball.boundryDetect(800, 600); //checks where the ball is on screen, if it passes the bottom of the screen, its set to destroyed
	  paddle.paddleBoundry(800, 600); //checks if the paddle is within the boundries
	  ball.paddleHit(paddle); //checks if the ball hit the paddle
	   
	   if (powerup7){ //if ball split powerup is active
	
	   ballPwr1Lost = ballPwr1.boundryDetect(800, 600); //checks where the balls are on screen
	   ballPwr2Lost = ballPwr2.boundryDetect(800, 600);	      
	  
	   ballPwr1.paddleHit(paddle); //checks if the balls hit the paddle
	   ballPwr2.paddleHit(paddle);
	    
		   for (int i=0; i<brickHigh; i++){ //runs through the 2d brick array
		    	for (int j=0; j<brickWide; j++){
		    	    	 
		    	 if (ballPwr1.collisionDetect (bricks [i][j]) == true || ballPwr2.collisionDetect (bricks [i][j]) == true ||ball.collisionDetect (bricks [i][j]) == true){ //checks if any of the 3 active balls collided with a brick
		    	 	bricks [i][j].destroy(); //destroys the brick
	    	 	
		    	 }
		    	 
	       	}
		    }
	   } 
	   else{
		   for (int i=0; i<brickHigh; i++){ //runs though the 2d brick array
		    	for (int j=0; j<brickWide; j++){
		    	    	 
		    	 if (ball.collisionDetect (bricks [i][j]) == true){ //checks if the ball hit a brick
		    	 	bricks [i][j].destroy(); //destroys the brick
	    	 	
		    	 }
		    	 
	       	}
		    } 
	   }
	 
	   if(ballLost &&!powerup7){ // if ball one is destroyed, and ball split is not active
			  lifeCounter -=1; //decreases the counter
			  ball.respawn(); //respawns the ball
		  }
	   
	   if (ballPwr1Lost &&  ballPwr2Lost &&powerup7){ //if the ball split powerup balls are destroyed
		   powerup7=false; //disables the powerup
		   ballsplit = false;
	   }
	   
	   else if (ballPwr1Lost &&  ballLost &&powerup7){ //if ball one and two are lost
		   ball = ballPwr2; //sets the remaining ball to the original ball reference
		   ballPwr2 =new Piece(0, 0, 0, 0, 0, 0); // remakes the remaining ball object
		   powerup7=false; //disables the powerup
		   ballsplit = false;
		   
	   }
	   
	   else if (ballPwr2Lost &&  ballLost &&powerup7){ //if ball one and three are lost
		   ball = ballPwr1; //sets the remaining ball to the original ball reference
		   ballPwr1 =new Piece(0, 0, 0, 0, 0, 0); // remakes the remaining ball object
		   powerup7=false; //disables the powerup
		   ballsplit = false;
	   }
   
	   
	   	 	   	   
  }
   
   public void doPowerup (){ // this class does the powerups
	   
	   //note, the powerup is disabled after each execution, to allow the level to have multiple blocks with the same powerup type
	   
   	if (powerup1){ // if big paddle powerup is enabled
   		paddle.sizeX =150; //sets the paddle to be 150 pixels long
   		powerup1 = false; //disables the powerup
   		powerupTag = ("Big Paddle"); //sets the tag
   		}
   	
   	if (powerup2){ // if the small paddle powerup is enabled
   		paddle.sizeX =50; //sets the paddle to be 50 pixels long
   		powerup2 = false;
   		powerupTag = ("Small Paddle");
   		}
   	if (powerup3){ //if the big ball powerup is enabled
   		ball.sizeX = 30; //sets the appropriate ball size
   		ball.sizeY = 30;
   		powerup3 = false;
   		if (powerup7){ //if ball split is enabled
   			ballPwr1.sizeX = 30; //sets the other two balls to the same size
   	   		ballPwr1.sizeY = 30;
   	     	ballPwr2.sizeX = 30;
	   		ballPwr2.sizeY = 30;
   		}
   		powerupTag = ("Big Ball");
   		}
   	
   	//same thing as above, but for small ball powerup
   	if (powerup4){
   		ball.sizeX = 5;
   		ball.sizeY = 5;
   		powerup4 = false;
   		if (powerup7){
   			ballPwr1.sizeX = 5;
   	   		ballPwr1.sizeY = 5;
   	     	ballPwr2.sizeX = 5;
	   		ballPwr2.sizeY = 5;
   		}
   		powerupTag = ("Small Ball");
   		}
   	
   
   	if (powerup5){ // if the slow ball powerup is enabled
   		ball.slowX(); //slows the ball
   		ball.slowY();
   		powerup5 = false;
   		if (powerup7){ // if ball split is enabled
   			ballPwr1.slowX(); // slows the other two balls
   	   		ballPwr1.slowY();
   	     	ballPwr2.slowX();
	   		ballPwr2.slowY();
   		}
   		powerupTag = ("Slow Ball");
   		}
   	
   	//same thing as above, but for fast ball powerup
   	if (powerup6){
   		ball.fastX();
   		ball.fastY();
   		powerup6 = false;
   		if (powerup7){
   			ballPwr1.fastX();
   	   		ballPwr1.fastY();
   	     	ballPwr2.fastX();
	   		ballPwr2.fastY();
   		}
   		powerupTag = ("Fast Ball");
   		}
   	
   	if (powerup7 && !ballsplit){ //if ball split powerup is enabled, and isn't aready enabled
   	//creates two balls	
   	ballPwr1 = new Piece(ball.positionX, ball.positionY, -ball.speedX, ball.speedY, ball.sizeX, ball.sizeY);
   	ballPwr2 = new Piece(ball.positionX, ball.positionY, -ball.speedX, -ball.speedY, ball.sizeX, ball.sizeY);
    ballsplit = true; //sets the ball split powerup to enabled - prevents the balls from being split multiple times when this powerup is used more then once on a level
    
    powerupTag = ("Ball Split");
   	}
   	
   	if (powerup8){ // if the +1 life powerup is enabled
   		lifeCounter +=1; //adds one to the life count
   		powerup8 = false;
   		powerupTag = ("+1 Life");
   	}
    	
   }
   
   public void resetGame(){ //this method resets the game after the reaches the next level
	   ball.positionX = 400;//resets the ball position
	   ball.positionY = 400;
	   ball.speedX = -5;//resets the ball speed
	   ball.speedY = -5;
	   ballPwr1 =new Piece(0, 0, 0, 0, 0, 0); //resets and turns off the ball slit powerup
	   ballPwr2 =new Piece(0, 0, 0, 0, 0, 0);
	   powerup7=false;
	   ballsplit = false;
	   ball.sizeX = 15; //resets the ball size
	   ball.sizeY = 15;
	   
   }
   
   public void masterReset(){ // this method resets the game every time the player starts a new game
	   lifeCounter =3; //resets the lives
	   levelCount =1; //resets the levels
	   createPieces(); //creates the pieces
	   ball = new Piece (500,450,-5,-5,15,15); //recreates the ball and the paddle
	   paddle= new Piece (375,540,0,0,100,10);
	   
   }
   
   
         
   private class GetKeys extends KeyAdapter { //this is the getKeys class, it gets keyboard inputs from the user
   	
	   
	   //checks for key pressed and key released events and applies them to the paddle object
        public void keyPressed(KeyEvent e) {
            paddle.keyPressed(e); 
                       
        }
        public void keyReleased(KeyEvent e) {
            paddle.keyReleased(e);
    }
   
   }



}
