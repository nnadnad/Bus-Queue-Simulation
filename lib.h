/**
 * library for rental purpose
 * need add variable for every function in main.c
*/



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

#define DATA_ARRIVAL_TIME 1
#define DATA_DESTINATION  2


/**
 * Variable for statistics
*/
/**
 * Average and maximum number in each queue
*/
#define VARIABLE_NUM_TERMINAL_1 1
#define VARIABLE_NUM_TERMINAL_2 2
#define VARIABLE_NUM_CAR_RENTAL 3

/**
 * Average and maximum delay in each queue
*/
#define VARIABLE_DELAY_TERMINAL_1 4
#define VARIABLE_DELAY_TERMINAL_2 5
#define VARIABLE_DELAY_CAR_RENTAL 6

/**
 * Average and maximum number on the bus
*/
#define VARIABLE_NUM_BUS 7

/**
 * Average, maximum, and minimum time the bus is stopped at each location
*/
#define VARIABLE_BUS_STOP_TERMINAL_1 8
#define VARIABLE_BUS_STOP_TERMINAL_2 9
#define VARIABLE_BUS_STOP_CAR_RENTAL 10

/**
 * Average, maximum, and minimum time for the bus to make a loop (departure
 * from the car rental to the next such departure)
*/
#define VARIABLE_BUS_LOOP 11

/**
 * Average, maximum, and minimum time a person is in the system by arrival
 * location
*/
#define VARIABLE_PERSON_SYSTEM 12