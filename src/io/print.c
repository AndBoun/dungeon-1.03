//
// Created by Andrew Boun on 2/11/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <dungeon.h>

void print_hardness_info(const Dungeon *d){
    for (int i = 0; i < DUNGEON_HEIGHT; i++){
        for (int j = 0; j < DUNGEON_WIDTH; j++){
            printf("%d ", d->grid[i][j].hardness);
        }
        printf("\n");
    }
}

// Prints grid with a border
void print_grid(const Dungeon *d){
    for(int i = 0; i < DUNGEON_WIDTH + 2; i++){
        printf("%c", HORIZONTAL_BORDER);
    }
    printf("\n");

    for (int i = 0; i < DUNGEON_HEIGHT; i++){
        printf("%c", VERTICAL_BORDER);
        for (int j = 0; j < DUNGEON_WIDTH; j++){
            printf("%c", d->grid[i][j].type);
        }
        printf("%c", VERTICAL_BORDER);
        printf("\n");
    }

    for(int i = 0; i < DUNGEON_WIDTH + 2; i++){
        printf("%c", HORIZONTAL_BORDER);
    }
    printf("\n");
}

void print_room_info(const Dungeon *d){
    for (int i = 0; i < d->num_rooms; i++){
        printf("Room %d\n", i + 1);
        printf("x: %d\n", d->rooms[i].x);
        printf("y: %d\n", d->rooms[i].y);
        printf("width: %d\n", d->rooms[i].width);
        printf("height: %d\n", d->rooms[i].height);
        printf("center_x: %d\n", d->rooms[i].center_x);
        printf("center_y: %d\n", d->rooms[i].center_y);
        printf("\n");
    }
}

void print_dist_map(const int dist_map[DUNGEON_HEIGHT][DUNGEON_WIDTH]){
    for(int i = 0; i < DUNGEON_WIDTH + 2; i++){
        printf("%c", HORIZONTAL_BORDER);
    }
    printf("\n");

    for (int i = 0; i < DUNGEON_HEIGHT; i++){
        printf("%c", VERTICAL_BORDER);
        for (int j = 0; j < DUNGEON_WIDTH; j++){
            if (dist_map[i][j] == 0){
                printf("%c", PLAYER);
            }else if (dist_map[i][j] == INF || dist_map[i][j] == -1){
                printf(" ");
            } else {
                printf("%d", dist_map[i][j] % 10);
            }
        }
        printf("%c", VERTICAL_BORDER);
        printf("\n");
    }

    for(int i = 0; i < DUNGEON_WIDTH + 2; i++){
        printf("%c", HORIZONTAL_BORDER);
    }
    printf("\n");
}
