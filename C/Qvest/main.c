#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define HIGH 30
#define WIDTH 81

struct{
    char map[HIGH][WIDTH+1];
    POINT size;
}loc;

typedef struct{
    char name[20];
    POINT pos;
    char type;
    char item_message[200];
    char item_need[20];
    int item_cnt;
    char item_given[20];
}Tobj;

typedef struct{
    char name[20];
}Titem;

Tobj* obj=NULL;
int objcnt=0;

struct {
    char name[20];
    POINT pos;
    POINT locpos;
    Titem items[20];
}player;

Tobj* obj_Add()
{
    objcnt++;
    obj=realloc(obj,sizeof(*obj)*objcnt);
    return obj+objcnt-1;
}

Tobj* obj_GetXY(int x,int y)
{
    for(int i=0;i<objcnt;i++)
        if((obj[i].pos.y==y)&&(obj[i].pos.x==x))
            return obj+i;
    return NULL;

}

int player_HaveCnt(char name[20])
{
    int cnt = 0;
    int len=strlen(name);
    if(name[len-1]=='\n')len--;
    for(int k=0;k<20;k++)
        if(strncmp(player.items[k].name,name,len)==0)
            cnt++;
    return cnt;
}

void player_AddItem(Titem item)
{
    for(int i=0;i<20;i++)
        if(player.items[i].name[0]==0)
        {
            sprintf(player.items[i].name,item.name);
            return;
        }
}

int delete_item(Titem item,int DelCnt)
{
    int cnt=player_HaveCnt(item.name);
    if(DelCnt>cnt) return 0;

    int len=strlen(item.name);
    for(int k=0;k<20;k++)
    {
        if(strncmp(player.items[k].name,item.name,len)==0)
        {
            memset(player.items[k].name,0,sizeof(player.items[k].name));
            DelCnt--;
            if(DelCnt<1) return 1;
        }
    }
    return -1;
}

void sort_items()
{
    for(int k=0;k<20;k++)
        for(int j=k+1;j<20;j++)
            if((player.items[k].name[0]==0)&&(player.items[j].name[0]!=0))
            {
                sprintf(player.items[k].name,player.items[j].name);
                memset(player.items[j].name,0,sizeof(player.items[j].name));
            }
}

void obj_StartDialog(Tobj* obj)
{
    if(obj==NULL)return;
    char ans;
    do
    {
        system("cls");
        puts(obj->name);

        if(obj->type=='/')
        {
            if(player_HaveCnt(obj->item_need)<obj->item_cnt)
            {
                printf(obj->item_message);
                puts("");
                puts("0 - Exit");
                ans = getch();
            }
            else
            {
                printf("Do you want enter?\n\n\n");
                puts("1 - Yes");
                puts("0 - No");
                ans=getch();
                if(ans=='1')
                {
                    player.pos.x+=(obj->pos.x-player.pos.x)*2;
                    player.pos.y+=(obj->pos.y-player.pos.y)*2;
                    ans='0';
                }
            }
        }
        if(obj->type=='N')
        {
            Titem item;
            sprintf(item.name,obj->item_given);
            if(player_HaveCnt(item.name)!=1)
            {
                printf("Are you want have %s?\n\n",obj->item_given);
                puts("1 - Yes");
                puts("0 - No");
                ans=getch();
                if(ans=='1')
                {
                    system("cls");
                    printf(obj->item_message);
                    puts("");
                    Titem item;
                    sprintf(item.name,obj->item_need);
                    if(player_HaveCnt(item.name)<obj->item_cnt)
                    {
                        puts("0 - Exit");
                        ans=getch();
                    }
                    else
                    {
                        puts("1 - Give apples");
                        puts("0 - Exit");
                        ans=getch();
                        if(ans=='1')
                        {
                            delete_item(item,obj->item_cnt);
                            Titem item;
                            sprintf(item.name,obj->item_given);
                            player_AddItem(item);
                            sort_items();
                        }
                    }
                    ans='0';
                }
            }
            else
            {
                printf("I can't give you anything\n\n0 - Exit\n");
                ans = getch();
            }
        }
    }
    while(ans!='0');
}

void obj_Download(char* FileName)
{
    obj=realloc(obj,0);
    objcnt=0;

    Tobj *tmp;
    FILE *f=fopen(FileName,"rt");

    if(f)
        while(!feof(f))
        {
            tmp=obj_Add();
            fgets(tmp->name,19,f);
            fscanf(f,"%c",&tmp->type);
            fscanf(f,"%d",&tmp->pos.y);
            fscanf(f,"%d\n",&tmp->pos.x);
            fgets(tmp->item_message,30,f);
            fgets(tmp->item_need,19,f);
                int len=strlen(tmp->item_need);
                if(tmp->item_need[len-1]=='\n')
                    tmp->item_need[len-1]='\0';
            fscanf(f,"%d\n",&tmp->item_cnt);
            fgets(tmp->item_given,19,f);

            len=strlen(tmp->item_given);
            if(tmp->item_given[len-1]=='\n')
                tmp->item_given[len-1]='\0';

        }
    fclose(f);
}

