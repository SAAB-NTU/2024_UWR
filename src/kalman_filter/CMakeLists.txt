cmake_minimum_required(VERSION 3.8)
project(kalman_filter)

# Enable warning options for GCC or Clang
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sonar_msgs REQUIRED)   
find_package(sensor_msgs REQUIRED)    
find_package(tf2 REQUIRED)   
find_package(tf2_geometry_msgs REQUIRED)   
find_package(geometry_msgs REQUIRED) 
find_package(rosbag2_cpp REQUIRED)   

# Find the installed iir library (iir1 installed via apt)
find_library(IIR_LIB NAMES iir)

# Add executable for kalman filter
add_executable(kf src/kf_v3_node.cpp src/kf.cpp src/kf_v3_bag_processing.cpp src/sonar_processing.cpp)
add_executable(kf_v4 src/kf_v4_node.cpp src/kf_v4.cpp src/kf_v3_bag_processing.cpp src/sonar_processing.cpp)

# Include directories (add the system include path for iir headers if necessary)
target_include_directories(kf PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_include_directories(kf_v4 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Set required C and C++ standards
target_compile_features(kf PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_compile_features(kf_v4 PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

# Link the iir1 library to the kalman filter target
target_link_libraries(kf ${IIR_LIB})

target_link_libraries(kf_v4 ${IIR_LIB})

# Link the ROS2 dependencies to your executable
ament_target_dependencies(kf rclcpp sonar_msgs sensor_msgs tf2 tf2_geometry_msgs geometry_msgs rosbag2_cpp)

ament_target_dependencies(kf_v4 rclcpp sonar_msgs sensor_msgs tf2 tf2_geometry_msgs geometry_msgs rosbag2_cpp)

# Installation instructions
install(TARGETS kf
  DESTINATION lib/${PROJECT_NAME})

  install(TARGETS kf_v4
  DESTINATION lib/${PROJECT_NAME})

# Add tests (optional)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  
  # Skipping linter checks temporarily
  set(ament_cmake_cpplint_FOUND TRUE)
  
  ament_lint_auto_find_test_dependencies()
endif()

# Mark this package as an ament package
ament_package()

