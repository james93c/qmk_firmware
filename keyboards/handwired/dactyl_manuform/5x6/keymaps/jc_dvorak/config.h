/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define MASTER_LEFT
//#define MASTER_RIGHT

#define EE_HANDS

/* Pro Micro clones often have unreliable USB VBUS detection, so the non-USB
   half can't tell it should be the slave and wrongly acts as master (silent
   slave). Force robust USB-based master/slave detection. */
#define SPLIT_USB_DETECT

/* Shorter detection window so the slave half wakes up sooner on plug-in.
   Safe only because of the watchdog below: on a host reboot the USB half
   can time out before the host enumerates it and wrongly become a slave;
   the watchdog reboots any slave that hears nothing from a master so
   detection is retried until the host is actually up. */
#define SPLIT_USB_TIMEOUT 1000
#define SPLIT_WATCHDOG_ENABLE
