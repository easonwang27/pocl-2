
#ifndef VX_API_

#define VX_API_

#include <inttypes.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*func_t)(void *);

void vx_spawnWarps(unsigned numWarps, unsigned numThreads, func_t func_ptr , void * args);

// struct context_t {

//   unsigned num_groups[3];            // use {2, 1, 1} for vecadd

//   unsigned global_offset[3];         // use {0, 0, 0} for vecadd

//   unsigned local_size[3];            // use {2, 1, 1} for vecadd

//   unsigned char *printf_buffer;  // zero for now

//   unsigned *printf_buffer_position;  // initialized to zero

//   unsigned printf_buffer_capacity;   // zero for now

//   unsigned work_dim;                 // use ‘1’ for vecadd

// };

/* The default work-group function prototype as generated by Workgroup.cc. */
typedef void (*vx_pocl_workgroup_func) (uint8_t * /* args */,
				     uint8_t * /* pocl_context */,
				     uint32_t /* group_x */,
				     uint32_t /* group_y */,
				     uint32_t /* group_z */);

void pocl_spawn(struct pocl_context * ctx, const void * pfn, void * arguments);

#ifdef __cplusplus
}
#endif


#endif