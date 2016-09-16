//Контрольная работа
//Игровые программы
//2. "Пакмэн". Персонаж, управляемый игроком бегает по лабиринту и
//собирает призы, преследуемый оравой монстров.
//Игровое поле смоделировано двумерным символьным массивом VERT_SIZE*HOR_SIZE
//Элементы массива:
//' ' (пробел) - свободно
//'*' - приз
//'\0xDB' - стенка, препятствие
//Дополнительные используемые в программе символы
//'o' - Pac-man
//'O' - Pac-man забирает приз
//'\0xFE' - монстр
//'X' - монстр съедает Pac-Mana
#include <stdio.h>//Для printf()
#include <locale.h>//Для setlocale()
#include <time.h>//Для time()
#include <conio.h>//Для kbhit() и getch()
#include <windows.h>//для SetConsoleCursorPosition()
#define VERT_SIZE	20//Вертикальный размер игрового поля, включая стенки (кол-во текстовых строк)
#define HOR_SIZE	30//Горизонтальный размер игрового поля, включая стенки (кол-во текстовых столбцов)
#define NUMBER_OF_MONSTERS	5//Количество монстров
#define SKIP		8000l//Количество пропусков хода монстров
//Основная функция
void pacMan();
//Выводит игровое поле на экран
int printField();
//Функция отображения монстров на игровом поле
//newMC - массив новых координат монстров
//Строки соответствуют монстрам
//0-й столбец - координата x
//1-й столбец - координата y
//Функция проверяет:
//если новая координата монстра - стенка или препятствие - ничего не делает
//иначе стирает монстра с прежнего места, если нужно восстанавливает приз,
//печатает монстра на новом месте,
//если там Pac-Man - съедает его, возврат 1
//иначе запоминает новые координаты и
//если там приз - запоминает его
//Возвращает 0, если Pac-Man не съеден
//Возвращает 1, если Pac-Man съеден
int moveMonsters(int newMC[][2]);
//Функция отображения Pac-Mana на игровом поле
//newPMC - массив новых координат Pac-Mana
//0-й столбец - координата x
//1-й столбец - координата y
//Функция проверяет:
//если новая координата Pac-Mana - стенка или препятствие - возвращает 0
//иначе стирает Pac-Mana с прежнего места,
//печатает Pac-Mana на новом месте,
//если там монстр - монстр съедает Pac-Mana, возврат 1
//иначе запоминает новые координаты и
//если там приз - забирает его, стирает из массива карты, возвращает -1
//Возвращает 0, если приза нет
int movePacMan(int newPMC[]);
//Перемещение курсора в позицию {x;y}
void gotoxy(int x, int y);
//Установка цвета текста консоли
void textcolor(WORD);
//Глобальный массив игрового поля размер - VERT_SIZE*HOR_SIZE
char field[VERT_SIZE][HOR_SIZE]=
{	{0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB},
	{0xDB,	' ',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	' ',	0xDB},
	{0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	'*',	'*',	'*',	0xDB,	'*',	'*',	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	'*',	'*',	0xDB,	'*',	'*',	'*',	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	'*',	'*',	'*',	0xDB,	'*',	'*',	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	'*',	'*',	0xDB,	'*',	'*',	'*',	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	'*',	'*',	'*',	0xDB,	'*',	'*',	'*',	'*',	'*',	'*',	'*',	' ',	'*',	'*',	'*',	'*',	'*',	'*',	0xDB,	'*',	'*',	'*',	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	'*',	'*',	'*',	0xDB,	'*',	'*',	'*',	'*',	'*',	'*',	' ',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	0xDB,	'*',	'*',	'*',	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	'*',	'*',	0xDB},
	{0xDB,	'*',	'*',	'*',	'*',	'*',	'*',	0xDB,	'*',	'*',	'*',  0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	'*',	'*',	'*',	0xDB,	'*',	'*',	'*',	'*',	'*',	'*',	0xDB},
	{0xDB,	' ',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	'*',	' ',	0xDB},
	{0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB,	0xDB}
};
//Глобальный массив координат монстров
//Кол-во строк соответствует кол-ву монстров
//0-й элемент строки - координата x монстра
//1-й элемент строки - координата y монстра
int monsterCoord[NUMBER_OF_MONSTERS][2]={{1,1},
													  {28,1},
                                         {15,7},
                                         {14,12},
                                         {1,18}};
