// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sonar_msgs:msg/KfValues.idl
// generated code does not contain a copyright notice

#ifndef SONAR_MSGS__MSG__DETAIL__KF_VALUES__BUILDER_HPP_
#define SONAR_MSGS__MSG__DETAIL__KF_VALUES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sonar_msgs/msg/detail/kf_values__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sonar_msgs
{

namespace msg
{

namespace builder
{

class Init_KfValues_k_v_3
{
public:
  explicit Init_KfValues_k_v_3(::sonar_msgs::msg::KfValues & msg)
  : msg_(msg)
  {}
  ::sonar_msgs::msg::KfValues k_v_3(::sonar_msgs::msg::KfValues::_k_v_3_type arg)
  {
    msg_.k_v_3 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sonar_msgs::msg::KfValues msg_;
};

class Init_KfValues_k_d_3
{
public:
  explicit Init_KfValues_k_d_3(::sonar_msgs::msg::KfValues & msg)
  : msg_(msg)
  {}
  Init_KfValues_k_v_3 k_d_3(::sonar_msgs::msg::KfValues::_k_d_3_type arg)
  {
    msg_.k_d_3 = std::move(arg);
    return Init_KfValues_k_v_3(msg_);
  }

private:
  ::sonar_msgs::msg::KfValues msg_;
};

class Init_KfValues_k_v_2
{
public:
  explicit Init_KfValues_k_v_2(::sonar_msgs::msg::KfValues & msg)
  : msg_(msg)
  {}
  Init_KfValues_k_d_3 k_v_2(::sonar_msgs::msg::KfValues::_k_v_2_type arg)
  {
    msg_.k_v_2 = std::move(arg);
    return Init_KfValues_k_d_3(msg_);
  }

private:
  ::sonar_msgs::msg::KfValues msg_;
};

class Init_KfValues_k_d_2
{
public:
  explicit Init_KfValues_k_d_2(::sonar_msgs::msg::KfValues & msg)
  : msg_(msg)
  {}
  Init_KfValues_k_v_2 k_d_2(::sonar_msgs::msg::KfValues::_k_d_2_type arg)
  {
    msg_.k_d_2 = std::move(arg);
    return Init_KfValues_k_v_2(msg_);
  }

private:
  ::sonar_msgs::msg::KfValues msg_;
};

class Init_KfValues_k_v_1
{
public:
  explicit Init_KfValues_k_v_1(::sonar_msgs::msg::KfValues & msg)
  : msg_(msg)
  {}
  Init_KfValues_k_d_2 k_v_1(::sonar_msgs::msg::KfValues::_k_v_1_type arg)
  {
    msg_.k_v_1 = std::move(arg);
    return Init_KfValues_k_d_2(msg_);
  }

private:
  ::sonar_msgs::msg::KfValues msg_;
};

class Init_KfValues_k_d_1
{
public:
  explicit Init_KfValues_k_d_1(::sonar_msgs::msg::KfValues & msg)
  : msg_(msg)
  {}
  Init_KfValues_k_v_1 k_d_1(::sonar_msgs::msg::KfValues::_k_d_1_type arg)
  {
    msg_.k_d_1 = std::move(arg);
    return Init_KfValues_k_v_1(msg_);
  }

private:
  ::sonar_msgs::msg::KfValues msg_;
};

class Init_KfValues_header
{
public:
  Init_KfValues_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_KfValues_k_d_1 header(::sonar_msgs::msg::KfValues::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_KfValues_k_d_1(msg_);
  }

private:
  ::sonar_msgs::msg::KfValues msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sonar_msgs::msg::KfValues>()
{
  return sonar_msgs::msg::builder::Init_KfValues_header();
}

}  // namespace sonar_msgs

#endif  // SONAR_MSGS__MSG__DETAIL__KF_VALUES__BUILDER_HPP_
