include_directories(
    ../include/curve_intersection
    ../3rdParty/googletest/googletest/include)

add_executable(Tests 
    Circle_Tests.cxx
	Ellipse_Tests.cxx
	Line_Tests.cxx
	curve_intersection_tests.cxx
	Bezier_Tests.cxx
	intersector_test.cxx
	Vector_Test.cxx
	Point_Test.cxx
	FormattedCurveSerializer_Test.cxx)

target_link_libraries(Tests
    gtest
	curveintersection)
