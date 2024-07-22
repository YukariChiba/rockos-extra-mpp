#ifndef __ES_VENC_DEF_H__
#define __ES_VENC_DEF_H__

/* the profile of h264e */
typedef enum esPROFILE_H264 {
    PROFILE_H264_BASELINE,
    PROFILE_H264_MAIN,
    PROFILE_H264_HIGH,
    PROFILE_H264_HIGH10,
} PROFILE_H264_E;

/* the profile of h265e */
typedef enum esPROFILE_H265 {
    PROFILE_H265_MAIN,
    PROFILE_H265_MAIN10,
    PROFILE_H265_MAIN_STILL_PICTURE,
} PROFILE_H265_E;

typedef enum esHEVC_TIER {
    HEVC_MAIN_TIER = 0,
    HEVC_HIGH_TIER,
} HEVC_TIER;

typedef enum esVENC_BITDEPTH_E {
    BIT_DEPTH_8BIT = 8,
    BIT_DEPTH_10BIT = 10,
} BIT_DEPTH_E;

typedef enum {
    ES_LEVEL_UNKNOWN = 0,
    ES_HEVC_LEVEL_1,
    ES_HEVC_LEVEL_2,
    ES_HEVC_LEVEL_2_1,
    ES_HEVC_LEVEL_3,
    ES_HEVC_LEVEL_3_1,
    ES_HEVC_LEVEL_4,
    ES_HEVC_LEVEL_4_1,
    ES_HEVC_LEVEL_5,
    ES_HEVC_LEVEL_5_1,
    ES_HEVC_LEVEL_5_2,
    ES_HEVC_LEVEL_6,
    ES_HEVC_LEVEL_6_1,
    ES_HEVC_LEVEL_6_2,

    /* H264 Defination*/
    ES_H264_LEVEL_1 = 100,
    ES_H264_LEVEL_1_b,
    ES_H264_LEVEL_1_1,
    ES_H264_LEVEL_1_2,
    ES_H264_LEVEL_1_3,
    ES_H264_LEVEL_2,
    ES_H264_LEVEL_2_1,
    ES_H264_LEVEL_2_2,
    ES_H264_LEVEL_3,
    ES_H264_LEVEL_3_1,
    ES_H264_LEVEL_3_2,
    ES_H264_LEVEL_4,
    ES_H264_LEVEL_4_1,
    ES_H264_LEVEL_4_2,
    ES_H264_LEVEL_5,
    ES_H264_LEVEL_5_1,
    ES_H264_LEVEL_5_2,
    ES_H264_LEVEL_6,
    ES_H264_LEVEL_6_1,
    ES_H264_LEVEL_6_2,
} ESMppEncLevel;

/* the GOP mode */
typedef enum esVENC_GOP_MODE_E {
    VENC_GOPMODE_NORMALP = 0, /* NORMALP */
    VENC_GOPMODE_DUALREF,       /* DUALREF */
    VENC_GOPMODE_SMARTREF,      /* SMARTREF */
    VENC_GOPMODE_ADVSMARTREF,   /* ADVSMARTREF */
    VENC_GOPMODE_BIPREDB,     /* BIPREDB: P can only ref one */
    VENC_GOPMODE_LOWDELAYB,   /* LOWDELAYB */
    VENC_GOPMODE_BUTT,
} VENC_GOP_MODE_E;

#endif
