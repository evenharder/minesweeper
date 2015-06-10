//	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	//
//				W		I		N		M		I		N		E				//
//	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	//
// 				array[y][x]......												// 

#include <stdio.h>

#include <conio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#include <windows.h>

//	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	//

#define col GetStdHandle(STD_OUTPUT_HANDLE)

#define RED SetConsoleTextAttribute( col,0x000c );

#define BLUE SetConsoleTextAttribute( col,0x0001 | 0x0008);
 
#define HIGH SetConsoleTextAttribute( col,0x00a);

#define WHITE SetConsoleTextAttribute( col,0x000f);

#define SKY SetConsoleTextAttribute( col, 0x000b);

#define YEL SetConsoleTextAttribute( col, 0x000e);

#define FLUOR SetConsoleTextAttribute( col, 0x000d);

#define VIO SetConsoleTextAttribute( col,0x0001 | 0x0008 |0x000c); 

#define BCK SetConsoleTextAttribute( col,0x0000);

#define GRAY SetConsoleTextAttribute( col,0x0008);

#define WHT SetConsoleTextAttribute( col,0x000F);

#define HIGHGRAY SetConsoleTextAttribute( col,0x00a | 0x0000);
//	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	//

#define ScreenX 70 // Screen Width 

#define ScreenY 41 // Screen Height

#define LEFT 75

#define RIGHT 77

#define UP 72

#define DOWN 80

#define ENTER 13

#define ESC 27

#define SPACE 32 

#define SHIFT 15

//	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	//

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

int Field[40][40];

int ShownField[40][40];

int Flag[40][40]; 

int Search[40][40];

int Wrong[40][40];

int FieldX;

int FieldY;

int Diff=1;

int Flag_Amount;

int Mine_Amount;

int Space_Left;

int real_p=1;

int game_over;

int Wrong_guess;

//	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	//

void setcursortype(CURSOR_TYPE c);

void gotoxy(int x, int y);

void Arrayprint(char a[], int x, int y, int delay);

void EmptyArray();

void random();

void DrawScreenEdge();

void Intro();

void clrscr();

void Difficulty();

void NumberField();

//void ShowMine();

void DrawMineEdge();

void PrintField();

void Move();

void rerandom(int y, int x);

void RevealValue(int y, int x);

void Expand0(int y, int x);

void PlayAgain();


//	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	//
int main()
{
	setcursortype(NOCURSOR);
	
	DrawScreenEdge();
	
	Intro();
	
	while(real_p)
	{
		clrscr();
		
		Difficulty();
		
		clrscr();
		
		EmptyArray();
		
		random();
		
		NumberField();
		
		//ShowMine();
		
		DrawMineEdge();
		
		Move();	
		
		PlayAgain();
	
	}
	gotoxy(0,ScreenY);
	
}

//	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	//

void setcursortype(CURSOR_TYPE c)
{
 	CONSOLE_CURSOR_INFO CurInfo;
 	switch (c) 
 	{
		case NOCURSOR:
 	
		CurInfo.dwSize=1;
		CurInfo.bVisible=FALSE;
		break;
  
		case SOLIDCURSOR:
 	
		CurInfo.dwSize=100;
		CurInfo.bVisible=TRUE;
		break;
  
		case NORMALCURSOR:
		
		CurInfo.dwSize=20;
		CurInfo.bVisible=TRUE;
		break;
 	}
 	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}

void gotoxy(int x,int y)
{
	COORD Cur;
	Cur.Y=y;
    Cur.X=x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}

void Arrayprint(char a[],int x,int y,int delay)
{
	int i,l;
	l=strlen(a);
	for(i=x;i<x+l;i++)
	{
		gotoxy(i,y);
		printf("%c",a[i-x]);
		Sleep(delay); //windows.h
	}
}

void EmptyArray()
{
	for(int i=0;i<40;i++)
	{
		for(int j=0;j<40;j++)
		{
			Flag[i][j]=0;
			ShownField[i][j]=0;
			Field[i][j]=0;
			Search[i][j]=0;
			Wrong[i][j]=0;
		}
	}
}

void random()
{
	int i=0;
	srand((unsigned)time(NULL));
	while(Mine_Amount!=i)
	{
		reshuffle:
	
		int randx=rand()%FieldX+1;
		int randy=rand()%FieldY+1;
	
		if(Field[randy][randx])
		{
			goto reshuffle;
		}
		else
		{
			Field[randy][randx]='*';
			i++;
		}
	}	
}

