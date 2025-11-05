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
} Color;

typedef struct {
    char* unicode;
    Color text_color;
    Color background_color;
} Cell;

typedef struct {
    Cell** current_cells;
    int current_width;
    int current_height;
} ScreenWriter;

Cell** copy_cell_array(Cell** cells, int length) {
    if (!cells || length <= 0) return NULL;

    Cell** copy = malloc(sizeof(Cell*) * length);
    if (!copy) return NULL;
    
    for (int i = 0; i < length; i++) {
        if (cells[i] == NULL) {
            copy[i] = NULL;
            continue;
        }

        // Allocate memory for new Cell
        copy[i] = malloc(sizeof(Cell));
        if (!copy[i]) {
            // In case of allocation failure, free already allocated cells
            for (int j = 0; j < i; j++) free(copy[j]);
            free(copy);
            return NULL;
        }

        // Copy the colors
        copy[i]->text_color = cells[i]->text_color;
        copy[i]->background_color = cells[i]->background_color;

        // Deep copy unicode string
        if (cells[i]->unicode) {
            copy[i]->unicode = strdup(cells[i]->unicode);
            if (!copy[i]->unicode) {
                // Free already allocated memory
                for (int j = 0; j <= i; j++) free(copy[j]);
                free(copy);
                return NULL;
            }
        } else {
            copy[i]->unicode = NULL;
        }
    }

    return copy;
}

void free_cell_array(Cell** cells, int length) {
    if (!cells) return;
    for (int i = 0; i < length; i++) {
        if (cells[i]) {
            free(cells[i]->unicode);
            free(cells[i]);
        }
    }
    free(cells);
}

int cell_eq(Cell* cell_1, Cell* cell_2) {
    return strcmp(cell_1->unicode, cell_2->unicode) == 0 &&
        cell_1->text_color.r == cell_2->text_color.r &&
        cell_1->text_color.g == cell_2->text_color.g &&
        cell_1->text_color.b == cell_2->text_color.b &&
        cell_1->background_color.r == cell_2->background_color.r &&
        cell_1->background_color.g == cell_2->background_color.g &&
        cell_1->background_color.b == cell_2->background_color.b;
}

void set_cursor(int row, int col) {
    printf("\033[%s;%sH", row, col);
}

void get_terminal_dimensions(int* width, int* height) {

    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("ioctl");
        return 1;
    }
    *width = w.ws_col;
    *height = w.ws_row;
}

/**
 * Repaints the screen with the new cells, skipping any that are unchanged
 */
void set_screen(Cell** new_cells, int width, int height, ScreenWriter* screen_writer) {

    // if screen size has changed reset everything
    if (screen_writer->current_height != height || screen_writer->current_width != width) {
        printf("\033[2J"); // Clear entire screen
        for (int i = 0; i < width * height; ++i) {
            Cell* cell = new_cells[i];
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
        printf(ANSI_RESET);
        fflush(stdout);
    }
    // otherwise only change what has changed
    else {
        int length = width * height;
        for (int i = 0; i < length; ++i) {
            Cell* cell = new_cells[i];
            Cell* old_cell = screen_writer->current_cells[i];
            if (!cell_eq(cell, old_cell)) {
                int y = i / width;
                int x = i - y;
                set_cursor(x, y);
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
            
        }
        printf(ANSI_RESET);
        fflush(stdout);
    }
    
}

#endif