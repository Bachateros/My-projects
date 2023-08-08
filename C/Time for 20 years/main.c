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
//ћожно заменить мес€цы на недели
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
        puts("\t   ƒо 20 лет осталось:");
        if(ost_month>1)
        {
            if(ost_day>4)
                printf("%d мес€ца\n\n»ли %d недель и %d дней",ost_month, ost_nedel, ost_day);
            else if(ost_day>1)
                printf("%d мес€ца\n\n»ли %d недель и %d дн€",ost_month, ost_nedel, ost_day);
            else if(ost_day==1)
                printf("%d мес€ца\n\n»ли %d недель и %d день",ost_month, ost_nedel, ost_day);
            else
                printf("%d мес€ца\n\n»ли %d недель ровно",ost_month, ost_nedel);
        }
        else if(ost_month==1){
            if(ost_day>4)
                printf("%d мес€ц\n\n»ли %d недель и %d дней",ost_month, ost_nedel, ost_day);
            else if(ost_day>1)
                printf("%d мес€ц\n\n»ли %d недель и %d дн€",ost_month, ost_nedel, ost_day);
            else if(ost_day==1)
                printf("%d мес€ц\n\n»ли %d недель и %d день",ost_month, ost_nedel, ost_day);
            else
                printf("%d мес€ц\n\n»ли %d недель ровно",ost_month, ost_nedel);
        }
        else{
            printf("\n%d недель и %d дней", ost_nedel, ost_day);
        }
        /*else
            printf("    ќсталось: %d часов %d минут\n", ost_hour,ost_min);*/
        //printf("\n\t\t    Time: %.2d:%.2d:%.2d\n",now->tm_hour,now->tm_min,now->tm_sec);
        Sleep(1000);
        setcur(0,0);
    }
    return 0;
}
