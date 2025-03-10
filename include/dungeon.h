//
// Created by Andrew Boun on 2/11/25.
//

#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdbool.h>

#define INF 1000000000

// Character definitions for the Dungeon grid
#define ROCK ' '
#define FLOOR '.'
#define CORRIDOR '#'
#define DOWN_STAIRS '>'
#define UP_STAIRS '<'
#define PLAYER '@'

// Border characters for the Dungeon grid
#define HORIZONTAL_BORDER '-'
#define VERTICAL_BORDER '|'

#define DUNGEON_WIDTH 80
#define DUNGEON_HEIGHT 21

#define PLACABLE_WIDTH 78
#define PLACABLE_HEIGHT 19

#define MIN_ROOMS 6
#define MAX_ROOMS 120

#define MIN_ROOM_WIDTH 4
#define MIN_ROOM_HEIGHT 3

#define MIN_DOWN_STAIRS 1
#define MAX_DOWN_STAIRS 4
#define MIN_UP_STAIRS 1
#define MAX_UP_STAIRS 4

#define MIN_HARDNESS 0
#define MAX_HARDNESS 255

// Maximum number of attempts to generate a room
// If the number of attempts exceeds this value,
// The grid will reset and try again
#define MAX_ATTEMPTS 2000

typedef struct {
    int x, y;       // top-left coordinate (not including border)
    int width, height;
    int center_x, center_y;
} Room;

typedef struct {
    int hardness;
    char type;
} FloorTile;

typedef struct {
    int x, y;
} Stair;

typedef struct {
    FloorTile grid[DUNGEON_HEIGHT][DUNGEON_WIDTH];
    Room* rooms;       // Dynamically allocated array of rooms
    int num_rooms;     // Number of rooms in the Dungeon
    int current_room_idx;  // Bit field initialized to 0 by default
    int pc_x, pc_y;    // Player character coordinates
    int num_up_stairs, num_down_stairs;
    Stair* up_stairs;
    Stair* down_stairs;
    int current_up_stair_idx;
    int current_down_stair_idx;

    int non_tunneling_dist_map [DUNGEON_HEIGHT][DUNGEON_WIDTH];
    int tunneling_dist_map [DUNGEON_HEIGHT][DUNGEON_WIDTH];
} Dungeon;


void init_dungeon(Dungeon *d);

// Function prototypes updated to work with Dungeon struct
void generate_corridor(Dungeon *d, int x1, int y1, int x2, int y2);

int can_insert_room(Dungeon *d, Room room);
void generate_room(Dungeon *d, Room room);
bool generate_random_room(Dungeon *d);

int generate_random_stair(Dungeon *d, char stair, int idx);
bool place_stair(Dungeon *d, int x, int y, char stair);

void print_room_info(const Dungeon *d);
void print_hardness_info(const Dungeon *d);
void print_grid(const Dungeon *d);

int place_random_player(Dungeon *d);
bool generate_random_dungeon(Dungeon *d);

void destroy_dungeon(Dungeon *d);

void print_dist_map(const int dist_map[DUNGEON_HEIGHT][DUNGEON_WIDTH]);

#endif