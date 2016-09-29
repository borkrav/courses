import java.awt.event.*; 

public class Piece { //piece class, controls the coordinates, sizes and speeds of various objects

protected int positionX; //integer values for the position, speed and size values of the game piece
protected int positionY;
protected int speedX;
protected int speedY;
protected int sizeX;
protected int sizeY;
protected Particle [][] particles; //the particle array that's associated with the game piece

//
//The following are overloaded constructors for the piece class, The one that's used is dependant on the arguments that are passed in
	protected Piece (int px, int py){ 
		positionX = px;
		positionY = py;
		
	}



	protected Piece (int px, int py,int szX, int szY, Particle [][] a){
		positionX = px;
    	positionY = py;
       	sizeX = szX;
    	sizeY = szY;
    	particles=a;
   	}
	

	protected Piece(int px, int py, int sx, int sy, int szX, int szY) {
    	positionX = px;
    	positionY = py;
    	speedX = sx;
    	speedY = sy;
    	sizeX = szX;
    	sizeY = szY;
    }
//    
    
	
	// move X and move Y methods, these increment the positions by the speed values
	protected void moveX (){
    	
    	positionX += speedX;
    	
    }
	protected void moveY(){
    	
    	positionY += speedY;
    }
    
	// inverse X and inverse Y methods, these reverse the speed of the object. This is used for bounces.
	protected void inverseX (){
       	speedX = -speedX;
    }
    
	protected void inverseY (){
    	speedY = -speedY;
    }
	
	// the following 4 methods double or half the speed of the object in the x/y direction. This is used by the powerup method
	protected void fastX(){
		speedX = speedX*2;
	}
	protected void slowX(){
		speedX = speedX/2;
	}
	protected void fastY(){
		speedY = speedY*2;
	}
	protected void slowY(){
		speedY = speedY/2;
	}
	
    
	protected boolean collisionDetect (Piece hit){ //This is the collision detection method, takes in the piece that's being hit. Returns true if object was hit, returns false if there was no collision
      	
      	int boundryMod=1; // a number to modify the collision boundaries, 1 seems to be the least glitchy
      	
      	// checks if the piece passed the hit pieces' Y coordinates, and inverses the speed if there is a hit
    	if (positionY + sizeY > hit.positionY-boundryMod && positionY < hit.positionY + hit.sizeY +boundryMod && positionX + sizeX > hit.positionX +boundryMod && positionX < hit.positionX + hit.sizeX -boundryMod){
    		
    		inverseY();
    		return true;
    		
    	}
      	// checks if the piece passed the hit pieces' X coordinates, and inverses the speed if there is a hit
    	else if (positionX +sizeX > hit.positionX-boundryMod && positionX < hit.positionX + hit.sizeX +boundryMod && positionY + sizeY > hit.positionY +boundryMod && positionY < hit.positionY + hit.sizeY-boundryMod){
    		
    		inverseX();
    		return true;
    		
    	}
    	
    	else {return false;} // if there was no hit, a false value is returned
    
    	    
    }
    
	protected boolean boundryDetect (int width, int height){ // method that checks the screen boundary collision
    	  	 
    	
    	if (positionX >= width-sizeX-2 || positionX <=0){ // if the ball passes the sides of the screen, the speed is reversed
      		inverseX();
       			    		
    	}
    	if (positionY <=0){ // if the ball passes the top of the screen,  the speed is reversed
       		inverseY();
    	}
    	
    	if (positionY >= height-sizeY*5/2){ //if the piece passes the bottom if the screen, it's destroyed
      		return true; // a true value is returned; the piece is destroyed
    	}
    	else return false; // if the piece didn't go below the screen, a false value is returned
    }
	
	protected void paddleBoundry(int width, int height){ // checks the boundaries for the paddle movement
		if (positionX >= width-sizeX-2 || positionX <=0){ // if the paddle passes the screen boundaries
       		speedX = 0; // the speed is set to zero
		}
	}
	
	protected void paddleHit (Piece hit){ // This is the paddle collision method, this works the same way as the collision detect class, but modified for the paddle. Only the top of the paddle reflects the ball.
		
        int boundryMod =10;
    	
    	if (positionY + sizeY > hit.positionY && positionY < hit.positionY + hit.sizeY && positionX + sizeX > hit.positionX -boundryMod && positionX < hit.positionX + hit.sizeX +boundryMod){
    		
    		inverseY();
    		
    		
    	}
	}

	protected void respawn(){ // This method respawns the piece. - used if the ball goes offscreen
		positionX = 100 + (int)(Math.random()*600); //sets a random x position
		positionY = 450; //sets the original Y position
		speedX = -5; // sets the original speeds and sizes
		speedY = -5;
		sizeX =15;
		sizeY = 15;
	}
	
	
	protected void keyPressed(KeyEvent e) { //method that checks if a key is pressed
       
        int key = e.getKeyCode();
       
        if (key == KeyEvent.VK_LEFT &&positionX>0) { //user presses left, and if the paddle is within the play area, it is given a speed
            speedX = -15;
        }

        if (key == KeyEvent.VK_RIGHT &&positionX<800-sizeX-2) { //user presses right, and if the paddle is within the play area, it is given a speed
        	speedX = 15;
        }
        
       
    }

	protected void keyReleased(KeyEvent e) { //method that checks if a key is released 
		
		int key = e.getKeyCode();
        
        if (key == KeyEvent.VK_LEFT) { //user releases left, paddle is stopped
            speedX = 0;
        }

        if (key == KeyEvent.VK_RIGHT) { //user releases left, paddle is stopped
            speedX = 0;
        }
	}


    
}