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

#ifndef VCDECAPI_H
#define VCDECAPI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "basetype.h"
#include "dectypes.h"
#include "dwl.h"

/*------------------------------------------------------------------------------
VCDecAPI : used in decapi.c or testbench
------------------------------------------------------------------------------*/
/**
 * \brief Returns the decoder’s API version. \n
 * This function does not require the creation of a decoder instance. \n
 * \ingroup common_group
 * \param [in]     void               None.
 * \param [out]    DecApiVersion      struct DecApiVersion.
 */
struct DecApiVersion VCDecGetAPIVersion(void);

/**
 * \brief Returns the decoder’s hardware and software build information. \n
 * This function does not require the creation of a decoder instance. \n
 * \ingroup common_group
 * \param [in]     void           None.
 * \param [out]    DecSwHwBuild   struct DecSwHwBuild.
 */
struct DecSwHwBuild VCDecGetBuild(u32 client_type);

/**
 * \brief This function read number of HW cores available (Multicore specific). \n
 * This function does not require the creation of a decoder instance. \n
 * \ingroup common_group
 * \param [in]     void           None.
 * \param [out]    u32            The number of available hardware decoding cores..
 */
u32 VCDecMCGetCoreCount(void); /* new, special one */

/**
 * \brief Unpacks metadata elements for sequence header C from buffer, 
          when metadata is packed according to SMPTE VC-1 Standard Annex J 
          (VC1 specific). \n
 * This function does not require the creation of a decoder instance. \n
 * \ingroup common_group
 * \param [in]     p_buffer       Pointer to buffer containing packed metadata. Buffer 
                                  must contain at least 4 bytes.
 * \param [in]     buffer_size    Buffer size in bytes.
 * \param [in]     p_meta_data    Pointer to stream metadata container.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_METADATA_FAIL.
 */
enum DecRet VCDecUnpackMetaData(const u8 *p_buffer, u32 buffer_size,
                                struct DecMetaData* p_meta_data);

/**
 * \brief Initializes decoder software. \n
 * Function reserves memory for the decoder instance and calls xxxInit to initialize the instance data. \n
 * \ingroup common_group
 * \param [in]     inst           Pointer to the location where this function returns a decoder instance. 
                                  This instance is later passed to other decoder API functions.
 * \param [in]     dec_cfg        Pointer to the decoder initialization parameters.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_MEMFAIL, DEC_FORMAT_NOT_SUPPORTED.
 */
enum DecRet VCDecInit(const void** inst, struct DecInitConfig *init_config);

/**
 * \brief This function provides read access to decoder information. This function should not 
 * be called before VCDecDecode function has indicated that headers are ready. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     info           Pointer to an DecSequenceInfo structure where the decoder information will be returned.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_HDRS_NOT_RDY, DEC_NOT_INITIALIZED
 */
enum DecRet VCDecGetInfo(void* inst, struct DecSequenceInfo* info);

/**
 * \brief This function is called by the client to set the decoder configuration. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     config         Pointer to the decoder configure parameters (DecConfig).
 * \param [out]    DecRet         value: DEC_OK, DEC_NOT_INITIALIZED, DEC_PARAM_ERROR
 */
enum DecRet VCDecSetInfo(void* inst, struct DecConfig *config);

/**
 * \brief This function decodes one or more NAL units from the current stream. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     output         Pointer to the decoder output parameters.
 * \param [in]     param          Pointer to the decoder input parameters.
 * \param [out]    DecRet         value: DEC_PIC_DECODED, DEC_HDRS_RDY, DEC_PARAM_ERROR, DEC_STRM_ERROR, 
 *                                DEC_NOT_INITIALIZED, DEC_HW_BUS_ERROR, DEC_HW_TIMEOUT, DEC_MEMFAIL, 
 *                                DEC_STREAM_NOT_SUPPORTED, DEC_NONREF_PIC_SKIPPED, DEC_WAITING_FOR_BUFFER, 
 *                                DEC_ABORTED, DEC_STRM_PROCESSED, DEC_SYSTEM_ERROR, DEC_HW_RESERVED, 
 *                                DEC_PENDING_FLUSH, DEC_NO_DECODING_BUFFER, DEC_BUF_EMPTY
 */
enum DecRet VCDecDecode(void* inst, struct DecOutput* output, struct DecInputParameters* param);

/**
 * \brief Provides access to the next picture in display order. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     pic            Pointer to a DecPicturePpu structure which used to return the picture parameters. 
 *                                The picture parameters are valid only when the return value indicates that an 
 *                                output picture is available.
 * \param [out]    DecRet         value: DEC_OK, DEC_PIC_RDY, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED, 
 *                                DEC_END_OF_STREAM, DEC_ABORTED, DEC_FLUSHED
 */
enum DecRet VCDecNextPicture(void* inst, struct DecPicturePpu* pic);

