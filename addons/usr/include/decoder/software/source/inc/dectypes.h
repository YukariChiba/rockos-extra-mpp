/*------------------------------------------------------------------------------
--       Copyright (c) 2015-2017, VeriSilicon Inc. All rights reserved        --
--         Copyright (c) 2011-2014, Google Inc. All rights reserved.          --
--         Copyright (c) 2007-2010, Hantro OY. All rights reserved.           --
--                                                                            --
-- This software is confidential and proprietary and may be used only as      --
--   expressly authorized by VeriSilicon in a written licensing agreement.    --
--                                                                            --
--         This entire notice must be reproduced on all copies                --
--                       and may not be removed.                              --
--                                                                            --
--------------------------------------------------------------------------------
-- Redistribution and use in source and binary forms, with or without         --
-- modification, are permitted provided that the following conditions are met:--
--   * Redistributions of source code must retain the above copyright notice, --
--       this list of conditions and the following disclaimer.                --
--   * Redistributions in binary form must reproduce the above copyright      --
--       notice, this list of conditions and the following disclaimer in the  --
--       documentation and/or other materials provided with the distribution. --
--   * Neither the names of Google nor the names of its contributors may be   --
--       used to endorse or promote products derived from this software       --
--       without specific prior written permission.                           --
--------------------------------------------------------------------------------
-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"--
-- AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE  --
-- IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE --
-- ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  --
-- LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        --
-- CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF       --
-- SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   --
-- INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN    --
-- CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)    --
-- ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE --
-- POSSIBILITY OF SUCH DAMAGE.                                                --
--------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

#ifndef DECTYPES_H
#define DECTYPES_H

#include "basetype.h"
#include "dwl.h"
#include "decapicommon.h"
#include "decsei.h"

/**
 * \enum DecCodec
 * \brief Specifies the decoder types.
 * \ingroup common_group
 */
enum DecCodec {
  DEC_MPEG4, /**< Support MPEG4 video decoder */
  DEC_MPEG2, /**< Support MPEG2 video decoder */
  DEC_VP6, /**< Support VP6 video decoder */
  DEC_VP8, /**< Support VP8 video decoder */
  DEC_VP9, /**< Support VP9 video decoder */
  DEC_HEVC, /**< Support HEVC video decoder */
  DEC_H264_H10P, /**< Support H264_High10 video decoder */
  DEC_H264, /**< Support H264 video decoder */
  DEC_AVS, /**< Support AVS video decoder */
  DEC_AVS2, /**< Support AVS2 video decoder */
  DEC_AV1, /**< Support AV1 video decoder */
  DEC_JPEG, /**< Support JPEG image decoder */
  DEC_VC1, /**< Support VC1 video decoder */
  DEC_RV, /**< Support RV video decoder */
  DEC_FMT_MAX /**< The limit on the input value of this parameter */
};

/**
 * \enum DecRet
 * \brief Specifies the return values for the decoder API functions.
 * \ingroup common_group
 */
