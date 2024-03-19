# Robot Arm Controller
3D printed robot arm, controlled with a Raspberry Pi Pico.

The docker container that the code is compiled in was created by [lukestep](https://hub.docker.com/r/lukstep/raspberry-pi-pico-sdk), for more instructions view his repo.

Run the following command in the repos root directory
```
docker run -d -it --name pico-sdk --mount type=bind,source=${PWD},target=/home/dev lukstep/raspberry-pi-pico-sdk:latest
```

## Framework 
Framework is a separate program to experiment the general program structure of a microcontroller.

![Alt text](documentation/images/spi_diagram2.png "Multiple SPI")

## Requirement
For src you need to install (nlohmann/json)[https://github.com/nlohmann/json/tree/develop?tab=readme-ov-file#integration], which you can do with [vcpkg](https://github.com/Microsoft/vcpkg/?tab=readme-ov-file#quick-start-unix).

## Resources
- [Step 1: A Basic Starting Point](https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

### PICO SDK
- [Raspberry Pi Pico C/C++ SDK](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)
- [Getting started with Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)
- [Making Two Raspberry Pi Pico Boards Communicate through SPI using C/C++ SDK](https://www.circuitstate.com/tutorials/making-two-raspberry-pi-pico-boards-communicate-through-spi-using-c-cpp-sdk/)

### Linux driver for SPI peripheral
- [SPI – Serial Peripheral Interface Protocol Basics](https://embetronicx.com/tutorials/tech_devices/spi-serial-peripheral-interface-protocol-basics/)
- [Linux Device Driver Tutorial – Part 1 | Introduction](https://embetronicx.com/tutorials/linux/device-drivers/linux-device-driver-part-1-introduction/)
- [Serial Peripheral Interface (SPI)](https://www.kernel.org/doc/html/v4.13/driver-api/spi.html)
- [Device Tree for Dummies](https://elinux.org/images/f/f9/Petazzoni-device-tree-dummies_0.pdf)