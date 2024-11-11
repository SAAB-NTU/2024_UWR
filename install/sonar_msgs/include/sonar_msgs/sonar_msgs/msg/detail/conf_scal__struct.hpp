// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sonar_msgs:msg/ConfScal.idl
// generated code does not contain a copyright notice

#ifndef SONAR_MSGS__MSG__DETAIL__CONF_SCAL__STRUCT_HPP_
#define SONAR_MSGS__MSG__DETAIL__CONF_SCAL__STRUCT_HPP_

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
# define DEPRECATED__sonar_msgs__msg__ConfScal __attribute__((deprecated))
#else
# define DEPRECATED__sonar_msgs__msg__ConfScal __declspec(deprecated)
#endif

namespace sonar_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ConfScal_
{
  using Type = ConfScal_<ContainerAllocator>;

  explicit ConfScal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->scalar_1 = 0.0f;
      this->confidence_1 = 0.0f;
      this->scalar_2 = 0.0f;
      this->confidence_2 = 0.0f;
      this->confidence_3 = 0.0f;
      this->scalar_3 = 0.0f;
    }
  }

  explicit ConfScal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->scalar_1 = 0.0f;
      this->confidence_1 = 0.0f;
      this->scalar_2 = 0.0f;
      this->confidence_2 = 0.0f;
      this->confidence_3 = 0.0f;
      this->scalar_3 = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _scalar_1_type =
    float;
  _scalar_1_type scalar_1;
  using _confidence_1_type =
    float;
  _confidence_1_type confidence_1;
  using _scalar_2_type =
    float;
  _scalar_2_type scalar_2;
  using _confidence_2_type =
    float;
  _confidence_2_type confidence_2;
  using _confidence_3_type =
    float;
  _confidence_3_type confidence_3;
  using _scalar_3_type =
    float;
  _scalar_3_type scalar_3;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__scalar_1(
    const float & _arg)
  {
    this->scalar_1 = _arg;
    return *this;
  }
  Type & set__confidence_1(
    const float & _arg)
  {
    this->confidence_1 = _arg;
    return *this;
  }
  Type & set__scalar_2(
    const float & _arg)
  {
    this->scalar_2 = _arg;
    return *this;
  }
  Type & set__confidence_2(
    const float & _arg)
  {
    this->confidence_2 = _arg;
    return *this;
  }
  Type & set__confidence_3(
    const float & _arg)
  {
    this->confidence_3 = _arg;
    return *this;
  }
  Type & set__scalar_3(
    const float & _arg)
  {
    this->scalar_3 = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sonar_msgs::msg::ConfScal_<ContainerAllocator> *;
  using ConstRawPtr =
    const sonar_msgs::msg::ConfScal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sonar_msgs::msg::ConfScal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sonar_msgs::msg::ConfScal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sonar_msgs::msg::ConfScal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sonar_msgs::msg::ConfScal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sonar_msgs::msg::ConfScal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sonar_msgs::msg::ConfScal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sonar_msgs::msg::ConfScal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sonar_msgs::msg::ConfScal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sonar_msgs__msg__ConfScal
    std::shared_ptr<sonar_msgs::msg::ConfScal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sonar_msgs__msg__ConfScal
    std::shared_ptr<sonar_msgs::msg::ConfScal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ConfScal_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->scalar_1 != other.scalar_1) {
      return false;
    }
    if (this->confidence_1 != other.confidence_1) {
      return false;
    }
    if (this->scalar_2 != other.scalar_2) {
      return false;
    }
    if (this->confidence_2 != other.confidence_2) {
      return false;
    }
    if (this->confidence_3 != other.confidence_3) {
      return false;
    }
    if (this->scalar_3 != other.scalar_3) {
      return false;
    }
    return true;
  }
  bool operator!=(const ConfScal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ConfScal_

// alias to use template instance with default allocator
using ConfScal =
  sonar_msgs::msg::ConfScal_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sonar_msgs

#endif  // SONAR_MSGS__MSG__DETAIL__CONF_SCAL__STRUCT_HPP_
