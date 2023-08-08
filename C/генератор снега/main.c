//Генератор снега

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define weight 90
#define hight 30

char pole[hight][weight+1];

void init()
{
    int i=0;
    for(i;i<weight;i++)
        pole[0][i]=' ';
    pole[0][weight]='\0';
    for(i=0;i<hight;i++)
        //sprintf(pole[i],pole[0]);
        strncpy(pole[i],pole[0],weight);
}

void show()
{
    for(int i=0;i<hight;i++)
        puts(pole[i]);
}

void snow()
{
    for(int i=0;i<weight;i++)
        if(rand()%10==1)pole[0][i]='*';
}

void moveSnow()
{
    int dx;
    for(int j=hight-1;j>=0;j--)
        for(int i=0;i<weight;i++)
        {
            if(pole[j][i]=='*')
            {
                pole[j][i]=' ';
                dx=0;
                if(rand()%10<1)dx--;
                if(rand()%10<1)dx++;
                i+=dx;
                if((i>=0)&&(i<weight))
                    pole[j+1][i]='*';
            }
        }
}

void move()
{

}

void setcure(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int main()
{
    init();
    do
    {
        setcure(0,0);

        moveSnow();
        snow();
        show();
        Sleep(110);
    }
    while(GetKeyState(VK_ESCAPE)>=0);

    return 0;
}
