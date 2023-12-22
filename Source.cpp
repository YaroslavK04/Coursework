#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include<windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<time.h>

using namespace std;
using namespace sf;

const int wall = 0, pass = 1, put = 2, razvil = 3, error = 4, player = 5, II = 6;
int x, y, w = 1, z = 1,wid,hei;
double time_II = 0;
clock_t start, stop, start_pl, end_pl;


Font font;
Text text;


void input_size(int* height, int* width); 

bool deadend(int** maze, int height, int width);

void mazemake(int** maze, int height, int width);


void visual(int** maze, int height, int width, RenderWindow* window, bool avto);

void vnes_lider(int time);
void vozvrat(int** maze, int height, int width); 
void poisk_puti(int** maze, int height, int width); 


void II_proxod(int** maze, RenderWindow* window, int height, int width); 

void play(int** maze, int height, int width, RenderWindow* window); 

void input_time_II(RenderWindow* window); 

bool mod_selectino(); 
void return_menu(); 

int main()
{
    srand(time(NULL));
    font.loadFromFile("D:/font/Disket-Mono-Regular.ttf");;
    text.setFont(font);
    return_menu();
	return 0;
}


void input_size(int* height, int* width) { // ���� ������� ���������
    RenderWindow window(VideoMode(800, 400), "Labirint");
    char size[4];
    bool vibor = TRUE;
    int i = -1, enter = 0;



    window.clear(Color::White);
    text.setString(L"������� �������:");
    text.setPosition(40, 90);
    text.setCharacterSize(60);
    text.setFillColor(Color::Red);
    window.draw(text);

    text.setString(L"������: ");
    text.setPosition(40, 200);
    text.setCharacterSize(60);
    text.setFillColor(Color::Blue);
    window.draw(text);
    window.display();



    while (window.isOpen() && enter != 2)
    {

        Event event;
        while (window.pollEvent(event) && enter != 2)
        {

            if (event.type == sf::Event::Closed || enter == 2)
            {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                int m = 1;
                if (vibor) {
                    for (int j = i; j >= 0; j--) {
                        switch (j) {
                        case(0):
                            (*height) += (int(size[j]) - 48) * m;
                            size[j] = NULL;
                            break;
                        case(1):
                            (*height) += (int(size[j]) - 48) * m;
                            m *= 10;
                            size[j] = NULL;
                            break;
                        case(2):
                            (*height) += (int(size[j]) - 48) * m;
                            m *= 10;
                            size[j] = NULL;
                            break;
                        default:
                            cout << "������";
                        }
                    }
                    if ((*height) % 2 == 0) {
                        (*height)++;
                    }
                    vibor = FALSE;
                    enter++;
                    i = -1;
                    Sleep(100);

                }
                else {
                    for (int j = i; j >= 0; j--) {
                        switch (j) {
                        case(0):
                            (*width) += (int(size[j]) - 48) * m;
                            break;
                        case(1):
                            (*width) += (int(size[j]) - 48) * m;
                            m *= 10;
                            break;
                        case(2):
                            (*width) += (int(size[j]) - 48) * m;
                            m *= 10;
                            break;
                        default:
                            cout << "������";
                        }
                    }
                    if ((*width) % 2 == 0) {
                        (*width)++;
                    }
                    enter++;

                }
                Sleep(100);
            }
            if ((event.type == Event::TextEntered && (event.key.code == '0' || event.key.code == '1' || event.key.code == '2' || event.key.code == '3' || event.key.code == '4' || event.key.code == '5' || event.key.code == '6' || event.key.code == '7' || event.key.code == '8' || event.key.code == '9')) || Keyboard::isKeyPressed(Keyboard::LShift) || i == -1) {


                window.clear(Color::White);
                text.setString(L"������� �������:");
                text.setPosition(40, 90);
                text.setCharacterSize(60);
                text.setFillColor(Color::Red);
                window.draw(text);
                if (vibor) {
                    text.setString(L"������: ");
                    text.setPosition(40, 200);
                    text.setCharacterSize(60);
                    text.setFillColor(Color::Blue);
                    window.draw(text);
                }
                else {
                    text.setString(L"������:");
                    text.setPosition(40, 200);
                    text.setCharacterSize(60);
                    text.setFillColor(Color::Blue);
                    window.draw(text);
                }

                text.setCharacterSize(70);
                text.setFillColor(Color::Green);
                if (event.type == Event::TextEntered && (event.key.code == '0' || event.key.code == '1' || event.key.code == '2' || event.key.code == '3' || event.key.code == '4' || event.key.code == '5' || event.key.code == '6' || event.key.code == '7' || event.key.code == '8' || event.key.code == '9')) {
                    i++;
                    size[i] = event.key.code;
                    for (int g = 0; g <= i; g++) {
                        text.setString(size[g]);
                        text.setPosition(330 + g * 50, 190);
                        window.draw(text);
                    }

                }
                if (Keyboard::isKeyPressed(Keyboard::LShift)) {

                    size[i] = NULL;
                    i--;
                    for (int g = 0; g <= i; g++) {
                        text.setString(size[g]);
                        text.setPosition(330 + g * 50, 190);
                        window.draw(text);
                    }
                }
                window.display();
                Sleep(200);


            }

        }

    }
}

