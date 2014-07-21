/**\file */
#ifndef SLIC_DECLARATIONS_LatencyInteractionExperiment_H
#define SLIC_DECLARATIONS_LatencyInteractionExperiment_H
#include "MaxSLiCInterface.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define LatencyInteractionExperiment_DisplayTotalWidth (1360)
#define LatencyInteractionExperiment_PixelClock (143)
#define LatencyInteractionExperiment_DisplayHeight (720)
#define LatencyInteractionExperiment_DisplayTotalHeight (733)
#define LatencyInteractionExperiment_DisplayWidth (1280)
#define LatencyInteractionExperiment_DisplayStartY (10)
#define LatencyInteractionExperiment_DisplayStartX (56)


/*----------------------------------------------------------------------------*/
/*---------------------------- Interface default -----------------------------*/
/*----------------------------------------------------------------------------*/



/**
 * \brief Basic static function for the interface 'default'.
 * 
 * \param [in] inscalar_LatencyInteractionExperimentKernel_Enable Input scalar parameter "LatencyInteractionExperimentKernel.Enable".
 * \param [in] inscalar_LatencyInteractionExperimentKernel_HSyncPolarity Input scalar parameter "LatencyInteractionExperimentKernel.HSyncPolarity".
 * \param [in] inscalar_LatencyInteractionExperimentKernel_VSyncPolarity Input scalar parameter "LatencyInteractionExperimentKernel.VSyncPolarity".
 * \param [in] inscalar_mcp_kernel_frame_offset Input scalar parameter "mcp_kernel.frame_offset".
 * \param [in] instream_cpu_to_plane_0 Stream "cpu_to_plane_0".
 * \param [in] instream_size_cpu_to_plane_0 The size of the stream instream_cpu_to_plane_0 in bytes.
 * \param [in] instream_sprite_0_content Stream "sprite_0_content".
 * \param [in] instream_size_sprite_0_content The size of the stream instream_sprite_0_content in bytes.
 * \param [in] instream_sprite_0_positions Stream "sprite_0_positions".
 * \param [in] instream_size_sprite_0_positions The size of the stream instream_sprite_0_positions in bytes.
 * \param [in] instream_sprite_1_content Stream "sprite_1_content".
 * \param [in] instream_size_sprite_1_content The size of the stream instream_sprite_1_content in bytes.
 * \param [in] instream_sprite_1_positions Stream "sprite_1_positions".
 * \param [in] instream_size_sprite_1_positions The size of the stream instream_sprite_1_positions in bytes.
 * \param [in] instream_sprite_2_content Stream "sprite_2_content".
 * \param [in] instream_size_sprite_2_content The size of the stream instream_sprite_2_content in bytes.
 * \param [in] instream_sprite_2_positions Stream "sprite_2_positions".
 * \param [in] instream_size_sprite_2_positions The size of the stream instream_sprite_2_positions in bytes.
 * \param [out] outstream_plane_0_to_cpu Stream "plane_0_to_cpu".
 * \param [in] outstream_size_plane_0_to_cpu The size of the stream outstream_plane_0_to_cpu in bytes.
 * \param [in] lmem_address_plane_0_read Linear LMem control for "plane_0_read" stream: base address, in bytes.
 * \param [in] lmem_arr_size_plane_0_read Linear LMem control for "plane_0_read" stream: array size, in bytes.
 * \param [in] lmem_address_plane_0_write Linear LMem control for "plane_0_write" stream: base address, in bytes.
 * \param [in] lmem_arr_size_plane_0_write Linear LMem control for "plane_0_write" stream: array size, in bytes.
 */
void LatencyInteractionExperiment(
	uint64_t inscalar_LatencyInteractionExperimentKernel_Enable,
	uint64_t inscalar_LatencyInteractionExperimentKernel_HSyncPolarity,
	uint64_t inscalar_LatencyInteractionExperimentKernel_VSyncPolarity,
	uint64_t inscalar_mcp_kernel_frame_offset,
	const void *instream_cpu_to_plane_0,
	size_t instream_size_cpu_to_plane_0,
	const void *instream_sprite_0_content,
	size_t instream_size_sprite_0_content,
	const void *instream_sprite_0_positions,
	size_t instream_size_sprite_0_positions,
	const void *instream_sprite_1_content,
	size_t instream_size_sprite_1_content,
	const void *instream_sprite_1_positions,
	size_t instream_size_sprite_1_positions,
	const void *instream_sprite_2_content,
	size_t instream_size_sprite_2_content,
	const void *instream_sprite_2_positions,
	size_t instream_size_sprite_2_positions,
	void *outstream_plane_0_to_cpu,
	size_t outstream_size_plane_0_to_cpu,
	size_t lmem_address_plane_0_read,
	size_t lmem_arr_size_plane_0_read,
	size_t lmem_address_plane_0_write,
	size_t lmem_arr_size_plane_0_write);

