
#include "simlib.h" /* Required for use of simlib.c. */
#include "lib.h"

double busArrival = 0.0;
double busDepartureFromCarRental = 0.0;

int listBusCapacity() {
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
    busArrival = sim_time;
    if (list_size[LIST_BUS_TO_TERMINAL_1] > 0) {
        event_schedule(sim_time + uniform(16,24, STREAM_UNLOADING), EVENT_UNLOAD_PERSON_TERMINAL_1);
    } else if (list_size[LIST_TERMINAL_1] > 0 && listBusCapacity() < MAX_BUS_SIZE) { 
        event_schedule(sim_time + uniform(15,25,STREAM_LOADING), EVENT_LOAD_PERSON_TERMINAL_1);
    } else {
        event_schedule(sim_time + 5.0 * 60.0, EVENT_DEPARTURE_BUS_TERMINAL_1);
    }
}

void departureBusTerminal1() {
    if ((sim_time - busArrival) < (5.0 * 60.0)) {
        event_schedule(busArrival + 5.0 * 60.0, EVENT_DEPARTURE_BUS_TERMINAL_1);
    } else {
        sampst ((sim_time - busArrival), VARIABLE_BUS_STOP_TERMINAL_1);
        event_schedule(sim_time + 1.0/(30.0 * 60.0 * 60.0), EVENT_ARRIVAL_BUS_TERMINAL_2);
    }
}

void unloadPersonTerminal1() {
    list_remove(FIRST, LIST_BUS_TO_TERMINAL_1);
    timest(listBusCapacity(), VARIABLE_NUM_BUS);
    sampst(sim_time - transfer[DATA_ARRIVAL_TIME], VARIABLE_PERSON_SYSTEM);

    if (list_size[LIST_BUS_TO_TERMINAL_1] > 0) {
        event_schedule(sim_time + uniform(16, 24, STREAM_UNLOADING), EVENT_UNLOAD_PERSON_TERMINAL_1);
    }else if (list_size[LIST_TERMINAL_1] > 0 && listBusCapacity() < MAX_BUS_SIZE) {
        event_schedule(sim_time + uniform(15, 25, STREAM_LOADING ), EVENT_LOAD_PERSON_TERMINAL_1);
    }else {
        event_schedule(sim_time, EVENT_DEPARTURE_BUS_TERMINAL_1);
    }
}

void loadPersonTerminal1() {
    list_remove(FIRST, LIST_TERMINAL_1);
    timest(list_size[LIST_TERMINAL_1], VARIABLE_NUM_TERMINAL_1);
    sampst((sim_time - transfer[DATA_ARRIVAL_TIME]), VARIABLE_DELAY_TERMINAL_1);
    list_file(LAST, LIST_BUS_TO_CAR_RENTAL);
    timest(list_bus_size(), VARIABLE_NUM_BUS);
    if (list_size[LIST_TERMINAL_1] > 0 && list_bus_size() < MAX_BUS_SIZE) {
        event_schedule(sim_time + uniform(15, 25, STREAM_LOADING), EVENT_LOAD_PERSON_TERMINAL_1);
    }else {
        event_schedule(sim_time, EVENT_DEPARTURE_BUS_TERMINAL_1);
    }
}

/**
 * Terminal 2
*/
void arrivalPersonTerminal2() {
    transfer[DATA_ARRIVAL_TIME] = sim_time;
    transfer[DATA_DESTINATION] = DESTINATION_CAR_RENTAL;
    list_file(LAST, LIST_TERMINAL_2);
    timest(list_size[LIST_TERMINAL_2], VARIABLE_NUM_TERMINAL_2);

    //set event
    event_schedule(sim_time + expon(60.0 * 60.0 / 10.0, STREAM_INTERARRIVAL_TERMINAL_2), EVENT_ARRIVAL_PERSON_TERMINAL_2);

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