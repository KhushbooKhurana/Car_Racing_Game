#include<iostream>  
#include<conio.h>  
#include <windows.h>  
#include <time.h>  
  
#define SCREEN_WIDTH 90  
#define SCREEN_HEIGHT 26  
#define WIN_WIDTH 70   
  
using namespace std;   
   
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);  
COORD CursorPosition;  
  
int enemyY[3];  
int enemyX[3];  
int enemyFlag[3];  
char car[4][4] = { ' ','±','±',' ',   
                    '±','±','±','±',   
                    ' ','±','±',' ',  
                    '±','±','±','±' };   
                      
int carPos = WIN_WIDTH/2;  
int score = 0;   
  
void gotoxy(int x, int y){  
    CursorPosition.X = x;  
    CursorPosition.Y = y;  
    SetConsoleCursorPosition(console, CursorPosition);  
}  
void setcursor(bool visible, DWORD size) {  
    if(size == 0)  
        size = 20;    
      
    CONSOLE_CURSOR_INFO lpCursor;     
    lpCursor.bVisible = visible;  
    lpCursor.dwSize = size;  
    SetConsoleCursorInfo(console,&lpCursor);  
}  
void drawBorder(){    
    for(int i=0; i<SCREEN_HEIGHT; i++){  
        for(int j=0; j<17; j++){  
            gotoxy(0+j,i); cout<<"±";  
            gotoxy(WIN_WIDTH-j,i); cout<<"±";  
        }  
    }   
    for(int i=0; i<SCREEN_HEIGHT; i++){  
        gotoxy(SCREEN_WIDTH,i); cout<<"±";  
    }   
}  
void genEnemy(int ind){  
    enemyX[ind] = 17 + rand()%(33);    
}  
void drawEnemy(int ind){  
    if( enemyFlag[ind] == true ){  
        gotoxy(enemyX[ind], enemyY[ind]);   cout<<"**";    
        gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" ** ";   
        gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"**";   
        gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" ** ";    
    }   
}  
void eraseEnemy(int ind){  
    if( enemyFlag[ind] == true ){  
        gotoxy(enemyX[ind], enemyY[ind]); cout<<"    ";    
        gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"    ";   
        gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"    ";   
        gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"    ";   
    }   
}  
void resetEnemy(int ind){  
    eraseEnemy(ind);  
    enemyY[ind] = 1;  
    genEnemy(ind);  
}  
  
void drawCar(){  
    for(int i=0; i<4; i++){  
        for(int j=0; j<4; j++){  
            gotoxy(j+carPos, i+22); cout<<car[i][j];  
        }  
    }  
}  
void eraseCar(){  
    for(int i=0; i<4; i++){  
        for(int j=0; j<4; j++){  
            gotoxy(j+carPos, i+22); cout<<" ";  
        }  
    }  
}  
   
int collision(){  
    if( enemyY[0]+4 >= 23 ){  
        if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){  
            return 1;  
        }  
    }  
    return 0;  
}   
void gameover(){  
    system("cls");  
    cout<<endl;  
    cout<<"\t\t--------------------------"<<endl;  
    cout<<"\t\t-------- Game Over -------"<<endl;  
    cout<<"\t\t--------------------------"<<endl<<endl;  
    cout<<"\t\tPress any key to go back to menu.";  
    getch();  
}  
void updateScore(){  
    gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;  
}  
  
void instructions(){  
      
    system("cls");  
    cout<<"Instructions";  
    cout<<"\n----------------";  
    cout<<"\n Avoid Cars by moving left or right. ";  
    cout<<"\n\n Press 'a' to move left";  
    cout<<"\n Press 'd' to move right";  
    cout<<"\n Press 'escape' to exit";  
    cout<<"\n\nPress any key to go back to menu";  
    getch();  
}  
  
