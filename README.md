# Airline Reservation System

A small airline has just purchased a computer for its new automated reservations system. The president has asked you to program the new system. You are to write a program to assign seats on each flight of the airline's only plane (capacity: 10 seats).

Your program should display the following menu of alternatives:

Please type 1 for "first class"
Please type 2 for "economy"

If the person types 1, then your program should assign a seat in the first class section (seats 1-5). If the person types 2, then your program should assign a seat in the economy section (seats 6-10). Your program should then print a boarding pass indicating the person's seat number and whether it is in the first class or economy section of the plane.
Use a single-subscripted array to represent the seating chart of the plane. Initialize all the elements of the array to 0 to indicate that all seats are empty. As each seat is assigned, set the corresponding elements of the array to 1 to indicate that the seat is no longer available.
Your program should, of course, never assign a seat that has already been assigned. When the first class section is full, your program should ask the person if it is acceptable to be placed in the economy section (and vice versa). If yes, then make the appropriate seat assignment. If no, then print the message "Next flight leaves in 3 hours."

Use and implement the following functions:
```c
// initializes seats to 0
void initSeats(int seats[], int size);

// displays seats
void displaySeats(int seats[], int size);

// returns 1 if assignment of seat is successful, calls assignFirstClass() if seatType is 1 and assignEconomy if seatType is 2
int assignSeat(int st[], int seatType);

// assigns seat and returns seat number, if there's no available seat, returns -1
int assignFirstClass(int seats[], int size);

// assigns seat and returns seat number, if there's no available seat, returns -1
int assignEconomy(int seats[], int size);

// displays the boarding pass
void boardPass(int seat);

// displays exit message if all seats are already taken or when the person doesn't want to take a seat.
void exit(void);
```