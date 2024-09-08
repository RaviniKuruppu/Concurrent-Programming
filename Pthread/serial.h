#ifndef SERIAL_H
#define SERIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include "linked_list.h"
#include "global.h"

unsigned long serialExecution(int total_operations, int member_frac, int insert_frac, int delete_frac);

#endif