enum DecRet {
  /** Success */
  DEC_OK = 0, /**<\hideinitializer */
  /** Stream processed */
  DEC_STRM_PROCESSED = 1, /**<\hideinitializer */
  /** Picture available for output */
  DEC_PIC_RDY = 2, /**<\hideinitializer */
  /** Picture decoded */
  DEC_PIC_DECODED = 3, /**<\hideinitializer */
  /** New stream headers decoded */
  DEC_HDRS_RDY = 4, /**<\hideinitializer */
  /** New stream headers decoded, data partitioned stream(mpeg4 specific) */
  DEC_DP_HDRS_RDY = 5, /**<\hideinitializer */
  /** Advanced coding tools detected in stream */
  DEC_ADVANCED_TOOLS = 6, /**<\hideinitializer */
  /** A slice was decoded */
  DEC_SLICE_RDY = 7, /**<\hideinitializer */
  /** Output pictures must be retrieved before continuing decode */
  DEC_PENDING_FLUSH = 8, /**<\hideinitializer */
  /** Skipped decoding non-reference picture */
  DEC_NONREF_PIC_SKIPPED = 9, /**<\hideinitializer */
  /** End-of-stream state set in the decoder */
  DEC_END_OF_STREAM = 10,         /**<\hideinitializer */
  /** End of video sequence */
  DEC_END_OF_SEQ = 11,         /**<\hideinitializer */
  /** Waiting for external buffers allocated. */
  DEC_WAITING_FOR_BUFFER = 12,    /**<\hideinitializer */
  /** Scan Processed(pjpeg specific) */
  DEC_SCAN_PROCESSED = 13,     /**<\hideinitializer */
  /** Decoder is aborted */
  DEC_ABORTED = 14,              /**<\hideinitializer */
  /** All pics have been flushed */
  DEC_FLUSHED = 15,              /**<\hideinitializer */
  /** The input buffer has consumed, but the decoding has not been completed */
  DEC_BUF_EMPTY = 16,              /**<\hideinitializer */
  /** Syntax element error found in stream */
  DEC_STREAM_ERROR_DEDECTED = 17,  /**<\hideinitializer */
  /** Resolution changed in multiresolution video */
  DEC_RESOLUTION_CHANGED = 18,    /**<\hideinitializer */
  /** video Object Sequence end marker dedected */
  DEC_VOS_END = 19,    /**<\hideinitializer */
  /** Invalid parameter was used */
  DEC_PARAM_ERROR = -1,          /**<\hideinitializer */
  /* An unrecoverable error in decoding */
  DEC_STRM_ERROR = -2,           /**<\hideinitializer */
  /** The decoder has not been initialized */
  DEC_NOT_INITIALIZED = -3,      /**<\hideinitializer */
  /** Memory allocation failed */
  DEC_MEMFAIL = -4,              /**<\hideinitializer */
  /** Initialization failed */
  DEC_INITFAIL = -5,             /**<\hideinitializer */
  /** Video sequence information is not available because stream headers have not been decoded */
  DEC_HDRS_NOT_RDY = -6,         /**<\hideinitializer */
  /** Video sequence frame size or tools not supported */
  DEC_STREAM_NOT_SUPPORTED = -8, /**<\hideinitializer */
  /** External buffer rejected. (Too much than requested) */
  DEC_EXT_BUFFER_REJECTED = -9,    /**<\hideinitializer */
  /** Invalid pp parameter was used */
  DEC_INFOPARAM_ERROR = -10,    /**<\hideinitializer */
  /** ERROR */
  DEC_ERROR = -11,              /**<\hideinitializer */
  /** Unsupported */
  DEC_UNSUPPORTED = -12,        /**<\hideinitializer */
  /** Invalid stream length used */
  DEC_INVALID_STREAM_LENGTH = -13, /**<\hideinitializer */
  /** Invalid input buffer size used */
  DEC_INVALID_INPUT_BUFFER_SIZE = -14, /**<\hideinitializer */
  /** Needs to increase input buffer */
  DEC_INCREASE_INPUT_BUFFER = -15, /**<\hideinitializer */
  /** Slice mode not supported for this operation type */
  DEC_SLICE_MODE_UNSUPPORTED = -16, /**<\hideinitializer */
  /** Supplied metadata is in wrong format */
  DEC_METADATA_FAIL = -17,     /**<\hideinitializer */
  /** The decoder has no available buffer */
  DEC_NO_DECODING_BUFFER = -99,  /**<\hideinitializer */
  /** Driver could not reserve decoder hardware */
  DEC_HW_RESERVED = -254,        /**<\hideinitializer */
  /** Hardware timeout occurred */
  DEC_HW_TIMEOUT = -255,         /**<\hideinitializer */
  /** Hardware received error status from system bus */
  DEC_HW_BUS_ERROR = -256,       /**<\hideinitializer */
  /** Hardware encountered an unrecoverable system error */
  DEC_SYSTEM_ERROR = -257,       /**<\hideinitializer */
  /** Decoder wrapper encountered an error */
  DEC_DWL_ERROR = -258,          /**<\hideinitializer */
  /** Hardware encountered an fatal system error */
  DEC_FATAL_SYSTEM_ERROR = -259,       /**<\hideinitializer */
  /** Evaluation limit exceeded */
  DEC_EVALUATION_LIMIT_EXCEEDED = -999, /**<\hideinitializer */
  /** Video format not supported */
  DEC_FORMAT_NOT_SUPPORTED = -1000 /**<\hideinitializer */
    /* TODO(vmr): Prune what is not needed from these. */
};

/**
 * \enum DecDARFormat
 * \brief DAR : Display aspect ratio(Only used in AVS and MPEG2).
 * \ingroup common_group
 */
enum DecDARFormat{
  /** Display aspect ratio 1 : 1 */
  DEC_1_1 = 0x01, /**<\hideinitializer */
  /** Display aspect ratio 4 : 3 */
  DEC_4_3 = 0x02, /**<\hideinitializer */
  /** Display aspect ratio 16 : 9 */
  DEC_16_9 = 0x03, /**<\hideinitializer */
  /** Display aspect ratio 2.21 : 1 */
  DEC_2_21_1 = 0x04 /**<\hideinitializer */
};

/**
 * \enum DecErrorConcealment
 * \brief Error concealment mode.
 * \ingroup common_group
 */
