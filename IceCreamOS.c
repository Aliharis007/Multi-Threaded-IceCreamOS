#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#define PRICE_TOPPING_1 1.8
#define PRICE_TOPPING_2 1.6
#define PRICE_FLAVOR_1 5.02
#define PRICE_FLAVOR_2 2.00
#define PRICE_FLAVOR_3 3.1

sem_t ticketSemaphore, flavorSemaphore, flavor1Semaphore, flavor2Semaphore, flavor3Semaphore, toppingSemaphore, topping1Semaphore, topping2Semaphore, paymentSemaphore;
pthread_t customerThreads[100];

int availableTickets = 50;
int flavorsAvailable[3] = {27, 36, 20};
int toppingsAvailable[2] = {17, 32};
double totalRevenue = 0.0;
int storeOpen = 1;

void signalHandler(int sig) {
    if (sig == SIGUSR1) {
        storeOpen = 0;
        printf("\nStore closure signal received. No more customers will be served.\n");
    }
}

void* customerThread(void* customerId);
double purchaseFlavors(int customerId);
double purchaseToppings(int customerId);
int ticketInitializer();
void processPayment(int customerId, double billAmount);

int main() {
    int numCustomers;
    numCustomers = ticketInitializer();
    int customerIds[numCustomers];

    sem_init(&ticketSemaphore, 0, 1);
    sem_init(&flavorSemaphore, 0, 3);
    sem_init(&flavor1Semaphore, 0, 1);
    sem_init(&flavor2Semaphore, 0, 1);
    sem_init(&flavor3Semaphore, 0, 1);
    sem_init(&toppingSemaphore, 0, 2);
    sem_init(&topping1Semaphore, 0, 1);
    sem_init(&topping2Semaphore, 0, 1);
    sem_init(&paymentSemaphore, 0, 1);

    signal(SIGUSR1, signalHandler);

    for (int i = 0; i < numCustomers; i++) {
        customerIds[i] = i + 100;
        pthread_create(&customerThreads[i], NULL, &customerThread, (void*)&customerIds[i]);
    }

    sleep(10);
    kill(getpid(), SIGUSR1);

    for (int i = 0; i < numCustomers; i++) {
        pthread_join(customerThreads[i], NULL);
    }

    printf("\n\t\t[ Total Income Retrieved ]\n\n");
    printf("Number of Customers Served: %d\n", numCustomers);
    printf("Total Revenue Generated: $ %.2f\n", totalRevenue);
    printf("Total Tickets Remaining: %d\n\n", availableTickets);

    sem_destroy(&ticketSemaphore);
    sem_destroy(&flavorSemaphore);
    sem_destroy(&flavor1Semaphore);
    sem_destroy(&flavor2Semaphore);
    sem_destroy(&flavor3Semaphore);
    sem_destroy(&toppingSemaphore);
    sem_destroy(&topping1Semaphore);
    sem_destroy(&topping2Semaphore);
    sem_destroy(&paymentSemaphore);

    return 0;
}

void* customerThread(void* customerId) {
    int id = *(int*)customerId;
    double bill = 0.0;

    if (!storeOpen) {
        printf("Customer[%d]: Store is closed. Leaving without service.\n", id);
        pthread_exit(NULL);
    }

    sem_wait(&ticketSemaphore);
    if (availableTickets <= 0) {
        printf("Customer[%d]: Leaving Shop. [REASON]: Tickets Finished\n", id);
        sleep(1);
        pthread_exit(NULL);
    }
    availableTickets--;
    printf("Customer[%d] Got Ticket.\n", id);
    sem_post(&ticketSemaphore);

    sleep(2);
    double originalBill;
    originalBill = purchaseFlavors(id) + purchaseToppings(id);
    processPayment(id, originalBill);

    printf("Customer[%d]: Leaving Ice-Cream Shop.\n\n", id);

    return NULL;
}

int ticketInitializer() {
    int numCustomers;
    printf("\nEnter number of customers to serve [1-%d]: ", availableTickets);
    scanf("%d", &numCustomers);
    printf("\n");

    if (numCustomers > availableTickets || numCustomers <= 0) {
        printf("Invalid input!\n\n");
        return 0;
    }
    return numCustomers;
}

double purchaseFlavors(int customerId) {
    int id = customerId;
    double bill = 0.0;
    int selectedFlavors = 0;

    sem_wait(&flavorSemaphore);
    if (flavorsAvailable[0] <= 0 && flavorsAvailable[1] <= 0 && flavorsAvailable[2] <= 0) {
        printf("Customer[%d]: Leaving Shop. [REASON]: Flavors Finished\n", id);
        sleep(1);
        pthread_exit(NULL);
    } else {
        sem_wait(&flavor1Semaphore);
        if (flavorsAvailable[0] > 0) {
            flavorsAvailable[0]--;
            selectedFlavors++;
            bill += PRICE_FLAVOR_1;
            printf("Customer[%d]: served with Flavour[0].\n", id);
            sleep(1);
        }
        sem_post(&flavor1Semaphore);

        sem_wait(&flavor2Semaphore);
        if (flavorsAvailable[1] > 0) {
            flavorsAvailable[1]--;
            selectedFlavors++;
            bill += PRICE_FLAVOR_2;
            printf("Customer[%d]: served with Flavour[1].\n", id);
            sleep(1);
        }
        sem_post(&flavor2Semaphore);

        sem_wait(&flavor3Semaphore);
        if (flavorsAvailable[2] > 0) {
            flavorsAvailable[2]--;
            selectedFlavors++;
            bill += PRICE_FLAVOR_3;
            printf("Customer[%d]: served with Flavour[2].\n", id);
            sleep(1);
        }
        sem_post(&flavor3Semaphore);

        if (selectedFlavors == 0) {
            printf("Customer[%d]: Leaving Shop. [REASON]: Flavours Finished\n", id);
            sleep(1);
            pthread_exit(NULL);
        }
    }

    printf("Customer[%d]: Got All Flavour(s)... Now Leaving Flavor Counter\n", id);
    sem_post(&flavorSemaphore);
    sleep(2);
    printf("\n");
    return bill;
}

double purchaseToppings(int customerId) {
    int id = customerId;
    double bill = 0.0;

    sem_wait(&toppingSemaphore);
    sem_wait(&topping1Semaphore);
    if (toppingsAvailable[0] > 0) {
        printf("Customer[%d]: served with Topping[0].\n", id);
        toppingsAvailable[0]--;
        bill += PRICE_TOPPING_1;
    }
    sem_post(&topping1Semaphore);

    sem_wait(&topping2Semaphore);
    if (toppingsAvailable[1] > 0) {
        printf("Customer[%d]: served with Topping[1].\n", id);
        toppingsAvailable[1]--;
        bill += PRICE_TOPPING_2;
    }
    sem_post(&topping2Semaphore);

    printf("Customer[%d]: Got All Toppings.. Now Leaving Topping Counter...\n", id);
    sem_post(&toppingSemaphore);
    sleep(2);
    printf("\n");
    return bill;
}

void processPayment(int customerId, double billAmount) {
    int id = customerId;
    sem_wait(&paymentSemaphore);
    totalRevenue += billAmount;
    printf("Customer[%d]: Total Billed: $ %.2f.\n", id, billAmount);
    sem_post(&paymentSemaphore);
    sleep(2);
}

