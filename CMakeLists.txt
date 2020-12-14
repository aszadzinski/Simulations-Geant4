
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(pet)

option(WITH_GEANT4_UIVIS "Pet detector" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(pet_run pet.cc ${sources} ${headers})
target_link_libraries(pet_run ${Geant4_LIBRARIES})

set(PET_SCRIPTS
  init_vis.mac
  run.mac
  start.py
  vis.mac)

foreach(_script ${PET_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


install(TARGETS pet_run DESTINATION bin)