enum DecErrorConcealment {
  /** If current picture is erroneous, freeze current picture */
  DEC_PICTURE_FREEZE = 0, /**<\hideinitializer */
  /** If current picture is erroneous, freeze whole picture until a new IDR picture encountered. */
  DEC_INTRA_FREEZE = 1 /**<\hideinitializer */
};

/**
 * \enum DecInputFormat_
 * \brief Format of the input sequence.
 * \ingroup common_group
 */
enum DecInputFormat {
  /** The format of the input sequence is VP7 */
  DEC_INPUT_VP7 = 0x01, /**<\hideinitializer */
  /** The format of the input sequence is VP8 */
  DEC_INPUT_VP8, /**<\hideinitializer */
  /** The format of the input sequence is WEBP */
  DEC_INPUT_WEBP, /**<\hideinitializer */
  /** The format of the input sequence is MPEG4 */
  DEC_INPUT_MPEG4, /**<\hideinitializer */
  /** The format of the input sequence is SORENSON */
  DEC_INPUT_SORENSON, /**<\hideinitializer */
  /** The format of the input sequence is CUSTOM_1 */
  DEC_INPUT_CUSTOM_1 /**<\hideinitializer */
};

/**
 * \enum DecSkipFrameMode
 * \brief Skip some frames when decoding.
 * \ingroup common_group
 */
enum DecSkipFrameMode {
  /** non_ref_recon : default value, decode all frame, but dont output
   *  recon data of non-reference frames(only hevc & h264_high10). */
  DEC_SKIP_NON_REF_RECON = 0, /**<\hideinitializer */
  /** non_ref : dont decode non-reference frames. */
  DEC_SKIP_NON_REF = 1, /**<\hideinitializer */
  /** none : close this feature for all function. */
  DEC_SKIP_NONE /**<\hideinitializer */
};

/**
 * \enum DecVideoRange
 * \brief Sample range of the YCbCr samples in the decoded picture.
 * \ingroup common_group
 */
enum DecVideoRange {
  /** Sample range [16, 235] */
  DEC_VIDEO_RANGE_NORMAL = 0x0, /**<\hideinitializer */
  /** Sample range [0, 255] */
  DEC_VIDEO_RANGE_FULL = 0x1, /**<\hideinitializer */
  /** similar to DEC_VIDEO_RANGE_NORMAL */
  DEC_VIDEO_STUDIO_SWING = 0x0, /**<\hideinitializer */
  /** similar to DEC_VIDEO_RANGE_FULL */
  DEC_VIDEO_FULL_SWING = 0x1 /**<\hideinitializer */
};

/**
 * \enum DecColorSpace
 * \brief Color space which be selected in the decoded picture.
 * \ingroup common_group
 */
enum DecColorSpace {
  /** Color spac : YUV */
  DEC_YCbCr_BT601 = 0x0, /**<\hideinitializer */
  /** Color spac : self define */
  DEC_CUSTOM = 0x1, /**<\hideinitializer */
  /** Color spac : RGB */
  DEC_RGB = 0x7 /**<\hideinitializer */
};

/**
 * \enum DecBufferType
 * \brief The type of buffer allocated.
 * \ingroup common_group
 */
enum DecBufferType {
  /** reference + compression table + DMV */
  REFERENCE_BUFFER = 0, /**<\hideinitializer */
  /** raster scan out buffer */
  RASTERSCAN_OUT_BUFFER, /**<\hideinitializer */
  /** douwnscale scan out buffer */
  DOWNSCALE_OUT_BUFFER, /**<\hideinitializer */
  /** filter mem + bsd control mem */
  TILE_EDGE_BUFFER, /**<\hideinitializer */
  /** segment map */
  SEGMENT_MAP_BUFFER, /**<\hideinitializer */
  /** tile info + prob table + entropy context counter */
  MISC_LINEAR_BUFFER, /**<\hideinitializer */
  /** The limit on the input value of this parameter */
  BUFFER_TYPE_NUM /**<\hideinitializer */
};

/**
 * \enum DecUserDataType
 * \brief User data type(Only used in MPEG4).
 * \ingroup common_group
 */
enum DecUserDataType {
  /** The data type is VOS */
  DEC_USER_DATA_VOS = 0, /**<\hideinitializer */
  /** The data type is VISO */
  DEC_USER_DATA_VISO, /**<\hideinitializer */
  /** The data type is VOL */
  DEC_USER_DATA_VOL, /**<\hideinitializer */
  /** The data type is GOV */
  DEC_USER_DATA_GOV /**<\hideinitializer */
};

/**
 * \struct DecParams
 * \brief partial tb_cfg.dec_params parameters..
 * \ingroup common_group
 */
