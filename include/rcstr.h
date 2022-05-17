#ifndef RCSTR__H
#define RCSTR__H

#define VERSION "0.0.1a"

#include <stdbool.h>
#include <string.h>
#include <malloc.h>

char* rcstr__dropped = "(dropped)";

typedef struct
{
    bool is_mutable;

    unsigned short refcount;
    char* raw;
}
rcstr;

bool rcstr__take(rcstr* string)
{
    if (string->refcount == 0)
        return false;

    string->refcount++;

    return true;
}

bool rcstr__drop(rcstr* string)
{
    if (string->refcount == 0 || string->raw == rcstr__dropped)
        return false;

    string->refcount--;

    if (string->refcount > 0)
        return false;

    if (string->is_mutable)
        free(string->raw);

    string->is_mutable = false;
    string->raw = rcstr__dropped;

    return true;
}

rcstr rcstr__new(char* string)
{
    if (string == NULL || string == rcstr__dropped)
        return (rcstr) { false, 0, rcstr__dropped };

    return (rcstr) { false, 1, string };
}

rcstr rcstr__new_mut(char* mut_string)
{
    if (mut_string == NULL || mut_string == rcstr__dropped)
        return (rcstr) { false, 0, rcstr__dropped };

    return (rcstr) { true, 1, mut_string };
}

rcstr rcstr__copy(rcstr* string)
{
    char* raw = malloc(strlen(string->raw));
    strcpy(raw, string->raw);

    rcstr__drop(string);

    return rcstr__new_mut(raw);
}

rcstr rcstr__cat(rcstr* left, rcstr* right)
{
    size_t raw_length = strlen(left->raw) + strlen(right->raw);
    char* raw = malloc(raw_length +1);
    
    strcpy(raw, left->raw);
    strcat(raw, right->raw);

    rcstr__drop(left);
    rcstr__drop(right);

    return rcstr__new_mut(raw);
}

#endif
