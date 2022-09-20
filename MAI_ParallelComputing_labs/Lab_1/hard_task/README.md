Interface:

----------------------------------------------------------
Environment:
CUDA Version: 11.7
GCC Version: 6.5.0
Device: NVIDIA GeForce 1650 Ti MAX-Q
Driver Version: 515.65.01
CXX standard: 11

----------------------------------------------------------
For more info:
./build.sh --help

----------------------------------------------------------
For CUDA inference verify results:
./build.sh --gpu --verify

For CPU inference verify results:
./build.sh --cpu --verify

For CUDA inference preformance test:
./build.sh --gpu --performance

For CPU inference perforamce test:
./build.sh --cpu --performance

-----------------------------------------------------------
For make graphics:
python3 make_graphics.py <cpu_table> <gpu_table>

Outputs: images/*