/**
 * \brief Basic static non-blocking function for the interface 'default'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * 
 * \param [in] inscalar_LatencyInteractionExperimentKernel_Enable Input scalar parameter "LatencyInteractionExperimentKernel.Enable".
 * \param [in] inscalar_LatencyInteractionExperimentKernel_HSyncPolarity Input scalar parameter "LatencyInteractionExperimentKernel.HSyncPolarity".
 * \param [in] inscalar_LatencyInteractionExperimentKernel_VSyncPolarity Input scalar parameter "LatencyInteractionExperimentKernel.VSyncPolarity".
 * \param [in] inscalar_mcp_kernel_frame_offset Input scalar parameter "mcp_kernel.frame_offset".
 * \param [in] instream_cpu_to_plane_0 Stream "cpu_to_plane_0".
 * \param [in] instream_size_cpu_to_plane_0 The size of the stream instream_cpu_to_plane_0 in bytes.
 * \param [in] instream_sprite_0_content Stream "sprite_0_content".
 * \param [in] instream_size_sprite_0_content The size of the stream instream_sprite_0_content in bytes.
 * \param [in] instream_sprite_0_positions Stream "sprite_0_positions".
 * \param [in] instream_size_sprite_0_positions The size of the stream instream_sprite_0_positions in bytes.
 * \param [in] instream_sprite_1_content Stream "sprite_1_content".
 * \param [in] instream_size_sprite_1_content The size of the stream instream_sprite_1_content in bytes.
 * \param [in] instream_sprite_1_positions Stream "sprite_1_positions".
 * \param [in] instream_size_sprite_1_positions The size of the stream instream_sprite_1_positions in bytes.
 * \param [in] instream_sprite_2_content Stream "sprite_2_content".
 * \param [in] instream_size_sprite_2_content The size of the stream instream_sprite_2_content in bytes.
 * \param [in] instream_sprite_2_positions Stream "sprite_2_positions".
 * \param [in] instream_size_sprite_2_positions The size of the stream instream_sprite_2_positions in bytes.
 * \param [out] outstream_plane_0_to_cpu Stream "plane_0_to_cpu".
 * \param [in] outstream_size_plane_0_to_cpu The size of the stream outstream_plane_0_to_cpu in bytes.
 * \param [in] lmem_address_plane_0_read Linear LMem control for "plane_0_read" stream: base address, in bytes.
 * \param [in] lmem_arr_size_plane_0_read Linear LMem control for "plane_0_read" stream: array size, in bytes.
 * \param [in] lmem_address_plane_0_write Linear LMem control for "plane_0_write" stream: base address, in bytes.
 * \param [in] lmem_arr_size_plane_0_write Linear LMem control for "plane_0_write" stream: array size, in bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *LatencyInteractionExperiment_nonblock(
	uint64_t inscalar_LatencyInteractionExperimentKernel_Enable,
	uint64_t inscalar_LatencyInteractionExperimentKernel_HSyncPolarity,
	uint64_t inscalar_LatencyInteractionExperimentKernel_VSyncPolarity,
	uint64_t inscalar_mcp_kernel_frame_offset,
	const void *instream_cpu_to_plane_0,
	size_t instream_size_cpu_to_plane_0,
	const void *instream_sprite_0_content,
	size_t instream_size_sprite_0_content,
	const void *instream_sprite_0_positions,
	size_t instream_size_sprite_0_positions,
	const void *instream_sprite_1_content,
	size_t instream_size_sprite_1_content,
	const void *instream_sprite_1_positions,
	size_t instream_size_sprite_1_positions,
	const void *instream_sprite_2_content,
	size_t instream_size_sprite_2_content,
	const void *instream_sprite_2_positions,
	size_t instream_size_sprite_2_positions,
	void *outstream_plane_0_to_cpu,
	size_t outstream_size_plane_0_to_cpu,
	size_t lmem_address_plane_0_read,
	size_t lmem_arr_size_plane_0_read,
	size_t lmem_address_plane_0_write,
	size_t lmem_arr_size_plane_0_write);

/**
 * \brief Advanced static interface, structure for the engine interface 'default'
 * 
 */
