/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "Utils.h"

string
getDirectory(string const &path) {
  size_t pos = path.rfind("/");
  if (pos == string::npos) {
    return path;
  } else {
    return path.substr(0, pos);
  }
}

string
joinPaths(string const &path, string const &file) {
  string tmppath(path);
  if ((tmppath.length() > 0) && (tmppath[tmppath.length() - 1] == '/')) {
    tmppath = tmppath.substr(0, tmppath.length() - 1);
  }
  string tmpfile(file);
  while ((tmpfile.length() >= 3) && (tmpfile.substr(0, 3) == "../")) {
    tmppath = getDirectory(tmppath);
    tmpfile = tmpfile.substr(3);
  }
  
  return tmppath + "/" + tmpfile;
}

