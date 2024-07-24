#ifndef __MPP_VDEC_CFG_H__
#define __MPP_VDEC_CFG_H__

#include "mpp_type.h"
#include "mpp_err.h"

typedef void *MppDecCfgPtr;

#ifdef __cplusplus
extern "C" {
#endif

MPP_RET mpp_dec_cfg_init(MppDecCfgPtr *cfg);
MPP_RET mpp_dec_cfg_deinit(MppDecCfgPtr *cfg);

MPP_RET mpp_dec_cfg_set_s32(MppDecCfgPtr cfg, const char *name, ES_S32 val);
MPP_RET mpp_dec_cfg_set_u32(MppDecCfgPtr cfg, const char *name, ES_U32 val);
MPP_RET mpp_dec_cfg_set_s64(MppDecCfgPtr cfg, const char *name, ES_S64 val);
MPP_RET mpp_dec_cfg_set_u64(MppDecCfgPtr cfg, const char *name, ES_U64 val);

MPP_RET mpp_dec_cfg_get_s32(MppDecCfgPtr cfg, const char *name, ES_S32 *val);
MPP_RET mpp_dec_cfg_get_u32(MppDecCfgPtr cfg, const char *name, ES_U32 *val);
MPP_RET mpp_dec_cfg_get_s64(MppDecCfgPtr cfg, const char *name, ES_S64 *val);
MPP_RET mpp_dec_cfg_get_u64(MppDecCfgPtr cfg, const char *name, ES_U64 *val);


#ifdef __cplusplus
}
#endif

#endif /*__MPP_VDEC_CMD_H__*/
