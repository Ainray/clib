set(SRC_C  ainray_c.cpp)
set(SRC_WIN32 ainray_win32api.cpp)


add_library(ainrayc ${SRC_C})
ainrayc_install_library(ainrayc)

if(BUILD_WIN32API)
add_library(ainraywin32 ${SRC_C})
target_link_libraries(ainraywin32 ainrayc)
ainrayc_install_library(ainraywin32)
endif(BUILD_WIN32API)
