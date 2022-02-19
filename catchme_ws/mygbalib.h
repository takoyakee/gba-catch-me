#include "sprites.h"
#define INPUT                      (KEY_MASK & (~REG_KEYS))



void fillPalette(void)
{
    int     i;

	// Fill the palette in GBA memory
    for (i = 0; i < NCOLS; i++)
        spritePal[i] = palette[i];
}

void fillSprites(void)
{
    int     i;

	// Load all sprites in GBA memory
    for (i = 0; i < 128*16*16; i++){
        spriteData[i] = (sprites[i*2+1] << 8) + sprites[i*2];
	 }
	// draw all sprites on screen, but all of them outside of the screen (starting at position (240,160) the bottom right corner of the GBA screen)
    for(i = 0; i < 128; i++)
        drawSprite(0, i, 240,160);


}


void drawSprite(int numb, int N, int x, int y)
{
	// Same as CA2, make specific sprite (based on its name/numb) appear on screen, as slide number N (each sprite needs a different, arbitrary, N >= 0)
    *(unsigned short *)(0x7000000 + 8*N) = y | 0x2000;
    *(unsigned short *)(0x7000002 + 8*N) = x | 0x4000;
    *(unsigned short *)(0x7000004 + 8*N) = numb*8;
}


void drawSpritesmall(int numb, int N, int x, int y)
{
    // Gift function: displays sprite number numb on screen at position (x,y), as sprite object N
    *(unsigned short *)(0x7000000 + 8*N) = y | 0x2000;
    *(unsigned short *)(0x7000002 + 8*N) = x;
    *(unsigned short *)(0x7000004 + 8*N) = numb*2;
}

//***Drawing functions***//
//PRESS [START] TO PLAY!
void mainScreen(void) {
	 //lives @ top left
	 drawSprite(LIFE_1, 125, 5, 5);
	 drawSprite(LIFE_1, 126, 25, 5);
	 drawSprite(LIFE_1, 127, 45, 5);
	 int sec = 45;
	 //**icecreams**//
	 int startpos = 42;
	 drawSprite(28, 55, startpos, sec);		
	 drawSprite(29, 54, startpos+10, sec);
	 drawSprite(30, 53, startpos+20, sec);		
	 drawSprite(31, 52, startpos+30, sec);		
	 drawSprite(32, 51, startpos+40, sec);		
	 drawSprite(33, 50, startpos+50, sec);		
	 drawSprite(34, 49, startpos+60, sec);		
	 drawSprite(35, 48, startpos+70, sec);		
	 drawSprite(36, 47, startpos+80, sec);		
	 drawSprite(37, 46, startpos+90, sec);		
	 drawSprite(38, 45, startpos+100, sec);		
	 drawSprite(39, 44, startpos+110, sec);		
	 drawSprite(40, 43, startpos+120, sec);		
	 drawSprite(41, 42, startpos+130, sec);		
	 //top row:
	 drawSprite(10, 116, 47, 80);		//P
	 drawSprite(11, 115, 54, 80);		//R
	 drawSprite(12, 114, 61, 80);		//E
	 drawSprite(13, 113, 68, 80);		//S
	 drawSprite(13, 112, 75, 80);		//S
	 drawSprite(14, 111, 82, 80);		//[
	 drawSprite(13, 110, 89, 80);		//S
	 drawSprite(15, 109, 96, 80);		//T
	 drawSprite(16, 108, 103, 80);	//A
	 drawSprite(11, 107, 110, 80);	//R
	 drawSprite(15, 106, 117, 80);	//T
	 drawSprite(17, 105, 124, 80);	//]
	 drawSprite(15, 104, 131, 80);	//T
	 drawSprite(18, 103, 138, 80);	//O
	 drawSprite(10, 102, 152, 80);	//P
	 drawSprite(19, 101, 159, 80);	//L
	 drawSprite(16, 100, 166, 80);	//A
	 drawSprite(20, 99, 173, 80);		//Y
	 drawSprite(21, 98, 180, 80);		//!

	 //initialises decision arrow at the top row
	 //drawSprite(42, 75, 40, 80);		// >
	 //drawSprite(43, 74, 185, 80);		// <

	 //second row:
	 drawSprite(7, 73, 75, 100);		//I 
	 drawSprite(8, 72, 82, 100);		//N 
	 drawSprite(13, 71, 89, 100);		//S
	 drawSprite(15, 70, 96, 100);		//T
	 drawSprite(11, 69, 103, 100);	//R
	 drawSprite(9, 68, 110, 100);		//U
	 drawSprite(44, 67, 117, 100);	//C 
	 drawSprite(15, 66, 124, 100);	//T
	 drawSprite(7, 65, 129, 100);		//I
	 drawSprite(18, 64, 136, 100);	//O
	 drawSprite(8, 63, 143, 100);		//N

	 //third row:
	 drawSprite(44, 62, 89, 120);			//C
	 drawSprite(11, 61, 96, 120);			//R
	 drawSprite(12, 60, 103, 120);		//E
	 drawSprite(6, 59, 111, 120);	      //D
	 drawSprite(7, 58, 116, 120);			//I
	 drawSprite(15, 57, 123, 120);		//T
	 drawSprite(13, 56, 130, 120);		//S
}

