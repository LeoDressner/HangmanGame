#include <graphics.h>
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define X_max 80
#define Y_max 25

#define TRUE 1
#define FALSE 0

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27
#define LEFT 75
#define RIGHT 77

#define MAX_TRIES 6

#define B LIGHTBLUE
#define W WHITE
#define LB LIGHTCYAN
#define LG LIGHTGREEN
#define PK LIGHTMAGENTA
#define R LIGHTRED
#define RR RED

// mao ni ang words to guess and hints
char *words[] = {"RECURSION", "COMPUTER", "GRAPHICS", "PROGRAM",
"COMPILE","INTERFACE","OPTIMIZE","ALGORITHM","DEBUGGER"};
char *hints[] = {
    "Function call itself repeatedly here.",
    "An electronic device for processing data.",
    "What you are using right now for visuals.",
    "A set of instructions to perform a task.",
    "Translating code into a machine code.",
    "Point of system interaction here.",
    "Improving code performance and speed.",
    "Step-by-step problem-solving method.",
    "Tool for finding coding errors.",
};

char wordToGuess[50], hint[100];
char guessedLetters[27];
int guessedCount = 0, triesLeft = MAX_TRIES;

// kani ang randomizer sa words to guess and hints
void initializeGame() {
    // maong 9 na siya kay mao na ang numbers na para guess mao na iyang i randomize
    int index = rand() % 9;  

    strcpy(wordToGuess, words[index]);
    strcpy(hint, hints[index]);
    // ang memset mo set ug value sa tanan part sa memory 
    // mao nang memset kay gi set man nato ang guessedLetters to 0
    // pasabot wala pay na guessed na letters
    memset(guessedLetters, 0, sizeof(guessedLetters));
    guessedCount = 0;
      
      //26 na siya kay 26 letters ang naa sa alphabet na mao imong i guess 
      for(int i=0;i<26;i++){
       guessedLetters[i] = 0;
      }
}

//mao ni mo check sa letter nga gi input sa user ug nasud ba sa guessedLetters
// kung nakit an na mo true(1) siya unya ug wapa mao nang false(0)
int isAlreadyGuessed(char guess) { //ang guess mao nay input sa user
    for (int i = 0; i < guessedCount; i++) {
	if (guessedLetters[i] == guess)
	return 1;
    }
    return 0;
}

// mao ni ang mo draw sa hangman ug magkamali
void drawHangman(int triesLeft) {
    setcolor(WHITE);
    line(50, 100, 150, 100);
    line(150, 100, 150, 150);
    line(40, 300, 170, 300);
    line(50, 100, 50, 300);
    line(50,120,70,100);

    if (triesLeft <= 5) circle(150, 170, 20);
    if (triesLeft <= 4) line(150, 190, 150, 240);
    if (triesLeft <= 3) line(150, 200, 130, 230);
    if (triesLeft <= 2) line(150, 200, 170, 230);
    if (triesLeft <= 1) line(150, 240, 130, 270);
    if (triesLeft == 0) line(150, 240, 170, 270);
}

