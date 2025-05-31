# BrainHack

BrainHack is a C++ tool for [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck), offering an **interpreter**, **debugger**, and **compiler**.

---

## Features

* **Interpret** Brainfuck code.
* **Debug** programs interactively.
* **Compile** to binaries or assembly.

---

## Installation

You'll need cmake.

1. **Clone:** `git clone https://github.com/NikodemMarek/brainhack.git && cd brainhack`
2. **Generate config** `mkdir build && cd build && cmake ..`
3. **Build:** `make`
4. **Run:** `./brainhack ../hello_world.bf`

---

## Usage

```bash
Usage: brainhack [options] <file.bf>
Options:
  -o, --output <file>   Specify output file
  -c, --compile         Compile to binary
  -a, --assembly        Generate assembly
  -d, --debug           Debug mode
  -h, --help            Show this help message
```

---

## Examples

* **Run:** `brainhack hello.bf`
* **Compile:** `brainhack my_prog.bf -c -o my_exec`
* **Assembly:** `brainhack my_prog.bf -a -o my_prog.asm`
* **Debug:** `brainhack broken.bf -d`

---

## Debugger

```bash
Output: Hell

  +---------+---------+---------+---------+---------+
0 | 108 (l) | 0 (NUL) | 0 (NUL) | 0 (NUL) | 0 (NUL) | 5
  +---------+---------+---------+---------+---------+
       ^
Next operation: INCREMENT VALUE BY 3 (108 + 111 = 111)

[number]Enter - execute next operation(s) | q - quit
```
