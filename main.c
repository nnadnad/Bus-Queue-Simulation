
#include "simlib.h" /* Required for use of simlib.c. */
#include "lib.h"

double busArrival = 0.0;
double busDepartureFromCarRental = 0.0;
// FILE *outfile;

int listBusCapacity() {
    return list_size[LIST_BUS_TO_TERMINAL_1] + list_size[LIST_BUS_TO_TERMINAL_2] + list_size[LIST_BUS_TO_CAR_RENTAL];
}

double max(double a, double b) { return a > b ? a : b; }


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
    timest(listBusCapacity(), VARIABLE_NUM_BUS);
    if (list_size[LIST_TERMINAL_1] > 0 && listBusCapacity() < MAX_BUS_SIZE) {
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
    double temp = sim_time - busArrival;
    if ((temp - (5.0 * 60.0)) < 1e-9) {
        sampst ((sim_time - busArrival), VARIABLE_BUS_STOP_TERMINAL_2);
        event_schedule(sim_time + 4.5/30.0 * 60.0 * 60.0, EVENT_ARRIVAL_BUS_CAR_RENTAL);
    } 
    else if (temp < (5.0 * 60.0)){
        event_schedule(busArrival + 5.0 * 60.0, EVENT_DEPARTURE_BUS_TERMINAL_2); // kalau gaada yang naik atau turun
        // printf("%f\n", sim_time - busArrival);
    }
    else{
        sampst ((sim_time - busArrival), VARIABLE_BUS_STOP_TERMINAL_2);
        event_schedule(sim_time + 4.5/30.0 * 60.0 * 60.0, EVENT_ARRIVAL_BUS_CAR_RENTAL);
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
    timest(listBusCapacity(), VARIABLE_NUM_BUS);

    if (list_size[LIST_TERMINAL_2] > 0 && listBusCapacity() < MAX_BUS_SIZE) {
        event_schedule(sim_time + uniform(15, 25, STREAM_LOADING), EVENT_LOAD_PERSON_TERMINAL_2);
    }else {
        event_schedule(sim_time, EVENT_DEPARTURE_BUS_TERMINAL_2);
    }
}


/**
 * Car rental
*/
void arrivalPersonCarRental() {
    transfer[DATA_ARRIVAL_TIME] = sim_time;

    double prob_distrib[3] = {0, 0.583, 1};
    if (random_integer(prob_distrib, STREAM_DESTINATION) == 1)
        transfer[DATA_DESTINATION] = DESTINATION_TERMINAL_1;
    else
        transfer[DATA_DESTINATION] = DESTINATION_TERMINAL_2;

    list_file(LAST, LIST_CAR_RENTAL);
    timest(list_size[LIST_CAR_RENTAL], VARIABLE_NUM_CAR_RENTAL);

    event_schedule(sim_time + expon(60.0 * 60.0 / 24.0, STREAM_INTERARRIVAL_CAR_RENTAL), EVENT_ARRIVAL_PERSON_CAR_RENTAL);
}

void arrvialBusCarRental() {
    busArrival = sim_time;
    if (list_size[LIST_BUS_TO_CAR_RENTAL] > 0) {
        event_schedule(sim_time + uniform(16, 24, STREAM_UNLOADING), EVENT_UNLOAD_PERSON_CAR_RENTAL);
    }else if (list_size[LIST_CAR_RENTAL] > 0 && listBusCapacity() < MAX_BUS_SIZE) {
        event_schedule(sim_time + uniform(15, 25, STREAM_LOADING), EVENT_LOAD_PERSON_CAR_RENTAL);
    }else {
        event_schedule(sim_time + 5.0 * 60.0, EVENT_DEPARTURE_BUS_CAR_RENTAL);
    }
}

void departureBusCarRental() {
  if ((sim_time - busArrival) < (5.0 * 60.0)){
    event_schedule(busArrival + 5.0 * 60.0, EVENT_DEPARTURE_BUS_CAR_RENTAL);
  }else {
    sampst((sim_time - busDepartureFromCarRental), VARIABLE_BUS_LOOP);
    busDepartureFromCarRental = sim_time;
    sampst((sim_time - busArrival), VARIABLE_BUS_STOP_CAR_RENTAL);
    event_schedule(sim_time + 4.5 / 30.0 * 60.0 * 60.0, EVENT_ARRIVAL_BUS_TERMINAL_1);
  }
}

void unloadPersonCarRental() {
    list_remove(FIRST, LIST_BUS_TO_CAR_RENTAL);
    timest(listBusCapacity(), VARIABLE_NUM_BUS);
    sampst(sim_time - transfer[DATA_ARRIVAL_TIME], VARIABLE_PERSON_SYSTEM);

    if (list_size[LIST_BUS_TO_CAR_RENTAL] > 0) {
        event_schedule(sim_time + uniform(16, 24, STREAM_UNLOADING), EVENT_UNLOAD_PERSON_CAR_RENTAL);
    }else if (list_size[LIST_CAR_RENTAL] > 0 && listBusCapacity() < MAX_BUS_SIZE) {
        event_schedule(sim_time + uniform(15, 25, STREAM_LOADING ), EVENT_LOAD_PERSON_CAR_RENTAL);
    }else {
        event_schedule(sim_time, EVENT_DEPARTURE_BUS_CAR_RENTAL);
    }
}

void loadPersonCarRental() {
    list_remove(FIRST, LIST_CAR_RENTAL);
    timest(list_size[LIST_CAR_RENTAL], VARIABLE_NUM_CAR_RENTAL);
    sampst((sim_time - transfer[DATA_ARRIVAL_TIME]), VARIABLE_DELAY_CAR_RENTAL);
    if(transfer[DATA_DESTINATION] == DESTINATION_TERMINAL_1){
        list_file(LAST, LIST_BUS_TO_TERMINAL_1);
    } else {
        list_file(LAST, LIST_BUS_TO_TERMINAL_2);
    }
    timest(listBusCapacity(), VARIABLE_NUM_BUS);
    if (list_size[LIST_CAR_RENTAL] > 0 && listBusCapacity() < MAX_BUS_SIZE) {
        event_schedule(sim_time + uniform(15, 25, STREAM_LOADING), EVENT_LOAD_PERSON_CAR_RENTAL);
    }else {
        event_schedule(sim_time, EVENT_DEPARTURE_BUS_CAR_RENTAL);
    }
}

/**
 * Init model simulation
*/
// void initModel() {
//     event_schedule(sim_time + expon(60.0 * 60.0 / 14.0, STREAM_INTERARRIVAL_TERMINAL_1), EVENT_ARRIVAL_PERSON_TERMINAL_1);
// 	event_schedule(sim_time + expon(60.0 * 60.0 / 10.0, STREAM_INTERARRIVAL_TERMINAL_2), EVENT_ARRIVAL_PERSON_TERMINAL_2);
// 	event_schedule(sim_time + expon(60.0 * 60.0 / 24.0, STREAM_INTERARRIVAL_CAR_RENTAL), EVENT_ARRIVAL_PERSON_CAR_RENTAL);
//     event_schedule(sim_time + 4.5 / 30.0 * 60.0 * 60.0, EVENT_ARRIVAL_BUS_TERMINAL_1); 
//     event_schedule(sim_time + 80.0 * 60.0 * 60.0, EVENT_END_SIMULATION);

//     sampst(0.0, 0);
//     timest(0.0, 0);
// }

// /**
//  * Print answer for TUBES 1
// */
// void print() {
//     /**
//      * Print answer fot TUBES 1
//     */
    

// }

int main() {

    printf("start: %.2f\n", sim_time);

    init_simlib(); // harus init simlib
    // initModel();
    // printf("\nCase mulai\n");
    event_schedule(sim_time + expon(60.0 * 60.0 / 14.0, STREAM_INTERARRIVAL_TERMINAL_1), EVENT_ARRIVAL_PERSON_TERMINAL_1);
	event_schedule(sim_time + expon(60.0 * 60.0 / 10.0, STREAM_INTERARRIVAL_TERMINAL_2), EVENT_ARRIVAL_PERSON_TERMINAL_2);
	event_schedule(sim_time + expon(60.0 * 60.0 / 24.0, STREAM_INTERARRIVAL_CAR_RENTAL), EVENT_ARRIVAL_PERSON_CAR_RENTAL);
    event_schedule(sim_time + 4.5 / 30.0 * 60.0 * 60.0, EVENT_ARRIVAL_BUS_TERMINAL_1); 
    event_schedule(sim_time + 80.0 * 60.0 * 60.0, EVENT_END_SIMULATION);

    sampst(0.0, 0);
    timest(0.0, 0);

    // printf("test");
    while ( next_event_type != EVENT_END_SIMULATION) {
        timing();
        // printf("loop");
        switch(next_event_type) {
        case EVENT_ARRIVAL_PERSON_TERMINAL_1:
            arrivalPersonTerminal1();
            // printf("\ncase 1");
            break;
        case EVENT_ARRIVAL_PERSON_TERMINAL_2:
            arrivalPersonTerminal2();
            // printf("\ncase 2");
            break;
        case EVENT_ARRIVAL_PERSON_CAR_RENTAL:
            arrivalPersonCarRental();
            // printf("\ncase 3");
            break;
        case EVENT_ARRIVAL_BUS_TERMINAL_1:
            arrvialBusTerminal1();
            // printf("\ncase 4");
            break;
        case EVENT_ARRIVAL_BUS_TERMINAL_2:
            arrvialBusTerminal2();
            // printf("\ncase 5");
            break;
        case EVENT_ARRIVAL_BUS_CAR_RENTAL:
            arrvialBusCarRental();
            // printf("\ncase 6");
            break;
        case EVENT_DEPARTURE_BUS_TERMINAL_1:
            departureBusTerminal1();
            // printf("\ncase 7");
            break;
        case EVENT_DEPARTURE_BUS_TERMINAL_2:
            departureBusTerminal2();
            // printf("\nsim time: %.2f",sim_time);
            break;
        case EVENT_DEPARTURE_BUS_CAR_RENTAL:
            departureBusCarRental();
            // printf("\ncase 9");
            break;
        case EVENT_UNLOAD_PERSON_TERMINAL_1:
            unloadPersonTerminal1();
            // printf("\ncase 10");
            break;
        case EVENT_UNLOAD_PERSON_TERMINAL_2:
            unloadPersonTerminal2();
            // printf("\ncase 11");
            break;
        case EVENT_UNLOAD_PERSON_CAR_RENTAL:
            unloadPersonCarRental();
            // printf("\ncase 12");
            break;
        case EVENT_LOAD_PERSON_TERMINAL_1:
            loadPersonTerminal1();
            // printf("\ncase 13");
            break;
        case EVENT_LOAD_PERSON_TERMINAL_2:
            loadPersonTerminal2();
            // printf("\ncase 14");
            break;
        case EVENT_LOAD_PERSON_CAR_RENTAL:
            loadPersonCarRental();
            // printf("\ncase 15");
            break;
        }
    }
    // printf("\nCase Selesai\n");

    // printf("\n\ntest 2");
    out_sampst(stdout, 1, 12);
    out_timest(stdout, 1, 12);

    printf("finish: %.2f\n\n", sim_time);
    

    // outfile = fopen("carRental.out", "w");
    printf("------------------------------------ Statistics  ------------------------------------\n");
    // timest(0,-VARIABLE_NUM_TERMINAL_1);
    printf("(A) Average and maximum number in each queue\n");
    printf("    1. Terminal 1:\n");
    printf("       - Avreage: %.2lf\n", transfer[1]);
    printf("       - Maximun: %.2lf\n", transfer[2]);
    
    // timest(0, -VARIABLE_NUM_TERMINAL_2);
    printf("    2. Terminal 2:\n");
    printf("       - Avreage: %.2lf\n", transfer[1]);
    printf("       - Maximun: %.2lf\n", transfer[2]);
    
    // timest(0, -VARIABLE_NUM_CAR_RENTAL);
    printf("    2. Car Rental:\n");
    printf("       - Avreage: %.2lf\n", transfer[1]);
    printf("       - Maximun: %.2lf\n\n", transfer[2]);

    // sampst(0, -VARIABLE_DELAY_TERMINAL_1);
    printf("(B) Average and maximum delay in each queue\n");
    printf("    1. Terminal 1:\n");
    printf("       - Avreage: %.2lf\n", transfer[1]);
    printf("       - Maximun: %.2lf\n", transfer[3]);
    
    // sampst(0, -VARIABLE_DELAY_TERMINAL_2);
    printf("    2. Terminal 2:\n");
    printf("       - Avreage: %.2lf\n", transfer[1]);
    printf("       - Maximun: %.2lf\n", transfer[3]);
    
    // sampst(0, -VARIABLE_DELAY_CAR_RENTAL);
    printf("    2. Car Rental:\n");
    printf("       - Avreage: %.2lf\n", transfer[1]);
    printf("       - Maximun: %.2lf\n\n", transfer[3]);

    // timest(0, -VARIABLE_NUM_BUS);
    printf("(C) Average and maximum number on the bus\n");
    printf("       - Avreage: %.2lf\n", transfer[1]);
    printf("       - Maximun: %.2lf\n\n", transfer[2]);
    
    // sampst(0, -VARIABLE_BUS_STOP_TERMINAL_1);
    printf("(D) Average, maximum, and minimum time bus stopped at each location\n");
    printf("    1. Terminal 1:\n");
    printf("       - Avreage: %.2lf\n", transfer[1]);
    printf("       - Maximun: %.2lf\n", transfer[3]);
    printf("       - Minimum: %.2lf\n", transfer[4]);

    
    // sampst(0, -VARIABLE_BUS_STOP_TERMINAL_2);
    printf("    2. Terminal 2:\n");
    printf("       - Avreage: %.2lf\n", transfer[1]);
    printf("       - Maximun: %.2lf\n", transfer[3]);
    printf("       - Minimum: %.2lf\n", transfer[4]);
    
    // sampst(0, -VARIABLE_BUS_STOP_CAR_RENTAL);
    printf("    3. Car Rental:\n");
    printf("       - Avreage: %.2lf\n", transfer[1]);
    printf("       - Maximun: %.2lf\n", transfer[3]);
    printf("       - Minimum: %.2lf\n\n", transfer[4]);

    // sampst(0, -VARIABLE_BUS_LOOP);
    printf("(E) Average, maximum, and minimum time bus making a loop\n");
    printf("       - Avreage: %.2lf\n", transfer[1]);
    printf("       - Maximun: %.2lf\n", transfer[3]);
    printf("       - Minimum: %.2lf\n\n", transfer[4]);

    // sampst(0, -VARIABLE_PERSON_SYSTEM);
    printf("(F) Average, maximum, and minimum time person in the system\n");
    printf("       - Avreage: %.2lf\n", transfer[1]);
    printf("       - Maximun: %.2lf\n", transfer[3]);
    printf("       - Minimum: %.2lf\n", transfer[4]);

    // fclose(outfile);

    return 0;    
}