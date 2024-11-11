// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sonar_msgs:msg/ThreeSonarDepth.idl
// generated code does not contain a copyright notice

#ifndef SONAR_MSGS__MSG__DETAIL__THREE_SONAR_DEPTH__STRUCT_H_
#define SONAR_MSGS__MSG__DETAIL__THREE_SONAR_DEPTH__STRUCT_H_

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

/// Struct defined in msg/ThreeSonarDepth in the package sonar_msgs.
typedef struct sonar_msgs__msg__ThreeSonarDepth
{
  std_msgs__msg__Header header;
  float distance_1;
  float confidence_1;
  float distance_2;
  float confidence_2;
  float distance_3;
  float confidence_3;
  float depth;
  float altitude;
  float pressure;
} sonar_msgs__msg__ThreeSonarDepth;

// Struct for a sequence of sonar_msgs__msg__ThreeSonarDepth.
typedef struct sonar_msgs__msg__ThreeSonarDepth__Sequence
{
  sonar_msgs__msg__ThreeSonarDepth * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sonar_msgs__msg__ThreeSonarDepth__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SONAR_MSGS__MSG__DETAIL__THREE_SONAR_DEPTH__STRUCT_H_
