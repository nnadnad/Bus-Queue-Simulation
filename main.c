
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
    transfer[DATA_ARRIVAL_TIME] = sim_time; //waktu orang arrival di terminal 1
    transfer[DATA_DESTINATION] = DESTINATION_CAR_RENTAL; // event type nya, orang di T! -> car rental
    list_file(LAST, LIST_TERMINAL_1); //bikin list person di T1, Last itu bisa masuk nya di akhir list (FIFO)

    timest(list_size[LIST_TERMINAL_1], VARIABLE_NUM_TERMINAL_1); 

    //set event dengan waktu yang sesuai di soal
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
    busArrival = sim_time;
    if (list_size[LIST_BUS_TO_TERMINAL_2] > 0) {
        event_schedule(sim_time + uniform(16,24, STREAM_UNLOADING), EVENT_UNLOAD_PERSON_TERMINAL_2); //unload kalo ada min 1 org yang mau dari car -> T2
    } else if (list_size[LIST_TERMINAL_2] > 0 && listBusCapacity() < MAX_BUS_SIZE) { 
        event_schedule(sim_time + uniform(15,25,STREAM_LOADING), EVENT_LOAD_PERSON_TERMINAL_2); // kondisi load orang di T2, kalau bus masih kosong, dan ada org di antrian T2
    } else {
        event_schedule(sim_time + 5.0 * 60.0, EVENT_DEPARTURE_BUS_TERMINAL_2); //waktu untuk delay buat load / unload 5 menit
    }
}

void departureBusTerminal2() {
    if ((sim_time - busArrival) < (5.0 * 60.0)) {
        event_schedule(busArrival + 5.0 * 60.0, EVENT_DEPARTURE_BUS_TERMINAL_2); // kalau gaada yang naik atau turun
    } else {
        sampst ((sim_time - busArrival), VARIABLE_BUS_STOP_TERMINAL_2);
        event_schedule(sim_time + 1.0/(30.0 * 60.0 * 60.0), EVENT_ARRIVAL_BUS_TERMINAL_2);
    }
}

void unloadPersonTerminal2() {
    list_remove(FIRST, LIST_BUS_TO_TERMINAL_2); 
    timest(listBusCapacity(), VARIABLE_NUM_BUS);
    sampst(sim_time - transfer[DATA_ARRIVAL_TIME], VARIABLE_PERSON_SYSTEM);

    if (list_size[LIST_BUS_TO_TERMINAL_2] > 0) {
        event_schedule(sim_time + uniform(16, 24, STREAM_UNLOADING), EVENT_UNLOAD_PERSON_TERMINAL_2); // remove org pertama yang ada di list car rental -> T2 yang ada di dalam bis
    }else if (list_size[LIST_TERMINAL_2] > 0 && listBusCapacity() < MAX_BUS_SIZE) {
        event_schedule(sim_time + uniform(15, 25, STREAM_LOADING ), EVENT_LOAD_PERSON_TERMINAL_2); // load org ke bus
    }else {
        event_schedule(sim_time, EVENT_DEPARTURE_BUS_TERMINAL_2);
    }
}

void loadPersonTerminal2() {
    list_remove(FIRST, LIST_TERMINAL_2);
    timest(list_size[LIST_TERMINAL_2], VARIABLE_NUM_TERMINAL_2);
    sampst((sim_time - transfer[DATA_ARRIVAL_TIME]), VARIABLE_DELAY_TERMINAL_2);
    
    list_file(LAST, LIST_BUS_TO_CAR_RENTAL);
    timest(list_bus_size(), VARIABLE_NUM_BUS);

    if (list_size[LIST_TERMINAL_2] > 0 && list_bus_size() < MAX_BUS_SIZE) {
        event_schedule(sim_time + uniform(15, 25, STREAM_LOADING), EVENT_LOAD_PERSON_TERMINAL_2);
    }else {
        event_schedule(sim_time, EVENT_DEPARTURE_BUS_TERMINAL_2);
    }
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