# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# build 
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
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

add_executable(
    OpcUaGui 
    ${OpcUaGui_SRC}
)

target_link_libraries(
    OpcUaGui
    ${pthread}
    ${OPCUASTACK_LIBRARY_CORE}
    ${OPCUASTACK_LIBRARY_CLIENT}
    ${Boost_LIBRARIES}
)

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# install
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
install(TARGETS OpcUaGui DESTINATION /usr/bin)

install(FILES ${PROJECT_SOURCE_DIR}/OpcUaGui/Config/OpcUaServer.xml DESTINATION /etc/OpcUaStack/OpcUaGui) 
install(FILES ${PROJECT_SOURCE_DIR}/OpcUaGui/Config/Opc.Ua.NodeSet.xml DESTINATION /etc/OpcUaStack/OpcUaGui)
install(FILES ${PROJECT_SOURCE_DIR}/OpcUaGui/linux/log/README DESTINATION /var/log/OpcUaStack/OpcUaGui)
install(DIRECTORY DESTINATION /var/log/OpcUaStack/OpcUaGui)

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
