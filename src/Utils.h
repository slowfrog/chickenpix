#pragma once

#include <string>
using namespace std;

/** Extracts the directory part of a path, witout the trailing slash. */
string getDirectory(string const &path);
/** Builds a full path from a path and a file name, removing ../ if necessary. */
string joinPaths(string const &path, string const &file);
