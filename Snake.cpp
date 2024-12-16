// Snake.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <windows.h>

int width = 10;
int height = 10;

int fruitCordX, fruitCordY;
int playerScore;

struct Snake
{
    int x;
    int y;
    Snake* next;
};
Snake* head = new Snake();

char side;
bool isGameOver;

void Add(int x, int y) {
    Snake* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    Snake* newSnake = new Snake();
    newSnake->x = x;
    newSnake->y = y;
    newSnake->next = nullptr;
    temp->next = newSnake;
}

bool correctFruitCord() {
    bool correct = true;
    Snake* temp = head;
    while (temp != nullptr) {
        if (temp->x == fruitCordX && temp->y == fruitCordY) {
            correct = false;
        }
        temp = temp->next;
    }
    delete temp;
    return correct;
}

void Initial()
{
    srand(time(NULL));
    isGameOver = false;
    side = 'S';
    head->x = std::rand() % width;
    head->y = std::rand() % height;
    if (head->x - 2 >= 0) {
        Add(head->x - 1, head->y);
        Add(head->x - 2, head->y);
    }
    else {
        Add(head->x + 1, head->y);
        Add(head->x + 2, head->y);
    }
    fruitCordX = std::rand() % width;
    fruitCordY = std::rand() % height;
    if (!correctFruitCord()) {
        if (fruitCordY - 1 >= 0)
            fruitCordY--;
        else fruitCordY++;
    }
    playerScore = 0;
    
}

void UserInput()
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (side!= 'R' && head->x <= head->next->x)
                side = 'L';
            break;
        case 'd':
            if (side != 'L' && head->x >= head->next->x)
                side = 'R';
            break;
        case 'w':
            if (side != 'D')
                side = 'U';
            break;
        case 's':
            if (side != 'U')
                side = 'D';
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}

void Rendering()
{
    system("cls");

    for (int i = 0; i < width + 2; i++)
        std::cout << "-";
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            if (j == 0 || j == width)
                std::cout << "|";
            if (i == head->y && j == head->x)
                std::cout << "O";
            else if (i == fruitCordY && j == fruitCordX)
                std::cout << "A";
            else {
                bool prTail = false;
                Snake* temp = head->next;
                while (temp != nullptr) {
                    if (temp->x == j && temp->y == i) {
                        std::cout << "o";
                        prTail = true;
                    }
                    temp = temp->next;
                }
                delete temp;
                if (!prTail)
                    std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < width + 2; i++)
        std::cout << "-";
    std::cout << std::endl;

    std::cout << "Score: " << playerScore << std::endl;
}

void Moving() {
    int initialX = head->x;
    int initialY = head->y;
    int tailX, tailY;

    switch (side) {
    case 'L':
        head->x--;
        break;
    case 'R':
        head->x++;
        break;
    case 'U':
        head->y--;
        break;
    case 'D':
        head->y++;
        break;
    }

    if (side != 'S'){
        Snake* temp = head->next;
        while (temp != nullptr) {
            if (temp->next == nullptr){
                tailX = temp->x;
                tailY = temp->y;
            }
            int tempX = temp->x;
            int tempY = temp->y;
            temp->x = initialX;
            temp->y = initialY;
            initialX = tempX;
            initialY = tempY;
            temp = temp->next;
        }
        delete temp;
    }

    if (head->x < 0 || head->x == width || head->y < 0 || head->y == height) {
        isGameOver = true;
    }

    Snake* temp = head->next;
    while (temp != nullptr) {
        if (head->x == temp->x && head->y == temp->y)
            isGameOver = true;
        temp = temp->next;
    }
    delete temp;

    if (head->x == fruitCordX && head->y == fruitCordY) {
        srand(time(NULL));
        do {
            fruitCordX = std::rand() % width;
            fruitCordY = std::rand() % height;
        } while (!correctFruitCord());
        Add(tailX, tailY);
        playerScore += 10;
    }
}

int main()
{
    Initial();
    while (!isGameOver) {
        Rendering();
        UserInput();
        Moving();
        Sleep(350);
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
