// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sonar_msgs:msg/ConfScal.idl
// generated code does not contain a copyright notice

#ifndef SONAR_MSGS__MSG__DETAIL__CONF_SCAL__STRUCT_H_
#define SONAR_MSGS__MSG__DETAIL__CONF_SCAL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/ConfScal in the package sonar_msgs.
typedef struct sonar_msgs__msg__ConfScal
{
  std_msgs__msg__Header header;
  float scalar_1;
  float confidence_1;
  float scalar_2;
  float confidence_2;
  float confidence_3;
  float scalar_3;
} sonar_msgs__msg__ConfScal;

// Struct for a sequence of sonar_msgs__msg__ConfScal.
typedef struct sonar_msgs__msg__ConfScal__Sequence
{
  sonar_msgs__msg__ConfScal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sonar_msgs__msg__ConfScal__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SONAR_MSGS__MSG__DETAIL__CONF_SCAL__STRUCT_H_
