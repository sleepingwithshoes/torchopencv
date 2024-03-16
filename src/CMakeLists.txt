
add_executable(${PROJECT_NAME}
        main.cpp)

target_link_libraries(${PROJECT_NAME}
        ${TORCH_LIBRARIES}
        ${OpenCV_LIBS})
