//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of paddle in pixels
#define paddlew 80
#define paddleh 10

// height and width of bricks in pixels
#define brickw 40
#define brickh 20

// radius of ball
#define radius 10

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GLabel initLife(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
void updateLife(GWindow widow, GLabel life, int lives);
GObject detectCollision(GWindow window, GOval ball);

int i,j;
double velx,vely;
 
int main(int argc,char*argv[])
{
    bool god=false;
    // seed pseudorandom number generator
    srand48(time(NULL));
    
    if(argc>2)
    {
    return 1;
    }
    
    else if(argc==2 && strcmp(argv[1],"GOD")==0)
    {
    god=true;
    }
    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);
    
    // instantiate no of lives
    GLabel life = initLife(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
 
    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // velocity in x and y direction
    velx=2.0;
    vely=2.0;

    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
    	updateScoreboard(window, label, points);
        updateLife(window, life, lives);
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
            {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
                {
                // ensure paddle follows the cursor
                double x = getX(event) - getWidth(paddle)/2;
                setLocation(paddle, x, HEIGHT-paddleh);
                }
            }
            
    move(ball,velx,vely);
    pause(10);
    
    if(god==true)
    	{
    	setLocation(paddle, getX(ball)-getWidth(ball), HEIGHT-paddleh);
    	}
    
    GObject object = detectCollision(window, ball);
        
    if (object != NULL)
        {
            // If the ball hits the paddle
            if (object == paddle)
            {
                vely = -1*vely;
            }
            
            // If the ball hits a block
            else if (strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                vely = -1*vely;
                
                // After breaking 5 bricks player starts getting 1 extra point for each brick
                points=points+((50-bricks)/5)+1;
                updateScoreboard(window, label, points);
                bricks--;                
            }
        }
   
    // bounce off right edge of window
    if (getX(ball) + getWidth(ball) >= getWidth(window))
    	{
    	velx = -velx;
    	}

    // bounce off left edge of window
    else if (getX(ball) <= 0)
        {
        velx = -velx;
        }
    
    // bounce off the upper edge of window
    else if(getY(ball)+getHeight(ball)/2<=0)
    	{
    	vely = -vely;
    	}
    // if paddle misses the ball 
    else if(getY(ball)+getHeight(ball)>=HEIGHT)
    	{
    	lives--;
    	setLocation(ball, 190, 200);
        updateLife(window, life, lives);
        //move paddle to start
        setLocation(paddle, getWidth(window)/2 - getWidth(paddle)/2, HEIGHT-paddleh);
        waitForClick();
    	}
    }
    
    // Win or lose message after game is over
    if (bricks > 0)
    {
        GLabel gameover = newGLabel("YOU LOSE!");
        setFont(gameover, "Arial-40");
        setColor(gameover, "RED");
        add(window, gameover);
        setLocation(gameover, 100, 400);
    }
    else
    {
        GLabel gameover = newGLabel("YOU WIN!");
        setFont(gameover, "Arial-40");
        setColor(gameover, "GREEN");
        add(window, gameover);
        setLocation(gameover, 100, 400);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
   string brickColors[] = {"RED","00FFFF","YELLOW","BLUE","GREEN"};
   int c=0;
   
   int y=50;
   for(i=0;i<ROWS;i++)
       {
       int x=6;
       for(j=0;j<COLS;j++)
      	   {
      	   GRect brick = newGRect(x + 5, y, 35, 10);
      	   
      	   // Sets colors for brick
      	   setColor(brick,brickColors[c]);
      	   setFilled(brick,true);
           add(window,brick);
           x=x+38;
      	   }
       y=y+15;
       c++;
       }  
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval ball=newGOval(((WIDTH/2)-radius),((HEIGHT/2)-radius),radius*2,radius*2);
    setColor(ball,"black");
    setFilled(ball,true);
    add(window,ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // Position the paddle and decides its dimensions
    GRect paddle = newGRect(WIDTH/2-paddlew/2, HEIGHT-paddleh, paddlew, paddleh); 
    add(window,paddle);
    
    // Adds color to the paddle
    setColor(paddle,"green");
    setFilled(paddle,true);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
// Initialize Glabel
GLabel label=newGLabel(" ");

// Set Location and add color to the label
setLocation(label, (getWidth(window) - getWidth(label)) / 2, (getHeight(window) - getHeight(label)) / 2);
setColor(label, "GREY");
setFont(label, "Arial-20");

add(window,label);
return label;
}

GLabel initLife(GWindow window)
{
GLabel life=newGLabel(" ");

// Set the color and location to display no of lives left
setLocation(life, 360, 20);
setColor(life, "BLACK");
setFont(life, "Aria-25");
add(window,life);
return life;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

// updates no of lives left
void updateLife(GWindow window, GLabel life, int lives)
{

    char s[6];
    sprintf(s, "%i", lives);
    setLabel(life, s);
    setLocation(life, 360, 20);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
