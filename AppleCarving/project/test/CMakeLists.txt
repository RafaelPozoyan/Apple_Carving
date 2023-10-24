add_executable(apple  main.cpp)




target_link_libraries(apple PUBLIC AppleCarving)

target_link_libraries(apple PRIVATE CGAL)