struct DecParams {
  /** output picture endian : big or little endian. */
  u32 output_picture_endian;
  /** how long are the hardware data bursts; better left unchanged. */
  u32 bus_burst_length;
  /** compensation for bus latency; values up to 63. */
  u32 latency_compensation;
  /** clock is gated from decoder between images and for disabled codecs. */
  u32 clk_gate_decoder;
  /** decoder data disgard : enable or disable. */
  u32 data_discard;
  /** reference buffer : adjust value. */
  u32 refbu_data_excess_max_pct;
  /** bus width is 64bit. */
  u32 bus_width64bit_enable;
  /** reference buffer : memory wait states for latency. */
  u32 latency;
  /** reference buffer : memory wait states for non_seq_clk. */
  u32 non_seq_clk;
  /** reference buffer : memory wait states for seq_clk. */
  u32 seq_clk;
  /** APF threshold value. */
  i32 apf_threshold_value;
  /** service merge disable. */
  u32 service_merge_disable;
  /** AXI outstanding threshold for write. */
  u32 axi_wr_outstand;
  /** AXI outstanding threshold for read. */
  u32 axi_rd_outstand;
};

/**
 * \struct DecUserConf
 * \brief User data configuration(Only used in MPEG4).
 * \ingroup common_group
 */
struct DecUserConf {
  /** The type of buffer allocated. */
  enum DecUserDataType user_data_type;
  /** The pointer to VOS data */
  u8  *p_user_data_vos;
  /** The VOS data max length */
  u32  user_data_vosmax_len;
  /** The pointer to VISO data */
  u8  *p_user_data_viso;
  /** The VISO data max length */
  u32  user_data_visomax_len;
  /** The pointer to VOL data */
  u8  *p_user_data_vol;
  /** The VOL data max length */
  u32  user_data_volmax_len;
  /** The pointer to GOV data */
  u8  *p_user_data_gov;
  /** The GOV data max length */
  u32  user_data_govmax_len;
};

/**
 * \struct DecCropParams
 * \brief Cropping info.
 * \ingroup common_group
 */
struct DecCropParams {
  /** The left offset value */
  u32 crop_left_offset;
  /** The wigth value */
  u32 crop_out_width;
  /** The top offset value */
  u32 crop_top_offset;
  /** The height value */
  u32 crop_out_height;
};

/**
 * \struct DecMetaData
 * \brief Container for the metadata of the stream(Only used in VC1). \n
 * Contains a wide range of information about the stream, e.g. what kind of 
 * tools are needed to decode the stream.
 * \ingroup common_group
 */
struct DecMetaData {
  u32     max_coded_width;  /**< Specifies the maximum coded width in
                                  *  pixels of picture within the sequence.
                                  *  Valid range [2,8192] (even values).*/
  u32     max_coded_height; /**< Specifies the maximum coded height in
                                  *  pixels of picture within the sequence.
                                  *  Valid range [2,8192] (even values).*/
  u32     vs_transform;    /**< Indicates whether variable sized transform
                                  *  is enabled for the sequence. Valid range [0,1].*/
  u32     overlap;        /**< Indicates whether overlap smoothing is
                                  *  enabled for the sequence. Valid range [0,1].*/
  u32     sync_marker;     /**< Indicates whether there are syncronization markers in
                                  *  the stream. Valid range [0,1].*/
  u32     quantizer;      /**< Indicates quantizer type used for the
                                  *  sequence. Valid range [0,3].*/
  u32     frame_interp;     /**< Indicates whether the INTERPFRM flag (which
                                  *  provides information to display process)
                                  *  exists in the picture headers. Valid range [0,1].*/
  u32     max_bframes;     /**< Specifies the maximum amount of consecutive
                                  *  B-frames within the sequence. Valid range [0,7].*/
  u32     fast_uv_mc;       /**< Indicates whether the rounding of color
                                  *  difference motion vectors is enabled. Valid range [0,1].*/
  u32     extended_mv;     /**< Indicates whether extended motion
                                  *  vectors are enabled for the sequence. Valid range [0,1].*/
  u32     multi_res;       /**< Indicates whether frames may be coded
                                  *  at smaller resolutions than
                                  *  the specified frame resolution. Valid range [0,1].*/
  u32     range_red;       /**< Indicates whether range reduction is used
                                  *  in the sequence. Valid range [0,1].*/
  u32     dquant;         /**< Indicates whether the quantization step
                                  *  may vary within a frame. Valid range [0,2].*/
  u32     loop_filter;     /**< Indicates whether loop filtering is
                                  *  enabled for the sequence. Valid range [0,1].*/
  u32     profile;        /**< Specifies profile of the input video bitstream. */
};

/**
 * \struct DecTime
 * \brief Time info(Only used in AVS, MP2 and MP4).
 * \ingroup common_group
 */
