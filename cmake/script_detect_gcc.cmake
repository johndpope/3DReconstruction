# ----------------------------------------------------------------------------
# Detect GNU version:
# ----------------------------------------------------------------------------
IF(CMAKE_COMPILER_IS_GNUCXX)
	execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion
		          OUTPUT_VARIABLE CMAKE_FBLIB_GCC_VERSION_FULL
		          OUTPUT_STRIP_TRAILING_WHITESPACE)

	# Output in CMAKE_FBLIB_GCC_VERSION_FULL: "X.Y"
	#  Look for the version number
	STRING(REGEX MATCH "[0-9]+.[0-9]+" CMAKE_GCC_REGEX_VERSION "${CMAKE_FBLIB_GCC_VERSION_FULL}")

	# Split the three parts:
	STRING(REGEX MATCHALL "[0-9]+" CMAKE_FBLIB_GCC_VERSIONS "${CMAKE_GCC_REGEX_VERSION}")

	LIST(GET CMAKE_FBLIB_GCC_VERSIONS 0 CMAKE_FBLIB_GCC_VERSION_MAJOR)
	LIST(GET CMAKE_FBLIB_GCC_VERSIONS 1 CMAKE_FBLIB_GCC_VERSION_MINOR)

	SET(CMAKE_FBLIB_GCC_VERSION ${CMAKE_FBLIB_GCC_VERSION_MAJOR}${CMAKE_FBLIB_GCC_VERSION_MINOR})

	IF($ENV{VERBOSE})
		MESSAGE(STATUS "gcc -dumpversion: ${CMAKE_FBLIB_GCC_VERSION_FULL}  -> Major=${CMAKE_FBLIB_GCC_VERSION_MAJOR} Minor=${CMAKE_FBLIB_GCC_VERSION_MINOR}")
	ENDIF($ENV{VERBOSE})
ENDIF(CMAKE_COMPILER_IS_GNUCXX)