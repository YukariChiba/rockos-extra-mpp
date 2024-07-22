#ifndef __MPP_VENC_CFG_H__
#define __MPP_VENC_CFG_H__

#include "mpp_type.h"
#include "mpp_err.h"

typedef void* MppEncCfgPtr;

#ifdef __cplusplus
extern "C" {
#endif

MPP_RET mpp_enc_cfg_init(MppEncCfgPtr *cfg);
MPP_RET mpp_enc_cfg_deinit(MppEncCfgPtr cfg);

MPP_RET mpp_enc_cfg_set_s32(MppEncCfgPtr cfg, const char *name, ES_S32 val);
MPP_RET mpp_enc_cfg_set_u32(MppEncCfgPtr cfg, const char *name, ES_U32 val);
MPP_RET mpp_enc_cfg_set_s64(MppEncCfgPtr cfg, const char *name, ES_S64 val);
MPP_RET mpp_enc_cfg_set_u64(MppEncCfgPtr cfg, const char *name, ES_U64 val);
MPP_RET mpp_enc_cfg_set_ptr(MppEncCfgPtr cfg, const char *name, void *val);
MPP_RET mpp_enc_cfg_set_st(MppEncCfgPtr cfg, const char *name, void *val);

MPP_RET mpp_enc_cfg_get_s32(MppEncCfgPtr cfg, const char *name, ES_S32 *val);
MPP_RET mpp_enc_cfg_get_u32(MppEncCfgPtr cfg, const char *name, ES_U32 *val);
MPP_RET mpp_enc_cfg_get_s64(MppEncCfgPtr cfg, const char *name, ES_S64 *val);
MPP_RET mpp_enc_cfg_get_u64(MppEncCfgPtr cfg, const char *name, ES_U64 *val);
MPP_RET mpp_enc_cfg_get_ptr(MppEncCfgPtr cfg, const char *name, void **val);
MPP_RET mpp_enc_cfg_get_st(MppEncCfgPtr cfg, const char *name, void *val);

void mpp_enc_cfg_show(void);

#ifdef __cplusplus
}
#endif

#endif /*__MPP_VENC_CFG_H__*/