//Instruction menu
void drawInstruction(void){
	 int topleft = 10;
	 int firstrow = 50;
	 int secondrow = 80;
	 int thirdrow = 140;
	 //top left:
	 drawSprite(7, 47, 5, topleft);			//I 
	 drawSprite(8, 48, 12, topleft);			//N 
	 drawSprite(13, 49, 19, topleft);		//S
	 drawSprite(15, 50, 26, topleft);		//T
	 drawSprite(11, 51, 33, topleft);		//R
	 drawSprite(9, 52, 40, topleft);			//U
	 drawSprite(44, 53, 47, topleft);		//C 
	 drawSprite(15, 54, 54, topleft);		//T
	 drawSprite(7, 55, 59, topleft);			//I
	 drawSprite(18, 56, 66, topleft);		//O
	 drawSprite(8, 57, 73, topleft);			//N
	
	 // first row:
	 drawSprite(10, 0, 47, firstrow);		//P
	 drawSprite(11, 1, 54, firstrow);		//R
	 drawSprite(12, 2, 61, firstrow);		//E
	 drawSprite(13, 3, 68, firstrow);		//S
	 drawSprite(13, 4, 75, firstrow);		//S
	 drawSprite(43, 5, 87, firstrow);		// <
	 drawSprite(42, 6, 92 , firstrow);		// >
	 drawSprite(15, 7, 102, firstrow);	   //T
	 drawSprite(18, 8, 109, firstrow);	   //O
	 drawSprite(5, 9, 122, firstrow);      //M
	 drawSprite(18, 10, 130, firstrow);	   //O
	 drawSprite(4, 11, 138, firstrow);     //V
	 drawSprite(12, 12, 146, firstrow);		//E

	 //second row:
	 drawSprite(13, 13, 47, secondrow);		//S
	 drawSprite(15, 14, 55, secondrow);		//T
	 drawSprite(16, 15, 63, secondrow);		//A
	 drawSprite(44, 16, 71, secondrow);		//C
	 drawSprite(45, 18, 79, secondrow);		//K
	 drawSprite(26,58, 91, secondrow);		//7
	 drawSprite(22,59, 100, secondrow);		//x
	 drawSprite(34, 19, 110, secondrow-5);	   //(icecream)
	 drawSprite(35, 20, 120, secondrow-5);	   //(icecream)
	 drawSprite(41, 21, 130, secondrow-5);	   //(icecream)
	 drawSprite(15, 22, 148, secondrow);	   //T
	 drawSprite(18, 23, 156, secondrow);	   //O
	 drawSprite(23, 24, 171, secondrow);    //W:
	 drawSprite(7, 25, 177, secondrow);		//I
	 drawSprite(8, 26, 185, secondrow);    //N


	 drawSprite(10, 33, 5, thirdrow);		//P
	 drawSprite(11, 34, 12, thirdrow);		//R
	 drawSprite(12, 35, 19, thirdrow);		//E
	 drawSprite(13, 36, 26, thirdrow);		//S
	 drawSprite(13, 37, 33, thirdrow);		//S
	 drawSprite(22, 38, 45, thirdrow);		//X
	 drawSprite(15, 39, 57, thirdrow);		//T
	 drawSprite(18, 40, 64, thirdrow);		//O
	 drawSprite(11, 41, 76, thirdrow);		//R
	 drawSprite(12, 42, 83, thirdrow);		//E
	 drawSprite(15, 43, 90, thirdrow);		//T
	 drawSprite(9, 44, 97, thirdrow);		//U
	 drawSprite(11, 45, 104, thirdrow);		//R
	 drawSprite(8, 46, 111, thirdrow);		//N

}

