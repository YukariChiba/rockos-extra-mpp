#ifndef __MPP_TDE_API_H__
#define __MPP_TDE_API_H__

#include "mpp_tde_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Complex process
 * @param src_frm The input source image buffer.
 * @param dst_frm The output destination image buffer.
 * @param pat_frm The pattern image buffer.
 * @param src_rect The rectangle on the source image that needs to be processed.
 * @param dst_rect The rectangle on the destination image that needs to be processed.
 * @param pat_rect The rectangle on the pattern image that needs to be processed.
 * @param usage The image processing usage.
 * @return MPP_SUCCESS on success, others as error.
 *
 * @note Pattern is not support currently.
 */
MPP_RET es_tde_complex_process(const MppFramePtr src_frm,
                               const MppFramePtr dst_frm,
                               const MppFramePtr pat_frm,
                               const RECT_S *src_rect,
                               const RECT_S *dst_rect,
                               const RECT_S *pat_rect,
                               ES_S32 usage);

/**
 * @brief Fill rectangle array
 * @param dst_frm The destination image.
 * @param rect_info_array The rectangle information arrays on the destination image that needs to be filled with color.
 * @param array_size The size of rectangle information array.
 * @return MPP_SUCCESS on success, others as error.
 *
 * @note When the thickness is negative values, or zero, or bigger than the width/height of rectangle, that means to
 * draw a full filled rectangle.
 */
MPP_RET es_tde_fill_rect_array(const MppFramePtr dst_frm, const TdeRectInfo *rect_info_array, ES_U32 array_size);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
