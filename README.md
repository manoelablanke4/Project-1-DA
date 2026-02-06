# Urban Navigation Path-Planning Tool - Project 1 Design of Algorithms


## **Group Members**
- Cosme José Pinheiro de Sousa - up202305463
- Manoela Blanke Américo - up202201391
- Ricardo Alexandre Ribeiro Fernandes - up202304126

---

A C++ path-planning system for urban navigation, inspired by GPS routing software.  
The project computes optimal and constrained routes on a graph representing an urban road network, supporting multiple real-world routing scenarios such as road restrictions and environmentally-friendly mobility.

---

## ✨ Features

- **Fastest Route Computation**  
  Computes the shortest / fastest path between a source and a destination.

- **Alternative Route Generation**  
  Finds an independent alternative route to the fastest path when applicable.

- **Restricted Routing**  
  Supports routing while avoiding:
  - Specific nodes (e.g., blocked intersections)
  - Specific edges or road segments (e.g., closed streets)

- **Environmentally-Friendly Routing**  
  Supports combined **driving + parking + walking** routes to reduce environmental impact.

The system is built around classic **graph algorithms** and mirrors the logic of real navigation systems such as Google Maps.

---

## 🧱 Project Structure

- `src/` – Main source code
- `include/` – Header files
- `Functions/` – Auxiliary functions and routing logic
- `data/` – Graph and dataset files
- `CMakeLists.txt` – Build configuration

---

## ✅ Requirements

- **CMake** (version 3.15 or higher recommended)
- **C++17 compatible compiler** (`g++`, `clang++`, etc.)
- Linux or macOS (Windows via WSL or a CMake-compatible environment)

---

## 🔧 Build Instructions

From the project root:

```bash
mkdir -p build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

## ▶️ How to Run

The program supports **two execution modes**:

- Interactive menu mode  
- Batch (file-based) mode  

After building the project, the executable will be located inside the `build/` directory.

---

### Interactive Menu Mode

Run the program **without arguments**:

```bash
./build/<executable>
```

This launches a terminal-based menu where the user can:

1. Compute the fastest route between two nodes  
2. Compute a restricted route (avoiding specific nodes or edges)  
3. Compute an environmentally-friendly route (driving + parking + walking)  
4. Exit the program  

**Important notes:**

- The output file is only updated when the program is exited using option **4**.
- From the menu, it is possible to load commands from an `input.txt` file located in the project root.
- When using an input file through the menu, results are written to `output.txt`.

---

### Batch Mode (Using an Input File)

Batch mode executes routing commands directly from a file without user interaction.

#### Input file only (default output)

```bash
./build/<executable> input.txt
```

- Reads routing instructions from `input.txt`
- Writes results to `output.txt` (created or overwritten)

#### Input file with custom output file

```bash
./build/<executable> input.txt custom_output.txt
```

- Reads routing instructions from `input.txt`
- Writes results to `custom_output.txt`

**Notes:**

- Batch mode supports the **fastest route** and **restricted route** scenarios.
- The file `input.txt` must be located in the **project root directory**.






- **Restricted route** (with nodes or segments to avoid)

> ⚠️ **Reminder:** The input file must be located at the **project root directory**.
