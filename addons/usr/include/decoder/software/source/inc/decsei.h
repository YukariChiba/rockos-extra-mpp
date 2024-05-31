/*------------------------------------------------------------------------------
--       Copyright (c) 2015-2017, VeriSilicon Inc. All rights reserved        --
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

#ifndef COMMON_SEI_H_
#define COMMON_SEI_H_

#include "basetype.h"

#define MAX_DPB_SIZE 16
#define MAX_CPB_CNT 32
#define HEVC_MAX_NUM_SEQ_PARAM_SETS 16
#define MAX_PAYLOAD_NUM 64 /**< This limit will easily cover all sane streams. */
#define MAX_SLICE_SEGMENTS 600
#define PAYLOAD_BYTE_SIZE 1024
#define INI_MAX 2147483647 /**< maximum (signed) int value */


/**
 * \enum DecSEIStatus
 * \brief it's SEI_param status.
 * \ingroup common_group
 */
enum DecSEIStatus {
  SEI_UNUSED = 0, /**< the sei_param is available */
  SEI_CURRENT = 1, /**< the sei_param is in use */
  SEI_USED = 2 /**< the sei_param is not available */
};

/**
 * \struct DecSEIBuffer
 * \brief it's used for SEI message of variable length (The length of 
 * SEI message cannot be determined before parsing).
 * \ingroup common_group
 */
struct DecSEIBuffer {
  u8 *buffer; /**< buffer pointer */
  u32 buffer_size; /**< buffer size */
  u32 available_size; /**< available data size in buffer */
};

/*------------------------------------------------------------------------------
-- HEVC SEI DATA STRUCTURE
------------------------------------------------------------------------------*/
/**
 * \struct HevcBufPeriodParameters
 * \brief structure to store Buffering period SEI parameters
 * \ingroup hevc_group
 */
struct HevcBufPeriodParameters {
  u8 bp_seq_parameter_set_id;
  u8 irap_cpb_params_present_flag;
  u32 cpb_delay_offset;
  u32 dpb_delay_offset;
  u8 concatenation_flag;
  u32 au_cpb_removal_delay_delta_minus1;

  u32 nal_initial_cpb_removal_delay[MAX_CPB_CNT];
  u32 nal_initial_cpb_removal_offset[MAX_CPB_CNT];
  u32 nal_initial_alt_cpb_removal_delay[MAX_CPB_CNT];
  u32 nal_initial_alt_cpb_removal_offset[MAX_CPB_CNT];

  u32 vcl_initial_cpb_removal_delay[MAX_CPB_CNT];
  u32 vcl_initial_cpb_removal_offset[MAX_CPB_CNT];
  u32 vcl_initial_alt_cpb_removal_delay[MAX_CPB_CNT];
  u32 vcl_initial_alt_cpb_removal_offset[MAX_CPB_CNT];
};

/**
 * \struct HevcPicTimingParameters
 * \brief structure to store Picture timing SEI parameters
 * \ingroup hevc_group
 */
struct HevcPicTimingParameters {
  u8 pic_struct;
  u8 source_scan_type;
  u8 duplicate_flage;
  u32 au_cpb_removal_delay; /* minus1 */
  u32 pic_dpb_output_delay;
  u32 pic_dpb_output_du_delay;

  u16 num_decoding_units_minus1;
  u8  du_common_cpb_removal_delay_flag;
  u32 du_common_cpb_removal_delay_increment_minus1;
  u16 num_nalus_in_du_minus1[MAX_SLICE_SEGMENTS];
  u32 du_cpb_removal_delay_increment_minus1[MAX_SLICE_SEGMENTS];
};

/**
 * \struct HevcUserDataRegParameters
 * \brief structure to store User Data Registered SEI parameters
 * \ingroup hevc_group
 */
struct HevcUserDataRegParameters {
  u8 itu_t_t35_country_code[MAX_PAYLOAD_NUM];
  u8 itu_t_t35_country_code_extension_byte[MAX_PAYLOAD_NUM];

  /* PayloadByteInfo */
  struct DecSEIBuffer payload_byte;
  u32 payload_byte_length[MAX_PAYLOAD_NUM]; /**< length of each SEI */
  u32 userdatareg_counter; /**< num of User data registered SEI message in one frame */
};

/**
 * \struct HevcUserDataUnRegParameters
 * \brief structure to store User Data UnRegistered SEI parameters
 * \ingroup hevc_group
 */
struct HevcUserDataUnRegParameters {
  u8 uuid_iso_iec_11578[MAX_PAYLOAD_NUM][16]; /**< 128bit */

