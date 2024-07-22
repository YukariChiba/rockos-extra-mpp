/*
 * Copyright © 2023 ESWIN.  All rights reserved.
 * Beijing ESWIN Computing Technology Co., Ltd and its affiliated companies ("ESWIN") retain
 * all intellectual property and proprietary rights in and to this software.Except as expressly
 * authorized by ESWIN, no part of the software may be released, copied, distributed,reproduced,
 * modified, adapted, translated, or created derivative work of, in whole or in part.
 * @Description: Common defination of rate control encoding
 * @Author: ESWIN
 */

#ifndef __ES_COMM_RC_H__
#define __ES_COMM_RC_H__

#include "mpp_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef ES_U32 ES_FR32;
#define FRAME_RATE_TO_FR32(FrameRateNum, FrameRateDenom) ((FrameRateNum) & 0xFFFF) | (((FrameRateDenom) & 0xFFFF) << 16)
#define FR32_TO_FRAME_RATE(fr32, rate_num, rate_denom) \
    rate_num = ((fr32) & 0xFFFF);                      \
    rate_num = (0 != (rate_num)) ? (rate_num) : 30;    \
    rate_denom = ((fr32) & 0xFFFF0000) >> 16;          \
    rate_denom = (0 != (rate_denom)) ? (rate_denom) : 1;

/* rc mode */
typedef enum esVENC_RC_MODE_E {
    VENC_RC_MODE_H264CBR = 1,
    VENC_RC_MODE_H264VBR,
    VENC_RC_MODE_H264AVBR, /* Not support */
    VENC_RC_MODE_H264QVBR, /* Not support */
    VENC_RC_MODE_H264CVBR, /* Not support */
    VENC_RC_MODE_H264FIXQP,
    VENC_RC_MODE_H264QPMAP,

    VENC_RC_MODE_MJPEGCBR,
    VENC_RC_MODE_MJPEGVBR,
    VENC_RC_MODE_MJPEGFIXQP,

    VENC_RC_MODE_H265CBR,
    VENC_RC_MODE_H265VBR,
    VENC_RC_MODE_H265AVBR, /* Not support */
    VENC_RC_MODE_H265QVBR, /* Not support */
    VENC_RC_MODE_H265CVBR, /* Not support */
    VENC_RC_MODE_H265FIXQP,
    VENC_RC_MODE_H265QPMAP,

    VENC_RC_MODE_BUTT,
} VENC_RC_MODE_E;

/* the attribute of h264e fixQP */
typedef struct esVENC_H264_FIXQP_S {
    ES_S32 change;
    ES_U32 GOP;           /* RW; Range:[1, 65536]; the interval of ISLICE. */
    ES_U32 statTime;      /* Unused, placeholder */
    ES_FR32 dstFrameRate; /* RW; Range:[0.015625, 240]; the target frame rate of the venc chnnel */
    ES_U32 IQP;           /* RW; Range:[0, 51]; QP of the I frame */
    ES_U32 PQP;           /* RW; Range:[0, 51]; QP of the P frame */
    ES_U32 BQP;           /* RW; Range:[0, 51]; QP of the B frame */
} VENC_H264_FIXQP_S;

/* the attribute of h264e CBR */
typedef struct esVENC_H264_CBR_S {
    ES_S32 change;
    ES_U32 GOP;           /* RW; Range:[1, 65536]; the interval of I Frame. */
    ES_U32 statTime;      /* RW; Range:[1, 60]; the rate statistic time, the unit is senconds(s) */
    ES_FR32 dstFrameRate; /* RW; Range:[0.015625, 240]; the target frame rate of the venc chnnel */
    ES_U32 bitRate;       /* RW; Range:[10, 800000]; average bitrate, the unit is kbps. */
    ES_U32 cpbSize;       /* RW; Range:[10, 800000]; the cpb size, the unit is kbps, Suggest [1.25 * bitRate] */
} VENC_H264_CBR_S;

