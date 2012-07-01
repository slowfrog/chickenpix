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

