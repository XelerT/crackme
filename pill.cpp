#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "pill.h"
#include "graphic_crack.h"

int main (int argc, char *argv[])
{
        if (argc != 3) {
                fprintf(stderr, "You need to enter mode and the way to the folder with gif. %d\n", argc);
                return NO_ARGS;
        }
        text_t text = {};
        unsigned char new_code[2] = {0xEB, 0x0C};
        FILE *code2change = fopen("ASIAS.COM", "r");
        get_text(code2change, &text, "ASIAS.COM");
        fclose(code2change);
        int change_adress = 0x84;

        switch_code_changer(*argv[1], &text, change_adress, new_code, 2);

        free(text.buf);
        free(text.lines);

        play_gif_progress_bar(argv[2]);

        return 0;
}

int switch_code_changer (int argument, text_t *text, int adress, unsigned char *new_code, int n_bytes)
{
        if (argument == CHANGE_BY_ADRESS) {
                change_in_adress(text, adress, new_code, n_bytes);
        } else {
                unsigned char *what2change = find_call2change(text);
                change_code(what2change, new_code, n_bytes);
        }
        FILE* code2change = fopen("asias_cracked.com", "w");
        fwrite(text->buf, sizeof(char), text->n_chars + 1, code2change);
        fclose(code2change);

        return 0;
}

static const int CALL_CODE_LEN = 2;

int change_code (unsigned char *what2change, unsigned char *new_code, int n_bytes)
{
        assert(what2change);

        for (int i = 0; i < n_bytes; i++)
                what2change[i] = new_code[i];

        return 0;
}

unsigned char* find_call2change (text_t *text)
{
        assert(text);

        unsigned char call_code[CALL_CODE_LEN] = {116, 12};

        return (unsigned char*) memmem((unsigned char*) text->buf, text->n_chars, (unsigned char*) call_code, CALL_CODE_LEN);
}

int change_in_adress (text_t *text, int address, unsigned char *new_code, int n_bytes)
{
        assert(text);
        assert(new_code);

        for (int i = 0; i < n_bytes; i++, address++) {
                printf("%x %x\n", text->buf[address], new_code[i]);
                text->buf[address] = new_code[i];
        }

        return 0;
}

int get_text (FILE *input, text_t *text, const char *file_name)
{
        assert(input);
        assert(text);
        assert(file_name);

        if (!input) {
                fprintf(stderr, "File pointer is null.");
                return NULL_FILE_PTR;
        }
        if (!text) {
                fprintf(stderr, "Text pointer is null.");
                return NULL_TEXT_PTR;
        }

        struct stat file = {};
        if (stat(file_name, &file) < 0)
                return FILE_ERR;

        size_t n_chars = 0;
        unsigned char *buf = (unsigned char*) calloc(file.st_size + 1, sizeof(unsigned char));
        if (!buf) {
                fprintf(stderr, "Calloc returned NULL.");
                return NULL_CALLOC;
        }

        n_chars = fread(buf, sizeof(unsigned char), file.st_size, input);
        text->n_chars = n_chars;

        text->buf = buf;
        text->n_lines = file.st_size - n_chars;
        if (!n_chars) {
                fprintf(stderr, "Input file is empty.");
                return EMPTY_FILE;
        }
        return 0;
}
