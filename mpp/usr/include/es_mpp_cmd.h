#ifndef __ES_MPP_CMD_H__
#define __ES_MPP_CMD_H__

/*
 * Command id bit usage is defined as follows:
 * bit 20 - 23  - module id
 * bit 16 - 19  - contex id
 * bit  0 - 15  - command id
 */
#define CMD_MODULE_ID_MASK              (0x00F00000)
#define CMD_MODULE_OSAL                 (0x00100000)
#define CMD_MODULE_MPP                  (0x00200000)
#define CMD_MODULE_CODEC                (0x00300000)
#define CMD_MODULE_HAL                  (0x00400000)

#define CMD_CTX_ID_MASK                 (0x000F0000)
#define CMD_CTX_ID_DEC                  (0x00010000)
#define CMD_CTX_ID_ENC                  (0x00020000)
#define CMD_CTX_ID_ISP                  (0x00030000)

/* separate encoder / decoder control command to different segment */
#define CMD_CFG_ID_MASK                 (0x0000FF00)

/* mpp status control command */
#define CMD_STATE_OPS                   (0x00000100)

/* decoder control command */
#define CMD_DEC_CFG_ALL                 (0x00000000)
#define CMD_DEC_QUERY                   (0x00000100)
#define CMD_DEC_CFG                     (0x00000200)

/* encoder control command */
#define CMD_ENC_CFG_ALL                 (0x00000000)
#define CMD_ENC_QUERY                   (0x00000100)
#define CMD_ENC_CFG_RC_API              (0x00000200)

#define CMD_ENC_CFG_ROI                 (0x00008300)