bool deadend(int** maze, int height, int width) // ������� �� ������
{
    int a = 0;

    if (x != 1)
    {
        if (maze[y][x - 2] == pass)
            a += 1;
    }
    else a += 1;

    if (y != 1)
    {
        if (maze[y - 2][x] == pass)
            a += 1;
    }
    else a += 1;

    if (x != width - 2)
    {
        if (maze[y][x + 2] == pass)
            a += 1;
    }
    else a += 1;

    if (y != height - 2)
    {
        if (maze[y + 2][x] == pass)
            a += 1;
    }
    else a += 1;

    if (a == 4)
        return 1;
    else
        return 0;
}


void mazemake(int** maze, int height, int width) // �������� ���������
{
    int c, a;
    bool b;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            maze[i][j] = wall;
        }
    }

    x = 3;
    y = 3;
    a = 0;
    while (a < 10000)
    {
        maze[y][x] = pass;
        a++;
        while (1)
        {
            c = rand() % 4;
            switch (c)
            {
            case 0:
                if (y != 1)
                    if (maze[y - 2][x] == wall)  // �����
                    {
                        maze[y - 1][x] = pass;
                        maze[y - 2][x] = pass;
                        y -= 2;
                    }
            case 1:
                if (y != height - 2)
                    if (maze[y + 2][x] == wall)  // ����
                    {
                        maze[y + 1][x] = pass;
                        maze[y + 2][x] = pass;
                        y += 2;
                    }
            case 2:
                if (x != 1)
                    if (maze[y][x - 2] == wall)  // ������
                    {
                        maze[y][x - 1] = pass;
                        maze[y][x - 2] = pass;
                        x -= 2;
                    }
            case 3:
                if (x != width - 2)
                    if (maze[y][x + 2] == wall)  // �������
                    {
                        maze[y][x + 1] = pass;
                        maze[y][x + 2] = pass;
                        x += 2;
                    }
            }
            if (deadend(maze, height, width)) {
                break;
            }

        }

        if (deadend(maze, height, width))
            do
            {
                x = 2 * (rand() % ((width - 1) / 2)) + 1;
                y = 2 * (rand() % ((height - 1) / 2)) + 1;
            } while (maze[y][x] != pass);
         }
}



