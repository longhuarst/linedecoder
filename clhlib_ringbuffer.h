//
// Created by coocx on 18-12-20.
//

#ifndef LINEDECODER_CLHLIB_RINGBUFFER_H
#define LINEDECODER_CLHLIB_RINGBUFFER_H



#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define clhlib_ringbuffer(type) \
    typedef struct clhlib_ringbuffer_##type##_type{ \
        type *pBuffer; \
        int32_t wridx; \
        int32_t rdidx; \
        int32_t length; \
        int32_t size; \
    }clhlib_ringbuffer_##type##_type; \
    \
    bool clhlib_ringbuffer_##type##_init(clhlib_ringbuffer_##type##_type *rb, int32_t size) { \
        if (rb == NULL){ \
            rb = (clhlib_ringbuffer_##type##_type *) malloc(sizeof(clhlib_ringbuffer_##type##_type)); \
            if (rb == NULL) \
                return false; \
        } \
        rb->size = size; \
        if (size <= 0){ \
            return false; \
        } \
        rb->length = 0; \
        rb->wridx = 0; \
        rb->rdidx = 0; \
        rb->pBuffer = ( type *)malloc(sizeof( type ) * rb->size); \
        if (rb->pBuffer == NULL) \
            return false; \
    } \
    \
    void clhlib_ringbuffer_##type##_delete(clhlib_ringbuffer_##type##_type *rb){ \
        if (rb == NULL) \
            return; \
        rb->length = 0; \
        rb->size = 0; \
        rb->wridx = 0; \
        rb->rdidx = 0; \
        free(rb->pBuffer); \
    } \
    \
    bool clhlib_ringbuffer_##type##_is_empty(clhlib_ringbuffer_##type##_type *rb){ \
        if (rb == NULL) \
            return false; \
        if (rb->length == 0) \
            return true; \
        return false; \
    } \
    \
    bool clhlib_ringbuffer_##type##_is_full(clhlib_ringbuffer_##type##_type *rb){ \
        if (rb == NULL) \
            return false; \
        if (rb->length >= (rb->size-1)) \
            return true; \
        return false; \
    } \
    \
    int32_t clhlib_ringbuffer_##type##_length(clhlib_ringbuffer_##type##_type *rb){ \
        if (rb == NULL) \
            return 0; \
            return 0; \
        return rb->length; \
    } \
    \
    int32_t clhlib_ringbuffer_##type##_push_back(clhlib_ringbuffer_##type##_type *rb, type data){ \
        int32_t delete_ = 0; \
        if (rb == NULL) \
            return 0; \
        if (clhlib_ringbuffer_##type##_is_full(rb)) { \
            rb->rdidx++; \
            rb->rdidx%=rb->size; \
            delete_ = 1; \
        } \
        memcpy(&rb->pBuffer[rb->wridx],&data,sizeof(type)); \
        rb->wridx++; \
        rb->wridx%=rb->size; \
        return delete_; \
    } \
    \
    type clhlib_ringbuffer_##type##_pop_front(clhlib_ringbuffer_##type##_type *rb, bool *success){ \
        if (rb == NULL) \
            return 0; \
        int32_t idx = rb->rdidx; \
        if (clhlib_ringbuffer_##type##_is_empty(rb)) { \
            *success = false; \
            return rb->pBuffer[0]; \
        } \
        *success = true; \
        rb->rdidx++; \
        rb->rdidx %= rb->size; \
        return rb->pBuffer[idx]; \
    } \
    \
    int32_t clhlib_ringbuffer_##type##_push_backs(clhlib_ringbuffer_##type##_type *rb, type *data, int32_t size){ \
        int32_t i = 0; \
        if (rb == NULL) \
            return 0; \
        for (i=0; i<size;++i){ \
            if (clhlib_ringbuffer_##type##_push_back(rb,data[i])){ \
                return i; \
            } \
        } \
        return i; \
    } \
    \
    int32_t clhlib_ringbuffer_##type##_pop_fronts(clhlib_ringbuffer_##type##_type *rb, type *data, int32_t size){ \
        int32_t i=0; \
        bool success = false; \
        if (rb == NULL) \
            return 0; \
        for (i=0; i<size; ++i){ \
            data[i] = clhlib_ringbuffer_##type##_pop_front(rb,&success); \
            if (success == false){ \
                return i; \
            } \
        } \
        return i;\
    } \
    \



#endif //LINEDECODER_CLHLIB_RINGBUFFER_H
