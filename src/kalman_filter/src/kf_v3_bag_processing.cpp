#include <rclcpp/rclcpp.hpp>
#include "../include/bag_processing.h"
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>

std::string bag_create_file(std::string path_param, rclcpp::Time current_time) 
{
    // Convert ROS2 time to system time
    std::time_t time_in_seconds = current_time.seconds();
    std::tm* time_info = std::localtime(&time_in_seconds);

    // Extract date and time components
    int year = time_info->tm_year + 1900;
    int month = time_info->tm_mon + 1;
    int day = time_info->tm_mday;
    int hour = time_info->tm_hour;
    int minute = time_info->tm_min;
    int second = time_info->tm_sec;

    // Format the date and time components as a string
    std::stringstream filename_stream;
    filename_stream << std::setw(4) << std::setfill('0') << year << "_"
                    << std::setw(2) << std::setfill('0') << month << "_"
                    << std::setw(2) << std::setfill('0') << day << "_"
                    << std::setw(2) << std::setfill('0') << hour << "_"
                    << std::setw(2) << std::setfill('0') << minute << "_"
                    << std::setw(2) << std::setfill('0') << second;
                    
    std::string filename = filename_stream.str();
    std::string file_path = path_param;
    std::string file_format = ".bag";
  
    file_path = file_path + filename + file_format;
    return file_path; 
}
