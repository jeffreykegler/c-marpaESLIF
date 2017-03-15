MACRO (MYPACKAGEEXPORT)

  IF (MYPACKAGE_DEBUG)
    MESSAGE (STATUS "[${PROJECT_NAME}-EXPORT-DEBUG] Creating target ${PROJECT_NAME}Export with export file ${INCLUDE_OUTPUT_PATH}/${PROJECT_NAME}/export.h")
  ENDIF ()
  INCLUDE (GenerateExportHeader)
  GENERATE_EXPORT_HEADER(${PROJECT_NAME}
    BASE_NAME ${PROJECT_NAME}
    EXPORT_MACRO_NAME ${PROJECT_NAME}_EXPORT
    EXPORT_FILE_NAME "${INCLUDE_OUTPUT_PATH}/${PROJECT_NAME}/export.h"
    STATIC_DEFINE ${PROJECT_NAME}_STATIC)
  ADD_CUSTOM_TARGET(${PROJECT_NAME}Export SOURCES "${INCLUDE_OUTPUT_PATH}/${PROJECT_NAME}/export.h")
  INSTALL(FILES ${_file} DESTINATION ${_dir})
  INSTALL (FILES ${INCLUDE_OUTPUT_PATH}/${PROJECT_NAME}/export.h DESTINATION include/${PROJECT_NAME}/)

ENDMACRO()
