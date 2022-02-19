// -----------------------------------------------------------------------------
// C-Skeleton to be used with HAM Library from www.ngine.de
// -----------------------------------------------------------------------------
#include "gba.h"
#include <math.h>
#include "mygbalib.h"
#include <stdlib.h>

// Counts and counters:
// number of object that has fallen. 
int obj_count = 0;
// interruptcount is increased every 0.1s. One object falls every 1s
int interruptcount = 8;
// number of object that is in stack
int stack_count = 0;
// number of object that has fallen and is out of screen: each fall count contributes to a loss in heart
int fall_count = 0;
// number of interrupts between each drawFallingObj (y + 1)
int obj_interrupt = 0;
// Game progress
//indication that game is over  (REAL GAME OVER IS WHEN game_over == -1)
int game_over = 0;  
// start = 0 : not in game, start = 1 in game, start = 2: instruction menu, start = 3: credits menu
int start = 0;
// stage = 0 
int stage = 0;

// Positions :
int arrow_pos = 0;
// contains initial position of basket (needs to be reinitialised)
int pos_x = 120, pos_y = 151;
//(arrays)
// contains ALL (whether in stack or fallen) obj's current coordinate 
int obj_coord[20][2];
// contains coord of obj in stack, such that ice cream moves with basket during button interrupt. x : relative to pos_x, y : depends on stack height
int stack_coord[20][2];
// contains obj number in stack, to call such that the same object (icecream) will move with basket during button interrupt
int stack_objnum [20];
// contains deviation from pos_x (current location of basket) for each object in stack (e.g. basket 130, obj1: (+6) 136, obj2: (+8) 138, obj3: 142 (+12)) (needs to be reinitialised)
int stack_dist = 0;
// stores color of each icecream
int obj_color [20];

// Constants (to be varied to fine-tune game or increase difficulty level)
int iheight = 12; //icecreamheight -- to account for the increase in height of stack
int max_y = 150;
//obj_length is the range in which icecream is considered to be stacked
int obj_length = 10;
//threshold for distance between adjacent icecreams
int threshold = 20;
int movespeed = 2;
int rate_objspawn = 8; //time between each obj spawn
// rate at which each drawFallingObj is called
int rate_objfall = 5;
int num_lives = 3;

