cmake_minimum_required(VERSION 2.8)
project(eventlogger)
include_directories(.)

set(BUILD_EVENTLOGGER ON CACHE BOOL "If on, Event Logger will be built into binary")
if(BUILD_EVENTLOGGER)
	set(EVENTLOGGER_FILES
		EventLogger.cpp
		EventLogger.h
	)
	add_test(eventlogger "${PYTHON2_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/test/test_eventlogger.py")
	add_test(validate_config_eventlogger "${PYTHON2_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/test/test_config_eventlogger.py")
endif()


if(EVENTLOGGER_FILES)
	add_definitions(-DBUILD_EVENTLOGGER)
	source_group("EventLogger" FILES ${EVENTLOGGER_FILES})
endif()


add_library(eventlogger
	${EVENTLOGGER_FILES}
)
#SET_TARGET_PROPERTIES(dclass PROPERTIES LINK_FLAGS -lfl)
