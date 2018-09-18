setservostik is a command line utility to set the status of the [Ultimarc Servostick](http://www.ultimarc.com/servostik.html)

# dependencies
- libusb-1.0
- cmake 3.5.0 (3.8.0 recommended)

# compilation:

cd 'folder you extracted the archive to'
mkdir -p builds/unix
cd builds/unix
cmake ../..
make
make install (as super user)