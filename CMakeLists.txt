cmake_minimum_required(VERSION 3.19)
project(Path-Tracer-CPU)
set(CMAKE_CXX_STANDARD 23)

if (WIN32)
    set(SDL2_DIR dependencies/SDL2-2.0.20)
endif()
set(glm_DIR dependencies/glm-0.9.9.8/glm/cmake/glm)
set(imgui_DIR dependencies/imgui-1.87)

set(SOURCE_FILES src/main.cpp)
 #${imgui_DIR}/backends/imgui_impl_opengl3.cpp ${imgui_DIR}/backends/imgui_impl_sdl.cpp ${imgui_DIR}/imgui.cpp ${imgui_DIR}/imgui_draw.cpp ${imgui_DIR}/imgui_demo.cpp ${imgui_DIR}/imgui_widgets.cpp ${imgui_DIR}/imgui_tables.cpp)

 # TODO: build library with imgui

add_executable(Path-Tracer-CPU src/main.cpp ${SOURCE_FILES})

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)

find_library(SDL2_LIB SDL2.lib ${SDL2_DIR}/lib/x64/)

target_link_libraries(Path-Tracer-CPU ${SDL2_LIBRARIES})

include_directories(Path-Tracer-CPU PUBLIC 
    ${SDL2_INCLUDE_DIRS} 
    ${GLM_INCLUDE_DIRS}
    ${imgui_DIR}
    include)

if (WIN32)
    configure_file("${SDL2_LIBRARIES_DIR}/SDL2.dll" "${CMAKE_BINARY_DIR}/" COPYONLY)
endif()