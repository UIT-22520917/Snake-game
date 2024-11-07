#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;

void gotoxy(int column, int line);
void VeVien(int MaxX, int MaxY);

struct Point {
    int x, y;
};

class CONRAN {
public:
    struct Point A[100];
    int DoDai;
    int MaxX = 20; // Chiều rộng bản đồ
    int MaxY = 20; // Chiều cao bản đồ

    CONRAN() {
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 12; A[2].y = 10;
    }

    void Ve() {
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            cout << "X";
        }
    }

    // missing arrow keys for movement, add collision, limit the area of movement but can go through like a loop
    void DiChuyen(int Huong) {
        for (int i = DoDai - 1; i > 0; i--) {
            A[i] = A[i - 1];
        }

        if (Huong == 0) A[0].x = A[0].x + 1;
        if (Huong == 1) A[0].y = A[0].y + 1;
        if (Huong == 2) A[0].x = A[0].x - 1;
        if (Huong == 3) A[0].y = A[0].y - 1;

        // Đi xuyên qua bản đồ (công dụng giới hạn)
        if (A[0].x >= MaxX) A[0].x = 0;  // Nếu ra ngoài bên phải, xuất hiện bên trái
        if (A[0].x < 0) A[0].x = MaxX - 1;  // Nếu ra ngoài bên trái, xuất hiện bên phải
        if (A[0].y >= MaxY) A[0].y = 0;  // Nếu ra ngoài dưới, xuất hiện trên
        if (A[0].y < 0) A[0].y = MaxY - 1;  // Nếu ra ngoài trên, xuất hiện dưới
    }

    // missing eating food and growing snake, saving points
    void An() {

    }

    // missing collision with snake body
    void vaCham() {

    }
};

int main() {
    CONRAN r;
    int Huong = 0;
    char t;

    while (1) {
        if (kbhit()) {
            t = getch();
            if (t == 'a') Huong = 2;
            if (t == 'w') Huong = 3;
            if (t == 'd') Huong = 0;
            if (t == 's') Huong = 1;
        }
        system("cls");
        VeVien(r.MaxX, r.MaxY);  // Vẽ viền bản đồ
        r.Ve();
        r.DiChuyen(Huong);
        Sleep(300);
    }

    return 0;
}

// Hàm vẽ viền bản đồ
void VeVien(int MaxX, int MaxY) {
    // Vẽ viền trên
    for (int i = 0; i < MaxX; i++) {
        gotoxy(i, 0);
        cout << "#";
    }

    // Vẽ viền dưới
    for (int i = 0; i < MaxX; i++) {
        gotoxy(i, MaxY - 1);
        cout << "#";
    }

    // Vẽ viền trái
    for (int i = 0; i < MaxY; i++) {
        gotoxy(0, i);
        cout << "#";
    }

    // Vẽ viền phải
    for (int i = 0; i < MaxY; i++) {
        gotoxy(MaxX - 1, i);
        cout << "#";
    }
}

void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}
