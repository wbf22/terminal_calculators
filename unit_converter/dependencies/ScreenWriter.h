#ifndef SCREEN_WRITER
#define SCREEN_WRITER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/ioctl.h>

#define ANSI_RESET "\x1b[0m"

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} SWColor;

typedef struct {
    char* unicode;
    SWColor text_color;
    SWColor background_color;
} SWCell;

typedef struct {
    SWCell** current_cells;
    int current_width;
    int current_height;
} ScreenWriter;

void sw_copy_cell(SWCell* cell, SWCell* dest) {
    free(dest->unicode);
    dest->unicode = strdup(cell->unicode);
    dest->background_color.r = cell->background_color.r;
    dest->background_color.g = cell->background_color.g;
    dest->background_color.b = cell->background_color.b;
    dest->text_color.r = cell->text_color.r;
    dest->text_color.g = cell->text_color.g;
    dest->text_color.b = cell->text_color.b;
}

SWCell** sw_copy_cell_array(SWCell** cells, int length) {
    if (!cells || length <= 0) return NULL;

    SWCell** copy = malloc(sizeof(SWCell*) * length);
    if (!copy) return NULL;
    
    for (int i = 0; i < length; i++) {
        if (cells[i] == NULL) {
            copy[i] = NULL;
            continue;
        }

        copy[i] = malloc(sizeof(SWCell));
        sw_copy_cell(cells[i], copy[i]);
    }

    return copy;
}

void sw_free_cell_array(SWCell** cells, int length) {
    if (!cells) return;
    for (int i = 0; i < length; i++) {
        if (cells[i]) {
            free(cells[i]->unicode);
            free(cells[i]);
        }
    }
    free(cells);
}

int sw_cell_eq(SWCell* cell_1, SWCell* cell_2) {
    return strcmp(cell_1->unicode, cell_2->unicode) == 0 &&
        cell_1->text_color.r == cell_2->text_color.r &&
        cell_1->text_color.g == cell_2->text_color.g &&
        cell_1->text_color.b == cell_2->text_color.b &&
        cell_1->background_color.r == cell_2->background_color.r &&
        cell_1->background_color.g == cell_2->background_color.g &&
        cell_1->background_color.b == cell_2->background_color.b;
}

void sw_set_cursor(int row, int col) {
    printf("\033[%s;%sH", row, col);
}

void sw_get_terminal_dimensions(int* width, int* height) {

    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("ioctl");
        *width = -1;
        *height = -1;
        return;
    }
    *width = w.ws_col;
    *height = w.ws_row;
}

/**
 * Repaints the screen with the new cells, skipping any that are unchanged
 */
void sw_set_screen(SWCell** new_cells, int width, int height, ScreenWriter* screen_writer) {

    // if screen size has changed reset everything
    if (screen_writer->current_cells == NULL || screen_writer->current_height != height || screen_writer->current_width != width) {
        printf("\033[2J"); // Clear entire screen
        for (int i = 0; i < width * height; ++i) {
            SWCell* cell = new_cells[i];
            printf(
                "\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm%s", 
                cell->text_color.r, 
                cell->text_color.g, 
                cell->text_color.b,

                cell->background_color.r, 
                cell->background_color.g, 
                cell->background_color.b,
            
                cell->unicode
            );
        }
        if (screen_writer->current_cells != NULL) {
            sw_free_cell_array(screen_writer->current_cells, screen_writer->current_width * screen_writer->current_height);
        }
        screen_writer->current_cells = sw_copy_cell_array(new_cells, width * height);
        printf(ANSI_RESET);
        fflush(stdout);
    }
    // otherwise only change what has changed
    else {
        int length = width * height;
        for (int i = 0; i < length; ++i) {
            SWCell* cell = new_cells[i];
            SWCell* old_cell = screen_writer->current_cells[i];
            if (!sw_cell_eq(cell, old_cell)) {
                int y = i / width;
                int x = i - y;
                sw_set_cursor(x, y);
                printf(
                    "\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm%s", 
                    cell->text_color.r, 
                    cell->text_color.g, 
                    cell->text_color.b,

                    cell->background_color.r, 
                    cell->background_color.g, 
                    cell->background_color.b,
                
                    cell->unicode
                );
                sw_copy_cell(cell, screen_writer->current_cells[i]);
            }
            
        }
        printf(ANSI_RESET);
        fflush(stdout);
    }
    
}

#endif