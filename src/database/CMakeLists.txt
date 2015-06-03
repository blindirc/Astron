cmake_minimum_required(VERSION 2.8)
project(database)
include_directories(.)


### YAML Depedency -- required by config, used by yaml database ###
set(YAMLCPP_USE_STATIC_LIBS ON CACHE BOOL "If true, will try to find static YamlCpp first instead of dynamic.")
find_package(YamlCpp)
if(NOT YAMLCPP_FOUND)
	set(YAMLCPP_USE_STATIC_LIBS OFF CACHE BOOL "If true, will try to find static YamlCpp first instead of dynamic.")
	find_package(YamlCpp)
endif()
if(YAMLCPP_FOUND)
	include_directories(${YAMLCPP_INCLUDE_DIR})
	link_directories(${YAMLCPP_LIBRARY_DIR})
	message(STATUS "Found the following YamlCpp library:")
	message("  ${YAMLCPP_LIBRARY}\n")
else()
	message(FATAL_ERROR "You need yamlcpp to build this, build yamlcpp in the 'dependencies/' directory, or install it as a system package")
endif()

set(BUILD_YAML ON) # ON CACHE BOOL "Stuff"
if(BUILD_YAML)
	add_definitions(-DASTRON_WITH_YAML)
endif()



set(BUILD_DBSERVER ON CACHE BOOL "If on, Database Server will be built into binary")
if(BUILD_DBSERVER)
	add_definitions(-DBUILD_DBSERVER)
	set(DBSERVER_FILES
		DatabaseServer.h
		DatabaseServer.cpp
		DatabaseBackend.h
		DatabaseBackend.cpp
		DBOperation.h
		DBOperation.cpp
		DBOperationQueue.h
		DBOperationQueue.cpp
		OldDatabaseBackend.h
		OldDatabaseBackend.cpp
		DBBackendFactory.h
		DBBackendFactory.cpp
	)

	set(BUILD_DB_YAML ON CACHE BOOL "If on, will support a YAML-based database (for development)")
	if(BUILD_DB_YAML)
		add_definitions(-DBUILD_DB_YAML)
		set(DBSERVER_FILES
			${DBSERVER_FILES}
			YAMLDatabase.cpp
		)
		add_test(db_yaml "${PYTHON2_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/test/test_dbserver_yaml.py")
		add_test(validate_config_dbyaml "${PYTHON2_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/test/test_config_dbyaml.py")
		set(PYTHON_TESTS ${PYTHON_TESTS} db_yaml validate_config_dbyaml)
	endif()

	### Check for soci and if available, compile SQL database support ###
	find_package(Soci COMPONENTS postgresql mysql sqlite3)

	if(SOCI_FOUND)
		message(STATUS "Found the following Soci library:")
		message("  ${SOCI_LIBRARY}\n")

		message(STATUS "Found the following Soci plugins:")
		### PostgreSQL support ##
		if(SOCI_postgresql_FOUND)
			set(BUILD_DB_POSTGRESQL ON CACHE BOOL "If on, will support PostgreSQL.")
			message(STATUS "  PostgreSQL found")
			message("    ${SOCI_postgresql_PLUGIN}")
		else()
			unset(BUILD_DB_POSTGRESQL CACHE)
			message(STATUS "  PostgreSQL not found")
			message("    won't add PostgreSQl support")
		endif()

		### MySQL support ###
		if(SOCI_mysql_FOUND)
			set(BUILD_DB_MYSQL ON CACHE BOOL "If on, will support MySQL.")
			message(STATUS "  MySQL found")
			message("    ${SOCI_mysql_PLUGIN}")
		else()
			unset(BUILD_DB_MYSQL CACHE)
			message(STATUS "  MySQL not found")
			message("    won't add MySQL support")
		endif()

		### SQLite3 support ###
		if(SOCI_sqlite3_FOUND)
			set(BUILD_DB_SQLITE ON CACHE BOOL "If on, will support SQLite3.")
			message(STATUS "  SQLite3 found")
			message("    ${SOCI_sqlite3_PLUGIN}")
		else()
			unset(BUILD_DB_SQLITE CACHE)
			message(STATUS "  SQLite3 not found")
			message("    won't add SQLite3 support")
		endif()

		message("")

		### Add files to compiler and linker ###
		if(BUILD_DB_SQLITE OR BUILD_DB_MYSQL OR BUILD_DB_POSTGRESQL)
			add_definitions(-DBUILD_DB_SQL)
			include_directories(${SOCI_INCLUDE_DIRS})
			link_directories(${SOCI_LIBRARY_DIR})
			set(DBSERVER_FILES
				${DBSERVER_FILES}
				SociSQLDatabase.cpp
			)
			set(SOCI_LIBRARY_NAMES soci_core dl)
			if(BUILD_DB_POSTGRESQL)
				set(SOCI_LIBRARY_NAMES ${SOCI_LIBRARY_NAMES} pq)
				add_test(db_pgsql "${PYTHON2_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/test/test_dbserver_postgres.py")
				add_test(validate_config_dbpostgres
					 "${PYTHON2_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/test/test_config_dbpostgres.py")
				set(PYTHON_TESTS ${PYTHON_TESTS} db_pgsql validate_config_dbpostgres)
			endif()
		endif()
	else()
		message(STATUS "Soci not found")
		message("  won't add SQL support")
		unset(BUILD_DB_MYSQL CACHE)
		unset(BUILD_DB_POSTGRESQL CACHE)
		unset(BUILD_DB_SQLITE CACHE)
	endif()
else()
	unset(BUILD_DB_FILESYSTEM CACHE)
	unset(BUILD_DB_YAML CACHE)
	unset(BUILD_DB_MYSQL CACHE)
	unset(BUILD_DB_POSTGRESQL CACHE)
	unset(BUILD_DB_SQLITE CACHE)
endif()


add_library(database
	${DBSERVER_FILES}
)

target_link_libraries(database ${SOCI_LIBRARY_NAMES})