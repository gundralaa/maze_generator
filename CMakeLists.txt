# Project Header
cmake_minimum_required(VERSION 3.10)
project(MazeGenerator)

# Set Source File Vars
# TODO Specify lib folder for system
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "/Volumes/YEAR_2/GameDev/libs")
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})
# Source Includes
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# GLFW Load
set(GLFW_DIR "${LIB_DIR}/glfw")
# Turn Off Options
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
# Add Module With CMake
add_subdirectory("${GLFW_DIR}" "glfw_build")
# Link Library
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# GLAD
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

# GLM
set(GLM_DIR "${LIB_DIR}/glm")
add_subdirectory("${GLM_DIR}" "glm_build")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLM_DIR}/glm")
target_link_libraries(${PROJECT_NAME} "glm")
