#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<windows.h>

/* 
 *
 * Start of Helper Functions
 * 
 */

void gotoxy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	
	return;
}

void delline(unsigned int lines) {
	COORD coord;
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO info;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	coord.X = info.dwCursorPosition.X;
	coord.Y = info.dwCursorPosition.Y;

	FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
	info.dwSize.X - (coord.X - 1) + (info.dwSize.X * (lines == 0 ? 0:(lines - 1))),
	coord, &written);
	gotoxy(info.dwCursorPosition.X, info.dwCursorPosition.Y);
}

int center(int y, const char *format, ...){
	va_list arg;
	int done, x;
	CONSOLE_SCREEN_BUFFER_INFO info;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	x = (info.dwSize.X / 2) - (strlen(format) - (strlen(format)) / 2);
	gotoxy(x,y);
	va_start (arg, format);
	done = vfprintf (stdout, format, arg);
	va_end (arg);

	return done;
}

void drawSBox(int x1,int y1,int x2,int y2){
    int i = 0;
    for(i=x1;i<=x2;i++){
        gotoxy(i,y1);
        printf("%c",196);
        gotoxy(i,y2);
        printf("%c",196);
    }
    for(i=y1;i<=y2;i++){
        gotoxy(x1,i);
        printf("%c",179);
        gotoxy(x2,i);
        printf("%c",179);
    }
    gotoxy(x1,y1);
    printf("%c",218);
    gotoxy(x1,y2);
    printf("%c",192);
    gotoxy(x2,y1);
    printf("%c",191);
    gotoxy(x2,y2);
    printf("%c",217);

    return;
}

/* 
 *
 * End of Helper Functions
 * 
 */

void initSeats(int seats[], int size){
    //initializes seats to 0
    memset(seats, '\0', (size / 2) * sizeof(seats));
}

void displaySeats(int seats[], int size){
    //displays seats
    int i = 0;

    gotoxy(0,0);
    center(3,"Welcome to MGM Airlines");
    center(5,"First Class Section:                    ");
    gotoxy(61,5);
    for(i = 0;i < (size / 2);i++)
        printf("[%d] ",seats[i]);
    center(6,"Economy Section:                      ");
    gotoxy(61,6);
    for(i = 5;i < size;i++)
        printf("[%d] ",seats[i]);
    center(8,"Please type 1 for \"first class\"");
    center(9,"Please type 2 for \"economy\"");
}

int assignFirstClass(int seats[], int size){
    //assigns seat and returns seat number, if there's no available seat, returns -1
    int i = 0;

    for(i = 0;i < size;i++)
        if(seats[i] == 0){
            seats[i] = 1;
            return i;
        }
    
    return -1;
}

int assignEconomy(int seats[], int size){
    //assigns seat and returns seat number, if there's no available seat, returns -1
    int i = 0;

    for(i = 5;i < size;i++)
        if(seats[i] == 0){
            seats[i] = 1;
            return i;
        }
    
    return -1;
}

int assignSeat(int st[], int seatType){
    //returns 1 if assignment of seat is successful, calls assignFirstClass() if
	//seatType is 1 and assignEconomy if seatType is 2
    int res = 0;

    if(seatType == 1){
        res = assignFirstClass(st,5);
        return ((res == -1) ? -1:res);
    }
    else if(seatType == 2){
        res = assignEconomy(st,10);
        return ((res == -1) ? -1:res);
    }
    return 0;
}

void boardPass(int seat){
    //displays the boarding pass
    drawSBox(48,12,70,16);
    center(13,"Boarding Pass");
    if(seat < 5)
        center(14,"First Class Section");
    else if(seat < 10)
        center(14,"Economy Section");
    center(15,"Seat #%d",seat + 1);
}

char Exit(char choice){
    //displays exit message if all seats are already taken or when the person
	//doesn't want to take a seat.
    char inpt;

    if(choice == 'n')
        center(18,"Next flight leaves in 3 hours.");
    else
        center(18,"All seats are taken.");
    center(20,"Do you want to run again? Y/N: ");
    do{
        fflush(stdin);
        gotoxy(75,20);
        scanf("%c",&inpt);
        gotoxy(75,20);
        delline(1);
        inpt = tolower(inpt);
        if(inpt != 'y' && inpt != 'n')
            center(22,"Invalid input! Please try again!");
    }while(inpt != 'y' && inpt != 'n');
    system("cls");
    if(inpt == 'n'){
        center(1,"Program Terminated!");
        gotoxy(0,2);
        sleep(2);
        exit(0);
    }
    return inpt;
}