void ColorNumber(int x)
{
	SetConsoleTextAttribute(col,x-48);
	printf("%d ",x-48);
}

void DrawScreenEdge()
{
	int i;

	for(i=0;i<ScreenX;i++)
	{	
		gotoxy(i,0);
		putch('+');
	}

	for(i=1;i<ScreenX;i++)
	{	
		gotoxy(i,5);
		putch('-');
	}
	
	for(i=0;i<ScreenY;i++)
	{
		gotoxy(ScreenX,i);
		putch('+');
	}

	for(i=ScreenX;i>0;i--)
	{
		gotoxy(i,ScreenY);
		putch('+');
	}
	
	for(i=ScreenY;i>0;i--)
	{
		gotoxy(0,i);
		putch('+');
	}
	WHT;
	
	gotoxy(8,ScreenY-3);
	printf("Move :");
	
	SKY;
	
	printf(" Arrow Keys ");
	WHT;
	printf(" Reveal :");
	
	YEL;
	
	printf(" Enter Key ");
	WHT;
	printf(" Flag :");
	
	VIO;
	printf(" Space Key");
	WHT;
	gotoxy(0,ScreenY);
}

void Intro()
{

	SKY;
	
	char game_name[25]={'W','I','N','M','I','N','E',' ','C','M','D',' ','V','e','r','.'};

	Arrayprint(game_name,10,2,30);
	
	YEL;
	
	char programmed_by[30]={'P','r','o','g','r','a','m','m','e','d',' ','b','y',' '};
	
	Arrayprint(programmed_by,40,2,30);
	
	HIGH;
	
	char evenharder[12]={'E','v','e','n','h','a','r','d','e','r','.'};

	//char seungwonpark[14]={'S','e','u','n','g','w','o','n','P','a','r','k'};

	Arrayprint(evenharder,54,2,40);
	
	WHT;
	
	Sleep(200);

}

void Difficulty()
{
	int ch;
	char selectdiff[25]={'S','e','l','e','c','t',' ','t','h','e',' ','d','i','f','f','i','c','u','l','t','y','.'};
	Arrayprint(selectdiff,23,8,40);
	
	YEL;
	
	gotoxy(30,16);
	printf("Tiny");
	
	gotoxy(28,16);
	printf("-");
	
	WHT;
	
	gotoxy(30,18);
	printf("Small");
	
	gotoxy(30,20);
	printf("Large");
	
	Diff=1;
	
	while(ch!=ENTER)
	{
	
	gotoxy(30,25);
	ch=getch();
	
	if(ch==0xE0 || ch==0)
	
		{
			ch=getch();
			
			if(Diff==1 && ch==DOWN)
			{
				Diff++;
				
				YEL;
				gotoxy(28,16);
				putch(' ');
				gotoxy(30,18);
				printf("Small");
				gotoxy(28,18);
				putch('-');
				
				WHT;
				gotoxy(30,16);
				printf("Tiny");
			}
			else if(Diff==2 && ch==UP)
			{
				Diff--;
				
				YEL;
				gotoxy(28,18);
				putch(' ');
				gotoxy(30,16);
				printf("Tiny");
				gotoxy(28,16);
				putch('-');
				
				WHT;
				gotoxy(30,18);
				printf("Small");
			}
			else if(Diff==2 && ch==DOWN)
			{
				Diff++;
				
				YEL;
				gotoxy(28,18);
				putch(' ');
				gotoxy(30,20);
				printf("Large");
				gotoxy(28,20);
				putch('-');
				
				WHT;
				gotoxy(30,18);
				printf("Small");
			}
			else if(Diff==3 && ch==UP)
			{
				Diff--;
				
				YEL;
				gotoxy(28,20);
				putch(' ');
				gotoxy(30,18);
				printf("Small");
				gotoxy(28,18);
				putch('-');
				
				WHT;
				gotoxy(30,20);
				printf("Large");
			}
		}
		else if(ch==ESC) {gotoxy(0,ScreenY); exit(1);}
	}
	
	VIO;
	
	if(Diff==1)
	{
		FieldX=9;
		FieldY=9;
		Mine_Amount=10;
		char tiny[8]{'T','i','n','y','.'};
		Arrayprint(tiny,30,25,40);
	}
	else if(Diff==2)
	{
		FieldX=16;
		FieldY=16;
		Mine_Amount=40;
		char small[8]{'S','m','a','l','l','.'};
		Arrayprint(small,30,25,40);
	}
	else //(Diff==3)
	{
		FieldX=30;
		FieldY=16;
		Mine_Amount=99;
		char large[8]{'L','a','r','g','e','.'};
		Arrayprint(large,30,25,40);
	}
	
	Space_Left=FieldX*FieldY;
	WHT;
	
	Sleep(350);
	
	gotoxy(0,ScreenY);
}

