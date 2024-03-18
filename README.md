# Robot Arm Controller
3D printed robot arm, controlled with a Raspberry Pi Pico.

The docker container that the code is compiled in was created by [lukestep](https://hub.docker.com/r/lukstep/raspberry-pi-pico-sdk), for more instructions view his repo.

Run the following command in the repos root directory
```
docker run -d -it --name pico-sdk --mount type=bind,source=${PWD},target=/home/dev lukstep/raspberry-pi-pico-sdk:latest
```

## Framework 
Framework is a separate program to experiment the general program structure of a microcontroller.

## Requirement
For src you need to install (nlohmann/json)[https://github.com/nlohmann/json/tree/develop?tab=readme-ov-file#integration], which you can do with [vcpkg](https://github.com/Microsoft/vcpkg/?tab=readme-ov-file#quick-start-unix).

## Resources
[Step 1: A Basic Starting Point](https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html)
