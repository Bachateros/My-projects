#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

struct TwentyTime{
    int year,month,day,hour,min;
};

void setcur(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
//����� �������� ������ �� ������
int main()
{
    setlocale(LC_CTYPE,"Russian");
    struct TwentyTime twenty={2023,6,29,12,30};
    while(1)
    {
        time_t mytime = time(NULL);
        struct tm *now = localtime(&mytime);
        int myday=180;
        int ost_month,ost_nedel,ost_day;//ost_hour,ost_min;
        ost_month=twenty.month-now->tm_mon-1;
        ost_day=myday-(ost_month*30);

        /*if(ost_min<0)
        {
            ost_min+=60;
            ost_hour--;
        }
        if(ost_hour<0)
        {
            ost_hour+=24;
            ost_day--;
        }*/
        ost_nedel=ost_day/7;
        ost_day%=7;
        puts("\t   �� 20 ��� ��������:");
        if(ost_month>1)
        {
            if(ost_day>4)
                printf("%d ������\n\n��� %d ������ � %d ����",ost_month, ost_nedel, ost_day);
            else if(ost_day>1)
                printf("%d ������\n\n��� %d ������ � %d ���",ost_month, ost_nedel, ost_day);
            else if(ost_day==1)
                printf("%d ������\n\n��� %d ������ � %d ����",ost_month, ost_nedel, ost_day);
            else
                printf("%d ������\n\n��� %d ������ �����",ost_month, ost_nedel);
        }
        else if(ost_month==1){
            if(ost_day>4)
                printf("%d �����\n\n��� %d ������ � %d ����",ost_month, ost_nedel, ost_day);
            else if(ost_day>1)
                printf("%d �����\n\n��� %d ������ � %d ���",ost_month, ost_nedel, ost_day);
            else if(ost_day==1)
                printf("%d �����\n\n��� %d ������ � %d ����",ost_month, ost_nedel, ost_day);
            else
                printf("%d �����\n\n��� %d ������ �����",ost_month, ost_nedel);
        }
        else{
            printf("\n%d ������ � %d ����", ost_nedel, ost_day);
        }
        /*else
            printf("    ��������: %d ����� %d �����\n", ost_hour,ost_min);*/
        //printf("\n\t\t    Time: %.2d:%.2d:%.2d\n",now->tm_hour,now->tm_min,now->tm_sec);
        Sleep(1000);
        setcur(0,0);
    }
    return 0;
}
