cmake_minimum_required(VERSION 3.09)
project(SSLWrap)

set(LIB_NAME SSLWrap)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -pthread -lstdc++fs")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

file(GLOB_RECURSE SOURCE_FILES "lib/*.cpp")
file(GLOB_RECURSE INCLUDE_FILES "lib/*.hpp")

add_library(${LIB_NAME} SHARED ${SOURCE_FILES})
target_include_directories(${LIB_NAME} PRIVATE ${src})

set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER "${INCLUDE_FILES}")

#Find and link OpenSSL
	find_package(OpenSSL REQUIRED)
	target_include_directories(${LIB_NAME} PRIVATE ${OPENSSL_INCLUDE_DIR})
	target_link_libraries(${LIB_NAME} ${OPENSSL_LIBRARIES})

target_link_libraries(${LIB_NAME} stdc++fs)

set(SSLWRAP_DEPS ${OPENSSL_LIBRARIES};stdc++fs)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif (NOT CMAKE_BUILD_TYPE)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(SSLWRAP_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/sslwrap CACHE STRING
		"Where to install the cmake files, relative to ${CMAKE_INSTALL_PREFIX}.")
set(SSLWRAP_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR} CACHE STRING
		"Where to install the library file, relative to ${CMAKE_INSTALL_PREFIX}")
set(SSLWRAP_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/SSLWrap CACHE STRING
		"Where to install the include files, relative to ${CMAKE_INSTALL_PREFIX}.")

set(CONFIG_OUTPUT ${PROJECT_BINARY_DIR}/sslwrap-config.cmake)
configure_package_config_file(${PROJECT_SOURCE_DIR}/install/sslwrap-config.cmake.in ${CONFIG_OUTPUT}
		INSTALL_DESTINATION ${SSLWRAP_CMAKE_DIR})

install(TARGETS ${LIB_NAME}
		LIBRARY
			DESTINATION ${CMAKE_INSTALL_PREFIX}/${SSLWRAP_INSTALL_DIR}
		PUBLIC_HEADER
			DESTINATION ${CMAKE_INSTALL_PREFIX}/${SSLWRAP_INCLUDE_DIR}
		)
install(FILES ${CONFIG_OUTPUT} DESTINATION ${CMAKE_INSTALL_PREFIX}/${SSLWRAP_CMAKE_DIR})