/* 
 * File:   queue.h
 * Author: zekwa
 *
 * Created on July 15, 2024, 5:16 PM
 */

#ifndef QUEUE_H
#define	QUEUE_H
#include <stdbool.h>
#include <stdint.h>
#include "../MCAL_Layer/mcal_std_types.h"

#define QUEUE_MAX_SIZE 64

typedef struct {
    uint8_t data[QUEUE_MAX_SIZE];
    int8_t front;
    int8_t rear;
} queue_t;

Std_ReturnType queueInit(queue_t* _queue);
bool enqueue(queue_t* _queue, uint8_t data);
bool dequeue(queue_t* _queue, uint8_t * _data);
bool isQueueFull(queue_t* _queue);
bool isQueueEmpty(queue_t* _queue);


#endif	/* QUEUE_H */

