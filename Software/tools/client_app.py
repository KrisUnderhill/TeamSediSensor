#!/usr/bin/python3

# client for communicating with ESP32 TeamSediSensor Project
# heavily inspired by the "BluetoothForLinuxDevelopers - V1.0" document
#   and the bluez example test scripts

from gi.repository import GLib
import dbus
import time
import sys
import re

import bluetooth_utils
import bluetooth_constants
from discovery import Discovery

sys.path.insert(0, '.')

class Connection:

    def __init__(self, verbose = False, pattern = '.*'):
        dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
        self.bus = dbus.SystemBus()
        self.pattern = pattern
        self.verbose = verbose
        self.discovery = Discovery(verbose=False, re_pattern=self.pattern,bus=self.bus)
        self.bdaddr = None


        self.connected = False
        object_manager = dbus.Interface(self.bus.get_object(bluetooth_constants.BLUEZ_SERVICE_NAME, "/"), bluetooth_constants.DBUS_OM_IFACE)
        managed_objects=object_manager.GetManagedObjects()
        for path, ifaces in managed_objects.items():
            for iface_name in ifaces:
                if iface_name == bluetooth_constants.DEVICE_INTERFACE:
                    device_properties = ifaces[bluetooth_constants.DEVICE_INTERFACE]
                    if( ('Name' in device_properties and re.search(self.pattern, bluetooth_utils.dbus_to_python(device_properties['Name']))) or 
                        ('Address' in device_properties and re.search(self.pattern, bluetooth_utils.dbus_to_python(device_properties['Address']))) ):
                        if 'Connected' in device_properties:
                            self.connected = True

        self.adapter_path = bluetooth_constants.BLUEZ_NAMESPACE + bluetooth_constants.ADAPTER_NAME
        self.device_proxy = None
        self.device_interface = None

    def is_connected(self):
        return self.connected

    def is_connected_other(self):
        if not self.connected:
            self.bdaddr = self.discovery.findDevice() 
            if self.bdaddr != None:
                device_path = bluetooth_utils.device_address_to_path(self.bdaddr, self.adapter_path)
                self.device_proxy = self.bus.get_object(bluetooth_constants.BLUEZ_SERVICE_NAME,device_path)
                self.device_interface = dbus.Interface(self.device_proxy, bluetooth_constants.DEVICE_INTERFACE)
                self.device_interface.Connect()
                props_interface = dbus.Interface(self.device_proxy, bluetooth_constants.DBUS_PROPERTIES)
                connected = props_interface.Get(bluetooth_constants.DEVICE_INTERFACE,"Connected")
                return connected 
        return False
    
    def connect(self):
        try:
            self.bdaddr = self.discovery.findDevice()
            if self.bdaddr != None:
                device_path = bluetooth_utils.device_address_to_path(self.bdaddr, self.adapter_path)
                self.device_proxy = self.bus.get_object(bluetooth_constants.BLUEZ_SERVICE_NAME,device_path)
                self.device_interface = dbus.Interface(self.device_proxy, bluetooth_constants.DEVICE_INTERFACE)
                self.device_interface.Connect()
            else:
                return bluetooth_constants.RESULT_ERR_NOT_FOUND
        except Exception as e:
            print("Failed to connect")
            print(e.get_dbus_name())
            print(e.get_dbus_message())
            if ("UnknownObject" in e.get_dbus_name()):
                print("Try scanning first to resolve this problem")
            return bluetooth_constants.RESULT_EXCEPTION
        else:
            if self.verbose:
                print("Connected OK")
            self.connected = True
            return bluetooth_constants.RESULT_OK
    
    def disconnect(self):
        if self.connected:
            try:
                self.device_interface.Disconnect()
            except Exception as e:
                print("Failed to disconnect")
                print(e.get_dbus_name())
                print(e.get_dbus_message())
                return bluetooth_constants.RESULT_EXCEPTION
            else:
                if self.verbose:
                    print("Disconnected OK")
                self.connected = False
                return bluetooth_constants.RESULT_OK
        else:
            return bluetooth_constants.RESULT_ERR_NOT_FOUND

if __name__ == "__main__":
    conn = Connection(True, 'ESP32')
    print(bool(conn.is_connected_other()))
    
    if conn.is_connected_other():
        print("Sorry - something is already connected to device " + conn.bdaddr)
        sys.exit(1)
        
    print("Connecting to " + conn.pattern)
    conn.connect()
    time.sleep(5)
    print("Disconnecting from " + conn.bdaddr)
    conn.disconnect()