void visual(int** maze, int height, int width, RenderWindow* window, bool avto) //����������� ���������� � ������� SFML �������.
{
    wid = (width * 23) / 15;
    hei = (height * 25) / 10;

    RectangleShape wal(Vector2f(20, 20));
    RectangleShape way(Vector2f(20, 20));
    RectangleShape space(Vector2f(20, 20));
    RectangleShape play(Vector2f(20, 20));
    RectangleShape III(Vector2f(20, 20));

    way.setFillColor(Color::Red);
    wal.setFillColor(Color::Black);
    space.setFillColor(Color::White);
    play.setFillColor(Color::Green);
    III.setFillColor(Color::Blue);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) {
            switch (maze[i][j])
            {
            case (wall):
                wal.setPosition(wid + j * 20, hei + i * 20);
                (*window).draw(wal);
                break;
            case (pass):
                space.setPosition(wid + j * 20, hei + i * 20);
                (*window).draw(space);
                break;
            case (error):
                space.setPosition(wid + j * 20, hei + i * 20);
                (*window).draw(space);
                break;
            case (razvil):
                if (avto) {
                    way.setPosition(wid + j * 20, hei + i * 20);
                    (*window).draw(way);
                }
                else {
                    space.setPosition(wid + j * 20, hei + i * 20);
                    (*window).draw(space);
                }
                break;
            case put:
                if (avto) {
                    way.setPosition(wid + j * 20, hei + i * 20);
                    (*window).draw(way);
                }
                else {
                    space.setPosition(wid + j * 20, hei + i * 20);
                    (*window).draw(space);
                }
                break;
            case (player):
                play.setPosition(wid + j * 20, hei + i * 20);
                (*window).draw(play);
                break;
            case (II):
                III.setPosition(wid + j * 20, hei + i * 20);
                (*window).draw(III);
                break;
            }
        }
    }
}

void vozvrat(int** maze, int height, int width) { // ������� �� ������ �� �������� 

    while (maze[y][x] != razvil) {

        if (maze[y - 1][x] == put || maze[y - 1][x] == razvil)  // �����
        {
            maze[y][x] = error;
            y--;
        }
        else if (maze[y + 1][x] == put || maze[y + 1][x] == razvil) {  // ����

            maze[y][x] = error;
            y++;
        }
        else if (maze[y][x - 1] == put || maze[y][x - 1] == razvil)  // ������
        {
            maze[y][x] = error;
            x--;
        }
        else if (maze[y][x + 1] == put || maze[y][x + 1] == razvil)  // �������
        {
            maze[y][x] = error;
            x++;
        }

    }

}
void poisk_puti(int** maze, int height, int width) { // ����� ���� � ������
    int razvilka = 0, save_y = 0, save_x = 0;
    x = 1;
    y = 1;
    while ((y != (height - 2)) || (x != (width - 2))) {
        
        save_y = 0;
        save_x = 0;
        razvilka = 0;
        if (maze[y - 1][x] == pass)  // �����
        {
            razvilka++;
            save_y = -1;
            save_x = 0;
        }

        if (maze[y + 1][x] == pass) {  // ����

            razvilka++;
            save_y = 1;
            save_x = 0;
        }

        if (maze[y][x - 1] == pass)  // ������
        {
            razvilka++;
            save_x = -1;
            save_y = 0;
        }
        if (maze[y][x + 1] == pass)  // �������
        {
            razvilka++;
            save_x = 1;
            save_y = 0;
        }
        if (razvilka == 1) {
            maze[y][x] = put;
            x += save_x;
            y += save_y;
        }
        else if (razvilka > 1) {
            maze[y][x] = razvil;
            x += save_x;
            y += save_y;
        }
        else {
            maze[y][x] = put;
            vozvrat(maze, height, width);
        }

    }
    maze[height - 2][width - 2] = put;
    maze[height - 2][width - 1] = put;

}


