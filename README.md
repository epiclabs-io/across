# ACross - cross-compile toolkit and runtime
by Javier Peletier - jm@friendev.com

ACross allows you to build your Arduino projects using Visual Studio.
Your Arduino code is cross-compiled and runs in your PC, which enables
step-by-step debugging. A host Arduino is connected via serial port to 
provide hardware access to your computer, i.e., when you call digitalWrite()
in your code, if running on a computer, it will contact the host Arduino to issue
the digitalWrite().

When an Arduino project that uses ACross is compiled for Arduino,
ACross gets out of the way.

This project is still under early development, current features include:

pinMode, digitalWrite, digitalRead, analogRead, analogWrite, millis, String
HardwareSerial emulation (via computer's virtual COM) and SPI.

Note-- this code is still undocumented. Published here only so that EtherFlow
 (https://github.com/friendev/etherflow) works.

See http://friendev.com/etherflow/ for more information
 
Copyright (c) 2015 All Rights Reserved, http://friendev.com

This source is subject to the GPLv2 license.
Please see the License.txt file for more information.
All other rights reserved.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.