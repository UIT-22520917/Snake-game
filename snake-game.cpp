#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
void gotoxy( int column, int line );
struct Point{
    int x,y;
};
class CONRAN{
public:
    struct Point A[100];
    int DoDai;
    CONRAN(){
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 9; A[1].y = 10;
        A[2].x = 8; A[2].y = 10;
    }

    void Ve(){
        for (int i = 0; i < DoDai; i++){
            gotoxy(A[i].x,A[i].y);
            cout<<"X";
        }
    }

    // missing arrow keys for movement, add collision, limit the area of movement but can go through like a loop
    void DiChuyen(int Huong){
        for (int i = DoDai-1; i>0;i--)
            A[i] = A[i-1];
        if (Huong==0) A[0].x = A[0].x + 1;
        if (Huong==1) A[0].y = A[0].y + 1;
        if (Huong==2) A[0].x = A[0].x - 1;
        if (Huong==3) A[0].y = A[0].y - 1;
        if (vaCham()) EndGame();

    }

    // missing eating food and growing snake, saving points
    void An(){

    }
    // missing collision with snake body

    bool vaCham() {
        for (int i = 1; i < DoDai; i++) {
            // cout << "Collision detected at: (" << A[0].x << ", " << A[0].y << ")" << endl;
            // for (int i = 0; i < DoDai; i++) {
            //     cout << "Segment " << i << ": (" << A[i].x << ", " << A[i].y << ")" << endl;
            // }
            if (A[0].x == A[i].x && A[0].y == A[i].y) return true;
        }
            
        return false;
    }

    void EndGame() {
        system("cls"); // Clear the screen
        cout << string(100, '\n'); // Move cursor down to simulate full screen
        cout << "Game Over" << endl;
        exit(0); // End the program
    }  
};

int main()
{
    CONRAN r;
    int Huong = 0;
    char t;

    
    while (1){
        if (kbhit()){
            t = getch();
            if (t=='a') Huong = 2;
            if (t=='w') Huong = 3;
            if (t=='d') Huong = 0;
            if (t=='x') Huong = 1;
        }
        system("cls");
        r.Ve();
        r.DiChuyen(Huong);
        Sleep(300);
    }

    return 0;
}


void gotoxy( int column, int line )
  {
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
  }
