#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

using namespace std;

// Oyun alan�n�n boyutlar�
const int width = 50;
const int height = 25;

// Y�lan�n ba��, meyve ve kuyru�unun pozisyonlar�n� tutan YAPI
struct Position
{
    int x, y;
};

class SnakeGame
{
private:
    bool gameOver;          // Oyunun biti� durumu
    int score;              // Oyuncunun skoru
    Position head;          // Y�lan�n ba� pozisyonu
    Position fruit;         // Meyvenin pozisyonu
    Position tail[100];     // Y�lan�n kuyru�u
    int tailLength;         // Kuyruk uzunlu�u
    enum Direction
    {
        STOP = 0, LEFT, RIGHT, UP, DOWN
    }
    dir;    // Y�nler

public:
    SnakeGame() : gameOver(false), score(0), tailLength(0), dir(STOP)
    {
        // Y�lan�n ba��n� oyun alan�n�n ortas�na yerle�tirme
        head = { width / 2, height / 2 };
        spawnFruit();
    }

    void run()
    {
        while (!gameOver) {
            draw();
            input();
            logic();
            Sleep(20);
        }
        gameOverScreen();    // Oyun bitti�inde ekran� g�sterir
    }

private:
    // Rastgele bir pozisyonda meyve olu�turan metot
    void spawnFruit() {
        fruit.x = rand() % width;
        fruit.y = rand() % height;
    }

    // Oyun ekran�n� �izen metot
    void draw()
    {
        system("cls");    // Konsolu temizleme

        // �st s�n�r �izgisi
        for (int i = 0; i < width + 2; i++)
            cout << "-";
        cout << endl;

        // Oyun alan�n� �izme
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    cout << "|";    // Sol s�n�r

                if (i == head.y && j == head.x)
                    cout << "O";    // Y�lan�n ba��
                else if (i == fruit.y && j == fruit.x)
                    cout << "*";    // Meyve
                else {
                    bool isTail = false;
                    // Kuyruk par�alar�n� ad�m ad�m �izme
                    for (int k = 0; k < tailLength; k++)
                    {
                        if (tail[k].x == j && tail[k].y == i) {
                            cout << "o";
                            isTail = true;
                            break;
                        }
                    }
                    if (!isTail)
                        cout << " "; // Bo� alan
                }

                if (j == width - 1)
                    cout << "|"; // Sa� s�n�r
            }
            cout << endl;
        }

        // Alt s�n�r �izgisi
        for (int i = 0; i < width + 2; i++)
            cout << "-";
        cout << endl;
        cout << endl;

        // Skoru g�sterme
        cout << "SCORE: " << score << endl;
    }

    // Kullan�c� girdisini alan metot
    void input()
    {
        if (_kbhit())    // Bir tu�a bas�ld���n� kontrol eder
        {
            switch (_getch())    // Bas�lan tu�a g�re i�lem yapar
            {
            case 'a': dir = (dir != RIGHT) ? LEFT : dir; break;  // Sol
            case 'd': dir = (dir != LEFT) ? RIGHT : dir; break;  // Sa�
            case 'w': dir = (dir != DOWN) ? UP : dir; break;     // Yukar�
            case 's': dir = (dir != UP) ? DOWN : dir; break;     // A�a��
            case 'x': gameOver = true; break;                    // Oyunu bitir
            }
        }
    }

    // Oyun mant���n� i�leyen metot
    void logic()
    {
        // Kuyru�un hareketini g�ncelleme
        Position prev = head;
        Position prev2;
        for (int i = 0; i < tailLength; i++)
        {
            prev2 = tail[i];
            tail[i] = prev;
            prev = prev2;
        }

        // Y�lan�n ba��n� hareket ettirme
        switch (dir)
        {
        case LEFT: head.x--; break;
        case RIGHT: head.x++; break;
        case UP: head.y--; break;
        case DOWN: head.y++; break;
        default: break;
        }

        // S�n�rlar� kontrol etme ve wrap-around uygulama
        if (head.x >= width)
            head.x = 0;
        else if (head.x < 0)
            head.x = width - 1;

        if (head.y >= height)
            head.y = 0;
        else if (head.y < 0)
            head.y = height - 1;

        // Kuyruk ile �arp��may� kontrol etme
        for (int i = 0; i < tailLength; i++)
        {
            if (tail[i].x == head.x && tail[i].y == head.y) {
                gameOver = true;
            }
        }

        // Meyve yeme kontrol�
        if (head.x == fruit.x && head.y == fruit.y)
        {
            score += 5;    // Skoru art�r�r
            spawnFruit();   // Yeni bir meyve olu�turur
            tailLength++;   // Kuyru�u uzat�r
        }
    }

    // Oyun bitti ekran�n�n metodu
    void gameOverScreen()
    {
        system("cls");
        cout << "GAME OVER!" << endl;
        cout << "SCORE: " << score << endl;
    }
};

int main()
{
    SnakeGame game;
    game.run();

    return 0;
}
