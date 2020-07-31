set(ainrayc_INCLUDE ainray_win32api.h ainray_c.h)
file(COPY ${ainrayc_INCLUDE} DESTINATION ${ainrayc_BINARY_DIR}/include)
install(FILES ${ainrayc_INCLUDE} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)