# Check for system zlib:
# ===================================================
SET(CMAKE_FBLIB_HAS_ZLIB 1)	# Always present: system or built-in
IF(MSVC)
	SET(CMAKE_FBLIB_HAS_ZLIB_SYSTEM 0)
ELSE(MSVC)
	FIND_PACKAGE(ZLIB)
	IF(ZLIB_FOUND)
			#MESSAGE(STATUS "Found library: zlib - Include: ${ZLIB_INCLUDE_DIR}")
			INCLUDE_DIRECTORIES("${ZLIB_INCLUDE_DIR}")

			SET(FBLIB_ZLIB_LIBS zlib) # APPEND_FBLIB_LIBS(z)

			SET(CMAKE_FBLIB_HAS_ZLIB_SYSTEM 1)
	ELSE(ZLIB_FOUND)
			
			SET(CMAKE_FBLIB_HAS_ZLIB_SYSTEM 0)			

	ENDIF(ZLIB_FOUND)
ENDIF(MSVC)
