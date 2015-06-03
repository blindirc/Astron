cmake_minimum_required(VERSION 2.8)
project(stateserver)
include_directories(.)


set(BUILD_STATESERVER ON CACHE BOOL "If on, State Server will be built into binary")
if(BUILD_STATESERVER)
	set(STATESERVER_FILES
		StateServer.cpp
		StateServer.h
		DistributedObject.cpp
		DistributedObject.h
	)
	add_test(stateserver "${PYTHON2_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/test/test_stateserver.py")
	add_test(validate_config_stateserver "${PYTHON2_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/test/test_config_stateserver.py")
	set(PYTHON_TESTS ${PYTHON_TESTS} stateserver validate_config_stateserver)

	set(BUILD_STATESERVER_DBSS ON CACHE BOOL "If on, the Database-State Server will be built into binary")
	if(BUILD_STATESERVER_DBSS)
		set(STATESERVER_FILES
			${STATESERVER_FILES}
			DBStateServer.h
			DBStateServer.cpp
			LoadingObject.h
			LoadingObject.cpp
		)
		add_test(dbss "${PYTHON2_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/test/test_dbss.py")
		add_test(validate_config_dbss "${PYTHON2_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/test/test_config_dbss.py")
		set(PYTHON_TESTS ${PYTHON_TESTS} dbss validate_config_dbss)
	endif()
else()
	unset(BUILD_STATESERVER_DBSS CACHE)
endif()

if(STATESERVER_FILES)
	add_definitions(-DBUILD_STATESERVER)
	source_group("StateServer" FILES ${STATESERVER_FILES})
endif()



add_library(stateserver
	${STATESERVER_FILES}
)
#SET_TARGET_PROPERTIES(dclass PROPERTIES LINK_FLAGS -lfl)