void drawWord() {
    setcolor(WHITE);
    int x = 270, y = 150;
    for (int i = 0; i < strlen(wordToGuess); i++) {

        // i check niya kung ang current letter na guessed naba by looking  for it in the guessedLetters array
        // if na found niya ang strchr mo return non null pointer and the condition will be true meaning na guess na ang letter
        // kung ang current letter makita sa mga gi guess na which is ang guessedletter ipakita niya ang letter nga na guess
	if (strchr(guessedLetters, wordToGuess[i])) {

             // gi convert ang letter into a string para ma display gamit ang outtextxy
	    char letter[2] = {wordToGuess[i], '\0'};
	    outtextxy(x, y, letter);

        } 
         else {
	    outtextxy(x, y, "_");
	}
         // plusan ug 30 para di mag dikit2 ang underscore ug ang letter na nga na guessed
	x += 30;
    }

    //kani ang pag draw sa hint
    setcolor(W);
    settextstyle(1,HORIZ_DIR,1);
    outtextxy(200,200, hint);

    // kani logo rani sa ubos haha
    setcolor(RR);
    settextstyle(1,HORIZ_DIR,1);
    outtextxy(40,310,"HANGMAN GAME");
}
// kani ang pag draw sa keyboard
void drawKeyboard() {
    int x = 250, y = 250;
    settextstyle(3, HORIZ_DIR, 1);
    for (char c = 'A'; c <= 'Z'; c++) {

	// gi set ang color depende kung na guess naba siya mao na ug na guess na darkgray ang color ug wala pa lightblue
	// kanang ? if na siya nya ang : else na 
	setcolor(isAlreadyGuessed(c) ? DARKGRAY : LIGHTBLUE);

        // pag draw ni sa rectangle keys sa keyboard
	rectangle(x, y, x + 30, y + 30);

        // gi convert niya ang letter into string aron ma display sud sa rectangle 
        // kanang c ang sa for loop na
	char letter[2] = {c, '\0'};
	outtextxy(x + 10, y + 10, letter);

        // nya plus 35 para di mag dikit ang mga rectangles and letters in short keys
	x += 35;
        
         // if muabot nadaw sa letter I ug R i ubos niya ang position sa next key para di magsumpay
	if (c == 'I' || c == 'R') { x = 250; y += 40; }
    }
}
// maoy mo check kung na guess naba sa player tanang letter sa word
int checkWin() {
    
    // the loop will run as long as i is lesser than the length of the string
    // so unless dili ma guess ang word magsige rani ug loop
    for (int i = 0; i < strlen(wordToGuess); i++) {

        // kung ang current letter(wordToGuess[i]) wala pa na guess which is wala pa siya nakita sa guessed letters
        // mo return 0 siya pasabot nga wapa nahuman ang duwa
	if (!strchr(guessedLetters, wordToGuess[i])) return 0;
    }

    // kung tanan letter na guess na mo return 1 na siya kay na true naman pasabot daog na
    return 1;
}
// mag add sa bag ong gi guess na letter
void updateGuessedLetters(char guess) {
    guessedLetters[guessedCount++] = guess; 
    guessedLetters[guessedCount] = '\0';
}


void box(int x1, int y1, int x2, int y2, char color = W, char bkg = 0);
void loading_bar(int d = 60, int n = 60, int x = 5, int y = 5, char clr = B);
void loading();
void menu();

void box(int x1, int y1, int x2, int y2, char color, char bkg) {
    int i;
    textcolor(color);
    textbackground(bkg);
    gotoxy(x1, y1);
    cprintf("%c", 201);
    gotoxy(x2, y1);
    cprintf("%c", 187);
    gotoxy(x1, y2);
    cprintf("%c", 200);
    gotoxy(x2, y2);
    cprintf("%c", 188);

    for (i = x1 + 1; i < x2; i++) {
	gotoxy(i, y1);
	cprintf("%c", 205);
	gotoxy(i, y2);
	cprintf("%c", 205);
    }
    for (i = y1 + 1; i < y2; i++) {
	gotoxy(x1, i);
	cprintf("%c", 186);
	gotoxy(x2, i);
	cprintf("%c", 186);
    }
}

void loading_bar(int d, int n, int x, int y, char clr) {
    textcolor(W + BLINK);
    gotoxy(x + n / 4 - 3, y + 1);
    cprintf("        LOADING...");
    textcolor(clr);

    for (int i = x; i <= x + n; i++) {
	gotoxy(i, y);
	cprintf("%c", 219);
	sound(50 + (i *10));
	delay(50);
	nosound();
    }

    gotoxy(x + n / 4 - 3, y + 1);
    textcolor(W);
    cprintf("     LOADING COMPLETE");

    delay(2000);
}
void loading() {
    char colr[] = {B, LB, LG, PK, R};
    clrscr();

    for (int z = 0; z < 11; ++z) {
	box(2 * z + 1, z + 1, 80 - 2 * z, 24 - z, colr[z % 5]);
	sound(200+(z*50));
	delay(300 - z * 30);
        nosound();
    }
    
    loading_bar(50,35, 23, 12, RR);

    clrscr();
}

void wrongsound() {
    sound(200); 
    delay(300);
    nosound();
}

void winsound() {
    sound(440); 
    delay(200);
    sound(550);
    delay(200);
    sound(660);
    delay(200);
    sound(770);
    delay(200);
    sound(880);
    delay(300);
    nosound();
}

void losesound() {
    sound(300);
    delay(300);
    sound(250);
    delay(300);
    sound(200);
    delay(300);
    sound(150);
    delay(300);
    sound(100);
    delay(500);
    nosound();
}
void menusound() {
    sound(300);
    delay(100);
    nosound();
}

void entersound() {
    sound(500);
    delay(100);
    nosound();
}

void correctsound(){
    sound(600);
    delay(100);
    sound(800);
    delay(100);
    nosound();
}

