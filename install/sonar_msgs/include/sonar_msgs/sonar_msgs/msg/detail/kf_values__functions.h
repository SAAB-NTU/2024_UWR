// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from sonar_msgs:msg/KfValues.idl
// generated code does not contain a copyright notice

#ifndef SONAR_MSGS__MSG__DETAIL__KF_VALUES__FUNCTIONS_H_
#define SONAR_MSGS__MSG__DETAIL__KF_VALUES__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "sonar_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "sonar_msgs/msg/detail/kf_values__struct.h"

/// Initialize msg/KfValues message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * sonar_msgs__msg__KfValues
 * )) before or use
 * sonar_msgs__msg__KfValues__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
bool
sonar_msgs__msg__KfValues__init(sonar_msgs__msg__KfValues * msg);

/// Finalize msg/KfValues message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
void
sonar_msgs__msg__KfValues__fini(sonar_msgs__msg__KfValues * msg);

/// Create msg/KfValues message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * sonar_msgs__msg__KfValues__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
sonar_msgs__msg__KfValues *
sonar_msgs__msg__KfValues__create();

/// Destroy msg/KfValues message.
/**
 * It calls
 * sonar_msgs__msg__KfValues__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
void
sonar_msgs__msg__KfValues__destroy(sonar_msgs__msg__KfValues * msg);

/// Check for msg/KfValues message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
bool
sonar_msgs__msg__KfValues__are_equal(const sonar_msgs__msg__KfValues * lhs, const sonar_msgs__msg__KfValues * rhs);

/// Copy a msg/KfValues message.
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
sonar_msgs__msg__KfValues__copy(
  const sonar_msgs__msg__KfValues * input,
  sonar_msgs__msg__KfValues * output);

/// Initialize array of msg/KfValues messages.
/**
 * It allocates the memory for the number of elements and calls
 * sonar_msgs__msg__KfValues__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
bool
sonar_msgs__msg__KfValues__Sequence__init(sonar_msgs__msg__KfValues__Sequence * array, size_t size);

/// Finalize array of msg/KfValues messages.
/**
 * It calls
 * sonar_msgs__msg__KfValues__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
void
sonar_msgs__msg__KfValues__Sequence__fini(sonar_msgs__msg__KfValues__Sequence * array);

/// Create array of msg/KfValues messages.
/**
 * It allocates the memory for the array and calls
 * sonar_msgs__msg__KfValues__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
sonar_msgs__msg__KfValues__Sequence *
sonar_msgs__msg__KfValues__Sequence__create(size_t size);

/// Destroy array of msg/KfValues messages.
/**
 * It calls
 * sonar_msgs__msg__KfValues__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
void
sonar_msgs__msg__KfValues__Sequence__destroy(sonar_msgs__msg__KfValues__Sequence * array);

/// Check for msg/KfValues message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_sonar_msgs
bool
sonar_msgs__msg__KfValues__Sequence__are_equal(const sonar_msgs__msg__KfValues__Sequence * lhs, const sonar_msgs__msg__KfValues__Sequence * rhs);

/// Copy an array of msg/KfValues messages.
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
sonar_msgs__msg__KfValues__Sequence__copy(
  const sonar_msgs__msg__KfValues__Sequence * input,
  sonar_msgs__msg__KfValues__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // SONAR_MSGS__MSG__DETAIL__KF_VALUES__FUNCTIONS_H_
