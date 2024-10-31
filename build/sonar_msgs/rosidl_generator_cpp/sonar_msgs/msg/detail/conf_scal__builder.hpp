// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sonar_msgs:msg/ConfScal.idl
// generated code does not contain a copyright notice

#ifndef SONAR_MSGS__MSG__DETAIL__CONF_SCAL__BUILDER_HPP_
#define SONAR_MSGS__MSG__DETAIL__CONF_SCAL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sonar_msgs/msg/detail/conf_scal__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sonar_msgs
{

namespace msg
{

namespace builder
{

class Init_ConfScal_scalar_3
{
public:
  explicit Init_ConfScal_scalar_3(::sonar_msgs::msg::ConfScal & msg)
  : msg_(msg)
  {}
  ::sonar_msgs::msg::ConfScal scalar_3(::sonar_msgs::msg::ConfScal::_scalar_3_type arg)
  {
    msg_.scalar_3 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sonar_msgs::msg::ConfScal msg_;
};

class Init_ConfScal_confidence_3
{
public:
  explicit Init_ConfScal_confidence_3(::sonar_msgs::msg::ConfScal & msg)
  : msg_(msg)
  {}
  Init_ConfScal_scalar_3 confidence_3(::sonar_msgs::msg::ConfScal::_confidence_3_type arg)
  {
    msg_.confidence_3 = std::move(arg);
    return Init_ConfScal_scalar_3(msg_);
  }

private:
  ::sonar_msgs::msg::ConfScal msg_;
};

class Init_ConfScal_confidence_2
{
public:
  explicit Init_ConfScal_confidence_2(::sonar_msgs::msg::ConfScal & msg)
  : msg_(msg)
  {}
  Init_ConfScal_confidence_3 confidence_2(::sonar_msgs::msg::ConfScal::_confidence_2_type arg)
  {
    msg_.confidence_2 = std::move(arg);
    return Init_ConfScal_confidence_3(msg_);
  }

private:
  ::sonar_msgs::msg::ConfScal msg_;
};

class Init_ConfScal_scalar_2
{
public:
  explicit Init_ConfScal_scalar_2(::sonar_msgs::msg::ConfScal & msg)
  : msg_(msg)
  {}
  Init_ConfScal_confidence_2 scalar_2(::sonar_msgs::msg::ConfScal::_scalar_2_type arg)
  {
    msg_.scalar_2 = std::move(arg);
    return Init_ConfScal_confidence_2(msg_);
  }

private:
  ::sonar_msgs::msg::ConfScal msg_;
};

class Init_ConfScal_confidence_1
{
public:
  explicit Init_ConfScal_confidence_1(::sonar_msgs::msg::ConfScal & msg)
  : msg_(msg)
  {}
  Init_ConfScal_scalar_2 confidence_1(::sonar_msgs::msg::ConfScal::_confidence_1_type arg)
  {
    msg_.confidence_1 = std::move(arg);
    return Init_ConfScal_scalar_2(msg_);
  }

private:
  ::sonar_msgs::msg::ConfScal msg_;
};

class Init_ConfScal_scalar_1
{
public:
  explicit Init_ConfScal_scalar_1(::sonar_msgs::msg::ConfScal & msg)
  : msg_(msg)
  {}
  Init_ConfScal_confidence_1 scalar_1(::sonar_msgs::msg::ConfScal::_scalar_1_type arg)
  {
    msg_.scalar_1 = std::move(arg);
    return Init_ConfScal_confidence_1(msg_);
  }

private:
  ::sonar_msgs::msg::ConfScal msg_;
};

class Init_ConfScal_header
{
public:
  Init_ConfScal_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ConfScal_scalar_1 header(::sonar_msgs::msg::ConfScal::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ConfScal_scalar_1(msg_);
  }

private:
  ::sonar_msgs::msg::ConfScal msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sonar_msgs::msg::ConfScal>()
{
  return sonar_msgs::msg::builder::Init_ConfScal_header();
}

}  // namespace sonar_msgs

#endif  // SONAR_MSGS__MSG__DETAIL__CONF_SCAL__BUILDER_HPP_
