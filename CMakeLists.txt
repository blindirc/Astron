cmake_minimum_required(VERSION 2.8.9 FATAL_ERROR) # Required for FindBoost
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
project(Astron)

find_package(PythonLibs)
find_package(PythonInterp)
if(PYTHONINTERP_FOUND)
	enable_testing()
	if(PYTHON_VERSION_MAJOR EQUAL 2)
		set(PYTHON2_EXECUTABLE "${PYTHON_EXECUTABLE}")
	else()
		set(PYTHON2_EXECUTABLE python2)
	endif()
endif()

### Configure CMake to use our extra Find modules ###
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")


### Define extra windows defines ###
if(WIN32)
	add_definitions(-D_WIN32_WINDOWS)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
endif()

### Set build type to Release with Debug Info by default ###
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type.")
endif()
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
	RelWithDebInfo Release Debug)

### Define astron’s git aha for use in program ###
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
	find_package(Git)
	if(GIT_FOUND)
		exec_program(
			"${GIT_EXECUTABLE}"
			"${CMAKE_CURRENT_SOURCE_DIR}"
			ARGS "describe --abbrev=8 --dirty --always"
			OUTPUT_VARIABLE GIT_SHA_VERSION
		)

		add_definitions(-DGIT_SHA1="${GIT_SHA_VERSION}")
	endif()
endif()


### Add per-compiler flags ###
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
   CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -Wall -Wextra")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO
		"${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g -Wall")

	# warnings are errors, release code should not have warnings
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Wall -Werror")

	# debug flags, wall, wextra
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Wextra")
endif()

if(CMAKE_GENERATOR STREQUAL Xcode)
	set(CMAKE_CXX_FLAGS_RELEASE
		"${CMAKE_CXX_FLAGS_RELEASE} -std=c++0x -stdlib=libc++")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO
		"${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -std=c++0x -stdlib=libc++")
	set(CMAKE_CXX_FLAGS_DEBUG
		"${CMAKE_CXX_FLAGS_DEBUG} -std=c++0x -stdlib=libc++")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_definitions(-std=c++11)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	execute_process(COMMAND "${CMAKE_C_COMPILER}" -dumpversion OUTPUT_VARIABLE GCC_VERSION)
	message(STATUS "GCC Version: ${GCC_VERSION}")
	if(GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
		add_definitions(-std=c++11) # Enable the new C++ standard
	else()
		add_definitions(-std=c++0x) # Enable the new C++ standard
	endif()
endif()


### Debug Flags -- compile in spam/debug log messages ###
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DASTRON_DEBUG_MESSAGES")


### OS Specific Settings ###
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")		### Linux requires pthreads
	set(CMAKE_CXX_FLAGS "-pthread")
endif()


### BOOST Dependency -- required by yaml-cpp and networking ###
set(Boost_USE_STATIC_LIBS ON CACHE BOOL "If true, will try to find static Boost first instead of dynamic.")
find_package(Boost COMPONENTS system filesystem)
if(NOT Boost_FOUND)
	unset(Boost_USE_STATIC_LIBS CACHE)
	set (Boost_USE_STATIC_LIBS OFF CACHE BOOL "If true, will try to find static Boost first instead of dynamic.")
	find_package(Boost COMPONENTS system filesystem)
	if(NOT Boost_FOUND)
		unset(Boost_USE_STATIC_LIBS CACHE)
	endif()
endif()
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIR})
	link_directories(${Boost_LIBRARY_DIRS})
	message("  ${Boost_LIBRARIES}\n")
else()
	message(FATAL_ERROR "You need boost to build this, set the BOOST_ROOT or BOOSTROOT env variables, or pass them to cmake")
endif()

add_definitions(
	-DBOOST_ALL_NO_LIB
	-D_SCL_SECURE_NO_WARNINGS
)

### SSL Dependency -- required by Boost::ASIO's SSL library
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
	include_directories(${OPENSSL_INCLUDE_DIR})
else()
	message(FATAL_ERROR "You need OpenSSL to build this.")
endif()

set(USE_32BIT_DATAGRAMS OFF CACHE BOOL
	"If on, datagrams and dclass fields will use 32-bit length tags instead of 16-bit.")
if(USE_32BIT_DATAGRAMS)
	add_definitions(-DASTRON_32BIT_DATAGRAMS)
	add_definitions(-DDCLASS_32BIT_SIZETAG)
endif()
set(USE_128BIT_CHANNELS OFF CACHE BOOL
	"If on, channels will be 128-bit and doids and zones will be 64-bit (instead of 64/32).")
