# Urban Navigation Path-Planning Tool - Project 1 DA

## **Group Members**
- Cosme José Pinheiro de Sousa - up202305463
- Manoela Blanke Américo - up202201391
- Ricardo Alexandre Ribeiro Fernandes - up202304126

---

## Project Overview

This project aims to develop a path-planning tool to assist with urban navigation, similar to GPS-based systems like Google Maps, with an emphasis on environmentally sustainable and resilient mobility alternatives. The tool is designed to provide various functionalities that enhance urban mobility, such as:

- **Fastest Route**: Identifying the fastest route to the destination.
- **Second-Fastest Independent Route**: Providing an alternative route that is independent from the fastest route.
- **Restricted Route Planning**: Supporting the planning of routes that exclude specific nodes or segments.
- **Environmentally-Friendly Routes**: Generating routes that combine driving and walking, including parking options, to reduce environmental impact.

The tool also accommodates constraints such as the unavailability of certain routes, ensuring practical and versatile solutions for diverse mobility needs. The ultimate goal of the project is to deliver a navigation system that prioritizes both efficiency and sustainability in urban mobility.

---

## 🛍️ How to Use the Program

### 🔘 Menu Mode (Interactive)

If you **run the program without arguments**, it will launch an interactive **menu** in the terminal:

```bash
./your_program
```

You’ll be able to:
1. Plan the fastest route
2. Plan a restricted route (avoid nodes or segments)
3. Plan an environmentally-friendly route (with parking and walking)
4. Exit the program

> ⚠️ **Important:** The output file is only updated when you **exit the program (option 4)**. Make sure to finish your session to write the results.

> ℹ️ **Note:** After selecting the route type (option 1, 2, or 3), you can choose **option 2** to use an input file. The file must be named `input.txt` and placed at the **root directory** of the project. It will automatically generate or update `output.txt`.

---

### ⚙️ Batch Mode (Automated Input)

You can run the program in **batch mode** by giving one or two arguments:

#### 1. Only input file:
```bash
./your_program input.txt
```
- The program immediately reads the instructions from `input.txt`.
- The results are written to a file named `output.txt` (created or overwritten if it exists).

#### 2. Input file + output file:
```bash
./your_program input.txt custom_output.txt
```
- The program reads from `input.txt` and writes the results to `custom_output.txt`.

> ℹ️ **Batch mode only supports**:
- **Fastest route** (Independent Route Planning)
- **Restricted route** (with nodes or segments to avoid)

> ⚠️ **Reminder:** The input file must be located at the **project root directory**.