struct DecTime {
  u32 hours; /**< hours information */
  u32 minutes; /**< minutes information */
  u32 seconds; /**< seconds information */
  u32 pictures; /**< pictures information */
  u32 time_incr; /**< vop time increment : mpeg4 specific */
  u32 time_res; /**< vop time increment resolution : mpeg4 specific */
};

#if defined(_MSC_VER) || defined(_WIN32)
/**
 * \struct SEI_header
 * \brief SEI header info of sei_buffer.
 * \ingroup common_group
 */
struct SEI_header {
  /* TODO(JZQ) : need fix, it has to be a compact struct */
  /** The SEI type */
  u8 type;
  /** The SEI data size */
  u16 size;
  /** The SEI status */
  u8 status;
};
#else
/**
 * \struct SEI_header
 * \brief SEI header info of sei_buffer.
 * \ingroup common_group
 */
struct SEI_header {
  /** The SEI type */
  u8 type;
  /** The SEI data size */
  u16 size;
  /** The SEI status */
  u8 status;
} __attribute__((packed));
#endif

/**
 * \struct SEI_buffer
 * \brief It stores captured SEI stream data.
 * \ingroup common_group
 */
struct SEI_buffer {
  u8 bitmask[32]; /**< 256bit, Indicata which SEI is interested */
  u8 *buffer; /**< SEI buffer pointer */
  u32 total_size; /**< 32bit, the buffer size */
  u32 available_size; /**< the available data size in SEI buffer */
};

/**
 * \struct DecInput
 * \brief The decoder input.
 * \ingroup common_group
 */
struct DecInput {
  struct DWLLinearMem buffer; /**< Pointer to the input buffer. */
  u8* stream[2];              /**< stream[0]: stream start before inputting.
                               *   stream[1]: stream end after inputting.   */
  u32 data_len;               /**< Number of bytes to be decoded. */
  struct SEI_buffer *sei_buffer; /**< SEI buffer */
  u32 pic_id; /**< current pic_id for the input frame */
  enum DecRet dec_ret; /**< the irq status for the input frame */
};

/**
 * \struct DecOutput
 * \brief The decoder output.
 * \ingroup common_group
 */
struct DecOutput {
  u8* strm_curr_pos; /**< Pointer to stream position where decoding ended */
  addr_t strm_curr_bus_address; /**< The bus address location where the decoding ended */
  u32 data_left; /**< How many bytes left undecoded */
  u8* strm_buff; /**< Pointer to stream buffer start */
  addr_t strm_buff_bus_address; /**< The bus address location where the stream buffer start */
  u32 buff_size; /**< The stream buffer size */
  u32 slice_height; /**< The height of WebP slice */
  struct SEI_buffer *sei_buffer; /**< SEI buffer */
};

/**
 * \struct DecSliceInfo
 * \brief Pointer to the slice info(Only used in RV). \n
 * It contains offset value of each slice in the data buffer, 
 * \ingroup common_group
 */
struct DecSliceInfo {
  /** The offset value of each slice in the data buffer, 
   * including start point "0" and end point "data_len". */
  u32 offset;
  /** Indicates whether slice info is available */
  u32 is_valid;
};

/**
 * \struct DecInputParameters
 * \brief Decoder input data
 * \ingroup common_group
 */
struct DecInputParameters {
  u32 pic_id; /**< picture decoded id */
  void* p_user_data; /**< potint to user data */
  u8* stream; /**< point to input stream */
  u32 strm_len; /**< input stream length */
  addr_t stream_bus_address; /**< input stream bus address */
  struct DWLLinearMem stream_buffer;  /**< input stream buffer */
  u32 buffer_size; /**< input stream buffer size */
  u32 dec_image_type;   /**< Full image or Thumbnail to be decoded */
  u32 slice_mb_set; /**< slice mode: mcu rows to decode */
  u32 ri_count;     /**< count of restart intervals in input stream */
  u32 *ri_array;    /**< offsets of beginnings of restart intervals */
  u32 low_latency; /**< Indicates whether low latency is available */
  u32 frame_len; /**< The frame date length */
  u32 pic_decoded; /**< flag : this pic has been decoded. */
  u32 exit_send_thread; /**< flag : exit the send thread. */
  u32 slice_height;     /**< height of WebP slice, unused for other formats */
  enum DecSkipFrameMode skip_frame; /* Skip some frames when decoding. */
  struct SEI_buffer *sei_buffer; /**< SEI buffer, HEVC and H264 apecific */

  /* MPEG4 specific */
  u32 enable_deblock;  /**< Enable deblocking of post processed picture.
                        * NOTE: This parameter is not valid if the decoder
                        * is not used in pipeline mode with the post
                        * processor i.e. it has no effect on the
                        * decoding process */

