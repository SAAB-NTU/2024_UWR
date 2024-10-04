// bag_creator.h
#ifndef BAG_PROCESSING_H
#define BAG_PROCESSING_H

#include <string>
#include <rclcpp/rclcpp.hpp>


std::string bag_create_file(std::string path_param, rclcpp::Time current_time);

#endif // BAG_PROCESSING_H

