cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)
if(NOT ParaView_BINARY_DIR)
  find_package(ParaView REQUIRED)
  include(${PARAVIEW_USE_FILE})
else()
  include_directories(${VTK_INCLUDE_DIRS})
endif(NOT ParaView_BINARY_DIR)

find_package(Boost REQUIRED COMPONENTS filesystem)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  set(SRC_LIST vtkSEPReader.h vtkSEPReader.cxx)
  add_paraview_plugin(SEPReader "1.0"
    DESCRIPTION "Reader for SEP data"
    SERVER_MANAGER_XML SEPReader.xml
    SERVER_MANAGER_SOURCES vtkSEPReader.cxx
    SERVER_SOURCES ${SRC_LIST}
    REQUIRED_ON_SERVER
  )

  target_link_libraries(SEPReader LINK_PUBLIC ${Boost_LIBRARIES})
else()
  message("This plugin needs boost and will not be compiled.")
endif()

