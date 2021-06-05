set(ainrayc_INCLUDE ainray_c.h ainray_error.h)
file(COPY ${ainrayc_INCLUDE} DESTINATION ${ainrayc_BINARY_DIR}/include)
install(FILES ${ainrayc_INCLUDE} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

if(BUILD_WIN32API STREQUAL "ON")
set(ainraywin32_INCLUDE ainray_osapi.h)
file(COPY ${ainraywin32_INCLUDE} DESTINATION ${ainrayc_BINARY_DIR}/include)
install(FILES ${ainraywin32_INCLUDE} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
endif(BUILD_WIN32API STREQUAL "ON")