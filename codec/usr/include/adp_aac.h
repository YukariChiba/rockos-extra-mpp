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

#ifndef _ADP_AAC_H_
#define _ADP_AAC_H_

#define FAAD_FMT_16BIT 1
#define FAAD_FMT_24BIT 2
#define FAAD_FMT_32BIT 3
#define FAAD_FMT_FLOAT 4
#define FAAD_FMT_FIXED FAAD_FMT_FLOAT
#define FAAD_FMT_DOUBLE 5

#define AOT_LC 2
#define AOT_HE 5
#define AOT_HEV2 29

typedef enum {
    AAC_TRANS_TYPE_ADTS = 0,
    AAC_TRANS_TYPE_LOAS = 1,
    AAC_TRANS_TYPE_LATM_MCP1 = 2,
    AAC_TRANS_TYPE_BUTT
} aac_trans_type;

typedef enum {
    AAC_TYPE_AACMAIN = 0,
    AAC_TYPE_AACLC = 1,
    AAC_TYPE_AACHE = 2,
    AAC_TYPE_AACLD = 3,
    AAC_TYPE_BUTT,
} aac_profile;

typedef struct {
    aac_profile profile;
    aac_trans_type trans_type;
    int32_t output_format;  // value FAAD_FMT_16BIT/FAAD_FMT_24BIT...
} audio_aacdecoder_attr;

typedef struct {
    int32_t bit_rate;     // bit rate: In range 8000 to 960000 ,default 64000
    int8_t aot;           // Audio object type, AOT_LC/AOT_HE/AOT_HEV2
    int8_t sbr;           // on:1 , off:0
    int8_t channels;      // default:2
    int8_t vbr;           // on:1 , off:0
    int32_t sample_rate;  // 44100/48000...
    int32_t afterburner;  // on:1 , off:0
} audio_aacenc_attr;

#ifdef __cplusplus
extern "C" {
#endif
void aacdec_init();

void aacenc_init();
#ifdef __cplusplus
}
#endif
#endif