  /* PayloadByteInfo */
  struct DecSEIBuffer payload_byte;
  u32 payload_byte_length[MAX_PAYLOAD_NUM]; /**< length of each SEI */
  u32 userdataunreg_counter; /**< num of User data unregistered SEI message in one frame */
};

/**
 * \struct HevcRecoveryPointParameters
 * \brief structure to store Recovery Point SEI parameters
 * \ingroup hevc_group
 */
struct HevcRecoveryPointParameters {
  i16 recovery_poc_cnt;
  u8 exact_match_flag;
  u8 broken_link_flag;
};

/**
 * \struct HevcActiveParameterSet
 * \brief structure to store Active Parameter Sets SEI parameters
 * \ingroup hevc_group
 */
struct HevcActiveParameterSet {
  u8 active_video_parameter_set_id;
  u8 self_contained_cvs_flag;
  u8 no_parameter_set_update_flag;
  u8 num_sps_ids_minus1;
  u8 active_seq_parameter_set_id[HEVC_MAX_NUM_SEQ_PARAM_SETS];
};

/**
 * \struct HevcMasterDisParameters
 * \brief structure to store Mastering Display Colour Volume SEI parameters
 * \ingroup hevc_group
 */
struct HevcMasterDisParameters {
  u16 display_primaries_x[3];
  u16 display_primaries_y[3];
  u16 white_point_x;
  u16 white_point_y;
  u32 max_display_mastering_luminance;
  u32 min_display_mastering_luminance;
};

/**
 * \struct HevcLightLevelParameters
 * \brief structure to store Content Light Level Info SEI parameters
 * \ingroup hevc_group
 */
struct HevcLightLevelParameters {
  u16 max_content_light_level;
  u16 max_pic_average_light_level;
};

/**
 * \struct HevcSEIParameters
 * \brief structure to store all SEI parameters of HEVC
 * \ingroup hevc_group
 */
struct HevcSEIParameters {
  u32 bufperiod_present_flag; /**< value of 1 : buf_param decode successful */
  u32 pictiming_present_flag; /**< value of 1 : pic_param decode successful */
  u32 userdata_reg_present_flag; /**< value of 1 : userdatareg_param decode successful */
  u32 userdata_unreg_present_flag; /**< value of 1 : userdataunreg_param decode successful */
  u32 recovery_point_present_flag; /**< value of 1 : recovery_param decode successful */
  u32 active_ps_present_flag; /**< value of 1 : activeps_param decode successful */
  u32 mastering_display_present_flag; /**< value of 1 : masterdis_param decode successful */
  u32 lightlevel_present_flag; /**< value of 1 : light_param decode successful */
  u32 decode_id; /**< all the SEI message belong to picture with decode_id */
  enum DecSEIStatus sei_status; /**< current state of SEI_param */
  struct HevcBufPeriodParameters buf_param; /**< Buffering period SEI message */
  struct HevcPicTimingParameters pic_param; /**< Picture timing SEI message */
  struct HevcUserDataRegParameters userdatareg_param; /**< User data registered SEI message */
  struct HevcUserDataUnRegParameters userdataunreg_param; /**< User data unregistered SEI message */
  struct HevcRecoveryPointParameters recovery_param; /**< Recovery point SEI message */
  struct HevcActiveParameterSet activeps_param; /**< Active parameter sets SEI message */
  struct HevcMasterDisParameters masterdis_param; /**< Mastering display colour volume SEI message */
  struct HevcLightLevelParameters light_param; /**< Content light level information SEI message */
};


/*------------------------------------------------------------------------------
-- H264 SEI DATA STRUCTURE
------------------------------------------------------------------------------*/
/**
 * \struct H264BufPeriodParameters
 * \brief structure to store Buffering period SEI parameters
 * \ingroup h264_group
 */
struct H264BufPeriodParameters {
  u8 seq_parameter_set_id;
  u32 initial_cpb_removal_delay[MAX_CPB_CNT];
  u32 initial_cpb_removal_delay_offset[MAX_CPB_CNT];
};

/**
 * \struct H264PicTimingParameters
 * \brief structure to store Picture timing SEI parameters
 * \ingroup h264_group
 */
struct H264PicTimingParameters {
  u32 cpb_removal_delay;
  u32 dpb_output_delay;
  u8 pic_struct;
  u8 clock_timestamp_flag[3];
  u8 ct_type;
  u8 nuit_field_based_flag;
  u8 counting_type;
  u8 full_timestamp_flag;
  u8 discontinuity_flag;
  u8 cnt_dropped_flag;
  u8 n_frames;
  u8 seconds_value;
  u8 minutes_value;
  u8 hours_value;
  u8 seconds_flag;
  u8 minutes_flag;
  u8 hours_flag;
  i32 time_offset;
};

