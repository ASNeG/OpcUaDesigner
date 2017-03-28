# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# build 
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

include_directories(
    ${OPCUASTACK_INSTALL_PREFIX}/usr/include/OpcUaStack${OPCUASTACK_VERSION_MAJOR}
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR}
)

file(
    GLOB 
    OpcUaGui_SRC 
    ${PROJECT_SOURCE_DIR}/OpcUaGui/*/*.cpp
)

QT5_ADD_RESOURCES(
    OpcUaGui_RES
    OpcUaGui/Resources/OpcUaGui.qrc
)


add_executable(
    OpcUaDesigner
    ${OpcUaGui_RES}
    ${OpcUaGui_SRC}
)

target_link_libraries(
    OpcUaDesigner
    ${pthread}
    ${OPCUASTACK_LIBRARY_CORE}
    ${OPCUASTACK_LIBRARY_CLIENT}
    ${Boost_LIBRARIES}
    ${CMAKE_DL_LIBS}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Core_LIBRARIES}
)


# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# install
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
install(TARGETS OpcUaDesigner DESTINATION /usr/bin)

install(FILES ${PROJECT_SOURCE_DIR}/OpcUaGui/Config/OpcUaDesigner.xml DESTINATION /etc/OpcUaStack/OpcUaDesigner) 
install(FILES ${PROJECT_SOURCE_DIR}/OpcUaGui/Config/Opc.Ua.NodeSet.xml DESTINATION /etc/OpcUaStack/OpcUaDesigner)
install(FILES ${PROJECT_SOURCE_DIR}/OpcUaGui/linux/log/README DESTINATION /var/log/OpcUaStack/OpcUaDesigner)
install(DIRECTORY DESTINATION /var/log/OpcUaStack/OpcUaDesigner)

if (WIN32)
else() 
endif()

if (CPACK_BINARY_DEB)
    set( CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/OpcUaGui/linux/script/postinst"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/OpcUaGui/linux/script/preinst"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/OpcUaGui/linux/script/prerm"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/OpcUaGui/linux/script/postrm")
endif()

if (CPACK_BINARY_RPM)
    set(CPACK_RPM_POST_INSTALL_SCRIPT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/OpcUaGui/linux/script/postinst)
    set(CPACK_RPM_PRE_UNINSTALL_SCRIPT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/OpcUaGui/linux/script/prerm)
endif()
