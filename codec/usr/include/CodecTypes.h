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

#ifndef CODEC_TYPES_H
#define CODEC_TYPES_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RET_SUCCESS 0

typedef enum {
    ERR_CODEC_SUCCESS = 0,
    ERR_CODEC_MEMORY,
    ERR_CODEC_PARAM,
    ERR_CODEC_EEXIST,
    ERR_CODEC_NOEXIST,
    ERR_CODEC_DECODEERR,
    ERR_CODEC_ENCODEERR,
} ERR_CODEC_CODE;

// For codec api types
typedef enum {
    AAC,
    MP3,
    G711,
    G722,
    G726,
    AMR,
    ADPCMA,
    MP2L2,
    UNKNOW
} es_codec_type;

typedef struct {
    uint8_t *input;
    int32_t input_size;
    int32_t frame_size;
    int32_t decoded_size;
    int32_t frame_off;
    uint32_t sample_rate;
    int16_t channels;
    int16_t bit_depth;
} es_frame_info;

typedef struct {
    es_codec_type en_type;
    int32_t (*pfnOpenEncoder)(void *pEncoderAttr, void **ppEncoder);
    int32_t (*pfnEncodeFrm)(void *pEncoder, const uint8_t *input, uint32_t input_size, uint8_t *output,
                            uint32_t *out_size);
    int32_t (*pfnGetFrmInfo)(void *pEncoder, void *pInfo);
    int32_t (*pfnCloseEncoder)(void *pEncoder);
} es_aenc_func;

typedef struct {
    es_codec_type de_type;
    int32_t (*pfnOpenDecoder)(void *pDecoderAttr, void **ppDecoder);
    int32_t (*pfnDecodeFrm)(void *pDecoder, const uint8_t *input_buffer, int32_t input_size, uint8_t *out_buffer,
                            uint32_t *out_size);
    int32_t (*pfnGetFrmInfo)(void *pDecoder, void *pInfo);
    int32_t (*pfnCloseDecoder)(void *pDecoder);
    int32_t (*pfnResetDecoder)(void *pDecoder);
} es_adec_func;

// For codec processor types.
typedef struct {
    es_codec_type type;
    uint32_t ptNumOfPerFrame;
    uint32_t bufferCount;
    void *aencAttr;
} es_aenc_attrs;

typedef enum {
    ES_ADEC_MODE_PACK = 0,
    ES_ADEC_MODE_SSTREAM,
    ES_ADEC_MODE_BUTT
} es_adec_mode;

typedef struct {
    es_codec_type type;
    uint32_t bufferCount;
    es_adec_mode mode;
    void *adecAttr;
} es_adec_attrs;

#ifdef __cplusplus
}
#endif

#endif  // CODEC_TYPES_H