/* the attribute of h264e VBR */
typedef struct esVENC_H264_VBR_S {
    ES_S32 change;
    ES_U32 GOP;           /* RW; Range:[1, 65536]; the interval of ISLICE. */
    ES_U32 statTime;      /* RW; Range:[1, 60]; the rate statistic time, the unit is senconds(s) */
    ES_FR32 dstFrameRate; /* RW; Range:[0.015625, 240]; the target frame rate of the venc chnnel */
    ES_U32 maxBitRate;    /* RW; Range:[10, 800000]; the max bitrate */
} VENC_H264_VBR_S;

/* the attribute of h264e CVBR */
typedef struct esVENC_H264_CVBR_S {
    ES_S32 change;
    ES_U32 GOP;           /* RW; Range:[1, 65536]; the interval of ISLICE. */
    ES_U32 statTime;      /* RW; Range:[1, 60]; the rate statistic time, the unit is senconds(s) */
    ES_FR32 dstFrameRate; /* RW; Range:[0.015625, 240]; the target frame rate of the venc chnnel */
    ES_U32 maxBitRate;    /* RW; Range:[2, 614400]; the max bitrate */

    ES_U32 shortTermStatTime;  /* RW; Range:[1, 120]; the long-term rate statistic time, the unit is second (s)*/
    ES_U32 longTermStatTime;   /* RW; Range:[1, 1440]; the long-term rate statistic time, the unit is
                                      longTermStatTimeUnit*/
    ES_U32 longTermMaxBitrate; /* RW; Range:[2, 614400]; the long-term target max bitrate, can not be larger than
                                      maxBitRate,the unit is kbps */
    ES_U32 longTermMinBitrate; /* RW; Range:[0, 614400]; the long-term target min bitrate,  can not be larger than
                                      longTermMaxBitrate,the unit is kbps */

} VENC_H264_CVBR_S;

/* the attribute of h264e AVBR */
typedef struct esVENC_H264_AVBR_S {
    ES_S32 change;
    ES_U32 GOP;           /* RW; Range:[1, 65536]; the interval of ISLICE. */
    ES_U32 statTime;      /* RW; Range:[1, 60]; the rate statistic time, the unit is senconds(s) */
    ES_FR32 dstFrameRate; /* RW; Range:[0.015625, 240]; the target frame rate of the venc chnnel */
    ES_U32 maxBitRate;    /* RW; Range:[2, 614400]; the max bitrate */
} VENC_H264_AVBR_S;

/* the attribute of h264e QPmap */
typedef struct esVENC_H264_QPMAP_S {
    ES_S32 change;
    ES_U32 GOP;           /* RW; Range:[1, 65536]; the interval of ISLICE. */
    ES_U32 statTime;      /* RW; Range:[1, 60]; the rate statistic time, the unit is senconds(s) */
    ES_FR32 dstFrameRate; /* RW; Range:[0.015625, 240]; the target frame rate of the venc chnnel */
} VENC_H264_QPMAP_S;

/* the attribute of h264e QVBR */
typedef struct esVENC_H264_QVBR_S {
    ES_S32 change;
    ES_U32 GOP;           /* RW; Range:[1, 65536]; the interval of ISLICE. */
    ES_U32 statTime;      /* RW; Range:[1, 60]; the rate statistic time, the unit is senconds(s) */
    ES_FR32 dstFrameRate; /* RW; Range:[0.015625, 240]; the target frame rate of the venc chnnel */
    ES_U32 targetBitRate; /* RW; Range:[2, 614400]; the target bitrate */
} VENC_H264_QVBR_S;

typedef struct esVENC_H264_CBR_S VENC_H265_CBR_S;
typedef struct esVENC_H264_VBR_S VENC_H265_VBR_S;
typedef struct esVENC_H264_AVBR_S VENC_H265_AVBR_S;
typedef struct esVENC_H264_FIXQP_S VENC_H265_FIXQP_S;
typedef struct esVENC_H264_QVBR_S VENC_H265_QVBR_S;
typedef struct esVENC_H264_CVBR_S VENC_H265_CVBR_S;
typedef struct esVENC_H264_QPMAP_S VENC_H265_QPMAP_S;

typedef struct esVENC_PARAM_H264_CBR_S VENC_PARAM_H265_CBR_S;
typedef struct esVENC_PARAM_H264_VBR_S VENC_PARAM_H265_VBR_S;

