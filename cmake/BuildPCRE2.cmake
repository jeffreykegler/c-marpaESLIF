INCLUDE (ExternalProject)

#
# Be toolchain compatible in any case (i.e. no test on CMAKE_CROSSCOMPILING)
#
SET (_CMAKE_CACHE_ARGS
#  -DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS}
  -DBUILD_CLAR:BOOL=${BUILD_CLAR}
  -DTHREADSAFE:BOOL=${THREADSAFE}
  -DCMAKE_SYSTEM_NAME:STRING=${CMAKE_SYSTEM_NAME}
  -DCMAKE_C_COMPILER:PATH=${CMAKE_C_COMPILER}
  -DCMAKE_CXX_COMPILER:PATH=${CMAKE_CXX_COMPILER}
  -DCMAKE_RC_COMPILER:PATH=${CMAKE_RC_COMPILER}
  -DDLLTOOL:PATH=${DLLTOOL}
  -DCMAKE_FIND_ROOT_PATH:PATH=${CMAKE_FIND_ROOT_PATH}
  -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE:STRING=${CMAKE_FIND_ROOT_PATH_MODE_INCLUDE}
  -DWIN32:BOOL=${WIN32}
  -DTARGET_TEST_SYSTEM:STRING=${TARGET_TEST_SYSTEM}
  -DTARGET_TEST_CMAKE_COMMAND:STRING=${TARGET_TEST_SYSTEM_COMMAND}
  )

#
# We always force PCRE2 in release mode
#
SET (_PCRE2_CMAKE_ARGS
  "-DCMAKE_INSTALL_PREFIX:PATH=${3RDPARTY_OUTPUT_PATH}"
  -DCMAKE_BUILD_TYPE:STRING=Release
  -DBUILD_SHARED_LIBS=N
  -DPCRE2_BUILD_PCRE2_8=Y
  -DPCRE2_BUILD_PCRE2_16=N
  -DPCRE2_BUILD_PCRE2_32=N
  -DPCRE2_BUILD_PCRE2GREP=N
  -DPCRE2_SUPPORT_JIT=Y
  -DPCRE2_BUILD_TESTS=N)
IF (MSVC)
  LIST (APPEND _PCRE2_CMAKE_ARGS "-DPCRE2_STATIC_RUNTIME=1")
ENDIF ()
IF (FIXME_CMAKE_ABSOLUTE)
  LIST (APPEND _PCRE2_CMAKE_ARGS "-DPCRE2_CMAKE_INCLUDE=${FIXME_CMAKE_ABSOLUTE}")
ENDIF ()
#
# We force the install command with DESTDIR= in any case, so that it always remains local
# even if user says "make install DESTDIR=/somewhere/else
#
# On Unix this is make
# On Unix this is nmake, usually lowercase (I have never seen this with capital letter(s))
#
MESSAGE(STATUS "Starting ExternalProject_Add for PCRE2 with:")
MESSAGE(STATUS "CMAKE_ARGS=${_PCRE2_CMAKE_ARGS}")
MESSAGE(STATUS "CMAKE_CACHE_ARGS=${_CMAKE_CACHE_ARGS}")
IF ("${CMAKE_MAKE_PROGRAM}" MATCHES ".*make")
  EXTERNALPROJECT_ADD(pcre2
    URL "${PROJECT_SOURCE_DIR}/3rdparty/tar/pcre2-10.23-patched.tar.gz"
    UPDATE_COMMAND "${CMAKE_COMMAND}" -E copy "${PROJECT_SOURCE_DIR}/3rdparty/tar/pcre2-10.23/CMakeLists_fixed.txt" "${CMAKE_CURRENT_BINARY_DIR}/pcre2/src/pcre2/CMakeLists.txt"
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/pcre2"
    CMAKE_ARGS ${_PCRE2_CMAKE_ARGS}
    CMAKE_CACHE_ARGS ${_CMAKE_CACHE_ARGS}
    INSTALL_COMMAND "${CMAKE_MAKE_PROGRAM}" install DESTDIR=
    )
ELSE ()
  EXTERNALPROJECT_ADD(pcre2
    URL "${PROJECT_SOURCE_DIR}/3rdparty/tar/pcre2-10.23-patched.tar.gz"
    UPDATE_COMMAND "${CMAKE_COMMAND}" -E copy "${PROJECT_SOURCE_DIR}/3rdparty/tar/pcre2-10.23/CMakeLists_fixed.txt" "${CMAKE_CURRENT_BINARY_DIR}/pcre2/src/pcre2/CMakeLists.txt"
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/pcre2"
    CMAKE_ARGS ${_PCRE2_CMAKE_ARGS}
    CMAKE_CACHE_ARGS ${_CMAKE_CACHE_ARGS}
    #
    # Only make (nmake) can handle the install DESTDIR= argument AFAIK
    #
    # INSTALL_COMMAND "${CMAKE_MAKE_PROGRAM}" install DESTDIR=
    )
ENDIF ()
SET (PCRE2_INCLUDE_DIR "${3RDPARTY_OUTPUT_PATH}/include")
SET (PCRE2_LINK_FLAGS  "${3RDPARTY_OUTPUT_PATH}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}pcre2-8${CMAKE_STATIC_LIBRARY_SUFFIX}")
SET (PCRE2_LIBRARIES   "${PCRE2_LINK_FLAGS}")
MESSAGE(STATUS "-----------------------------------------")
MESSAGE(STATUS "Setup PCRE2:")
MESSAGE(STATUS "")
MESSAGE(STATUS "        INCLUDE_DIR: ${PCRE2_INCLUDE_DIR}")
MESSAGE(STATUS "         LINK_FLAGS: ${PCRE2_LINK_FLAGS}")
MESSAGE(STATUS "          LIBRARIES: ${PCRE2_LIBRARIES}")
MESSAGE(STATUS "-----------------------------------------")
SET (PCRE2_INCLUDE_DIRS "${PCRE2_INCLUDE_DIR}")
#
# For linkage in static mode
#
# ADD_DEFINITIONS(-DPCRE2_EXP_DECL=extern)

SET (PCRE2_FOUND FALSE)
MARK_AS_ADVANCED (
  PCRE2_FOUND
  PCRE2_INCLUDE_DIRS
  PCRE2_LIBRARIES
  )
