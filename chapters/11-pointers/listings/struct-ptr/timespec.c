#include <time.h>

/**
 * Computes a time difference.
 *
 * This uses a double to compute the time. If we want to be able
 * to track times without further loss of precision and have
 * double with 52 bit mantissa, this corresponds to a maximal
 * time difference of about 4.5E6 seconds, or 52 days.
 */
double timespec_diff(struct timespec const *later,
                     struct timespec const *sooner) {
  if (later->tv_sec < sooner->tv_sec) {
    return -timespec_diff(sooner, later);
  } else {
    return (later->tv_sec - sooner->tv_sec) +
           (later->tv_nsec - sooner->tv_nsec) * 1E-9;
  }
}
