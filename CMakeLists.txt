cmake_minimum_required(VERSION 3.29)

# Set a default build type if none was specified
set(DEFAULT_BUILD_TYPE "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build" FORCE)

	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
		"Debug" "Release" "MinSizeRel" "RelWithDebInfo"
	)
endif()

# Get project version from src/version.hpp
block(SCOPE_FOR VARIABLES PROPAGATE ROUNDHELL_VERSION)
	string(CONCAT VERSION_REGEX
		"#define[ \t]+ROUNDHELL_VERSION_MAJOR[ \t]+([0-9]+)"
		".*"
		"#define[ \t]+ROUNDHELL_VERSION_MINOR[ \t]+([0-9]+)"
		".*"
		"#define[ \t]+ROUNDHELL_VERSION_PATCH[ \t]+([0-9]+)"
	)
	file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/src/version.hpp" UNUSED
		REGEX ${VERSION_REGEX}
		LIMIT_COUNT 1
		NEWLINE_CONSUME
		ENCODING UTF-8
	)
	if (NOT CMAKE_MATCH_COUNT EQUAL 3)
		message(FATAL_ERROR "Version info in `src/version.hpp` not found or invalid")
	endif()
	set(ROUNDHELL_VERSION "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}")
endblock()

# Get id of current git commit
block(SCOPE_FOR VARIABLES PROPAGATE ROUNDHELL_COMMIT)
	set(commit "_NO_DATA")
	find_package(Git)
	if (Git_FOUND)
		execute_process(
			COMMAND ${GIT_EXECUTABLE} rev-parse --short=7 HEAD
			RESULT_VARIABLE result # return code from the last child or a string describing an error condition
			OUTPUT_VARIABLE output
			ERROR_VARIABLE error
			OUTPUT_STRIP_TRAILING_WHITESPACE
		)
		if (result EQUAL 0)
			set(commit "${output}")
		else()
			set(commit "_GIT_FAIL")
			message(WARNING
				"Cannot retrieve latest commit ID\n"
				"`git` exited with code ${result} and error message:\n"
				"${error}"
			)
		endif()
	else()
		set(commit "_NO_GIT")
		message(WARNING "Cannot get current commit ID: No Git found on system\n")
	endif()
	message(STATUS "Project's current commit ID: ${commit}")
	set(ROUNDHELL_COMMIT "${commit}")
endblock()

project(
	RoundHell
	LANGUAGES CXX
	DESCRIPTION "Simple bullet-hell game"
	VERSION "${ROUNDHELL_VERSION}"
)
message(STATUS "Building ${PROJECT_NAME} version ${PROJECT_VERSION} from commit ${ROUNDHELL_COMMIT}")

# If install prefix is not user-provided, use project's default.
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CACHE{CMAKE_INSTALL_PREFIX} TYPE PATH HELP "Install prefix" FORCE VALUE "${CMAKE_BINARY_DIR}/install")
endif()
message(STATUS "Install prefix is '${CMAKE_INSTALL_PREFIX}'")

configure_file(
	"${PROJECT_SOURCE_DIR}/src/config/project_path.hpp.in"
	"${PROJECT_BINARY_DIR}/src-generated/config/project_path.hpp"
	@ONLY
)

configure_file(
	"${PROJECT_SOURCE_DIR}/src/config/commit.hpp.in"
	"${PROJECT_BINARY_DIR}/src-generated/config/commit.hpp"
	@ONLY
)

set(EXECUTABLE_NAME round-hell)
set(TESTS_HOST_NAME "${EXECUTABLE_NAME}-tests")
set(COMMON_OBJS "${EXECUTABLE_NAME}-common-objs")

add_executable(${EXECUTABLE_NAME})
add_executable(${TESTS_HOST_NAME})

set_target_properties(${EXECUTABLE_NAME}
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
	#VERSION "${PROJECT_VERSION}"
)

target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_23)

if(MSVC)
	target_compile_options(${EXECUTABLE_NAME} PRIVATE /Wall /WX)
	target_compile_options(${EXECUTABLE_NAME} PRIVATE "$<$<CONFIG:Debug>:/DEBUG;/D_DEBUG>")
	target_compile_options(${EXECUTABLE_NAME} PRIVATE "$<$<CONFIG:Release>:/O2>")
else()
	target_compile_options(${EXECUTABLE_NAME} PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow)
	target_compile_options(${EXECUTABLE_NAME} PRIVATE "$<$<CONFIG:Debug>:-O0;-g3>")
	target_compile_options(${EXECUTABLE_NAME} PRIVATE "$<$<CONFIG:Release>:-O2>")
endif()

set_target_properties(${TESTS_HOST_NAME}
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
	#VERSION ${PROJECT_VERSION}
)

target_compile_features(${TESTS_HOST_NAME} PRIVATE cxx_std_23)

if(MSVC)
	target_compile_options(${TESTS_HOST_NAME} PRIVATE /Wall /WX)
	target_compile_options(${TESTS_HOST_NAME} PRIVATE "$<$<CONFIG:Debug>:/DEBUG;/D_DEBUG>")
	target_compile_options(${TESTS_HOST_NAME} PRIVATE "$<$<CONFIG:Release>:/O2>")
else()
	target_compile_options(${TESTS_HOST_NAME} PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow)
	target_compile_options(${TESTS_HOST_NAME} PRIVATE "$<$<CONFIG:Debug>:-O0;-g3>")
	target_compile_options(${TESTS_HOST_NAME} PRIVATE "$<$<CONFIG:Release>:-O2>")
endif()

add_subdirectory(extern)
add_subdirectory(src)

add_subdirectory(extern/Catch2)
add_subdirectory(tests)

target_link_libraries(${COMMON_OBJS}
	PUBLIC
		extern
)
target_include_directories(${COMMON_OBJS}
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/src/"
		"${CMAKE_BINARY_DIR}/src-generated/"
)

target_link_libraries(${EXECUTABLE_NAME}
	PRIVATE
		${COMMON_OBJS}
)

target_link_libraries(${TESTS_HOST_NAME}
	PRIVATE
		Catch2::Catch2WithMain
		${COMMON_OBJS}
)

target_compile_definitions(${TESTS_HOST_NAME}
	PRIVATE
		ROUNDHELL_TESTING
)

add_custom_command(
	TARGET ${EXECUTABLE_NAME}
	POST_BUILD
	COMMAND
		${CMAKE_COMMAND} -E create_symlink
			"${CMAKE_SOURCE_DIR}/assets"
			"${CMAKE_BINARY_DIR}/bin/$<CONFIG>/assets"
	VERBATIM
)

