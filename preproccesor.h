#ifndef PREPROCESSOR
#define PREPROCESSOR

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>
#include <iostream>
#include <unistd.h>
#include <queue>

//we used a preprocessor

#define NAME_1 "/queue1"

#define NAME_2 "/queue2"

#define NUM_1 2

#define NUM_2 3

#define NUM 5

struct my_message_c1 {
    int number[NUM_1] ;
    int flag[NUM_1] ;
    int number_of_number ;
};

struct my_message_c2 {
    int number[NUM_2] ;
    int flag[NUM_2] ;
    int number_of_number ;
};

#define SIZE_C1 (sizeof(struct my_message_c1))

#define SIZE_C2 (sizeof(struct my_message_c2))


#endif