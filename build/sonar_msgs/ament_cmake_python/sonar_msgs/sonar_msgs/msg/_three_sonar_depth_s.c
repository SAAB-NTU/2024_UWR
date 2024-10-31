// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from sonar_msgs:msg/ThreeSonarDepth.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "sonar_msgs/msg/detail/three_sonar_depth__struct.h"
#include "sonar_msgs/msg/detail/three_sonar_depth__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool sonar_msgs__msg__three_sonar_depth__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[50];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("sonar_msgs.msg._three_sonar_depth.ThreeSonarDepth", full_classname_dest, 49) == 0);
  }
  sonar_msgs__msg__ThreeSonarDepth * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // distance_1
    PyObject * field = PyObject_GetAttrString(_pymsg, "distance_1");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->distance_1 = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // confidence_1
    PyObject * field = PyObject_GetAttrString(_pymsg, "confidence_1");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->confidence_1 = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // distance_2
    PyObject * field = PyObject_GetAttrString(_pymsg, "distance_2");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->distance_2 = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // confidence_2
    PyObject * field = PyObject_GetAttrString(_pymsg, "confidence_2");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->confidence_2 = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // distance_3
    PyObject * field = PyObject_GetAttrString(_pymsg, "distance_3");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->distance_3 = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // confidence_3
    PyObject * field = PyObject_GetAttrString(_pymsg, "confidence_3");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->confidence_3 = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // depth
    PyObject * field = PyObject_GetAttrString(_pymsg, "depth");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->depth = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // altitude
    PyObject * field = PyObject_GetAttrString(_pymsg, "altitude");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->altitude = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // pressure
    PyObject * field = PyObject_GetAttrString(_pymsg, "pressure");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->pressure = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * sonar_msgs__msg__three_sonar_depth__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of ThreeSonarDepth */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("sonar_msgs.msg._three_sonar_depth");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "ThreeSonarDepth");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  sonar_msgs__msg__ThreeSonarDepth * ros_message = (sonar_msgs__msg__ThreeSonarDepth *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // distance_1
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->distance_1);
    {
      int rc = PyObject_SetAttrString(_pymessage, "distance_1", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // confidence_1
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->confidence_1);
    {
      int rc = PyObject_SetAttrString(_pymessage, "confidence_1", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // distance_2
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->distance_2);
    {
      int rc = PyObject_SetAttrString(_pymessage, "distance_2", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // confidence_2
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->confidence_2);
    {
      int rc = PyObject_SetAttrString(_pymessage, "confidence_2", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // distance_3
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->distance_3);
    {
      int rc = PyObject_SetAttrString(_pymessage, "distance_3", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // confidence_3
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->confidence_3);
    {
      int rc = PyObject_SetAttrString(_pymessage, "confidence_3", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // depth
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->depth);
    {
      int rc = PyObject_SetAttrString(_pymessage, "depth", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // altitude
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->altitude);
    {
      int rc = PyObject_SetAttrString(_pymessage, "altitude", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pressure
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->pressure);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pressure", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}