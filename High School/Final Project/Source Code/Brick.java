
public class Brick extends Piece { //brick class, subclass of piece

	protected boolean destroyed = false; // boolean, holds whether or not the brick is destroyed
	protected int powerup; //powerup value
	protected boolean powerupUsed = false; //boolean, holds whether or not the powerup was used
			
	protected Brick(int px, int py, int szX, int szY, Particle[][]a) { //constructor, creates a brick object
		super(px, py, szX, szY,a); //calls the constructor from the superclass
		
	}

	protected void destroy (){ //method that destroys the brick
		destroyed = true;
	}
	
	protected void usePowerup (){ //method that uses the powerup
		powerupUsed = true;
	}
	
	
}
		
			


