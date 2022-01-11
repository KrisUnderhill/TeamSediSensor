#!/usr/bin/python3
# mockup of functionality for ESP device
# heavily inspired by the "BluetoothForLinuxDevelopers - V1.0" document
#   and the bluez example test scripts

import bluetooth_constants
import bluetooth_exceptions
import dbus
import dbus.exceptions
import dbus.service
import dbus.mainloop.glib
import sys
from gi.repository import GLib
sys.path.insert(0, '.')

bus = None
adapter_path = None
adv_mgr_interface = None

class Advertisement(dbus.service.Object):
    PATH_BASE = '/org/bluez/ldsg/advertisement'

    def __init__(self, bus, index, advertising_type):
        self.path = self.PATH_BASE + str(index)
        self.bus = bus
        self.ad_type = advertising_type
        self.service_uuids = None
        self.manufacturer_data = None
        self.solicit_uuids = None
        self.service_data = None
        self.local_name = "ESP32 Mock"
        self.include_tx_power = True
        self.data = None
        self.discoverable = True
        dbus.service.Object.__init__(self, bus, self.path)

dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
bus = dbus.SystemBus()
# assume adapter supports advertising
adapter_path = bluetooth_constants.BLUEZ_NAMESPACE + bluetooth_constants.ADAPTER_NAME
print(adapter_path)
