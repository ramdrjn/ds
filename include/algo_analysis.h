#ifndef _ALGO_ANALYSIS_H_
#define _ALGO_ANALYSIS_H_

#include "log.h"

static int algo_steps;
static int algo_storage;

static inline void algo_time_analysis(int n, char *complexity)
{
    info("number of steps for n value %d is %d", n, algo_steps);
    info("time complexity is O(%s)", complexity);
}

static inline void algo_space_analysis(int n, char *complexity)
{
    info("number of storage for n value %d is %d", n, algo_storage);
    info("storage complexity is O(%s)", complexity);
}

#endif /*_ALGO_ANALYSIS_H_*/
