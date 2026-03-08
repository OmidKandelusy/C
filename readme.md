This repository contains basic C programing samples accompanied with a docker build environment.

To run a specific sample, we first the docker container image as

cd `this repository path`
`docker build -t c-samples .`
`docker run -it --rm c-samples`

This would open up a interactive terminal to select a specific example to run:

./build/factorial

In order to stop the container that is being run, type in `exit` in the terminal