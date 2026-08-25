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
		"${CMAKE_CURRENT_SOURCE_DIR}/components/sprite.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/components/animation.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/loaders/sdl_texture_loader.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/loaders/subtexture_loader.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/loaders/animation_data_loader.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/data/resources_data.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/components/relation.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/utils/traverse.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/utils/entt.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/components/transform.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/systems/world_transform_updater.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/components/order.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/systems/animation.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/systems/sprite_renderer.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/systems/fps_limiter.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/systems/frame_counter.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/components/movement.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/systems/movement.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/systems/random_movement.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/entity_builder.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/application.cpp"
)