void clrscr()
{
	int i,j;
	
	for(i=1;i<ScreenX;i++)
	{
		gotoxy(i,4);
		putch(' ');
		for(j=6;j<ScreenY-3;j++)
		{
			gotoxy(i,j);
			putch(' ');
		}
	}
	gotoxy(0,ScreenY);
}

void DrawMineEdge()
{
	int i;
	GRAY;
	for(i=35-FieldX-2;i<35+FieldX+1;i++)
	{	
		gotoxy(i,8);
		putch('+');
	}

	for(i=8;i<12+FieldY;i++)
	{
		gotoxy(35+FieldX+1,i);
		putch('+');
	}
	for(i=35+FieldX+1;i>35-FieldX-2;i--)
	{
		gotoxy(i,12+FieldY);
		putch('+');
	}
	
	for(i=12+FieldY;i>8;i--)
	{
		gotoxy(35-FieldX-2,i);
		putch('+');
	}
	WHT;
	gotoxy(0,ScreenY);
}

void PrintField() //For Dubugging
{
	for(int i=1;i<=FieldY;i++)
	{
		gotoxy(35-FieldX,i+10);
		for(int j=1;j<=FieldX;j++)
		{
			if(Field[i][j]=='*')
			{
				if(Flag[i][j])
				{
					VIO;
					printf("> ");
				}	
				else
				{
					GRAY;printf("%c ",Field[i][j]);WHT;
				}
			}
			else if(Flag[i][j]){RED;printf("><");WHT;}
			else if((Field[i][j]!=48)&&Field[i][j])ColorNumber(Field[i][j]);
			else printf("  ");
		}
	}
}

void NumberField()
{
	for(int i=1;i<=FieldY;i++)
	{
		for(int j=1;j<=FieldX;j++)
		{	
			int Near_Mine=0;
			if(Field[i][j]!='*')
			{
				if(Field[i-1][j-1]=='*') Near_Mine++;
				if(Field[i-1][j]=='*') Near_Mine++;
				if(Field[i-1][j+1]=='*') Near_Mine++;
				if(Field[i][j+1]=='*') Near_Mine++;
				if(Field[i+1][j+1]=='*') Near_Mine++;
				if(Field[i+1][j]=='*') Near_Mine++;
				if(Field[i+1][j-1]=='*') Near_Mine++;
				if(Field[i][j-1]=='*') Near_Mine++;
				Field[i][j]=Near_Mine+48;
			}
		}
	}
}

void Expand0(int y, int x)
{
	if((x>FieldX)||(x<1)||(y>FieldY)||(y<1)) {BCK;return;}
	if(ShownField[y][x]==1) {BCK;return;}
	else
	{
		if(Flag[y][x])
		{
			Wrong[y][x]=1;
			Wrong_guess++;
			BCK;
			return;
		}
		if(Field[y][x]!='0')
		{
			gotoxy(33-FieldX+2*x,y+10);
			ColorNumber(Field[y][x]);
			Space_Left--;
			ShownField[y][x]=1;
			WHT;
		}
		else
		{
			BCK;
			gotoxy(33-FieldX+2*x,y+10);
			printf("[]");
			Space_Left--;
			ShownField[y][x]=1;
			Expand0(y-1,x-1);
			Expand0(y-1,x);
			Expand0(y-1,x+1);
			Expand0(y,x+1);
			Expand0(y+1,x+1);
			Expand0(y+1,x);
			Expand0(y+1,x-1);
			Expand0(y,x-1);
		}
	}
}

