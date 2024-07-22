#ifndef __MPP_RC_DEFS_H__
#define __MPP_RC_DEFS_H__

#include "mpp_venc_ref.h"

#define MAX_CPB_REFS                    (8)

typedef enum EncFrmType_e {
    INTER_P_FRAME   = 0,
    INTER_B_FRAME   = 1,
    INTRA_FRAME     = 2,
    INTER_VI_FRAME  = 3,
    INTRA_RFH_FRAME = 4,
} EncFrmType;

/*
 * EncFrmStatus controls record the encoding frame status and also control
 * work flow of encoder. It is the communicat channel between encoder implement
 * module, rate control module and hardware module.
 *
 * bit  0 ~ 31 frame status
 *      0 ~ 15 current frame status
 *     16 ~ 31 reference frame status
 * bit 32 ~ 63 encoding flow control
 */
typedef union EncFrmStatus_u {
    struct {
        /*
         * bit  0 ~ 31  frame status
         */
        /* status flag */
        ES_U32          valid           : 1;
        /*
         * 0 - write the reconstructed frame pixel to memory
         * 1 - do not write the reconstructed frame pixel to memory
         */
        ES_U32          non_recn        : 1;

        /*
         * 0 - normal frame and normal dpb management
         * 1 - save recon frame as first pass extra frame. Used in two pass mode
         */
        ES_U32          save_pass1      : 1;

        /*
         * 0 - use normal input source frame as input
         * 1 - use the previously stored first pass recon frame as input frame
         */
        ES_U32          use_pass1       : 1;

        /* reference status flag */
        /*
         * 0 - inter frame
         * 1 - intra frame
         */
        ES_U32          is_intra        : 1;

        /*
         * Valid when is_intra is true
         * 0 - normal intra frame
         * 1 - IDR frame
         */
        ES_U32          is_idr          : 1;

        /*
         * 0 - mark as reference frame
         * 1 - mark as non-refernce frame
         */
        ES_U32          is_non_ref      : 1;

        /*
         * Valid when is_non_ref is false
         * 0 - mark as short-term reference frame
         * 1 - mark as long-term refernce frame
         */
        ES_U32          is_lt_ref       : 1;

        /* bit 8 - 15 */
        ES_U32          lt_idx          : 4;
        ES_U32          temporal_id     : 4;

        /* distance between current frame and reference frame */
        MppEncRefMode   ref_mode        : 6;
        ES_S32          ref_arg         : 8;
        ES_S32          ref_dist        : 2;

        /*
         * bit 32 ~ 63  encoder flow control flags
         */
        /*
         * 0 - normal frame encoding
         * 1 - current frame will be dropped
         */
        ES_U32          drop            : 1;

        /*
         * 0 - rate control module does not change frame type parameter
         * 1 - rate control module changes frame type parameter reencode is needed
         *     to reprocess the dpb process. Also this means dpb module will follow
         *     the frame status parameter provided by rate control module.
         */
        ES_U32          re_dpb_proc     : 1;

        /*
         * 0 - current frame encoding is in normal flow
         * 1 - current frame encoding is in reencode flow
         */
        ES_U32          reencode        : 1;

        /*
         * When true current frame size is super large then the frame should be reencoded.
         */
        ES_U32          super_frame     : 1;

        /*
         * When true currnet frame is force to encoded as software skip frame
         */
        ES_U32          force_pskip     : 1;

        /*
         * Current frame is intra refresh frame
         */
        ES_U32          is_i_refresh    : 1;
        /*
         * Current frame needs add recovery point prefix
         */
        ES_U32          is_i_recovery   : 1;
        ES_U32          reserved1       : 1;

        /* reencode times */
        ES_U32          reencode_times  : 8;

        /* sequential index for each frame */
        ES_U32          seq_idx         : 16;
    };
    ES_U64 val;
} EncFrmStatus;

typedef struct EncCpbStatus_t {
    ES_S32              seq_idx;

    EncFrmStatus        curr;
    EncFrmStatus        refr;

    /* initial cpb status for current frame encoding */
    EncFrmStatus        init[MAX_CPB_REFS];
    /* final cpb status after current frame encoding */
    EncFrmStatus        final[MAX_CPB_REFS];
} EncCpbStatus;

#define ENC_RC_FORCE_QP                 (0x00000001)

typedef struct EncRcForceCfg_t {
    ES_U32              force_flag;
    ES_S32              force_qp;
    ES_U32              reserve[6];
} EncRcForceCfg;

/*
 * communication channel between rc / hal / hardware
 *
 * rc   -> hal      bit_target / bit_max / bit_min
 * hal  -> hw       quality_target / quality_max / quality_min
 * hw   -> rc / hal bit_real / quality_real / madi / madp
 */
typedef struct EncRcCommonInfo_t {
    EncFrmType      frame_type;

    /* rc to hal */
    ES_S32          bit_target;
    ES_S32          bit_max;
    ES_S32          bit_min;

    ES_S32          quality_target;
    ES_S32          quality_max;
    ES_S32          quality_min;

    /* rc from hardware */
    ES_S32          bit_real;
    ES_S32          quality_real;
    ES_S32          madi;
    ES_S32          madp;

    ES_U32          iblk4_prop; // scale 256

    ES_S64          sse;
    ES_U32          lvl64_inter_num;
    ES_U32          lvl32_inter_num;
    ES_U32          lvl16_inter_num;
    ES_U32          lvl8_inter_num;
    ES_U32          lvl32_intra_num;
    ES_U32          lvl16_intra_num;
    ES_U32          lvl8_intra_num;
    ES_U32          lvl4_intra_num;

    ES_S32          reserve[5];
} EncRcTaskInfo;

typedef struct EncRcTask_s {
    EncCpbStatus    cpb;
    EncFrmStatus    frm;
    EncRcTaskInfo   info;
    EncRcForceCfg   force;
    MppFramePtr     frame;
} EncRcTask;

#endif /* __MPP_RC_DEFS_H__ */
