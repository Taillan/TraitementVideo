Cmake_minimum_required(VERSION 3.6)

# =============================================================================
# Project
# =============================================================================
project(exple VERSION 1.0 LANGUAGES CXX)
set(PROJECT_DESCRIPTION "OpenCV Teaching - P. FOUBERT - Example")

# We choose to compile in debug
set(CMAKE_BUILD_TYPE "Debug")

# -------------------------------------------------
# Default C/CXX standards
# -------------------------------------------------
set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_EXTENSIONS        OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------
# OpenCV
# -------------------------------------------------

    # ---------------------------------------------
    # We chose to install OpenCV in a custom folder
    # ---------------------------------------------
    set(OPENCV_DIR_HINT "/nfs/opt/bdr/OpenCV")

    # ---------------------------------------------
    # OpenCV
    # ---------------------------------------------
    find_package(OpenCV HINTS ${OPENCV_DIR_HINT})
    if (${OpenCV_VERSION_MAJOR} LESS 3)
      message("OpenCV_VERSION_MAJOR=${OpenCV_VERSION_MAJOR}")
      message(WARNING "OpenCV version should be 3.0.0 or greater. "
                      "Found version: ${OpenCV_VERSION}")
    endif()
    include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})
    list(APPEND EXTRA_LIBS ${OpenCV_LIBS})

    message(STATUS "OPENCV_DIR_HINT=${OPENCV_DIR_HINT}")
    message(STATUS "OpenCV_VERSION=${OpenCV_VERSION}")
    message(STATUS "OpenCV_LIBS=${OpenCV_LIBS}")

    # ---------------------------------------------
    # OpenCV dependencies
    # ---------------------------------------------

    # In case OpenCV is using Eigen
    find_package(Eigen3 QUIET)
    mark_as_advanced(Eigen3_DIR)
    if (Eigen_FOUND)
      list(APPEND EXTRA_LIBS Eigen3::Eigen)
    endif()

    # In case OpenCV is using Iconv
    find_package(Iconv QUIET)
    if (Iconv_FOUND)
      list(APPEND EXTRA_LIBS Iconv::Iconv)
    endif()

    # In case OpenCV is using OpenMP
    find_package(OpenMP QUIET)
    if (OpenMP_CXX_FOUND)
      list(APPEND EXTRA_LIBS OpenMP::OpenMP_CXX)
    endif()

# =============================================================================
# Targets
# =============================================================================
add_executable(video video.cpp)
add_executable(stegano stegano.cpp)
target_compile_definitions(video PRIVATE DATA_FOLDER="./data/")
target_compile_definitions(stegano PRIVATE DATA_FOLDER="./data/")
target_link_libraries(video ${EXTRA_LIBS})
target_link_libraries(stegano ${EXTRA_LIBS})