void PlayAgain()
{
	int temp_play=1;
	int ch;
	char apply_limit[50]={'P','l','a','y',' ','a','g','a','i','n','?'};
	FLUOR;
	Arrayprint(apply_limit,28,30,50);
	
	FLUOR;
	gotoxy(33,32);
	printf("YES");
	
	gotoxy(31,32);
	printf("\-");
	
	WHT;
	
	gotoxy(33,34);
	printf("NO");
	
	
	while(ch!=ENTER)
	{
	ch=getch();
	
	if(ch==0xE0 || ch==0)
	
		{
			ch=getch();
			
			if(temp_play==1 && ch==DOWN)
			{
				temp_play=0;
				
				FLUOR;
				gotoxy(31,34);
				printf("\-");
				gotoxy(33,34);
				printf("NO");
				WHT;
				gotoxy(33,32);
				printf("YES");
				gotoxy(31,32);
				putch(' ');

			}
			else if(temp_play==0 && ch==UP)
			{
				temp_play=1;
				
				FLUOR;
				gotoxy(31,32);
				printf("\-");
				gotoxy(33,32);
				printf("YES");
				WHT;
				gotoxy(33,34);
				printf("NO");
				gotoxy(31,34);
				putch(' ');

			}
		}
		else if(ch==ESC) {gotoxy(0,ScreenY); exit(1);}		
	}
	real_p=temp_play;
	
	char game_end[25]={'C','l','o','s','i','n','g',' ','P','r','o','g','r','a','m','.','.','.','.','.','.'};
	
	FLUOR;
	
	if(real_p==0)
	
	Arrayprint(game_end,25,36,50);
	
	WHT;
	
	Sleep(350);

}

void RevealValue(int y, int x)
{
	if((x>FieldX)||(x<1)||(y>FieldY)||(y<1)||(Flag[y][x])) return;
	
	if(ShownField[y][x]==0)
	{
		if(Field[y][x]=='*')
		{
			WHT;
			if(game_over==0) PrintField();
			HIGH;
			if(Flag[y][x]==1)SKY;
			gotoxy(33-FieldX+2*x,y+10);
			printf("\* ");
			gotoxy(30,4);
			RED;
			printf("GAME OVER");
			WHT;
			game_over++;
		}
		else if(Field[y][x]!='0')
		{
			HIGH;
			gotoxy(33-FieldX+2*x,y+10);
			ColorNumber(Field[y][x]);
			ShownField[y][x]=1;
			Space_Left--;
			WHT;
			if(Flag[y][x])
			{
				Flag[y][x]=0;
				Flag_Amount--;
			}
		}
		else
		{
			Expand0(y,x);
			BCK;
			gotoxy(33-FieldX+2*x,y+10);
			printf("[]");
			WHT;
			
		}
	}
	else return;
}

void rerandom(int y, int x)
{	
	if(Field[y][x]=='*')
	{
		Field[y][x]=48;
		
		if(Field[y-1][x-1]!='*') Field[y-1][x-1]--; else Field[y][x]++;
		if(Field[y-1][x]!='*') Field[y-1][x]--;	else Field[y][x]++;
		if(Field[y-1][x+1]!='*') Field[y-1][x+1]--;	else Field[y][x]++;
		if(Field[y][x+1]!='*') Field[y][x+1]--;	else Field[y][x]++;
		if(Field[y+1][x+1]!='*') Field[y+1][x+1]--;	else Field[y][x]++;
		if(Field[y+1][x]!='*') Field[y+1][x]--;	else Field[y][x]++;	
		if(Field[y+1][x-1]!='*') Field[y+1][x-1]--;	else Field[y][x]++;
		if(Field[y][x-1]!='*') Field[y][x-1]--;	else Field[y][x]++;
		
		again:
	
		int randy=rand()%FieldY+1;
		int randx=rand()%FieldX+1;
		if(x==randx&&y==randy) 
		{
			Field[randy][randx]=48;
			goto again;
		}
		
		if(Field[randy][randx]=='*')
		{
			Field[randy][randx]=48;
			goto again;
		}
		else 
		{
			Field[randy][randx]='*';
			randy--; randx--;
			if(Field[randy][randx]!='*') Field[randy][randx]++;
			randx++;
			if(Field[randy][randx]!='*') Field[randy][randx]++;
			randx++;
			if(Field[randy][randx]!='*') Field[randy][randx]++;
			randy++;
			if(Field[randy][randx]!='*') Field[randy][randx]++;
			randy++;
			if(Field[randy][randx]!='*') Field[randy][randx]++;
			randx--;
			if(Field[randy][randx]!='*') Field[randy][randx]++;
			randx--;
			if(Field[randy][randx]!='*') Field[randy][randx]++;
			randy--;
			if(Field[randy][randx]!='*') Field[randy][randx]++;
			randx++;
		}
	}
}

