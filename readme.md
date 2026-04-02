# Repository Description

This repository contains basic examples, typical coding challenges, and subsystem illustrating
important and powerful solutions that can be developed wiht C programing language. Currently, this is a work in progress work and stay in this status until the first reales tag would be issued to the main branch.

The breif description about the main directories of the reposiory, what is the goal behid them:
1. Essentials: this folder contains the core concepts related to the C programing wherein there are user interactive eamples which the user can really see how things work. This folder clearly shows how pointers, data strucuters, and basic algorithms can be implemented in C.

2. Problems: this folder is intended to contain the typical coding challeng problems that are usually appear in skill evaluation in one form or the other, like leedcode, codebyte, etc.

3. subsystem: the ideae behind this folder to show that how the C language program can be used to implement c modules that can be imported and used as building blocks of bigger projects. Another importatn reason is reflecting the systematic approaches like how to design the header files and publicly exposed APIs, in code documentation, etxc.

# Usage Notes

This repo is accompanied with a docker build environment. To run a specific sample, you need to first create the docker container image as

cd `this repository path`
`docker build -t c-samples .`
`docker run -it --rm c-samples`

This would open up a interactive terminal to select a specific example to run:

`./build/factorial`

In order to stop the container that is being run, type in `exit` in the terminal