// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from sonar_msgs:msg/KfValues.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "sonar_msgs/msg/detail/kf_values__rosidl_typesupport_introspection_c.h"
#include "sonar_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "sonar_msgs/msg/detail/kf_values__functions.h"
#include "sonar_msgs/msg/detail/kf_values__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void sonar_msgs__msg__KfValues__rosidl_typesupport_introspection_c__KfValues_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  sonar_msgs__msg__KfValues__init(message_memory);
}

void sonar_msgs__msg__KfValues__rosidl_typesupport_introspection_c__KfValues_fini_function(void * message_memory)
{
  sonar_msgs__msg__KfValues__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember sonar_msgs__msg__KfValues__rosidl_typesupport_introspection_c__KfValues_message_member_array[7] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sonar_msgs__msg__KfValues, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "k_d_1",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sonar_msgs__msg__KfValues, k_d_1),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "k_v_1",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sonar_msgs__msg__KfValues, k_v_1),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "k_d_2",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sonar_msgs__msg__KfValues, k_d_2),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "k_v_2",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sonar_msgs__msg__KfValues, k_v_2),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "k_d_3",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sonar_msgs__msg__KfValues, k_d_3),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "k_v_3",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sonar_msgs__msg__KfValues, k_v_3),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers sonar_msgs__msg__KfValues__rosidl_typesupport_introspection_c__KfValues_message_members = {
  "sonar_msgs__msg",  // message namespace
  "KfValues",  // message name
  7,  // number of fields
  sizeof(sonar_msgs__msg__KfValues),
  sonar_msgs__msg__KfValues__rosidl_typesupport_introspection_c__KfValues_message_member_array,  // message members
  sonar_msgs__msg__KfValues__rosidl_typesupport_introspection_c__KfValues_init_function,  // function to initialize message memory (memory has to be allocated)
  sonar_msgs__msg__KfValues__rosidl_typesupport_introspection_c__KfValues_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t sonar_msgs__msg__KfValues__rosidl_typesupport_introspection_c__KfValues_message_type_support_handle = {
  0,
  &sonar_msgs__msg__KfValues__rosidl_typesupport_introspection_c__KfValues_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_sonar_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sonar_msgs, msg, KfValues)() {
  sonar_msgs__msg__KfValues__rosidl_typesupport_introspection_c__KfValues_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!sonar_msgs__msg__KfValues__rosidl_typesupport_introspection_c__KfValues_message_type_support_handle.typesupport_identifier) {
    sonar_msgs__msg__KfValues__rosidl_typesupport_introspection_c__KfValues_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &sonar_msgs__msg__KfValues__rosidl_typesupport_introspection_c__KfValues_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif