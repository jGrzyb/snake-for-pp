#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <cstdio>
#include <conio.h>

using namespace std;

string board[21][21];
bool bitten=false;
int timet=0;
struct Pos
{
    int x=10, y=10;
};
struct Snake
{
    int len=2;
    Pos pos[500];
} snaket;

void tabGen();
void screen();
void play();
void snake(char dir);
char opp(char x);
bool ifwasd(char x);
void apple();
void start();
void loose(char* dirp);
void clear();




int main() {
    start();
    play();

    return 0;
}




void tabGen()
{
    for(int i=0; i<21; i++)
    {
        for(int j=0; j<21; j++)
        {
            board[i][j]="  ";
        }
    }
    for(int i=0; i<21; i++)
    {
        board[i][0]="| ";
        board[0][i]="__";
        board[i][20]="| ";
        board[20][i]="__";
    }
    board[10][10]="8 ";
    board[0][20]="_ ";
    board[20][0]="|_";
    board[20][20]="| ";
}


void screen()
{
    string board1[21]={};
    string board2;
    for(int i=0; i<21; i++)
    {
        for(int j=0; j<21; j++)
        {
            board1[i]+=board[i][j];
        }
        board2 += (board1[i] + "\n");
    }
    clear();
    cout << board2;
    cout << "  time: " << timet/5/60 << ":"; if(timet/5%60<10) cout << "0" << timet/5%60; else cout << timet/5%60; cout << endl << "  points: " << snaket.len-2;
}


void play()
{
    char dir;
    while(true)
    {
        char temp=getch();
        if(ifwasd(temp) && temp!=opp(dir)) {
                dir=temp;
        }
        if(!ifwasd(dir)) {
            dir = 'w';
        }
        do
        {
            snake(dir);
            if(bitten==true) break;
            timet++;
            screen();
            Sleep(200);
        }while(!_kbhit());
        if(bitten==true) {
            loose(&dir);
        }
    }
}


void snake(char dir)
{
    board[snaket.pos[snaket.len-1].x][snaket.pos[snaket.len-1].y]="  ";
    for(int i=snaket.len-1; i>0; i--)
    {
        snaket.pos[i].x=snaket.pos[i-1].x;
        snaket.pos[i].y=snaket.pos[i-1].y;
        switch(i%3)
        {
            case 0: board[snaket.pos[i].x][snaket.pos[i].y]="o "; break;
            case 1: board[snaket.pos[i].x][snaket.pos[i].y]="o "; break;
            case 2: board[snaket.pos[i].x][snaket.pos[i].y]="0 "; break;

        }
    }
    switch(dir)
    {
        case 'w':
            snaket.pos[0].x--; break;
        case 's':
            snaket.pos[0].x++; break;
        case 'a':
            snaket.pos[0].y--; break;
        case 'd':
            snaket.pos[0].y++; break;
        default:
            break;
    }
    if(snaket.pos[0].x==20) snaket.pos[0].x=1;
    if(snaket.pos[0].x==0) snaket.pos[0].x=19;
    if(snaket.pos[0].y==20) snaket.pos[0].y=1;
    if(snaket.pos[0].y==0) snaket.pos[0].y=19;

    if(board[snaket.pos[0].x][snaket.pos[0].y]=="X ") {
        snaket.len++;
        apple();
    }
    if((board[snaket.pos[0].x][snaket.pos[0].y]=="o ")||(board[snaket.pos[0].x][snaket.pos[0].y]=="0 ")) {
        bitten=true;
        return;
    }
    else
        board[snaket.pos[0].x][snaket.pos[0].y]="8 ";
}


char opp(char x)
{
    char y;
    if(x=='w') y='s';
    if(x=='a') y='d';
    if(x=='s') y='w';
    if(x=='d') y='a';
    return y;
}


bool ifwasd(char x)
{
    if((x=='w')||(x=='a')||(x=='s')||(x=='d'))
    return true;
    else return false;
}


void apple()
{
    Pos apos;
    do
    {
        apos.x=rand()%19+1;
        apos.y=rand()%19+1;
    } while (board[apos.x][apos.y]!="  ");
    board[apos.x][apos.y]="X ";
}


void start()
{
    srand(time(NULL));
    tabGen();
    apple();
    bitten=false;
    timet=0;
    snaket.len=2;
    snaket.pos[0].x=10;
    snaket.pos[0].y=10;
    screen();
    cout << "\n\n  Welcome to Snake! \n  Press W, A, S or D to start and control snake";
}


void loose(char* dirp)
{
    cout << endl << "  You lost! You collected " << snaket.len-2 << " apples in " << timet/5/60 << ":"; if(timet/5%60<10) cout << "0" << timet/5%60; else cout << timet/5%60; cout << " minutes!" << endl <<
    "  Do you want to play again? [y/n]";
    char dec;
    while((dec!='y')&&(dec!='n'))
    {
        dec=getch();
    }
    if(dec=='y') {
        start();
        *dirp='0';
        return;
    }
    if(dec=='n') {
        exit(0);
    }
}

void clear() {
    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}