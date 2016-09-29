Requirements:
This game uses a lot of particles, which are CPU intensive. To get optimal performance, run the game on at least a 2.0 GHz CPU. Required files: Levels folder, Board.java, Brick.java, Mainframe.java, Paints.java, Particle.java, Piece.java

Instructions:
If running a game from a JDK, run from the Mainframe class.  
The paddle is controlled with the left and right arrow keys. The object of the game is to destroy all of the bricks by bouncing a ball into them.

Special bricks:

Red power ups (white cross):
Fast ball – doubles the ball speed
Small ball – makes the ball small
Small paddle – makes the paddle small

Blue power ups (white cross):
Slow ball – halves the ball speed
Big ball – makes the ball big
Big paddle – makes the paddle big

Green power ups (white cross):
Triple split – splits the ball into three

Gray power ups (white cross):
+1life – grants the player one extra life

All bricks without the white cross are regular bricks.


Known bugs:

The ball “rolls” on the paddle when it hits it at a certain angle.

The ball glitches though, and sometimes gets stuck on the indestructible bricks. This happens when the ball hits the brick at a certain angle.

Level editing guide:

To edit a level, open up the Levels folder, and open the file you would like to change. 
To change the brick types, change the appropriate number.

The level layout looks like this:

level name
xx xx xx xx xx xx xx xx xx 
xx xx xx xx xx xx xx xx xx 
xx xx xx xx xx xx xx xx xx 
xx xx xx xx xx xx xx xx xx 
xx xx xx xx xx xx xx xx xx 
xx xx xx xx xx xx xx xx xx 
xx xx xx xx xx xx xx xx xx 
xx xx xx xx xx xx xx xx xx 
xx xx xx xx xx xx xx xx xx 
xx xx xx xx xx xx xx xx xx 


Legend:
Brick 00 = iron brick
Brick 01 = big paddle
Brick 02 = small paddle
Brick 03 = big ball
Brick 04 = small ball
Brick 05 = speed ball X
Brick 06 = speed ball Y
Brick 07 = triple split
Brick 08 = +1 life
Brick 10 = white
Brick 11 = light yellow
Brick 12 = light orange
Brick 13 = light red
Brick 14 = light green
Brick 15 = light blue
Brick 16 = yellow green

