// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sonar_msgs:msg/KfValues.idl
// generated code does not contain a copyright notice
#include "sonar_msgs/msg/detail/kf_values__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
sonar_msgs__msg__KfValues__init(sonar_msgs__msg__KfValues * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    sonar_msgs__msg__KfValues__fini(msg);
    return false;
  }
  // k_d_1
  // k_v_1
  // k_d_2
  // k_v_2
  // k_d_3
  // k_v_3
  return true;
}

void
sonar_msgs__msg__KfValues__fini(sonar_msgs__msg__KfValues * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // k_d_1
  // k_v_1
  // k_d_2
  // k_v_2
  // k_d_3
  // k_v_3
}

bool
sonar_msgs__msg__KfValues__are_equal(const sonar_msgs__msg__KfValues * lhs, const sonar_msgs__msg__KfValues * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // k_d_1
  if (lhs->k_d_1 != rhs->k_d_1) {
    return false;
  }
  // k_v_1
  if (lhs->k_v_1 != rhs->k_v_1) {
    return false;
  }
  // k_d_2
  if (lhs->k_d_2 != rhs->k_d_2) {
    return false;
  }
  // k_v_2
  if (lhs->k_v_2 != rhs->k_v_2) {
    return false;
  }
  // k_d_3
  if (lhs->k_d_3 != rhs->k_d_3) {
    return false;
  }
  // k_v_3
  if (lhs->k_v_3 != rhs->k_v_3) {
    return false;
  }
  return true;
}

bool
sonar_msgs__msg__KfValues__copy(
  const sonar_msgs__msg__KfValues * input,
  sonar_msgs__msg__KfValues * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // k_d_1
  output->k_d_1 = input->k_d_1;
  // k_v_1
  output->k_v_1 = input->k_v_1;
  // k_d_2
  output->k_d_2 = input->k_d_2;
  // k_v_2
  output->k_v_2 = input->k_v_2;
  // k_d_3
  output->k_d_3 = input->k_d_3;
  // k_v_3
  output->k_v_3 = input->k_v_3;
  return true;
}

sonar_msgs__msg__KfValues *
sonar_msgs__msg__KfValues__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sonar_msgs__msg__KfValues * msg = (sonar_msgs__msg__KfValues *)allocator.allocate(sizeof(sonar_msgs__msg__KfValues), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sonar_msgs__msg__KfValues));
  bool success = sonar_msgs__msg__KfValues__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sonar_msgs__msg__KfValues__destroy(sonar_msgs__msg__KfValues * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sonar_msgs__msg__KfValues__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sonar_msgs__msg__KfValues__Sequence__init(sonar_msgs__msg__KfValues__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sonar_msgs__msg__KfValues * data = NULL;

  if (size) {
    data = (sonar_msgs__msg__KfValues *)allocator.zero_allocate(size, sizeof(sonar_msgs__msg__KfValues), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sonar_msgs__msg__KfValues__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sonar_msgs__msg__KfValues__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
sonar_msgs__msg__KfValues__Sequence__fini(sonar_msgs__msg__KfValues__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      sonar_msgs__msg__KfValues__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

sonar_msgs__msg__KfValues__Sequence *
sonar_msgs__msg__KfValues__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sonar_msgs__msg__KfValues__Sequence * array = (sonar_msgs__msg__KfValues__Sequence *)allocator.allocate(sizeof(sonar_msgs__msg__KfValues__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sonar_msgs__msg__KfValues__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sonar_msgs__msg__KfValues__Sequence__destroy(sonar_msgs__msg__KfValues__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sonar_msgs__msg__KfValues__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sonar_msgs__msg__KfValues__Sequence__are_equal(const sonar_msgs__msg__KfValues__Sequence * lhs, const sonar_msgs__msg__KfValues__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sonar_msgs__msg__KfValues__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sonar_msgs__msg__KfValues__Sequence__copy(
  const sonar_msgs__msg__KfValues__Sequence * input,
  sonar_msgs__msg__KfValues__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sonar_msgs__msg__KfValues);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sonar_msgs__msg__KfValues * data =
      (sonar_msgs__msg__KfValues *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sonar_msgs__msg__KfValues__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sonar_msgs__msg__KfValues__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sonar_msgs__msg__KfValues__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