//Instruction menu
void drawCredits(void){
	 int topleft = 10;
	 int firstrow = 40;
	 int secondrow = 60;
	 int thirdrow = 140;
	 int thirdrow2 = 80;

	 //top left:
	 drawSprite(44, 47, 5, topleft);			//C
	 drawSprite(11, 48, 12, topleft);		//R 
	 drawSprite(12, 49, 19, topleft);		//E
	 drawSprite(6, 50, 28, topleft);			//D
	 drawSprite(7, 51, 33, topleft);			//I
	 drawSprite(15, 52, 40, topleft);		//T
	 drawSprite(13, 53, 47, topleft);		//S 

	
	 // first row:
	 drawSprite(30, 61, 77, firstrow-5);		//icecream
	 drawSprite(12, 0, 103, firstrow);		//E
	 drawSprite(9, 1, 110, firstrow);		//U
	 drawSprite(3, 2, 117, firstrow);		//G
	 drawSprite(12, 4, 124, firstrow);		//E
	 drawSprite(8, 5, 131, firstrow);		//N
	 drawSprite(12, 6, 138 , firstrow);		//E
	 drawSprite(30, 62, 159, firstrow-5);		//icecream


	 //second row:
	 drawSprite(33, 63, 77, secondrow-5);		//icecream
	 drawSprite(20, 13, 97, secondrow);		//Y
	 drawSprite(16, 14, 105, secondrow);	//A
	 drawSprite(8, 15, 113, secondrow);		//N
	 drawSprite(19, 16, 124, secondrow);	//L
	 drawSprite(7, 18, 129, secondrow);		//I
	 drawSprite(8, 22, 136, secondrow);		//N
	 drawSprite(3, 23, 143, secondrow);		//G
	 drawSprite(33, 64, 159, secondrow-5);		//icecream

	 drawSprite(38, 65, 77, thirdrow2-5);		//icecream
	 drawSprite(24, 33, 97, thirdrow2);		//Z 
	 drawSprite(16, 34, 106, thirdrow2);	//A
	 drawSprite(44, 35, 113, thirdrow2);	//C
	 drawSprite(25, 36, 122, thirdrow2);	//H 
	 drawSprite(16, 37, 131, thirdrow2);	//A
	 drawSprite(11, 38, 138, thirdrow2);	//R
	 drawSprite(20, 39, 145, thirdrow2);	//Y
	 drawSprite(38, 66, 159, thirdrow2-5);		//icecream

	 drawSprite(10, 40, 5, thirdrow);		//P
	 drawSprite(11, 41, 12, thirdrow);		//R
	 drawSprite(12, 42, 19, thirdrow);		//E
	 drawSprite(13, 43, 26, thirdrow);		//S
	 drawSprite(13, 44, 33, thirdrow);		//S
	 drawSprite(22, 45, 45, thirdrow);		//X
	 drawSprite(15, 46, 57, thirdrow);		//T
	 drawSprite(18, 54, 64, thirdrow);		//O
	 drawSprite(11, 55, 76, thirdrow);		//R
	 drawSprite(12, 56, 83, thirdrow);		//E
	 drawSprite(15, 57, 90, thirdrow);		//T
	 drawSprite(9, 58, 97, thirdrow);		//U
	 drawSprite(11, 59, 104, thirdrow);		//R
	 drawSprite(8, 60, 111, thirdrow);		//N



}

void drawGameover(void){
	 int top = 65;
	 int bot = 140;
	 drawSprite(3, 117, 77, top); 	//G 
	 drawSprite(16, 118, 86, top); 	//A
	 drawSprite(5, 119, 96, top); 	//M
	 drawSprite(12, 120, 103, top);	//E
	 drawSprite(18, 121, 116, top);	//O
	 drawSprite(4, 122, 124, top);	//V
	 drawSprite(12, 123, 131, top);	//E
	 drawSprite(11, 124, 138, top);	//R

	 drawSprite(10, 116, 47, bot);	//P
	 drawSprite(11, 115, 54, bot);	//R
	 drawSprite(12, 114, 61, bot);	//E
	 drawSprite(13, 113, 68, bot);	//S
	 drawSprite(13, 112, 75, bot);	//S
	 drawSprite(14, 111, 82, bot);	//[
	 drawSprite(13, 110, 89, bot);	//S
	 drawSprite(15, 109, 96, bot);	//T
	 drawSprite(16, 108, 103, bot);	//A
	 drawSprite(11, 107, 110, bot);	//R
	 drawSprite(15, 106, 117, bot);	//T
	 drawSprite(17, 105, 124, bot);	//]
	 drawSprite(15, 104, 131, bot);	//T
	 drawSprite(18, 103, 138, bot);	//O
	 drawSprite(5, 102, 152, bot);	//M
	 drawSprite(16, 101, 162, bot);	//A
	 drawSprite(7, 100, 167, bot);	//I
	 drawSprite(8, 99, 174, bot);		//N

}

void drawgameCompleted(void){
	 int bot = 140;
	 drawSprite(33, 88, 74, 65);
	 drawSprite(3, 87, 104, 50); 		//G
	 drawSprite(16, 86, 113, 50); 	//A
	 drawSprite(5, 85, 122, 50); 		//M 
	 drawSprite(12, 84, 129, 50);		//E
	 drawSprite(44, 83, 90, 70);			//C
	 drawSprite(18, 82, 97, 70);			//O
	 drawSprite(5, 81, 106, 70);			//M 
	 drawSprite(10, 80, 113, 70);			//P
	 drawSprite(19, 79, 120, 70);			//L
	 drawSprite(12, 78, 127, 70);			//E
	 drawSprite(15, 77, 134, 70);			//T
	 drawSprite(12, 76, 141, 70);			//E
	 drawSprite(33, 75, 150, 65);

	 drawSprite(10, 116, 47, bot);	//P
	 drawSprite(11, 115, 54, bot);	//R
	 drawSprite(12, 114, 61, bot);	//E
	 drawSprite(13, 113, 68, bot);	//S
	 drawSprite(13, 112, 75, bot);	//S
	 drawSprite(14, 111, 82, bot);		//[
	 drawSprite(13, 110, 89, bot);		//S
	 drawSprite(15, 109, 96, bot);		//T
	 drawSprite(16, 108, 103, bot);		//A
	 drawSprite(11, 107, 110, bot);		//R
	 drawSprite(15, 106, 117, bot);		//T
	 drawSprite(17, 105, 124, bot);		//]
	 drawSprite(15, 104, 131, bot);	//T
	 drawSprite(18, 103, 138, bot);	//O
	 drawSprite(5, 102, 152, bot);		//M
	 drawSprite(16, 101, 162, bot);		//A
	 drawSprite(7, 100, 167, bot);		//I
	 drawSprite(8, 99, 174, bot);			//N
}

void drawstageClear(void){
	int bot = 140;
	int top = 65;
	//display stage clear
	drawSprite(33, 98, 57, top-5);
	drawSprite(13, 97, 73, top); 	//S
	drawSprite(15, 96, 82, top); 	//T
	drawSprite(16, 95, 91, top); 	//A
	drawSprite(3, 94, 100, top); 	//G
	drawSprite(12, 93, 109, top); //E
	drawSprite(44, 92, 124, top); 	//C
	drawSprite(19, 91, 133, top); 	//L
	drawSprite(12, 90, 142, top); 	//E
	drawSprite(16, 89, 151, top); 	//A
	drawSprite(11, 88, 160, top); 	//R
	drawSprite(33, 87, 170, top-5);

	drawSprite(10, 116, 81, bot);		//P
	drawSprite(11, 115, 88, bot);		//R
	drawSprite(12, 114, 95, bot);		//E 
	drawSprite(13, 113, 102, bot);	//S 
	drawSprite(13, 112, 109, bot);	//S 
	drawSprite(14, 111, 116, bot);		//[ 
	drawSprite(13, 110, 123, bot);		//S
	drawSprite(15, 109, 130, bot);		//T
	drawSprite(16, 108, 137, bot);		//A
	drawSprite(11, 107, 144, bot);		//R
	drawSprite(15, 106, 151, bot);		//T
	drawSprite(17, 105, 158, bot);		//]

	//redisplay lives
	drawSprite(LIFE_1, 125, 5, 5);
	drawSprite(LIFE_1, 126, 25, 5);
	drawSprite(LIFE_1, 127, 45, 5);	 

}
