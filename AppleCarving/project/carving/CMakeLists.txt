add_library(AppleCarving AppleCarving.cpp include/AppleCarving/AppleCarving.hpp)

target_link_libraries(AppleCarving PUBLIC CGAL)
find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt5)
if(CGAL_Qt5_FOUND)
  target_link_libraries(AppleCarving  PUBLIC CGAL::CGAL_Basic_viewer)
else()
  message(STATUS "NOTICE: The example 'draw_triangulation_3' requires Qt5, and will not be compiled.")
endif()

set_property(TARGET AppleCarving PROPERTY CXX_STANDARD 20)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS AppleCarving)