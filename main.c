#include<stdio.h>
#include<windows.h>
#include<ctype.h>
#include"airlines.h"

char inpt(void){
    char inpt;
    center(10,"Your choice:  ");
    do{
        fflush(stdin);
        gotoxy(66,10);
        delline(1);
        gotoxy(66,10);
        scanf("%c",&inpt);
        if(inpt != '1' && inpt != '2'){
            gotoxy(0,12);
            delline(5);
            center(12,"Invalid input! Please try again!");
        }
    }while(inpt != '1' && inpt != '2');

    return inpt;
}

char chElse(int choice){
    char ch1[] = "first class", ch2[] = "economy", inpt;

    center(12,"Sorry for the inconvenience, but the %s is already full.\n",(choice == 1 ? ch1:ch2));
    center(13,"Would it be acceptable to be placed in the %s section?\n\n",(choice == 1 ? ch2:ch1));
    center(14,"Please type \"Y\" for Yes and \"N\" for No: ");
    do{
        fflush(stdin);
        gotoxy(80,14);
        scanf("%c",&inpt);
        gotoxy(80,14);
        delline(3);
        inpt = tolower(inpt);
        if(inpt != 'y' && inpt != 'n')
            center(16,"Invalid input! Please try again!");
    }while(inpt != 'y' && inpt != 'n');

    return inpt;
}

int main(void){
    int seats[10], size = 10;
    int res = 0, choice = 0, ch0 = 0;

    
    initSeats(seats,size);
    while(1){
        displaySeats(seats,size);
        if(ch0 == 'n' || (seats[4] == 1 && seats[9] == 1))
            if(Exit(ch0) == 'y'){
                ch0 = '\0';
                initSeats(seats,size);
                displaySeats(seats,size);
            }
        choice = ((int) inpt()) - 48;
        res = assignSeat(seats,choice);
        if(choice == 1){
            gotoxy(0,12);
            delline(5);
            if(res != -1)
                boardPass(res);
            else if((ch0 = chElse(choice)) == 'y'){
                gotoxy(0,12);
                delline(3);
                res = assignSeat(seats,2);
                boardPass(res);
            }
        }else if(choice == 2){
            gotoxy(0,12);
            delline(5);
            if(res != -1)
                boardPass(res);
            else if((ch0 = chElse(choice)) == 'y'){
                gotoxy(0,12);
                delline(3);
                res = assignSeat(seats,1);
                boardPass(res);
            }
        }
    }

    return 0;
}