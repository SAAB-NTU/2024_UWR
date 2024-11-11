// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from sonar_msgs:msg/ConfScal.idl
// generated code does not contain a copyright notice

#ifndef SONAR_MSGS__MSG__DETAIL__CONF_SCAL__FUNCTIONS_H_
#define SONAR_MSGS__MSG__DETAIL__CONF_SCAL__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "sonar_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "sonar_msgs/msg/detail/conf_scal__struct.h"

/// Initialize msg/ConfScal message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * sonar_msgs__msg__ConfScal
 * )) before or use
 * sonar_msgs__msg__ConfScal__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
bool
sonar_msgs__msg__ConfScal__init(sonar_msgs__msg__ConfScal * msg);

/// Finalize msg/ConfScal message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
void
sonar_msgs__msg__ConfScal__fini(sonar_msgs__msg__ConfScal * msg);

/// Create msg/ConfScal message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * sonar_msgs__msg__ConfScal__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
sonar_msgs__msg__ConfScal *
sonar_msgs__msg__ConfScal__create();

/// Destroy msg/ConfScal message.
/**
 * It calls
 * sonar_msgs__msg__ConfScal__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
void
sonar_msgs__msg__ConfScal__destroy(sonar_msgs__msg__ConfScal * msg);

/// Check for msg/ConfScal message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
bool
sonar_msgs__msg__ConfScal__are_equal(const sonar_msgs__msg__ConfScal * lhs, const sonar_msgs__msg__ConfScal * rhs);

/// Copy a msg/ConfScal message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
bool
sonar_msgs__msg__ConfScal__copy(
  const sonar_msgs__msg__ConfScal * input,
  sonar_msgs__msg__ConfScal * output);

/// Initialize array of msg/ConfScal messages.
/**
 * It allocates the memory for the number of elements and calls
 * sonar_msgs__msg__ConfScal__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
bool
sonar_msgs__msg__ConfScal__Sequence__init(sonar_msgs__msg__ConfScal__Sequence * array, size_t size);

/// Finalize array of msg/ConfScal messages.
/**
 * It calls
 * sonar_msgs__msg__ConfScal__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
void
sonar_msgs__msg__ConfScal__Sequence__fini(sonar_msgs__msg__ConfScal__Sequence * array);

/// Create array of msg/ConfScal messages.
/**
 * It allocates the memory for the array and calls
 * sonar_msgs__msg__ConfScal__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
sonar_msgs__msg__ConfScal__Sequence *
sonar_msgs__msg__ConfScal__Sequence__create(size_t size);

/// Destroy array of msg/ConfScal messages.
/**
 * It calls
 * sonar_msgs__msg__ConfScal__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
void
sonar_msgs__msg__ConfScal__Sequence__destroy(sonar_msgs__msg__ConfScal__Sequence * array);

/// Check for msg/ConfScal message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
bool
sonar_msgs__msg__ConfScal__Sequence__are_equal(const sonar_msgs__msg__ConfScal__Sequence * lhs, const sonar_msgs__msg__ConfScal__Sequence * rhs);

/// Copy an array of msg/ConfScal messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
bool
sonar_msgs__msg__ConfScal__Sequence__copy(
  const sonar_msgs__msg__ConfScal__Sequence * input,
  sonar_msgs__msg__ConfScal__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // SONAR_MSGS__MSG__DETAIL__CONF_SCAL__FUNCTIONS_H_
