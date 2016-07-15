add_executable(hdeem_timestats hdeem_timestats.cpp)
target_link_libraries(hdeem_timestats ${HDEEM_LIBRARIES})

add_executable(hdeem_cxx hdeem_cxx.cpp)
target_link_libraries(hdeem_cxx ${HDEEM_LIBRARIES})

add_executable(hdeem_raw hdeem_raw.cpp)
target_link_libraries(hdeem_raw ${HDEEM_LIBRARIES})
