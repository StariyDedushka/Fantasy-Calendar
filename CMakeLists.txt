cmake_minimum_required(VERSION 3.1.0)

 project(gurps_calendar)

 set(CMAKE_AUTOMOC ON)
 set(CMAKE_AUTORCC ON)
 set(CMAKE_AUTOUIC ON)

 if(CMAKE_VERSION VERSION_LESS "3.7.0")
     set(CMAKE_INCLUDE_CURRENT_DIR ON)
 endif()

 find_package(Qt5 COMPONENTS Widgets REQUIRED)
 find_package(Qt5 COMPONENTS SQLite3 REQUIRED)

 add_executable(gurps_calendar
     mainwindow.ui
     settings.ui
     mainwindow.cpp
     settingswindow.cpp

     abstractitem.cpp
     abstractscene.cpp
     calendarevent.cpp
     calendaritem.cpp
     calendarscene.cpp
     calendarsystem.cpp
     calendarview.cpp
     customdatetime.cpp
     eventcontainer.cpp
     eventscene.cpp
     eventview.cpp
     settings.cpp
     main.cpp
     # resources.qrc
 )

 target_link_libraries(gurps_calendar Qt5::Widgets)
