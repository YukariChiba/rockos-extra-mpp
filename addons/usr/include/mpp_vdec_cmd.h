#ifndef __MPP_VDEC_CMD_H__
#define __MPP_VDEC_CMD_H__

#include "mpp_type.h"
#include "mpp_err.h"

/*
 * decoder query interface is only for debug usage
 */
#define MPP_DEC_QUERY_STATUS        (0x00000001)
#define MPP_DEC_QUERY_WAIT          (0x00000002)
#define MPP_DEC_QUERY_FPS           (0x00000004)
#define MPP_DEC_QUERY_BPS           (0x00000008)
#define MPP_DEC_QUERY_DEC_IN_PKT    (0x00000010)
#define MPP_DEC_QUERY_DEC_WORK      (0x00000020)
#define MPP_DEC_QUERY_DEC_OUT_FRM   (0x00000040)

#define MPP_DEC_QUERY_ALL           (MPP_DEC_QUERY_STATUS       | \
                                     MPP_DEC_QUERY_WAIT         | \
                                     MPP_DEC_QUERY_FPS          | \
                                     MPP_DEC_QUERY_BPS          | \
                                     MPP_DEC_QUERY_DEC_IN_PKT   | \
                                     MPP_DEC_QUERY_DEC_WORK     | \
                                     MPP_DEC_QUERY_DEC_OUT_FRM)

typedef struct MppDecQueryCfg_t {
    /*
     * 32 bit query flag for query data check
     * Each bit represent a query data switch.
     * bit 0 - for querying decoder runtime status
     * bit 1 - for querying decoder runtime waiting status
     * bit 2 - for querying decoder realtime decode fps
     * bit 3 - for querying decoder realtime input bps
     * bit 4 - for querying decoder input packet count
     * bit 5 - for querying decoder start hardware times
     * bit 6 - for querying decoder output frame count
     */
    ES_U32      query_flag;

    /* 64 bit query data output */
    ES_U32      rt_status;
    ES_U32      rt_wait;
    ES_U32      rt_fps;
    ES_U32      rt_bps;
    ES_U32      dec_in_pkt_cnt;
    ES_U32      dec_hw_run_cnt;
    ES_U32      dec_out_frm_cnt;
} MppDecQueryCfg;

typedef void* MppExtCbCtx;
typedef MPP_RET (*MppExtCbFunc)(MppExtCbCtx cb_ctx, MppCtxPtr mpp, ES_S32 cmd, void *arg);

#endif /*__MPP_VDEC_CMD_H__*/
