#ifndef BT24CSE051_H
#define BT24CSE051_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern int BookingId;

typedef enum
{
    Cab = 0,
    Bike = 1
} VehicleType;
typedef enum
{
    Free = 0,
    booked = 1
} DriverStatus;

typedef struct
{
    int x;
    int y;
} Location;

typedef struct Driver_tag
{
    int d_Id;
    char name[50];
    VehicleType v_Type;
    DriverStatus d_Status;
    Location loc;
    float total_Earnings;
    int height;
    struct Driver_tag *left;
    struct Driver_tag *right;
} Driver;

typedef struct Passenger_tag
{
    int p_Id;
    char name[50];
    char number[15];
    int frequency;
    int height;
    struct Passenger_tag *left;
    struct Passenger_tag *right;
} Passenger;

typedef struct Booking_tag
{
    int b_Id;
    int d_Id;
    int p_Id;
    VehicleType v_Type;
    float distance;
    float fare;
    int date;
    int height;
    struct Booking_tag *left;
    struct Booking_tag *right;
} Booking;

// AVL helpers
int getHeight(int h);
int getBalance(int lh, int rh);

// Driver AVL
Driver *newDriverNode(int id, char name[], int type, int x, int y);
Driver *rotateRightDriver(Driver *y);
Driver *rotateLeftDriver(Driver *x);
Driver *insertDriver(Driver *root, int id, char name[], int type, int x, int y);
Driver *minDriverNode(Driver *root);
Driver *deleteDriverNode(Driver *root, int id);
Driver *findDriverByID(Driver *root, int d_id);
void inorderDrivers(Driver *root);

// Passenger AVL
Passenger *newPassengerNode(int id, char name[], char mobile[]);
Passenger *rotateRightPassenger(Passenger *y);
Passenger *rotateLeftPassenger(Passenger *x);
Passenger *insertPassenger(Passenger *root, int id, char name[], char mobile[]);
Passenger *findPassengerByID(Passenger *root, int p_id);
Passenger *findPassengerByMobile(Passenger *root, char mobile[]);
void inorderPassengers(Passenger *root);

// Booking AVL
Booking *newBookingNode(int b_id, int d_id, int p_id, VehicleType vt);
Booking *rotateRightBooking(Booking *y);
Booking *rotateLeftBooking(Booking *x);
Booking *insertBooking(Booking *root, int b_id, int d_id, int p_id, VehicleType vt);
Booking *findBookingByID(Booking *root, int b_id);
void inorderBookings(Booking *root);

// helpers
float calculateDistance(int x1, int y1, int x2, int y2);

// main functions
void addDriver(Driver **root, int id, char name[], int type, int x, int y);
void addPassenger(Passenger **root, int id, char name[], char mobile[]);
Driver *findNearestVehicle(Driver *root, int p_x, int p_y, int prefType);
int requestRide(Driver *dRoot, Passenger *pRoot, Booking **bRoot, int p_id, int p_x, int p_y, int prefType);
void completeRide(Driver *dRoot, Passenger *pRoot, Booking *bRoot, int booking_id, float distance);
float calculateDriverEarnings(Driver *dRoot, int d_id);
void displayTopDrivers(Driver *dRoot, Booking *bRoot);
void displayFrequentPairs(Driver *dRoot, Passenger *pRoot, Booking *bRoot);
void displayAvailableVehicles(Driver *root);
void updateDriverLocation(Driver *root, int d_id, int new_x, int new_y);
void deleteDriver(Driver **root, int d_id);
void displayBookingHistory(Booking *root);
void rangeSearchPassengers(Passenger *root, int pid1, int pid2);

// File handling
void saveDrivers(Driver *root);
void loadDrivers(Driver **root);
void savePassengers(Passenger *root);
void loadPassengers(Passenger **root);
void saveBookings(Booking *root);
void loadBookings(Booking **root);

#endif