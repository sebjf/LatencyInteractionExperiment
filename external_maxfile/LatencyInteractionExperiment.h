/**\file */
#ifndef SLIC_DECLARATIONS_LatencyInteractionExperiment_H
#define SLIC_DECLARATIONS_LatencyInteractionExperiment_H
#include "MaxSLiCInterface.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define LatencyInteractionExperiment_DisplayTotalWidth (1688)
#define LatencyInteractionExperiment_DisplayHeight (1024)
#define LatencyInteractionExperiment_DisplayTotalHeight (1066)
#define LatencyInteractionExperiment_DisplayWidth (1280)


/*----------------------------------------------------------------------------*/
/*---------------------------- Interface default -----------------------------*/
/*----------------------------------------------------------------------------*/




/**
 * \brief Basic static function for the interface 'default'.
 * 
 * \param [in] inscalar_MaxVideoSignalKernel_HSyncPolarity Input scalar parameter "MaxVideoSignalKernel.HSyncPolarity".
 * \param [in] inscalar_MaxVideoSignalKernel_VSyncPolarity Input scalar parameter "MaxVideoSignalKernel.VSyncPolarity".
 * \param [in] instream_cpu_to_plane_0 Stream "cpu_to_plane_0".
 * \param [in] instream_size_cpu_to_plane_0 The size of the stream instream_cpu_to_plane_0 in bytes.
 * \param [in] instream_frame_offset_stream Stream "frame_offset_stream".
 * \param [in] instream_size_frame_offset_stream The size of the stream instream_frame_offset_stream in bytes.
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
 * \param [in] lmem_address_plane_0_write Linear LMem control for "plane_0_write" stream: base address, in bytes.
 * \param [in] lmem_arr_size_plane_0_write Linear LMem control for "plane_0_write" stream: array size, in bytes.
 */
void LatencyInteractionExperiment(
	uint64_t inscalar_MaxVideoSignalKernel_HSyncPolarity,
	uint64_t inscalar_MaxVideoSignalKernel_VSyncPolarity,
	const void *instream_cpu_to_plane_0,
	size_t instream_size_cpu_to_plane_0,
	const void *instream_frame_offset_stream,
	size_t instream_size_frame_offset_stream,
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
 * \param [in] inscalar_MaxVideoSignalKernel_HSyncPolarity Input scalar parameter "MaxVideoSignalKernel.HSyncPolarity".
 * \param [in] inscalar_MaxVideoSignalKernel_VSyncPolarity Input scalar parameter "MaxVideoSignalKernel.VSyncPolarity".
 * \param [in] instream_cpu_to_plane_0 Stream "cpu_to_plane_0".
 * \param [in] instream_size_cpu_to_plane_0 The size of the stream instream_cpu_to_plane_0 in bytes.
 * \param [in] instream_frame_offset_stream Stream "frame_offset_stream".
 * \param [in] instream_size_frame_offset_stream The size of the stream instream_frame_offset_stream in bytes.
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
 * \param [in] lmem_address_plane_0_write Linear LMem control for "plane_0_write" stream: base address, in bytes.
 * \param [in] lmem_arr_size_plane_0_write Linear LMem control for "plane_0_write" stream: array size, in bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *LatencyInteractionExperiment_nonblock(
	uint64_t inscalar_MaxVideoSignalKernel_HSyncPolarity,
	uint64_t inscalar_MaxVideoSignalKernel_VSyncPolarity,
	const void *instream_cpu_to_plane_0,
	size_t instream_size_cpu_to_plane_0,
	const void *instream_frame_offset_stream,
	size_t instream_size_frame_offset_stream,
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
	size_t lmem_address_plane_0_write,
	size_t lmem_arr_size_plane_0_write);

/**
 * \brief Advanced static interface, structure for the engine interface 'default'
 * 
 */
typedef struct { 
	uint64_t inscalar_MaxVideoSignalKernel_HSyncPolarity; /**<  [in] Input scalar parameter "MaxVideoSignalKernel.HSyncPolarity". */
	uint64_t inscalar_MaxVideoSignalKernel_VSyncPolarity; /**<  [in] Input scalar parameter "MaxVideoSignalKernel.VSyncPolarity". */
	const void *instream_cpu_to_plane_0; /**<  [in] Stream "cpu_to_plane_0". */
	size_t instream_size_cpu_to_plane_0; /**<  [in] The size of the stream instream_cpu_to_plane_0 in bytes. */
	const void *instream_frame_offset_stream; /**<  [in] Stream "frame_offset_stream". */
	size_t instream_size_frame_offset_stream; /**<  [in] The size of the stream instream_frame_offset_stream in bytes. */
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

