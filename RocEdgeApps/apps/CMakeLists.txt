
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(roc_edge_apps VERSION 1.1.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# CMake Options
option(BUILD_APPS_RRCF_INTRO "build application: rrcf into" ON)
option(BUILD_APPS_RRCF_NYC_TAXI "build application: rrcf NYC taxi" ON)
option(BUILD_APPS_USER_RULE_FX_SCALING_LAW "build application: user rule fx scaling law" ON)


set (LIB_DIR "libroc_edge")
set (BIN_DIR "bin")
if(MSVC)
    set (LIB_DIR "libroc_edge/msvc")
    set (BIN_DIR "bin/msvc")
endif(MSVC)

set (BIN_DIR "bin")
if(MSVC)
    set (BIN_DIR "bin/msvc")
endif(MSVC)

  
# ---- apps  ------------
set (LIBROC_EDGE libroc_edge)

add_library(${LIBROC_EDGE} STATIC IMPORTED)

if(MSVC)
  set_property(TARGET ${LIBROC_EDGE} PROPERTY IMPORTED_LOCATION_RELEASE libroc_edge/msvc/Release/libroc_edge.lib)
  set_property(TARGET ${LIBROC_EDGE} PROPERTY IMPORTED_LOCATION_DEBUG   libroc_edge/msvc/Debug/libroc_edge.lib)
endif(MSVC)

if(NOT MSVC)
  set_property(TARGET ${LIBROC_EDGE} APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
  set_target_properties(${LIBROC_EDGE} PROPERTIES
      IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
      IMPORTED_LOCATION_RELEASE libroc_edge/libroc_edge.a
  )
  set(CMAKE_CXX_FLAGS "-O2 -Wall -pthread")
endif()

# Increase Stack on Windows
if(MSVC)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:10000000")
endif()

# ----------
if(BUILD_APPS_RRCF_INTRO)

    set(EXECUTABLE_NAME rrcf_intro)

    add_executable(${EXECUTABLE_NAME})

    target_sources(${EXECUTABLE_NAME} PRIVATE 
              ../RocEdgeApps/apps/rrcf_intro/main.cpp
              ../RocEdgeApps/apps/rrcf_intro/user_rule.hpp
              ../RocEdgeApps/apps/rrcf_intro/user_rule.cpp
              ../RocEdgeApps/apps/rrcf_intro/user_rule_data.cpp
              ../RocEdgeApps/apps/rrcf_intro/user_rule_optimize.cpp
              )

    target_include_directories(${EXECUTABLE_NAME}  PUBLIC ../../RocEdgeIF/include)
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBROC_EDGE})

    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED YES
      ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR}
      LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR}
      RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    )

endif()


# ----------
if(BUILD_APPS_RRCF_NYC_TAXI)

    set(EXECUTABLE_NAME rrcf_nyc_taxi)

    add_executable(${EXECUTABLE_NAME})

    target_sources(${EXECUTABLE_NAME} PRIVATE 
              ../RocEdgeApps/apps/rrcf_nyc_taxi/main.cpp
              ../RocEdgeApps/apps/rrcf_nyc_taxi/user_rule.hpp
              ../RocEdgeApps/apps/rrcf_nyc_taxi/user_rule.cpp
              ../RocEdgeApps/apps/rrcf_nyc_taxi/user_rule_data.cpp
              ../RocEdgeApps/apps/rrcf_nyc_taxi/user_rule_optimize.cpp
              )

    target_include_directories(${EXECUTABLE_NAME}  PUBLIC ../../RocEdgeIF/include)
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBROC_EDGE})

    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED YES
      ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR}
      LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR}
      RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    )

endif()

# ----------

if(BUILD_APPS_USER_RULE_FX_SCALING_LAW)

    set(EXECUTABLE_NAME scaling_law_fx)

    add_executable(${EXECUTABLE_NAME})

    target_sources(${EXECUTABLE_NAME} PRIVATE 
              ../RocEdgeApps/apps/user_rule_fx_scaling_law/main.cpp
              ../RocEdgeApps/apps/user_rule_fx_scaling_law/user_rule_sl.hpp
              ../RocEdgeApps/apps/user_rule_fx_scaling_law/user_rule_sl.cpp
              ../RocEdgeApps/apps/user_rule_fx_scaling_law/user_rule_sl_data.cpp
              ../RocEdgeApps/apps/user_rule_fx_scaling_law/user_rule_sl_optimize.cpp
              )

    target_include_directories(${EXECUTABLE_NAME}  PUBLIC ../../RocEdgeIF/include)
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBROC_EDGE})

    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED YES
      ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR}
      LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR}
      RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    )

endif()

# ----------