/* the attribute of mjpege fixQP */
typedef struct esVENC_MJPEG_FIXQP_S {
    ES_S32 change;
    ES_U32 GOP;           /* unused. */
    ES_U32 statTime;      /* unused */
    ES_FR32 dstFrameRate; /* RW; Range:[0.015625, 240]; the target frame rate of the venc chnnel */
    ES_U32 qFactor;       /* RW; Range:[1,99];image quality. */
} VENC_MJPEG_FIXQP_S;

/* the attribute of mjpege CBR */
typedef struct esVENC_MJPEG_CBR_S {
    ES_S32 change;
    ES_U32 GOP;           /* unused. */
    ES_U32 statTime;      /* RW; Range:[1, 60]; the rate statistic time, the unit is senconds(s) */
    ES_FR32 dstFrameRate; /* RW; Range:[0.015625, 240]; the target frame rate of the venc chnnel */
    ES_U32 bitRate;       /* RW; Range:[10, 800000]; average bitrate, the unit is kbps. */
} VENC_MJPEG_CBR_S;

/* the attribute of mjpege VBR */
typedef struct esVENC_MJPEG_VBR_S {
    ES_S32 change;
    ES_U32 GOP;           /* unused. */
    ES_U32 statTime;      /* RW; Range:[1, 60]; the rate statistic time, the unit is senconds(s) */
    ES_FR32 dstFrameRate; /* RW; Range:[0.015625, 240]; the target frame rate of the venc chnnel */
    ES_U32 maxBitRate;    /* RW; Range:[10, 800000]; the max bitrate */
} VENC_MJPEG_VBR_S;

typedef struct esRC_PUB_S {
    ES_U32 change;
    ES_U32 GOP;
    ES_U32 statTime;      /* RW; Range:[1, 60]; the rate statistic time, the unit is senconds(s) */
    ES_FR32 dstFrameRate; /* RW; Range:[0.015625, 240]; the target frame rate of the venc chnnel */
} RC_PUB_S;

/* the attribute of rc */
typedef struct esVENC_RC_ATTR_S {
    VENC_RC_MODE_E rcMode; /* RW; the type of rc*/
    union {
        ES_S32 change; /* for macro ENTRY */
        RC_PUB_S pub;

        VENC_H264_CBR_S h264CBR;
        VENC_H264_VBR_S h264VBR;
        VENC_H264_AVBR_S h264AVBR;
        VENC_H264_QVBR_S h264QVBR;
        VENC_H264_CVBR_S h264CVBR;
        VENC_H264_FIXQP_S h264FixQP;
        VENC_H264_QPMAP_S h264QPMap;

        VENC_MJPEG_CBR_S mjpegCBR;
        VENC_MJPEG_VBR_S mjpegVBR;
        VENC_MJPEG_FIXQP_S mjpegFixQP;

        VENC_H265_CBR_S h265CBR;
        VENC_H265_VBR_S h265VBR;
        VENC_H265_AVBR_S h265AVBR;
        VENC_H265_QVBR_S h265QVBR;
        VENC_H265_CVBR_S h265CVBR;
        VENC_H265_FIXQP_S h265FixQP;
        VENC_H265_QPMAP_S h265QPMap;
    };
} VENC_RC_ATTR_S;

/* the super frame mode */
typedef enum esRC_SUPERFRM_MODE_E {
    SUPERFRM_NONE = 0, /* sdk don't care super frame */
    SUPERFRM_DISCARD,  /* the super frame is discarded */
    SUPERFRM_REENCODE, /* the super frame is re-encode */
    SUPERFRM_BUTT
} VENC_SUPERFRM_MODE_E;

/* the type of qpmap block unit */
typedef enum esQPMAP_META_TYPE_E {
    QPMAP_META_TYPE_SKIP,
    QPMAP_META_TYPE_IPCM,
} VENC_QPMAP_META_TYPE_E;

