# Repository Description

This repository contains basic examples, typical coding challenges, and subsystems illustrating important and powerful solutions that can be developed via the C programming language. Specifically, the repository layout current contains three main sections as

1. Essentials: this folder contains the core concepts related to the C programming. There are user-interactive eamples which illustrates the fundamentals such as pointers, data structures, and basic algorithms.

2. Problems: this folder is intended to contain the typical coding challenge problems that are usually appear in skill evaluation in one form or the other, like leetcode, codebyte, etc.

3. subsystem: the idea behind this folder is to create plug and play C modules that can be imported and used as building blocks of bigger projects. Further, it reflects the systematic approaches in structuring software development kit (SDK)s, e.g., how to design the header files, publicly exposed APIs, documentation, etc.

# Continuous Integration (CI)
The CI workflow enforces checks on the commits being pushed to the main branch. The workflow steps contains a build step where all the targets listed in the repository's makefile will be build.


## Usage Notes

There are two main ways to build the projects in this repository: a) docker build b) direct build with a C compiler. However, it is recommended
to use the docker build environment that is accompanied with this repo for guaranteed reproducing results. To run a specific sample, you need to first create the docker container image as

cd `this repository path`
`docker build -t c-samples .`
`docker run -it --rm c-samples`

This would open up a interactive terminal to select a specific example to run:

`./build/factorial`

In order to stop the container that is being run, type in `exit` in the terminal.

## Formatting Files
There is a `setup.sh` bash script in the root of the repository that currently includes a few lines enabling formatting the entire repository's files with clang-format. Note: before using the bash, make sure that the clang-format is installed on your machine, and do not forget to make the file executable via the following command: `chmod +x setup.sh`. 