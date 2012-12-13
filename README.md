chickenpix
==========

Collaboration for the [Liberated Pixel Cup](http://lpc.opengameart.org).

POC and WIP on the [github page](http://slowfrog.github.com/chickenpix).

Discussion on the [google group](http://groups.google.com/group/chickenpix).

Downloads that were previously available on GitHub have been migrated to S3.
- [Windows 32bit binary](https://s3-eu-west-1.amazonaws.com/slowfrog/chickenpix/clcp13.zip)
- [Linux 32bit binary Debian](https://s3-eu-west-1.amazonaws.com/slowfrog/chickenpix/chickenpix_linux.tar.bz2)
- [All sources](https://s3-eu-west-1.amazonaws.com/slowfrog/chickenpix/chickenpix_src.tar.bz2)

Building and running
--------------------

### Linux

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


### Windows

The project and solution files for Microsoft Visual Studio 2010 express are
provided, but they may contain hardcoded paths.


### Mac OS X

XCode project files are provided, but they may contain hardcoded paths.


### Dependencies

Chickenpix depends on:
- the dev library for Python 2.7
- the dev library for ClanLib 2.3
- the dev library for SFML 1.6

Chickenpix embeds:
- TmxParser
- tinyxml