/* the block unit size */
typedef enum esVENC_QPMAP_BLOCK_UNIT_E {
    /**
     * Block Unit Size Of QpMap:
     * h265: support 64x64、32x32、16x16
     * h264: support 64x64、32x32、16x16
     *******************************
     * Block Unit Size Of SkipMap:
     * h265: support 64x64、32x32
     * h264: support 64x64、32x32、16x16
     *******************************
     * Block Unit Size Of IpcmMap:
     * h265: support 64x64
     * h264: support 16x16
     */
    VENC_QPMAP_BLOCK_UNIT_64x64 = 0,
    VENC_QPMAP_BLOCK_UNIT_32x32 = 1,
    VENC_QPMAP_BLOCK_UNIT_16x16 = 2,
    VENC_QPMAP_BLOCK_UNIT_BUTT,
} ES_VENC_QPMAP_BLOCK_UNIT_E;

/* the attribute of qpmap */
typedef struct esVENC_QPMAP_META_S {
    ES_VENC_QPMAP_BLOCK_UNIT_E qpMapBlockUnit;   /* 0: 64x64, 1: 32x32, 2: 16x16 */
    ES_BOOL bMetaEnable;                         /* enable ipcm/skip data info */
    VENC_QPMAP_META_TYPE_E metaType;             /* ipcmMap; skipMap, default: skipMap */
    ES_VENC_QPMAP_BLOCK_UNIT_E metaMapBlockUnit; /* skipMap: 0: 64x64, 1: 32x32, 2: 16x16 ; ipcm: 2: 16x16 */
} VENC_QPMAP_META_S;

/* the param of h264e CBR */
typedef struct esVENC_PARAM_H264_CBR_S {
    ES_U32 change;
    ES_U32 IProp;                /* RW; Range:[50, 100];I frame bits percent of bitrate in static scene. Default [80]*/
    ES_U32 maxQP;                /* RW; Range:[0, 51]; the max QP value. Default [40]*/
    ES_U32 minQP;                /* RW; Range:[0, 51]; the min QP value,can not be larger than maxQP. Default [20]*/
    ES_U32 maxIQP;               /* RW; Range:[0, 51]; max QP for i frame. Default [35] */
    ES_U32 minIQP;               /* RW; Range:[0, 51]; min QP for i frame,can not be larger than maxIQP. Default [20]*/
    ES_S32 maxReEncodeTimes;     /* RW; Range:[0, 3]; Range:max number of re-encode times.*/
    ES_BOOL bQPMapEn;            /* RW; Range:[0, 1]; enable QPmap.*/
    VENC_QPMAP_META_S qpMapMeta; /* RW; QPmap meta related info.*/
} VENC_PARAM_H264_CBR_S;

/* the param of h264e VBR */
typedef struct esVENC_PARAM_H264_VBR_S {
    ES_U32 change;
    ES_U32 IProp;                /* RW; Range:[50, 100];I frame bits percent of bitrate in static scene. Default [80] */
    ES_U32 maxQP;                /* RW; Range:[0, 51]; the max P B QP. Default [51] */
    ES_U32 minQP;                /* RW; Range:[0, 51]; the min P B QP,can not be larger than maxQP. Default [24] */
    ES_U32 maxIQP;               /* RW; Range:[0, 51]; the max I QP. Default [51] */
    ES_U32 minIQP;               /* RW; Range:[0, 51]; the min I QP ,can not be larger than maxIQP. Default [24] */
    ES_S32 maxReEncodeTimes;     /* RW; Range:[0, 3]; max number of re-encode times */
    ES_BOOL bQPMapEn;            /* RW; Range:[0, 1]; enable QPmap */
    VENC_QPMAP_META_S qpMapMeta; /* RW; QPmap meta related info */
    ES_S32 changePos;            /* RW; Range:[50, 100]; Indicates the ratio of the current bit rate to the maximum
                                        bit rate when the QP value starts to be adjusted. Default [90]*/
} VENC_PARAM_H264_VBR_S;