//Глобальный массив координат Pac-Mana
//0-й элемент строки - координата x
//1-й элемент строки - координата y
int pMCoord[2]={28,18};
void main()
{
   pacMan();
}
//Основная функция игры
void pacMan()
{
	int i;
	int keycode=0;//код нажатой клавиши
	int newPMC[2];//куда передвинуть Pac-Mana
	int newMC[NUMBER_OF_MONSTERS][2];//куда передвинуть монстров
	int numPrizes;//Изначальное количество призов
	int count=0;//Количество съеденных призов
	int stepRes;//Результат шага
	int gameOver=0;//Конец игры
	long int skip=SKIP;//количество пропусков хода монстров
	setlocale(LC_ALL, "ru-Ru.DOS");
	numPrizes=printField();//выводит игровое поле на экран
	moveMonsters(monsterCoord);//расставить на игровом поле монстров
	movePacMan(pMCoord);//Поставить на игровое поле Pac-Mana
	srand(time(NULL));//инициализация генератора случайных чисел 
	while(keycode!=27 && gameOver!=1)//Пока не нажата клавиша escape и не закончена игра
	{
		keycode=0;
		stepRes=0;//результат шага Pac-Mana
		if((skip--)==0)//SKIP шагов пропустили
		{
			skip=SKIP;//В следующий раз опять пропустить SKIP шагов
			//Случайным образом вычислить направления передвижения монстров
			//0 - вверх
			//1 - влево
			//2 - вправо
			//3 - вниз
			for(i=0; i<NUMBER_OF_MONSTERS; i++)
			{
				switch(rand()%4)
				{
					case 0:
						newMC[i][0]=monsterCoord[i][0];
						newMC[i][1]=monsterCoord[i][1]-1;
						break;
					case 1:
						newMC[i][0]=monsterCoord[i][0]-1;
						newMC[i][1]=monsterCoord[i][1];
						break;
					case 2:
						newMC[i][0]=monsterCoord[i][0]+1;
						newMC[i][1]=monsterCoord[i][1];
						break;
					case 3:
						newMC[i][0]=monsterCoord[i][0];
						newMC[i][1]=monsterCoord[i][1]+1;
				}
			}
			stepRes=moveMonsters(newMC);//переместить на игровом поле монстров
			if(stepRes==1)//Pac-Man съеден
			{
				gameOver=1;
				gotoxy(12,VERT_SIZE);//Переместить курсор под игровое поле
				textcolor(FOREGROUND_RED | FOREGROUND_INTENSITY);
				printf("Game over! Nyam-Nyam!");
				Sleep(3000);
			}
			stepRes=0;
		}
		if(_kbhit())//нажата клавиша
		{
			keycode=_getch();//считывание символа из буфера клавиатуры
		}
		switch (keycode)
		{
			case 72://стрелка вверх
				newPMC[0]=pMCoord[0];
				newPMC[1]=pMCoord[1]-1;
				stepRes=movePacMan(newPMC);//Передвинуть Pac-Mana
				break;
			case 75://стрелка влево
				newPMC[0]=pMCoord[0]-1;
				newPMC[1]=pMCoord[1];
				stepRes=movePacMan(newPMC);//Передвинуть Pac-Mana
				break;
			case 77://стрелка вправо
				newPMC[0]=pMCoord[0]+1;
				newPMC[1]=pMCoord[1];
				stepRes=movePacMan(newPMC);//Передвинуть Pac-Mana
				break;
			case 80://стрелка вниз
				newPMC[0]=pMCoord[0];
				newPMC[1]=pMCoord[1]+1;
				stepRes=movePacMan(newPMC);//Передвинуть Pac-Mana
		}
		if(stepRes==1)//Съел монстр
		{
			gameOver=1;
			gotoxy(12,VERT_SIZE);//Переместить курсор под игровое поле
            textcolor(FOREGROUND_RED | FOREGROUND_INTENSITY);
			printf("Game over! Nyam-Nyam!");
			Sleep(3000);
		}
		if (stepRes == -1)//Приз
		{
            count++;
         	gotoxy(7,VERT_SIZE);//Переместить курсор под игровое поле
            printf("   ");//Очистить поле (3 символа) для вывода счета
			gotoxy(7, VERT_SIZE);//Переместить курсор под игровое поле
			textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			printf("%-3d", count);
            if(count==numPrizes)//Собрали все призы
            {
				gameOver=1;
				gotoxy(12,VERT_SIZE);//Переместить курсор под игровое поле
				textcolor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            	printf("Game over! Victory!");
				Sleep(3000);
            }
		}      
	}
}
//Выводит игровое поле на экран (стенки, препятствия и призы)
//Подсчитывает количество звездочек (призов)
int printField()
{
   int i,j;
   int nPrizes=0;//количество призов
   for(i=0; i<VERT_SIZE; i++)
   {
      for(j=0; j<HOR_SIZE; j++)
      {
      	if(field[i][j]=='*')//приз
         {
         	textcolor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            nPrizes++;
         }
         else//стенка, препятствие или пусто
         {
			 textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
         }
   		printf("%c",field[i][j]);
      }
      printf("\n");
   }
   printf("Count: %d",0);//количество призов
   return nPrizes;
}
//Функция отображения монстров на игровом поле
//newMC - массив новых координат монстров
//Строки соответствуют монстрам
//0-й столбец - координата x
//1-й столбец - координата y
//Функция проверяет:
//если новая координата монстра - стенка или препятствие - возвращает 0
//иначе стирает монстра с прежнего места, если нужно восстанавливает приз,
//печатает монстра на новом месте,
//если там Pac-Man - съедает его, возврат 1
//иначе запоминает новые координаты
//Возвращает 0, если Pac-Man не съеден
//Возвращает 1, если Pac-Man съеден
int moveMonsters(int newMC[][2])
{
   int i;
	for(i=0; i<NUMBER_OF_MONSTERS; i++)//i - номер монстра
   {
   	if(field[newMC[i][1]][newMC[i][0]]!=(char)0xDB)//если не стенка и не препятствие
      {
		//Поставить курсор в старую позицию монстра
      	gotoxy(monsterCoord[i][0],monsterCoord[i][1]);
		if(field[monsterCoord[i][1]][monsterCoord[i][0]]=='*')//если под монстром был приз
		{
			//Напечатать приз в старые координаты монстра
			textcolor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("*");
		}
		else
		{
            //Напечатать пробел в старые координаты монстра
			printf(" ");
		}
		//Поставить курсор в новую позицию монстра
      	gotoxy(newMC[i][0],newMC[i][1]);
      	//Напечатать монстра на новом месте
      	textcolor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
      	printf("%c",0xFE);
      	if(newMC[i][0]==pMCoord[0] && newMC[i][1]==pMCoord[1])//координаты монстра и Pac-Mana совпадают
      	{
      		//Поставить курсор в новую позицию монстра
      		gotoxy(newMC[i][0],newMC[i][1]);
      		//Съесть Pac-Mana
         	textcolor(FOREGROUND_RED | FOREGROUND_INTENSITY);
      		printf("X");
         	return 1;//Pac-Man съеден
      	}
         //Запомнить новые координаты монстра
         monsterCoord[i][0]=newMC[i][0];
         monsterCoord[i][1]=newMC[i][1];
      }
   }
   return 0;
}
//Функция отображения Pac-Mana на игровом поле
//newPMC - массив новых координат Pac-Mana
//0-й столбец - координата x
//1-й столбец - координата y
//Функция проверяет:
//если новая координата Pac-Mana - стенка или препятствие - возвращает 0
//иначе стирает Pac-Mana с прежнего места,
//печатает Pac-Mana на новом месте,
//если там монстр - монстр съедает Pac-Mana, возврат 1
//иначе запоминает новые координаты и
//если там приз - забирает его, стирает из массива карты, возвращает -1
//Возвращает 0, если приза нет
int movePacMan(int newPMC[])
{
	int i;
	if(field[newPMC[1]][newPMC[0]]!=(char)0xDB)//если не стенка и не препятствие
	{
		//Поставить курсор в старую позицию Pac-Mana
		gotoxy(pMCoord[0],pMCoord[1]);
		//Напечатать пробел в старые координаты Pac-Mana
		printf(" ");
		//Поставить курсор в новую позицию Pac-Mana
		gotoxy(newPMC[0],newPMC[1]);
		//Напечатать Pac-Mana на новом месте
		textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("o");
		for(i=0; i<NUMBER_OF_MONSTERS; i++)//i - номер монстра
		{
			if(newPMC[0]==monsterCoord[i][0] && newPMC[1]==monsterCoord[i][1])//координаты монстра и Pac-Mana совпадают
			{
				//Поставить курсор в новую позицию Pac-Mana
				gotoxy(newPMC[0],newPMC[1]);
				//Съесть Pac-Mana
				textcolor(FOREGROUND_RED | FOREGROUND_INTENSITY);
				printf("X");
				return 1;//Pac-Man съеден
			}
		}
		//Запомнить новые координаты Pac-Mana
		pMCoord[0]=newPMC[0];
		pMCoord[1]=newPMC[1];
		if(field[newPMC[1]][newPMC[0]]=='*')//если под Pac-Manом - приз
		{
			//Поставить курсор в новую позицию Pac-Mana
			gotoxy(newPMC[0],newPMC[1]);
			//Забрать приз
			textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			printf("O");
			Sleep(40); 	// sleep time in milliseconds
			gotoxy(newPMC[0],newPMC[1]);
			printf("o");
			//Стереть из массива карты приз
			field[newPMC[1]][newPMC[0]]=' ';
			return -1;//приз забрали
		}
	}
	return 0;
}
//Перемещение курсора в позицию {x;y} для 32-битной версии
void gotoxy(int x, int y)
{
	HANDLE hs;
	COORD c = { x, y };
	hs = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hs,c);
}
//Установка цвета текста консоли
void textcolor(WORD attr)
{
	HANDLE hs;
	hs = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hs, attr);
}