void loc_LoadFromFile(char* FileName)
{
    system("cls");
    loc.size.x=loc.size.y=0;
    for(int i=0;i<HIGH;i++)
        loc.map[i][0]='\0';

    FILE *f=fopen(FileName,"r");
    if(f!=NULL)
    {
        char c[WIDTH+1];
        int line=0;
        while(!feof(f))
        {
            fgets(c,WIDTH,f);
            int len=strlen(c);
            if(len>loc.size.x)
                loc.size.x=len;
            if(len<WIDTH)
            {
                while(len<WIDTH)
                {
                    c[len-1]=' ';
                    len++;
                }
                c[len-1]='\n';
                c[len]='\0';
            }
            sprintf(loc.map[line],c);
            line++;
        }
        loc.size.y=line;
        loc.map[line-1][loc.size.x-2]='#';
        loc.map[line-1][loc.size.x-1]='\0';

    }
    fclose(f);
}

char map[HIGH][WIDTH+1];

void setcur()
{
    COORD coord;
    coord.X=0;
    coord.Y=0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void map_Show()
{
    setcur();
    for(int i=0;i<HIGH;i++)
        printf("%s",map[i]);
}

void loc_PutOnMap()
{
    memcpy(map,loc.map,sizeof(map));
}

void player_Init(int locx,int locy,int x,int y,char *name)
{
    player.pos.x=x;
    player.pos.y=y;
    player.locpos.x=locx;
    player.locpos.y=locy;
    sprintf(player.name,name);
    memset(player.items,0,sizeof(player.items));
}

void player_PutOnMap()
{
    map[player.pos.y][player.pos.x]='A';

    static int dx = 45;

    for(int k=0;k<20;k++)
    {
        for(int i=0;i<20;i++)
            if((player.items[k].name[i]!=0)&&(player.items[k].name[i]!='\n'))
                map[k][dx+i]=player.items[k].name[i];
    }
}

void player_Move()
{
    POINT old=player.pos;
    if(GetKeyState('W')<0)player.pos.y--;
    if(GetKeyState('A')<0)player.pos.x--;
    if(GetKeyState('S')<0)player.pos.y++;
    if(GetKeyState('D')<0)player.pos.x++;
    if(map[player.pos.y][player.pos.x]!=' ')
    {
        if(map[player.pos.y][player.pos.x]=='a')
        {
            Titem item;
            sprintf(item.name,"Apple");
            player_AddItem(item);
            Sleep(500);
        }
        Tobj* obj=obj_GetXY(player.pos.x,player.pos.y);
        player.pos=old;
        obj_StartDialog(obj);
    }

    if(player.pos.x>loc.size.x-3)
    {
        player.locpos.x++;
        player_locDownload();
        player.pos.x=1;
    }
    if(player.pos.x<1)
    {
        player.locpos.x--;
        player_locDownload();
        player.pos.x=loc.size.x-3;
    }
    if(player.pos.y<1)
    {
        player.locpos.y++;
        player_locDownload();
        player.pos.y=loc.size.y-2;
    }
    if(player.pos.y>loc.size.y-2)
    {
        player.locpos.y--;
        player_locDownload();
        player.pos.y=1;
    }
}

void player_Save()
{
    FILE *f=fopen(player.name,"wb");
    if(f==NULL);
    else
    {
        fwrite(&player,1,sizeof(player),f);
    }
    fclose(f);
}

void player_Download(char *name)
{
    FILE *f=fopen(name,"rb");
    if(f==NULL)
        player_Init(0,0,4,2,name);
    else
        fread(&player,1,sizeof(player),f);
    player_locDownload();
    fclose(f);
}

void player_locDownload()
{
    char c[30];
    sprintf(c,"map_%d_%d.txt",player.locpos.x,player.locpos.y);
    loc_LoadFromFile(c);
    sprintf(c,"obj_%d_%d.txt",player.locpos.x,player.locpos.y);
    obj_Download(c);
}

void obj_PutOnMap()
{
    for(int i=0;i<objcnt;i++)
        map[obj[i].pos.y][obj[i].pos.x]=obj[i].type;
}

void Init_Player()
{
    puts("Enter your name:");
    char name[20];
    scanf("%s",name);
    player_Download(name);
}

int main()
{
    Init_Player();
    do
    {
        player_Move();
        loc_PutOnMap();
        obj_PutOnMap();
        player_PutOnMap();
        map_Show();
        Sleep(50);
    }
    while(GetKeyState(VK_ESCAPE)>=0);
    player_Save();
    return 0;
}
