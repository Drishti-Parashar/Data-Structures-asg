#include <stdio.h>
#include <string.h>

#define MAX_MOVIES 30
#define MAX_QUEUE 50
#define MAX_BOOKINGS 100

/* -------------------- STRUCTURES -------------------- */

struct Movie
{
    int id;
    char name[50];
    char genre[20];
    char language[20];
    char time[15];
    int seats;
    float price;
};

struct Customer
{
    char name[50];
    int movieID;
};

struct Booking
{
    int bookingID;
    char customerName[50];
    int movieID;
};

/* -------------------- MOVIE DATASET -------------------- */

struct Movie movies[MAX_MOVIES] =
{
    {101, "Avengers Endgame", "Action", "English", "10:00 AM", 4, 250},
    {102, "Dangal", "Drama", "Hindi", "11:30 AM", 4, 180},
    {103, "3 Idiots", "Comedy", "Hindi", "01:00 PM", 4, 150},
    {104, "Interstellar", "Sci-Fi", "English", "02:30 PM", 4, 300},
    {105, "Kantara", "Thriller", "Kannada", "04:00 PM", 4, 220},
    {106, "Jawan", "Action", "Hindi", "05:30 PM", 4, 200},
    {107, "ZNMD", "Drama", "Hindi", "07:00 PM", 4, 180},
    {108, "Inception", "Sci-Fi", "English", "08:00 PM", 4, 280},
    {109, "Stree 2", "Horror", "Hindi", "09:00 PM", 4, 220},
    {110, "Spider-Man", "Action", "English", "10:00 PM", 4, 270},

    {111, "Pathaan", "Action", "Hindi", "10:30 AM", 4, 230},
    {112, "Barbie", "Comedy", "English", "12:00 PM", 4, 200},
    {113, "Oppenheimer", "Drama", "English", "01:30 PM", 4, 320},
    {114, "KGF Chapter 2", "Action", "Kannada", "03:00 PM", 4, 240},
    {115, "RRR", "Action", "Telugu", "04:30 PM", 4, 250},
    {116, "Taare Zameen Par", "Drama", "Hindi", "06:00 PM", 4, 160},
    {117, "Bhool Bhulaiyaa 2", "Horror", "Hindi", "07:30 PM", 4, 210},
    {118, "Avatar", "Sci-Fi", "English", "09:00 PM", 4, 350},
    {119, "Drishyam 2", "Thriller", "Hindi", "10:00 PM", 4, 190},
    {120, "Pushpa", "Action", "Telugu", "10:30 PM", 4, 230},

    {121, "Lagaan", "Drama", "Hindi", "11:00 AM", 4, 170},
    {122, "Chhichhore", "Comedy", "Hindi", "12:30 PM", 4, 180},
    {123, "The Batman", "Action", "English", "02:00 PM", 4, 280},
    {124, "Joker", "Drama", "English", "03:30 PM", 4, 260},
    {125, "Bahubali", "Action", "Telugu", "05:00 PM", 4, 220},
    {126, "Andhadhun", "Thriller", "Hindi", "06:30 PM", 4, 190},
    {127, "Dunki", "Drama", "Hindi", "08:00 PM", 4, 220},
    {128, "Animal", "Action", "Hindi", "09:30 PM", 4, 250},
    {129, "Toy Story", "Animation", "English", "07:00 PM", 4, 180},
    {130, "Finding Nemo", "Animation", "English", "05:30 PM", 4, 170}
};

/* -------------------- GLOBAL VARIABLES -------------------- */

/* Waiting Queue */
struct Customer waitingQueue[MAX_QUEUE];
int front = -1;
int rear = -1;

/* Bookings */
struct Booking bookings[MAX_BOOKINGS];
int bookingCount = 0;
int nextBookingID = 1;


/* -------------------- FIND MOVIE -------------------- */

int findMovie(int id)
{
    int i;

    for(i = 0; i < MAX_MOVIES; i++)
    {
        if(movies[i].id == id)
        {
            return i;
        }
    }

    return -1;
}


/* -------------------- DISPLAY ALL MOVIES -------------------- */

