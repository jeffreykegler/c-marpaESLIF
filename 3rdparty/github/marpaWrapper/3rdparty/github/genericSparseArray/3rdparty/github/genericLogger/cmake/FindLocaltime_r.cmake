INCLUDE (StringToInternalBool)
MACRO (FINDLOCALTIME_R)
  #
  # Dependencies
  #
  STRINGTOINTERNALBOOL(_HAVE_TIME_H HAVE_TIME_H)
  #
  # Test
  #
  FOREACH (KEYWORD "localtime_r" "_localtime_r" "__localtime_r")
    MESSAGE(STATUS "Looking for ${KEYWORD}")
    TRY_COMPILE (C_HAS_${KEYWORD} ${CMAKE_CURRENT_BINARY_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/localtime_r.c
      COMPILE_DEFINITIONS "-DC_LOCALTIME_R=${KEYWORD} -DHAVE_TIME_H=${_HAVE_TIME_H}")
    IF (C_HAS_${KEYWORD})
      MESSAGE(STATUS "Looking for ${KEYWORD} - found")
      SET (C_LOCALTIME_R ${KEYWORD})
      BREAK ()
    ENDIF ()
  ENDFOREACH ()
ENDMACRO ()
IF (NOT C_LOCALTIME_R)
  FINDLOCALTIME_R ()
  SET (C_LOCALTIME_R "${C_LOCALTIME_R}" CACHE STRING "C LOCALTIME_R")
  MARK_AS_ADVANCED (C_LOCALTIME_R)
ENDIF (NOT C_LOCALTIME_R)