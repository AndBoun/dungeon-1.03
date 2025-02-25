//
// Created by Andrew Boun on 2/24/25.
//

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// Node structure for the priority queue
typedef struct {
    int vertex;    // Vertex identifier
    int distance;  // Distance (priority) value
    int x, y; // Coordinates of the vertex
} PQNode;

// Priority queue structure
typedef struct {
    PQNode* heap;     // The actual heap array
    int* positions;   // Map from vertex IDs to their positions in the heap
    int size;         // Current size of the heap
    int capacity;     // Maximum capacity of the heap
} PriorityQueue;

// Create a priority queue with given maximum size
PriorityQueue* pq_create(int max_size);

// Free all memory used by the priority queue
void pq_destroy(PriorityQueue* pq);

// Check if the priority queue is empty
int pq_is_empty(PriorityQueue* pq);

// Insert a vertex with its distance into the priority queue
void pq_insert(PriorityQueue* pq, int vertex, int distance, int x, int y);

// Extract the vertex with minimum distance
int pq_extract_min(PriorityQueue* pq);

// Check if a vertex is in the priority queue
int pq_contains(PriorityQueue* pq, int vertex);

// Update (decrease) the distance of a vertex in the queue
void pq_decrease_key(PriorityQueue* pq, int vertex, int new_distance);

// Get the current distance of a vertex in the queue
int pq_get_distance(PriorityQueue* pq, int vertex);

#endif // PRIORITY_QUEUE_H