/* the param of h264e AVBR */
typedef struct esVENC_PARAM_H264_AVBR_S {
    ES_U32 change;
    ES_S32 changePos; /* RW; Range:[50, 100]; Indicates the ratio of the current bit rate to the maximum
                             bit rate when the QP value starts to be adjusted */
    ES_U32 minIprop;  /* RW; Range:[1, 100] ; the min ratio of i frame and p frame,can not be smaller than minIprop */
    ES_U32 maxIprop;  /* RW; Range:[1, 100] ; the max ratio of i frame and p frame */

    ES_S32 maxReEncodeTimes;     /* RW; Range:[0, 3]; max number of re-encode times */
    ES_BOOL bQPMapEn;            /* RW; Range:[0, 1]; enable QPmap */
    VENC_QPMAP_META_S qpMapMeta; /* RW; QPmap meta related info */

    ES_S32 minStillPercent; /* RW; Range:[5, 100]; the min percent of target bitrate for still scene */
    ES_U32 maxStillQP;      /* RW; Range:[0, 51]; the max QP value of I frame for still scene,
                                      can not be smaller than minIQP and can not be larger than su32MaxIQP */
    ES_U32 minStillPSNR;    /* RW; reserved,Invalid member currently */

    ES_U32 maxQP;      /* RW; Range:[0, 51]; the max P B QP */
    ES_U32 minQP;      /* RW; Range:[0, 51]; the min P B QP,can not be larger than maxQP */
    ES_U32 maxIQP;     /* RW; Range:[0, 51]; the max I QP */
    ES_U32 minIQP;     /* RW; Range:[0, 51]; the min I QP,can not be larger than maxIQP */
    ES_U32 minQPDelta; /* RW; Range:[0, 4];Difference between FrameLevelMinQP and MinQP, FrameLevelMinQP = MinQP(or
                              MinIQP) + MinQPDelta  */
    ES_U32 motionSensitivity; /* RW; Range:[0, 100]; Motion Sensitivity */
} VENC_PARAM_H264_AVBR_S;

/* the param of h264e QVBR */
typedef struct esVENC_PARAM_H264_QVBR_S {
    ES_U32 change;
    ES_U32 minIprop; /* RW; Range:[1, 100]; the min ratio of i frame and p frame */
    ES_U32 maxIprop; /* RW; Range:[1, 100] ; the max ratio of i frame and p frame,can not be smaller than minIprop */
    ES_U32 maxQP;    /* RW; Range:[0, 51]; the max P B QP */
    ES_U32 minQP;    /* RW; Range:[0, 51]; the min P B QP,can not be larger than maxQP */
    ES_U32 maxIQP;   /* RW; Range:[0, 51]; the max I QP */
    ES_U32 minIQP;   /* RW; Range:[0, 51]; the min I QP,can not be larger than maxIQP */

    ES_S32 bitPercentUL;     /* RW; Range:[30, 180]; Indicate the ratio of bitrate  upper limit */
    ES_S32 bitPercentLL;     /* RW; Range:[30, 180]; Indicate the ratio of bitrate  lower limit, can not be larger than
                                    bitPercentUL */
    ES_S32 psnrFluctuateUL;  /* RW; Range:[18, 40]; Reduce the target bitrate when the value of psnr approch the
                                    upper limit */
    ES_S32 psnrFluctuateLL;  /* RW; Range:[18, 40]; Increase the target bitrate when the value of psnr approch the
                                    lower limit, can not be larger than psnrFluctuateUL */
    ES_S32 maxReEncodeTimes; /* RW; Range:[0, 3];max number of re-encode times [0, 3] */
    ES_BOOL bQPMapEn;        /* RW; Range:[0, 1]; enable QPmap */
    VENC_QPMAP_META_S qpMapMeta; /* RW; QPmap meta related info */
} VENC_PARAM_H264_QVBR_S;

/* the param of h264e CVBR */
typedef struct esVENC_PARAM_H264_CVBR_S {
    ES_U32 minIprop; /* RW; Range:[1, 100] ; the min ratio of i frame and p frame */
    ES_U32 maxIprop; /* RW; Range:[1, 100] ; the max ratio of i frame and p frame,can not be smaller than minIprop */
    ES_U32 maxQP;    /* RW; Range:[0, 51]; the max P B QP */
    ES_U32 minQP;    /* RW; Range:[0, 51]; the min P B QP,can not be larger than maxQP */
    ES_U32 maxIQP;   /* RW; Range:[0, 51]; the max I QP */
    ES_U32 minIQP;   /* RW; Range:[0, 51]; the min I QP,can not be larger than maxIQP */

    ES_U32 minQPDelta;      /* RW; Range:[0, 4];Difference between FrameLevelMinQP and MinQP, FrameLevelMinQP = MinQP(or
                                   MinIQP) + MinQPDelta  */
    ES_U32 maxQPDelta;      /* RW; Range:[0, 4];Difference between FrameLevelMaxQP and MaxQP, FrameLevelMaxQP = MaxQP(or
                                   MaxIQP) - MaxQPDelta  */
    ES_U32 extraBitPercent; /* RW; Range:[0, 1000]; the extra bits that can be allocated when the actual bitrate goes
                                   above the target bitrate*/
    ES_U32
    longTermStatTimeUnit;        /* RW; Range:[1, 1800]; the time unit of LongTermStatTime,, the unit is senconds(s)*/
    ES_S32 maxReEncodeTimes;     /* RW; Range:[0, 3]; max number of re-encode times */
    ES_BOOL bQPMapEn;            /* RW; Range:[0, 1]; enable QPmap.*/
    VENC_QPMAP_META_S qpMapMeta; /* RW; QPmap meta related info */
} VENC_PARAM_H264_CVBR_S;

