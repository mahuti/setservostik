15/09/2018

setservostik has been developed on a debian 9 system and compiled with gcc 6.3
It comes with a CMakeLists.txt allowing you to generate the correct files for your build system.

The default cmake that ships with debian 9 at the time of writing is 3.7.2 .
3.7.2 is also the version that is specified in the CMakeLists.txt file.

If your distro has a lower version adapt the version number in the CMakeLists.txt file.

If you don't have cmake installed you can install it using 'apt-get install cmake' as super user.

compilation:

cd 'folder you extracted the archive to'
cmake .
make
make install (as super user)