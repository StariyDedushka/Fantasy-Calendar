cmake_minimum_required(VERSION 3.1.0)

 project(gurps_calendar)

 set(CMAKE_AUTOMOC ON)
 set(CMAKE_AUTORCC ON)
 set(CMAKE_AUTOUIC ON)

 if(CMAKE_VERSION VERSION_LESS "3.7.0")
     set(CMAKE_INCLUDE_CURRENT_DIR ON)
 endif()

 find_package(Qt5 REQUIRED COMPONENTS Widgets Core Sql)

 file(GLOB_RECURSE SOURCE_FILES "source/*.cpp")
 file(GLOB_RECURSE HEADER_FILES "include/*.h")

 add_executable(gurps_calendar
     ${HEADER_FILES}
     ${SOURCE_FILES}
     # resources.qrc
 )

 target_include_directories(gurps_calendar PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}
			   ${CMAKE_CURRENT_SOURCE_DIR}/include
			   ${CMAKE_CURRENT_SOURCE_DIR}/include/common)

 file(GLOB UI_FILES "ui/*.ui")
 qt5_wrap_ui(UI_HEADERS ${UI_FILES})

 target_sources(gurps_calendar PRIVATE ${UI_HEADERS})

 target_link_libraries(gurps_calendar Qt5::Core Qt5::Widgets Qt5::Sql)
