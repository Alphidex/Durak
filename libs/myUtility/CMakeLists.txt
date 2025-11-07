add_library(Utility)

target_sources(Utility
    PRIVATE
        myUtility.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES myUtility.h
    )