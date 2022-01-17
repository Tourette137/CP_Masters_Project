#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/papiRun.h"
#include "include/BucketSort.h"
#include "include/config.h"
#include "include/Utils.h"
#include "papi.h"

#define NUM_EVENTS 3
int Events[NUM_EVENTS] = {PAPI_L1_DCM, PAPI_L2_DCM, PAPI_L3_TCM};

// PAPI counters' values
long long values[NUM_EVENTS], min_values[NUM_EVENTS];

// number of times the function is executed and measured
#define NUM_RUNS 5


int runPapi(double *secondsSort, int **array) {

    long long start_usec, end_usec, elapsed_usec, min_usec=0L;
    int num_hwcntrs = 0;
    int i,run;

    fprintf (stdout, "\nSetting up PAPI...");
    // Initialize PAPI
    PAPI_library_init (PAPI_VER_CURRENT);

    /* Get the number of hardware counters available */
    if ((num_hwcntrs = PAPI_num_counters()) <= PAPI_OK)  {
        fprintf (stderr, "PAPI error getting number of available hardware counters!\n");
        return 0;
    }
    fprintf(stdout, "done!\nThis system has %d available counters.\n\n", num_hwcntrs);

    // We will be using at most NUM_EVENTS counters
    if (num_hwcntrs >= NUM_EVENTS) {
        num_hwcntrs = NUM_EVENTS;
    } else {
        fprintf (stderr, "Error: there aren't enough counters to monitor %d events!\n", NUM_EVENTS);
        return 0;
    }

    double secondsRuns[NUM_RUNS];
    int* copiaArray = malloc(NARRAY * sizeof(int));

    for (run=0 ; run < NUM_RUNS ; run++) {

        memcpy(copiaArray, *array, NARRAY * sizeof(int));

        fprintf (stderr, "\nrun=%d ", run);

        // use PAPI timer (usecs) - note that this is wall clock time
        // for process time running in user mode -> PAPI_get_virt_usec()
        // real and virtual clock cycles can also be read using the equivalent
        // PAPI_get[real|virt]_cyc()
        start_usec = PAPI_get_real_usec();

        /* Start counting events */
        if (PAPI_start_counters(Events, num_hwcntrs) != PAPI_OK) {
            fprintf (stderr, "PAPI error starting counters!\n");
            return 0;
        }

        BucketSort(copiaArray);

        /* Stop counting events */
        if (PAPI_stop_counters(values, NUM_EVENTS) != PAPI_OK) {
            fprintf (stderr, "PAPI error stoping counters!\n");
            return 0;
        }

        end_usec = PAPI_get_real_usec();
        fprintf (stderr, "done!\n");

        elapsed_usec = end_usec - start_usec;

        secondsRuns[run]=elapsed_usec;

        if ((run==0) || (elapsed_usec < min_usec)) {
            min_usec = elapsed_usec;
            for (i=0 ; i< NUM_EVENTS ; i++) min_values[i] = values [i];
        };

    } // end runs
    printf ("\nWall clock time: %lld usecs\n", min_usec);

    memcpy(*array, copiaArray, NARRAY * sizeof(int));

    double totalTimeRuns = 0;
    for (int i=0; i<NUM_RUNS; i++)
        totalTimeRuns += secondsRuns[i];
    *secondsSort = (totalTimeRuns/(double)NUM_RUNS) / (double)1000000;

    // output PAPI counters' values
    for (i=0 ; i< NUM_EVENTS ; i++) {
            char EventCodeStr[PAPI_MAX_STR_LEN];

            if (PAPI_event_code_to_name(Events[i], EventCodeStr) == PAPI_OK) {
                    fprintf (stdout, "%s = %lld\n", EventCodeStr, min_values[i]);
            } else {
                    fprintf (stdout, "PAPI UNKNOWN EVENT = %lld\n", min_values[i]);
            }
    }

    #if NUM_EVENTS >1
    // evaluate CPI and Texec here
    if ((Events[0] == PAPI_TOT_CYC) && (Events[1] == PAPI_TOT_INS)) {
        float CPI = ((float) min_values[0]) / ((float) min_values[1]);
        fprintf (stdout, "CPI = %.2f\n", CPI);
    }
    #endif

    printf ("\nThat's all, folks\n");
    return 1;
}