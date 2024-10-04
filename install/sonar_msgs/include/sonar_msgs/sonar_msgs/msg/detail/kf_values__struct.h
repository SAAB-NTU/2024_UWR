// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sonar_msgs:msg/KfValues.idl
// generated code does not contain a copyright notice

#ifndef SONAR_MSGS__MSG__DETAIL__KF_VALUES__STRUCT_H_
#define SONAR_MSGS__MSG__DETAIL__KF_VALUES__STRUCT_H_

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

/// Struct defined in msg/KfValues in the package sonar_msgs.
typedef struct sonar_msgs__msg__KfValues
{
  std_msgs__msg__Header header;
  float k_d_1;
  float k_v_1;
  float k_d_2;
  float k_v_2;
  float k_d_3;
  float k_v_3;
} sonar_msgs__msg__KfValues;

// Struct for a sequence of sonar_msgs__msg__KfValues.
typedef struct sonar_msgs__msg__KfValues__Sequence
{
  sonar_msgs__msg__KfValues * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sonar_msgs__msg__KfValues__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SONAR_MSGS__MSG__DETAIL__KF_VALUES__STRUCT_H_
