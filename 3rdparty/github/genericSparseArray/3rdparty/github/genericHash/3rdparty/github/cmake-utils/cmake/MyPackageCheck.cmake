MACRO (MYPACKAGECHECK name)

  GET_PROPERTY(_test_path_set GLOBAL PROPERTY MYPACKAGE_TEST_PATH SET)
  IF (${_test_path_set})
    GET_PROPERTY(_test_path GLOBAL PROPERTY MYPACKAGE_TEST_PATH)
  ELSE ()
    SET (_test_path $ENV{PATH})
    IF ("${CMAKE_HOST_SYSTEM}" MATCHES ".*Windows.*")
      STRING(REGEX REPLACE "/" "\\\\"  _test_path "${_test_path}")
    ELSE ()
      STRING(REGEX REPLACE " " "\\\\ "  _test_path "${_test_path}")
    ENDIF ()
    MESSAGE(STATUS "[${PROJECT_NAME}-CHECK-STATUS] Initializing TEST_PATH with PATH")
    SET_PROPERTY(GLOBAL PROPERTY MYPACKAGE_TEST_PATH ${_test_path})
  ENDIF ()

  GET_PROPERTY(_targets_for_test_set GLOBAL PROPERTY MYPACKAGE_DEPENDENCY_${PROJECT_NAME}_TARGETS_FOR_TEST SET)
  IF (_targets_for_test_set)
    IF ("${CMAKE_HOST_SYSTEM}" MATCHES ".*Windows.*")
      SET (SEP "\\;")
    ELSE ()
      SET (SEP ":")
    ENDIF ()
    SET (_targets_log_for_eval)

    GET_PROPERTY(_targets_for_test GLOBAL PROPERTY MYPACKAGE_DEPENDENCY_${PROJECT_NAME}_TARGETS_FOR_TEST)
    FOREACH (_target ${_targets_for_test})
      IF (NOT ("${_test_path}" STREQUAL ""))
        SET (_test_path "\$<TARGET_FILE_DIR:${_target}>${SEP}${_test_path}")
      ELSE ()
        SET (_test_path "\$<TARGET_FILE_DIR:${_target}>")
      ENDIF ()
    ENDFOREACH ()
  ENDIF ()

  IF (NOT ("x${TARGET_TEST_CMAKE_COMMAND}" STREQUAL "x"))
    GET_FILENAME_COMPONENT(_target_test_cmake_command ${TARGET_TEST_CMAKE_COMMAND} ABSOLUTE)
  ELSE ()
    SET (_target_test_cmake_command "")
  ENDIF ()
  FOREACH (_name ${name} ${name}_static)
    ADD_TEST (NAME ${_name}
      COMMAND ${CMAKE_COMMAND} -E env "PATH=${_test_path}" ${_target_test_cmake_command} $<TARGET_FILE:${_name}> ${ARGN}
      WORKING_DIRECTORY ${LIBRARY_OUTPUT_PATH})
    ADD_DEPENDENCIES(check ${_name})
  ENDFOREACH ()

ENDMACRO()