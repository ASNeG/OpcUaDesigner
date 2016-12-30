# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# build 
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

add_definitions(
    ${Qt5Widgets_DEFINITIONS}
)

include_directories(
    ${OPCUASTACK_INSTALL_PREFIX}/usr/include/OpcUaStack${OPCUASTACK_VERSION_MAJOR}
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR}
    ${Qt5Widgets_INCLUDE_DIRS}
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


add_library(
    OpcUaNodeSetModul SHARED 
    ${OpcUaNodeSetModul_RES}
    ${OpcUaNodeSetModul_SRC}
)

target_link_libraries(
    OpcUaNodeSetModul
    ${pthread}
    ${OPCUASTACK_LIBRARY_CORE}
    ${OPCUASTACK_LIBRARY_CLIENT}
    ${Boost_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
)


# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# install
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
install(TARGETS OpcUaNodeSetModul DESTINATION /usr/lib)

install(FILES ${PROJECT_SOURCE_DIR}/OpcUaNodeSetModul/Config/OpcUaNodeSet.Modul.xml DESTINATION /etc/OpcUaStack/OpcUaDesigner) 