void checkbutton(void)
{
	// Gift function to show you how a function that can be called upon button interrupt to detect which button was pressed and run a specific function for each button could look like. You would have to define each buttonA/buttonB/... function yourself.
	 //note: using default joypad configuration 1
    u16 buttons = INPUT;

    if ((buttons & KEY_A) == KEY_A)
    {
        //buttonA();
    }
	 //keyb = X
    if ((buttons & KEY_B) == KEY_B)
    {
		if(start == 2){
			clearscreen();
			mainScreen();
			start = 0;
			arrow_pos = 15; //middle value for second row
			drawSprite(42, 75, 70, 100);		// >
	 		drawSprite(43, 74, 153, 100);		// <
		}

		if(start == 3){
			clearscreen();
			mainScreen();
			start = 0;
			arrow_pos = 25; //middle value for second row
			drawSprite(42, 75, 82, 120);		// >
	 		drawSprite(43, 74, 138, 120);		// <
		}
    }

    if ((buttons & KEY_SELECT) ==  KEY_SELECT)
    {
        //buttonSel();
    }

	 //keystart = enter
    if ((buttons & KEY_START) == KEY_START)
    { 
	  //In main menu (start ==0 && stage ==0), check which option is selected
		 //play game
		 if (start == 0 && stage == 0) {
		 	if ( 0 <= arrow_pos && arrow_pos <= 10){
		 		start = 1;
				clearscreen();
 				drawSprite(2,0,pos_x,pos_y);
		 		//lives @ top left
		 		drawSprite(LIFE_1, 125, 5, 5);
	 			drawSprite(LIFE_1, 126, 25, 5);
	 			drawSprite(LIFE_1, 127, 45, 5);
		 	}

			 //instruction page
			 else if ( 11 <= arrow_pos && arrow_pos <= 20){
				clearscreen();
				drawInstruction(); 
				start = 2;
		 	 }

			 // credits page
		 	else if ( 21 <= arrow_pos && arrow_pos <= 28){
				clearscreen();
				drawCredits();
				start = 3;
		 	}
		 }
		 //called when a stage is cleared
		 else if (start == 0 && stage > 0) {
		 	start = 1;
			srand(stage*4+5);
			clearscreen();
 			drawSprite(2,0,pos_x,pos_y);

		 	//lives @ top left
		 	drawSprite(LIFE_1, 125, 5, 5);
	 		drawSprite(LIFE_1, 126, 25, 5);
	 		drawSprite(LIFE_1, 127, 45, 5);
		 }


		 //called when a stage is cleared
		 else if (start == 0 && stage == -1) {
			clearscreen();
			mainScreen();
			stage = 0;
		   arrow_pos = 100;
		 }
    }

    if ((buttons & KEY_RIGHT) == KEY_RIGHT && start == 1)
    {
		 pos_x += movespeed;
		 if (pos_x > 220) {
			 pos_x = 220;
		 }

		 //drawing basket to illustrate moving right
		 drawSprite(2,0,pos_x,pos_y);

		 int s, stack_x = pos_x;
		 for (s = 1; s < stack_count+1; s++){  //indexing is as such due to the nature of the update in drawFallingObj()
			 //draw each obj/icecream in the stack, stack_coord[s][0] is the relative position wrt to pos_x
			 drawSprite(obj_color[stack_objnum[s]], stack_objnum[s], stack_coord[s][0]+pos_x, stack_coord[s][1]);
			 //drawSprite(28, stack_objnum[s], stack_coord[s][0]+pos_x, stack_coord[s][1]);
		 }

    }
    if ((buttons & KEY_LEFT) == KEY_LEFT && start == 1)
    {
		 pos_x -= movespeed;
		 if (pos_x < 0) {
			 pos_x = 0;
		 }
		 //drawing basket to illustrate moving left
		 drawSprite(2,0,pos_x,pos_y);

		 int s;
		 for (s = 1; s < stack_count+1; s++){  //indexing is as such due to the nature of the update in drawFallingObj()
			 //draw each obj/icecream in the stack, stack_coord[s][0] is the relative position wrt to pos_x
			 drawSprite(obj_color[stack_objnum[s]], stack_objnum[s], stack_coord[s][0]+pos_x, stack_coord[s][1]);
			 //drawSprite(28, stack_objnum[s], pos_x+stack_coord[s][0], stack_coord[s][1]);
		 }
    }
	 if ((buttons & KEY_UP) == KEY_UP)
    {	
		//check if in main menu. start == 0 and stage == 0 only in main menu 
	  	 if (start == 0 && stage == 0){
			 arrow_pos -= 1;
			 if( 0 <= arrow_pos && arrow_pos <= 10){		  			// 0 - 10 : range for top row																					
			 	 drawSprite(42, 75, 40, 80);		// >
		 		 drawSprite(43, 74, 185, 80);	// <
			 } else if( 11 <= arrow_pos && arrow_pos <= 20){		// 11 - 20 : range for second row																							
				 drawSprite(42, 75, 70, 100);		// >
	 			 drawSprite(43, 74, 153, 100);	// <
			 } else if( 21 <= arrow_pos && arrow_pos <= 28){	   // 21 - 28 : range for bottom row
				 drawSprite(42, 75, 82, 120);		// >
	 			 drawSprite(43, 74, 138, 120);	// <
			 } else {															//if arrow_pow becomes negative -- loops back to bottom row
				 arrow_pos = 28;
			 }
		}
    }


    if ((buttons & KEY_DOWN) == KEY_DOWN)
    {	
		//check if in main menu. start == 0 and stage == 0 only in main menu 
	  	 if (start == 0 && stage == 0){
			 arrow_pos += 1;
			 if( 0 <= arrow_pos && arrow_pos <= 10){		  			// 0 - 10 : range for top row																					
			 	 drawSprite(42, 75, 40, 80);		// >
		 		 drawSprite(43, 74, 185, 80);		// <
			 } else if( 11 <= arrow_pos && arrow_pos <= 20){		// 11- 20 : range for second row																							
				 drawSprite(42, 75, 70, 100);		// >
	 			 drawSprite(43, 74, 153, 100);	// <
			 } else if( 21 <= arrow_pos && arrow_pos <= 28){	   // 21 - 28 : range for bottom row
				 drawSprite(42, 75, 82, 120);		// >
	 			 drawSprite(43, 74, 138, 120);	// <
			 } else {															//if arrow_pow > 28 -- loops back to top row
				 arrow_pos = 0;
			 }
		}	
    }
}


