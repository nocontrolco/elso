# ELSO project

[![build](https://github.com/nocontrolco/elso/actions/workflows/build.yml/badge.svg)](https://github.com/nocontrolco/elso/actions/workflows/build.yml)

Elso is electronic football game using vehicles.
ELSO stands for **Electric Lightning Soccer Overdrive**.

- The entry point of the project/program should be via Python. C/C++ code is made available through bindings, and is used mainly for raw data processing.
- The file `src/python/main.py` is the main one. Where the program should start and finish.
- I/O handling & argument parsing is also done in Python. Eventually, file handling (e.g. largers ones) should be delegated to C++ code, but always called by python.

## Setting up Environment
First, one should download the repository informations. If you already have it set in your machine, you can skip to environment creating/updating.

```bash
$ git clone git@github.com:nocontrolco/elso.git
```

Here are the instructions for creating the development environment using miniconda:
```bash
$ wget https://repo.anaconda.com/miniconda/Miniconda3-py310_23.1.0-1-Linux-x86_64.sh
$ sh Miniconda3-py310_23.1.0-1-Linux-x86_64.sh
$ conda config --set auto_activate_base true
$ conda env create --file environment.yml
$ conda activate elso
```

If you already have the conda elso environment created in your maching, it is enough to just run `conda env update --file environment.yml --prune`, so the packages will be updated/installed.

## Building & Testing
Here are the instructions for building up the project and run the tests
```bash
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build . --config Release --target all -- -j 10
$ cd ~/Reps/elso/build/tests/cpp
$ ctest -V --output-on-failure
$ pytest ../tests/python -v
```

For debugging/developing (locally), it's recommended that you run cmake build with `--config Debug`.

## Project Contribution
- Every branch should have an issue assigned to it
- Every created branch must be named following the pattern `fb-ELSO-<issue_number>-<developer>-<keywords>`
- For every issue created, (especially for github) please beware of the issue mapping `ELSO-<issue_number>:` before the title
- PRs might have any title, but it is essential that any commit related to the issue have the `ELSO-<issue_number>` in its message, to ensure one can easily map it back to the issue
- Review commits should be tagged with the `--fixup`, e.g. `git commit --fixup HEAD`, to facilitate rebase/squash prior to merging
- Prior to merge any PR, after reviews, one should squash the commits in order to every PR/branch enters as fewers commits as possible to allow the project to have clear changes and straightforward identification to any change
- Common sense requires that every public callable (i.e. potentially used elsewhere in the code) should have a simple and straightforward documentation
- Also, **prior to opening any PR**, please use our code formatting file with clang. For that, use the installed `clang-format -i <file>s`.
- Code style is completely to the programmer, although subject to PR reviews
