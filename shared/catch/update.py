#!/usr/bin/env python3

# -------------------------
# CONTEXT MANAGER
# -------------------------

from contextlib import contextmanager
import urllib.request
import os
import shutil


@contextmanager
def cwd(path):
    oldpwd=os.getcwd()
    os.chdir(path)
    try:
        yield
    finally:
        os.chdir(oldpwd)

# -------------------------
# Downloading and installing CATCH
# -------------------------

def main() :
	with cwd(os.path.dirname(os.path.realpath(__file__))) :
		# Downloading the CATCH framework
		if (os.path.exists("include/catch/catch.hpp")) :
			print("Found existing file include/catch/catch.hpp. Removing it now.")
			os.remove("include/catch/catch.hpp")
		if (os.path.exists("catch.hpp")) :
			print ("catch.hpp file already exists in the directory. Removing it now.")
			os.remove("catch.hpp")
		print ("Downloading CATCH framework...")
		urllib.request.urlretrieve("https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp", "catch.hpp")
		shutil.move("catch.hpp", "include/catch/catch.hpp")
		print ("Download complete. CATCH is now available in include/catch")


if __name__ == "__main__":
    main()