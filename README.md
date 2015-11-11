# LPC8xx Template

## Intro

This is a starter template forked from K. Townsend's, microbuilder, LPC810_CodeBase.
The original can be found [here](https://github.com/microbuilder/LPC810_CodeBase).

This starter template supports all LPC8xx series MCU's with the original goal of the LPC810_CodeBase, to provide a very small abstraction layer on top of the CMSIS libraries. The libraries provided in the LPCOpen repo are nice, but they tend to be very large and mask away details from the user.

## Feature Set
* All the original work from the LPC810_CodeBase plus:
* Support for multiple UART channels.
* A blocking one shot timer that can be used with precision to the microsecond.
* A basic Maxim 1wire driver.
* A DS18B20 driver.
* Up to date documentation from NXP.

## To Do
- [x] Refactor `src` directory into a modules directories pattern and update Makefile.
- [ ] Add add floating point support to the `printf` function.
- [ ] Allow for different baud rates when using multiple UART channels in one project.
- [ ] Add multiple device support to DS18B20 library.

## Supported Make Commands

- `make clean`
- `make all`

## Pull Requests
Before submitting a pull request please ensure the following:
* The change set follows the styling found in the repo. Think Linux kernel style guide.
* If the change set is fixing bugs or adding support to the original files in LPC810_CodeBase, please submit it there.
