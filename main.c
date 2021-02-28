
#include "simlib.h" /* Required for use of simlib.c. */
#include "lib.h"

int numberBusCapacity() {
    return list_size[LIST_BUS_TO_TERMINAL_1] + list_size[LIST_BUS_TO_TERMINAL_2] + list_size[LIST_BUS_TO_CAR_RENTAL];
}


/**
 * Termiinal 1
*/
void arrivalPersonTerminal1() {
    transfer[DATA_ARRIVAL_TIME] = sim_time;
    transfer[DATA_DESTINATION] = DESTINATION_CAR_RENTAL;
    list_file(LAST, LIST_TERMINAL_1);
    timest(list_size[LIST_TERMINAL_1], VARIABLE_NUM_TERMINAL_1);

    //set event
    event_schedule(sim_time + expon(60.0 * 60.0 / 14.0, STREAM_INTERARRIVAL_TERMINAL_1), EVENT_ARRIVAL_PERSON_TERMINAL_1);
}

void arrvialBusTerminal1() {

}

void departureBusTerminal1() {

}

void unloadPersonTerminal1() {

}

void loadPersonTerminal1() {

}

/**
 * Terminal 2
*/
void arrivalPersonTerminal2() {

}

void arrvialBusTerminal2() {

}

void departureBusTerminal2() {

}

void unloadPersonTerminal2() {

}

void loadPersonTerminal2() {

}


/**
 * Car rental
*/
void arrivalPersonCarRental() {

}

void arrvialBusCarRental() {

}

void departureBusCarRental() {

}

void unloadPersonCarRental() {

}

void loadPersonCarRental() {

}

/**
 * Init model simulation
*/
void initModel() {

}

/**
 * Print answer for TUBES 1
*/
void print() {

}

int main() {
    
}