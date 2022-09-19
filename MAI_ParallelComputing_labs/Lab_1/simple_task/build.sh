# -----------------------------------------------------------------
#                             Usage
# -----------------------------------------------------------------
print_usage() {
echo "Command line arguments: "
echo "   --help                   --  Script usage"
echo "   -gp | --gpu              --  Building a program for GPU with CUDA support"
echo "   -cp | --cpu              --  Building a program for CPU with OpenMP support"
echo "   -v  | --verify           --  Building a program for verify result."
echo "                                Verification of the results takes place in comparison with a serial CPU program"
echo "   -p  | --performance      --  Building a program for Build a program for"
echo "                                performance testing. Displays the results"
echo "                                of load testing in the form of a table"
echo "The output program will be saved along the path ./build/Lab_1"
exit 0
}


# -----------------------------------------------------------------
#                         Parse options
# -----------------------------------------------------------------
BUILD_DIR=build
C_COMPILER=/usr/bin/gcc-6

IS_GPU_BUILD="OFF"
IS_CPU_BUILD="OFF"
IS_VERIFY="OFF"
IS_PERFORMANCE="OFF"

while test $# -gt 0; do
  case "$1" in
    -gp | --gpu) IS_GPU_BUILD="ON" && shift;;
    -cp | --cpu) IS_CPU_BUILD="ON" && shift;;
    -v | --verify) IS_VERIFY="ON" && shift;;
    -p | --performance) IS_PERFORMANCE="ON" && shift;;
    --help) print_usage;;
    -* | --*) echo "Unknown option $1" && exit 1;;
  esac
done
if [ "${IS_GPU_BUILD}" = "ON" ]; then
  IS_CPU_BUILD="OFF"
fi
if [ "${IS_PERFORMANCE}" = "ON" ]; then
  IS_VERIFY="OFF"
fi

echo "---------- Build configuration ----------"
echo "   GPU build:         ${IS_GPU_BUILD}"
echo "   CPU build:         ${IS_CPU_BUILD}"
echo "   Verify build:      ${IS_VERIFY}"
echo "   Performance build: ${IS_PERFORMANCE}"
echo "---------- ------------------- ----------"



# -----------------------------------------------------------------
#                  Create build directory
# -----------------------------------------------------------------
if [ -d "$BUILD_DIR" ]; then
  echo "Build directory check: $BUILD_DIR - exist."
  printf "Cleaning build cache...   "
  rm -rf $BUILD_DIR
  echo "Done."
fi

printf "Create new build directory...   "
mkdir $BUILD_DIR
echo "Done."



# -----------------------------------------------------------------
#                       Run building
# -----------------------------------------------------------------
CMAKE_ARGS="-DCMAKE_C_COMPILER=${C_COMPILER} \
            -DLAB_GPU=${IS_GPU_BUILD} \
            -DLAB_CPU=${IS_CPU_BUILD} \
            -DLAB_VERIFY=${IS_VERIFY} \
            -DLAB_PERFORMANCE=${IS_PERFORMANCE} ..
"

cd build
cmake ${CMAKE_ARGS}
make
