setservostik has been coded on debian 9 and comes with a CMakeLists.txt
allowing you to generate the correct files for your build system.

The default cmake that ships with debian 9 is 3.7.2
3.7.2 is also the version that is specified in the CMakeLists.txt file

If your distro has a lower version adapt the version number in the CMakeLists.txt file

if you don't have cmake installed you can apt-get install cmake

compilation:

cd to the folder you extracted the archive to
cmake .
make
make install