#ifndef __ES_COMM_VIDEO_H__
#define __ES_COMM_VIDEO_H__

#include "mpp_type.h"

typedef struct esRECT_S {
    ES_S32 x;
    ES_S32 y;
    ES_S32 width;
    ES_S32 height;
} RECT_S;

typedef enum esROTATION_E {
    ROTATION_0 = 0,
    ROTATION_FLIP_H = 0x01,
    ROTATION_FLIP_V = 0x02,
    ROTATION_180 = 0x03,
    ROTATION_90 = 0x04,
    ROTATION_270 = 0x07,
    ROTATION_BUTT
} ROTATION_E;

#endif
