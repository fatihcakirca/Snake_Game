#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

using namespace std;

// Oyun alanýnýn boyutlarý
const int width = 50;
const int height = 25;

// Yýlanýn baþý, meyve ve kuyruðunun pozisyonlarýný tutan YAPI
struct Position
{
    int x, y;
};

class SnakeGame
{
private:
    bool gameOver;          // Oyunun bitiþ durumu
    int score;              // Oyuncunun skoru
    Position head;          // Yýlanýn baþ pozisyonu
    Position fruit;         // Meyvenin pozisyonu
    Position tail[100];     // Yýlanýn kuyruðu
    int tailLength;         // Kuyruk uzunluðu
    enum Direction
    {
        STOP = 0, LEFT, RIGHT, UP, DOWN
    }
    dir;    // Yönler

public:
    SnakeGame() : gameOver(false), score(0), tailLength(0), dir(STOP)
    {
        // Yýlanýn baþýný oyun alanýnýn ortasýna yerleþtirme
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
        gameOverScreen();    // Oyun bittiðinde ekraný gösterir
    }

private:
    // Rastgele bir pozisyonda meyve oluþturan metot
    void spawnFruit() {
        fruit.x = rand() % width;
        fruit.y = rand() % height;
    }

    // Oyun ekranýný çizen metot
    void draw()
    {
        system("cls");    // Konsolu temizleme

        // Üst sýnýr çizgisi
        for (int i = 0; i < width + 2; i++)
            cout << "-";
        cout << endl;

        // Oyun alanýný çizme
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    cout << "|";    // Sol sýnýr

                if (i == head.y && j == head.x)
                    cout << "O";    // Yýlanýn baþý
                else if (i == fruit.y && j == fruit.x)
                    cout << "*";    // Meyve
                else {
                    bool isTail = false;
                    // Kuyruk parçalarýný adým adým çizme
                    for (int k = 0; k < tailLength; k++)
                    {
                        if (tail[k].x == j && tail[k].y == i) {
                            cout << "o";
                            isTail = true;
                            break;
                        }
                    }
                    if (!isTail)
                        cout << " "; // Boþ alan
                }

                if (j == width - 1)
                    cout << "|"; // Sað sýnýr
            }
            cout << endl;
        }

        // Alt sýnýr çizgisi
        for (int i = 0; i < width + 2; i++)
            cout << "-";
        cout << endl;
        cout << endl;

        // Skoru gösterme
        cout << "SCORE: " << score << endl;
    }

    // Kullanýcý girdisini alan metot
    void input()
    {
        if (_kbhit())    // Bir tuþa basýldýðýný kontrol eder
        {
            switch (_getch())    // Basýlan tuþa göre iþlem yapar
            {
            case 'a': dir = (dir != RIGHT) ? LEFT : dir; break;  // Sol
            case 'd': dir = (dir != LEFT) ? RIGHT : dir; break;  // Sað
            case 'w': dir = (dir != DOWN) ? UP : dir; break;     // Yukarý
            case 's': dir = (dir != UP) ? DOWN : dir; break;     // Aþaðý
            case 'x': gameOver = true; break;                    // Oyunu bitir
            }
        }
    }

    // Oyun mantýðýný iþleyen metot
    void logic()
    {
        // Kuyruðun hareketini güncelleme
        Position prev = head;
        Position prev2;
        for (int i = 0; i < tailLength; i++)
        {
            prev2 = tail[i];
            tail[i] = prev;
            prev = prev2;
        }

        // Yýlanýn baþýný hareket ettirme
        switch (dir)
        {
        case LEFT: head.x--; break;
        case RIGHT: head.x++; break;
        case UP: head.y--; break;
        case DOWN: head.y++; break;
        default: break;
        }

        // Sýnýrlarý kontrol etme ve wrap-around uygulama
        if (head.x >= width)
            head.x = 0;
        else if (head.x < 0)
            head.x = width - 1;

        if (head.y >= height)
            head.y = 0;
        else if (head.y < 0)
            head.y = height - 1;

        // Kuyruk ile çarpýþmayý kontrol etme
        for (int i = 0; i < tailLength; i++)
        {
            if (tail[i].x == head.x && tail[i].y == head.y) {
                gameOver = true;
            }
        }

        // Meyve yeme kontrolü
        if (head.x == fruit.x && head.y == fruit.y)
        {
            score += 5;    // Skoru artýrýr
            spawnFruit();   // Yeni bir meyve oluþturur
            tailLength++;   // Kuyruðu uzatýr
        }
    }

    // Oyun bitti ekranýnýn metodu
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
