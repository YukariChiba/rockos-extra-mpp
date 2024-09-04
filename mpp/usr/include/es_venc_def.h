#ifndef __ES_VENC_DEF_H__
#define __ES_VENC_DEF_H__

#include "es_mpp_video.h"

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
    VENC_GOPMODE_DUALREF,     /* DUALREF */
    VENC_GOPMODE_SMARTREF,    /* SMARTREF */
    VENC_GOPMODE_ADVSMARTREF, /* ADVSMARTREF */
    VENC_GOPMODE_BIPREDB,     /* BIPREDB: P can only ref one */
    VENC_GOPMODE_LOWDELAYB,   /* LOWDELAYB */
    VENC_GOPMODE_BUTT,
} VENC_GOP_MODE_E;

typedef enum MppEncSeiMode_e {
    MPP_ENC_SEI_MODE_DISABLE,                /* default mode, SEI writing is disabled */
    MPP_ENC_SEI_MODE_ONE_SEQ,                /* one sequence has only one SEI */
    MPP_ENC_SEI_MODE_ONE_FRAME               /* one frame may have one SEI, if SEI info has changed */
} MppEncSeiMode;

typedef struct MppEncUserData_t {
    ES_U32 len;
    void *pdata;
} MppEncUserData;

typedef struct MppEncUserDataFull_t {
    ES_U32 len;
    ES_CHAR uuid[20];
    void *pdata;
} MppEncUserDataFull;

typedef struct MppEncUserDataSet_t {
    ES_U32 count;
    MppEncUserDataFull *datas;
} MppEncUserDataSet;

#define ES_VENC_MAX_ROI_NUM 8

/* the attribute of the roi */
typedef struct esVENC_ROI_ATTR_S {
    ES_BOOL bEnable; /* RW; Range:[0, 1]; Whether to enable this ROI */
    ES_BOOL bAbsQP;  /* RW; Range:[0, 1]; QP mode of an ROI.ES_FALSE: relative QP.ES_TURE: absolute QP.*/
    ES_S32 QP;       /* RW; Range:[-51, 51]; QP value,only relative mode can QP value less than 0. */
    RECT_S rect;     /* RW; Region of an ROI*/
} VENC_ROI_ATTR_S;

typedef struct esVENC_JPEG_ROI_INFO_S {
    ES_U32 rectLeft;
    ES_U32 rectTop;
    ES_U32 rectWidth;
    ES_U32 rectHeight;
} VENC_JPEG_ROI_INFO_S;

#define ES_JPEG_ROI_RECT_NUM 32
typedef struct esVENC_JPEG_ROI_ATTR_S {
    VENC_JPEG_ROI_INFO_S ROIMap[ES_JPEG_ROI_RECT_NUM]; /* Region of non ROI*/
    ES_U32 ROIRectNum;                                 /* ROI region number*/
    ES_U8 nonROILumaFilter[64];                        /* non ROI region quantization tables for luma filter. */
    ES_U8 nonROIChromaFilter[64];                      /* non ROI region quantization tables for chroma filter. */
    ES_S32 nonROILevel;                                /* RW; Range:[0, 9]; non ROI region qLevel. */
} VENC_JPEG_ROI_ATTR_S;

#endif
