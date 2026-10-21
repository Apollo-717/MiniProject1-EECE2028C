# MiniProject 1

A templated, ordered doubly linked list with a student database menu.

## Build and run

Use a C++20 compiler and CMake 3.20 or newer. In CLion, open this folder,
select its bundled MinGW toolchain, and run `MiniProject1_EECE2028C`.

From a terminal with the compiler and CMake on PATH:

```
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Run `build/MiniProject1_EECE2028C.exe` on Windows (without `.exe` on Linux).
For multi-configuration generators, use the executable in `build/Debug/`.

The assignment entry point can also be built with:

```
g++ -std=c++20 Miniproject1.cpp -o MiniProject1
```

Submit `Miniproject1.cpp` together with `src/` and `include/`; the entry point
includes those files. Do not compile it together with `src/main.cpp`.
The old root-level `MiniProject1.exe` is from the original repo; use a fresh build.

## Use

Options 1-12 match the database assignment. Options 13-16 expose IsEmpty,
Size, SeeNext, and Reset. Locations start at zero. Get Student removes the
student; Search and Display leave students in place. Press Enter for GPA 0.
M Numbers use uppercase M and eight digits, matching the assignment example.

New lists sort ascending by M Number. Reverse toggles the order; subsequent
inserts preserve that direction. Reverse and insertion reset traversal.
SeeAt makes SeeNext return the following item. Display never changes traversal.
Largest and smallest refer to M Number, even after reversing.

The list owns successfully added objects. GetItem transfers ownership to its
caller. Other returned pointers are borrowed; do not delete them or change
an item's M Number while it remains in the list. Failed AddItem calls leave
ownership with the caller. Copies own separate students and nodes and preserve
the source cursor position (including the end position).

## Files and validation

Load `docs/sample_students.txt` from the repo working directory to try the demo.
Each line contains quoted first and last names, M Number, birth year, month,
day, and GPA. Names with spaces are supported. Saving includes birthdays, even
though the display shows age. Filenames are relative to the working directory.

Loading replaces the list only after every record passes validation, and sorts
ascending. Missing, malformed, or duplicate-containing files leave the current
list unchanged. An empty file clears the list. Blank lines are ignored.
The menu rejects empty names, invalid IDs, nonnumeric input, nonfinite/out-of-range
GPAs, invalid calendar dates, future birthdays, and duplicate IDs.

## Tests and report

`list_tests` covers ordering, traversal, deletion, copying, assignment, reversal,
file handling, validation, and lifetime accounting with another template type.
Optional end-to-end menu tests (Python 3):

```
python tests/menu_tests.py build/MiniProject1_EECE2028C.exe
```

The PDF report in `docs/` contains implementation details and captured test output.
The lifetime test checks owned object destruction; it is not a full heap profiler.
