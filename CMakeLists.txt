cmake_minimum_required(VERSION 3.5)

project(IMAGEProcesseur LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( CMAKE_CXX_FLAGS "-O3")

set( SOURCES
    main.cpp)

set( MOC_HEADERS
    IPPMProcessor.hpp
    IPPMFilter.hpp
    PPMFilterSobel.hpp
    PPMProcessor.hpp
    PPMFilterBlur.hpp
    DFTCalculator.hpp.hpp
    GrayscaleConverter.hpp
    pixeltype.h)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(IMAGEProcesseur
               ${SOURCES}
               )

target_link_libraries(IMAGEProcesseur PRIVATE Qt5::Widgets)
