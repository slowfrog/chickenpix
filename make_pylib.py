import zipfile
import os.path

libpath = "K:/soft/Python27/lib"

if __name__ == "__main__":
    out = zipfile.PyZipFile("python27.zip", "w")
    #out.writepy("toto.py")
    for pack in [
        "UserDict",
        "__future__",
        "_abcoll",
        "_weakrefset",
        "abc",
        "copy_reg",
        "genericpath",
        "hashlib",
        "linecache",
        "ntpath",
        "os",
        "random",
        "stat",
        "types",
        "warnings"
        ]:
        out.writepy(os.path.join(libpath, pack + ".py"))
    out.close()


    
