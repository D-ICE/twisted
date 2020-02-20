
# HEADER_FILES
set(SRC_FILES
        SimplifiedHarrisSpectrum.cpp
        )

add_library(twisted_engine SHARED ${SRC_FILES})

target_include_directories(twisted_engine PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>
        )

