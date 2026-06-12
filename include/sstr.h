#ifndef SSTR_H
#define SSTR_H

#define DEFAULT_CAPACITY 16
#define SSTR_NPOS ((size_t)-1)

// VALID STRING:
//
// s != NULL
//
// Either:
//
//     ptr == NULL
//     len == 0
//     cap == 0
//
// Or:
//
//     ptr != NULL
//     cap >= len + 1
//     ptr[len] == '\0'
//
// Functions that modify the buffer (clear, insert, trim, etc.) return
// ERR_INVALID_STATE if the string is in the zero/unallocated state.

#include <stdbool.h>
#include <stdlib.h>

typedef enum {
  SUCCESS = 0,
  ERR_NULL_ARGUMENT,
  ERR_OUT_OF_MEMORY,
  ERR_OUT_OF_BOUNDS,
  ERR_STRING_INIT_FAILED,
} Err;

// maybe place  assert((s->ptr == NULL) == (s->len == 0) && (s->ptr == NULL) ==
// (s->cap == 0));

typedef struct {

  char *ptr;
  size_t len;
  size_t cap; // sizeof(void *) ? for default capacity
} String;

// Helper functions
static inline size_t min_size(size_t a, size_t b) { return a < b ? a : b; }

size_t sstr_strlen(const char *string);

static size_t sstr_memcpy(char *restrict to, const void *restrict from,
                          size_t bytes_num);

static size_t sstr_memmove(char *to, const void *from, size_t bytes_num);

// implement later
static size_t sstr_memmove();

// implemented
Err sstr_init(String *s, const char *cstr);
Err sstr_destroy(String *s);
Err sstr_clear(String *s);

Err sstr_append(String *s, const char *slice);
Err sstr_append_n(String *s, const char *slice, size_t len);

Err sstr_insert(String *s, size_t index, const char *slice);

size_t sstr_len(const String *s);
size_t sstr_cap(const String *s);

Err sstr_copy(String *s_dest, const String *s_src);
Err sstr_reserve(String *s, size_t count);

bool sstr_empty(const String *s);

Err sstr_shrink(String *s);

Err sstr_trim(String *s);
Err sstr_ltrim(String *s);
Err sstr_rtrim(String *s);

char *sstr_c_str(const String *s);

Err sstr_tolower(String *s);
Err sstr_toupper(String *s);

// < 0 if a < b
// 0 if a == b
// > 0 if a > b
int sstr_cmp(const String *s1, const String *s2);

Err sstr_at(const String *s, size_t index,
            char *out); // bounds-checked index access

size_t sstr_find(const String *str, const char *substr);

#endif /* SSTR_H */
