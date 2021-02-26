
#include "simlib.h" /* Required for use of simlib.c. */


/** 
 * DEFINE EVENT TYPE ASSIGNMENT
*/
/**
 * Event type for arrival
*/
#define EVENT_ARRIVAL_PERSON_TERMINAL_1   1 
#define EVENT_ARRIVAL_PERSON_TERMINAL_2   2 
#define EVENT_ARRIVAL_PERSON_CAR_RENTAL   3 

//
#define EVENT_ARRIVAL_BUS_TERMINAL_1      4
#define EVENT_ARRIVAL_BUS_TERMINAL_2      5
#define EVENT_ARRIVAL_BUS_CAR_RENTAL      6

/**
 * Event type for departure
*/
#define EVENT_DEPARTURE_BUS_TERMINAL_1    7
#define EVENT_DEPARTURE_BUS_TERMINAL_2    8
#define EVENT_DEPARTURE_BUS_CAR_RENTAL    9

/**
 * Event type for unload person
*/
#define EVENT_UNLOAD_PERSON_TERMINAL_1    10
#define EVENT_UNLOAD_PERSON_TERMINAL_2    11
#define EVENT_UNLOAD_PERSON_CAR_RENTAL    12

/**
 * Event type for load person
*/
#define EVENT_LOAD_PERSON_TERMINAL_1      13
#define EVENT_LOAD_PERSON_TERMINAL_2      14
#define EVENT_LOAD_PERSON_CAR_RENTAL      15

/**
 * Event type for end the simulation
*/
#define EVENT_END_SIMULATION              16

/**
 * Random stream for TUBES 1
*/
#define STREAM_INTERARRIVAL_TERMINAL_1  1
#define STREAM_INTERARRIVAL_TERMINAL_2  2
#define STREAM_INTERARRIVAL_CAR_RENTAL  3
#define STREAM_UNLOADING                4
#define STREAM_LOADING                  5
#define STREAM_DESTINATION              6

/**
 * Define variable
*/
#define DESTINATION_TERMINAL_1 1
#define DESTINATION_TERMINAL_2 2
#define DESTINATION_CAR_RENTAL 3

#define LIST_TERMINAL_1 1
#define LIST_TERMINAL_2 2
#define LIST_CAR_RENTAL 3
#define LIST_BUS_TO_TERMINAL_1  4
#define LIST_BUS_TO_TERMINAL_2  5
#define LIST_BUS_TO_CAR_RENTAL  6

/**
 * Max bus capacity
*/
#define MAX_BUS_SIZE 20





int main() {
    
}