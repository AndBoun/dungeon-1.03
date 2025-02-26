//
// Created by Andrew Boun on 2/25/25.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dijkstra.h>


#define INF 1000000000

// Helper struct to store node data
typedef struct {
    int x;
    int y;
} NodeData;

static int find_all_paths(
    int dist_map[DUNGEON_HEIGHT][DUNGEON_WIDTH],
    int graph[DUNGEON_HEIGHT][DUNGEON_WIDTH],
    int start_x,
    int start_y
);

int find_path(
    int dist_map[DUNGEON_HEIGHT][DUNGEON_WIDTH],
    int graph[DUNGEON_HEIGHT][DUNGEON_WIDTH],
    int start_x,
    int start_y, 
    int end_x,
    int end_y
); 

// Copy function for PriorityQueue
static void* copy_node_data(const void* data) {
    NodeData* new_data = malloc(sizeof(NodeData));
    memcpy(new_data, data, sizeof(NodeData));
    return new_data;
}

// Destroy function for PriorityQueue
static void destroy_node_data(void* data) {
    free(data);
}

// Convert x,y coordinates to unique key for priority queue
static int coord_to_key(int x, int y, int cols) {
    return y * cols + x;
}

int create_non_tunneling_map(Dungeon *d) {
    // Initialize the graph with -1 for unreachable cells
    int graph[DUNGEON_HEIGHT][DUNGEON_WIDTH];
    for (int y = 0; y < DUNGEON_HEIGHT; y++) {
        for (int x = 0; x < DUNGEON_WIDTH; x++) {
            if (d->grid[y][x].hardness == 0){
                graph[y][x] = 1;
            } else {
                graph[y][x] = -1; // -1 for unreachable
            }
        }
    }

    // Initialize the distance map
    for (int i = 0; i < DUNGEON_HEIGHT; i++) {
        for (int j = 0; j < DUNGEON_WIDTH; j++) {
            d->non_tunneling_dist_map[i][j] = INF;
        }
    }

    find_all_paths(d->non_tunneling_dist_map, graph, d->pc_x, d->pc_y);
    
    return 0;
}

int create_tunneling_map(Dungeon *d) {
    // Initialize the graph with -1 for unreachable cells
    int graph[DUNGEON_HEIGHT][DUNGEON_WIDTH];

    for (int y = 0; y < DUNGEON_HEIGHT; y++) {
        for (int x = 0; x < DUNGEON_WIDTH; x++) {
            if (d->grid[y][x].hardness != MAX_HARDNESS){
                graph[y][x] = 1 + (d->grid[y][x].hardness / 85);
            } else {
                graph[y][x] = -1;
            }
        }
    }


    // Initialize the distance map
    for (int i = 0; i < DUNGEON_HEIGHT; i++) {
        for (int j = 0; j < DUNGEON_WIDTH; j++) {
            d->tunneling_dist_map[i][j] = INF;
        }
    }

    find_all_paths(d->tunneling_dist_map, graph, d->pc_x, d->pc_y);

    return 0;
}

static int find_all_paths(
    int dist_map[DUNGEON_HEIGHT][DUNGEON_WIDTH],
    int graph[DUNGEON_HEIGHT][DUNGEON_WIDTH],
    int start_x,
    int start_y
) {
    // Direction arrays for 8-directional movement
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    // int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    // int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
    
    int rows = DUNGEON_HEIGHT;
    int cols = DUNGEON_WIDTH;
    PriorityQueue* pq = pq_create(
        rows * cols, rows * cols,
        copy_node_data, destroy_node_data
    );
    
    // Initialize start node
    NodeData start_data = {start_x, start_y};
    pq_insert(pq, coord_to_key(start_x, start_y, cols), &start_data, 0);

    dist_map[start_y][start_x] = 0;
    

    // Process nodes
    while (!pq_is_empty(pq)) {
        NodeData* current = pq_extract_min(pq);
        int curr_x = current->x;
        int curr_y = current->y;
        
        // Check all 8 directions
        for (int i = 0; i < 8; i++) {
            int next_x = curr_x + dx[i];
            int next_y = curr_y + dy[i];
            
            if (next_x >= 0 && next_x < cols && 
                next_y >= 0 && next_y < rows && 
                graph[next_y][next_x] != -1) {
                
                int edge_cost = graph[curr_y][curr_x];
                int new_dist = dist_map[curr_y][curr_x] + edge_cost;
                    
                if (new_dist < dist_map[next_y][next_x]) {
                    dist_map[next_y][next_x] = new_dist;
                    NodeData next_data = {next_x, next_y};
                    pq_insert(pq, coord_to_key(next_x, next_y, cols), &next_data, new_dist);
                }
            }
        }
        
        free(current);
    }
    
    pq_destroy(pq);
    return 0;
}