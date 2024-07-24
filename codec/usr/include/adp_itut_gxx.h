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

#ifndef ADP_ITUT_GXX_H_
#define ADP_ITUT_GXX_H_
typedef enum {
    ALAW,
    ULAW,
} G711_TYPE;

typedef struct {
    G711_TYPE type;
} audio_g711_attr;
typedef struct {
    int32_t bit_rate; /*64000/56000/48000  bps*/
} audio_g722_attr;

typedef struct {
    int32_t bit_rate; /*40000/32000/24000/16000  bps*/
} audio_g726_attr;

void itut_gxxdec_init();
void itut_gxxenc_init();
#endif