CMAKE_MINIMUM_REQUIRED( VERSION 3.10 )
SET( PROJECT_NAME "Lab_1" )
SET( GPU_LIB_NAME "Lab1_CUDA" )
SET( CPU_LIB_NAME "Lab1_OpenMP" )

PROJECT( ${PROJECT_NAME} )

# ------------------------------------------------------------------------
#                    Project options.
# ------------------------------------------------------------------------
option( LAB_CPU         "OpenMP Version of programm" OFF )
option( LAB_GPU         "CUDA Version of programm"   OFF )
option( LAB_VIRIFY      "Building a program for verify result." OFF )
option( LAB_PERFORMANCE "Building a program for Build a program for performance testing. Displays the results" OFF )

# ------------------------------------------------------------------------
#                    Building statuses.
# ------------------------------------------------------------------------
MESSAGE( STATUS "Using c compiler at path: ${CMAKE_C_COMPILER}")
MESSAGE( STATUS "Using cxx compiler at path: ${CMAKE_CXX_COMPILER}")
MESSAGE( STATUS "CPU Version mode: ${LAB_CPU}")
MESSAGE( STATUS "GPU Version mode: ${LAB_GPU}")


SET( DEVICE_DEPENDENT_LIBS "" )
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR} )

# ------------------------------------------------------------------------
#                    Check possible options error.
# ------------------------------------------------------------------------
# If setted all mods
if( LAB_CPU AND LAB_GPU )
    message( FATAL_ERROR "Don't use all variance." )
endif()

# If any mode not setted
if (NOT LAB_CPU AND NOT LAB_GPU)
    message( WARNING "CPU mode setted as default. For set mode use:" )
    message( WARNING "\t-DLAB_CPU option" )
    message( WARNING "\t-DLAB_GPU option" )
    SET(LAB_CPU ON)
endif()

# ------------------------------------------------------------------------

ADD_EXECUTABLE(${PROJECT_NAME} 
    "main.cpp"
    "verify/verify.cpp"
)

# ------------------------------------------------------------------------
#                   Build for CPU. OpenMP parallel mode.
# ------------------------------------------------------------------------
if(LAB_CPU)
    message( STATUS "----- Build CPU version with openmp support. -----" )

    # Create compile definitions
    TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PUBLIC CPU_MODE_ENABLE)

    # Set CMake flags for OpenMP
    SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -std=c++11")

    # Set sources
    SET( CPU_LIB_SOURCES "cpu_impl/cpu_implementation.cpp" )

    # Create library
    ADD_LIBRARY( ${CPU_LIB_NAME} STATIC ${CPU_LIB_SOURCES} )

    SET( DEVICE_DEPENDENT_LIBS ${CPU_LIB_NAME} )
endif()

# ------------------------------------------------------------------------
#                   Build for GPU. CUDA parallel mode.
# ------------------------------------------------------------------------
if (LAB_GPU)
    message( STATUS "----- Build GPU version with CUDA support. -----" )
    
    # Create compile definition
    TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PUBLIC GPU_MODE_ENABLE)

    # Find CUDA library
    INCLUDE( FindCUDA )
    FIND_PACKAGE( CUDA REQUIRED )
    INCLUDE_DIRECTORIES( ${CUDA_INCLUDE_DIRS} )
    
    # Show CUDA found status
    MESSAGE( STATUS "CUDA version: ${CUDA_VERSION_STRING}" )
    MESSAGE( STATUS "CUDA include dirs: ${CUDA_INCLUDE_DIRS}" )
    MESSAGE( STATUS "CUDA rt library: ${CUDA_CUDART_LIBRARY}" )
    MESSAGE( STATUS "CUDA nvcc: ${CUDA_NVCC_EXECUTABLE}" )

    # Set flags
    SET( CUDA_NVCC_FLAGS "-arch=sm_30" )
    SET( CUDA_PROPAGATE_HOST_FLAGS OFF )    
    
    # Add sources
    SET( CUDA_SOURCES "cuda_impl/cuda_implementation.cu" )
    
    # Add library
    CUDA_ADD_LIBRARY( ${GPU_LIB_NAME} ${CUDA_SOURCES} STATIC )
    SET( DEVICE_DEPENDENT_LIBS ${GPU_LIB_NAME} ${CUDA_CUDART_LIBRARY} )
endif()

# Create target definitions for running mode
if ( LAB_VERIFY )
    TARGET_COMPILE_DEFINITIONS( ${PROJECT_NAME} PUBLIC VERIFY_ENABLE )
elseif( LAB_PERFORMANCE )
    TARGET_COMPILE_DEFINITIONS( ${PROJECT_NAME} PUBLIC PERFORMANCE_ENABLE )
endif()

# Link device dependent libraries with main project
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${DEVICE_DEPENDENT_LIBS} )