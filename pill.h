#ifndef PILL_H
#define PILL_H

enum errors {
        NULL_FILE_PTR   = -5,
        NULL_TEXT_PTR   = -4,
        EMPTY_FILE      = -3,
        NULL_CALLOC     = -2,
        FILE_ERR        = -1
};

struct line_t
{
        char *ptr = nullptr;
        size_t n_chars = 0;
};

struct text_t {
        size_t n_lines = 0;
        size_t n_chars = 0;
        unsigned char *buf = nullptr;
        line_t *lines = nullptr;
};

int get_text         (FILE *input, text_t *text, const char *file_name);
int change_code      (unsigned char *what2change);
unsigned char* find_call2change (text_t *text);

#endif /*PILL_H*/
