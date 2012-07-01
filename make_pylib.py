import zipfile
import os.path

libpath = "K:/soft/Python27/lib"

if __name__ == "__main__":
    out = zipfile.PyZipFile("python27.zip", "w")
    #out.writepy("toto.py")
    for pack in ["os", 
	             "ntpath", "stat", "genericpath", "warnings", "linecache", "types", "UserDict", 
				 "_abcoll", "abc", "_weakrefset", "copy_reg" ]:
        out.writepy(os.path.join(libpath, pack + ".py"))
    out.close()


    
