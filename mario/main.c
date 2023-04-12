#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define MapHeight 30
#define MapWidth 120

typedef struct{
    float x,y;
    float height,width;
    float vertSpeed;
    BOOL IsFly;
    char CType;
    float HorizSpeed;
}Tobject;

char map[MapHeight][MapWidth+1];
Tobject mario;
Tobject *brick=NULL;
int BrickLenght;
int level=1;
int maxlvl;
static int score=0;

int MovingLenght;
Tobject *moving=NULL;

void ClearMap()
{
    //printf("\tscore: %d\n",score);
    for(int i=0;i<MapWidth-1;i++)
        map[0][i]=' ';
    map[0][MapWidth]='\0';
    for(int i=0;i<MapHeight;i++)
        sprintf(map[i],map[0]);
}

void PutScoreOnMap()
{
    char c[30];
    sprintf(c,"score: %d",score);
    int len=strlen(c);
    for(int i=0;i<len;i++)
        map[0][i+5]=c[i];
}

void ShowMap()
{
    for(int i=0;i<MapHeight;i++)
        if(i!=MapHeight-1)
            printf("%s\n",map[i]);
        else
            printf("%s",map[i]);
}

BOOL IsOnMap(int x,int y)
{
    return (y<MapHeight)&&(y>=0)&&
            (x<MapWidth-1)&&(x>=0);
}

BOOL IsCollision(Tobject obj1,Tobject obj2)
{
    return ((obj1.y+obj1.height>obj2.y)&&(obj1.y<obj2.y+obj2.height)&&
            (obj1.x+obj1.width>obj2.x)&&(obj1.x<obj2.x+obj2.width));
}

void SetPosObject(Tobject *obj,float x,float y)
{
    obj->x=x;
    obj->y=y;
}

void InitObject(Tobject *obj,float x,float y,float w,float h,char type)
{
    SetPosObject(obj,x,y);
    obj->height=h;
    obj->width=w;
    obj->vertSpeed=0;
    obj->CType=type;
    obj->HorizSpeed=0.4;
}
void DeathPlayer();
Tobject* GetNewMoving();

void  VertMove(Tobject *obj)
{
    obj->IsFly=TRUE;
    obj->vertSpeed+=0.05;
    obj->y+=obj->vertSpeed;
    for(int i=0;i<BrickLenght;i++)
        if(IsCollision(*obj,brick[i]))
        {
            if(obj->vertSpeed>0)
                obj->IsFly=FALSE;
            obj->y-=obj->vertSpeed;
            obj->vertSpeed=0;
            if(brick[i].CType=='+')
            {
                level++;
                //if(level>maxlvl)level=1;
                system("color 2F");
                Sleep(200);
                CreateLevel(level);
            }
            if((brick[i].CType=='?')&&(obj->IsFly)&&(obj->CType=='@'))
            {
                brick[i].CType='-';
                InitObject(GetNewMoving(),brick[i].x,brick[i].y-2,2,2,'$');
                moving[MovingLenght-1].vertSpeed=-0.7;
            }
            break;
        }
}

void PutObjectOnMap(Tobject obj)
{
    int ix=(int)round(obj.x);
    int iy=(int)round(obj.y);
    int iw=(int)round(obj.width);
    int ih=(int)round(obj.height);
    for(int i=iy;i<iy+ih;i++)
        for(int j=ix;j<ix+iw;j++)
            if(IsOnMap(j,i))
                map[i][j]=obj.CType;
}

void HorizontMoveMap(int dx)
{
    mario.x-=dx;
    for(int i=0;i<BrickLenght;i++)
        if(IsCollision(mario,brick[i]))
        {
            mario.x+=dx;
            return;
        }
    mario.x+=dx;

    for(int i=0;i<BrickLenght;i++)
        brick[i].x+=dx;
    for(int i=0;i<MovingLenght;i++)
        moving[i].x+=dx;
}

void DeathPlayer()
{
    system("color 4F");
    Sleep(200);
    score=0;
    CreateLevel(level);
}

void DeleteMoving(int i)
{
    MovingLenght--;
    moving[i]=moving[MovingLenght];
    moving=realloc(moving,sizeof(Tobject)*MovingLenght);
}

void KillMoving(int i)
{
    if((mario.IsFly)&&(mario.vertSpeed>0)&&(!moving[i].IsFly)&&
        (mario.y+mario.height>(moving[i].y+moving[i].height)/2)||(moving[i].CType=='$'))
    {
        if(moving[i].CType=='o')
            score+=50;
        else score+=100;
        DeleteMoving(i);
    }
    else
        DeathPlayer();

}

