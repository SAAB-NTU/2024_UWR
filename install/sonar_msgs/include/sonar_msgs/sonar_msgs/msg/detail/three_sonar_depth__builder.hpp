// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sonar_msgs:msg/ThreeSonarDepth.idl
// generated code does not contain a copyright notice

#ifndef SONAR_MSGS__MSG__DETAIL__THREE_SONAR_DEPTH__BUILDER_HPP_
#define SONAR_MSGS__MSG__DETAIL__THREE_SONAR_DEPTH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sonar_msgs/msg/detail/three_sonar_depth__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sonar_msgs
{

namespace msg
{

namespace builder
{

class Init_ThreeSonarDepth_pressure
{
public:
  explicit Init_ThreeSonarDepth_pressure(::sonar_msgs::msg::ThreeSonarDepth & msg)
  : msg_(msg)
  {}
  ::sonar_msgs::msg::ThreeSonarDepth pressure(::sonar_msgs::msg::ThreeSonarDepth::_pressure_type arg)
  {
    msg_.pressure = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sonar_msgs::msg::ThreeSonarDepth msg_;
};

class Init_ThreeSonarDepth_altitude
{
public:
  explicit Init_ThreeSonarDepth_altitude(::sonar_msgs::msg::ThreeSonarDepth & msg)
  : msg_(msg)
  {}
  Init_ThreeSonarDepth_pressure altitude(::sonar_msgs::msg::ThreeSonarDepth::_altitude_type arg)
  {
    msg_.altitude = std::move(arg);
    return Init_ThreeSonarDepth_pressure(msg_);
  }

private:
  ::sonar_msgs::msg::ThreeSonarDepth msg_;
};

class Init_ThreeSonarDepth_depth
{
public:
  explicit Init_ThreeSonarDepth_depth(::sonar_msgs::msg::ThreeSonarDepth & msg)
  : msg_(msg)
  {}
  Init_ThreeSonarDepth_altitude depth(::sonar_msgs::msg::ThreeSonarDepth::_depth_type arg)
  {
    msg_.depth = std::move(arg);
    return Init_ThreeSonarDepth_altitude(msg_);
  }

private:
  ::sonar_msgs::msg::ThreeSonarDepth msg_;
};

class Init_ThreeSonarDepth_confidence_3
{
public:
  explicit Init_ThreeSonarDepth_confidence_3(::sonar_msgs::msg::ThreeSonarDepth & msg)
  : msg_(msg)
  {}
  Init_ThreeSonarDepth_depth confidence_3(::sonar_msgs::msg::ThreeSonarDepth::_confidence_3_type arg)
  {
    msg_.confidence_3 = std::move(arg);
    return Init_ThreeSonarDepth_depth(msg_);
  }

private:
  ::sonar_msgs::msg::ThreeSonarDepth msg_;
};

class Init_ThreeSonarDepth_distance_3
{
public:
  explicit Init_ThreeSonarDepth_distance_3(::sonar_msgs::msg::ThreeSonarDepth & msg)
  : msg_(msg)
  {}
  Init_ThreeSonarDepth_confidence_3 distance_3(::sonar_msgs::msg::ThreeSonarDepth::_distance_3_type arg)
  {
    msg_.distance_3 = std::move(arg);
    return Init_ThreeSonarDepth_confidence_3(msg_);
  }

private:
  ::sonar_msgs::msg::ThreeSonarDepth msg_;
};

class Init_ThreeSonarDepth_confidence_2
{
public:
  explicit Init_ThreeSonarDepth_confidence_2(::sonar_msgs::msg::ThreeSonarDepth & msg)
  : msg_(msg)
  {}
  Init_ThreeSonarDepth_distance_3 confidence_2(::sonar_msgs::msg::ThreeSonarDepth::_confidence_2_type arg)
  {
    msg_.confidence_2 = std::move(arg);
    return Init_ThreeSonarDepth_distance_3(msg_);
  }

private:
  ::sonar_msgs::msg::ThreeSonarDepth msg_;
};

class Init_ThreeSonarDepth_distance_2
{
public:
  explicit Init_ThreeSonarDepth_distance_2(::sonar_msgs::msg::ThreeSonarDepth & msg)
  : msg_(msg)
  {}
  Init_ThreeSonarDepth_confidence_2 distance_2(::sonar_msgs::msg::ThreeSonarDepth::_distance_2_type arg)
  {
    msg_.distance_2 = std::move(arg);
    return Init_ThreeSonarDepth_confidence_2(msg_);
  }

private:
  ::sonar_msgs::msg::ThreeSonarDepth msg_;
};

class Init_ThreeSonarDepth_confidence_1
{
public:
  explicit Init_ThreeSonarDepth_confidence_1(::sonar_msgs::msg::ThreeSonarDepth & msg)
  : msg_(msg)
  {}
  Init_ThreeSonarDepth_distance_2 confidence_1(::sonar_msgs::msg::ThreeSonarDepth::_confidence_1_type arg)
  {
    msg_.confidence_1 = std::move(arg);
    return Init_ThreeSonarDepth_distance_2(msg_);
  }

private:
  ::sonar_msgs::msg::ThreeSonarDepth msg_;
};

class Init_ThreeSonarDepth_distance_1
{
public:
  explicit Init_ThreeSonarDepth_distance_1(::sonar_msgs::msg::ThreeSonarDepth & msg)
  : msg_(msg)
  {}
  Init_ThreeSonarDepth_confidence_1 distance_1(::sonar_msgs::msg::ThreeSonarDepth::_distance_1_type arg)
  {
    msg_.distance_1 = std::move(arg);
    return Init_ThreeSonarDepth_confidence_1(msg_);
  }

private:
  ::sonar_msgs::msg::ThreeSonarDepth msg_;
};

class Init_ThreeSonarDepth_header
{
public:
  Init_ThreeSonarDepth_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ThreeSonarDepth_distance_1 header(::sonar_msgs::msg::ThreeSonarDepth::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ThreeSonarDepth_distance_1(msg_);
  }

private:
  ::sonar_msgs::msg::ThreeSonarDepth msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sonar_msgs::msg::ThreeSonarDepth>()
{
  return sonar_msgs::msg::builder::Init_ThreeSonarDepth_header();
}

}  // namespace sonar_msgs

#endif  // SONAR_MSGS__MSG__DETAIL__THREE_SONAR_DEPTH__BUILDER_HPP_
