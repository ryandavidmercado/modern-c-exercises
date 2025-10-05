#include <stddef.h>
#include <stdlib.h>
/**
 * a type for a circular buffer for double values
 *
 * This data structure allows to add double values to tail and to pop the value
 * from head (FIFO). Each such structure has a maximal amount of elements that
 * can be stored in it.
 *
 */
struct circular {
  size_t start [[deprecated("privat")]]; /* First element index */
  size_t len [[deprecated("privat")]];   /* Number of elements */
  size_t cap [[deprecated("privat")]];   /* Maximum capacity */
  double *tab [[deprecated("privat")]];  /* Data array */
};
typedef struct circular circular;

// --------- DATA OPERATIONS (append, pop, element) ---------

/**
 * Append a new element with value *value* to the buffer *c*.
 *
 * Returns: c if the new element could be appended, null otherwise.
 */
circular *circular_append(circular *c, double value);

/**
 * Remove the oldest element from *c* and return its value.
 *
 * Returns: the removed element if it exists, 0.0 otherwise.
 */
double circular_pop(circular *c);

/**
 * Return a pointer to position pos in buffer *c*.
 *
 * Returns: a poitner to element *pos* of the buffer, otherwise nullptr.
 */
double *circular_element(circular const *c, size_t pos);
//
// ----------------------------------------------------------

// --------- LIFECYCLE OPERATIONS (PRE-DEFINED STRUCT) ---------

/**
 * Initialize a circular buffer *c* with maximally *cap* elements.
 *
 * Only use this function on an uninitialized buffer.
 * Each buffer that is initialized with this function must be destroyed
 * with a call to circular_destroy.
 */
circular *circular_init(circular *c, size_t cap);
//
/**
 * Destroy circular buffer *c*.
 *
 * *c* must have been initialized with a call to circular_init.
 */
void circular_destroy(circular *c);

// ---------------------------------------------------------------

// --------- LIFECYCLE OPERATIONS (CREATE/ALLOCATE STRUCT) ---------

/**
 * Allocate and initialize a circular buffer with maximally *len* elements.
 * Each buffer that is allocated with this function must be deleted with a call
 * to circular_delete.
 */
[[nodiscard("pointer to allocated data dropped")]] [[__gnu__::__malloc__]]
inline circular *circular_new(size_t len) {
  return circular_init(malloc(sizeof(circular)), len);
}
//
/**
 * Delete circular buffer *c*.
 * *c* must have been allocated with a call to circular_new.
 */
inline void circular_delete(circular *c) {
  circular_destroy(c);
  free(c);
}

// ------------------------------------------------------------------

// --------- LENGTH OPERATIONS ----------

/**
 * Resize to capacity *cap*.
 */
[[nodiscard("returned pointer replaces function argument.")]]
circular *circular_resize(circular *c, size_t cap);
//
/**
 * Returns the number of elements stored.
 */
size_t circular_getlength(circular const *c);

// --------------------------------------
