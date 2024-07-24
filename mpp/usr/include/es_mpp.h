#ifndef __ES_MPP_H__
#define __ES_MPP_H__

#include "mpp_err.h"
#include "mpp_type.h"
#include "es_mpp_cmd.h"

#define MPP_TIMEOUT_BLOCK       (-1L)
#define MPP_TIMEOUT_NON_BLOCK   (0L)

MPP_RET esmpp_create(MppCtxPtr *ctx, MppCtxType type, MppCodingType coding);
MPP_RET esmpp_destroy(MppCtxPtr* ctx);

MPP_RET esmpp_init(MppCtxPtr *ctx);
MPP_RET esmpp_deinit(MppCtxPtr *ctx);

MPP_RET esmpp_open(MppCtxPtr ctx);
MPP_RET esmpp_close(MppCtxPtr ctx);
MPP_RET esmpp_reset(MppCtxPtr ctx);

MPP_RET esmpp_put_frame(MppCtxPtr ctx, MppFramePtr frame);
MPP_RET esmpp_get_packet(MppCtxPtr ctx, MppPacketPtr *packet, ES_S32 timeout_us);
MPP_RET esmpp_put_packet(MppCtxPtr ctx, MppPacketPtr packet);
MPP_RET esmpp_get_frame(MppCtxPtr ctx, MppFramePtr *frame, ES_S32 timeout_us);
MPP_RET esmpp_control(MppCtxPtr ctx, MpiCmd cmd, MppParamPtr param);

#endif
