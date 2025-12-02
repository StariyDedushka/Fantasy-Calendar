cmake_minimum_required(VERSION 3.1.0)

 project(gurps_calendar)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
 set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Sql Xml)

file(GLOB_RECURSE SOURCE_FILES "source/*.cpp")
file(GLOB_RECURSE HEADER_FILES "include/*.h")
file(GLOB_RECURSE UI_FILES "ui/*.ui")

file(GLOB_RECURSE ALL_INCLUDE_DIRS LIST_DIRECTORIES true "include/*")

add_executable(gurps_calendar
               ${HEADER_FILES}
	       ${SOURCE_FILES}
	       # resources.qrc
	       )
target_include_directories(gurps_calendar PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}
		            )

foreach(dir ${ALL_INCLUDE_DIRS})
    if(IS_DIRECTORY ${dir})
	message(STATUS "Adding include directory: ${dir}")
	target_include_directories(gurps_calendar PRIVATE ${dir})
    endif()
endforeach()


qt5_wrap_ui(UI_HEADERS ${UI_FILES})

target_sources(gurps_calendar PRIVATE ${UI_HEADERS})

target_link_libraries(gurps_calendar Qt5::Core Qt5::Widgets Qt5::Sql Qt5::Xml)

source_group("Header Files" FILES ${HEADER_FILES})
source_group("Source Files" FILES ${SOURCE_FILES})
source_group("UI Files" FILES ${UI_FILES})

# Отдельная группа для common headers
file(GLOB COMMON_HEADERS "include/common/*.h")
if(COMMON_HEADERS)
 source_group("Header Files\\common" FILES ${COMMON_HEADERS})
 message(STATUS "Common headers found: ${COMMON_HEADERS}")
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_GLOBAL_SOURCE_DIRS
 "${ALL_INCLUDE_DIRS}"
 "${CMAKE_CURRENT_SOURCE_DIR}/source"
 "${CMAKE_CURRENT_SOURCE_DIR}/ui"
)
