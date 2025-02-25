//
// Created by Andrew Boun on 2/24/25.
//

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "priority_queue.h"

// Initialize a new priority queue
PriorityQueue* pq_create(int max_size) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (!pq) {
        return NULL;
    }
    
    pq->heap = malloc(max_size * sizeof(PQNode));
    if (!pq->heap) {
        free(pq);
        return NULL;
    }
    
    pq->positions = malloc(max_size * sizeof(int));
    if (!pq->positions) {
        free(pq->heap);
        free(pq);
        return NULL;
    }
    
    pq->size = 0;
    pq->capacity = max_size;
    
    // Initialize all positions to -1 (not in heap)
    for (int i = 0; i < max_size; i++) {
        pq->positions[i] = -1;
    }
    
    return pq;
}

// Free all memory used by the priority queue
void pq_destroy(PriorityQueue* pq) {
    if (pq) {
        free(pq->heap);
        free(pq->positions);
        free(pq);
    }
}

// Check if the priority queue is empty
int pq_is_empty(PriorityQueue* pq) {
    return pq->size == 0;
}

// Get the index of the parent node
static int parent(int i) {
    return (i - 1) / 2;
}

// Get the index of the left child
static int left_child(int i) {
    return 2 * i + 1;
}

// Get the index of the right child
static int right_child(int i) {
    return 2 * i + 2;
}

// Swap two nodes in the heap and update their positions
static void pq_swap(PriorityQueue* pq, int i, int j) {
    PQNode temp = pq->heap[i];
    pq->heap[i] = pq->heap[j];
    pq->heap[j] = temp;
    
    // Update positions
    pq->positions[pq->heap[i].vertex] = i;
    pq->positions[pq->heap[j].vertex] = j;
}

// Maintain heap property by moving a node upward
static void heapify_up(PriorityQueue* pq, int i) {
    while (i > 0 && pq->heap[i].distance < pq->heap[parent(i)].distance) {
        pq_swap(pq, i, parent(i));
        i = parent(i);
    }
}

// Maintain heap property by moving a node downward
static void heapify_down(PriorityQueue* pq, int i) {
    int smallest = i;
    int left = left_child(i);
    int right = right_child(i);
    
    if (left < pq->size && pq->heap[left].distance < pq->heap[smallest].distance) {
        smallest = left;
    }
    
    if (right < pq->size && pq->heap[right].distance < pq->heap[smallest].distance) {
        smallest = right;
    }
    
    if (smallest != i) {
        pq_swap(pq, i, smallest);
        heapify_down(pq, smallest);
    }
}

// Insert a vertex with its distance into the priority queue
void pq_insert(PriorityQueue* pq, int vertex, int distance, int x, int y) {
    if (pq->size >= pq->capacity) {
        // Queue is full
        return;
    }
    
    // Create new node
    int i = pq->size;
    pq->heap[i].vertex = vertex;
    pq->heap[i].x = x;
    pq->heap[i].y = y;
    pq->heap[i].distance = distance;
    pq->positions[vertex] = i;
    pq->size++;
    
    // Fix the heap property
    heapify_up(pq, i);
}

// Extract the vertex with minimum distance
int pq_extract_min(PriorityQueue* pq) {
    if (pq_is_empty(pq)) {
        return -1; // Error: queue is empty
    }
    
    int min_vertex = pq->heap[0].vertex;
    
    // Replace root with last element
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->positions[pq->heap[0].vertex] = 0;
    
    // Mark the extracted vertex as not in heap
    pq->positions[min_vertex] = -1;
    
    // Reduce size and fix heap
    pq->size--;
    heapify_down(pq, 0);
    
    return min_vertex;
}

// Check if a vertex is in the priority queue
int pq_contains(PriorityQueue* pq, int vertex) {
    return (vertex >= 0 && vertex < pq->capacity) ? (pq->positions[vertex] != -1) : 0;
}

// Update (decrease) the distance of a vertex in the queue
void pq_decrease_key(PriorityQueue* pq, int vertex, int new_distance) {
    int i = pq->positions[vertex];
    
    if (i == -1) {
        // Vertex not in queue
        return;
    }
    
    // Update distance only if it's smaller
    if (new_distance < pq->heap[i].distance) {
        pq->heap[i].distance = new_distance;
        heapify_up(pq, i);
    }
}

// Get the current distance of a vertex in the queue
int pq_get_distance(PriorityQueue* pq, int vertex) {
    int i = pq->positions[vertex];
    
    if (i == -1) {
        // Vertex not in queue
        return INT_MAX;
    }
    
    return pq->heap[i].distance;
}