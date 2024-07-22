#ifndef __MPP_TYPE_H__
#define __MPP_TYPE_H__

#include <stddef.h>

#if defined(_WIN32) && !defined(__MINGW32CE__)

typedef unsigned char           ES_U8;
typedef unsigned short          ES_U16;
typedef unsigned int            ES_U32;
typedef unsigned long           ES_ULONG;
typedef unsigned __int64        ES_U64;

typedef char                    ES_S8;
typedef short                   ES_S16;
typedef int                     ES_S32;
typedef long                    ES_LONG;
typedef __int64                 ES_S64;

#else

typedef unsigned char           ES_U8;
typedef unsigned short          ES_U16;
typedef unsigned int            ES_U32;
typedef unsigned long           ES_ULONG;
typedef unsigned long long int  ES_U64;

typedef char                    ES_S8;
typedef short                   ES_S16;
typedef int                     ES_S32;
typedef long                    ES_LONG;
typedef long long int           ES_S64;

#endif

typedef char                    ES_CHAR;

#ifndef ES_VOID
#define ES_VOID void
#endif

/*----------------------------------------------*
 * const defination                             *
 *----------------------------------------------*/
typedef enum {
    ES_FALSE = 0,
    ES_TRUE = 1,
} ES_BOOL;

#ifndef ES_NULL
#define ES_NULL 0L
#endif

#ifndef MODULE_TAG
#define MODULE_TAG              NULL
#endif

/**
 * @ingroup es_mpi
 * @brief The type of mpp context
 * @details This type is used when calling mpp_init(), which including decoder,
 *          encoder and Image Signal Process(ISP). So far decoder and encoder
 *          are supported perfectly, and ISP will be supported in the future.
 */
typedef enum {
    MPP_CTX_DEC,  /**< decoder */
    MPP_CTX_ENC,  /**< encoder */
    MPP_CTX_ISP,  /**< isp */
    MPP_CTX_BUTT, /**< undefined */
} MppCtxType;

/**
 * @ingroup es_mpi
 * @brief Enumeration used to define the possible video compression codings.
 *        sync with the omx_video.h
 *
 * @note  This essentially refers to file extensions. If the coding is
 *        being used to specify the ENCODE type, then additional work
 *        must be done to configure the exact flavor of the compression
 *        to be used.  For decode cases where the user application can
 *        not differentiate between MPEG-4 and H.264 bit streams, it is
 *        up to the codec to handle this.
 */
typedef enum {
    MPP_VIDEO_CodingUnused,             /**< Value when coding is N/A */
    MPP_VIDEO_CodingAutoDetect,         /**< Autodetection of coding type */
    MPP_VIDEO_CodingMPEG2,              /**< AKA: H.262 */
    MPP_VIDEO_CodingH263,               /**< H.263 */
    MPP_VIDEO_CodingMPEG4,              /**< MPEG-4 */
    MPP_VIDEO_CodingWMV,                /**< Windows Media Video (WMV1,WMV2,WMV3)*/
    MPP_VIDEO_CodingRV,                 /**< all versions of Real Video */
    MPP_VIDEO_CodingAVC,                /**< H.264/AVC */
    MPP_VIDEO_CodingMJPEG,              /**< Motion JPEG */
    MPP_VIDEO_CodingVP8,                /**< VP8 */
    MPP_VIDEO_CodingVP9,                /**< VP9 */
    MPP_VIDEO_CodingVC1 = 0x01000000,   /**< Windows Media Video (WMV1,WMV2,WMV3)*/
    MPP_VIDEO_CodingFLV1,               /**< Sorenson H.263 */
    MPP_VIDEO_CodingDIVX3,              /**< DIVX3 */
    MPP_VIDEO_CodingVP6,
    MPP_VIDEO_CodingHEVC,               /**< H.265/HEVC */
    MPP_VIDEO_CodingAVSPLUS,            /**< AVS+ */
    MPP_VIDEO_CodingAVS,                /**< AVS profile=0x20 */
    MPP_VIDEO_CodingAVS2,               /**< AVS2 */
    MPP_VIDEO_CodingAV1,                /**< av1 */
    MPP_VIDEO_CodingKhronosExtensions = 0x6F000000, /**< Reserved region for introducing Khronos Standard Extensions */
    MPP_VIDEO_CodingVendorStartUnused = 0x7F000000, /**< Reserved region for introducing Vendor Extensions */
    MPP_VIDEO_CodingMax = 0x7FFFFFFF
} MppCodingType;

/*
 * All external interface object list here.
 * The interface object is defined as void * for expandability
 * The cross include between these objects will introduce extra
 * compiling difficulty. So we move them together in this header.
 *
 * Object interface header list:
 *
 * MppCtx           - es_mpi.h
 * MppParam         - es_mpi.h
 *
 * MppFramePtr         - mpp_frame.h
 * MppPacketPtr        - mpp_packet.h
 *
 * MppBufferPtr        - mpp_buffer.h
 * MppBufferGroupPtr   - mpp_buffer.h
 *
 * MppMetaPtr          - mpp_meta.h
 */

typedef void* MppCtxPtr;
typedef void* MppParamPtr;

typedef void* MppFramePtr;
typedef void* MppPacketPtr;

typedef void* MppBufferPtr;
typedef void* MppBufferGroupPtr;

typedef void* MppMetaPtr;

#endif /*__MPP_TYPE_H__*/
