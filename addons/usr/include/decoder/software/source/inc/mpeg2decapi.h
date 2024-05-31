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

#ifndef __MPEG2DECAPI_H__
#define __MPEG2DECAPI_H__

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

/* decoder output picture format */
typedef enum {
  MPEG2DEC_SEMIPLANAR_YUV420 = 0x020001,
  MPEG2DEC_TILED_YUV420 = 0x020002
} Mpeg2DecOutFormat;

/* Decoder instance */
typedef void *Mpeg2DecInst;

/* Input structure */
typedef struct {
  u8 *stream;         /* Pointer to stream to be decoded              */
  addr_t stream_bus_address;   /* DMA bus address of the input stream */
  u32 data_len;         /* Number of bytes to be decoded                */
  u32 pic_id;
  enum DecSkipFrameMode skip_frame; /* Skip some frames when decoding. */
} Mpeg2DecInput;

/* stream info filled by Mpeg2DecGetInfo */
typedef struct {
  u32 frame_width;
  u32 frame_height;
  u32 coded_width;
  u32 coded_height;
  u32 profile_and_level_indication;
  u32 display_aspect_ratio;
  u32 stream_format;
  u32 video_format;
  u32 video_range;      /* ??? only [0-255] */
  u32 colour_primaries;
  u32 transfer_characteristics;
  u32 matrix_coefficients;
  u32 colour_description_present_flag;
  u32 interlaced_sequence;
  enum DecDpbMode dpb_mode;         /* DPB mode; frame, or field interlaced */
  u32 pic_buff_size;
  u32 multi_buff_pp_size;
  Mpeg2DecOutFormat output_format;
} Mpeg2DecInfo;

typedef struct {
  u32 key_picture;
  u32 pic_id;
  u32 decode_id;
  u32 pic_coding_type[2];
  u32 interlaced;
  u32 field_picture;
  u32 top_field;
  u32 first_field;
  u32 repeat_first_field;
  u32 single_field;
  u32 output_other_field;
  u32 repeat_frame_count;
  u32 number_of_err_mbs;
  u32 cycles_per_mb;   /**< Avarage cycle count per macroblock */
  enum DecDpbMode dpb_mode;         /* DPB mode; frame, or field interlaced */
  struct DecTime time_code;
  struct Mpeg2OutputInfo {
    u8 *output_picture;
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
} Mpeg2DecPicture;

/* Version information */
typedef struct {
  u32 major;           /* API major version */
  u32 minor;           /* API minor version */

} Mpeg2DecApiVersion;

typedef struct DecSwHwBuild  Mpeg2DecBuild;

struct Mpeg2DecConfig {
  enum DecErrorHandling error_handling;
  enum DecDpbFlags dpb_flags;
  u32 use_adaptive_buffers; // When sequence changes, if old output buffers (number/size) are sufficient for new sequence,
  // old buffers will be used instead of reallocating output buffer.
  u32 guard_size;       // The minimum difference between minimum buffers number and allocated buffers number
  // that will force to return HDRS_RDY even buffers number/size are sufficient
  // for new sequence.
  DecPicAlignment align;
  u32 num_frame_buffers;
  PpUnitConfig ppu_config[DEC_MAX_PPU_COUNT];
};

/*------------------------------------------------------------------------------
    Prototypes of Decoder API functions
------------------------------------------------------------------------------*/

Mpeg2DecApiVersion Mpeg2DecGetAPIVersion(void);

Mpeg2DecBuild Mpeg2DecGetBuild(void);

enum DecRet Mpeg2DecInit(Mpeg2DecInst * dec_inst, const void *dwl, struct Mpeg2DecConfig *dec_cfg);

enum DecRet Mpeg2DecDecode(Mpeg2DecInst dec_inst,
                           Mpeg2DecInput * input,
                           struct DecOutput * output);

enum DecRet Mpeg2DecGetInfo(Mpeg2DecInst dec_inst, Mpeg2DecInfo * dec_info);

enum DecRet Mpeg2DecNextPicture(Mpeg2DecInst dec_inst, Mpeg2DecPicture * picture);

enum DecRet Mpeg2DecPictureConsumed(Mpeg2DecInst dec_inst,
                                    Mpeg2DecPicture *picture);

enum DecRet Mpeg2DecEndOfStream(Mpeg2DecInst dec_inst);
enum DecRet Mpeg2DecAbort(Mpeg2DecInst dec_inst);
enum DecRet Mpeg2DecAbortAfter(Mpeg2DecInst dec_inst);

void Mpeg2DecRelease(Mpeg2DecInst dec_inst);

enum DecRet Mpeg2DecPeek(Mpeg2DecInst dec_inst, Mpeg2DecPicture * picture);
enum DecRet Mpeg2DecGetBufferInfo(Mpeg2DecInst dec_inst, struct DecBufferInfo *mem_info);

enum DecRet Mpeg2DecAddBuffer(Mpeg2DecInst dec_inst, struct DWLLinearMem *info);
enum DecRet Mpeg2DecSetInfo(Mpeg2DecInst dec_inst, struct Mpeg2DecConfig *dec_cfg);
/*------------------------------------------------------------------------------
    Prototype of the API trace funtion. Traces all API entries and returns.
    This must be implemented by the application using the decoder API!
    Argument:
        string - trace message, a null terminated string
------------------------------------------------------------------------------*/
void Mpeg2DecTrace(const char *string);

#ifdef __cplusplus
}
#endif

#endif                       /* __MPEG2DECAPI_H__ */
