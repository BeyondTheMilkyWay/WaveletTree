//
// Created by dsisejkovic on 12.01.16..
//

#include "Timer.h"

double timedifference_msec(struct timeval t0, struct timeval t1) {
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

void timerStart() {
    gettimeofday(&t0, 0);
}

void timerStop() {
    gettimeofday(&t1, 0);
}

double timerGetTimeSpan() {
    return timedifference_msec(t0, t1);
}