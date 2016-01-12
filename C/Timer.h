//
// Created by dsisejkovic on 12.01.16..
//

#ifndef C_TIMER_H
#define C_TIMER_H

#include <time.h>
#include <sys/time.h>

clock_t start;
clock_t end;

struct timeval t0;
struct timeval t1;

void timerStart();

void timerStop();

double timerGetTimeSpan();

#endif //C_TIMER_H
