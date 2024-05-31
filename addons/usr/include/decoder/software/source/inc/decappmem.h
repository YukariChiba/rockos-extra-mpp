/**
 * dec_appmem.h
 * Support sys memory alloc&free callback interface; by using these callback app could impl memory alloc/free itself.
 * APP must make sure the thread safty.
 */

#ifndef DEC_APPMEM_H
#define DEC_APPMEM_H

#include "dwl.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Callback function used as allocate memory from app layer.
 * \param [in] ctx Specify the user context from app layer.
 * \param [in] size Specify the target memory size.
 * \param [inout] info Store the memory information:
 * \param [out] virtualAddress in info specify the virtual address.
 * \param [out] busAddress in info specify the bus address.
 * \param [inout] size in info specify the memory size.
 * \param [in] mem_type in info specify the memory type. APP layer should check if the memory is used as dbp:
 *                      info->mem_type & DWL_MEM_TYPE_DPB
 * \param [out] priv in info to store the private data by app layer.
 */
typedef i32 (*DWLMallocLinearCallBackFunc)(const void *ctx, u32 size, struct DWLLinearMem *info);

/**
 * \brief Callback function used as free memory from app layer.
 * \param [in] ctx Specify the user context from app layer.
 * \param [in] info Store the memory information:
 * \param [out] virtualAddress in info specify the virtual address.
 * \param [out] busAddress in info specify the bus address.
 * \param [inout] size in info specify the memory size.
 * \param [in] mem_type in info specify the memory type. APP layer should check if the memory is used as dbp:
 *                      info->mem_type & DWL_MEM_TYPE_DPB
 * \param [in] priv in info to store the private data by app layer.
 */
typedef void (*DWLFreeLinearCallBackFunc)(const void *ctx, struct DWLLinearMem *info);

/**
 * Set the callback function and user context of app memory.
 * \param [in] inst Specify the dwl instance.
 * \param [in] memalloc Specify the callback function of "memory allocation".
 * \param [in] memfree Specify the callback function of "memory free".
 * \param [in] ctx Specify the user context.
 * \return DWL_OK initialize successfully;
 * \return DWL_ERROR initialize failed.
 */
i32 DWLSetAppMemCb(void *instance, DWLMallocLinearCallBackFunc memalloc, DWLFreeLinearCallBackFunc memfree, void *ctx);

#ifdef __cplusplus
}
#endif

#endif /* end of DEC_APPMEM_H */
