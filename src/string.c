#include "../include/string.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

ErrorCode string_init(String *s_out, const char *s_in) {
  if (s_out == NULL) {
    return ERR_NULL_PTR;
  }

  if (s_in == NULL) {
    s_out->ptr = NULL;
    s_out->len = 0;
    s_out->cap = 0;

    return ERR_NULL_PTR;
  }
  s_out->ptr = NULL;
  s_out->len = 0;
  s_out->cap = DEFAULT_CAPACITY;

  for (size_t i = 0; s_in[i] != '\0'; i++) {
    s_out->len += 1;
  }

  if (s_out->len >= s_out->cap) {
    s_out->cap = s_out->len * 2;
  }

  s_out->ptr = (char *)malloc(s_out->cap);
  if (s_out->ptr == NULL) {
    return ERR_ALLOC_FAILED;
  }

  for (size_t i = 0; s_in[i] != '\0'; i++) {
    s_out->ptr[i] = s_in[i];
  }
  s_out->ptr[s_out->len] = '\0';

  return SUCCESS;
}

ErrorCode string_destroy(String *s) {
  if (s == NULL) {
    return ERR_NULL_PTR;
  }

  free(s->ptr);
  s->ptr = NULL;
  s->len = 0;
  s->cap = 0;

  return SUCCESS;
}

ErrorCode string_append(String *s, const char *slice) {
  if (s == NULL || slice == NULL) {
    return ERR_NULL_ARGUMENT;
  }

  if (s->ptr == NULL) {
    return (string_init(s, slice) == SUCCESS) ? SUCCESS
                                              : ERR_STRING_INIT_FAILED;
  }

  size_t slice_len = 0; // size_t slice_len = my_strlen(slice);

  for (size_t i = 0; slice[i] != '\0'; i++) {
    slice_len++;
  }

  size_t new_len = s->len + slice_len;

  if (s->cap < new_len + 1) {
    size_t tmp_cap = new_len * 2;
    char *tmp_ptr = realloc(s->ptr, tmp_cap);

    if (tmp_ptr == NULL) {
      return ERR_ALLOC_FAILED;
    }

    s->ptr = tmp_ptr;
    s->cap = tmp_cap;
  }

  for (size_t i = 0; slice[i] != '\0'; i++) {
    s->ptr[s->len + i] = slice[i];
  }

  s->len = new_len;
  s->ptr[s->len] = '\0';

  return SUCCESS;
}
