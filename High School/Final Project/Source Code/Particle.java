
import java.awt.Color;

public class Particle { //particle class, used for particles

	public int amountX; //amount of particles in the X direction
	public int amountY; //amount in the Y direction
	public int xCoord; //coordinates of particle
	public int yCoord;
	public double degree; //angle value
	public Color color; //colour value
	
	public Particle(int x, int y, double d, Color c){ //creates a particle object
	
		xCoord = x;
		yCoord = y;
		degree = d;	
		color = c;
	}
	
	public Particle[][] createExplosion(int x, int y, int placeX, int placeY){ //method that creates an array of particles to be used when the brick is destroyed
		//takes in coordinates of the brick and amount of particles
		amountX = x; //takes in the amound values
		amountY = y;
		
		Particle[][] particles = new Particle [amountX] [amountY]; //creates a 2d particle array using the amount values
		
		double counter = -60; //two counters, one for angle, the other for counter
		int colCounter =0;
		
		
		for (int i=0; i< amountX; i++){ //double loop that runs through all the elements of the 2d array
			for (int j=0; j< amountY; j++){
				if (counter ==60){counter =-60;} //angle counter - counts from -60 to 60 degrees
				if (colCounter >2){colCounter =0;} //colour counter - counts from 0 to 2
				if (colCounter ==0){color = Color.red;} //sets the color value according to the counter
				if (colCounter ==1){color = Color.yellow;}
				if (colCounter ==2){color = Color.orange;}
				//fills in the particle array
				particles [i][j] = new Particle (placeX+i, placeY+j, counter, color); //creates particle using the brick coordinates, using the angle counter and the color
				counter+= 1; //adds to the counters
				colCounter +=1;
				
				
			}
		}
		
		return particles; //returns the particle array
		
	}
	
	
	public void animate(){ //animates the particles - this creates the explosion effect, the particles are animated in different directions
		double rad = Math.toRadians(degree); //converts the degree value to radians
		xCoord += Math.random()*25*Math.sin(rad); // increments the X coordinates by a random value * sin of the angle
		yCoord += Math.random()*28*Math.cos(rad); // increments the Y coordinates by a random value * cos of the angle
				
	}
	
	
	public boolean boundryCheck(){ //checks if the particle leaves the screen
		if (xCoord<800 && xCoord>0 && yCoord<600 && yCoord>0){
			return true; //returns true
			
		}
		else return false; //if the particle is on screen, it returns true
	}
	
	

}
