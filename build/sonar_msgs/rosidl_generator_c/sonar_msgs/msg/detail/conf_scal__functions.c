// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sonar_msgs:msg/ConfScal.idl
// generated code does not contain a copyright notice
#include "sonar_msgs/msg/detail/conf_scal__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
sonar_msgs__msg__ConfScal__init(sonar_msgs__msg__ConfScal * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    sonar_msgs__msg__ConfScal__fini(msg);
    return false;
  }
  // scalar_1
  // confidence_1
  // scalar_2
  // confidence_2
  // confidence_3
  // scalar_3
  return true;
}

void
sonar_msgs__msg__ConfScal__fini(sonar_msgs__msg__ConfScal * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // scalar_1
  // confidence_1
  // scalar_2
  // confidence_2
  // confidence_3
  // scalar_3
}

bool
sonar_msgs__msg__ConfScal__are_equal(const sonar_msgs__msg__ConfScal * lhs, const sonar_msgs__msg__ConfScal * rhs)
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
  // scalar_1
  if (lhs->scalar_1 != rhs->scalar_1) {
    return false;
  }
  // confidence_1
  if (lhs->confidence_1 != rhs->confidence_1) {
    return false;
  }
  // scalar_2
  if (lhs->scalar_2 != rhs->scalar_2) {
    return false;
  }
  // confidence_2
  if (lhs->confidence_2 != rhs->confidence_2) {
    return false;
  }
  // confidence_3
  if (lhs->confidence_3 != rhs->confidence_3) {
    return false;
  }
  // scalar_3
  if (lhs->scalar_3 != rhs->scalar_3) {
    return false;
  }
  return true;
}

bool
sonar_msgs__msg__ConfScal__copy(
  const sonar_msgs__msg__ConfScal * input,
  sonar_msgs__msg__ConfScal * output)
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
  // scalar_1
  output->scalar_1 = input->scalar_1;
  // confidence_1
  output->confidence_1 = input->confidence_1;
  // scalar_2
  output->scalar_2 = input->scalar_2;
  // confidence_2
  output->confidence_2 = input->confidence_2;
  // confidence_3
  output->confidence_3 = input->confidence_3;
  // scalar_3
  output->scalar_3 = input->scalar_3;
  return true;
}

sonar_msgs__msg__ConfScal *
sonar_msgs__msg__ConfScal__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sonar_msgs__msg__ConfScal * msg = (sonar_msgs__msg__ConfScal *)allocator.allocate(sizeof(sonar_msgs__msg__ConfScal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sonar_msgs__msg__ConfScal));
  bool success = sonar_msgs__msg__ConfScal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sonar_msgs__msg__ConfScal__destroy(sonar_msgs__msg__ConfScal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sonar_msgs__msg__ConfScal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sonar_msgs__msg__ConfScal__Sequence__init(sonar_msgs__msg__ConfScal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sonar_msgs__msg__ConfScal * data = NULL;

  if (size) {
    data = (sonar_msgs__msg__ConfScal *)allocator.zero_allocate(size, sizeof(sonar_msgs__msg__ConfScal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sonar_msgs__msg__ConfScal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sonar_msgs__msg__ConfScal__fini(&data[i - 1]);
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
sonar_msgs__msg__ConfScal__Sequence__fini(sonar_msgs__msg__ConfScal__Sequence * array)
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
      sonar_msgs__msg__ConfScal__fini(&array->data[i]);
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

sonar_msgs__msg__ConfScal__Sequence *
sonar_msgs__msg__ConfScal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sonar_msgs__msg__ConfScal__Sequence * array = (sonar_msgs__msg__ConfScal__Sequence *)allocator.allocate(sizeof(sonar_msgs__msg__ConfScal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sonar_msgs__msg__ConfScal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sonar_msgs__msg__ConfScal__Sequence__destroy(sonar_msgs__msg__ConfScal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sonar_msgs__msg__ConfScal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sonar_msgs__msg__ConfScal__Sequence__are_equal(const sonar_msgs__msg__ConfScal__Sequence * lhs, const sonar_msgs__msg__ConfScal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sonar_msgs__msg__ConfScal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sonar_msgs__msg__ConfScal__Sequence__copy(
  const sonar_msgs__msg__ConfScal__Sequence * input,
  sonar_msgs__msg__ConfScal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sonar_msgs__msg__ConfScal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sonar_msgs__msg__ConfScal * data =
      (sonar_msgs__msg__ConfScal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sonar_msgs__msg__ConfScal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sonar_msgs__msg__ConfScal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sonar_msgs__msg__ConfScal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