typedef struct esVENC_PARAM_H264_QPMAP_S {
    ES_U32 change;
    VENC_QPMAP_META_S qpMapMeta; /* RW; QPmap meta related info */
} VENC_PARAM_H264_QPMAP_S;

/* the param of mjpege CBR */
typedef struct esVENC_PARAM_MJPEG_CBR_S {
    ES_U32 change;
    ES_U32 maxQfactor; /* RW; Range:[1, 99]; the max Qfactor value*/
    ES_U32 minQfactor; /* RW; Range:[1, 99]; the min Qfactor value ,can not be larger than maxQfactor */
} VENC_PARAM_MJPEG_CBR_S;

/* the param of mjpege VBR */
typedef struct esVENC_PARAM_MJPEG_VBR_S {
    ES_U32 change;
    ES_S32 changePos;  /* RW; Range:[50, 100]; Indicates the ratio of the current bit rate to the maximum
                                           bit rate when the Qfactor value starts to be adjusted */
    ES_U32 maxQfactor; /* RW; Range:[1, 99]; max image quailty allowed */
    ES_U32 minQfactor; /* RW; Range:[1, 99]; min image quality allowed ,can not be larger than maxQfactor*/
} VENC_PARAM_MJPEG_VBR_S;

/* the param of h265e AVBR */
typedef struct esVENC_PARAM_H265_AVBR_S {
    ES_U32 change;
    ES_S32 changePos;       /* RW; Range:[50, 100];Indicates the ratio of the current bit rate to the maximum
                                   bit rate when the QP value starts to be adjusted */
    ES_S32 minStillPercent; /* RW; Range:[5, 100]; the min percent of target bitrate for still scene */
    ES_U32 maxStillQP;      /* RW; Range:[0, 51]; the max QP value of I frame for still scene,
                                      can not be smaller than minIQP and can not be larger than su32MaxIQP*/
    ES_U32 minStillPSNR;    /* RW; reserved */

    ES_U32 minIprop;   /* RW; [1, 100]; the min ratio of i frame and p frame */
    ES_U32 maxIprop;   /* RW; [1, 100]; the max ratio of i frame and p frame,can not be smaller than minIprop */
    ES_U32 maxQP;      /* RW; Range:[0, 51]; the max P B QP */
    ES_U32 minQP;      /* RW; Range:[1, 51]; the min P B QP,can not be larger than maxQP */
    ES_U32 maxIQP;     /* RW; Range:[0, 51]; the max I QP */
    ES_U32 minIQP;     /* RW; Range:[1, 51]; the min I QP,can not be larger than maxIQP */
    ES_U32 minQPDelta; /* RW; Range:[0, 4];Difference between FrameLevelMinQP and MinQP, FrameLevelMinQP = MinQP(or
                              MinIQP) + MinQPDelta  */
    ES_U32 motionSensitivity;    /* RW; Range:[0, 100]; Motion Sensitivity */
    ES_S32 maxReEncodeTimes;     /* RW; Range:[0, 3]; Range:max number of re-encode times.*/
    ES_BOOL bQPMapEn;            /* RW; Range:[0, 1]; enable QPmap.*/
    VENC_QPMAP_META_S qpMapMeta; /* RW; QPmap meta related info */
} VENC_PARAM_H265_AVBR_S;

