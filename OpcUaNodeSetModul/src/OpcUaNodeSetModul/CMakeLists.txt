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
    ${PROJECT_SOURCE_DIR}/../../OpcUaDesigner/src
    ${Boost_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR}
)

file(
    GLOB 
    OpcUaNodeSetModul_SRC 
    ${PROJECT_SOURCE_DIR}/OpcUaNodeSetModul/*/*.cpp
)

QT5_ADD_RESOURCES(
    OpcUaNodeSetModul_RES
    OpcUaNodeSetModul/Resources/OpcUaNodeSetModul.qrc
)

#qt5_wrap_cpp(
#    moc_files OpcUaGui/ModulInterface/ModulInterface.h
#)

add_library(
    OpcUaNodeSetModul SHARED 
    ${OpcUaNodeSetModul_RES}
    ${OpcUaNodeSetModul_SRC}
    ${moc_files}
)

target_link_libraries(
    OpcUaNodeSetModul
    ${pthread}
    ${OPCUASTACK_LIBRARY_CORE}
    ${OPCUASTACK_LIBRARY_CLIENT}
    ${OPCUASTACK_LIBRARY_SERVER}
    ${Boost_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Core_LIBRARIES}
)

set_target_properties(
    OpcUaNodeSetModul 
    PROPERTIES COMPILE_DEFINITIONS "MYSHAREDLIB_LIBRARY"
)


# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# install
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
install(TARGETS OpcUaNodeSetModul DESTINATION /usr/lib)

install(FILES ${PROJECT_SOURCE_DIR}/OpcUaNodeSetModul/Config/OpcUaNodeSetModul.xml DESTINATION /etc/OpcUaStack/OpcUaDesigner/Modul) 