void play(){  
    carPos = -1 + WIN_WIDTH/2;  //This initializes the car's position to the center of the screen horizontally.
    score = 0;  
   enemyFlag[0] = 1;  // Flags indicating whether enemies are active
    enemyFlag[1] = 0;  // Flags indicating whether enemies are active
    enemyY[0] = enemyY[1] = 1;  //Initial vertical positions of enemies.
        
    system("cls");   
    drawBorder();   
    updateScore();  
    genEnemy(0);  //Generate enemies at the beginning of the game.
    genEnemy(1);  //Generate enemies at the beginning of the game.
      
    gotoxy(WIN_WIDTH + 7, 2);cout<<"Car Game";  
    gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";  
    gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";  
    gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";  
    gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";  
    gotoxy(WIN_WIDTH + 2, 14);cout<<" < Key - Left";  
    gotoxy(WIN_WIDTH + 2, 15);cout<<" > Key - Right";   
      
    gotoxy(18, 5);cout<<"Press any key to start";  
    getch();  
    gotoxy(18, 5);cout<<"                      ";  
      
    while(1){  
        if(kbhit()){  
            char ch = getch();  
            if( ch=='<' ){  
                if( carPos > 18 )  
                    carPos -= 4;  
            }  
            if( ch=='>'  ){  
                if( carPos < 50 )  
                    carPos += 4;  
            }   
            if(ch==27){  
                break;  
            }  
        }   
          
        drawCar();   
        drawEnemy(0);   
        drawEnemy(1);   
        if( collision() == 1  ){  
            gameover();  
            return;  
        }   
        Sleep(50);  
        eraseCar(); //Updates the positions of the enemies, scores, and erases them from their previous positions.
        eraseEnemy(0);
        eraseEnemy(1);
		/*These functions are likely responsible for erasing the previous positions of the enemies from the screen. 
		This ensures that when the enemies move, they don't leave a trail behind them.  */
        
        if( enemyY[0] == 10 )  
            if( enemyFlag[1] == 0 )  
                enemyFlag[1] = 1;  
          
/*This condition checks if the first enemy has reached a certain vertical position (enemyY[0] == 10) and 
if the second enemy flag is not set. If these conditions are met, it sets the flag
for the second enemy (enemyFlag[1]) to 1, indicating that the second enemy should start moving.*/
		  
        if( enemyFlag[0] == 1 )  
            enemyY[0] += 1;
			 
	/* If the flag for the first enemy is set (indicating it should move),it increments the
	 vertical position (enemyY[0]) of the first enemy, effectively moving it down the screen.*/ 
          
        if( enemyFlag[1] == 1 )  
            enemyY[1] += 1;  
            
        //similar to enemy1
           
        if( enemyY[0] > SCREEN_HEIGHT-4 ){  
            resetEnemy(0);  
            score++;  
            updateScore();  
        }  

/*If the first enemy reaches the bottom, it resets the first enemy, 
increments the player's score, and updates the score display.*/

        if( enemyY[1] > SCREEN_HEIGHT-4 ){  
            resetEnemy(1);  
            score++;  
            updateScore();  
        }  
    }  
}  
  
int main()  
{  
    setcursor(0,0);   
    srand( (unsigned)time(NULL));   
/* => This line initializes the random number generator with a seed value.
=> time(NULL) returns the current time in seconds since the Unix epoch (January 1, 1970).
=> Converting it to an unsigned integer ensures that the value is non-negative.
=> This current time value serves as the seed for the random number generator.
=> Using srand() with different seed values ensures that the sequence of random numbers generated by rand() 
will be different each time the program is run, assuming the execution time is different.
=> This is commonly done to introduce variability in the generated random numbers, 
making the behavior of the program less predictable and more interesting, such as in games or simulations.
*/
       
    do{  
        system("cls");  
        gotoxy(10,5); cout<<" -------------------------- ";   
        gotoxy(10,6); cout<<" |        Car Game        | ";   
        gotoxy(10,7); cout<<" --------------------------";  
        gotoxy(10,9); cout<<"1. Start Game";  
        gotoxy(10,10); cout<<"2. Instructions";      
        gotoxy(10,11); cout<<"3. Quit";  
        gotoxy(10,13); cout<<"Select option: ";  
        char op = getche();  
          
        if( op=='1') play();  
        else if( op=='2') instructions();  
        else if( op=='3') exit(0);  
          
    }while(1);  
      
    return 0;  
}