typedef struct { 
	uint64_t inscalar_LatencyInteractionExperimentKernel_Enable; /**<  [in] Input scalar parameter "LatencyInteractionExperimentKernel.Enable". */
	uint64_t inscalar_LatencyInteractionExperimentKernel_HSyncPolarity; /**<  [in] Input scalar parameter "LatencyInteractionExperimentKernel.HSyncPolarity". */
	uint64_t inscalar_LatencyInteractionExperimentKernel_VSyncPolarity; /**<  [in] Input scalar parameter "LatencyInteractionExperimentKernel.VSyncPolarity". */
	uint64_t inscalar_mcp_kernel_frame_offset; /**<  [in] Input scalar parameter "mcp_kernel.frame_offset". */
	const void *instream_cpu_to_plane_0; /**<  [in] Stream "cpu_to_plane_0". */
	size_t instream_size_cpu_to_plane_0; /**<  [in] The size of the stream instream_cpu_to_plane_0 in bytes. */
	const void *instream_sprite_0_content; /**<  [in] Stream "sprite_0_content". */
	size_t instream_size_sprite_0_content; /**<  [in] The size of the stream instream_sprite_0_content in bytes. */
	const void *instream_sprite_0_positions; /**<  [in] Stream "sprite_0_positions". */
	size_t instream_size_sprite_0_positions; /**<  [in] The size of the stream instream_sprite_0_positions in bytes. */
	const void *instream_sprite_1_content; /**<  [in] Stream "sprite_1_content". */
	size_t instream_size_sprite_1_content; /**<  [in] The size of the stream instream_sprite_1_content in bytes. */
	const void *instream_sprite_1_positions; /**<  [in] Stream "sprite_1_positions". */
	size_t instream_size_sprite_1_positions; /**<  [in] The size of the stream instream_sprite_1_positions in bytes. */
	const void *instream_sprite_2_content; /**<  [in] Stream "sprite_2_content". */
	size_t instream_size_sprite_2_content; /**<  [in] The size of the stream instream_sprite_2_content in bytes. */
	const void *instream_sprite_2_positions; /**<  [in] Stream "sprite_2_positions". */
	size_t instream_size_sprite_2_positions; /**<  [in] The size of the stream instream_sprite_2_positions in bytes. */
	void *outstream_plane_0_to_cpu; /**<  [out] Stream "plane_0_to_cpu". */
	size_t outstream_size_plane_0_to_cpu; /**<  [in] The size of the stream outstream_plane_0_to_cpu in bytes. */
	size_t lmem_address_plane_0_read; /**<  [in] Linear LMem control for "plane_0_read" stream: base address, in bytes. */
	size_t lmem_arr_size_plane_0_read; /**<  [in] Linear LMem control for "plane_0_read" stream: array size, in bytes. */
	size_t lmem_address_plane_0_write; /**<  [in] Linear LMem control for "plane_0_write" stream: base address, in bytes. */
	size_t lmem_arr_size_plane_0_write; /**<  [in] Linear LMem control for "plane_0_write" stream: array size, in bytes. */
} LatencyInteractionExperiment_actions_t;

/**
 * \brief Advanced static function for the interface 'default'.
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void LatencyInteractionExperiment_run(
	max_engine_t *engine,
	LatencyInteractionExperiment_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'default'.
 *
 * Schedule the actions to run on the engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in] interface_actions Actions to be executed.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *LatencyInteractionExperiment_run_nonblock(
	max_engine_t *engine,
	LatencyInteractionExperiment_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'default'.
 * 
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void LatencyInteractionExperiment_run_group(max_group_t *group, LatencyInteractionExperiment_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule the actions to run on the first device available in the group and return immediately.
 * The status of the run must be checked with ::max_wait. 
 * Note that use of ::max_nowait is prohibited with non-blocking running on groups:
 * see the ::max_run_group_nonblock documentation for more explanation.
 *
 * \param [in] group Group to use.
 * \param [in] interface_actions Actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *LatencyInteractionExperiment_run_group_nonblock(max_group_t *group, LatencyInteractionExperiment_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'default'.
 * 
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void LatencyInteractionExperiment_run_array(max_engarray_t *engarray, LatencyInteractionExperiment_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule to run the array of actions on the array of engines, and return immediately.
 * The length of interface_actions must match the size of engarray.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * \param [in] engarray The array of devices to use.
 * \param [in] interface_actions The array of actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *LatencyInteractionExperiment_run_array_nonblock(max_engarray_t *engarray, LatencyInteractionExperiment_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* LatencyInteractionExperiment_convert(max_file_t *maxfile, LatencyInteractionExperiment_actions_t *interface_actions);

/**
 * \brief Initialise a maxfile.
 */
max_file_t* LatencyInteractionExperiment_init(void);

/* Error handling functions */
int LatencyInteractionExperiment_has_errors(void);
const char* LatencyInteractionExperiment_get_errors(void);
void LatencyInteractionExperiment_clear_errors(void);
/* Free statically allocated maxfile data */
void LatencyInteractionExperiment_free(void);
/* These are dummy functions for hardware builds. */
int LatencyInteractionExperiment_simulator_start(void);
int LatencyInteractionExperiment_simulator_stop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SLIC_DECLARATIONS_LatencyInteractionExperiment_H */

