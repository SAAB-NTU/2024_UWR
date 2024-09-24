// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sonar_msgs:msg/ThreeSonarDepth.idl
// generated code does not contain a copyright notice

#ifndef SONAR_MSGS__MSG__DETAIL__THREE_SONAR_DEPTH__STRUCT_HPP_
#define SONAR_MSGS__MSG__DETAIL__THREE_SONAR_DEPTH__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sonar_msgs__msg__ThreeSonarDepth __attribute__((deprecated))
#else
# define DEPRECATED__sonar_msgs__msg__ThreeSonarDepth __declspec(deprecated)
#endif

namespace sonar_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ThreeSonarDepth_
{
  using Type = ThreeSonarDepth_<ContainerAllocator>;

  explicit ThreeSonarDepth_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->distance_1 = 0.0f;
      this->confidence_1 = 0.0f;
      this->distance_2 = 0.0f;
      this->confidence_2 = 0.0f;
      this->distance_3 = 0.0f;
      this->confidence_3 = 0.0f;
      this->depth = 0.0f;
      this->altitude = 0.0f;
      this->pressure = 0.0f;
    }
  }

  explicit ThreeSonarDepth_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->distance_1 = 0.0f;
      this->confidence_1 = 0.0f;
      this->distance_2 = 0.0f;
      this->confidence_2 = 0.0f;
      this->distance_3 = 0.0f;
      this->confidence_3 = 0.0f;
      this->depth = 0.0f;
      this->altitude = 0.0f;
      this->pressure = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _distance_1_type =
    float;
  _distance_1_type distance_1;
  using _confidence_1_type =
    float;
  _confidence_1_type confidence_1;
  using _distance_2_type =
    float;
  _distance_2_type distance_2;
  using _confidence_2_type =
    float;
  _confidence_2_type confidence_2;
  using _distance_3_type =
    float;
  _distance_3_type distance_3;
  using _confidence_3_type =
    float;
  _confidence_3_type confidence_3;
  using _depth_type =
    float;
  _depth_type depth;
  using _altitude_type =
    float;
  _altitude_type altitude;
  using _pressure_type =
    float;
  _pressure_type pressure;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__distance_1(
    const float & _arg)
  {
    this->distance_1 = _arg;
    return *this;
  }
  Type & set__confidence_1(
    const float & _arg)
  {
    this->confidence_1 = _arg;
    return *this;
  }
  Type & set__distance_2(
    const float & _arg)
  {
    this->distance_2 = _arg;
    return *this;
  }
  Type & set__confidence_2(
    const float & _arg)
  {
    this->confidence_2 = _arg;
    return *this;
  }
  Type & set__distance_3(
    const float & _arg)
  {
    this->distance_3 = _arg;
    return *this;
  }
  Type & set__confidence_3(
    const float & _arg)
  {
    this->confidence_3 = _arg;
    return *this;
  }
  Type & set__depth(
    const float & _arg)
  {
    this->depth = _arg;
    return *this;
  }
  Type & set__altitude(
    const float & _arg)
  {
    this->altitude = _arg;
    return *this;
  }
  Type & set__pressure(
    const float & _arg)
  {
    this->pressure = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sonar_msgs::msg::ThreeSonarDepth_<ContainerAllocator> *;
  using ConstRawPtr =
    const sonar_msgs::msg::ThreeSonarDepth_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sonar_msgs::msg::ThreeSonarDepth_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sonar_msgs::msg::ThreeSonarDepth_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sonar_msgs::msg::ThreeSonarDepth_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sonar_msgs::msg::ThreeSonarDepth_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sonar_msgs::msg::ThreeSonarDepth_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sonar_msgs::msg::ThreeSonarDepth_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sonar_msgs::msg::ThreeSonarDepth_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sonar_msgs::msg::ThreeSonarDepth_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sonar_msgs__msg__ThreeSonarDepth
    std::shared_ptr<sonar_msgs::msg::ThreeSonarDepth_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sonar_msgs__msg__ThreeSonarDepth
    std::shared_ptr<sonar_msgs::msg::ThreeSonarDepth_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ThreeSonarDepth_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->distance_1 != other.distance_1) {
      return false;
    }
    if (this->confidence_1 != other.confidence_1) {
      return false;
    }
    if (this->distance_2 != other.distance_2) {
      return false;
    }
    if (this->confidence_2 != other.confidence_2) {
      return false;
    }
    if (this->distance_3 != other.distance_3) {
      return false;
    }
    if (this->confidence_3 != other.confidence_3) {
      return false;
    }
    if (this->depth != other.depth) {
      return false;
    }
    if (this->altitude != other.altitude) {
      return false;
    }
    if (this->pressure != other.pressure) {
      return false;
    }
    return true;
  }
  bool operator!=(const ThreeSonarDepth_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ThreeSonarDepth_

// alias to use template instance with default allocator
using ThreeSonarDepth =
  sonar_msgs::msg::ThreeSonarDepth_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sonar_msgs

#endif  // SONAR_MSGS__MSG__DETAIL__THREE_SONAR_DEPTH__STRUCT_HPP_
