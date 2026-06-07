target_sources(${TESTS_HOST_NAME}
	PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/config.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/version.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/errors.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/clock.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/subtexture.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/resource_multi_cache.cpp"
)

