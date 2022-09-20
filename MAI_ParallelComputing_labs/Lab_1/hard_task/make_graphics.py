import matplotlib.pyplot as plt
import numpy as np
import sys
import os

time_unit = 'microseconds'

cpu_tests_file = ""
gpu_tests_file = ""

if (len(sys.argv) < 3):
    print("Please enter the command line arfuments:")
    print("   make_graphics.py <csv_table_cpu> <csv_table_gpu>")
    exit(1)
else:
    cpu_tests_file = sys.argv[1]
    gpu_tests_file = sys.argv[2]

if not os.path.isfile(cpu_tests_file):
    print(f"Error: Table with CPU tests not exist. Path: {cpu_tests_file}")
    exit(1)

if not os.path.isfile(gpu_tests_file):
    print(f"Error: Table with GPU tests not exist. Path: {gpu_tests_file}")
    exit(1)

def read_table(table_path: str, limiter=';'):
    file = open(table_path)
    num_elements = []
    duration = []
    for line in file:
        splitted = line.strip().split(limiter)
        if len(splitted) > 1:
            num_elements.append(int(splitted[0]))
            duration.append(float(splitted[1]))
    file.close()
    return (np.array(num_elements), np.array(duration))

cpu_results = read_table(cpu_tests_file)
gpu_results = read_table(gpu_tests_file)

fig = plt.figure(figsize=(15, 10))
plt.title("CPU tests results")
plt.plot(cpu_results[0], cpu_results[1])
plt.xlabel("Number of elements")
plt.ylabel("Duration (microseconds)")
plt.grid()
plt.savefig("images/cpu_results.png", dpi=300)
plt.clf()

fig = plt.figure(figsize=(15, 10))
plt.title("GPU tests results")
plt.plot(gpu_results[0], gpu_results[1])
plt.xlabel("Number of elements")
plt.ylabel("Duration (microseconds)")
plt.grid()
plt.savefig("images/gpu_results.png", dpi=300)
plt.clf()

fig = plt.figure(figsize=(15, 10))
plt.title("Difference between CPU and GPU tests results")
plt.plot(gpu_results[0], gpu_results[1], label="GPU time cruve")
plt.plot(cpu_results[0], cpu_results[1], label="CPU time cruve")
plt.xlabel("Number of elements")
plt.ylabel("Duration (microseconds)")
plt.grid()
plt.legend()
plt.savefig("images/diff.png", dpi=300)
plt.clf()