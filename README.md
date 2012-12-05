chickenpix
==========

Collaboration for the [Liberated Pixel Cup](http://lpc.opengameart.org).

POC and WIP on the [github page](http://slowfrog.github.com/chickenpix).

Discussion on the [google group](http://groups.google.com/group/chickenpix).


Building and running
--------------------

* Linux

Building on Linux, provided you have all the required dependencies (see below),
should be as simple as:
$ make

It will build two versions of the game, one using the ClanLib library, the
other using SFML. If you only want one version of the game, you can run
either,

for the SFML version:
$ make smain

for the ClanLib version:
$ make clmain

Run the SFML version from the chickenpix directory with:
$ ./smain

Run the ClanLib version from the chickenpix directory with:
$ ./clmain


* Windows

The project and solution files for Microsoft Visual Studio 2010 express are
provided, but they may contain hardcoded paths.


* Mac OS X

XCode project files are provided, but they may contain hardcoded paths.


* Dependencies

Chickenpix depends on:
- the dev library for Python 2.7
- the dev library for ClanLib 2.3
- the dev library for SFML 1.6

Chickenpix embeds:
- TmxParser
- tinyxml
