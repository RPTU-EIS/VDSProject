add_subdirectory(test)

add_library(Manager Manager.cpp)
target_link_libraries(Manager gvc cgraph)
