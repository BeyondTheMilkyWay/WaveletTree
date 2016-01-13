//
// Created by dsisejkovic on 13.01.16..
//

#ifndef C_BATCHTESTER_H
#define C_BATCHTESTER_H

#include "Basic.h"
#include "Utils.h"

/**
 * Generates performance report (cpu usage and used memory) for
 * tree build for given 'file_name'. Batch will be executed 'num_of_runs' times.
 * Result will be written to '<file_name>_batch_res.txt'.
 */
void batchTest(char *file_name, char *out_file_name, int num_of_runs);

#endif //C_BATCHTESTER_H