  /* VP8 specific */
  u32 *p_pic_buffer_y;    /**< luminance output address of user allocated buffer,
                             used in conjunction with external buffer allocation */
  addr_t pic_buffer_bus_address_y; /**< The bus address for luminance output */
  u32 *p_pic_buffer_c;    /**< chrominance output address of user allocated buffer,
                             used in conjunction with external buffer allocation */
  addr_t pic_buffer_bus_address_c; /**< The bus address for luminance output */

  /* JPEG specific */
  struct DWLLinearMem picture_buffer_y;    /**< luma output address ==> if user allocated */
  struct DWLLinearMem picture_buffer_cb_cr; /**< chroma output address ==> if user allocated */
  struct DWLLinearMem picture_buffer_cr; /**< chroma output address ==> if user allocated */

  /* RV specific */
  u32 timestamp;     /**< timestamp of current picture from rv frame header.
                      * NOTE: timestamp of a B-frame should be adjusted referring
                      * to its forward reference frame's timestamp */
  u32 slice_info_num;    /**< The number of slice offset entries. */
  struct DecSliceInfo *slice_info;     /**< Pointer to the slice_info. */
};

/**
 * \brief Stream consumed callback prototype \n
 * This callback is invoked by the decoder to notify the application that 
 * a stream buffer was fully processed and can be reused.
 * \param stream base address of a buffer that was set as input when
 *                calling xxxDecDecode().
 * \param p_user_data application provided pointer to some private data.
 *                  This is set at decoder initialization time.
 * \sa DecMCConfig;
 * \ingroup common_group
 */
typedef void DecMCStreamConsumed(void *stream, void *p_user_data);

/**
 * \struct struct DecMCConfig
 * \brief Multicore decoder init configuration. \n
 * \ingroup common_group
 */
struct DecMCConfig {
  /** Indicates whether multicore is available */
  u32 mc_enable;
  /** Application provided callback for stream buffer processed */
  DecMCStreamConsumed *stream_consumed_callback;
};

/**
 * \struct struct DecInitConfig
 * \brief Decoder initialization params, will be used in VCDecInit.
 * \ingroup common_group
 */
struct DecInitConfig {
  const void* dwl_inst;       /**< struct DWL instance. */
  enum DecCodec codec; /**< Specifies the decoder types. */
  u32 disable_picture_reordering; /**< Output in decoding order. */
  enum DecErrorHandling error_handling; /**< Error handling mode. */
  u32 use_video_compressor; /**< Indicates whether RFC is available */
  u32 use_ringbuffer; /**< Indicates whether ringbuffer is available */
  u32 full_stream_mode; /**< Specifies the decoder input mode is full stream mode. */
  enum DecDecoderMode decoder_mode; /**< Decoder working mode. */
  u32 guard_size; /**< The minimum difference between minimum buffers number and allocated 
                       buffers number that will force to return HDRS_RDY even buffers 
                       number/size are sufficient for new sequence. */
  u32 use_adaptive_buffers; /**< When sequence changes, if old output buffers (number/size) 
                                 are sufficient for new sequence, old buffers will be used 
                                 instead of reallocating output buffer. */
  u32 num_frame_buffers; /* To use n frame buffers in decoder specified by user */
  u32 rlc_mode; /**< Indicates whether rlc mode is available(H264/MPEG4 only) */
  enum DecErrorConcealment concealment_mode; /**< Error concealment mode. */
  u32 max_num_pics_to_decode; /**< limits the decoding to N pictures. 0 for unlimited. */
  struct DecMCConfig mc_cfg; /**< Multicore decoder init configuration. */
  enum DecSkipFrameMode skip_frame; /**< Skip some frames when decoding. */
  u32 auxinfo; /**< qp_output_enable */
  enum DecInputFormat dec_format; /**< Format of the input sequence(vp8/mpeg4 only). */
  /* h264 specific */
  u32 mvc; /**< Indicates whether mvc stream */
  /* rv specific */
  u32 frame_code_length; /**< Frame code length */
  u32 *frame_sizes; /**< Frame size */
  u32 rv_version; /**< RV version : RV8 RV9 RV10 */
  u32 max_frame_width; /**< Max frame width */
  u32 max_frame_height; /**< Max frame heigth */
  /* vc1 specific */
  struct DecMetaData meta_data; /**< The metadata of the stream(Only used in VC1) */
  /* av1 specific */
  u32 disable_late_hw_sync;
  u32 disable_clock_gating;
  u32 enable_dram_throttle;
  u32 annexb;
  u32 plainobu;
  u32 multicore_poll_period;
  u32 tile_transpose;
  u32 oppoints;
};

/**
 * \struct struct DecConfig
 * \brief Decoder setting params, will be used in VCDecSetInfo.
 * \ingroup common_group
 */
