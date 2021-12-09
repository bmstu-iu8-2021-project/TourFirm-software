cmake_minimum_required(VERSION 3.5)

project(CourseWork LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ignoreMe "${FOO}${BAZ}${BAR}")

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql)

set(TS_FILES CourseWork_ru_RU.ts)

if(ANDROID)
  add_library(CourseWork SHARED
    main.cpp
    moc_mainwindow.cpp
    secondwindow.cpp
    secondwindow.h
    moc_mainwindow.h
    mainwindow.ui
    secondwindow.ui
    comboboxitemdelegate.h
    comboboxitemdelegate.cpp
    booking.h
    booking.cpp
    booking.ui
    tours.h
    tours.cpp
    tours.ui
    regular.h
    regular.cpp
    regular.ui
    checkboxdelegate.cpp
    checkboxdelegate.h
    dateeditdelegate.cpp
    dateeditdelegate.h
    settings.h
    settings.cpp
    settings.ui
    ${MOC_Files}
    ${TS_FILES}
  )
else()
  add_executable(CourseWork
    main.cpp
    mainwindow.cpp
    mainwindow.h
    secondwindow.cpp
    secondwindow.h
    mainwindow.ui
    secondwindow.ui
    comboboxitemdelegate.h
    comboboxitemdelegate.cpp
    booking.h
    booking.cpp
    booking.ui
    tours.h
    tours.cpp
    tours.ui
    regular.h
    regular.cpp
    regular.ui
    checkboxdelegate.cpp
    checkboxdelegate.h
    dateeditdelegate.cpp
    dateeditdelegate.h
    settings.h
    settings.cpp
    settings.ui
    ${TS_FILES}
  )
endif()

target_link_libraries(CourseWork PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt5::Core Qt5::Quick Qt5::Sql)
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
