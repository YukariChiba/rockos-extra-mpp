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

#ifndef __MP4DECAPI_H__
#define __MP4DECAPI_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "basetype.h"
#include "decapicommon.h"
#include "dectypes.h"
#include "dwl.h"

/*------------------------------------------------------------------------------
    API type definitions
------------------------------------------------------------------------------*/

typedef enum MP4DecStrmFmt_ {
  MP4DEC_MPEG4,
  MP4DEC_SORENSON,
  MP4DEC_CUSTOM_1
} MP4DecStrmFmt;

/* decoder output picture format */
typedef enum MP4DecOutFormat_ {
  MP4DEC_SEMIPLANAR_YUV420 = 0x020001,
  MP4DEC_TILED_YUV420 = 0x020002
} MP4DecOutFormat;

/* Decoder instance */
typedef void *MP4DecInst;

/* Input structure */
typedef struct MP4DecInput_ {
  const u8 *stream;       /* Pointer to stream to be decoded  */
  addr_t stream_bus_address; /* DMA bus address of the input stream */
  u32 data_len;        /* Number of bytes to be decoded                */
  u32 enable_deblock;  /* Enable deblocking of post processed picture  */
  /* NOTE: This parameter is not valid if the decoder
   * is not used in pipeline mode with the post
   * processor i.e. it has no effect on the
   * decoding process */

  u32 pic_id;
  enum DecSkipFrameMode skip_frame; /* Skip some frames when decoding. */
} MP4DecInput;

/* stream info filled by MP4DecGetInfo */
typedef struct MP4DecInfo_ {
  u32 frame_width;
  u32 frame_height;
  u32 coded_width;
  u32 coded_height;
  u32 stream_format;
  u32 profile_and_level_indication;
  u32 video_format;
  u32 video_range;
  u32 par_width;
  u32 par_height;
  u32 user_data_voslen;
  u32 user_data_visolen;
  u32 user_data_vollen;
  u32 user_data_govlen;
  u32 interlaced_sequence;
  enum DecDpbMode dpb_mode;         /* DPB mode; frame, or field interlaced */
  u32 pic_buff_size;
  u32 multi_buff_pp_size;
  MP4DecOutFormat output_format;
  u32 gmc_support;
} MP4DecInfo;

/* Version information */
typedef struct MP4DecVersion_ {
  u32 major;    /* API major version */
  u32 minor;    /* API minor version */
} MP4DecApiVersion;

typedef struct DecSwHwBuild  MP4DecBuild;

typedef struct {
  u32 key_picture;
  u32 pic_id;
  u32 decode_id;
  u32 pic_coding_type;
  u32 interlaced;
  u32 field_picture;
  u32 top_field;
  u32 nbr_of_err_mbs;
  u32 cycles_per_mb;   /**< Avarage cycle count per macroblock */
  struct DecTime time_code;
  struct MP4OutputInfo {
    const u8 *output_picture;
    addr_t output_picture_bus_address;
    u32 frame_width;
    u32 frame_height;
    u32 coded_width;
    u32 coded_height;
    u32 pic_stride;
    u32 pic_stride_ch;
    enum DecPictureFormat output_format;
    struct DecCropParams crop_params; /**< Cropping parameters for the picture */
#ifdef SUPPORT_DEC400
    struct DWLLinearMem dec400_luma_table;           /**< Buffer properties *//*sunny add for tile status address*/
    struct DWLLinearMem dec400_chroma_table;
#endif
  } pictures[DEC_MAX_OUT_COUNT];
} MP4DecPicture;

struct MP4DecConfig {
  enum DecErrorHandling error_handling;
  enum DecDpbFlags dpb_flags;
  u32 use_adaptive_buffers; // When sequence changes, if old output buffers (number/size) are sufficient for new sequence,
  // old buffers will be used instead of reallocating output buffer.
  u32 guard_size;       // The minimum difference between minimum buffers number and allocated buffers number
  // that will force to return HDRS_RDY even buffers number/size are sufficient
  // for new sequence.
  DecPicAlignment align;
  u32 rlc_mode;
  u32 num_frame_buffers;
  MP4DecStrmFmt strm_fmt;
  PpUnitConfig ppu_config[DEC_MAX_PPU_COUNT];
};
/*------------------------------------------------------------------------------
    Prototypes of Decoder API functions
------------------------------------------------------------------------------*/

MP4DecApiVersion MP4DecGetAPIVersion(void);

MP4DecBuild MP4DecGetBuild(void);

enum DecRet MP4DecInit(MP4DecInst * dec_inst, const void *dwl, struct MP4DecConfig *dec_cfg);

enum DecRet MP4DecDecode(MP4DecInst dec_inst,
                       const MP4DecInput *input,
                       struct DecOutput *output);

enum DecRet MP4DecSetCustomInfo(MP4DecInst * dec_inst,
                        const u32 width,
                        const u32 height );

enum DecRet MP4DecGetInfo(MP4DecInst dec_inst,
                        MP4DecInfo  * dec_info);

enum DecRet MP4DecGetUserData(MP4DecInst dec_inst,
                            const MP4DecInput* input,
                            struct DecUserConf* p_user_data_config);

enum DecRet MP4DecNextPicture(MP4DecInst dec_inst, MP4DecPicture *picture);

enum DecRet MP4DecPictureConsumed(MP4DecInst    dec_inst,
                                MP4DecPicture *picture);

enum DecRet MP4DecEndOfStream(MP4DecInst dec_inst);

void  MP4DecRelease(MP4DecInst dec_inst);

enum DecRet MP4DecPeek(MP4DecInst        dec_inst,
                     MP4DecPicture    *picture);

enum DecRet MP4DecGetBufferInfo(MP4DecInst dec_inst, struct DecBufferInfo *mem_info);

enum DecRet MP4DecAddBuffer(MP4DecInst dec_inst, struct DWLLinearMem *info);

enum DecRet MP4DecSetInfo(MP4DecInst dec_inst, struct MP4DecConfig *dec_cfg);

enum DecRet MP4DecAbort(MP4DecInst dec_inst);

enum DecRet MP4DecAbortAfter(MP4DecInst dec_inst);

/*------------------------------------------------------------------------------
    Prototype of the API trace funtion. Traces all API entries and returns.
    This must be implemented by the application using the decoder API!
    Argument:
        string - trace message, a null terminated string
------------------------------------------------------------------------------*/
void MP4DecTrace(const char *string);

#ifdef __cplusplus
}
#endif

#endif /* __MP4DECAPI_H__ */