struct DecConfig {
  PpUnitConfig ppu_cfg[DEC_MAX_OUT_COUNT]; /**< A structure containing PP unit configuration information. */
  DelogoConfig delogo_params[2]; /**< delogo config parameters */
  DecPicAlignment align; /**< Stride alignment: aligned to 1/8/16/.../512 bytes. */
  u32 hw_conceal; /**< Use Hw error concealment(only hevc/h264/av1).*/
  u32 disable_slice; /**< disable slice mode(only hevc/h264). */
  /* jpeg specific */
  u32 dec_image_type; /**< decode image type : JPEGDEC_IMAGE or JPEGDEC_THUMBNAIL */
};

/**
 * \struct struct DecSequenceInfo
 * \brief Video sequence information.
 * \ingroup common_group
 */
struct DecSequenceInfo {
  u32 vp_version;       /**< VP codec version defined in input stream */
  u32 vp_profile;       /**< VP cocec profile defined in input stream */
  u32 pic_width;                    /**< decoded picture width in pixels */
  u32 pic_height;                   /**< decoded picture height in pixels */
  u32 scaled_width;     /**< scaled width of the displayed video */
  u32 scaled_height;    /**< scaled height of the displayed video */
  u32 pic_width_thumb;                    /**< decoded picture width in pixels in Thumbnail */
  u32 pic_height_thumb;                   /**< decoded picture height in pixels in Thumbnail */
  u32 scaled_width_thumb;     /**< scaled width of the displayed video in Thumbnail */
  u32 scaled_height_thumb;    /**< scaled height of the displayed video in Thumbnail */
  u32 sar_width;                    /**< sample aspect ratio */
  u32 sar_height;                   /**< sample aspect ratio */
  struct DecCropParams crop_params; /**< Cropping parameters for the picture */
  enum DecVideoRange video_range;   /**< YUV sample video range */
  u32 matrix_coefficients; /**< matrix coefficients RGB->YUV conversion */
  u32 is_mono_chrome;      /**< is sequence monochrome */
  u32 is_interlaced;       /**< is sequence interlaced */
  u32 num_of_ref_frames;   /**< Maximum number of reference frames */
  u32 chroma_format_idc; /*0 mono chrome; 1 yuv420; 2 yuv422*/
  u32 bit_depth_luma;    /**< Bit depth of stored picture for luma */
  u32 bit_depth_chroma; /**< Bit depth of stored picture for chroma */
  u32 pic_stride;       /**< Byte width of the picture as stored in memory for luma */
  u32 pic_stride_ch;    /**< Byte width of the picture as stored in memory for chroma */
  enum DecDpbMode dpb_mode;             /**< DPB mode : frame, or field interlaced */
  enum DecPictureFormat output_format; /**< Format of the output picture */
  enum DecPictureFormat output_format_thumb; /**< Format of the output picture in thumbnail */
  u32 coding_mode; /**< JPEG code type :
                         * JPEG_BASELINE
                         * JPEG_PROGRESSIVE
                         * JPEG_NONINTERLEAVED
                         */
  u32 coding_mode_thumb;    /**< JPEG code type in thumbnail :
                                 * JPEG_BASELINE
                                 * JPEG_PROGRESSIVE
                                 * JPEG_NONINTERLEAVED
                                 */
  u32 thumbnail_type;  /**< Thumbnail exist or not or not supported */

  /* H264 specific */
  u32 pp_enabled; /**< post process is available */
  u32 h264_base_mode;    /**< baseline profile, only H264 */
  /* VC1 specific */
  u32 frame_rate_numerator;
  u32 frame_rate_denominator;
  u32 buf_release_flag;
  /* JPEG specific */
  struct DecInputParameters jpeg_input_info; /**< Decoder input data(Only jpeg in here) */
  u32 img_max_dec_width; /**< Maximum supported decoding width for jpeg */ 
  u32 img_max_dec_height; /**< Maximum supported decoding height for jpeg */ 
  /* AVS specific */
  u32 profile_id; /**< The profile id */
  u32 level_id; /**< The level id */
  /* MPEG2 MPEG4 AVS specific */
  u32 profile_and_level_indication;
  u32 display_aspect_ratio;
  u32 stream_format;
  u32 video_format;
  u32 colour_primaries;
  u32 transfer_characteristics;
  u32 colour_description_present_flag;
  u32 multi_buff_pp_size;
  /* MPEG4 specific */
  u32 user_data_voslen; /**< length of VOS data */
  u32 user_data_visolen; /**< length of VIS0 data */
  u32 user_data_vollen; /**< length of VOL data */
  u32 user_data_govlen; /**< length of GOV data */
  u32 gmc_support;
  /* RV specific */
  u32 out_pic_coded_width; /**< output picture width */
  u32 out_pic_coded_height; /**< output picture height */
  u32 out_pic_stat;
};

