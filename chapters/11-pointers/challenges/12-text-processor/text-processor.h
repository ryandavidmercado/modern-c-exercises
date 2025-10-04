#include <stddef.h>
typedef struct blob blob;
struct blob {
  char *text;
  blob *prev;
  blob *next;
};

/**
 * Splits the given blob into two blobs by slicing text at the split_point.
 * The given blob gets a *next of the new blob, while the new blob inherits
 * the previous *next from the given blob.
 *
 * Returns the given blob.
 */
blob *blob_split(blob *base, size_t split_point);

/**
 * Joins the given blob with its *next blob by concatenating the text of the
 * *next blob. The given blob inherits the previous *next from its *next blob.
 *
 * Returns the given blob.
 */
blob *blob_join_with_next(blob *base);

/**
 * Creates a set of blobs delimited against the input text.
 * The *next blob is created when the input reaches a newline.
 * The newline character is included in the preceding blob.
 *
 * Returns the root blob.
 */
blob *blob_create(char const *text);

/**
 * Prints the entire text or prints until the text is cut off due to the screen
 * size.
 */
void blob_print(blob *root);
