# include "../../cub3d.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void map_free(t_map *map) {
    if (map && map->grid) {
        for (int i = 0; i < map->height; i++) {
            if (map->grid[i]) {
                free(map->grid[i]);
            }
        }
        free(map->grid);
        map->grid = NULL;
    }
    map->width = 0;
    map->height = 0;
}

// Trims a newline character from the end of a line
void trim_newline(char *line) {
    int len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }
}

// Initializes the map by reading the map file
void map_init(t_map *map, const char *map_file) {
    char *line = NULL;
    int height = 0;
    int width = 0;
    int fd;
    size_t grid_size = 0;

    if (!map || !map_file) {
        perror("error: invalid map or file path!");
        exit(EXIT_FAILURE);
    }

    // Open the map file
    fd = open(map_file, O_RDONLY);
    if (fd == -1) {
        perror("error: failed to open map file!");
        exit(EXIT_FAILURE);
    }

    // Estimate initial grid size to allocate memory
    grid_size = 32; // Assume an initial size of 32 rows
    map->grid = (char **)malloc(grid_size * sizeof(char *));
    if (!map->grid) {
        perror("error: failed to allocate memory for map grid!");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Read the map line by line
    while ((line = get_next_line(fd)) != NULL) {
        trim_newline(line);

        // Reallocate memory if grid size is exceeded
        if (height >= (int)grid_size) {
            grid_size *= 2; // Double the size
            char **new_grid = (char **)realloc(map->grid, grid_size * sizeof(char *));
            if (!new_grid) {
                free(line);
                // map_free(map);
                perror("error: failed to reallocate memory for map grid!");
                close(fd);
                exit(EXIT_FAILURE);
            }
            map->grid = new_grid;
        }

        // Copy the line to the map grid
        map->grid[height] = strdup(line);
        if (!map->grid[height]) {
            free(line);
            // map_free(map);
            perror("error: failed to duplicate line!");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Update width and height
        int line_length = strlen(map->grid[height]);
        if (line_length > width) {
            width = line_length;
        }
        height++;

        free(line);
    }

    close(fd);

    // Update map dimensions
    map->height = height;
    map->width = width;

    // Handle empty map case
    if (height == 0) {
        perror("error: empty map file!");
        // free(map->grid);
        map->grid = NULL;
        map->width = 0;
        map->height = 0;
        exit(EXIT_FAILURE);
    }
}
