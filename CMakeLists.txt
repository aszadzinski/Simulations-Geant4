
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(muon)

option(WITH_GEANT4_UIVIS "Muon detector" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(muon_run muon.cc ${sources} ${headers})
target_link_libraries(muon_run ${Geant4_LIBRARIES})

set(MUON_SCRIPTS
  init_vis.mac
  run.mac
  vis.mac)

foreach(_script ${MUON_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


install(TARGETS muon_run DESTINATION bin)