typedef enum {
    MPP_OSAL_CMD_BASE                   = CMD_MODULE_OSAL,
    MPP_OSAL_CMD_END,

    MPP_CMD_BASE                        = CMD_MODULE_MPP,
    /*
     * timeout setup, refer to  MPP_TIMEOUT_XXX
     * zero     - non block
     * negative - block with no timeout
     * positive - timeout in milisecond
     */
    MPP_SET_INPUT_TIMEOUT,              /* parameter type ES_S64 */
    MPP_SET_OUTPUT_TIMEOUT,             /* parameter type ES_S64 */
    MPP_SET_DISABLE_THREAD,             /* MPP no thread mode and use external thread to decode */

    MPP_STATE_CMD_BASE                  = CMD_MODULE_MPP | CMD_STATE_OPS,
    MPP_START,
    MPP_STOP,
    MPP_PAUSE,
    MPP_RESUME,

    MPP_CMD_END,

    MPP_CODEC_CMD_BASE                  = CMD_MODULE_CODEC,
    MPP_CODEC_GET_FRAME_INFO,
    MPP_CODEC_CMD_END,

    MPP_DEC_CMD_BASE                    = CMD_MODULE_CODEC | CMD_CTX_ID_DEC,
    MPP_DEC_SET_FRAME_INFO,             /* vpu api legacy control for buffer slot dimension init */
    MPP_DEC_SET_EXT_BUF_GROUP,          /* IMPORTANT: set external buffer group to mpp decoder */
    MPP_DEC_SET_INFO_CHANGE_READY,
    MPP_DEC_SET_PRESENT_TIME_ORDER,     /* use input time order for output */
    MPP_DEC_SET_PARSER_SPLIT_MODE,      /* Need to setup before init */
    MPP_DEC_SET_PARSER_FAST_MODE,       /* Need to setup before init */
    MPP_DEC_GET_STREAM_COUNT,
    MPP_DEC_GET_VPUMEM_USED_COUNT,
    MPP_DEC_SET_VC1_EXTRA_DATA,
    MPP_DEC_SET_OUTPUT_FORMAT,
    MPP_DEC_SET_DISABLE_ERROR,          /* When set it will disable sw/hw error (H.264 / H.265) */
    MPP_DEC_SET_IMMEDIATE_OUT,
    MPP_DEC_SET_ENABLE_DEINTERLACE,     /* MPP enable deinterlace by default. Vpuapi can disable it */
    MPP_DEC_SET_ENABLE_FAST_PLAY,       /* enable idr output immediately */
    MPP_DEC_SET_DISABLE_THREAD,         /* MPP no thread mode and use external thread to decode */
    MPP_DEC_SET_MAX_USE_BUFFER_SIZE,
    MPP_DEC_SET_ENABLE_MVC,             /* enable MVC decoding*/

    MPP_DEC_CMD_QUERY                   = CMD_MODULE_CODEC | CMD_CTX_ID_DEC | CMD_DEC_QUERY,
    /* query decoder runtime information for decode stage */
    MPP_DEC_QUERY,                      /* set and get MppDecQueryCfg structure */

    CMD_DEC_CMD_CFG                     = CMD_MODULE_CODEC | CMD_CTX_ID_DEC | CMD_DEC_CFG,
    MPP_DEC_SET_CFG,                    /* set MppDecCfg structure */
    MPP_DEC_GET_CFG,                    /* get MppDecCfg structure */

    MPP_DEC_CMD_END,

    MPP_ENC_CMD_BASE                    = CMD_MODULE_CODEC | CMD_CTX_ID_ENC,
    /* basic encoder setup control */
    MPP_ENC_SET_CFG,                    /* set MppEncCfgPtr structure */
    MPP_ENC_GET_CFG,                    /* get MppEncCfgPtr structure */
    /* runtime encoder setup control */
    MPP_ENC_SET_IDR_FRAME,              /* next frame will be encoded as intra frame */
    MPP_ENC_GET_HDR_SYNC,               /* get vps / sps / pps which has better sync behavior parameter is MppPacket */
    MPP_ENC_SET_SEI_CFG,                /* SEI: Supplement Enhancemant Information, parameter is MppSeiMode */
    MPP_ENC_GET_SEI_DATA,               /* SEI: Supplement Enhancemant Information, parameter is MppPacket */

    /* query encoder runtime information for encode stage */
    MPP_ENC_QUERY,                      /* set and get MppEncQueryCfg structure */

    /* User define rate control stategy API control */
    MPP_ENC_CFG_RC_API                  = CMD_MODULE_CODEC | CMD_CTX_ID_ENC | CMD_ENC_CFG_RC_API,
    /*
     * Get RcApiQueryAll structure
     * Get all available rate control stategy string and count
     */
    MPP_ENC_GET_RC_API_ALL              = MPP_ENC_CFG_RC_API + 1,
    /*
     * Get RcApiQueryType structure
     * Get available rate control stategy string with certain type
     */
    MPP_ENC_GET_RC_API_BY_TYPE          = MPP_ENC_CFG_RC_API + 2,
    /*
     * Set RcImplApi structure
     * Add new or update rate control stategy function pointers
     */
    MPP_ENC_SET_RC_API_CFG              = MPP_ENC_CFG_RC_API + 3,
    /*
     * Get RcApiBrief structure
     * Get current used rate control stategy brief information (type and name)
     */
    MPP_ENC_GET_RC_API_CURRENT          = MPP_ENC_CFG_RC_API + 4,
    /*
     * Set RcApiBrief structure
     * Set current used rate control stategy brief information (type and name)
     */
    MPP_ENC_SET_RC_API_CURRENT          = MPP_ENC_CFG_RC_API + 5,

    MPP_ENC_CMD_END,

    MPP_ISP_CMD_BASE                    = CMD_MODULE_CODEC | CMD_CTX_ID_ISP,
    MPP_ISP_CMD_END,

    MPP_HAL_CMD_BASE                    = CMD_MODULE_HAL,
    MPP_HAL_CMD_END,

    MPI_CMD_BUTT,
} MpiCmd;

#endif /*__ES_MPP_CMD_H__*/
