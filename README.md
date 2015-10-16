owfscpp
==========
Simple cpp library 1-wire interface

Introduction
============
A simple class to communicate with owserver, the backend component of the OWFS 1-wire bus control system.
See http://owfs.org/ for more information on OWFS 1-wire bus control system.

Features
========
All messages of owserver protocol are supported
Support of persitentes connections
All owserver flags are modifiable
Compile on Linux and Windows, Intel or ARM.

Quality developpment
====================
 - Static audit with CppCheck
 - Security audit with VisualCodeGrepper
 - Dynamic audit with Address Sanitizer.
 - Unit tests replay for each version.

Portability
===========
Unit tests passed successfully on :
 - Windows Seven (CPU Intel Celeron)
 - Linux Ubuntu (CPU Intel Atom)
 - Linux Raspian on Raspberry Pi (CPU ARM)
 - Linux FunPlug on NAS DNS-320 (CPU ARM)

For more informations
=====================
Documentation http://catjage.free.fr/dev/owfscpp/index.html

Licence
=======
owfscpp is free software : you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

owfscpp is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with owfscpp. If not, see http://www.gnu.org/licenses/.
