add_executable(hdeem_timestats hdeem_timestats.cpp)
target_link_libraries(hdeem_timestats PUBLIC hdeem::cxx)

add_executable(hdeem_avg hdeem_avg.cpp)
target_link_libraries(hdeem_avg PUBLIC hdeem::cxx)

add_executable(hdeem_raw hdeem_raw.cpp)
target_link_libraries(hdeem_raw PUBLIC hdeem::cxx)
