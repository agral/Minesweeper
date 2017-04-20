# Minesweeper

A minesweeper game in C++ utilizing SDL2 libraries.  

**In development**  
It will be gradually developed in order to create an AI solver
of a Minesweeper game.

Features to be added:
 * Game logic
 * Graphical interface
 * A reliable logging utility
 * An AI solver

### Building
There are several build targets provided in the Makefile. Aside from building
the project itself, you may also build the unit tests and the documentation.
###### Building the project
 In order to build
the project, simply issue the ``make`` command. Please note that this project
links to SDL2 libraries, and therefore it is required that you install
at least:
  * lSDL2 (core SDL2 library)
  * lSDL2_image (Image module of SDL2 library)
  * lSDL2_ttf (TrueType font module of SDL2 library)

prior to building the project. See the **License and attribution** chapter
below for links to the download page.
###### Building the unit tests
Execute the ``make test`` in order to build the unit tests. The tests use
``catch`` library provided with the source code. You may also issue the
``make ut`` command to build and run the tests.
###### Building the documentation
The documentation to this project has to be generated with the use of a
``doxygen`` tool (see the **License and attribution** page for links to the
download page). After making sure that the doxygen executable is in the PATH
(try ``type doxygen``), issue the ``make doc`` command.
The generated documentation will be put in doc/html/ subdirectory.

### License and attribution
Unless otherwise stated in the individual files,
the entire content of this repository is available under the **MIT license**
found in the [LICENSE file](LICENSE).  
This project makes use of the following third party libraries:
###### SDL2 libraries
[SDL2 libraries](https://www.libsdl.org/download-2.0.php)
are not distributed with this project. You will have to install
them separately in order to build it.  
SDL2 libraries are distributed under the
[zlib license](www.libsdl.org/license.php).
###### Catch library
[Catch library](https://github.com/philsquared/Catch)
used for unit testing is sourced under the
[BSL-1.0 license](https://github.com/philsquared/Catch/blob/master/LICENSE.txt).
###### Doxygen
[Doxygen tool](https://github.com/doxygen/doxygen)
is used for generating the documentation.
The tool itself is distributed under the
[GNU GPL v2 license](https://github.com/doxygen/doxygen/blob/master/LICENSE),
but the generated documentation, as a derivative work, is shared under the
[MIT license](LICENSE).
Please recall that in order to read the documentation, you will have to
generate it first using this tool. Issue the ``make doc`` command,
making sure that the doxygen executable is in the PATH.
