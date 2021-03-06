/*
   setservostik - rotates Ultimarc's ServoStick joystick to 4 or 8 way
   Copyright (C) 2018 Gijsbrecht De Waegeneer
   Copyright (C) 2018 Timothy Reaves

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.

   contact: gijsbrecht.dewaegeneer@ telenet.be
 */

#include "Config.h"

#include <iostream>
#include <libusb-1.0/libusb.h>
#include <sstream>

#define UM_REQUEST_TYPE 0x21
#define UM_REQUEST 9
#define UM_TIMEOUT 2000
#define SERVOSTIK_VENDOR 0xD209
#define SERVOSTIK_PRODUCT 0x1700
#define SERVOSTIK_VALUE 0x0200
#define SERVOSTIK_MESG_LENGTH 4
#define SERVOSTIK_INTERFACE 0
#define KERNEL_DRIVER_ATTACHED 1

void cleanup(libusb_context * context, libusb_device_handle * devicehandle) {
   if (devicehandle) {
      libusb_close(devicehandle);
   }
   if (context) {
      libusb_exit(context);
   }
}

[[noreturn]] void
   errorhandler(libusb_context * context, libusb_device_handle * deviceHandle, const std::string & errorMessage) {
   std::cerr << "ERROR: " << errorMessage << "\n";
   cleanup(context, deviceHandle);
   exit(EXIT_FAILURE);
}

[[noreturn]] void errorhandler(libusb_context * context, libusb_device_handle * deviceHandle, int rc) {
   std::cerr << "ERROR: " << libusb_error_name(rc) << " - " << libusb_strerror(static_cast<libusb_error>(rc)) << "\n";
   cleanup(context, deviceHandle);
   exit(EXIT_FAILURE);
}

auto rotatestick(int way) {
   libusb_context *       context(nullptr);
   libusb_device *        device(nullptr);
   libusb_device_handle * deviceHandle(nullptr);
   libusb_device **       devices;
   auto                   rc = libusb_init(&context);

   if (rc != LIBUSB_SUCCESS) {
      errorhandler(context, deviceHandle, rc);
   }
#if LIBUSB_API_VERSION >= 0x01000106
   libusb_set_option(context, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_WARNING);
#else
   libusb_set_debug(context, LIBUSB_LOG_LEVEL_WARNING);
#endif
   auto deviceCount = libusb_get_device_list(context, &devices);

   for (auto deviceIndex(0); deviceIndex < deviceCount; deviceIndex++) {
      device = devices[deviceIndex];
      libusb_device_descriptor descriptor = {};
      rc = libusb_get_device_descriptor(device, &descriptor);
      if (rc != LIBUSB_SUCCESS) {
         std::cout << "WARNING: " << libusb_error_name(rc) << " - " << libusb_strerror(static_cast<libusb_error>(rc))
                   << " - trying to proceed...\n";
      } else {
         if ((descriptor.idVendor == SERVOSTIK_VENDOR) && (descriptor.idProduct == SERVOSTIK_PRODUCT)) {
            break;
         }
      }
      device = nullptr;
   }

   if (device == nullptr) {
      std::stringstream ss;
      ss << std::hex << "0x" << SERVOSTIK_VENDOR << ":0x" << std::hex << SERVOSTIK_PRODUCT << " device not found";
      errorhandler(context, deviceHandle, ss.str());
   } else {   // good to go
      rc = libusb_open(device, &deviceHandle);
      if (rc != LIBUSB_SUCCESS) {
         errorhandler(context, deviceHandle, rc);
      }
      if (deviceHandle) {
         if (libusb_kernel_driver_active(deviceHandle, SERVOSTIK_INTERFACE) == KERNEL_DRIVER_ATTACHED) {
            rc = libusb_detach_kernel_driver(deviceHandle, SERVOSTIK_INTERFACE);
            if (rc != LIBUSB_SUCCESS) {
               errorhandler(context, deviceHandle, rc);
            }
         }

         unsigned char message[SERVOSTIK_MESG_LENGTH] = { 0x00, 0x00, 0x00, 0x00 };   // 4-way
         if (way == 8) {
            message[3] = 0x01;
         }   // 8-way
         rc = libusb_control_transfer(deviceHandle,
                                      UM_REQUEST_TYPE,
                                      UM_REQUEST,
                                      SERVOSTIK_VALUE,
                                      SERVOSTIK_INTERFACE,
                                      message,
                                      SERVOSTIK_MESG_LENGTH,
                                      UM_TIMEOUT);
         std::cout << "servostik " << way << "-way -> " << ((rc == sizeof(message)) ? "SUCCESS" : "FAILURE") << "\n";
      }
   }
   libusb_free_device_list(devices, 1);
   cleanup(context, deviceHandle);
   return EXIT_SUCCESS;
}

int main(int argc, char * argv[]) {
   long int way(8);
   switch (argc) {
      case 2:
         try {
            way = std::stol(argv[1], nullptr, 10);
         } catch (std::exception &) {
            way = 8;
         }
         break;
      default:
         std::cout << " _____     _   _____                 _____ _   _ _   \n"
                      "|   __|___| |_|   __|___ ___ _ _ ___|   __| |_|_| |_  \n"
                      "|__   | -_|  _|__   | -_|  _| | | . |__   |  _| | '_| \n"
                      "|_____|___|_| |_____|___|_|  \\_/|___|_____|_| |_|_,_| \n"
                      "setservostik Copyright (C) 2018  De Waegeneer Gijsbrecht\n"
                      "Ultimarc ServoStik switcher Version "
                   << VERSION << "\n\n[ " << argv[0]
                   << " restrictorway ] change joystick(s) to 4 or 8 way\n\n"
                      "This program comes with ABSOLUTELY NO WARRANTY. This is free software,\nand you are welcome to "
                      "redistribute it under certain conditions.\n"
                      "license: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007\nCopyright (C) 2007 Free Software "
                      "Foundation, Inc. <https://fsf.org/>\n";
         return EXIT_SUCCESS;
   }
   return rotatestick((!((way > 0) && (way < 5))) ? 8 : 4);
}