/* the param of h265e QVBR */
typedef struct esVENC_PARAM_H265_QVBR_S {
    ES_U32 change;
    ES_U32 minIprop; /* RW; [1, 100]; the min ratio of i frame and p frame */
    ES_U32 maxIprop; /* RW; [1, 100]; the max ratio of i frame and p frame,can not be smaller than minIprop */
    ES_U32 maxQP;    /* RW; Range:[0, 51]; the max P B QP */
    ES_U32 minQP;    /* RW; Range:[0, 51]; the min P B QP,can not be larger than maxQP */
    ES_U32 maxIQP;   /* RW; Range:[0, 51]; the max I QP */
    ES_U32 minIQP;   /* RW; Range:[0, 51]; the min I QP,can not be larger than maxIQP */

    ES_S32 bitPercentUL;     /* RW; Range:[30, 180]; Indicate the ratio of bitrate  upper limit*/
    ES_S32 bitPercentLL;     /* RW; Range:[30, 180]; Indicate the ratio of bitrate  lower limit,can not be larger than
                                    bitPercentUL */
    ES_S32 psnrFluctuateUL;  /* RW; Range:[18, 40]; Reduce the target bitrate when the value of psnr approch the
                                    upper limit */
    ES_S32 psnrFluctuateLL;  /* RW; Range:[18, 40]; Increase the target bitrate when the value of psnr approch the
                                    lower limit, can not be larger than psnrFluctuateUL */
    ES_S32 maxReEncodeTimes; /* RW; [0, 3]; max number of re-encode times [0, 3]*/
    ES_BOOL bQPMapEn;        /* RW; Range:[0, 1]; enable QPmap */
    VENC_QPMAP_META_S qpMapMeta; /* RW; QPmap meta related info */
} VENC_PARAM_H265_QVBR_S;

/* the param of h265e CVBR */
typedef struct esVENC_PARAM_H265_CVBR_S {
    ES_U32 change;
    ES_U32 minIprop;   /* RW; Range:[1, 100] ; the min ratio of i frame and p frame */
    ES_U32 maxIprop;   /* RW; Range:[1, 100] ; the max ratio of i frame and p frame,can not be smaller than minIprop */
    ES_U32 maxQP;      /* RW; Range:[0, 51]; the max P B QP */
    ES_U32 minQP;      /* RW; Range:[0, 51]; the min P B QP,can not be larger than maxQP */
    ES_U32 maxIQP;     /* RW; Range:[0, 51]; the max I QP */
    ES_U32 minIQP;     /* RW; Range:[0, 51]; the min I QP,can not be larger than maxIQP */
    ES_U32 minQPDelta; /* RW; Range:[0, 4]; Difference between FrameLevelMinQP and MinQP, FrameLevelMinQP = MinQP(or
                              MinIQP) + MinQPDelta */
    ES_U32 maxQPDelta; /* RW; Range:[0, 4]; Difference between FrameLevelMaxQP and MaxQP, FrameLevelMaxQP = MaxQP(or
                              MaxIQP) - MaxQPDelta */
    ES_U32 extraBitPercent; /* RW; Range:[0, 1000]; the extra ratio of bitrate that can be allocated when the actual
                                   bitrate goes above the long-term target bitrate */
    ES_U32
    longTermStatTimeUnit;    /* RW; Range:[1, 1800]; the time unit of LongTermStatTime, the unit is senconds(s) */
    ES_S32 maxReEncodeTimes; /* RW; Range:[0, 3]; max number of re-encode times */
    ES_BOOL bQPMapEn;
    VENC_QPMAP_META_S qpMapMeta; /* RW; QPmap meta related info */
} VENC_PARAM_H265_CVBR_S;

/* the param of h265e QPMAP */
typedef struct esVENC_PARAM_H265_QPMAP_S {
    ES_U32 change;
    VENC_QPMAP_META_S qpMapMeta; /* RW; QPmap meta related info */
} VENC_PARAM_H265_QPMAP_S;

/* The param of rc */
typedef struct esVENC_RC_PARAM_S {
    ES_S32 ctbRc;              /* RW; Range:[0,3]; CTB QP adjustment mode for different targets */
    ES_S32 blockRCSize;        /* RW; Range:[0,2];Block size in CTB QP adjustment for Subjective Quality.
                                      h265: 0=64x64, 1=32x32, 2=16x16, default [0], h264: 2=16x16 only */
    ES_U32 rcQpDeltaRange;     /* RW; Range:[0,15];Max absolute value of CU/MB QP delta relative to frame QP in CTB RC,
                                      Default [10] */
    ES_U32 rcBaseMBComplexity; /* RW; Range:[0,31]; MB complexity base in CTB QP adjustment for Subjective Quality.
                                      Default [15] */
    ES_U32 ctbRcRowQpStep;     /* RW; Range:(0, INT_MAX]; The maximum accumulated QP adjustment step per CTB Row allowed
                                      by CTB rate control. Default [4] */

    ES_S32 firstFrameStartQP; /* RW; Range:[-1, 51];Start QP value of the first frame */
    union {
        ES_U32 change;
        VENC_PARAM_H264_CBR_S paramH264CBR;
        VENC_PARAM_H264_VBR_S paramH264VBR;
        VENC_PARAM_H264_AVBR_S paramH264AVBR;
        VENC_PARAM_H264_QVBR_S paramH264QVBR;
        VENC_PARAM_H264_CVBR_S paramH264CVBR;
        VENC_PARAM_H264_QPMAP_S paramH264QPMap;
        VENC_PARAM_H265_CBR_S paramH265CBR;
        VENC_PARAM_H265_VBR_S paramH265VBR;
        VENC_PARAM_H265_AVBR_S paramH265AVBR;
        VENC_PARAM_H265_QVBR_S paramH265QVBR;
        VENC_PARAM_H265_CVBR_S paramH265CVBR;
        VENC_PARAM_H265_QPMAP_S paramH265QPMap;
        VENC_PARAM_MJPEG_CBR_S paramMjpegCBR;
        VENC_PARAM_MJPEG_VBR_S paramMjpegVBR;
    };
} VENC_RC_PARAM_S;

/* the frame lost mode */
typedef enum esVENC_FRAMELOST_MODE_E {
    FRMLOST_NORMAL = 0, /* normal mode */
    FRMLOST_PSKIP,      /* pskip */
    FRMLOST_BUTT,
} VENC_FRAMELOST_MODE_E;

/* The param of the frame lost mode */
typedef struct esVENC_FRAMELOST_S {
    ES_BOOL bFrmLostOpen; /* RW; Range:[0,1];Indicates whether to discard frames to ensure stable bit rate when the
                              instant bit rate is exceeded */
    ES_U32 frmLostBpsThr; /* RW; Range:[64k, 163840k]; the instant bit rate threshold */
    VENC_FRAMELOST_MODE_E frmLostMode; /* RW; frame lost strategy */
    ES_U32 encFrmGaps;                 /* RW; Range:[0,65535]; the gap of frame lost */
} VENC_FRAMELOST_S;

/* the rc priority */
typedef enum esVENC_RC_PRIORITY_E {
    VENC_RC_PRIORITY_BITRATE_FIRST = 1, /* bitrate first */
    VENC_RC_PRIORITY_FRAMEBITS_FIRST,   /* framebits first */

    VENC_RC_PRIORITY_BUTT,
} VENC_RC_PRIORITY_E;

/* the config of the superframe */
typedef struct esVENC_SUPERFRAME_CFG_S {
    VENC_SUPERFRM_MODE_E superFrmMode; /* RW; Indicates the mode of processing the super frame */
    ES_U32 superIFrmBitsThr;       /* RW; Range:[0, 4294967295];Indicate the threshold of the super I frame for enabling
                                          the super frame processing mode */
    ES_U32 superPFrmBitsThr;       /* RW; Range:[0, 4294967295];Indicate the threshold of the super P frame for enabling
                                          the super frame processing mode */
    ES_U32 superBFrmBitsThr;       /* RW; Range:[0, 4294967295];Indicate the threshold of the super B frame for enabling
                                          the super frame processing mode */
    VENC_RC_PRIORITY_E rcPriority; /* RW; Rc Priority */
} VENC_SUPERFRAME_CFG_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __ES_COMM_RC_H__ */