void displayMovies()
{
    int i;

    printf("\n==================== MOVIE LIST ====================\n");

    printf("%-5s %-22s %-12s %-10s %-12s %-8s %-8s\n",
           "ID", "Movie", "Genre", "Language",
           "Time", "Seats", "Price");

    printf("--------------------------------------------------------------------------\n");

    for(i = 0; i < MAX_MOVIES; i++)
    {
        printf("%-5d %-22s %-12s %-10s %-12s %-8d Rs.%-6.2f\n",
               movies[i].id,
               movies[i].name,
               movies[i].genre,
               movies[i].language,
               movies[i].time,
               movies[i].seats,
               movies[i].price);
    }
}


/* -------------------- SEARCH MOVIE -------------------- */

void searchMovie()
{
    int id;
    int index;

    printf("\nEnter Movie ID to search: ");
    scanf("%d", &id);

    index = findMovie(id);

    if(index == -1)
    {
        printf("\nMovie not found!\n");
        return;
    }

    printf("\nMovie Found!\n");
    printf("-----------------------------\n");
    printf("Movie ID   : %d\n", movies[index].id);
    printf("Movie Name : %s\n", movies[index].name);
    printf("Genre      : %s\n", movies[index].genre);
    printf("Language   : %s\n", movies[index].language);
    printf("Show Time  : %s\n", movies[index].time);
    printf("Seats Left : %d\n", movies[index].seats);
    printf("Price      : Rs. %.2f\n", movies[index].price);
}


/* -------------------- SORT MOVIES -------------------- */

