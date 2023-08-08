#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<locale.h>

int main()
{
    setlocale(LC_ALL,"Russian");

    char pole[10][21];
    int i;
    int x=10,y=5;//координаты собаки
    int ox,oy;//координаты перед следущим ходом, чтобы не пройти сквозь стены
    int ax=5,ay=3;//координаты €блока
    char key;//действие
    srand(time(NULL));//рандомайзер
    int counter=0;//счетчик €блок

    do
    {
        //создание пол€
        sprintf(pole,"####################");
        for(i=1;i<9;i++)sprintf(pole[i],"#                  #");
        sprintf(pole[9],"####################");

        system("cls");
        pole[y][x]=2;
        pole[ay][ax]=1;
        //вывод пол€
        puts("ƒл€ передвижени€ используйте кнопки wasd");
        puts("ƒл€ выхода из игры нажмите e\n");
        for(i=0;i<10;i++)
            printf("%s\n",pole[i]);
        printf("\n оличество съеденных €блок = %d\n",counter);

        key=getch();
        ox=x,oy=y;
        switch(key)//передвижение
        {
            case'w':y--;break;
            case's':y++;break;
            case'a':x--;break;
            case'd':x++;
        }
        if(pole[y][x]=='#')//чтобы не пройти сквозь стену
        {
            x=ox;
            y=oy;
        }
        if((x==ax) && (y==ay))
        {
            ax=rand()*1.0/RAND_MAX * 18+1;
            ay=rand()*1.0/RAND_MAX * 8 +1;
            counter++;
        }
    }
    while(key!='e');//условие выхода
}