void II_proxod(int** maze, RenderWindow* window, int height, int width) { // �������� ����
    stop = clock();
    if (((double)(stop - start) / CLOCKS_PER_SEC) >= time_II) {
        start = clock();
        if (maze[z][w + 1] == put || maze[z][w + 1] == razvil || maze[z][w + 1] == player || maze[z][w + 1] == II)  // �������
        {
            maze[z][w] = error;
            w++;
            maze[z][w] = II;
        }

        if (maze[z - 1][w] == put || maze[z - 1][w] == razvil || maze[z - 1][w] == player || maze[z - 1][w] == II)  // �����
        {
            maze[z][w] = error;
            z--;

            maze[z][w] = II;
        }

        if (maze[z][w - 1] == put || maze[z][w - 1] == razvil || maze[z][w - 1] == player || maze[z][w - 1] == II)  // ������
        {
            maze[z][w] = error;
            w--;

            maze[z][w] = II;
        }


        if (maze[z + 1][w] == put || maze[z + 1][w] == razvil || maze[z + 1][w] == player || maze[z + 1][w] == II) {  // ����

            maze[z][w] = error;
            z++;

            maze[z][w] = II;
        }

        (*window).clear(Color::White);

        visual(maze, height, width, window, FALSE);

        (*window).display();

    }
}