/**
 * \struct struct DecPictureInfo
 * \brief Picture specific information.
 * \ingroup common_group
 */
struct DecPictureInfo {
  enum DecPicCodingType pic_coding_type; /**< Picture coding type */
  enum DecPicCodingType pic_coding_type_field; /**< Picture coding type for bottom field */
  u32 is_corrupted;             /**< Tells whether picture is corrupted */
  enum DecPictureFormat format; /**< Color format of the picture */
  struct DecTime time_code; /**< Time info(Only used in AVS, MP2 and MP4). */
  u32 cycles_per_mb;            /**< Avarage decoding time in cycles per mb */
  u32 pic_id;                   /**< Identifier for the picture to be decoded */
  u32 decode_id;               /**< Identifier for the picture to be decoded */
  u32 is_intra_frame;    /**< Indicates if Frame is an Intra Frame */
  u32 is_intra_frame_field;    /**< Indicates if Frame is an Intra Frame for bottom field */
  u32 is_golden_frame;   /**< Indicates if Frame is a Golden reference Frame */
  u32 field_picture; /**< Indicates if Frame is a field Frame */
  u32 top_field; /**< Indicates if this is a top field */
  u32 first_field; /**< Indicates if this is a first field */
  u32 repeat_first_field;
  u32 single_field;
  u32 output_other_field;
  u32 repeat_frame_count;
  u32 nbr_of_err_mbs;     /**< Number of concealed macroblocks in the frame  */
  u32 num_slice_rows;    /**< Number of luminance pixels rows in WebP output picture buffer.
                             If set to 0, whole picture ready.*/
  u32 last_slice;       /**< last slice flag  */
  u32 luma_stride;      /**< pixel row stride for luminance */
  u32 chroma_stride;    /**< pixel row stride for chrominance */

  /* H264 specific */
  u32 view_id;          /**< Identifies the view to which the output picture belongs */
};

/**
 * \struct struct DecPicture
 * \brief Structure to carry information about decoded pictures.
 * \ingroup common_group
 */
struct DecPicture {
  struct DecSequenceInfo sequence_info; /**< Sequence coding parameters used */
  struct DWLLinearMem luma;             /**< Buffer properties */
  struct DWLLinearMem chroma;           /**< Buffer properties : cb */
  struct DWLLinearMem chroma_cr;           /**< Buffer properties : cr */
  struct DWLLinearMem dmv;           /**< DMV Buffer properties */
  struct DWLLinearMem qp;           /**< QP Buffer properties */
  struct DWLLinearMem luma_table;           /**< Buffer properties *//*sunny add for tile status address*/
  struct DWLLinearMem chroma_table;           /**< Buffer properties *//*sunny add for tile status address*/
  struct DecPictureInfo picture_info;   /**< Picture specific parameters */
  struct DecSEIParameters sei_param; /**< SEI parameters of all formats */
  struct DWLLinearMem hdr;
  u32 pic_width; /**< picture width */
  u32 pic_height; /**< picture height */
  u32 pic_stride; /**< picture stride for luma */
  u32 pic_stride_ch; /**< picture stride for chroma */
  u32 chroma_format;
  u32 pp_enabled; /**< post process is available */

#ifdef SUPPORT_DEC400
    struct DWLLinearMem dec400_luma_table; /**< dec400 compress table for luma */
    struct DWLLinearMem dec400_chroma_table; /**< dec400 compress table for chroma */
#endif
	/*if sequence_info.is_interlaced==1*/
  u32 top_field_first;                  /**< 1-top field firs; 0-bottom field first */
  u32 fields_in_picture;                /**< how many fields in picture:0-no field;1-one field;2-two fields */
};

/**
 * \struct struct DecPicturePpu
 * \brief Structure to carry information about decoded pictures for 'n' pp channal.
 * \ingroup common_group
 */
struct DecPicturePpu {
  struct DecPicture pictures[DEC_MAX_OUT_COUNT];
};

/**
 * \struct struct DecBufferInfo
 * \brief A structure containing the reference buffer information
 * \ingroup common_group
 */
struct DecBufferInfo {
  u32 next_buf_size; /**< extra buffer size */
  u32 buf_num; /**< extra buffer number */
  u32 add_extra_ext_buf; /**< number of extra buffer has been added */
  struct DWLLinearMem buf_to_free; /**< the initialized buffer */
#ifdef ASIC_TRACE_SUPPORT
  u32 is_frame_buffer; /**< Indicates if the buffer is a frame buffer */
#endif
};

#define IS_EXTERNAL_BUFFER(config, type) (((config) >> (type)) & 1)

#endif /* DECTYPES_H */
