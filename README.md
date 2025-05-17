# Virtual Computer in C – Instruction-Based Simulator

## Description

This project simulates a very simple virtual computer built entirely in C.  
The user interacts through the terminal by typing simple textual commands (e.g. `LOAD R1 3`, `ADD R1`, `MEM`).  
The system supports basic memory and register operations, mimicking low-level behavior.

> This project is being actively rewritten and improved. The current version is the **base implementation (Version 1)**, and work has begun on **Version 2**, which introduces pointers, dynamic memory, structs, and handler-based execution.

---

## Version 1 – Simple Static Logic
 
 User input is handled via `fgets()` and parsed using manual string matching (`strcmp`, `strlen`)  
 Command processing is handled via `if-else` blocks  
 Registers `R1`, `R2`
 Memory is simulated with a static 2D integer array  
 Supported commands:
- `BOOT`: Initialize memory and registers with random values
- `MEM`: Print memory contents (array-like)
- `LOAD R1 n` / `LOAD R2 n`: Load memory value into register
- `STORE R1 n` / `STORE R2 n`: Store register value into memory
- `ADD R1` / `SUB R1`: Arithmetic between registers
- `SHOW R1` / `SHOW R2`: Display current register values

 **Educational Focus**:  
The goal of this version was to reinforce core C fundamentals such as:
- Arrays
- Manual string processing
- Procedural logic flow
- Simple memory simulation

---

##  Upcoming – Version 2 Overview

 In Version 2, the architecture is being rebuilt around modern C principles:

| Feature | Description |
|--------|-------------|
|  `struct Instruction` | Dynamic representation of user commands |
|  Function pointers | Each command maps to a specific function dynamically |
|  `malloc` & `free` | All instructions are allocated dynamically and properly destroyed |
|  Validation layer | Defensive programming to reject invalid user input |
|  Handler-based execution | Removes the need for huge `if-else` chains |
|  (Planned) Parallel extensions | Future expansion using parallel programmin for concurrent instruction execution |

This allows the project to simulate a **mini interpreter**, while teaching modular programming and memory-safe design in C.

---

