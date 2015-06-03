cmake_minimum_required(VERSION 2.8)
project(clientagent)
include_directories(.)



set(BUILD_CLIENTAGENT ON CACHE BOOL "If on, Client Agent will be built into binary")
if(BUILD_CLIENTAGENT)
	set(CLIENTAGENT_FILES
		Client.h
		Client.cpp
		ClientAgent.h
		ClientAgent.cpp
		ClientMessages.h
		ClientFactory.cpp
		ClientFactory.h
		AstronClient.cpp
	)
	add_test(clientagent "${PYTHON2_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/test/test_clientagent.py")
	add_test(validate_config_clientagent "${PYTHON2_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/test/test_config_clientagent.py")
	set(PYTHON_TESTS ${PYTHON_TESTS} clientagent validate_config_clientagent)
endif()

if(CLIENTAGENT_FILES)
	add_definitions(-DBUILD_CLIENTAGENT)
	source_group("ClientAgent" FILES ${CLIENTAGENT_FILES})
endif()


add_library(clientagent
	${CLIENTAGENT_FILES}
)
#SET_TARGET_PROPERTIES(dclass PROPERTIES LINK_FLAGS -lfl)
