//����������� ������
//������� ���������
//2. "������". ��������, ����������� ������� ������ �� ��������� �
//�������� �����, ������������ ������ ��������.
//������� ���� ������������� ��������� ���������� �������� VERT_SIZE*HOR_SIZE
//�������� �������:
//' ' (������) - ��������
//'*' - ����
//'\0xDB' - ������, �����������
//�������������� ������������ � ��������� �������
//'o' - Pac-man
//'O' - Pac-man �������� ����
//'\0xFE' - ������
//'X' - ������ ������� Pac-Mana
#include <stdio.h>//��� printf()
#include <locale.h>//��� setlocale()
#include <time.h>//��� time()
#include <conio.h>//��� kbhit() � getch()
#include <windows.h>//��� SetConsoleCursorPosition()
#define VERT_SIZE	20//������������ ������ �������� ����, ������� ������ (���-�� ��������� �����)
#define HOR_SIZE	30//�������������� ������ �������� ����, ������� ������ (���-�� ��������� ��������)
#define NUMBER_OF_MONSTERS	5//���������� ��������
#define SKIP		8000l//���������� ��������� ���� ��������
//�������� �������
void pacMan();
//������� ������� ���� �� �����
int printField();
//������� ����������� �������� �� ������� ����
//newMC - ������ ����� ��������� ��������
//������ ������������� ��������
//0-� ������� - ���������� x
//1-� ������� - ���������� y
//������� ���������:
//���� ����� ���������� ������� - ������ ��� ����������� - ������ �� ������
//����� ������� ������� � �������� �����, ���� ����� ��������������� ����,
//�������� ������� �� ����� �����,
//���� ��� Pac-Man - ������� ���, ������� 1
//����� ���������� ����� ���������� �
//���� ��� ���� - ���������� ���
//���������� 0, ���� Pac-Man �� ������
//���������� 1, ���� Pac-Man ������
int moveMonsters(int newMC[][2]);
//������� ����������� Pac-Mana �� ������� ����
//newPMC - ������ ����� ��������� Pac-Mana
//0-� ������� - ���������� x
//1-� ������� - ���������� y
//������� ���������:
//���� ����� ���������� Pac-Mana - ������ ��� ����������� - ���������� 0
//����� ������� Pac-Mana � �������� �����,
//�������� Pac-Mana �� ����� �����,
//���� ��� ������ - ������ ������� Pac-Mana, ������� 1
//����� ���������� ����� ���������� �
//���� ��� ���� - �������� ���, ������� �� ������� �����, ���������� -1
//���������� 0, ���� ����� ���
int movePacMan(int newPMC[]);
//����������� ������� � ������� {x;y}
void gotoxy(int x, int y);
//��������� ����� ������ �������
void textcolor(WORD);
//���������� ������ �������� ���� ������ - VERT_SIZE*HOR_SIZE
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
//���������� ������ ��������� ��������
//���-�� ����� ������������� ���-�� ��������
//0-� ������� ������ - ���������� x �������
//1-� ������� ������ - ���������� y �������
int monsterCoord[NUMBER_OF_MONSTERS][2]={{1,1},
													  {28,1},
                                         {15,7},
                                         {14,12},
                                         {1,18}};
