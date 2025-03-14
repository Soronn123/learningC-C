cmake_minimum_required(VERSION 3.5)

project(Liequeen VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS AxContainer REQUIRED)
find_package(Qt5 COMPONENTS Charts REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

set(BOOSTROOT "C:/Users/Shiro/Documents/liberarry/boost_1_84_0/boost_mingw_530")
find_package(Boost 1.84.0 REQUIRED)


set_property(TARGET harfbuzz::harfbuzz PROPERTY
                         IMPORTED_IMPLIB "c:/msys64/mingw64/lib/libharfbuzz.dll.a" )

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        parserMath.h
        app.o
        screenmenu.h
        screenmenu.cpp
        screenmenu.ui
        photo.qrc
        qcustomplot.cpp
        qcustomplot.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
qt_add_executable(Liequeen
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        dialog.h dialog.cpp dialog.ui
        information.h information.cpp information.ui
        chartxy.h chartxy.cpp chartxy.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Liequeen APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Liequeen SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Liequeen
            ${PROJECT_SOURCES}
        )
    endif()
endif()

include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(Liequeen PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Liequeen PRIVATE ${Boost_LIBRARIES})
target_link_libraries(Liequeen PRIVATE Qt6::AxContainer)
target_link_libraries(Liequeen PRIVATE Qt6::Charts)
target_link_libraries(Liequeen PRIVATE Qt${QT_VERSION_MAJOR}::Widgets PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Liequeen)
endif()
set_target_properties(Liequeen PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Liequeen
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Liequeen)
endif()
