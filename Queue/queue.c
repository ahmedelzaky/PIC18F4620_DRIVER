/* 
 * File:   queue.c
 * Author: zekwa
 *
 * Created on July 15, 2024, 5:16 PM
 */


#include "queue.h"

Std_ReturnType queueInit(queue_t* _queue) {
    Std_ReturnType ret = E_OK;
    if (NULL == _queue) {
        ret = E_NOT_OK;
    } else {
        _queue->front = -1;
        _queue->rear = -1;
    }
    return ret;
}

bool isQueueFull(queue_t* _queue) {
    return ((_queue->rear + 1) % QUEUE_MAX_SIZE) == _queue->front;
}

bool isQueueEmpty(queue_t* _queue) {
    return _queue->front == -1;
}

bool enqueue(queue_t* _queue, uint8_t data) {

    if (isQueueFull(_queue)) {
        return false;
    }

    if (_queue->front == -1) {
        _queue->front = 0;
    }

    _queue->rear = (_queue->rear + 1) % QUEUE_MAX_SIZE;
    _queue->data[_queue->rear] = data;

    return true;
}

bool dequeue(queue_t* _queue, uint8_t * _data) {
    if (isQueueEmpty(_queue)) {
        return false;
    }
    uint8_t data = _queue->data[_queue->front];
    if (_queue->front == _queue->rear) {
        _queue->front = _queue->rear = -1;
    } else {
        _queue->front = (_queue->front + 1) % QUEUE_MAX_SIZE;
    }

    * _data = data;
    return true;
}

