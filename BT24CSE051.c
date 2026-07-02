#include "BT24CSE051.h"

int BookingId = 0;

// AVL helpers

int getHeight(int h)
{
    return h;
}

int getBalance(int lh, int rh)
{
    return lh - rh;
}

/// Driver AVL

Driver *newDriverNode(int id, char name[], int type, int x, int y)
{
    Driver *newNode = (Driver *)malloc(sizeof(Driver));
    newNode->d_Id = id;
    strcpy(newNode->name, name);
    newNode->v_Type = (VehicleType)type;
    newNode->d_Status = Free;
    newNode->loc.x = x;
    newNode->loc.y = y;
    newNode->total_Earnings = 0.0;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Driver *rotateRightDriver(Driver *y)
{
    Driver *x = y->left;
    Driver *T = x->right;

    x->right = y;
    y->left = T;

    int lh = y->left ? y->left->height : 0;
    int rh = y->right ? y->right->height : 0;
    y->height = 1 + (lh > rh ? lh : rh);

    lh = x->left ? x->left->height : 0;
    rh = x->right ? x->right->height : 0;
    x->height = 1 + (lh > rh ? lh : rh);

    return x;
}

Driver *rotateLeftDriver(Driver *x)
{
    Driver *y = x->right;
    Driver *T = y->left;

    y->left = x;
    x->right = T;

    int lh = x->left ? x->left->height : 0;
    int rh = x->right ? x->right->height : 0;
    x->height = 1 + (lh > rh ? lh : rh);

    lh = y->left ? y->left->height : 0;
    rh = y->right ? y->right->height : 0;
    y->height = 1 + (lh > rh ? lh : rh);

    return y;
}

Driver *insertDriver(Driver *root, int id, char name[], int type, int x, int y)
{
    if (root == NULL)
        return newDriverNode(id, name, type, x, y);

    if (id < root->d_Id)
        root->left = insertDriver(root->left, id, name, type, x, y);
    else if (id > root->d_Id)
        root->right = insertDriver(root->right, id, name, type, x, y);
    else
        return root;

    int lh = root->left ? root->left->height : 0;
    int rh = root->right ? root->right->height : 0;
    root->height = 1 + (lh > rh ? lh : rh);

    int bal = getBalance(lh, rh);

    if (bal > 1 && id < root->left->d_Id)
        return rotateRightDriver(root);
    if (bal < -1 && id > root->right->d_Id)
        return rotateLeftDriver(root);
    if (bal > 1 && id > root->left->d_Id)
    {
        root->left = rotateLeftDriver(root->left);
        return rotateRightDriver(root);
    }
    if (bal < -1 && id < root->right->d_Id)
    {
        root->right = rotateRightDriver(root->right);
        return rotateLeftDriver(root);
    }

    return root;
}

Driver *minDriverNode(Driver *root)
{
    while (root->left)
        root = root->left;
    return root;
}

Driver *deleteDriverNode(Driver *root, int id)
{
    if (root == NULL)
        return NULL;

    if (id < root->d_Id)
        root->left = deleteDriverNode(root->left, id);
    else if (id > root->d_Id)
        root->right = deleteDriverNode(root->right, id);
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            Driver *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                free(root);
                return NULL;
            }
            *root = *temp;
            free(temp);
        }
        else
        {
            Driver *succ = minDriverNode(root->right);
            root->d_Id = succ->d_Id;
            strcpy(root->name, succ->name);
            root->v_Type = succ->v_Type;
            root->d_Status = succ->d_Status;
            root->loc = succ->loc;
            root->total_Earnings = succ->total_Earnings;
            root->right = deleteDriverNode(root->right, succ->d_Id);
        }
    }

    int lh = root->left ? root->left->height : 0;
    int rh = root->right ? root->right->height : 0;
    root->height = 1 + (lh > rh ? lh : rh);

    int bal = getBalance(lh, rh);

    if (bal > 1 && getBalance(root->left->left ? root->left->left->height : 0,
                              root->left->right ? root->left->right->height : 0) >= 0)
        return rotateRightDriver(root);
    if (bal > 1)
    {
        root->left = rotateLeftDriver(root->left);
        return rotateRightDriver(root);
    }
    if (bal < -1 && getBalance(root->right->left ? root->right->left->height : 0,
                               root->right->right ? root->right->right->height : 0) <= 0)
        return rotateLeftDriver(root);
    if (bal < -1)
    {
        root->right = rotateRightDriver(root->right);
        return rotateLeftDriver(root);
    }

    return root;
}

