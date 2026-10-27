#include <stdio.h>
#include <string.h>

#define MAX_SEATS 5   /* confirmed seats available on the train */
#define MAX_WAIT  5   /* capacity of the waiting list */

typedef struct {
    int bookingId;
    char name[50];
    int age;
    int seatNo;       /* 0 while on the waiting list */
} Passenger;

/* Confirmed bookings (seats 1..MAX_SEATS) */
Passenger confirmed[MAX_SEATS];
int confirmedCount = 0;
int seatTaken[MAX_SEATS + 1] = {0};

/* Waiting list: circular queue (FIFO) */
Passenger waiting[MAX_WAIT];
int wFront = 0;
int wCount = 0;

int nextId = 1001;

/* ---------- waiting queue operations ---------- */

int waitIsEmpty(void) { return wCount == 0; }
int waitIsFull(void)  { return wCount == MAX_WAIT; }

void enqueueWaiting(Passenger p) {
    int rear = (wFront + wCount) % MAX_WAIT;
    waiting[rear] = p;
    wCount++;
}

Passenger dequeueWaiting(void) {
    Passenger p = waiting[wFront];
    wFront = (wFront + 1) % MAX_WAIT;
    wCount--;
    return p;
}

/* ---------- seat helpers ---------- */

/* Returns the lowest free seat number, or -1 if every seat is taken */
int allocateSeat(void) {
    int i;
    for (i = 1; i <= MAX_SEATS; i++) {
        if (!seatTaken[i]) {
            seatTaken[i] = 1;
            return i;
        }
    }
    return -1;
}

int seatsAvailable(void) {
    return MAX_SEATS - confirmedCount;
}

/* ---------- main operations ---------- */

/* 1. Book ticket */
void bookTicket(void) {
    Passenger p;

    if (seatsAvailable() == 0 && waitIsFull()) {
        printf("Sorry, all seats are booked and the waiting list is full.\n");
        return;
    }

    printf("Enter passenger name: ");
    scanf(" %49[^\n]", p.name);
    do {
        printf("Enter age: ");
        scanf("%d", &p.age);
        if (p.age < 1 || p.age > 120)
            printf("Invalid age, try again.\n");
    } while (p.age < 1 || p.age > 120);

    p.bookingId = nextId++;

    if (seatsAvailable() > 0) {
        p.seatNo = allocateSeat();
        confirmed[confirmedCount++] = p;
        printf("\nBooking CONFIRMED. Booking ID: %d, Seat No: %d\n",
               p.bookingId, p.seatNo);
    } else {
        p.seatNo = 0;
        enqueueWaiting(p);
        printf("\nTrain is full. Added to WAITING LIST. Booking ID: %d, "
               "Waiting position: %d\n", p.bookingId, wCount);
    }
}

/* 2. Cancel ticket */
void cancelTicket(void) {
    int id, i, k, seat, found = -1;
    Passenger promoted;

    printf("Enter booking ID to cancel: ");
    scanf("%d", &id);

    /* search the confirmed list */
    for (i = 0; i < confirmedCount; i++) {
        if (confirmed[i].bookingId == id) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        seat = confirmed[found].seatNo;
        printf("\nBooking %d (%s) cancelled. Seat %d is now free.\n",
               id, confirmed[found].name, seat);

        /* remove the booking: shift later entries left */
        for (i = found; i < confirmedCount - 1; i++)
            confirmed[i] = confirmed[i + 1];
        confirmedCount--;
        seatTaken[seat] = 0;

        /* promote the first passenger from the waiting list */
        if (!waitIsEmpty()) {
            promoted = dequeueWaiting();
            promoted.seatNo = allocateSeat();
            confirmed[confirmedCount++] = promoted;
            printf("Waiting-list passenger %s (Booking ID %d) is now "
                   "CONFIRMED with Seat %d.\n",
                   promoted.name, promoted.bookingId, promoted.seatNo);
        }
        return;
    }

    /* not confirmed: check the waiting list */
    for (i = 0; i < wCount; i++) {
        if (waiting[(wFront + i) % MAX_WAIT].bookingId == id) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        printf("\nWaiting-list booking %d (%s) cancelled.\n",
               id, waiting[(wFront + found) % MAX_WAIT].name);
        /* close the gap, keeping the FIFO order of the others */
        for (k = found; k < wCount - 1; k++)
            waiting[(wFront + k) % MAX_WAIT] =
                waiting[(wFront + k + 1) % MAX_WAIT];
        wCount--;
    } else {
        printf("No booking found with ID %d.\n", id);
    }
}

/* 3. Display bookings */
void displayBookings(void) {
    int i;

    printf("\n===== CONFIRMED PASSENGERS =====\n");
    if (confirmedCount == 0) {
        printf("None.\n");
    } else {
        printf("%-10s %-25s %-5s %-5s\n", "BookingID", "Name", "Age", "Seat");
        printf("------------------------------------------------\n");
        for (i = 0; i < confirmedCount; i++)
            printf("%-10d %-25s %-5d %-5d\n", confirmed[i].bookingId,
                   confirmed[i].name, confirmed[i].age, confirmed[i].seatNo);
    }

    printf("\n===== WAITING LIST (front to rear) =====\n");
    if (waitIsEmpty()) {
        printf("None.\n");
    } else {
        printf("%-5s %-10s %-25s %-5s\n", "Pos", "BookingID", "Name", "Age");
        printf("------------------------------------------------\n");
        for (i = 0; i < wCount; i++) {
            Passenger *p = &waiting[(wFront + i) % MAX_WAIT];
            printf("%-5d %-10d %-25s %-5d\n", i + 1, p->bookingId, p->name, p->age);
        }
    }

    printf("\nSeats available : %d of %d\n", seatsAvailable(), MAX_SEATS);
    printf("Waiting list    : %d of %d\n", wCount, MAX_WAIT);
}

/* ---------- main ---------- */

int main() {
    int choice;

    do {
        printf("\n===== TRAIN TICKET BOOKING SYSTEM =====\n");
        printf("1. Book ticket\n");
        printf("2. Cancel ticket\n");
        printf("3. Display bookings\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookTicket();      break;
            case 2: cancelTicket();    break;
            case 3: displayBookings(); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice, try again.\n");
        }
    } while (choice != 4);

    return 0;
}