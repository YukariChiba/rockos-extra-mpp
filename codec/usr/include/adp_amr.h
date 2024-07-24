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

#ifndef ADP_AMR_H_
#define ADP_AMR_H_

typedef struct {
    /**
     * NB:4750/5150/5900/6700/7400/7950/10200/12200 bps
     * WB:6600/8850/12650/14250/15850/18250/19850/23050/23850 bps
     */
    int32_t bit_rate;
    /**
     * 0:disable DTX; 1: enable DTX
     */
    int32_t dtx;
    int32_t is_wb;
} audio_amr_encoder_attr;

typedef struct {
    int32_t is_wb;
} audio_amr_decoder_attr;

void amrdec_init();
void amrenc_init();
#endif