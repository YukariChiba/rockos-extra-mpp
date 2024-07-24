// Copyright (c) 2023 ESWIN Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ES_CODEC_SDK_H
#define ES_CODEC_SDK_H
#include <stdint.h>
#include "CodecTypes.h"

#ifdef __cplusplus
extern "C" {
#endif
/*-------------------------- Encoding Functions ---------------------------*/
/**
 * @brief Initializes the audio encoder.
 * This function initializes the audio encoder module. It prepares the necessary resources
 * and configurations for audio encoding.
 *
 * @return Returns an error code indicating the success or failure of the initialization.
 * A value of 0 indicates success, while a non-zero value represents an error.
 */
int32_t es_aenc_init();

/**
 * @brief Creates an audio encoder and binds it to a specific channel.
 *
 * @param chn The channel number to which the audio encoder is bound.
 * @param type The audio encoding format.
 * @param attr Pointer to the audio encoder attribute.
 *
 * @return Returns the handle of the audio encoder.
 */
int32_t es_aenc_create(uint32_t chn, es_codec_type type, void *attr);

/**
 * @brief Encodes audio data for frames bound to a specific channel.
 *
 * @param chn The channel number to which the audio data to be encoded is bound.
 * @param input Pointer to the audio data to encode.
 * @param input_size The size of the audio data to encode.
 * @param output Pointer to the buffer where the encoded audio data will be stored.
 * @param out_size Pointer to the size of the encoded audio data.
 *
 * @return Returns the status of execution.
 */
int32_t es_aenc_encode_frame(uint32_t chn, uint8_t *input, int32_t input_size, uint8_t *output, uint32_t *out_size);

/**
 * @brief Destroys an audio encoder bound to a specific channel.
 *
 * @param chn The channel number of the audio encoder to destroy.
 *
 * @return Returns the status of execution.
 */
int32_t es_aenc_destroy(uint32_t chn);

/**
 * @brief Registers a new set of audio encoding format decoding functions with the system.
 *
 * @param func Pointer to the structure containing function pointers and attributes for
 * the new audio encoding format.
 *
 * @return Returns the status of execution.
 */
int32_t es_aenc_register(const es_aenc_func *func);

/**
 * @brief Unregisters a previously registered audio encoding format decoding function from the system.
 *
 * @param type The audio encoding format to unregister.
 *
 * @return Returns the status of execution.
 */
int32_t es_aenc_unregister(es_codec_type type);

/**
 * @brief Get frame info for audio encode.
 *
 * This function is used to parse the length and offset of an audio frame.
 * Given the input data and input length, the function analyzes the input data
 * to determine the length and offset of the audio frame.
 *
 * @param chn The channel number.
 * @param input The input data buffer.
 * @param input_size The length of the input data.
 * @param frame_info A pointer to an struct es_frame_info (incldue frame_size, sample rate etc).
 *
 * @return Returns the status of execution. On success, it returns 0. Non-zero values indicate
 * failure or an error occurred during execution.
 */
int32_t es_aenc_parse_packets(uint32_t chn, uint8_t *input, int32_t input_size, es_frame_info *frame_info);

/*-------------------------- Decoding Functions ---------------------------*/
/**
 * @brief Initializes the audio decoder.
 * This function initializes the audio decoder module. It prepares the necessary resources
 * and configurations for audio decoding.
 *
 * @return Returns an error code indicating the success or failure of the initialization.
 * A value of 0 indicates success, while a non-zero value represents an error.
 */
int32_t es_adec_init();

/**
 * @brief Creates an audio decoder and binds it to a specific channel.
 *
 * @param chn The channel number to which the audio decoder is bound.
 * @param type The audio decoding format.
 * @param attr Pointer to the audio decoder attribute.
 *
 * @return Returns the handle of the audio decoder.
 */
int32_t es_adec_create(uint32_t chn, es_codec_type type, void *attr);

/**
 * @brief Decodes audio data for frames bound to a specific channel.
 *
 * @param chn The channel number to which the audio data to be decoded is bound.
 * @param input Pointer to the audio data to decode.
 * @param input_size The size of the audio data to decode.
 * @param output Pointer to the buffer where the decoded audio data will be stored.
 * @param out_size Pointer to the size of the decoded audio data.
 *
 * @return Returns the status of execution.
 */
int32_t es_adec_decode_stream(uint32_t chn, uint8_t *input, int32_t input_size, uint8_t *output, uint32_t *out_size);

/**
 * @brief Updates the buffer for the specified channel.
 *
 * This function is typically called after the `es_adec_frame` function has been used to
 * decode audio data and the caller has retrieved the decoded audio data from the output buffer.
 * After reading the decoded data from the output buffer, the caller must call this function to
 * update the buffer so that it can be used again to store newly processed audio data.
 *
 * @param chn The channel number of the buffer to update.
 *
 * @return Returns the status of execution.
 */
int32_t es_update_buffer(uint32_t chn);

/**
 * @brief Destroys an audio decoder bound to a specific channel.
 *
 * @param chn The channel number of the audio decoder to destroy.
 *
 * @return Returns the status of execution.
 */
int32_t es_adec_destroy(uint32_t chn);

/**
 * @brief Registers a new set of audio decoding format decoding functions with the system.
 *
 * @param func Pointer to the structure containing function pointers and attributes for the new audio
 * decoding format.
 *
 * @return Returns the status of execution.
 */
int32_t es_adec_register(const es_adec_func *func);

/**
 * @brief Unregisters a previously registered audio decoding format decoding function from the system.
 *
 * @param type The audio decoding format to unregister.
 *
 * @return Returns the status of execution.
 */
int32_t es_adec_unregister(es_codec_type type);

/**
 * @brief Get frame info for audio decode.
 *
 * This function is used to parse the length and offset of an audio frame.
 * Given the input data and input length, the function analyzes the input data
 * to determine the length and offset of the audio frame.
 *
 * @param chn The channel number.
 * @param input The input data buffer.
 * @param input_size The length of the input data.
 * @param frame_info A pointer to an struct es_frame_info (incldue frame_size, sample rate etc).
 *
 * @return Returns the status of execution. On success, it returns 0. Non-zero values indicate
 * failure or an error occurred during execution.
 */
int32_t es_adec_parse_packets(uint32_t chn, uint8_t *input, int32_t input_size, es_frame_info *frame_info);

#ifdef __cplusplus
}
#endif

#endif  // ES_CODEC_SDK_H