INCLUDE_DIRECTORIES(include)
ADD_LIBRARY(prepmatrix STATIC src/matrix.cpp src/helper_for_matrix.cpp)

ADD_SUBDIRECTORY(tests)