if(USE_128BIT_CHANNELS)
	add_definitions(-DASTRON_128BIT_CHANNELS)
endif()

set(BUILD_TESTS OFF CACHE BOOL "If set to true, test files will be compiled in")
if(BUILD_TESTS)
	set(TEST_FILES
		src/tests/MDParticipantTest.cpp
		src/tests/MDPerformanceTest.cpp
	)
endif()

### Define core components ###
set(CORE_FILES
	src/core/global.h
	src/core/global.cpp
	src/core/main.cpp
	src/core/Logger.h
	src/core/Logger.cpp
	src/core/Role.h
	src/core/Role.cpp
	src/core/RoleFactory.h
	src/core/RoleFactory.cpp
	src/core/shutdown.h
	src/core/shutdown.cpp
	src/core/types.h
	src/core/msgtypes.h
)

set(CONFIG_FILES
	src/config/ConfigGroup.h
	src/config/ConfigGroup.cpp
	src/config/ConfigVariable.h
	src/config/ConfigVariable.cpp
	src/config/constraints.cpp
)

set(MESSAGEDIRECTOR_FILES
	src/messagedirector/ChannelMap.cpp
	src/messagedirector/ChannelMap.h
	src/messagedirector/MessageDirector.cpp
	src/messagedirector/MessageDirector.h
	src/messagedirector/MDNetworkParticipant.cpp
	src/messagedirector/MDNetworkParticipant.h
	src/messagedirector/MDNetworkUpstream.cpp
	src/messagedirector/MDNetworkUpstream.h
)

set(UTIL_FILES
	src/util/Datagram.h
	src/util/DatagramIterator.h
	src/util/EventSender.cpp
	src/util/EventSender.h
	src/util/password_prompt.cpp
	src/util/password_prompt.h
	src/util/Timeout.cpp
	src/util/Timeout.h
)

set(NET_FILES
	src/net/address_utils.cpp
	src/net/address_utils.h
	src/net/NetworkAcceptor.cpp
	src/net/NetworkAcceptor.h
	src/net/NetworkClient.cpp
	src/net/NetworkClient.h
	src/net/NetworkConnector.cpp
	src/net/NetworkConnector.h
	src/net/TcpAcceptor.cpp
	src/net/TcpAcceptor.h
	src/net/SslAcceptor.cpp
	src/net/SslAcceptor.h
)

include_directories(src)
add_test(validate_config_core "${PYTHON2_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/test/test_config.py")
add_test(messagedirector "${PYTHON2_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/test/test_messagedirector.py")
set(PYTHON_TESTS ${PYTHON_TESTS} messagedirector)
add_executable(astrond
	${CORE_FILES}
	${CONFIG_FILES}
	${MESSAGEDIRECTOR_FILES}
	${UTIL_FILES}
  ${NET_FILES}
	${TEST_FILES}
)

### Setup source groups and defines for configurables ###
source_group("Core" FILES ${CORE_FILES})
source_group("Config" FILES ${CONFIG_FILES})
source_group("Util" FILES ${UTIL_FILES})
source_group("MessageDirector" FILES ${MESSAGEDIRECTOR_FILES})
source_group("Net" FILES ${NET_FILES})
if(TEST_FILES)
	source_group("DaemonTests" FILES ${TEST_FILES})
endif()

### Header source group ###
#foreach(sourcefile IN LISTS ASTROND_SOURCES)
#	if(sourcefile MATCHES .*\\.h)
#		set(ASTROND_HEADERS "${ASTROND_HEADERS} ${sourcefile}")
#	endif()
#endforeach(sourcefile)
#source_group("Header Files" FILES ${ASTROND_HEADERS})


add_subdirectory(src/dclass)

#Default Modules
add_subdirectory(src/stateserver)
add_subdirectory(src/eventlogger)
add_subdirectory(src/database)
add_subdirectory(src/clientagent)

add_dependencies(astrond dclass)
target_link_libraries(astrond dclass ${OPENSSL_LIBRARIES} ${YAMLCPP_LIBNAME} ${Boost_LIBRARIES})

### Handle some final testing configuration ###
if(USE_32BIT_DATAGRAMS)
	set(PYTHON_TEST_ENV ${PYTHON_TEST_ENV} "USE_32BIT_DATAGRAMS=true")
endif()
if(USE_128BIT_CHANNELS)
	set(PYTHON_TEST_ENV ${PYTHON_TEST_ENV} "USE_128BIT_CHANNELS=true")
endif()
if(PYTHON_TEST_ENV)
	set_tests_properties(${PYTHON_TESTS} PROPERTIES ENVIRONMENT "${PYTHON_TEST_ENV}")
endif()
