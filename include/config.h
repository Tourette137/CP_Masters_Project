#ifndef CONFIG
#define CONFIG

// Array size
extern int NARRAY;
// Number of buckets
extern int NBUCKET;
// Each bucket capacity
extern int INTERVAL;
// 0 -> INSERTION_SORT | 1 -> QUICK_SORT
extern int METHOD;
// See if it is Parallel (1) or Squential (0)
extern int SEQ_PAR;
// Puts how many threads wants
extern int OMP_NUM_THREADS;

#endif