void escsound(){
   sound(200);
   delay(100);
   nosound();
}
void puthangman() {
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 9);
    int midx, midy;
    midx = getmaxx() / 2;
    midy = getmaxy() / 2;

    setbkcolor(BLACK);
    setcolor(RED);
    outtextxy(100, midy - 105, "HANGMAN");

    setcolor(W);
    settextstyle(1, HORIZ_DIR, 1);
    circle(332, 85, 6); // head
    line(332, 91, 332, 110); // body
    line(332, 95, 340, 103); // right hand
    line(324, 103, 332, 95); // left hand
    line(332, 110, 340, 118); // right leg
    line(324, 118, 332, 110); // left leg
    moveto(280, 45); outtext("+---+");
    moveto(285, 60); outtext("|     |");
    moveto(285, 75); outtext("|");
    moveto(285, 90); outtext("|");
    moveto(285, 105); outtext("|");
    moveto(285, 120); outtext("|");
    moveto(285, 124); outtext("=====");

    setcolor(W);
    rectangle(10, 10, 630, 470);
    setcolor(R);
    rectangle(20, 20, 620, 460);
    setcolor(B);
    rectangle(30, 30, 610, 450);
}
void design() {
    setcolor(W);
    rectangle(10, 10, 630, 470);
    setcolor(R);
    rectangle(20, 20, 620, 460);
    setcolor(B);
    rectangle(30, 30, 610, 450);
    setcolor(RR);
}

void howtoplay() {
    cleardevice();
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
    int midx, midy;
    midx = getmaxx() / 2;
    midy = getmaxy() / 2;

    setbkcolor(BLACK);
    setcolor(RED);
    outtextxy(230, midy - 200, "HANGMAN");

    setcolor(W);
    rectangle(10, 10, 630, 470);
    setcolor(R);
    rectangle(20, 20, 620, 460);
    setcolor(B);
    rectangle(30, 30, 610, 450);

    setcolor(W);
    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(50, midy - 130, "How to Play Hangman:");
    outtextxy(50, midy - 110, "1. Guess the word before you run out of tries.");
    outtextxy(50, midy - 90, "2. Type one letter at a time.");
    outtextxy(50, midy - 70, "3. If the letter is correct, it will be revealed in the");
    outtextxy(80, midy - 50, "word.");
    outtextxy(50, midy - 30, "4. If the letter is incorrect, a part of the hangman is ");
    outtextxy(80, midy - 10, "drawn.");
    outtextxy(50, midy + 10, "5. You have 6 tries in total.");
    outtextxy(50, midy + 30, "6. Guess all the letters correctly to win!");
    outtextxy(50, midy + 50, "Press ESC or ENTER to return to the menu.");

    while (TRUE) {
	if (kbhit()) {
	    char ch = getch();
	    if (ch == ESC||ch==ENTER) {
		entersound();
		break;
	    }
	}
	delay(100);
    }
    closegraph();
    menu();
}

void drawmenu(int selected) {
    const char* menu_items[] = {"Start Game", "How To Play?", "Exit"};
    int yPos = 250;
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);

    for (int i = 0; i < 3; i++) {
	setcolor(i == selected ? W + BLINK : RR);
	outtextxy(230, yPos + i * 50, menu_items[i]);
    }
}

