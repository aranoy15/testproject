target_include_directories(drivers PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
    ${CMAKE_SOURCE_DIR}/conf
)

add_subdirectory(Src)