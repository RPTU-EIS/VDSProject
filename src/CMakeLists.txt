add_subdirectory(test)

add_library(Manager Manager.cpp)

enable_testing()

add_subdirectory(googletest)
# add_subdirectory(test)
