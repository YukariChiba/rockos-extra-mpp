#ifndef ES_DMA_MEM_H
#define ES_DMA_MEM_H

#define HEAP_FLAGS_SPRAM_FORCE_CONTIGUOUS	(1 << 0)

typedef enum _ES_DMA_TYPE{
    DMA_TYPE_SYS = 0,
    DMA_TYPE_CMA,
    DMA_TYPE_SYS_COHERENT,
    DMA_TYPE_MMZ_0,
    DMA_TYPE_MMZ_1,
    DMA_TYPE_SPRAM_0,
    DMA_TYPE_SPRAM_1,
    DMA_TYPE_WRAP,
    DMA_TYPE_MAX,
}es_dma_type;

typedef enum _ES_CACHE_TYPE{
    CACHED_BUF = 0,
    UNCACHED_BUF,
    LLC_BUF,
}es_cache_type;

typedef struct _ES_DMA_MEM{

	int dmabuf_fd;		    //dmabuf fd
	es_dma_type type;		//dma type
	void* vir_addr;			//virtual address
	size_t size;		//buffer size
    void * priv_data; 		//internal mutex
}es_dma_buf;

es_dma_buf *es_dma_alloc(es_dma_type dma_type, size_t size, es_cache_type cache_type, unsigned long heap_flags);            		//alloc dma memory. The memory is not initialized, and vir_addr is NULL.
int es_dma_free(es_dma_buf* es_dmabuf);                               		//free dma memory.

int es_dma_map(es_dma_buf* es_dmabuf, es_cache_type cache_typee);                                        // creates a new mapping in the virtual address space of the calling process, and set vir_addr.
int es_dma_unmap(es_dma_buf* es_dmabuf);                                      // unmap, clear vir_addr.

void es_dma_sync_start(es_dma_buf* es_dmabuf);                                 //sync_start, for cpu read/write. Must call es_dma_sync_end() after access.
void es_dma_sync_end(es_dma_buf* es_dmabuf);                                   //sync_end,for devices read/ write.

int es_dma_map_sync(es_dma_buf* es_dmabuf);                                    // map --- sync_start, set vir_addr. Must use es_dma_unmap_sync() after access.
int es_dma_unmap_sync(es_dma_buf* es_dmabuf);                                  // sync_end --- unmap, clear vir_addr.

int read_from_es_dma(es_dma_buf* src_dma,void *dst_addr, size_t len);      // map --- sync_start --- read --- sync_end --- unmap.
int write_to_es_dma( void *src_addr,es_dma_buf* dst_dma, size_t len);      // map --- sync_start --- write --- sync_end --- unmap.

es_dma_buf* es_dma_wrap(int fd, void* vir_addr, size_t size);            //alloc es_dma_buf with an existing fd
int es_dma_unwrap(es_dma_buf* es_dmabuf);                               //free the es_dma_buf without the fd

#endif