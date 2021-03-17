cmake_minimum_required(VERSION 3.17)
project(ClangCurriculumDesign)

set(CMAKE_CXX_STANDARD 14)

add_executable(ClangCurriculumDesign
        bitmap_image_file_scaling/main.cc
        high_precision_calculate/main.cc
        histogram_equalization/main.cc
        linkedlist/main.cc
        rle/main.cc
        stack/main.cc)
