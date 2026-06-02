add_library(${COMMON_OBJS})

target_compile_features(${COMMON_OBJS} PUBLIC cxx_std_23)

if(MSVC)
	target_compile_options(${COMMON_OBJS} PRIVATE /Wall /WX)
	target_compile_options(${COMMON_OBJS} PRIVATE "$<$<CONFIG:Debug>:/DEBUG;/D_DEBUG>")
	target_compile_options(${COMMON_OBJS} PRIVATE "$<$<CONFIG:Release>:/O2>")
else()
	target_compile_options(${COMMON_OBJS} PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow)
	target_compile_options(${COMMON_OBJS} PRIVATE "$<$<CONFIG:Debug>:-O0;-g3>")
	target_compile_options(${COMMON_OBJS} PRIVATE "$<$<CONFIG:Release>:-O2>")
endif()

target_sources(${EXECUTABLE_NAME}
	PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

target_sources(${COMMON_OBJS}
	PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/errors.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/clock.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/any_component.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/subtexture.cpp"
)