//���������� ������ ��������� Pac-Mana
//0-� ������� ������ - ���������� x
//1-� ������� ������ - ���������� y
int pMCoord[2]={28,18};
void main()
{
   pacMan();
}
//�������� ������� ����
void pacMan()
{
	int i;
	int keycode=0;//��� ������� �������
	int newPMC[2];//���� ����������� Pac-Mana
	int newMC[NUMBER_OF_MONSTERS][2];//���� ����������� ��������
	int numPrizes;//����������� ���������� ������
	int count=0;//���������� ��������� ������
	int stepRes;//��������� ����
	int gameOver=0;//����� ����
	long int skip=SKIP;//���������� ��������� ���� ��������
	setlocale(LC_ALL, "ru-Ru.DOS");
	numPrizes=printField();//������� ������� ���� �� �����
	moveMonsters(monsterCoord);//���������� �� ������� ���� ��������
	movePacMan(pMCoord);//��������� �� ������� ���� Pac-Mana
	srand(time(NULL));//������������� ���������� ��������� ����� 
	while(keycode!=27 && gameOver!=1)//���� �� ������ ������� escape � �� ��������� ����
	{
		keycode=0;
		stepRes=0;//��������� ���� Pac-Mana
		if((skip--)==0)//SKIP ����� ����������
		{
			skip=SKIP;//� ��������� ��� ����� ���������� SKIP �����
			//��������� ������� ��������� ����������� ������������ ��������
			//0 - �����
			//1 - �����
			//2 - ������
			//3 - ����
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
			stepRes=moveMonsters(newMC);//����������� �� ������� ���� ��������
			if(stepRes==1)//Pac-Man ������
			{
				gameOver=1;
				gotoxy(12,VERT_SIZE);//����������� ������ ��� ������� ����
				textcolor(FOREGROUND_RED | FOREGROUND_INTENSITY);
				printf("Game over! Nyam-Nyam!");
				Sleep(3000);
			}
			stepRes=0;
		}
		if(_kbhit())//������ �������
		{
			keycode=_getch();//���������� ������� �� ������ ����������
		}
		switch (keycode)
		{
			case 72://������� �����
				newPMC[0]=pMCoord[0];
				newPMC[1]=pMCoord[1]-1;
				stepRes=movePacMan(newPMC);//����������� Pac-Mana
				break;
			case 75://������� �����
				newPMC[0]=pMCoord[0]-1;
				newPMC[1]=pMCoord[1];
				stepRes=movePacMan(newPMC);//����������� Pac-Mana
				break;
			case 77://������� ������
				newPMC[0]=pMCoord[0]+1;
				newPMC[1]=pMCoord[1];
				stepRes=movePacMan(newPMC);//����������� Pac-Mana
				break;
			case 80://������� ����
				newPMC[0]=pMCoord[0];
				newPMC[1]=pMCoord[1]+1;
				stepRes=movePacMan(newPMC);//����������� Pac-Mana
		}
		if(stepRes==1)//���� ������
		{
			gameOver=1;
			gotoxy(12,VERT_SIZE);//����������� ������ ��� ������� ����
            textcolor(FOREGROUND_RED | FOREGROUND_INTENSITY);
			printf("Game over! Nyam-Nyam!");
			Sleep(3000);
		}
		if (stepRes == -1)//����
		{
            count++;
         	gotoxy(7,VERT_SIZE);//����������� ������ ��� ������� ����
            printf("   ");//�������� ���� (3 �������) ��� ������ �����
			gotoxy(7, VERT_SIZE);//����������� ������ ��� ������� ����
			textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			printf("%-3d", count);
            if(count==numPrizes)//������� ��� �����
            {
				gameOver=1;
				gotoxy(12,VERT_SIZE);//����������� ������ ��� ������� ����
				textcolor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            	printf("Game over! Victory!");
				Sleep(3000);
            }
		}      
	}
}
//������� ������� ���� �� ����� (������, ����������� � �����)
//������������ ���������� ��������� (������)
int printField()
{
   int i,j;
   int nPrizes=0;//���������� ������
   for(i=0; i<VERT_SIZE; i++)
   {
      for(j=0; j<HOR_SIZE; j++)
      {
      	if(field[i][j]=='*')//����
         {
         	textcolor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            nPrizes++;
         }
         else//������, ����������� ��� �����
         {
			 textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
         }
   		printf("%c",field[i][j]);
      }
      printf("\n");
   }
   printf("Count: %d",0);//���������� ������
   return nPrizes;
}
//������� ����������� �������� �� ������� ����
//newMC - ������ ����� ��������� ��������
//������ ������������� ��������
//0-� ������� - ���������� x
//1-� ������� - ���������� y
//������� ���������:
//���� ����� ���������� ������� - ������ ��� ����������� - ���������� 0
//����� ������� ������� � �������� �����, ���� ����� ��������������� ����,
//�������� ������� �� ����� �����,
//���� ��� Pac-Man - ������� ���, ������� 1
//����� ���������� ����� ����������
//���������� 0, ���� Pac-Man �� ������
//���������� 1, ���� Pac-Man ������
int moveMonsters(int newMC[][2])
{
   int i;
	for(i=0; i<NUMBER_OF_MONSTERS; i++)//i - ����� �������
   {
   	if(field[newMC[i][1]][newMC[i][0]]!=(char)0xDB)//���� �� ������ � �� �����������
      {
		//��������� ������ � ������ ������� �������
      	gotoxy(monsterCoord[i][0],monsterCoord[i][1]);
		if(field[monsterCoord[i][1]][monsterCoord[i][0]]=='*')//���� ��� �������� ��� ����
		{
			//���������� ���� � ������ ���������� �������
			textcolor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("*");
		}
		else
		{
            //���������� ������ � ������ ���������� �������
			printf(" ");
		}
		//��������� ������ � ����� ������� �������
      	gotoxy(newMC[i][0],newMC[i][1]);
      	//���������� ������� �� ����� �����
      	textcolor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
      	printf("%c",0xFE);
      	if(newMC[i][0]==pMCoord[0] && newMC[i][1]==pMCoord[1])//���������� ������� � Pac-Mana ���������
      	{
      		//��������� ������ � ����� ������� �������
      		gotoxy(newMC[i][0],newMC[i][1]);
      		//������ Pac-Mana
         	textcolor(FOREGROUND_RED | FOREGROUND_INTENSITY);
      		printf("X");
         	return 1;//Pac-Man ������
      	}
         //��������� ����� ���������� �������
         monsterCoord[i][0]=newMC[i][0];
         monsterCoord[i][1]=newMC[i][1];
      }
   }
   return 0;
}
//������� ����������� Pac-Mana �� ������� ����
//newPMC - ������ ����� ��������� Pac-Mana
//0-� ������� - ���������� x
//1-� ������� - ���������� y
//������� ���������:
//���� ����� ���������� Pac-Mana - ������ ��� ����������� - ���������� 0
//����� ������� Pac-Mana � �������� �����,
//�������� Pac-Mana �� ����� �����,
//���� ��� ������ - ������ ������� Pac-Mana, ������� 1
//����� ���������� ����� ���������� �
//���� ��� ���� - �������� ���, ������� �� ������� �����, ���������� -1
//���������� 0, ���� ����� ���
int movePacMan(int newPMC[])
{
	int i;
	if(field[newPMC[1]][newPMC[0]]!=(char)0xDB)//���� �� ������ � �� �����������
	{
		//��������� ������ � ������ ������� Pac-Mana
		gotoxy(pMCoord[0],pMCoord[1]);
		//���������� ������ � ������ ���������� Pac-Mana
		printf(" ");
		//��������� ������ � ����� ������� Pac-Mana
		gotoxy(newPMC[0],newPMC[1]);
		//���������� Pac-Mana �� ����� �����
		textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("o");
		for(i=0; i<NUMBER_OF_MONSTERS; i++)//i - ����� �������
		{
			if(newPMC[0]==monsterCoord[i][0] && newPMC[1]==monsterCoord[i][1])//���������� ������� � Pac-Mana ���������
			{
				//��������� ������ � ����� ������� Pac-Mana
				gotoxy(newPMC[0],newPMC[1]);
				//������ Pac-Mana
				textcolor(FOREGROUND_RED | FOREGROUND_INTENSITY);
				printf("X");
				return 1;//Pac-Man ������
			}
		}
		//��������� ����� ���������� Pac-Mana
		pMCoord[0]=newPMC[0];
		pMCoord[1]=newPMC[1];
		if(field[newPMC[1]][newPMC[0]]=='*')//���� ��� Pac-Man�� - ����
		{
			//��������� ������ � ����� ������� Pac-Mana
			gotoxy(newPMC[0],newPMC[1]);
			//������� ����
			textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			printf("O");
			Sleep(40); 	// sleep time in milliseconds
			gotoxy(newPMC[0],newPMC[1]);
			printf("o");
			//������� �� ������� ����� ����
			field[newPMC[1]][newPMC[0]]=' ';
			return -1;//���� �������
		}
	}
	return 0;
}
//����������� ������� � ������� {x;y} ��� 32-������ ������
void gotoxy(int x, int y)
{
	HANDLE hs;
	COORD c = { x, y };
	hs = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hs,c);
}
//��������� ����� ������ �������
void textcolor(WORD attr)
{
	HANDLE hs;
	hs = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hs, attr);
}