Driver *findDriverByID(Driver *root, int d_id)
{
    if (root == NULL)
        return NULL;
    if (root->d_Id == d_id)
        return root;
    if (d_id < root->d_Id)
        return findDriverByID(root->left, d_id);
    return findDriverByID(root->right, d_id);
}

void inorderDrivers(Driver *root)
{
    if (root == NULL)
        return;
    inorderDrivers(root->left);
    printf("Driver ID:%d Name:%s Type:%d Status:%d Location:%d %d Earnings:%.2f\n",
           root->d_Id, root->name, root->v_Type, root->d_Status,
           root->loc.x, root->loc.y, root->total_Earnings);
    inorderDrivers(root->right);
}

/// Passenger AVL

Passenger *newPassengerNode(int id, char name[], char mobile[])
{
    Passenger *newNode = (Passenger *)malloc(sizeof(Passenger));
    newNode->p_Id = id;
    strcpy(newNode->name, name);
    strcpy(newNode->number, mobile);
    newNode->frequency = 0;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Passenger *rotateRightPassenger(Passenger *y)
{
    Passenger *x = y->left;
    Passenger *T = x->right;

    x->right = y;
    y->left = T;

    int lh = y->left ? y->left->height : 0;
    int rh = y->right ? y->right->height : 0;
    y->height = 1 + (lh > rh ? lh : rh);

    lh = x->left ? x->left->height : 0;
    rh = x->right ? x->right->height : 0;
    x->height = 1 + (lh > rh ? lh : rh);

    return x;
}

Passenger *rotateLeftPassenger(Passenger *x)
{
    Passenger *y = x->right;
    Passenger *T = y->left;

    y->left = x;
    x->right = T;

    int lh = x->left ? x->left->height : 0;
    int rh = x->right ? x->right->height : 0;
    x->height = 1 + (lh > rh ? lh : rh);

    lh = y->left ? y->left->height : 0;
    rh = y->right ? y->right->height : 0;
    y->height = 1 + (lh > rh ? lh : rh);

    return y;
}

Passenger *insertPassenger(Passenger *root, int id, char name[], char mobile[])
{
    if (root == NULL)
        return newPassengerNode(id, name, mobile);

    if (id < root->p_Id)
        root->left = insertPassenger(root->left, id, name, mobile);
    else if (id > root->p_Id)
        root->right = insertPassenger(root->right, id, name, mobile);
    else
        return root;

    int lh = root->left ? root->left->height : 0;
    int rh = root->right ? root->right->height : 0;
    root->height = 1 + (lh > rh ? lh : rh);

    int bal = getBalance(lh, rh);

    if (bal > 1 && id < root->left->p_Id)
        return rotateRightPassenger(root);
    if (bal < -1 && id > root->right->p_Id)
        return rotateLeftPassenger(root);
    if (bal > 1 && id > root->left->p_Id)
    {
        root->left = rotateLeftPassenger(root->left);
        return rotateRightPassenger(root);
    }
    if (bal < -1 && id < root->right->p_Id)
    {
        root->right = rotateRightPassenger(root->right);
        return rotateLeftPassenger(root);
    }

    return root;
}

Passenger *findPassengerByID(Passenger *root, int p_id)
{
    if (root == NULL)
        return NULL;
    if (root->p_Id == p_id)
        return root;
    if (p_id < root->p_Id)
        return findPassengerByID(root->left, p_id);
    return findPassengerByID(root->right, p_id);
}

Passenger *findPassengerByMobile(Passenger *root, char mobile[])
{
    if (root == NULL)
        return NULL;
    if (strcmp(root->number, mobile) == 0)
        return root;
    Passenger *res = findPassengerByMobile(root->left, mobile);
    if (res)
        return res;
    return findPassengerByMobile(root->right, mobile);
}

void inorderPassengers(Passenger *root)
{
    if (root == NULL)
        return;
    inorderPassengers(root->left);
    printf("Passenger ID:%d Name:%s Mobile:%s Frequency:%d\n",
           root->p_Id, root->name, root->number, root->frequency);
    inorderPassengers(root->right);
}

/// Booking AVL

Booking *newBookingNode(int b_id, int d_id, int p_id, VehicleType vt)
{
    Booking *newNode = (Booking *)malloc(sizeof(Booking));
    newNode->b_Id = b_id;
    newNode->d_Id = d_id;
    newNode->p_Id = p_id;
    newNode->v_Type = vt;
    newNode->distance = 0;
    newNode->fare = 0;
    newNode->date = 0;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Booking *rotateRightBooking(Booking *y)
{
    Booking *x = y->left;
    Booking *T = x->right;

    x->right = y;
    y->left = T;

    int lh = y->left ? y->left->height : 0;
    int rh = y->right ? y->right->height : 0;
    y->height = 1 + (lh > rh ? lh : rh);

    lh = x->left ? x->left->height : 0;
    rh = x->right ? x->right->height : 0;
    x->height = 1 + (lh > rh ? lh : rh);

    return x;
}

Booking *rotateLeftBooking(Booking *x)
{
    Booking *y = x->right;
    Booking *T = y->left;

    y->left = x;
    x->right = T;

    int lh = x->left ? x->left->height : 0;
    int rh = x->right ? x->right->height : 0;
    x->height = 1 + (lh > rh ? lh : rh);

    lh = y->left ? y->left->height : 0;
    rh = y->right ? y->right->height : 0;
    y->height = 1 + (lh > rh ? lh : rh);

    return y;
}

Booking *insertBooking(Booking *root, int b_id, int d_id, int p_id, VehicleType vt)
{
    if (root == NULL)
        return newBookingNode(b_id, d_id, p_id, vt);

    if (b_id < root->b_Id)
        root->left = insertBooking(root->left, b_id, d_id, p_id, vt);
    else if (b_id > root->b_Id)
        root->right = insertBooking(root->right, b_id, d_id, p_id, vt);
    else
        return root;

    int lh = root->left ? root->left->height : 0;
    int rh = root->right ? root->right->height : 0;
    root->height = 1 + (lh > rh ? lh : rh);

    int bal = getBalance(lh, rh);

    if (bal > 1 && b_id < root->left->b_Id)
        return rotateRightBooking(root);
    if (bal < -1 && b_id > root->right->b_Id)
        return rotateLeftBooking(root);
    if (bal > 1 && b_id > root->left->b_Id)
    {
        root->left = rotateLeftBooking(root->left);
        return rotateRightBooking(root);
    }
    if (bal < -1 && b_id < root->right->b_Id)
    {
        root->right = rotateRightBooking(root->right);
        return rotateLeftBooking(root);
    }

    return root;
}

Booking *findBookingByID(Booking *root, int b_id)
{
    if (root == NULL)
        return NULL;
    if (root->b_Id == b_id)
        return root;
    if (b_id < root->b_Id)
        return findBookingByID(root->left, b_id);
    return findBookingByID(root->right, b_id);
}

void inorderBookings(Booking *root)
{
    if (root == NULL)
        return;
    inorderBookings(root->left);
    printf("BookingID:%d Driver:%d Passenger:%d Distance:%.2f Fare:%.2f\n",
           root->b_Id, root->d_Id, root->p_Id, root->distance, root->fare);
    inorderBookings(root->right);
}

/// helpers

float calculateDistance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

/// File handling

void writeDriverToFile(Driver *node, FILE *fp)
{
    if (!node)
        return;
    writeDriverToFile(node->left, fp);
    fprintf(fp, "%d,%s,%d,%d,%d,%d,%.2f\n",
            node->d_Id, node->name, node->v_Type, node->d_Status,
            node->loc.x, node->loc.y, node->total_Earnings);
    writeDriverToFile(node->right, fp);
}

void saveDrivers(Driver *root)
{
    FILE *fp = fopen("drivers.csv", "w");
    if (!fp)
        return;
    fprintf(fp, "id,name,type,status,x,y,earnings\n");
    writeDriverToFile(root, fp);
    fclose(fp);
}

void loadDrivers(Driver **root)
{
    FILE *fp = fopen("drivers.csv", "r");
    if (!fp)
        return;
    char line[200];
    fgets(line, 200, fp);
    while (fgets(line, 200, fp))
    {
        int id, type, status, x, y;
        float earn;
        char name[50];
        sscanf(line, "%d,%[^,],%d,%d,%d,%d,%f",
               &id, name, &type, &status, &x, &y, &earn);
        *root = insertDriver(*root, id, name, type, x, y);
        Driver *d = findDriverByID(*root, id);
        d->d_Status = (DriverStatus)status;
        d->total_Earnings = earn;
    }
    fclose(fp);
}

void writePassengerToFile(Passenger *node, FILE *fp)
{
    if (!node)
        return;
    writePassengerToFile(node->left, fp);
    fprintf(fp, "%d,%s,%s,%d\n",
            node->p_Id, node->name, node->number, node->frequency);
    writePassengerToFile(node->right, fp);
}

void savePassengers(Passenger *root)
{
    FILE *fp = fopen("passenger.csv", "w");
    if (!fp)
        return;
    fprintf(fp, "id,name,number,frequency\n");
    writePassengerToFile(root, fp);
    fclose(fp);
}

void loadPassengers(Passenger **root)
{
    FILE *fp = fopen("passenger.csv", "r");
    if (!fp)
        return;
    char line[200];
    fgets(line, 200, fp);
    while (fgets(line, 200, fp))
    {
        int id, freq;
        char name[50], number[15];
        sscanf(line, "%d,%[^,],%[^,],%d", &id, name, number, &freq);
        *root = insertPassenger(*root, id, name, number);
        Passenger *p = findPassengerByID(*root, id);
        p->frequency = freq;
    }
    fclose(fp);
}

void writeBookingToFile(Booking *node, FILE *fp)
{
    if (!node)
        return;
    writeBookingToFile(node->left, fp);
    fprintf(fp, "%d,%d,%d,%d,%.2f,%.2f\n",
            node->b_Id, node->d_Id, node->p_Id, node->v_Type,
            node->distance, node->fare);
    writeBookingToFile(node->right, fp);
}

void saveBookings(Booking *root)
{
    FILE *fp = fopen("bookings.csv", "w");
    if (!fp)
        return;
    fprintf(fp, "b_id,d_id,p_id,type,dist,fare\n");
    writeBookingToFile(root, fp);
    fclose(fp);
}

void loadBookings(Booking **root)
{
    FILE *fp = fopen("bookings.csv", "r");
    if (!fp)
        return;
    char line[200];
    fgets(line, 200, fp);
    while (fgets(line, 200, fp))
    {
        int bid, did, pid, type;
        float dist, fare;
        sscanf(line, "%d,%d,%d,%d,%f,%f",
               &bid, &did, &pid, &type, &dist, &fare);
        *root = insertBooking(*root, bid, did, pid, (VehicleType)type);
        Booking *b = findBookingByID(*root, bid);
        b->distance = dist;
        b->fare = fare;
        if (bid >= BookingId)
            BookingId = bid + 1;
    }
    fclose(fp);
}

/// main functions

void addDriver(Driver **root, int id, char name[], int type, int x, int y)
{
    if (findDriverByID(*root, id))
    {
        printf("Driver already exists\n");
        return;
    }
    *root = insertDriver(*root, id, name, type, x, y);
}

void addPassenger(Passenger **root, int id, char name[], char mobile[])
{
    if (findPassengerByID(*root, id))
        return;
    if (findPassengerByMobile(*root, mobile))
        return;
    *root = insertPassenger(*root, id, name, mobile);
}

void traverseNearest(Driver *node, int p_x, int p_y, int prefType, Driver **best, float *minDist)
{
    if (!node)
        return;
    traverseNearest(node->left, p_x, p_y, prefType, best, minDist);
    if (node->d_Status == Free &&
        (prefType == -1 || node->v_Type == (VehicleType)prefType))
    {
        float dist = calculateDistance(node->loc.x, node->loc.y, p_x, p_y);
        if (dist <= 5 && dist < *minDist)
        {
            *minDist = dist;
            *best = node;
        }
    }
    traverseNearest(node->right, p_x, p_y, prefType, best, minDist);
}

Driver *findNearestVehicle(Driver *root, int p_x, int p_y, int prefType)
{
    Driver *best = NULL;
    float minDist = 999999;
    traverseNearest(root, p_x, p_y, prefType, &best, &minDist);
    return best;
}

int requestRide(Driver *dRoot, Passenger *pRoot, Booking **bRoot, int p_id, int p_x, int p_y, int prefType)
{
    if (!findPassengerByID(pRoot, p_id))
    {
        printf("Passenger does not exist\n");
        return -1;
    }
    Driver *driver = findNearestVehicle(dRoot, p_x, p_y, prefType);
    if (driver == NULL)
    {
        printf("No driver available within 5km\n");
        return -1;
    }
    int bid = BookingId++;
    *bRoot = insertBooking(*bRoot, bid, driver->d_Id, p_id, driver->v_Type);
    driver->d_Status = booked;
    return bid;
}

void completeRide(Driver *dRoot, Passenger *pRoot, Booking *bRoot, int booking_id, float distance)
{
    Booking *booking = findBookingByID(bRoot, booking_id);
    if (!booking)
    {
        printf("Booking not found\n");
        return;
    }

    Driver *driver = findDriverByID(dRoot, booking->d_Id);
    if (!driver)
    {
        printf("Driver not found\n");
        return;
    }

    Passenger *pass = findPassengerByID(pRoot, booking->p_Id);
    if (!pass)
    {
        printf("Passenger not found\n");
        return;
    }

    booking->distance = distance;
    float fare;
    if (booking->v_Type == Cab)
        fare = distance * 10;
    else
        fare = distance * 5;

    driver->total_Earnings += fare;
    booking->fare = fare;
    pass->frequency = pass->frequency + 1;
    driver->d_Status = Free;
}

float calculateDriverEarnings(Driver *dRoot, int d_id)
{
    Driver *driver = findDriverByID(dRoot, d_id);
    if (!driver)
    {
        printf("Driver not found\n");
        return 0;
    }
    return driver->total_Earnings;
}

void collectDrivers(Driver *node, Driver *arr[], int *cnt)
{
    if (!node)
        return;
    collectDrivers(node->left, arr, cnt);
    arr[(*cnt)++] = node;
    collectDrivers(node->right, arr, cnt);
}

float sumDriverFares(Booking *node, int d_id)
{
    if (!node)
        return 0;
    float total = 0;
    if (node->d_Id == d_id)
        total += node->fare;
    total += sumDriverFares(node->left, d_id);
    total += sumDriverFares(node->right, d_id);
    return total;
}

void displayTopDrivers(Driver *dRoot, Booking *bRoot)
{
    if (!dRoot)
    {
        printf("No drivers registered\n");
        return;
    }

    Driver *arr[1000];
    int cnt = 0;
    collectDrivers(dRoot, arr, &cnt);

    float earnings[1000];
    for (int i = 0; i < cnt; i++)
        earnings[i] = sumDriverFares(bRoot, arr[i]->d_Id);

    for (int i = 0; i < cnt - 1; i++)
    {
        for (int j = 0; j < cnt - i - 1; j++)
        {
            if (earnings[j] < earnings[j + 1])
            {
                Driver *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                float tempE = earnings[j];
                earnings[j] = earnings[j + 1];
                earnings[j + 1] = tempE;
            }
        }
    }

    int count = 0;
    while (count < cnt && count < 3)
    {
        printf("Driver ID:%d Name:%s Earnings:%.2f\n",
               arr[count]->d_Id, arr[count]->name, earnings[count]);
        count++;
    }
}

void collectBookings(Booking *node, Booking *arr[], int *cnt)
{
    if (!node)
        return;
    collectBookings(node->left, arr, cnt);
    arr[(*cnt)++] = node;
    collectBookings(node->right, arr, cnt);
}

void displayFrequentPairs(Driver *dRoot, Passenger *pRoot, Booking *bRoot)
{
    Booking *arr[5000];
    int cnt = 0;
    collectBookings(bRoot, arr, &cnt);

    if (cnt == 0)
    {
        printf("No rides found.\n");
        return;
    }

    int maxCount = 0;
    int best_d = -1, best_p = -1;

    for (int i = 0; i < cnt; i++)
    {
        int count = 0;
        for (int j = 0; j < cnt; j++)
        {
            if (arr[i]->d_Id == arr[j]->d_Id && arr[i]->p_Id == arr[j]->p_Id)
                count++;
        }
        if (count > maxCount)
        {
            maxCount = count;
            best_d = arr[i]->d_Id;
            best_p = arr[i]->p_Id;
        }
    }

    Driver *d = findDriverByID(dRoot, best_d);
    Passenger *p = findPassengerByID(pRoot, best_p);

    if (d && p)
        printf("Most frequent pair: %s & %s (%d rides)\n", d->name, p->name, maxCount);
}

void printAvailableVehicles(Driver *node)
{
    if (!node)
        return;
    printAvailableVehicles(node->left);
    if (node->d_Status == Free)
    {
        printf("Id:-%d\n", node->d_Id);
        printf("Name:-%s\n", node->name);
        printf("Vehicle:-%d\n", node->v_Type);
        printf("Location:- %d %d\n", node->loc.x, node->loc.y);
    }
    printAvailableVehicles(node->right);
}

void displayAvailableVehicles(Driver *root)
{
    if (!root)
    {
        printf("No drivers registered\n");
        return;
    }
    printAvailableVehicles(root);
}

void updateDriverLocation(Driver *root, int d_id, int new_x, int new_y)
{
    Driver *driver = findDriverByID(root, d_id);
    if (!driver)
    {
        printf("Driver not found\n");
        return;
    }
    driver->loc.x = new_x;
    driver->loc.y = new_y;
    printf("Location Updated\n");
}

void deleteDriver(Driver **root, int d_id)
{
    Driver *driver = findDriverByID(*root, d_id);
    if (!driver)
    {
        printf("Driver not found\n");
        return;
    }
    if (driver->d_Status == booked)
    {
        printf("Driver is currently booked. Cannot delete.\n");
        return;
    }
    *root = deleteDriverNode(*root, d_id);
    printf("Driver deleted.\n");
}

void displayBookingHistory(Booking *root)
{
    if (!root)
    {
        printf("No bookings yet\n");
        return;
    }
    inorderBookings(root);
}

void rangeSearchPassengers(Passenger *root, int pid1, int pid2) {
    if (root == NULL) return;

    if (root->p_Id > pid2) {
        rangeSearchPassengers(root->left, pid1, pid2);
    } 
    else if (root->p_Id < pid1) {
        rangeSearchPassengers(root->right, pid1, pid2);
    } 
    else {
        rangeSearchPassengers(root->left, pid1, pid2);
        printf("Passenger ID: %d | Name: %s | Mobile: %s\n", root->p_Id, root->name, root->number);
        rangeSearchPassengers(root->right, pid1, pid2);
    }
}

int main()
{
    Driver *dRoot = NULL;
    Passenger *pRoot = NULL;
    Booking *bRoot = NULL;

    loadDrivers(&dRoot);
    loadPassengers(&pRoot);
    loadBookings(&bRoot);

    int choice;
    while (1)
    {
        printf("\n===== Ride Hailing System (AVL Trees) =====\n");
        printf("1. Add Driver          2. Add Passenger\n");
        printf("3. Request Ride        4. Complete Ride\n");
        printf("5. Top Drivers         6. Frequent Pairs\n");
        printf("7. Available Vehicles  8. Update Location\n");
        printf("9. Delete Driver       10. History\n");
        printf("11. Range Search       12. Show All\n");
        printf("0. Save & Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            saveDrivers(dRoot);
            savePassengers(pRoot);
            saveBookings(bRoot);
            printf("Saving data and exiting...\n");
            break;
        }

        switch (choice)
        {
        case 1:
        {
            int id, type, x, y;
            char name[50];
            printf("Enter :- Driver ID, Name, Type (0=Cab,1=Bike), x, y: ");
            scanf("%d %s %d %d %d", &id, name, &type, &x, &y);
            addDriver(&dRoot, id, name, type, x, y);
            break;
        }
        case 2:
        {
            int id;
            char name[50], mobile[15];
            printf("Enter Passenger ID, Name, Mobile: ");
            scanf("%d %s %s", &id, name, mobile);
            addPassenger(&pRoot, id, name, mobile);
            break;
        }
        case 3:
        {
            int p_id, x, y, prefType;
            printf("Enter Passenger ID, Location(x y), PrefType (0=Cab,1=Bike,-1=Any): ");
            scanf("%d %d %d %d", &p_id, &x, &y, &prefType);
            int booking_id = requestRide(dRoot, pRoot, &bRoot, p_id, x, y, prefType);
            if (booking_id == -1)
                printf("Ride request failed.\n");
            else
                printf("Ride booked! Booking ID: %d\n", booking_id);
            break;
        }
        case 4:
        {
            int booking_id;
            float distance;
            printf("Enter Booking ID and Distance travelled: ");
            scanf("%d %f", &booking_id, &distance);
            completeRide(dRoot, pRoot, bRoot, booking_id, distance);
            printf("Ride completed.\n");
            break;
        }
        case 5:
            displayTopDrivers(dRoot, bRoot);
            break;
        case 6:
            displayFrequentPairs(dRoot, pRoot, bRoot);
            break;
        case 7:
            displayAvailableVehicles(dRoot);
            break;
        case 8:
        {
            int id, x, y;
            printf("Enter Driver ID and new location (x y): ");
            scanf("%d %d %d", &id, &x, &y);
            updateDriverLocation(dRoot, id, x, y);
            break;
        }
        case 9:
        {
            int id;
            printf("Enter Driver ID to delete: ");
            scanf("%d", &id);
            deleteDriver(&dRoot, id);
            break;
        }
        case 10:
            displayBookingHistory(bRoot);
            break;
        case 11:
        {
            int p1, p2;
            printf("Enter P_ID1 and P_ID2: ");
            scanf("%d %d", &p1, &p2);
            rangeSearchPassengers(pRoot, p1, p2);
            break;
        }
        case 12:
            printf("-- Drivers --\n");
            inorderDrivers(dRoot);
            printf("-- Passengers --\n");
            inorderPassengers(pRoot);
            printf("-- Bookings --\n");
            inorderBookings(bRoot);
            break;
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}