void stageClear(void) { //not sure if this is the best way to do this but so far the only way i managed to get it to work
	//reinitialise necessary values
	stack_count = 0;
	fall_count = 0;
 	stack_dist = 0;
	pos_x = 120;
	pos_y = 151;
	clearscreen();
	drawstageClear();
	//REG_TM2D = REG_TM2D+75; //Increase falling speed
	rate_objfall -= 1;
	obj_count = 0;
	//start = 0: require pressing enter to continue
	start = 0;
	stage += 1;
	movespeed += 1;
	if (stage == 3){
		rate_objspawn = 7;
	}
	interruptcount = rate_objspawn ;

}

//restartGame() causes a reinitialisation of all values and draws all exisitng objects outside of screen
void restartGame(void){
	 //re-initialise necessary values
	 interruptcount = rate_objspawn ;
	 stack_count = 0;
 	 fall_count = 0;
 	 stack_dist = 0;
	 pos_x = 120;
	 pos_y = 151;
	 obj_count = 0;
	 //start = 0 && stage = -1 --> redirect to main menu after game over/completed
	 start = 0;
	 stage = -1;

	 rate_objfall = 5;
	 rate_objspawn = 8;
	 movespeed = 2;
}
	 
void Gameover(void){
	 clearscreen();
	 drawGameover();
	 restartGame(); 
}


void gameCompleted(void) {
	 clearscreen();
	 drawgameCompleted();
	 restartGame();	
}


//clears all objects on screen
void clearscreen(void){
 	 int i;
	 int oob = 250;
	 for (i = 0; i < 128; i++){
		 drawSprite(0,i, oob, oob);
	 }
}
	 
//function will iterate through obj_coord when called. Since earlier object will either fall/belong to stack, there can be some filtering to the indexing
void drawFallingObj(){

		 //dead keeps track of the number of fallen/ice cream on stack so that we do not iterate through their old coords
		 int dead = stack_count + fall_count;
		 int i;
		 //add 1 as obj num = 0 is RESERVED for basket
		 for (i = dead+1; i < obj_count+1; i++){
			 //checks if obj's y is higher than the current stack, +iheight such that the reference is with the bottom of icecream
			 if (obj_coord[i][1]+iheight >= max_y - stack_count*iheight) {
				 int difference;
				 if (stack_count == 0){
				 	 difference = obj_coord[i][0] - pos_x;
				 }
				 else {
					 difference = obj_coord[i][0] - (stack_dist+pos_x); 
				 }
				 //object has landed on ice cream as the difference in x coordinate is within certain magnitude
				 if (abs(difference) <= obj_length){
					 stack_count+=1;
					 //update in the stack_coord so that we can call during button interrupt
					 stack_dist += difference;
					 stack_coord[stack_count][0] = stack_dist;
					 stack_coord[stack_count][1] = max_y - stack_count*iheight;
					 stack_objnum[stack_count] = i;
					 //draw the icecream in the stack
					 drawSprite(obj_color[i], i, pos_x+stack_dist, stack_coord[stack_count][1]);
					 if (stack_count == 7) { // number of stacks to clear stage
						stageClear();
						if (stage == 4) { //number of stages to clear game
							gameCompleted();
						}
					}
				 }
				 //object has fallen and should be drawn outside of the screen
				 else{
					 fall_count+=1;
					 //CAN BE IMPROVED: TO CONTINUE LETTING ICECREAM FALL UNTIL 160 (THIS IS MORE CHALLENGING THAN IT LOOKS AS ALTERING THE FALL COUNT MAY CAUSE THE INDEXING TO BE HAYWIRE)
					 drawSprite(0,i, 250, 160);
					 //drawSprite(28, i, 250,160);
					 obj_coord[i][0] = 250; //just in case something doesnt go as plan, theorectically dont need update
					 obj_coord[i][1] = 160; 
					 //Function to lose life and display as such (recall that obj num for lives are 125, 126, 127)
					 drawSprite(LIFE_2, 124+fall_count, 5+(fall_count-1)*20 ,5);
					 if (fall_count == num_lives) {
						 Gameover();
						 drawSprite(LIFE_1, 125, 5, 5);
	 					 drawSprite(LIFE_1, 126, 25, 5);
	 					 drawSprite(LIFE_1, 127, 45, 5);	 
					 }
				 } 
			 }
			 //obj's y is not higher than current stack (not in interested zone)
			 else {
				 obj_coord[i][1] += 1;
				 drawSprite(obj_color[i],i, obj_coord[i][0], obj_coord[i][1]);
				 //drawSprite(28, i, obj_coord[i][0], obj_coord[i][1]);
			 }
		 }	
}