void sortMovies()
{
    int i, j;
    struct Movie temp;

    for(i = 0; i < MAX_MOVIES - 1; i++)
    {
        for(j = 0; j < MAX_MOVIES - i - 1; j++)
        {
            if(movies[j].price > movies[j + 1].price)
            {
                temp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }

    printf("\nMovies sorted by ticket price successfully!\n");

    displayMovies();
}


/* -------------------- ADD TO WAITING QUEUE -------------------- */

void addToQueue(char customerName[], int movieID)
{
    if(rear == MAX_QUEUE - 1)
    {
        printf("\nWaiting Queue is full!\n");
        return;
    }

    if(front == -1)
    {
        front = 0;
    }

    rear++;

    strcpy(waitingQueue[rear].name, customerName);
    waitingQueue[rear].movieID = movieID;

    printf("\nCustomer added to waiting queue successfully!\n");
    printf("Queue Position: %d\n", rear - front + 1);
}


/* -------------------- BOOK TICKET -------------------- */

void bookTicket()
{
    char customerName[50];
    int movieID;
    int index;

    printf("\nEnter Customer Name: ");
    scanf(" %[^\n]", customerName);

    printf("Enter Movie ID: ");
    scanf("%d", &movieID);

    index = findMovie(movieID);

    if(index == -1)
    {
        printf("\nMovie not found!\n");
        return;
    }

    /* If seats are available */
    if(movies[index].seats > 0)
    {
        if(bookingCount >= MAX_BOOKINGS)
        {
            printf("\nBooking storage is full!\n");
            return;
        }

        movies[index].seats--;

        bookings[bookingCount].bookingID = nextBookingID;
        strcpy(bookings[bookingCount].customerName, customerName);
        bookings[bookingCount].movieID = movieID;

        bookingCount++;
        nextBookingID++;

        printf("\nTicket booked successfully!\n");
        printf("Booking ID : %d\n", nextBookingID - 1);
        printf("Customer   : %s\n", customerName);
        printf("Movie      : %s\n", movies[index].name);
        printf("Seats Left : %d\n", movies[index].seats);
    }

    /* If movie is full */
    else
    {
        int choice;

        printf("\nSorry! No seats available for %s.\n", movies[index].name);

        printf("Would you like to join the waiting queue?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            addToQueue(customerName, movieID);
        }
        else
        {
            printf("\nCustomer did not join the waiting queue.\n");
        }
    }
}


/* -------------------- CANCEL TICKET -------------------- */

void cancelTicket()
{
    int bookingID;
    int i, j;
    int movieIndex;
    int found = 0;

    printf("\nEnter Booking ID to cancel: ");

    scanf("%d", &bookingID);

    for(i = 0; i < bookingCount; i++)
    {
        if(bookings[i].bookingID == bookingID)
        {
            found = 1;

            movieIndex = findMovie(bookings[i].movieID);

            if(movieIndex != -1)
            {
                movies[movieIndex].seats++;

                printf("\nBooking cancelled successfully!\n");
                printf("Customer : %s\n", bookings[i].customerName);
                printf("Movie    : %s\n", movies[movieIndex].name);
            }

            /*
               Check if someone is waiting for the same movie.
               If yes, give the newly available seat to that customer.
            */

            for(j = front; j <= rear; j++)
            {
                if(waitingQueue[j].movieID == bookings[i].movieID)
                {
                    if(bookingCount < MAX_BOOKINGS)
                    {
                        printf("\nWaiting customer found!\n");
                        printf("Customer %s gets the available seat.\n",
                               waitingQueue[j].name);

                        movies[movieIndex].seats--;

                        bookings[bookingCount].bookingID = nextBookingID;
                        strcpy(bookings[bookingCount].customerName,
                               waitingQueue[j].name);
                        bookings[bookingCount].movieID =
                               waitingQueue[j].movieID;

                        bookingCount++;
                        nextBookingID++;

                        /* Remove customer from queue */
                        for(int k = j; k < rear; k++)
                        {
                            waitingQueue[k] = waitingQueue[k + 1];
                        }

                        rear--;

                        if(rear < front)
                        {
                            front = -1;
                            rear = -1;
                        }

                        printf("New Booking ID: %d\n",
                               nextBookingID - 1);
                    }

                    break;
                }
            }

            /* Remove cancelled booking */
            for(j = i; j < bookingCount - 1; j++)
            {
                bookings[j] = bookings[j + 1];
            }

            bookingCount--;

            break;
        }
    }

    if(!found)
    {
        printf("\nBooking ID not found!\n");
        printf("Please check the Booking ID from 'Display Current Bookings'.\n");
    }
}


/* -------------------- DISPLAY WAITING QUEUE -------------------- */

void displayQueue()
{
    int i;

    if(front == -1)
    {
        printf("\nWaiting Queue is empty.\n");
        return;
    }

    printf("\n================ WAITING QUEUE ================\n");

    printf("%-10s %-25s %-10s\n",
           "Position", "Customer", "Movie ID");

    printf("-----------------------------------------------\n");

    for(i = front; i <= rear; i++)
    {
        printf("%-10d %-25s %-10d\n",
               i - front + 1,
               waitingQueue[i].name,
               waitingQueue[i].movieID);
    }
}



/* -------------------- DISPLAY BOOKINGS -------------------- */

void displayBookings()
{
    int i;

    if(bookingCount == 0)
    {
        printf("\nNo current bookings.\n");
        return;
    }

    printf("\n================ CURRENT BOOKINGS ================\n");

    printf("%-12s %-25s %-10s %-25s\n",
           "Booking ID", "Customer", "Movie ID", "Movie");

    printf("------------------------------------------------------------------\n");

    for(i = 0; i < bookingCount; i++)
    {
        int movieIndex = findMovie(bookings[i].movieID);

        printf("%-12d %-25s %-10d %-25s\n",
               bookings[i].bookingID,
               bookings[i].customerName,
               bookings[i].movieID,
               movies[movieIndex].name);
    }
}


/* -------------------- MAIN FUNCTION -------------------- */

int main()
{
    int choice;

    do
    {
        printf("\n\n========== MOVIE TICKET BOOKING SYSTEM ==========\n");

        printf("1. Display All Movies\n");
        printf("2. Search Movie\n");
        printf("3. Sort Movies by Price\n");
        printf("4. Book Ticket\n");
        printf("5. Cancel Ticket\n");
        printf("6. Display Waiting Queue\n");
        printf("7. Display Current Bookings\n");
        printf("8. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                displayMovies();
                break;

            case 2:
                searchMovie();
                break;

            case 3:
                sortMovies();
                break;

            case 4:
                bookTicket();
                break;

            case 5:
                cancelTicket();
                break;

            case 6:
                displayQueue();
                break;


            case 7:
                displayBookings();
                break;

            case 8:
                printf("\nThank you for using the Movie Ticket Booking System!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while(choice != 8);

    return 0;
}
