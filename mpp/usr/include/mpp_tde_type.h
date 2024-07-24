#ifndef __MPP_TDE_TYPE_H__
#define __MPP_TDE_TYPE_H__

#include "mpp_type.h"
#include "mpp_frame.h"
#include "es_mpp_video.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef enum TdeNnMode {
    TDE_NN_MODE_MIN_MAX, /* MIN-MAX mode */
    TDE_NN_MODE_Z_SCORE  /* Z-Score mode */
} TdeNnMode;

typedef enum TdeUsage {
    /* Rotation */
    TDE_USAGE_RORATION_MASK = 0x3f, /* Rotation mask */
    TDE_USAGE_ROT_90 = 1 << 0,      /* Clockwise rotate 90 */
    TDE_USAGE_ROT_180 = 1 << 1,     /* Clockwise rotate 180 */
    TDE_USAGE_ROT_270 = 1 << 2,     /* Clockwise rotate 270 */
    TDE_USAGE_FLIP_H = 1 << 3,      /* Flip horizontal */
    TDE_USAGE_FLIP_V = 1 << 4,      /* Flip vertical */
    TDE_USAGE_FLIP_H_V = 1 << 5,    /* Flip horizontal and vertical, equal to rotate 180 */

    /* Alpha Blend */
    TDE_USAGE_BLEND_MASK = 0x1ffc0,     /* Alpha blend mask */
    TDE_USAGE_BLEND_SRC = 1 << 6,       /* Porter-duff "SRC" */
    TDE_USAGE_BLEND_DST = 1 << 7,       /* Porter-duff "DST" */
    TDE_USAGE_BLEND_SRC_OVER = 1 << 8,  /* Porter-duff "SRC over DST" */
    TDE_USAGE_BLEND_DST_OVER = 1 << 9,  /* Porter-duff "DST over SRC" */
    TDE_USAGE_BLEND_SRC_IN = 1 << 10,   /* Porter-duff "SRC in DST" */
    TDE_USAGE_BLEND_DST_IN = 1 << 11,   /* Porter-duff "DST in SRC" */
    TDE_USAGE_BLEND_SRC_OUT = 1 << 12,  /* Porter-duff "SRC out DST" */
    TDE_USAGE_BLEND_DST_OUT = 1 << 13,  /* Porter-duff "DST out SRC" */
    TDE_USAGE_BLEND_SRC_ATOP = 1 << 14, /* Porter-duff "SRC ATOP" */
    TDE_USAGE_BLEND_DST_ATOP = 1 << 15, /* Porter-duff "DST ATOP" */
    TDE_USAGE_BLEND_XOR = 1 << 16,      /* XOR */

    /* Colorkey */
    TDE_USAGE_COLORKEY_MASK = 0x60000,     /* Colorkey mask */
    TDE_USAGE_COLORKEY_NORMAL = 1 << 17,   /* Normal */
    TDE_USAGE_COLORKEY_INVERTED = 1 << 18, /* Inverted */

    TDE_USAGE_SYNC = 1 << 19,
    TDE_USAGE_CROP = 1 << 20, /* Unused */
    TDE_USAGE_COLOR_FILL = 1 << 21,
    TDE_USAGE_COLOR_PALETTE = 1 << 22,
    TDE_USAGE_NN_QUANTIZE = 1 << 23,
    TDE_USAGE_ROP = 1 << 24,
    TDE_USAGE_ALPHA_BLEND_PRE_MUL = 1 << 25,
    TDE_USAGE_ASYNC = 1 << 26,
    TDE_USAGE_MOSAIC = 1 << 27,
    TDE_USAGE_OSD = 1 << 28,
    TDE_USAGE_PRE_INTR = 1 << 29,
    TDE_USAGE_ALPHA_BIT_MAP = 1 << 30,
} TdeUsage;

typedef enum TDE_WORK_MODE_E {
    TDE_WORKMODE_INDEPENDENT_0, /* Core 0 */
    TDE_WORKMODE_INDEPENDENT_1, /* Core 1 */
    TDE_WORKMODE_COMBINED,      /* Combined mode */
} TdeWorkMode;

/* Float32 format to 4 bytes, NN paramter */
typedef struct TdeRgb {
    ES_U32 r; /* R channel */
    ES_U32 g; /* G channel */
    ES_U32 b; /* B channel */
} TdeRgb;

typedef struct TdeNnParam {
    TdeNnMode nn_mode;
    TdeRgb min_value;
    TdeRgb min_max_reciprocal;
    TdeRgb std_reciprocal;
    TdeRgb mean_value;
    ES_U32 step_reciprocal;
} TdeNnParam;

typedef struct TdeRectInfo {
    RECT_S rect;      /* Rectangle definition */
    ES_U32 color;     /* Rectangle ARGB color */
    ES_S32 thickness; /* The thickness of lines that make up the rectangle. */
} TdeRectInfo;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