//ensures adjacent objects are some distance (threshold) apart
int generateObjx(int prev_x){
	int obj_x = (rand()%149)+40; 
	while (abs(prev_x-obj_x) < threshold){
		obj_x = (rand()%149)+40;
	}
}

void Handler(void)
{
    REG_IME = 0x00; 																												// Stop all other interrupt handling, while we handle this current one

	 // Creates new object every 1s (can be varied according to level)
    if ((REG_IF & INT_TIMER1) == INT_TIMER1 && (interruptcount == rate_objspawn) && (start == 1))
    {	
		obj_count += 1;
		int obj_x = generateObjx(obj_coord[obj_count-1][0]); 															// new object number aka, N
		int obj_y = 0;
		obj_color[obj_count]= (rand()%14)+28;

		//update in obj_coord to iterate during drawFallingObj function
		obj_coord[obj_count][0] = obj_x;
		obj_coord[obj_count][1] = obj_y;
	 	
		drawFallingObj();																	//spawns an icecream randomly along the x axis
		interruptcount = 0; 																//doesnt spawn a new object, keeps the N value constant for now
	 }
  
	 //Rate at which falling object is being drawn
    else if (((REG_IF & INT_TIMER2) == INT_TIMER2) && obj_count > 0 && obj_interrupt == rate_objfall)												
    {		 
		 	 drawFallingObj();
			 obj_interrupt = 0;
	 }

	 //Rate at which falling object is being drawn
    else if (((REG_IF & INT_TIMER2) == INT_TIMER2) && obj_count > 0)													
    {		 
		 	 obj_interrupt++; 
	 }

	 //Every interrupt = 0.1s
    else if ((REG_IF & INT_TIMER1) == INT_TIMER1 && (start == 1)) 
    {		
			 interruptcount++;
	 }


	 //handles button interrupts
    if ((REG_IF & INT_BUTTON) == INT_BUTTON) 
    {		
			 checkbutton(); //regularly checks if we press the arrows or enter keys
	 	
	 }


    REG_IF = REG_IF; // Update interrupt table, to confirm we have handled this interrupt
    
    REG_IME = 0x01;  // Re-enable interrupt handling
}


// -----------------------------------------------------------------------------
// Project Entry Point
// -----------------------------------------------------------------------------
int main(void)
{

    // Set Mode 2
    *(unsigned short *) 0x4000000 = 0x40 | 0x2 | 0x1000;

    // Fill SpritePal
    *(unsigned short *) 0x5000200 = 0;

    //Fill SpriteData
	 fillSprites();
	 //Fill SpritePalette
	 fillPalette();
	 
	 REG_IME = 0x0;

	 mainScreen();

    // Set Handler Function for interrupts and enable selected interrupts
    REG_INT = (int)&Handler;
    REG_IE |=  INT_TIMER1 | INT_BUTTON | INT_TIMER2;

	 KEYCNT |= 0x7FFF;		

    REG_TM1D =	57524;		
    REG_TM1CNT |= TIMER_FREQUENCY_256 | TIMER_INTERRUPTS | TIMER_ENABLE;	

    REG_TM2D = 65000;	
    REG_TM2CNT |= TIMER_FREQUENCY_64 | TIMER_INTERRUPTS | TIMER_ENABLE;

	 REG_IME = 0x1;
    while(1);

	return 0;
}

