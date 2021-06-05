set(SRC_C  ainray_c.cpp ainray_error.cpp)
set(SRC_OS ainray_osapi.cpp)


add_library(generalc ${SRC_C})
ainrayc_install_library(generalc)

if(BUILD_WIN32API STREQUAL "ON")
    add_library(generalwin32 ${SRC_OS})
    target_link_libraries(generalwin32 generalc)
    ainrayc_install_library(generalwin32)
else()
    add_library(generalunix ${SRC_OS})
    target_link_libraries(generalunix generalc)
    ainrayc_install_library(generalunix)
endif(BUILD_WIN32API STREQUAL "ON")
