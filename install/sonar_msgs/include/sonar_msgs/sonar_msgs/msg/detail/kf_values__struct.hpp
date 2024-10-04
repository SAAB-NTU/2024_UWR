// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sonar_msgs:msg/KfValues.idl
// generated code does not contain a copyright notice

#ifndef SONAR_MSGS__MSG__DETAIL__KF_VALUES__STRUCT_HPP_
#define SONAR_MSGS__MSG__DETAIL__KF_VALUES__STRUCT_HPP_

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
# define DEPRECATED__sonar_msgs__msg__KfValues __attribute__((deprecated))
#else
# define DEPRECATED__sonar_msgs__msg__KfValues __declspec(deprecated)
#endif

namespace sonar_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct KfValues_
{
  using Type = KfValues_<ContainerAllocator>;

  explicit KfValues_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->k_d_1 = 0.0f;
      this->k_v_1 = 0.0f;
      this->k_d_2 = 0.0f;
      this->k_v_2 = 0.0f;
      this->k_d_3 = 0.0f;
      this->k_v_3 = 0.0f;
    }
  }

  explicit KfValues_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->k_d_1 = 0.0f;
      this->k_v_1 = 0.0f;
      this->k_d_2 = 0.0f;
      this->k_v_2 = 0.0f;
      this->k_d_3 = 0.0f;
      this->k_v_3 = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _k_d_1_type =
    float;
  _k_d_1_type k_d_1;
  using _k_v_1_type =
    float;
  _k_v_1_type k_v_1;
  using _k_d_2_type =
    float;
  _k_d_2_type k_d_2;
  using _k_v_2_type =
    float;
  _k_v_2_type k_v_2;
  using _k_d_3_type =
    float;
  _k_d_3_type k_d_3;
  using _k_v_3_type =
    float;
  _k_v_3_type k_v_3;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__k_d_1(
    const float & _arg)
  {
    this->k_d_1 = _arg;
    return *this;
  }
  Type & set__k_v_1(
    const float & _arg)
  {
    this->k_v_1 = _arg;
    return *this;
  }
  Type & set__k_d_2(
    const float & _arg)
  {
    this->k_d_2 = _arg;
    return *this;
  }
  Type & set__k_v_2(
    const float & _arg)
  {
    this->k_v_2 = _arg;
    return *this;
  }
  Type & set__k_d_3(
    const float & _arg)
  {
    this->k_d_3 = _arg;
    return *this;
  }
  Type & set__k_v_3(
    const float & _arg)
  {
    this->k_v_3 = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sonar_msgs::msg::KfValues_<ContainerAllocator> *;
  using ConstRawPtr =
    const sonar_msgs::msg::KfValues_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sonar_msgs::msg::KfValues_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sonar_msgs::msg::KfValues_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sonar_msgs::msg::KfValues_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sonar_msgs::msg::KfValues_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sonar_msgs::msg::KfValues_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sonar_msgs::msg::KfValues_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sonar_msgs::msg::KfValues_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sonar_msgs::msg::KfValues_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sonar_msgs__msg__KfValues
    std::shared_ptr<sonar_msgs::msg::KfValues_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sonar_msgs__msg__KfValues
    std::shared_ptr<sonar_msgs::msg::KfValues_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const KfValues_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->k_d_1 != other.k_d_1) {
      return false;
    }
    if (this->k_v_1 != other.k_v_1) {
      return false;
    }
    if (this->k_d_2 != other.k_d_2) {
      return false;
    }
    if (this->k_v_2 != other.k_v_2) {
      return false;
    }
    if (this->k_d_3 != other.k_d_3) {
      return false;
    }
    if (this->k_v_3 != other.k_v_3) {
      return false;
    }
    return true;
  }
  bool operator!=(const KfValues_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct KfValues_

// alias to use template instance with default allocator
using KfValues =
  sonar_msgs::msg::KfValues_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sonar_msgs

#endif  // SONAR_MSGS__MSG__DETAIL__KF_VALUES__STRUCT_HPP_