/**
 * \struct H264UserDataRegParameters
 * \brief structure to store User Data Registered SEI parameters
 * \ingroup h264_group
 */
struct H264UserDataRegParameters {
  u8 itu_t_t35_country_code[MAX_PAYLOAD_NUM];
  u8 itu_t_t35_country_code_extension_byte[MAX_PAYLOAD_NUM];

  /* PayloadByteInfo */
  struct DecSEIBuffer payload_byte;
  u32 payload_byte_length[MAX_PAYLOAD_NUM]; /**< length of each SEI */
  u32 userdatareg_counter; /**< num of User data registered SEI message in one frame */
};

/**
 * \struct H264UserDataUnRegParameters
 * \brief structure to store User Data UnRegistered SEI parameters
 * \ingroup h264_group
 */
struct H264UserDataUnRegParameters {
  u8 uuid_iso_iec_11578[MAX_PAYLOAD_NUM][16]; /**< 128bit */

  /* PayloadByteInfo */
  struct DecSEIBuffer payload_byte;
  u32 payload_byte_length[MAX_PAYLOAD_NUM]; /**< length of each SEI */
  u32 userdataunreg_counter; /**< num of User data unregistered SEI message in one frame */
};

/**
 * \struct H264RecoveryPointParameters
 * \brief structure to store Recovery Point SEI parameters
 * \ingroup h264_group
 */
struct H264RecoveryPointParameters {
  u16 recovery_frame_cnt;
  u8 exact_match_flag;
  u8 broken_link_flag;
  u8 changing_slice_group_idc;
};

/**
 * \struct H264MasterDisParameters
 * \brief structure to store Mastering Display Colour Volume SEI parameters
 * \ingroup h264_group
 */
struct H264MasterDisParameters {
    u16 display_primaries_x[3];
    u16 display_primaries_y[3];
    u16 white_point_x;
    u16 white_point_y;
    u32 max_display_mastering_luminance;
    u32 min_display_mastering_luminance;
};

/**
 * \struct H264LightLevelParameters
 * \brief structure to store Content Light Level Info SEI parameters
 * \ingroup h264_group
 */
struct H264LightLevelParameters {
  u16 max_content_light_level;
  u16 max_pic_average_light_level;
};

/**
 * \struct H264SEIParameters
 * \brief structure to store all SEI parameters of H264
 * \ingroup h264_group
 */
struct H264SEIParameters {
  u32 bufperiod_present_flag; /**< value of 1 : buf_param decode successful */
  u32 pictiming_present_flag; /**< value of 1 : pic_param decode successful */
  u32 userdata_reg_present_flag; /**< value of 1 : userdatareg_param decode successful */
  u32 userdata_unreg_present_flag; /**< value of 1 : userdataunreg_param decode successful */
  u32 recovery_point_present_flag; /**< value of 1 : recovery_param decode successful */
  u32 mastering_display_present_flag; /**< value of 1 : masterdis_param decode successful */
  u32 lightlevel_present_flag; /**< value of 1 : light_param decode successful */
  u32 decode_id; /**< all the SEI message belong to picture with decode_id */
  enum DecSEIStatus sei_status; /**< current state of SEI_param */
  struct H264BufPeriodParameters buf_param; /**< Buffering period SEI message */
  struct H264PicTimingParameters pic_param; /**< Picture timing SEI message */
  struct H264UserDataRegParameters userdatareg_param; /**< User data registered SEI message */
  struct H264UserDataUnRegParameters userdataunreg_param; /**< User data unregistered SEI message */
  struct H264RecoveryPointParameters recovery_param; /**< Recovery point SEI message */
  struct H264MasterDisParameters masterdis_param; /**< Mastering display colour volume SEI message */
  struct H264LightLevelParameters light_param; /**< Content light level information SEI message */
};

/*------------------------------------------------------------------------------
-- SEI DATA STRUCTURE OF ALL DECODER
------------------------------------------------------------------------------*/
/**
 * \struct DecSEIParameters
 * \brief structure to store SEI parameters of all formats
 * \ingroup common_group
 */
struct DecSEIParameters {
  struct HevcSEIParameters *hevc; /**< SEI parameters of HEVC */
  struct H264SEIParameters *h264; /**< SEI parameters of H264 */
};

#endif /* #ifdef COMMON_SEI_H_ */
