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
    OpcUaClientModul_SRC 
    ${PROJECT_SOURCE_DIR}/OpcUaClientModul/*/*.cpp
)

QT5_ADD_RESOURCES(
    OpcUaClientModul_RES
    OpcUaClientModul/Resources/OpcUaClientModul.qrc
)

#qt5_wrap_cpp(
#    moc_files OpcUaGui/ModulInterface/ModulInterface.h
#)

add_library(
    OpcUaClientModul SHARED 
    ${OpcUaClientModul_RES}
    ${OpcUaClientModul_SRC}
    ${moc_files}
)

target_link_libraries(
    OpcUaClientModul
    ${pthread}
    ${OPCUASTACK_LIBRARY_CORE}
    ${OPCUASTACK_LIBRARY_CLIENT}
    ${Boost_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Core_LIBRARIES}
)

set_target_properties(
    OpcUaClientModul 
    PROPERTIES COMPILE_DEFINITIONS "MYSHAREDLIB_LIBRARY"
)


# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# install
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
install(TARGETS OpcUaClientModul DESTINATION /usr/lib)

install(FILES ${PROJECT_SOURCE_DIR}/OpcUaClientModul/Config/OpcUaClientModul.xml DESTINATION /etc/OpcUaStack/OpcUaDesigner/Modul) 

