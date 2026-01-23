#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

const int WIDTH = 35;
const int HEIGHT = 15;
const int MAX_ZMEIKA = (WIDTH - 2) * (HEIGHT - 2);

// Строки для границ поля
const string TOP_BORDER = "###################################\n";
const string MIDDLE_BORDER = "#                                 #\n";
const string BOTTOM_BORDER = "###################################\n";

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Point {
    int x, y;
};

class Game {
private:
    char field[HEIGHT][WIDTH];
    Point zmeika[MAX_ZMEIKA];
    int zmeika_length;
    Direction zmeika_dir;
    Point food;
    bool isRunning;
    int score;

public:
    Game() {
        srand(time(NULL));
        initGame();
    }

    void initGame() {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                field[y][x] = ' ';
            }
        }
        for (int x = 0; x < WIDTH; x++) {
            field[0][x] = '#';
            field[HEIGHT - 1][x] = '#';
        }
        for (int y = 0; y < HEIGHT; y++) {
            field[y][0] = '#';
            field[y][WIDTH - 1] = '#';
        }

        zmeika_length = 3;
        for (int i = 0; i < zmeika_length; i++) {
            zmeika[i].x = WIDTH / 2;
            zmeika[i].y = HEIGHT / 2 + i;
        }

        zmeika_dir = UP;
        isRunning = true;
        score = 0;

        generateFood();
        updateField();
    }

    void generateFood() {
        bool onZmeika;
        do {
            onZmeika = false;
            food.x = rand() % (WIDTH - 2) + 1;
            food.y = rand() % (HEIGHT - 2) + 1;

            for (int i = 0; i < zmeika_length; i++) {
                if (zmeika[i].x == food.x && zmeika[i].y == food.y) {
                    onZmeika = true;
                    break;
                }
            }
        } while (onZmeika);

        field[food.y][food.x] = 'F';
    }

    void updateField() {
        for (int y = 1; y < HEIGHT - 1; y++) {
            for (int x = 1; x < WIDTH - 1; x++) {
                field[y][x] = ' ';
            }
        }

        field[food.y][food.x] = '0';
        field[zmeika[0].y][zmeika[0].x] = 'O';
        for (int i = 1; i < zmeika_length; i++) {
            field[zmeika[i].y][zmeika[i].x] = 'o';
        }
    }

    void draw() {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

        cout << "Очки: " << score << "                \n";

        cout << TOP_BORDER;

        for (int y = 1; y < HEIGHT - 1; y++) {
            cout << '#';
            for (int x = 1; x < WIDTH - 1; x++) {
                cout << field[y][x];
            }
            cout << "#\n";
        }
        cout << BOTTOM_BORDER;

        cout.flush();
    }

    void move() {
        Point prev[MAX_ZMEIKA];
        for (int i = 0; i < zmeika_length; i++) {
            prev[i] = zmeika[i];
        }

        switch (zmeika_dir) {
        case UP: zmeika[0].y--; break;
        case DOWN: zmeika[0].y++; break;
        case LEFT: zmeika[0].x--; break;
        case RIGHT: zmeika[0].x++; break;
        }

        if (zmeika[0].x <= 0 || zmeika[0].x >= WIDTH - 1 ||
            zmeika[0].y <= 0 || zmeika[0].y >= HEIGHT - 1) {
            isRunning = false;
            return;
        }

        for (int i = 1; i < zmeika_length; i++) {
            if (zmeika[0].x == zmeika[i].x && zmeika[0].y == zmeika[i].y) {
                isRunning = false;
                return;
            }
        }

        for (int i = 1; i < zmeika_length; i++) {
            zmeika[i] = prev[i - 1];
        }

        if (zmeika[0].x == food.x && zmeika[0].y == food.y) {
            if (zmeika_length < MAX_ZMEIKA) {
                zmeika[zmeika_length] = prev[zmeika_length - 1];
                zmeika_length++;
                score += 10;
                generateFood();
            }
        }

        updateField();
    }

    void handleInput() {
        if (_kbhit()) {
            char key = _getch();

            if (key == 0 || key == 224) {
                key = _getch();
                switch (key) {
                case 1: if (zmeika_dir != DOWN) zmeika_dir = UP; break;
                case 2: if (zmeika_dir != UP) zmeika_dir = DOWN; break;
                case 3: if (zmeika_dir != RIGHT) zmeika_dir = LEFT; break;
                case 4: if (zmeika_dir != LEFT) zmeika_dir = RIGHT; break;
                }
            }
            else {
                switch (key) {
                case 'w': case 'W': if (zmeika_dir != DOWN) zmeika_dir = UP; break;
                case 's': case 'S': if (zmeika_dir != UP) zmeika_dir = DOWN; break;
                case 'a': case 'A': if (zmeika_dir != RIGHT) zmeika_dir = LEFT; break;
                case 'd': case 'D': if (zmeika_dir != LEFT) zmeika_dir = RIGHT; break;
                case 5: isRunning = false; break;
                }
            }
        }
    }

    void run() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        system("cls");

        while (isRunning) {
            draw();
            handleInput();
            move();
            Sleep(100);
        }

        cursorInfo.bVisible = TRUE;
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        SetConsoleCursorPosition(hConsole, { 0, HEIGHT + 3 });

        cout << "\nИгра окончена! Счет: " << score << endl;
        cout << "Нажмите любую клавишу..." << endl;
        _getch();
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    cout << "ИГРА ЗМЕЙКА\n" << endl;
    cout << "Управление: WASD (только английская раскладка)" << endl;
    cout << "Нажмите любую клавишу для начала..." << endl;
    _getch();

    Game game;
    game.run();

    return 0;
}