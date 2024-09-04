#ifndef __MPP_PACKET_H__
#define __MPP_PACKET_H__

#include "mpp_meta.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * MppPacketPtr interface
 *
 * mpp_packet_init = mpp_packet_new + mpp_packet_set_data + mpp_packet_set_size
 * mpp_packet_copy_init = mpp_packet_init + memcpy
 */
MPP_RET mpp_packet_new(MppPacketPtr *packet);
MPP_RET mpp_packet_init(MppPacketPtr *packet, void *data, size_t size);
MPP_RET mpp_packet_init_with_buffer(MppPacketPtr *packet, MppBufferPtr buffer);
MPP_RET mpp_packet_copy_init(MppPacketPtr *packet, const MppPacketPtr src);
MPP_RET mpp_packet_deinit(MppPacketPtr *packet);

/*
 * data   : ( R/W ) start address of the whole packet memory
 * size   : ( R/W ) total size of the whole packet memory
 * pos    : ( R/W ) current access position of the whole packet memory, used for buffer read/write
 * length : ( R/W ) the rest length from current position to end of buffer
 *                  NOTE: normally length is updated only by set_pos,
 *                        so set length must be used carefully for special usage
 */
void    mpp_packet_set_data(MppPacketPtr packet, void *data);
void    mpp_packet_set_size(MppPacketPtr packet, size_t size);
void    mpp_packet_set_pos(MppPacketPtr packet, void *pos);
void    mpp_packet_set_length(MppPacketPtr packet, size_t size);

void*   mpp_packet_get_data(const MppPacketPtr packet);
void*   mpp_packet_get_pos(const MppPacketPtr packet);
size_t  mpp_packet_get_size(const MppPacketPtr packet);
size_t  mpp_packet_get_length(const MppPacketPtr packet);


void    mpp_packet_set_pts(MppPacketPtr packet, ES_S64 pts);
ES_S64  mpp_packet_get_pts(const MppPacketPtr packet);
void    mpp_packet_set_dts(MppPacketPtr packet, ES_S64 dts);
ES_S64  mpp_packet_get_dts(const MppPacketPtr packet);
void    mpp_packet_set_reordered_opaque(MppPacketPtr packet, ES_S64 reordered_opaque);
ES_S64  mpp_packet_get_reordered_opaque(const MppPacketPtr packet);

void    mpp_packet_set_flag(MppPacketPtr packet, ES_U32 flag);
ES_U32  mpp_packet_get_flag(const MppPacketPtr packet);

MPP_RET mpp_packet_set_eos(MppPacketPtr packet);
MPP_RET mpp_packet_clr_eos(MppPacketPtr packet);
ES_U32  mpp_packet_get_eos(MppPacketPtr packet);
MPP_RET mpp_packet_set_extra_data(MppPacketPtr packet);

void        mpp_packet_set_buffer(MppPacketPtr packet, MppBufferPtr buffer);
MppBufferPtr   mpp_packet_get_buffer(const MppPacketPtr packet);

/*
 * data access interface
 */
MPP_RET mpp_packet_read(MppPacketPtr packet, size_t offset, void *data, size_t size);
MPP_RET mpp_packet_write(MppPacketPtr packet, size_t offset, void *data, size_t size);

/*
 * meta data access interface
 */
ES_S32  mpp_packet_has_meta(const MppPacketPtr packet);
MppMetaPtr mpp_packet_get_meta(const MppPacketPtr packet);

/*
 * multi packet sequence interface for slice/split encoding/decoding
 * partition - the packet is a part of a while image
 * soi - Start Of Image
 * eoi - End Of Image
 */
ES_U32  mpp_packet_is_partition(const MppPacketPtr packet);
ES_U32  mpp_packet_is_soi(const MppPacketPtr packet);
ES_U32  mpp_packet_is_eoi(const MppPacketPtr packet);

/*
 * packet segement pack info for
 * segment number - number of segment
 * segment info   - base address of segment info
 */
typedef struct MppPktSeg_t MppPktSeg;

struct MppPktSeg_t {
    ES_S32          index;
    ES_S32          type;
    ES_U32          offset;
    ES_U32          len;
    const MppPktSeg *next;
};

ES_U32 mpp_packet_get_segment_nb(const MppPacketPtr packet);
const MppPktSeg *mpp_packet_get_segment_info(const MppPacketPtr packet);

#ifdef __cplusplus
}
#endif

#endif /*__MPP_PACKET_H__*/
