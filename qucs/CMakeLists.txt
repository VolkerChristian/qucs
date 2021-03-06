PROJECT(qucs-suite CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
cmake_policy(VERSION 2.8)

# set this to 4 or 5
OPTION (USE_QT5 "Using of Qt5 version for compiling" ON)
OPTION (DISABLE_QDEBUG "Disabling of qDebug() messages" OFF)

IF(${USE_QT5})
    SET(USE_QT_VERSION 5)
ELSE(${USE_QT5})
    SET(USE_QT_VERSION 4)
ENDIF(${USE_QT5})


# SET(USE_QT5 ${USE_QT5} PARENT_SCOPE)
# SET(DISABLE_QDEBUG ${DISABLE_QDEBUG} PARENT_SCOPE)

SET(USE_QT5 ${USE_QT5} CACHE BOOL "Set compiling with Qt5" FORCE)
SET(DISABLE_QDEBUG ${DISABLE_QDEBUG} CACHE BOOL "Disable debug infos" FORCE)


file (STRINGS "${qucs-suite_SOURCE_DIR}/VERSION" QUCS_VERSION)
message(STATUS "Configuring Qucs: VERSION ${QUCS_VERSION}")

SET(GIT unknown)
IF(EXISTS ${CMAKE_SOURCE_DIR}/../.git )
  FIND_PACKAGE(Git)
  # Get the latest abbreviated commit hash of the working branch
  execute_process(
    COMMAND ${GIT_EXECUTABLE} log --pretty=format:%h -n 1u
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
  )
  SET(GIT ${GIT_COMMIT_HASH})
  message(STATUS "Found Git repository, last commit hash: ${GIT}")
ENDIF()

message(STATUS "${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}
    ${qucs-suite_BINARY_DIR}" )


IF (UNIX AND NOT APPLE)
  IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
    message(STATUS "Compile for processor : ${CMAKE_SYSTEM_PROCESSOR}")
    SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
  ENDIF()
ENDIF()


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
elseif(COMPILER_SUPPORTS_CXX0X)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


IF(${USE_QT_VERSION} MATCHES "4")
    FIND_PACKAGE( Qt4 4.8.1 REQUIRED )
    SET( QT_USE_QT TRUE )
    #SET( QT_USE_QTXML TRUE )
    #SET( QT_USE_QTSVG TRUE )
    SET( QT_USE_QTCORE TRUE )
    SET( QT_USE_QTGUI TRUE )
    SET( QT_USE_QTSCRIPT TRUE )
    SET( QT_DEBUG TRUE)
    INCLUDE( ${QT_USE_FILE} )
    ADD_DEFINITIONS(${QT_DEFINITIONS} -DQT_DEPRECATED_WARNINGS)
ELSE()
    FIND_PACKAGE(Qt5 COMPONENTS Core Gui Widgets LinguistTools Script REQUIRED QUIET)
    INCLUDE_DIRECTORIES(${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

    ADD_DEFINITIONS(${QT_DEFINITIONS})
ENDIF()

IF(DISABLE_QDEBUG)
    message(STATUS "disable qDebug(): ${DISABLE_QDEBUG}")
    ADD_DEFINITIONS(-DQT_NO_DEBUG_OUTPUT -DQT_NO_DEBUG -DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
ENDIF()


ADD_SUBDIRECTORY( man )
ADD_SUBDIRECTORY( qucs )
ADD_SUBDIRECTORY( qucs-activefilter )
ADD_SUBDIRECTORY( qucs-attenuator )
#ADD_SUBDIRECTORY( qucs-doc )
ADD_SUBDIRECTORY( qucs-filter )
ADD_SUBDIRECTORY( qucs-lib )
ADD_SUBDIRECTORY( qucs-transcalc )
ADD_SUBDIRECTORY( qucs-rescodes )
#ADD_SUBDIRECTORY( examples )
ADD_SUBDIRECTORY( translations )
ADD_SUBDIRECTORY( contrib )
ADD_SUBDIRECTORY(qucs-powercombining)


#
# Custom uninstall target
#
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake)


