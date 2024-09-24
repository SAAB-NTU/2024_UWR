// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sonar_msgs:msg/ConfScal.idl
// generated code does not contain a copyright notice

#ifndef SONAR_MSGS__MSG__DETAIL__CONF_SCAL__TRAITS_HPP_
#define SONAR_MSGS__MSG__DETAIL__CONF_SCAL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sonar_msgs/msg/detail/conf_scal__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace sonar_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const ConfScal & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: scalar_1
  {
    out << "scalar_1: ";
    rosidl_generator_traits::value_to_yaml(msg.scalar_1, out);
    out << ", ";
  }

  // member: confidence_1
  {
    out << "confidence_1: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence_1, out);
    out << ", ";
  }

  // member: scalar_2
  {
    out << "scalar_2: ";
    rosidl_generator_traits::value_to_yaml(msg.scalar_2, out);
    out << ", ";
  }

  // member: confidence_2
  {
    out << "confidence_2: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence_2, out);
    out << ", ";
  }

  // member: confidence_3
  {
    out << "confidence_3: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence_3, out);
    out << ", ";
  }

  // member: scalar_3
  {
    out << "scalar_3: ";
    rosidl_generator_traits::value_to_yaml(msg.scalar_3, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ConfScal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: scalar_1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "scalar_1: ";
    rosidl_generator_traits::value_to_yaml(msg.scalar_1, out);
    out << "\n";
  }

  // member: confidence_1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence_1: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence_1, out);
    out << "\n";
  }

  // member: scalar_2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "scalar_2: ";
    rosidl_generator_traits::value_to_yaml(msg.scalar_2, out);
    out << "\n";
  }

  // member: confidence_2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence_2: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence_2, out);
    out << "\n";
  }

  // member: confidence_3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence_3: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence_3, out);
    out << "\n";
  }

  // member: scalar_3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "scalar_3: ";
    rosidl_generator_traits::value_to_yaml(msg.scalar_3, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ConfScal & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace sonar_msgs

namespace rosidl_generator_traits
{

[[deprecated("use sonar_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const sonar_msgs::msg::ConfScal & msg,
  std::ostream & out, size_t indentation = 0)
{
  sonar_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sonar_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sonar_msgs::msg::ConfScal & msg)
{
  return sonar_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sonar_msgs::msg::ConfScal>()
{
  return "sonar_msgs::msg::ConfScal";
}

template<>
inline const char * name<sonar_msgs::msg::ConfScal>()
{
  return "sonar_msgs/msg/ConfScal";
}

template<>
struct has_fixed_size<sonar_msgs::msg::ConfScal>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<sonar_msgs::msg::ConfScal>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<sonar_msgs::msg::ConfScal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SONAR_MSGS__MSG__DETAIL__CONF_SCAL__TRAITS_HPP_
