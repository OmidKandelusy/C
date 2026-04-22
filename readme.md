# Repository Description

This repository contains basic examples, typical coding challenges, and subsystems illustrating important and powerful solutions that can be developed via the C programing language. Specifically, the repository layout current contains three main sections as

1. Essentials: this folder contains the core concepts related to the C programing. There are user-interactive eamples which illustrates the fundamentals such as pointers, data strucuters, and basic algorithms.

2. Problems: this folder is intended to contain the typical coding challeng problems that are usually appear in skill evaluation in one form or the other, like leedcode, codebyte, etc.

3. subsystem: the ideae behind this folder is to create plug and play C modules that can be imported and used as building blocks of bigger projects. Further, it reflects the systematic approaches in structuing sofware development kit (SDK)s, e.g., how to design the header files, publicly exposed APIs, documentation, etc.

# Usage Notes

This repo is accompanied with a docker build environment. To run a specific sample, you need to first create the docker container image as

cd `this repository path`
`docker build -t c-samples .`
`docker run -it --rm c-samples`

This would open up a interactive terminal to select a specific example to run:

`./build/factorial`

In order to stop the container that is being run, type in `exit` in the terminal.

## Formatting Files
There is a `setup.sh` bash script in the root of the repository that currently inlcudes a few lines enabling formatting the entire repository's files with clang-format. Note: before using the bash, make sure taht the clang-format is installed on your machine, and do not forget to make the file executable via the following command: `chmod +x setup.sh`. 