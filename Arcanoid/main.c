#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

#define weight 65
#define hight 25

char pole[hight][weight+1];

typedef struct{
    int x,y,w;
}Tracket;

typedef struct{
    float x,y;
    int ix,iy;
    float alfa,speed;
}TBall;
int level=1;
Tracket racket;
TBall ball;
int cnt=0,maxcnt=0;
void init(int level)
{
    int i=0;
    for(i;i<weight;i++)
        pole[0][i]='#';
    pole[0][i+1]='\0';
    strncpy(pole[1],pole[0],weight+1);
    for(i=1;i<weight-1;i++)
        pole[1][i]=' ';
    for(i=2;i<hight;i++)
        strncpy(pole[i],pole[1],weight+1);
    if((level==2)||(level==3))
    {
        for(i=15;i<55;i++)
            pole[5][i]='#';
    }
    if(level==3)
    {
        for(i=10;i<25;i++)
            pole[10][i]='#';
        for(i=45;i<60;i++)
            pole[10][i]='#';
    }
    if(level==5)
    {
        for(i=15;i<55;i+=2)
            pole[5][i]='#';
        for(i=10;i<25;i+=2)
            pole[10][i]='#';
        for(i=45;i<60;i+=2)
            pole[10][i]='#';
    }
    if(level==4)
    {
        for(int j=1;j<12;j++)
            for(int i=8;i<weight;i+=7)
                pole[j][i]='#';
    }
    if(level==6)
    {
        for(int y=5;y<hight-10;y+=3)
        {
            if(y%2)i=3;
            else i=2;
            for(i;i<weight-1;i+=4)
            {
                pole[y][i+1]=pole[y][i]='#';
                if(i%2){if(pole[y][i+2]=='#')pole[y][i]=' ';}
                else if(pole[y][i+2]=='#')pole[y][i+1]=' ';


            }
        }
    }
}

void show()
{
    for(int i=0;i<hight;i++)
    {
        printf("%s",pole[i]);
        if(i==1)
            printf("\tMake more 10 hits to change level");
        if(i==3)
            printf("\tlevel %d\t",level);
        if(i==5)
            printf("\thit %d\t",cnt);
        if(i==6)
            printf("\tmax %d\t",maxcnt);
        if(i!=hight-1)printf("\n");
    }
}

void ShowPreview()
{
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\tLEVEL %d",level);
    Sleep(1000);
    system("cls");
}

void initBall()
{
    ball.x=2.;
    ball.y=2.;
    ball.alfa=-1;
    ball.speed=.5;
}

void putBall()
{
    pole[ball.iy][ball.ix]='*';
}

void moveBall(float x,float y)
{
    ball.x=x;
    ball.y=y;
    ball.iy=(int)round(ball.y);
    ball.ix=(int)round(ball.x);
}

void autoMoveBall()
{
    if(ball.alfa<0) ball.alfa+=2*M_PI;
    if(ball.alfa>2*M_PI) ball.alfa-=2*M_PI;

    TBall bl=ball;
    moveBall(ball.x + ball.speed*cos(ball.alfa),
             ball.y + ball.speed*sin(ball.alfa));
    if((pole[ball.iy][ball.ix]=='#')||(pole[ball.iy][ball.ix]=='@'))
    {
        if(pole[ball.iy][ball.ix]=='@')
            cnt++;
        if((ball.ix != bl.ix)&&(ball.iy!=bl.iy))
        {
            if(pole[bl.iy][ball.ix]==pole[ball.iy][bl.ix])
                bl.alfa=bl.alfa+M_PI;
            else
            {
                if(pole[bl.iy][ball.ix]=='#')
                    bl.alfa=(2*M_PI-bl.alfa)+M_PI;
                else
                    bl.alfa=(2*M_PI-bl.alfa);
            }
        }
        else if(ball.iy==bl.iy)
            bl.alfa=(2*M_PI-bl.alfa)+M_PI;
        else
            bl.alfa=(2*M_PI-bl.alfa);
    ball=bl;
    autoMoveBall();
    }
}

void initRacket()
{
    racket.y=hight-1;
    racket.w=7;
    racket.x=(weight-racket.w)/2;
}

void moveRacket(int x)
{
    racket.x=x;
    if(racket.x<1) racket.x=1;
    if(racket.x>weight-racket.w-1) racket.x=weight-1-racket.w;
}

void putRacket()
{
    for(int i=racket.x;i<racket.w+racket.x;i++)
        pole[racket.y][i]='@';
}

void setcur(int x, int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int main()
{
    char c;

    BOOL run=FALSE;
    initRacket();
    initBall();
    ShowPreview();
    do
    {

        setcur(0,0);
        if(ball.iy>=hight-1)
        {
            run=FALSE;
            if(cnt>maxcnt)
                maxcnt=cnt;
            cnt=0;
            system("cls");
            ball.alfa=-1;
        }
        if((cnt>10))
        {
            level++;
            ball.speed+=0.1;
            run=FALSE;
            cnt=maxcnt=0;
            if(level!=7)ShowPreview();
        }
        if(run)
            autoMoveBall();
        init(level);
        putRacket();
        putBall();
        show();

        if(GetKeyState('A')<0)moveRacket(racket.x-1);
        if(GetKeyState('D')<0)moveRacket(racket.x+1);
        if(GetKeyState(VK_SPACE)<0)run=TRUE;
        if(!run)
            moveBall(racket.x+racket.w/2,racket.y-1);
        Sleep(10);
        if(level==7)
        {
            system("cls");
            printf("THE END OF GAME\n\nCONGRATULATOINS!");
            sleep(5);
            break;
        }
    }
    while((GetKeyState(VK_ESCAPE)>=0)&&(level!=7));
    return 0;
}
