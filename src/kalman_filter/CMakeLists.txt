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
find_package(message_filters REQUIRED)   

# iir1 (Butterworth filters). Not packaged on conda-forge, so use an installed
# copy if present, otherwise build it from source.
find_package(iir QUIET)
if(iir_FOUND)
  set(IIR_LIB iir::iir_static)
else()
  include(FetchContent)
  FetchContent_Declare(iir1
    GIT_REPOSITORY https://github.com/berndporr/iir1.git
    GIT_TAG 1.9.5
  )
  FetchContent_GetProperties(iir1)
  if(NOT iir1_POPULATED)
    FetchContent_Populate(iir1)
  endif()
  # Build iir1's sources directly instead of add_subdirectory(): its own
  # CMakeLists installs an iirConfig.cmake without the targets file, which
  # a later find_package(iir) then picks up from our install/ and fails on.
  file(GLOB IIR1_SOURCES ${iir1_SOURCE_DIR}/iir/*.cpp)
  add_library(iir_static STATIC ${IIR1_SOURCES})
  target_include_directories(iir_static PUBLIC ${iir1_SOURCE_DIR})
  set_target_properties(iir_static PROPERTIES POSITION_INDEPENDENT_CODE ON)
  set(IIR_LIB iir_static)
endif()

# Add executable for kalman filter
add_executable(kf src/kf_v3_node.cpp src/kf.cpp src/kf_v3_bag_processing.cpp src/sonar_processing.cpp)
add_executable(kf_v4 src/kf_v4_node.cpp src/kf_v4.cpp src/kf_v3_bag_processing.cpp src/sonar_processing.cpp)
add_executable(kf_3dof src/kf_3dof_node.cpp src/kf_3dof.cpp src/kf_v3_bag_processing.cpp src/sonar_processing.cpp)
add_executable(gd_conf src/grad_descent_confidence.cpp)
add_executable(imu_topic src/imu_topic.cpp)

# Include directories (add the system include path for iir headers if necessary)
target_include_directories(kf PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_include_directories(kf_v4 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_include_directories(kf_3dof PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)


target_include_directories(gd_conf PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_include_directories(imu_topic PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)


	
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME}/)
# Set required C and C++ standards
target_compile_features(kf PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_compile_features(kf_v4 PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_compile_features(kf_3dof PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_compile_features(gd_conf PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_compile_features(imu_topic PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

# Link the iir1 library to the kalman filter target
target_link_libraries(kf ${IIR_LIB})

target_link_libraries(kf_v4 ${IIR_LIB})

target_link_libraries(kf_3dof ${IIR_LIB})


# Link the ROS2 dependencies to your executable
ament_target_dependencies(kf rclcpp sonar_msgs sensor_msgs tf2 tf2_geometry_msgs geometry_msgs rosbag2_cpp)

ament_target_dependencies(kf_v4 rclcpp sonar_msgs sensor_msgs tf2 tf2_geometry_msgs geometry_msgs rosbag2_cpp)

ament_target_dependencies(kf_3dof rclcpp sonar_msgs sensor_msgs tf2 tf2_geometry_msgs geometry_msgs rosbag2_cpp)

ament_target_dependencies(gd_conf rclcpp sonar_msgs sensor_msgs tf2 tf2_geometry_msgs geometry_msgs rosbag2_cpp)

ament_target_dependencies(imu_topic rclcpp  sensor_msgs rosbag2_cpp message_filters)

# Installation instructions
install(TARGETS kf
  DESTINATION lib/${PROJECT_NAME})

  install(TARGETS kf_v4
  DESTINATION lib/${PROJECT_NAME})
  
    install(TARGETS kf_3dof
  DESTINATION lib/${PROJECT_NAME})
  
    install(TARGETS gd_conf
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS imu_topic
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

