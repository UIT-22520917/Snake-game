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
    Point food;
    int Diem;
    int MaxX = 20; // Chiều rộng bản đồ
    int MaxY = 20; // Chiều cao bản đồ

    CONRAN() {
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 9; A[1].y = 10;
        A[2].x = 8; A[2].y = 10;
        Diem = 0;
        srand(time(0));
        taoMoi(); // Tạo thức ăn ban đầu
    }

    void Ve() {
        // Vẽ rắn
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            cout << "X";
        }

        // Vẽ thức ăn
        gotoxy(food.x, food.y);
        cout << "O";

        // Hiển thị điểm số
        gotoxy(MaxX + 2, 0); // Đặt vị trí hiển thị điểm bên ngoài bản đồ
        cout << "Score: " << Diem;
    }

    void DiChuyen(int Huong) {
        // Di chuyển thân rắn
        for (int i = DoDai - 1; i > 0; i--) {
            A[i] = A[i - 1];
        }

        // Di chuyển đầu rắn theo hướng
        if (Huong == 0) A[0].x = A[0].x + 1;    // Đi sang phải
        if (Huong == 1) A[0].y = A[0].y + 1;    // Đi xuống
        if (Huong == 2) A[0].x = A[0].x - 1;    // Đi sang trái
        if (Huong == 3) A[0].y = A[0].y - 1;    // Đi lên

        // Xử lý cho rắn đi xuyên qua biên bản đồ
        if (A[0].x >= MaxX) A[0].x = 1;        // Nếu ra ngoài phải, xuất hiện bên trái
        if (A[0].x < 1) A[0].x = MaxX - 1;     // Nếu ra ngoài trái, xuất hiện bên phải
        if (A[0].y >= MaxY) A[0].y = 1;        // Nếu ra ngoài dưới, xuất hiện trên
        if (A[0].y < 1) A[0].y = MaxY - 1;     // Nếu ra ngoài trên, xuất hiện dưới

        // Kiểm tra va chạm với thân rắn
        if (vaCham()) EndGame();
    }

    void taoMoi() {
        // Đặt thức ăn trong phạm vi bản đồ, tránh viền
        food.x = rand() % (MaxX - 2) + 1; // X trong khoảng từ 1 đến MaxX - 2
        food.y = rand() % (MaxY - 2) + 1; // Y trong khoảng từ 1 đến MaxY - 2
    }

    void An() {
        // Kiểm tra nếu đầu rắn ăn thức ăn
        if (A[0].x == food.x && A[0].y == food.y) {
            DoDai++;    // Tăng độ dài rắn
            Diem++;     // Tăng điểm
            taoMoi();   // Sinh thức ăn mới
        }
    }

    bool vaCham() {
        // Kiểm tra va chạm của đầu rắn với thân
        for (int i = 1; i < DoDai; i++) {
            if (A[0].x == A[i].x && A[0].y == A[i].y) return true;
        }
        return false;
    }

    void EndGame() {
        system("cls"); // Xóa màn hình
        cout << "Game Over" << endl;
        cout << "Score: " << Diem << endl;
        exit(0); // Kết thúc chương trình
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
        r.Ve();                   // Vẽ rắn, thức ăn và điểm số
        r.DiChuyen(Huong);        // Di chuyển rắn
        r.An();                   // Kiểm tra nếu rắn ăn thức ăn
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

// Hàm đặt vị trí con trỏ trong console
void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}