void play(int** maze, int height, int width, RenderWindow* window) { // ���� 
    start = clock();
    start_pl = clock();
  
    RectangleShape play(Vector2f(20, 20));


    play.setFillColor(Color::Green);

    int x = 1, y = 1;
    bool win = TRUE;
    maze[y][x] = II;
    play.setPosition(wid + x * 20, hei + y * 20);
  

    while ((*window).isOpen() && win)
    {

        (*window).clear(Color::White);

        visual(maze, height, width, window, FALSE);
        (*window).draw(play);
        (*window).display();


        II_proxod(maze, window, height, width);
        Event event;
        while ((*window).pollEvent(event))
        {

          

            II_proxod(maze, window, height, width);

            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
            {
                (*window).close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Insert))
            {
                (*window).close();
                return_menu();
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                if (maze[y][x + 1] != wall)  // �������
                {
                    x++;
                    play.setPosition(wid + x * 20, hei + y * 20);
               
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                if (maze[y - 1][x] != wall)  // �����
                { 
                    y--;
                    play.setPosition(wid + x * 20, hei + y * 20);
                   
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                if (maze[y][x - 1] != wall)  // ������
                {
                    x--;
                    play.setPosition(wid + x * 20, hei + y * 20);
                   
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                if (maze[y + 1][x] != wall) {  // ����
                    y++;
                    play.setPosition(wid + x * 20, hei + y * 20);
                  
                }
            }
            (*window).clear(Color::White);

            visual(maze, height, width, window, FALSE);
            (*window).draw(play);
            (*window).display();

        }
        if (y== height - 2 && x == width - 2) {
            end_pl = clock();
            (*window).close();
            RenderWindow okno(VideoMode(400, 400), "Labirint");

            okno.clear(Color::White);
            text.setString(L"!������!");
            text.setPosition(40, 150);
            text.setCharacterSize(60);
            text.setFillColor(Color::Green);
            okno.draw(text);
            okno.display();
            win = FALSE;
            Sleep(3000);
            okno.close();
   
            vnes_lider(((int)(end_pl - start_pl) / CLOCKS_PER_SEC));
           
        }
        if (maze[height - 2][width - 2] == II) {
            (*window).close();
            RenderWindow okno(VideoMode(400, 400), "Labirint");

            okno.clear(Color::White);
            text.setString(L"��������");
            text.setPosition(40, 150);
            text.setCharacterSize(60);
            text.setFillColor(Color::Red);
            okno.draw(text);
            okno.display();
            win = FALSE;
            Sleep(5000);
            okno.close();
            return_menu();
        }

    }

}



void input_time_II(RenderWindow* window) { // ���� �������� ������������ ����

    char size[7];
    int i = -1;
    bool vibor = TRUE;
    RectangleShape rectangle1(Vector2f(400, 90));
    rectangle1.setFillColor(Color::White);
    rectangle1.setPosition(100, 250);
    rectangle1.setOutlineThickness(3);
    rectangle1.setOutlineColor(Color::Black);

    (*window).clear(Color::White);
    text.setString(L"������� ");
    text.setPosition(50, 100);
    text.setCharacterSize(50);
    text.setFillColor(Color::Red);
    (*window).draw(text);
    text.setString(L"�������� ����");
    text.setPosition(100, 160);
    (*window).draw(text);
    (*window).draw(rectangle1);
    (*window).display();

    while ((*window).isOpen())
    {

        Event event;
        while ((*window).pollEvent(event))
        {


            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
            {
                (*window).close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            int m = 10;
            double n = 0.1;

            for (int j = 0; j <= i; j++) {
                if (size[j] == '.' || size[j] == ',') { vibor = FALSE; }
                if (vibor) {
                    time_II = (time_II * m) + (int(size[j]) - 48);
                }
                if (!vibor && size[j] != '.' && size[j] != ',') {
                    time_II += (int(size[j]) - 48) * n;
                    n *= 0.1;
                }

            }

            Sleep(100);
            (*window).close();
        }
        if ((event.type == Event::TextEntered && (event.key.code == '0' || event.key.code == '1' || event.key.code == '2' || event.key.code == '3' || event.key.code == '4' || event.key.code == '5' || event.key.code == '6' || event.key.code == '7' || event.key.code == '8' || event.key.code == '9' || event.key.code == '.' || event.key.code == ',')) || Keyboard::isKeyPressed(Keyboard::LShift)) {


            (*window).clear(Color::White);
            text.setString(L"������� ");
            text.setPosition(50, 100);
            text.setCharacterSize(50);
            text.setFillColor(Color::Red);
            (*window).draw(text);
            text.setString(L"�������� ����");
            text.setPosition(100, 160);
            (*window).draw(text);
            (*window).draw(rectangle1);
            text.setCharacterSize(60);
            text.setFillColor(Color::Green);
            if (event.type == Event::TextEntered && (event.key.code == '0' || event.key.code == '1' || event.key.code == '2' || event.key.code == '3' || event.key.code == '4' || event.key.code == '5' || event.key.code == '6' || event.key.code == '7' || event.key.code == '8' || event.key.code == '9' || event.key.code == '.' || event.key.code == ',')) {
                i++;
                size[i] = event.key.code;
                for (int g = 0; g <= i; g++) {
                    text.setString(size[g]);
                    text.setPosition(200 + g * 35, 250);
                    (*window).draw(text);
                }

            }
            if (Keyboard::isKeyPressed(Keyboard::LShift)) {

                size[i] = NULL;
                i--;
                for (int g = 0; g <= i; g++) {
                    text.setString(size[g]);
                    text.setPosition(200 + g * 35, 250);
                    (*window).draw(text);
                }
            }
            (*window).display();
            Sleep(200);




        }
    }


}


bool mod_selectino() { // ����� ������ ������ ��������� 

    RenderWindow window(VideoMode(600, 500), "Labirint");
    RectangleShape rectangle1(Vector2f(400, 100));
    RectangleShape rectangle2(Vector2f(560, 100));



    rectangle1.setFillColor(Color::White);
    rectangle1.setPosition(100, 150);
    rectangle1.setOutlineThickness(5);
    rectangle1.setOutlineColor(Color::White);

    rectangle2.setFillColor(Color::White);
    rectangle2.setPosition(20, 300);
    rectangle2.setOutlineThickness(5);
    rectangle2.setOutlineColor(Color::White);


    while (window.isOpen())
    {
        window.clear(Color::White);
        text.setString(L"���a��");
        text.setPosition(150, 150);
        text.setCharacterSize(70);
        text.setFillColor(Color::Blue);


        window.draw(rectangle1);
        window.draw(text);

        text.setString(L"�������������");
        text.setPosition(30, 300);
        text.setCharacterSize(60);
        text.setFillColor(Color::Red);

        window.draw(rectangle2);
        window.draw(text);

        window.display();

        Vector2i pos = Mouse::getPosition(window);
        Event event;
        while (window.pollEvent(event))
        {


            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
            if (rectangle1.getGlobalBounds().contains(pos.x, pos.y)) {
                rectangle1.setOutlineColor(Color::Black);
                if (event.key.code == Mouse::Left) {
                    input_time_II(&window);
                    return TRUE;
                }

            }
            else {
                rectangle1.setOutlineColor(Color::White);
            }
            if (rectangle2.getGlobalBounds().contains(pos.x, pos.y)) {
                rectangle2.setOutlineColor(Color::Black);
                if (event.key.code == Mouse::Left) { return FALSE; }

            }
            else {
                rectangle2.setOutlineColor(Color::White);
            }
        }
    }

}
void return_menu() { // ���������� ��������� 
    bool mod;
    int height = 0, width = 0;

    input_size(&height, &width);

    int** maze = new int* [height];
    for (int i = 0; i < height; i++) {
        maze[i] = new int[width];
    }
    mazemake(maze, height, width);
    RenderWindow window(VideoMode(width * 23, height * 25), "Labirint");



    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
        }

        window.clear(Color::White);

        visual(maze, height, width, &window, TRUE);

        window.display();

        Sleep(2000);


        mod = mod_selectino();
        if (mod) {
            poisk_puti(maze, height, width);
            play(maze, height, width, &window);
        }
        else {
            poisk_puti(maze, height, width);

            window.clear(Color::White);

            visual(maze, height, width, &window, TRUE);

            window.display();
            Sleep(5000);
            return_menu();

        }

    }
}

void vnes_lider(int time) { // �������� ���������� � ����� ��� ����������� � ���� � ����� ������ �� ����� � ���� windows

    RenderWindow window(VideoMode(600, 600), "Labirint");
    char lider[10];
    int i = -1;

    window.clear(Color::White);
    text.setString(L"������� ���:");
    text.setPosition(20, 20);
    text.setCharacterSize(60);
    text.setFillColor(Color::Red);
    window.draw(text);
    window.display();


    text.setCharacterSize(80);
    text.setFillColor(Color::Blue);
    FILE* file;
    file = fopen("D:/����/�������� ������/������.txt", "a");
    String string;
    char mas[10];

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {


            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                for (int a = 0; a <= i; a++) {
                    fprintf(file, "%c", lider[a]);
                }
              
                fprintf(file, "%c", ' ');
                fprintf(file, "%d", time);
                   
                 

                
                fprintf(file, "\n");
                fclose(file);
                window.clear(Color::White);
                text.setString(L"���������� : ");
                text.setPosition(20, 20);
                text.setCharacterSize(60);
                text.setFillColor(Color::Red);
                window.draw(text);
                file = fopen("D:/����/�������� ������/������.txt", "r+");
                int peremeshenie_po_y = 0;
                while (fgets(mas, 10, file)) {

                    text.setString(mas);
                    text.setPosition(20, 100 + peremeshenie_po_y);
                    text.setCharacterSize(40);
                    text.setFillColor(Color::Blue);
                    window.draw(text);
                    peremeshenie_po_y += 50;
                }
                window.display();

                Sleep(5000);
                return_menu();
            }
            if ((event.type == Event::TextEntered || Keyboard::isKeyPressed(Keyboard::LShift))) {
                window.clear(Color::White);
                text.setString(L"������� ���:");
                text.setPosition(20, 20);
                text.setCharacterSize(60);
                text.setFillColor(Color::Red);
                window.draw(text);
                text.setCharacterSize(80);
                text.setFillColor(Color::Blue);
                if (event.type == Event::TextEntered) {
                    i++;
                    lider[i] = event.key.code;
                    for (int g = 0; g <= i; g++) {
                        text.setString(lider[g]);
                        text.setPosition(20 + g * 50, 200);
                        window.draw(text);
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::LShift)) {

                    lider[i] = NULL;
                    i--;
                    printf("-%d", i);
                    for (int g = 0; g <= i; g++) {
                        text.setString(lider[g]);
                        text.setPosition(20 + g * 50, 200);
                        window.draw(text);
                    }
                }
                window.display();
                Sleep(200);


            }

        }

    }
}