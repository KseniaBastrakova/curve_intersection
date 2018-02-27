include_directories(
    ../include/curve_intersection
    ../3rdParty/googletest/googletest/include)

add_executable(Tests 
    circle_tests.cxx
	ellipse_tests.cxx
	line_tests.cxx
	curve_intersection_tests.cxx
	bezier_curve_test.cxx
	intersector_test.cxx
	vector_test.cxx)

target_link_libraries(Tests
    gtest
	curveintersection)
