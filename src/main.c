//
// Created by Andrew Boun on 2/11/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include <dungeon.h>
#include <load_save.h>
#include <priority_queue.h>

// Custom data structure
typedef struct {
    char name[20];
    int value;
} Data;

// Copy function for Data
void* copy_data(const void* src) {
    Data* new_data = malloc(sizeof(Data));
    if (new_data) {
        memcpy(new_data, src, sizeof(Data));
    }
    return new_data;
}

// Cleanup function for Data
void destroy_data(void* data) {
    free(data);
}

int main(int argc, char *argv[]) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec ^ getpid());

    Dungeon d;
    init_dungeon(&d);

    int load_flag = 0;
    int save_flag = 0;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--load") == 0) {
            load_flag = 1;
        } else if (strcmp(argv[i], "--save") == 0) {
            save_flag = 1;
        }
    }

    if (load_flag) {
        load(&d);
        print_grid(&d);
    } else {
        if (generate_random_dungeon(&d)) {
            print_grid(&d);
        } else {
            printf("Dungeon generation failed.\n");
            return 1;
        }
    }

    if (save_flag) {
        save(&d);
        printf("Dungeon saved.\n");
    }

    destroy_dungeon(&d);

    // Create priority queue with capacity 10 and key range 100
    PriorityQueue* pq = pq_create(10, 100, copy_data, destroy_data);
    
    // Create some test data
    Data items[] = {
        {"Item A", 100},
        {"Item B", 200},
        {"Item C", 300}
    };
    
    // Insert items with different priorities
    pq_insert(pq, 5, &items[0], 30);  // key 5, priority 30
    pq_insert(pq, 2, &items[1], 10);  // key 2, priority 10
    pq_insert(pq, 8, &items[2], 20);  // key 8, priority 20
    
    // Update priority of an item
    pq_update_priority(pq, 5, 5);  // Update key 5 to priority 5
    
    // Extract items in priority order
    while (!pq_is_empty(pq)) {
        int min_key = pq_get_min_key(pq);
        printf("Priority: %d\n", pq_get_priority(pq, min_key));
        Data* data = pq_extract_min(pq);
        printf("Key: %d, Name: %s, Value: %d\n", 
               min_key, data->name, data->value);
        free(data);  // Free the extracted data
    }
    
    pq_destroy(pq);


    return 0;
}