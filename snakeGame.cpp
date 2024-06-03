#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define BoardXMax 102
#define BoardYMax 21
#define BoardXMin 1
#define BoardYMin 1
int snakeXMin = 2,snakeXMax = 101,snakeYMin = 2,snakeYMax = 20;
char direction = 'R';
int snakeLength = 5;
int appleX,appleY;
int appleFlag = 1;
void gotoxy(int x,int y)
{
    printf("\033[%d;%dH", (y), (x));
}

struct snake
{
    int x,y;
    struct snake * next;
};
struct snake * head = NULL;
void PrintBoard()
{
     for(int i = BoardYMin ; i <= BoardYMax ; i++)
    {
        for(int j = BoardXMin ; j <= BoardXMax ; j++)
        {
            if(i == BoardYMin && j == BoardXMin)
            {
                printf("%c",201);
            }
            else if(i == BoardYMin && j == BoardXMax)
            {
                printf("%c",187);
            }
            else if(i == BoardYMax && j == BoardXMin)
            {
                printf("%c",200);
            }
            else if(i == BoardYMax && j == BoardXMax)
            {
                printf("%c",188);
            }
            else if((i == BoardYMin || i == BoardYMax) && (j > BoardXMin && j < BoardXMax))
            {
                printf("%c",205);
            }
            else if((j == BoardXMin || j == BoardXMax) && (i > BoardYMin && i < BoardYMax))
            {
                printf("%c",186);
            }
            else
                printf(" ");
        }
        printf("\n");
    }
}

void printSnake()
{
    for(int i = 1 ; i <= 5 ; i++)
    {
        struct snake *temp = (struct snake*)malloc(sizeof(struct snake));
        temp->x = i + 1;
        temp->y = 2;
        temp->next = NULL;
        gotoxy(temp->x,temp->y);
        printf("*");
        if(head == NULL)
        {
            head = temp;
        }
        else
        {
            temp->next = head;
            head = temp;
        }
    }
}
int Move()
{
    struct snake *temp=NULL;
    int newx,newy;
    switch(direction)
    {
        case 'R':
            newx=head->x+1;
            newy=head->y;
            break;
        case 'L':
            newx=head->x-1;
            newy=head->y;
            break;
        case 'U':
            newx=head->x;
            newy=head->y-1;
            break;
        case 'D':
            newx=head->x;
            newy=head->y+1;
            break;
    }
    if(newx > snakeXMax)
        newx=snakeXMin;
    if(newy > snakeYMax)
        newy=snakeYMin;
    if(newx < snakeXMin)
        newx=snakeXMax;
    if(newy < snakeXMin)
        newy=snakeYMax;

    struct snake*temp1 = head;
    for(int i = 0 ; i < snakeLength ; i++)
    {
        if(temp1->x == newx && temp1->y == newy)
        {
            return 1;
        }
        temp1 = temp1->next;
    }
    temp = (struct snake*) malloc(sizeof(struct snake));
    temp->x=newx;
    temp->y=newy;
    temp->next=head;
    head=temp;
    gotoxy(newx,newy);
    switch (direction)
    {
        case 'R':
            printf("%c",16);
            break;
        case 'L':
            printf("%c",17);
            break;
        case 'U':
            printf("%c",30);
            break;
        case 'D':
            printf("%c",31);
            break;    
    }
    

    //delete_tail
    temp = head;
    while(temp->next->next!=NULL)
    {
        temp=temp->next;
    }
    gotoxy(temp->next->x,temp->next->y);
    printf(" ");
    free(temp->next);
    temp->next=NULL;
    return 0;
}

void addNode()
{
    struct snake *newNode =(struct snake *)malloc(sizeof(struct snake)),*temp = head;
    int newx,newy;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    switch (direction)
    {
        case 'R':
            newx= temp->x - 1;
            newy= temp->y;
            break;
        case 'L':
            newx= temp->x + 1;
            newy= temp->y;
            break;
        case 'U':
            newy= temp->y + 1;
            newx= temp->x;
            break;
        case 'D':
            newy= temp->y - 1;
            newx= temp->x;
            break;
    }
    if(newx > snakeXMax)
        newx=snakeXMin;
    if(newy > snakeYMax)
        newy=snakeYMin;
    if(newx < snakeXMin)
        newx=snakeXMax;
    if(newy < snakeXMin)
        newy=snakeYMax;
    newNode->x = newx;
    newNode->y = newy;
    newNode->next =NULL;
    temp->next =newNode;
}

int Random(int lower, int upper)
{
    srand(time(NULL));
	return lower + rand() % (upper - lower + 1);
}

void printApple()
{
    appleX=Random(snakeXMin+2,snakeXMax-2);
    appleY=Random(snakeYMin+2,snakeYMax-2);
    appleFlag = -1;
    gotoxy(appleX,appleY);
    printf("%c",64);
}
int main()
{
    
    PrintBoard();
    printSnake();
    while(snakeLength < 25)
    {
        if(head->x == appleX && head->y == appleY)
        {
            addNode();
            snakeLength++;
            appleFlag = 1;
        }
        if(appleFlag != -1)
        {
            printApple();
        }
        if(Move() == 1)
        {
            gotoxy(BoardXMax/2 -10,BoardYMax/2);
            printf("THE SNAKE ATE ITSELF :(");
            break;
        }
        gotoxy(1,BoardYMax+1);
        printf("SCORE : %d",snakeLength);
        if(kbhit())
        {
            if(getch()==224)
            {
                switch(getch())
                {
                    case 75: direction='L';
                    break;
                    case 77: direction='R';
                    break;
                    case 72: direction='U';
                    break;
                    case 80: direction='D';
                    break;
                }
            }
            else
            {
                break;
            }
        }
        if(direction == 'R' || direction == 'L')
            Sleep(100);
        else if(direction == 'U' || direction == 'D')
            Sleep(150);    
    }
    if(snakeLength == 25)
    {
        gotoxy(BoardXMax/2 -10,BoardYMax/2);
        printf("Congratulations You Won :D");
    }
    getch();
    return 0;
}