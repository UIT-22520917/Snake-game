#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>
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
    int speed= 200;
    int currentDirection; // Biến lưu hướng hiện tại

    CONRAN() {
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 9; A[1].y = 10;
        A[2].x = 8; A[2].y = 10;
        Diem = 0;
        currentDirection = 0; // Khởi tạo hướng ban đầu
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

    void DiChuyen(int &Huong) {
        // Kiểm tra nếu hướng mới là ngược lại hướng hiện tại
        if ((Huong == 0 && currentDirection == 2) || 
            (Huong == 2 && currentDirection == 0) || 
            (Huong == 1 && currentDirection == 3) || 
            (Huong == 3 && currentDirection == 1)) {
            Huong = currentDirection; // Giữ nguyên hướng hiện tại nếu hướng mới là ngược lại
        } else {
            currentDirection = Huong; 
        }

        // Lưu vị trí trước khi di chuyển
        Point prevHead = A[0];

        // Di chuyển thân rắn
        for (int i = DoDai - 1; i > 0; i--) {
            A[i] = A[i - 1];
        }

        // Di chuyển đầu rắn theo hướng
        if (Huong == 0) A[0].x = A[0].x + 1;    // Đi sang phải
        if (Huong == 1) A[0].y = A[0].y + 1;    // Đi xuống
        if (Huong == 2) A[0].x = A[0].x - 1;    // Đi sang trái
        if (Huong == 3) A[0].y = A[0].y - 1;    // Đi lên

        // Đi xuyên qua bản đồ (công dụng giới hạn)
        if (A[0].x >= MaxX-1) A[0].x = 1;  // Nếu ra ngoài bên phải, xuất hiện bên trái
        if (A[0].x < 1) A[0].x = MaxX - 2;  // Nếu ra ngoài bên trái, xuất hiện bên phải
        if (A[0].y >= MaxY-1) A[0].y = 1;  // Nếu ra ngoài dưới, xuất hiện trên
        if (A[0].y < 1) A[0].y = MaxY - 2;  // Nếu ra ngoài trên, xuất hiện dưới

        // Kiểm tra va chạm với thân rắn
        for (int i = 1; i < DoDai; i++) {
            if (A[0].x == A[i].x && A[0].y == A[i].y) {
                // Reset to previous state if collision detected
                A[0] = prevHead;
                DoDai--; // Giảm độ dài rắn
                break;
            }
        }

        if (vaCham()) {
            Sleep(1000); // dừng 1 giây cho người dùng thấy tại sao end game
            EndGame();
        }
    }   

   void taoMoi() {
    bool valid = false;  // Biến kiểm tra xem vị trí thức ăn có hợp lệ không
    while (!valid) {
        // Sinh ra tọa độ thức ăn ngẫu nhiên
        food.x = rand() % (MaxX - 2) + 1; // X trong khoảng từ 1 đến MaxX - 2
        food.y = rand() % (MaxY - 2) + 1; // Y trong khoảng từ 1 đến MaxY - 2

        // Kiểm tra xem thức ăn có trùng với thân rắn không
        valid = true;  // Giả định thức ăn hợp lệ
        for (int i = 0; i < DoDai; i++) {
            if (A[i].x == food.x && A[i].y == food.y) {
                valid = false;  // Nếu thức ăn trùng với thân, set lại valid = false và thoát khỏi vòng lặp
                break;
            }
        }
    }
}


    void An() {
        // Kiểm tra nếu đầu rắn ăn thức ăn
        if (A[0].x == food.x && A[0].y == food.y) {
            DoDai++;    // Tăng độ dài rắn
            Diem++;     // Tăng điểm
            speed-= 5;
            taoMoi();   // Sinh thức ăn mới
        }
    }

    bool vaCham() {
        // Kiểm tra va chạm của đầu rắn với thân
        for (int i = 1; i < DoDai; i++) {
            if (A[0].x == A[i].x && A[0].y == A[i].y) 
                if (A[0].x == A[2].x && A[0].y == A[2].y) return false;
                else
            return true;
        }
        return false;
    }

    void EndGame() {
        system("cls"); // Xóa màn hình
        cout << "Game Over" << endl;
        cout << "Score: " << Diem << endl;
        Sleep(1000);
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
        Sleep(r.speed);
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