/**
 * \brief This function informs the decoder that the client has finished processing the specific 
 * picture and releases the picture buffer for the decoder to process the next picture. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     pic            Pointer to a DecPicturePpu structure which used to return the picture parameters. 
 *                                The picture parameters are valid only when the return value indicates that an 
 *                                output picture is available.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet VCDecPictureConsumed(void* inst, struct DecPicturePpu *pic);

/**
 * \brief This function informs the decoder that it should not be expecting any more input stream and to 
 * finish decoding and outputting all the buffers that are currently pending in the component. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_INIT_FAIL
 */
enum DecRet VCDecEndOfStream(void* inst);

/**
 * \brief This function is called by the client to get the frame buffer information 
 * requested by the decoder, including the requested buffer size and buffer numbers. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     buf_info       Pointer to a DecBufferInfo structure which used to return the buffer info.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_WAITING_FOR_BUFFER
 */
enum DecRet VCDecGetBufferInfo(void *inst, struct DecBufferInfo *buf_info);

/**
 * \brief This function is called by the client to add an external frame buffer into the decoder. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     buf            Pointer to a DWLLinearMem structure.
 * \param [out]    DecRet         value: DEC_PARAM_ERROR, DEC_EXT_BUFFER_REJECTED, DEC_WAITING_FOR_BUFFER
 */
enum DecRet VCDecAddBuffer(void *inst, struct DWLLinearMem *buf);

/**
 * \brief This function is called by the client to indicates that 'n' extra frames in DPB are needed. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     n              Need 'n' extra frames in DPB.
 * \param [out]    DecRet         value: DEC_OK.
 */
enum DecRet VCDecUseExtraFrmBuffers(void* inst, u32 n);

/**
 * \brief Get last decoded picture if any available. No pictures are removed from output nor DPB buffers. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     pic            Pointer to a DecPicturePpu structure which used to return the picture parameters. 
 *                                The picture parameters are valid only when the return value indicates that an 
 *                                output picture is available.
 * \param [out]    DecRet         value: DEC_OK, DEC_PIC_RDY, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet VCDecPeek(void* inst, struct DecPicturePpu *pic);

/**
 * \brief This function is called by the client to abort the decoder. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet VCDecAbort(void* inst);

/**
 * \brief This function is called by the client to reset the decoder after the decoder is aborted. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet VCDecAbortAfter(void* inst);

/**
 * \brief This function is called by client to set the decoder output picture order as either 
 * decoding order or display order. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     no_reorder     Set the output model to no_reording.
 * \param [out]    void           None.
 */
void VCDecSetNoReorder(void* inst, u32 no_reorder);

/**
 * \brief Releases the decoder instance. \n
 * Function used to release instance data and frees the memory allocated for the instance. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit. 
 *                                The decoder instance to be released.
 * \param [out]    void           None.
 */
void VCDecRelease(void* inst);

/**
 * \brief This function is related to low latency mode and is called by the client to update 
 * the decoder stream length register at the specified address. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     last_flag      This flag is used to indicate if this packet is the last packet 
 *                                in the frame or stream.
 * \param [in]     strm_bus_addr  The bus address of the stream is used to record the how much stream 
 *                                data has been written to the input buffer.
 * \param [out]    void           None.
 */
void VCDecUpdateStrmInfoCtrl(void* inst, u32 last_flag, u32 strm_bus_addr);

/**
 * \brief This function is related to low latency mode and is called by the client to update 
 * input stream information. \n
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     info           Stream information data structure.
 * \param [out]    void           None.
 */
void VCDecUpdateStrm(void* inst, struct strmInfo info);

/**
 * \brief This function is used to get user data information (mpeg4 specific). \n
 * \ingroup common_group
 * \param [in]     inst                A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     param               Pointer to the input parameters.
 * \param [in]     user_data_config    Pointer to the user data configuration.
 * \param [out]    DecRet              value: DEC_OK, DEC_PARAM_ERROR.
 */
enum DecRet VCDecGetUserData(void* inst, struct DecInputParameters* param,
                             struct DecUserConf* user_data_config);

/**
 * \brief Provide external information to decoder. Used for some custom streams 
 *        which do not contain all necessary information in the elementary bitstream. 
 *        (mpeg4 specific). \n
 * \ingroup common_group
 * \param [in]     inst                A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     width               Frame width in pixels.
 * \param [in]     height              Frame height in pixels.
 * \param [out]    DecRet              value: DEC_OK, DEC_PARAM_ERROR.
 */
enum DecRet VCDecSetCustomInfo(void* inst, const u32 width, const u32 height);

#ifdef SUPPORT_ALLOCATE_CALLBACK
i32 VC_RegisterAllocateCallback(void *instance, void *userdata);
#endif

#ifdef __cplusplus
}
#endif

#endif // VCDECAPI_H