void Move()
{
	
	int x=1;
	int y=1;
	int pre_x=0;
	int pre_y=0;
	int pre_pre_x=-1;
	int pre_pre_y=-1; 
	int try_=0;
	int ch;
	Flag_Amount=0;
	game_over=0;
	Wrong_guess=0;
	{
		for(int i=1;i<=FieldY;i++)
		{
			gotoxy(35-FieldX,i+10);
			for(int j=1;j<=FieldX;j++)
			{
				printf("[]");
			}
		}
	}
	gotoxy(33-FieldX+2*x,y+10);
	HIGH;
	printf("[]");
	WHT;
	while(1)
	{
		fflush(stdin);
		WHT;
		gotoxy(2,4);
		printf("Flag Left : %3d",Mine_Amount-Flag_Amount);
		gotoxy(53,4);
		printf("Space Left : ");
		gotoxy(66,4);
		printf("%3d",Space_Left-Mine_Amount);
		gotoxy(33,9);
		YEL;
		printf("\^\-\^");
		WHT;
		
		while(ch!=ENTER)
		{
			ch=getch();
			
			if(ch==0xE0 || ch==0)
			{
				ch=getch();
				
				if(ch==LEFT)
				{
					if(x>1)
					{
						WHT;
						gotoxy(33-FieldX+2*x,y+10);
						if(ShownField[y][x])
						{
							if(Field[y][x]!='0')
							{
								ColorNumber(Field[y][x]);
							}
							else
							{
								BCK;
								printf("[]");
								WHT;
							}
							
						}
						else if(Flag[y][x])
						{
							FLUOR;
							printf("> ");
							WHT;
						}
						else
						{
							printf("[]");
						}
						
						x--;
						HIGH;
					
						gotoxy(33-FieldX+2*x,y+10);
						if(ShownField[y][x])
						{
							if(Field[y][x]!='0')
							{
								printf("%c ",Field[y][x]);
							}
							else
							{
								HIGHGRAY;
								printf("[]");
								WHT;
							}
							
						}
						else if(Flag[y][x])
						{
							printf("> ");
							WHT;
						}
						else
						{
							printf("[]");
						}
						
					}
				}
				else if(ch==RIGHT)
				{
					if(x<FieldX)
					{
						WHT;
						gotoxy(33-FieldX+2*x,y+10);
						if(ShownField[y][x])
						{
							if(Field[y][x]!='0')
							{
								ColorNumber(Field[y][x]);
							}
							else
							{
								BCK;
								printf("[]");
								WHT;
							}
							
						}
						else if(Flag[y][x])
						{
							FLUOR;
							printf("> ");
							WHT;
						}
						else
						{
							printf("[]");
						}
						
						x++;
						HIGH;
					
						gotoxy(33-FieldX+2*x,y+10);
						if(ShownField[y][x])
						{
							if(Field[y][x]!='0')
							{
								printf("%c ",Field[y][x]);
							}
							else
							{
								HIGHGRAY;
								printf("[]");
								WHT;
							}
							
						}
						else if(Flag[y][x])
						{
							printf("> ");
							WHT;
						}
						else
						{
							printf("[]");
						}
					}
				}
				else if(ch==UP)
				{
					if(y>1)
					{
						WHT;
						gotoxy(33-FieldX+2*x,y+10);
						if(ShownField[y][x])
						{
							if(Field[y][x]!='0')
							{
								ColorNumber(Field[y][x]);
							}
							else
							{
								BCK;
								printf("[]");
								WHT;
							}
							
						}
						else if(Flag[y][x])
						{
							FLUOR;
							printf("> ");
							WHT;
						}
						else
						{
							printf("[]");
						}
						
						y--;
						HIGH;
						
						gotoxy(33-FieldX+2*x,y+10);
						if(ShownField[y][x])
						{
							if(Field[y][x]!='0')
							{
								printf("%c ",Field[y][x]);
							}
							else
							{
								HIGHGRAY;
								printf("[]");
								WHT;
							}
							
						}
						else if(Flag[y][x])
						{
							printf("> ");
							WHT;
						}
						else
						{
							printf("[]");
						}
					}
				}
				else if(ch==DOWN)
				{
					if(y<FieldY)
					{
						WHT;
						gotoxy(33-FieldX+2*x,y+10);
						if(ShownField[y][x])
						{
							if(Field[y][x]!='0')
							{
								ColorNumber(Field[y][x]);
							}
							else
							{
								BCK;
								printf("[]");
								WHT;
							}
							
						}
						else if(Flag[y][x])
						{
							FLUOR;
							printf("> ");
							WHT;
						}
						else
						{
							printf("[]");
						}
						
						y++;
						HIGH;
						
						gotoxy(33-FieldX+2*x,y+10);
						if(ShownField[y][x])
						{
							if(Field[y][x]!='0')
							{
								printf("%c ",Field[y][x]);
							}
							else
							{
								HIGHGRAY;
								printf("[]");
								WHT;
							}
							
						}
						else if(Flag[y][x])
						{
							printf("> ");
							WHT;
						}
						else
						{
							printf("[]");
						}
					}
				}
			}
			else if((ch==SPACE)&&ShownField[y][x]==0)
			{
				gotoxy(33-FieldX+2*x,y+10);
				if(Flag[y][x]==0)
				{
					HIGH;
					printf("> ");
					WHT;
					Flag[y][x]=1;
					Flag_Amount++;
					if(Field[y][x]=='*') Wrong[y][x]=1;
				}
				else
				{
					HIGH;
					printf("[]");
					Flag[y][x]=0;
					WHT;
					Flag_Amount--;
					if(Field[y][x]=='*') Wrong[y][x]=0;
				}
				WHT;
				gotoxy(2,4);
				printf("Flag Left : %3d",Mine_Amount-Flag_Amount);
			}
		}
		
		try_++;
		
		if(try_==1) 
		{
			rerandom(y,x);
		}
		
		if(Flag[y][x]==0)RevealValue(y,x);
		
		if(ShownField[y][x]&&Field[y][x]!='0') // 
		{	
			int whether_open;
			whether_open=Flag[y-1][x-1]+Flag[y-1][x]+Flag[y-1][x+1]+Flag[y][x+1]+Flag[y+1][x+1]+Flag[y+1][x]+Flag[y+1][x-1]+Flag[y][x-1];
			if(whether_open==Field[y][x]-48)
			{
				if(!Flag[y-1][x-1])RevealValue(y-1,x-1);
				if(!Flag[y-1][x])RevealValue(y-1,x);
				if(!Flag[y-1][x+1])RevealValue(y-1,x+1);
				if(!Flag[y][x+1])RevealValue(y,x+1);
				if(!Flag[y+1][x+1])RevealValue(y+1,x+1);
				if(!Flag[y+1][x])RevealValue(y+1,x);
				if(!Flag[y+1][x-1])RevealValue(y+1,x-1);
				if(!Flag[y][x-1])RevealValue(y,x-1);			
			}
		}
		
		if(Wrong_guess>=1)
		{
			PrintField();
			gotoxy(30,4);
			RED;
			printf("GAME OVER");
			game_over=1;
		}
		if(game_over>=1) 
		{
			gotoxy(33,9);
			YEL;
			printf("x\_x");
			goto end;
		}
		else if(Flag[y][x])
		{
			;
		}
		else if(Field[y][x]=='*')
		{
			;
		}
		else if(Field[y][x]!=48)
		{
			gotoxy(33-FieldX+2*x,y+10);
			HIGH;
			printf("%c ",Field[y][x]);
		}
		else
		{
			gotoxy(33-FieldX+2*x,y+10);
			HIGH;
			printf("[]");
		}
		
		if(Space_Left==Mine_Amount)
		{
			WHT;
			gotoxy(2,4);
			printf("Flag Left :   0");
			gotoxy(53,4);
			printf("Space Left :   0");
			gotoxy(33,9);
			YEL;
			printf("\#\^\#");
			HIGH;
			gotoxy(25,4);
			printf("Congratulations\!");
			break;
		}
	ch=0;
	
	}
	
	end:
	;
}
//	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	//
