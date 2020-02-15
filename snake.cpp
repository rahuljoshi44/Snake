#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>

int mapHeight=20;
int mapWidth=60;

struct element
{
    int posX;
    int posY;
}snake,tail[100],fruit;

void checkHit(int &amp;Dir,int &amp;g)
{
    if(kbhit())
    {
        switch(getch())
		 {
			case 'w':Dir=1;
				 break;
			case 'a':Dir=2;
				 break;
			case 's':Dir=3;
				 break;
			case 'd':Dir=4;
				 break;
			case 'q':g=0;
				 break;

		  }
    }
}
void updatePos(int &x, int &y,int dir)
 {
	if(dir==1)
	    y--;
	if(dir==2)
	    x--;
	if(dir==3)
	    y++;
	if(dir==4)
	    x++;
 }

void drawMap(int x, int y,int fx, int fy,int tc, element t[100],int &g)
 {
	for(int i=0;i<mapHeight;i++)
	{
		for(int j=0;j<mapWidth;j++)
		{
		    int check=0;
		  for(int a=0;a<tc;a++)
		  {
			if(t[a].posY==i&&t[a].posX==j)
			{
                cout<<char(219);
                check=1;
			}
			if(t[a].posY==y&&t[a].posX==x)
			    g=0;
		  }
		  if(x==0||x==mapWidth-1||y==0||y==mapHeight-1)
		    g=0;
		  else if(i==0&&j!=0&&j!=mapWidth-1)
		    cout<<char(205);
		  else if(i==0&&j==0)
		    cout<<char(201);
		  else if(i==mapHeight-1&&j==0)
		    cout<<char(200);
		  else if(j==0&&i!=0)
		    cout<<char(186);
		  else if(i==0&&j==mapWidth-1)
		    cout<<char(187);
		  else if(i==mapHeight-1&&j!=mapWidth-1)
		    cout<<char(205);
		  else if(i==mapHeight-1&&j==mapWidth-1)
		    cout<<char(188);
		  else if(j==mapWidth-1&&i!=0)
		    cout<<char(186);
		  else if(i==y&&j==x)
		    cout<<char(219);
		  else if(i==fy&&j==fx)
		    cout<<"*";
		  else if(check==0)
		     cout<<" ";
		}
		 cout<<"\n";
	 }
 }

void fruitCheck(int x, int y, int &fx, int &fy,int &tc,int &f)
 {
	if(x==fx&&y==fy)
	{
		randomize();
		fx=random(mapWidth);
		fy=random(mapHeight);
		tc+=2;
		f++;
	}
 }

void updateTail(int x,int y, element tail[100],int tc)
 {
	int prevX=tail[0].posX;
	int prevY=tail[0].posY;
	tail[0].posX=x;
	tail[0].posY=y;
	int switchX;
	int switchY;
	for(int i=1;i<tc;i++)
	{
		switchX=tail[i].posX;
		switchY=tail[i].posY;
		tail[i].posX=prevX;
		tail[i].posY=prevY;
		prevX=switchX;
		prevY=switchY;
	}
 }

void status(int x, int y, int tx, int ty, int fe)
 {
	cout<<"\n\t\t\t    SCORE:"<<fe;
	cout<<"\n\t\t W:UP A:LEFT S:DOWN D:RIGHT";
	cout<<"\n\t\t\tPRESS Q TO QUIT";
 }

void instructions()
 {
	cout<<"\t\t\t\tINSTRUCTIONS\n";
	cout<<"\t\t\t\t************";
	cout<<"\nIn SNAKE, you have to eat the fruit that may spawn in any ";
	cout<<"location on the map,\nwithout hitting the walls or your own tail.";
	cout<<"After eating a fruit, you gain a\npoint and your tail increases in length.";
	cout<<"The goal is to get as many points as\npossible.";
	cout<<"\n\n\t\t\t\tControls:\n";
	cout<<"\t\t\t\t\W:UP\n\t\t\t\tA:LEFT\n\t\t\t\tS:DOWN\n\t\t\t\tD:RIGHT\n";
	cout<<"\nThe snake moves on its own, you do not need to continually press ";
	cout<<"the key to keepit moving.";
	cout<<"\n\n\n\n\n\n\t\t\tPRESS ANY BUTTON TO CONTINUE";
	getch();
 }

void main()
 {
	clrscr();
	textcolor(GREEN);
	instructions();
	int highScore=0;
	start:
	randomize();
	int gameOver=1;
	int dir;
	int tailCount=0;
	int fruitsEaten=0;
	char choice;

	snake.posX=20;
	snake.posY=11;
	fruit.posX=random(mapWidth-1);
	fruit.posY=random(mapHeight-1);

	if(choice=='1')
	 dir=0;
    do
	{
	  clrscr();
	  randomize();
	  cout<<"\t\t\t   SNAKE\n";
	  drawMap(snake.posX,snake.posY,fruit.posX,fruit.posY,tailCount,tail,gameOver);
	  updateTail(snake.posX,snake.posY,tail,tailCount);
	  checkHit(dir,gameOver);
	  updatePos(snake.posX,snake.posY,dir);
	  fruitCheck(snake.posX,snake.posY,fruit.posX,fruit.posY,tailCount,fruitsEaten);
	  status(snake.posX,snake.posY,fruit.posX,fruit.posY,fruitsEaten);
	  delay(75);
	}while(gameOver==1);
	if(fruitsEaten>highScore)
	highScore=fruitsEaten;
	clrscr();
	cout<<"\n\t\t\t\t GAME OVER";
	cout<<"\n\t\t\t\t *********";
	cout<<"\n\t\t\t\t SCORE:"<<fruitsEaten;
	cout<<"\n\t\t\t\t HIGH SCORE:"<<highScore;
	cout<<"\n\t\t\t\t PLAY AGAIN(1)";
	choice=getch();
	if(choice=='1')
	goto start;
 }
