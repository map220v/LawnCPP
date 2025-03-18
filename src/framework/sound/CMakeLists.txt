include(FetchContent)

target_sources(${PROJECT_NAME} PRIVATE
        "BassMusicInterface.cpp"
        "BassSoundInstance.cpp"
        "BassSoundManager.cpp"
)


if (WIN32)
    set(BASS_SRC https://www.un4seen.com/files/bass24.zip)
    set(BASS_LIB c/x64/bass.lib)
    set(BASS_INCLUDE c)
elseif (UNIX)
    if (APPLE)
        set(BASS_SRC https://www.un4seen.com/files/bass24-osx.zip)
        set(BASS_LIB libbass.dylib)
        set(BASS_INCLUDE "")
    elseif (ANDROID)
        set(BASS_SRC https://www.un4seen.com/files/bass24-android.zip)
        set(BASS_LIB libs/arm64-v8a/libbass.so)
        set(BASS_INCLUDE c)
    else ()
        set(BASS_SRC https://www.un4seen.com/files/bass24-linux.zip)
        if(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
            set(BASS_LIB libs/aarch64/libbass.so)
        else()
            set(BASS_LIB libs/x86_64/libbass.so)
        endif()
        set(BASS_INCLUDE "")
    endif ()
endif ()

FetchContent_Declare(
        bass
        URL ${BASS_SRC}
        DOWNLOAD_EXTRACT_TIMESTAMP ${CMAKE_SOURCE_DIR}/external/bass/.timestamp
)

FetchContent_GetProperties(bass)
if (NOT bass_POPULATED)
    FetchContent_Populate(bass)
    file(COPY ${bass_SOURCE_DIR}/${BASS_LIB} DESTINATION ${CMAKE_BINARY_DIR})
endif ()

get_filename_component(bassfile ${BASS_LIB} NAME)

add_library(bass STATIC IMPORTED GLOBAL)
set_target_properties(bass PROPERTIES
        IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/${bassfile}
)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        bass
)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${bass_SOURCE_DIR}/${BASS_INCLUDE}
)

if (WIN32)
    configure_file("${bass_SOURCE_DIR}/x64/bass.dll" ${CMAKE_BINARY_DIR} COPYONLY)
endif ()