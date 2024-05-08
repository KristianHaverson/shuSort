cmake_minimum_required(VERSION 3.4)

project(shuSort LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find ROOT package
find_package(ROOT REQUIRED COMPONENTS Core Physics HistPainter)

message(STATUS "ROOT version: ${ROOT_VERSION}")
include(${ROOT_USE_FILE})

# Add executable target
add_executable(shuSort shuSort.cc                # main()
                       src/CommandLineParser.cc  # parses input files (settings.dat, calibrator.dat)

                       src/Settings.cc          # holds settings
                       src/InputOutput.cc       # managets I/O streams
                       src/Calibrator.cc        # applies calibration

                       src/SortedEvent.cc       # class that holds sorted data (can be read in to get calibration)
                       src/SortedHistograms.cc  # class that holds sorted histograms  
                       )

# Generate ROOT dictionary
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/SortedEvent.h)
ROOT_GENERATE_DICTIONARY(G__SortedEvent ${HEADERS} MODULE SortedEvent LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/include/SortedEvent_LinkDef.h)

# Add dictionary source to the executable
add_library(SortedEvent_dict SHARED ${CMAKE_CURRENT_BINARY_DIR}/G__SortedEvent.cxx)
target_include_directories(SortedEvent_dict PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(SortedEvent_dict ${ROOT_LIBRARIES})

set_target_properties(SortedEvent_dict PROPERTIES 
    OUTPUT_NAME "SortedEvent"  # Set the output name to libSortedEvent.so
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib  # Set library output directory
    LINK_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/G__SortedEvent.cxx
)



# Link against ROOT libraries and the dictionary library
target_link_libraries(shuSort PUBLIC ${ROOT_LIBRARIES} SortedEvent_dict)

# Set output directory for executable
set_target_properties(shuSort PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin  # Executable output directory
)

# Move additional build artifacts to build/lib directory
add_custom_command(TARGET SortedEvent_dict POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/lib
    COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_CURRENT_BINARY_DIR}/G__SortedEvent.cxx ${CMAKE_BINARY_DIR}/lib/G__SortedEvent.cxx
    COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_BINARY_DIR}/libSortedEvent_rdict.pcm ${CMAKE_BINARY_DIR}/lib/libSortedEvent_rdict.pcm
    COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_BINARY_DIR}/libSortedEvent.rootmap ${CMAKE_BINARY_DIR}/lib/libSortedEvent.rootmap
    COMMAND ${CMAKE_COMMAND} -E rename $<TARGET_FILE:SortedEvent_dict> ${CMAKE_BINARY_DIR}/lib/$<TARGET_FILE_NAME:SortedEvent_dict>
)


# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")
