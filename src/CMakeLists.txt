find_package(OpenGL REQUIRED)

set(INCLUDE_DIR "${PixelWindow_SOURCE_DIR}/include/PixelWindow")

set(SRC 
	"${INCLUDE_DIR}/Window.h"
	"${INCLUDE_DIR}/PixelWindow.h"
	Window.cpp
	PixelWindow.cpp
)

add_library(PixelWindow ${SRC})

# include dir
target_include_directories(PixelWindow PUBLIC "${INCLUDE_DIR}/..")

target_link_libraries(PixelWindow glad)
target_link_libraries(PixelWindow glfw)
target_link_libraries(PixelWindow OpenGL::GL)