void HorizMoveObj(Tobject *obj)
{
    obj->x+=obj->HorizSpeed;
    for(int j=0;j<BrickLenght;j++)
    {
        if(IsCollision(*obj,brick[j]))
        {
            obj->x-=obj->HorizSpeed;
            obj->HorizSpeed*=-1;
        }
    }
    if(obj->CType=='o')
    {
        Tobject tmp=*obj;
        VertMove(&tmp);
        if(tmp.IsFly)
        {
            obj->x-=obj->HorizSpeed;
            obj->HorizSpeed*=-1;
        }
    }
}

void setcur(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

Tobject* GetNewBrick()
{
    BrickLenght++;
    brick=realloc(brick,sizeof(Tobject)*BrickLenght);
    return brick+BrickLenght-1;
}

Tobject* GetNewMoving()
{
    MovingLenght++;
    moving=realloc(moving,sizeof(Tobject)*MovingLenght);
    return moving+MovingLenght-1;
}


void CreateLevel(int lvl)
{
    InitObject(&mario,30,12,3,3,'@');
    system("color 0F");
    BrickLenght=0;
    MovingLenght=0;
    moving=NULL;
    brick=NULL;
    if(lvl==1)
    {
        InitObject(GetNewBrick(),15,20,30,10,'#');
        InitObject(GetNewBrick(),60,15,20,30,'#');
        InitObject(GetNewBrick(),100,6,15,30,'#');
        InitObject(GetNewBrick(),135,24,20,10,'#');
        InitObject(GetNewBrick(),167,15,10,15,'#');
        InitObject(GetNewBrick(),200,10,5,20,'+');
    }
    if(lvl==2)
    {
        InitObject(GetNewBrick(),-13,0,30,30,'#');
        InitObject(GetNewBrick(),15,25,30,10,'#');
        InitObject(GetNewBrick(),40,19,50,30,'#');
        InitObject(GetNewBrick(),90,25,80,30,'#');
        InitObject(GetNewBrick(),135,18,20,10,'#');
        InitObject(GetNewBrick(),167,15,10,15,'#');
        InitObject(GetNewBrick(),200,15,10,15,'#');
        InitObject(GetNewBrick(),240,10,5,20,'+');
            InitObject(GetNewMoving(),22,10,3,2,'o');
            InitObject(GetNewMoving(),42,10,3,2,'o');
            InitObject(GetNewMoving(),52,10,3,2,'o');
            InitObject(GetNewMoving(),62,10,3,2,'o');
            InitObject(GetNewMoving(),72,10,3,2,'o');
            InitObject(GetNewMoving(),92,10,3,2,'o');
            InitObject(GetNewMoving(),102,10,3,2,'o');
            InitObject(GetNewMoving(),122,10,3,2,'o');
    }
    if(lvl==3)
    {
        InitObject(GetNewBrick(),20,20,60,10,'#');
            InitObject(GetNewBrick(),30,8,5,3,'-');
            InitObject(GetNewBrick(),35,8,5,3,'?');
            InitObject(GetNewBrick(),40,8,15,3,'-');
            InitObject(GetNewBrick(),55,8,5,3,'?');
            InitObject(GetNewBrick(),60,8,5,3,'-');
        InitObject(GetNewBrick(),100,15,30,20,'#');
        InitObject(GetNewBrick(),120,20,40,10,'#');
        InitObject(GetNewBrick(),150,20,20,10,'#');
        InitObject(GetNewBrick(),180,14,40,30,'#');
        InitObject(GetNewBrick(),240,28,3,5,'+');
        InitObject(GetNewMoving(),40,12,3,2,'o');
    }
    maxlvl=3;
}

void Win()
{
    system("cls");
    printf("\n\n\n\n\n\n\n\n\t\t\tCONGRATULATIONS!\n\t\t\tYOU WIN!");
    Sleep(1000);
}

int main()
{
    CreateLevel(level);

    do
    {
        setcur(0,0);
        ClearMap();
        for(int i=0;i<BrickLenght;i++)
            PutObjectOnMap(brick[i]);
        for(int i=0;i<MovingLenght;i++)
        {
            PutObjectOnMap(moving[i]);
            VertMove(moving+i);
            HorizMoveObj(moving+i);
        }
        VertMove(&mario);
        PutObjectOnMap(mario);

        if((GetKeyState(VK_SPACE)<0)&&(!mario.IsFly))mario.vertSpeed=-1;
        if(GetKeyState('D')<0) HorizontMoveMap(-1);
        if(GetKeyState('A')<0) HorizontMoveMap(1);

        if(mario.y>MapHeight)
        {
            DeathPlayer();
        }
        for(int i=0;i<MovingLenght;i++)
        {
            if(IsCollision(mario,moving[i]))
            {
                KillMoving(i);
            }
        }
        PutScoreOnMap();
        ShowMap();
        Sleep(10);
    }
    while((GetKeyState(VK_ESCAPE)>=0)||(level!=4));
    setcur(0,0);
    Win();
    return 0;
}
