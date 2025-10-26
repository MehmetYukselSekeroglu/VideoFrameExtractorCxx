cmake_minimum_required(VERSION 3.16)

project(VideoFrameExtractor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenCV'yi bulma - DLL'lerin olduğu dizine göre ayarla
set(OpenCV_DIR "D:/opencv/opencv/build")
find_package(OpenCV REQUIRED)

# OpenCV bileşenlerini kontrol et
if(OpenCV_FOUND)
    message(STATUS "OpenCV version: ${OpenCV_VERSION}")
    message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
    message(STATUS "OpenCV include dir: ${OpenCV_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "OpenCV bulunamadı! Lütfen OpenCV_DIR yolunu kontrol edin.")
endif()

# Qt'yi bulma
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    VideoProcessor.h
    VideoProcessor.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VideoFrameExtractor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(VideoFrameExtractor SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(VideoFrameExtractor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# OpenCV ve Qt kütüphanelerini bağlama
target_link_libraries(VideoFrameExtractor PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${OpenCV_LIBS}
)

# OpenCV include dizinlerini ekle
target_include_directories(VideoFrameExtractor PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

# Derleme tanımlamalarını ekle (gerekiyorsa)
if(MSVC)
    target_compile_definitions(VideoFrameExtractor PRIVATE
        _USE_MATH_DEFINES
        NOMINMAX
    )
endif()

# Hedef özellikleri
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.VideoFrameExtractor)
endif()

set_target_properties(VideoFrameExtractor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Windows için runtime kütüphanelerini kopyalama - GÜNCELLENMİŞ YOL
if(WIN32)
    # OpenCV DLL'lerini kopyala
    add_custom_command(TARGET VideoFrameExtractor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "D:/opencv/opencv/build/x64/vc16/bin/opencv_world4120.dll"
            $<TARGET_FILE_DIR:VideoFrameExtractor>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "D:/opencv/opencv/build/x64/vc16/bin/opencv_videoio_ffmpeg4120_64.dll"
            $<TARGET_FILE_DIR:VideoFrameExtractor>
        COMMENT "OpenCV DLL'leri kopyalanıyor..."
    )

    # Debug modunda debug DLL'lerini kopyala
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_custom_command(TARGET VideoFrameExtractor POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "D:/opencv/opencv/build/x64/vc16/bin/opencv_world4120d.dll"
                $<TARGET_FILE_DIR:VideoFrameExtractor>
            COMMENT "OpenCV Debug DLL'leri kopyalanıyor..."
        )
    endif()
endif()

include(GNUInstallDirs)
install(TARGETS VideoFrameExtractor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VideoFrameExtractor)
endif()