void tamaNaPlease() { //exit ni function
    int selected = 0;
    cleardevice();
    while (TRUE) {
	setbkcolor(BLACK);
	design();

	settextstyle(1, HORIZ_DIR, 4);
	setcolor(RR);
	outtextxy(75, 180, "Are you sure you want to exit?");


	settextstyle(1, HORIZ_DIR, 5);
	setcolor(selected == 0 ? W + BLINK : RR);
	outtextxy(240, 250, "Yes");
	setcolor(selected == 1 ? W + BLINK : RR);
	outtextxy(340, 250, "No");


	if (kbhit()) {
	    char ch = getch();
	    if (ch == 0 || ch == 224) {
		ch = getch();
		if (ch == LEFT) {
		    selected = (selected == 0) ? 1 : 0;
		    menusound();
		} else if (ch == RIGHT) {
		    selected = (selected == 1) ? 0 : 1;
		    menusound();
		}
	    } else if (ch == ENTER) {
	       entersound();
	       if (selected == 0){ exit(0); }
	       else if (selected == 1){ menu(); }
	    } else if (ch == ESC) {
		escsound();
		menu();
	    }
	}
	delay(100);
    }
    closegraph();
}
int playagain();
void startgame();
void menu() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    cleardevice();

    int selected = 0;
    puthangman();

    while (TRUE) {
	drawmenu(selected);

	if (kbhit()) {
	    char ch = getch();
	    if (ch == 0 || ch == 224) {
		ch = getch();
		if (ch == UP) {
		    selected = (selected == 0) ? 2 : selected - 1;
		    menusound();
		} else if (ch == DOWN) {
		    selected = (selected == 2) ? 0 : selected + 1;
		    menusound();
		}
	    } else if (ch == ENTER) {
		entersound();
		if (selected == 0) {
		    delay(300);
		    startgame();
		} else if (selected == 1) {
		    delay(300);
		    howtoplay();
		} else if (selected == 2) {
		    delay(300);
		    tamaNaPlease();
		}
	    } else if (ch == ESC) {
		escsound();
		tamaNaPlease();
	    }
	}

	delay(100);
    }

    closegraph();
}
int playagain() {
    int selected = 0;
     cleardevice();
    while (1) {
	setbkcolor(BLACK);
	design();
	settextstyle(1,HORIZ_DIR,4);
	setcolor(RR);
	outtextxy(90, 180, "Do You Want To Play Again?");

	settextstyle(1, HORIZ_DIR, 5);
	setcolor(selected == 0 ? W + BLINK : RR);
	outtextxy(240, 250, "Yes");
	setcolor(selected == 1 ? W + BLINK : RR);
	outtextxy(340, 250, "No");


	if (kbhit()) {
	    char ch = getch();
	    if (ch == 0 || ch == 224) {
		ch = getch();
		if (ch == LEFT) {
		    selected = (selected == 0) ? 1 : 0;
		    menusound();
		} else if (ch == RIGHT) {
		    selected = (selected == 1) ? 0 : 1;
		    menusound();
		}
	     }
		else if (ch == ENTER) {
		  entersound();
		if (selected == 0) {
		    startgame();
		    getch();
		} else {
		    menu();
		}

		}
	  }
	 delay(100);
    }
}
void win(){
    cleardevice();
    design();
    setcolor(GREEN);
    settextstyle(1,HORIZ_DIR,8);
    outtextxy(150, 140, "You Win!");
    winsound();
    while (!kbhit()) {
    setcolor(WHITE);
    settextstyle(1,HORIZ_DIR,4);
    outtextxy(110, 270, "Press any key to continue...");
    delay(500);

    setcolor(BLACK);
    outtextxy(110, 270, "Press any key to continue...");
    delay(500);
  }
 entersound();
 getch();

}
void lose(){
    cleardevice();
    design();
    setcolor(RED);
    settextstyle(1,HORIZ_DIR,8);
    outtextxy(150, 140, "You Lose!");
    losesound();
    while (!kbhit())
    {
    setcolor(WHITE);
    settextstyle(1,HORIZ_DIR,4);
    outtextxy(110, 270, "Press any key to continue...");
    delay(500);

    setcolor(BLACK);
    outtextxy(110, 270, "Press any key to continue...");
    delay(500);
    }
entersound();
getch();
}

void startgame() {
    cleardevice();
    initializeGame();
    triesLeft = MAX_TRIES;

    while (triesLeft > 0) {
	cleardevice();
	design();
	drawHangman(triesLeft);
	drawWord();
	drawKeyboard();

	char guess = getch();

	 if(guess == ESC){
	   escsound();
	   tamaNaPlease();
	   return;
	 }


	if (guess >= 'a' && guess <= 'z') {
	    guess -= 32;
	} else if (!(guess >= 'A' && guess <= 'Z')) {
	    continue;
	}

	if (isAlreadyGuessed(guess)) continue;

	int correctGuess = 0;
	for (int i = 0; i < strlen(wordToGuess); i++) {
	    if (wordToGuess[i] == guess) {
		correctGuess = 1;
		break;

	    }

	}

	updateGuessedLetters(guess);
	if(correctGuess){
	   correctsound();
	}
	else{
	   triesLeft--;
	   wrongsound();
	}

	if (checkWin()) {
	    design();
	    drawWord();
	    drawHangman(triesLeft);
	    drawKeyboard();
	    delay(300);
	    win();
	    delay(300);
	    playagain();

	}
	delay(100);
    }
    design();
    drawWord();
    drawHangman(triesLeft);
    drawKeyboard();
    delay(300);
    lose();
    delay(300);
    playagain();

}

int main() {
    _setcursortype(_NOCURSOR);
    srand(time(NULL));
    loading();
    menu();
}

