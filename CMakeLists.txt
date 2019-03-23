cmake_minimum_required(VERSION 3.09)
project(libSSLWrap VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
set(SSLWRAP_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/sslwrap CACHE STRING
		"Where to install the cmake files, relative to ${CMAKE_INSTALL_PREFIX}.")
set(SSLWRAP_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR} CACHE STRING
		"Where to install the library file, relative to ${CMAKE_INSTALL_PREFIX}")
set(SSLWRAP_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/SSLWrap CACHE STRING
		"Where to install the include files, relative to ${CMAKE_INSTALL_PREFIX}.")
option(BUILD_SHARED_LIBS "Build shared libraries (.so) instead of static ones (.a)" ON)

add_library(sslwrap src/ClientContext.cpp src/Context.cpp src/init.cpp src/IpAddress.cpp src/Listener.cpp
		src/Packet.cpp src/ServerContext.cpp src/Socket.cpp src/SSLError.cpp)

add_library(SSLWrap::sslwrap ALIAS sslwrap)

target_include_directories(sslwrap
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif (NOT CMAKE_BUILD_TYPE)

target_compile_options(sslwrap PRIVATE -Wall -Wextra -pedantic)
target_compile_options(sslwrap PRIVATE "$<$<CONFIG:DEBUG>:-g>")
target_compile_options(sslwrap PRIVATE "$<$<CONFIG:RELEASE>:-O3;-Werror>")

#Find and link OpenSSL
	find_package(OpenSSL REQUIRED)
	target_link_libraries(sslwrap PRIVATE OpenSSL::SSL)

install(TARGETS sslwrap
	EXPORT sslwarp-targets
	LIBRARY DESTINATION ${SSLWRAP_INSTALL_DIR}
	ARCHIVE DESTINATION ${SSLWRAP_INSTALL_DIR}
)

set_target_properties(sslwrap PROPERTIES EXPORT_NAME SSLWrap)

install(DIRECTORY include/ DESTINATION ${SSLWRAP_INCLUDE_DIR})
install(EXPORT sslwarp-targets
	FILE
		SSLWrapTargets.cmake
	NAMESPACE
		SSLWrap::
	DESTINATION
		${SSLWRAP_CMAKE_DIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/SSLWrapConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion
)

set(CONFIG_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/SSLWrapConfig.cmake)
configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/install/SSLWrapConfig.cmake.in ${CONFIG_OUTPUT}
	INSTALL_DESTINATION ${SSLWRAP_CMAKE_DIR})

install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/SSLWrapConfig.cmake
	${CMAKE_CURRENT_BINARY_DIR}/SSLWrapConfigVersion.cmake
	DESTINATION ${SSLWRAP_CMAKE_DIR}
)

export(EXPORT sslwarp-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/SSLWrapTargets.cmake NAMESPACE SSLWrap::)

export(PACKAGE SSLWrap)