#!/usr/bin/python3

# client for communicating with ESP32 TeamSediSensor Project
# heavily inspired by the "BluetoothForLinuxDevelopers - V1.0" document
#   and the bluez example test scripts

from gi.repository import GLib
import bluetooth_utils
import bluetooth_constants
import dbus
import dbus.mainloop.glib
import sys
import re
sys.path.insert(0, '.')

# Client connect and disconnect

class Discovery:

    def __init__(self, verbose = True, re_pattern = '.*'):
        self.verbose = verbose
        self.pattern = re.compile(re_pattern, re.IGNORECASE)

        self.adapter_interface = None
        self.mainloop = None
        self.timer_id = None
        self.devices = {}
        self.managed_objects_found = 0

    def list_devices_found(self):
        print("Full list of devices",len(self.devices),"discovered:")
        print("------------------------------")
        for path in self.devices:
            dev = self.devices[path]
            print(bluetooth_utils.dbus_to_python(dev['Address']))
       
    def interfaces_added(self, path, interfaces):
        # interfaces is an array of dictionary entries
        if not bluetooth_constants.DEVICE_INTERFACE in interfaces:
            return
        device_properties = interfaces[bluetooth_constants.DEVICE_INTERFACE]
        if path not in self.devices:
            self.devices[path] = device_properties
            dev = self.devices[path]
            if(self.verbose):
                print("NEW path  :", path)
                if 'Address' in dev:
                    print("NEW bdaddr: ", bluetooth_utils.dbus_to_python(dev['Address']))
                if 'Name' in dev:
                    print("NEW name  : ", bluetooth_utils.dbus_to_python(dev['Name']))
                if 'RSSI' in dev:
                    print("NEW RSSI  : ", bluetooth_utils.dbus_to_python(dev['RSSI']))
            print("------------------------------")
    
    def interfaces_removed(self, path, interfaces):
        # interfaces is an array of dictionary strings in this signal
        if not bluetooth_constants.DEVICE_INTERFACE in interfaces:
            return
        if path in self.devices:
            dev = self.devices[path]
            if 'Address' in dev:
                print("DEL bdaddr: ", bluetooth_utils.dbus_to_python(dev['Address']))
            else:
                print("DEL path  : ", path)
                print("------------------------------")
            del self.devices[path]
    
    
    def properties_changed(self, interface, changed, invalidated, path):
        if interface != bluetooth_constants.DEVICE_INTERFACE:
            return
        if path in self.devices:
            self.devices[path] = dict(self.devices[path].items())
            self.devices[path].update(changed.items())
        else:
            self.devices[path] = changed
    
        dev = self.devices[path]
        print("CHG path  :", path)
        if 'Address' in dev:
            print("CHG bdaddr: ", bluetooth_utils.dbus_to_python(dev['Address']))
        if 'Name' in dev:
            print("CHG name  : ", bluetooth_utils.dbus_to_python(dev['Name']))
        if 'RSSI' in dev:
            print("CHG RSSI  : ", bluetooth_utils.dbus_to_python(dev['RSSI']))
        print("------------------------------")
    
    def get_known_devices(self, bus):
        object_manager = dbus.Interface(bus.get_object(bluetooth_constants.BLUEZ_SERVICE_NAME, "/"), bluetooth_constants.DBUS_OM_IFACE)
        managed_objects=object_manager.GetManagedObjects()
    
        for path, ifaces in managed_objects.items():
            for iface_name in ifaces:
                if iface_name == bluetooth_constants.DEVICE_INTERFACE:
                    self.managed_objects_found += 1
                    print("EXI path  : ", path)
                    device_properties = ifaces[bluetooth_constants.DEVICE_INTERFACE]
                    self.devices[path] = device_properties
                    if 'Address' in device_properties:
                        print("EXI bdaddr: ", bluetooth_utils.dbus_to_python(device_properties['Address']))
                    if 'Name' in device_properties:
                        print("EXI name: ", bluetooth_utils.dbus_to_python(device_properties['Name']))
                    if 'Connected' in device_properties:
                        print("EXI cncted: ", bluetooth_utils.dbus_to_python(device_properties['Connected']))           
                    print("------------------------------")
                
    def discovery_timeout(self):
        GLib.source_remove(self.timer_id)
        self.mainloop.quit()
        self.adapter_interface.StopDiscovery()
        bus = dbus.SystemBus()
        bus.remove_signal_receiver(self.interfaces_added,"InterfacesAdded")
        bus.remove_signal_receiver(self.interfaces_added,"InterfacesRemoved")
        bus.remove_signal_receiver(self.properties_changed,"PropertiesChanged")
        self.list_devices_found()
        return True
    
    def discover_devices(self, bus, timeout):
        adapter_path = bluetooth_constants.BLUEZ_NAMESPACE + bluetooth_constants.ADAPTER_NAME
    
        # acquire the adapter interface so we can call its methods 
        adapter_object = bus.get_object(bluetooth_constants.BLUEZ_SERVICE_NAME, adapter_path)
        self.adapter_interface = dbus.Interface(adapter_object, bluetooth_constants.ADAPTER_INTERFACE)
        
        # register signal handler functions so we can asynchronously report discovered devices
        
        # InterfacesAdded signal is emitted by BlueZ when an advertising packet from a device it doesn't
        # already know about is received
        bus.add_signal_receiver(self.interfaces_added,
                dbus_interface = bluetooth_constants.DBUS_OM_IFACE,
                signal_name = "InterfacesAdded")
    
        # InterfacesRemoved signal is emitted by BlueZ when a device "goes away"
        bus.add_signal_receiver(self.interfaces_removed,
                dbus_interface = bluetooth_constants.DBUS_OM_IFACE,
                signal_name = "InterfacesRemoved")
    
        # PropertiesChanged signal is emitted by BlueZ when something re: a device already encountered
        # changes e.g. the RSSI value
        bus.add_signal_receiver(self.properties_changed,
               dbus_interface = bluetooth_constants.DBUS_PROPERTIES,
                signal_name = "PropertiesChanged",
                path_keyword = "path")
        
        self.mainloop = GLib.MainLoop()
        self.timer_id = GLib.timeout_add(timeout, self.discovery_timeout)
        self.adapter_interface.StartDiscovery(byte_arrays=True)
    
        self.mainloop.run()
        
        device_list = self.devices.values()
        discovered_devices = []
        for device in device_list:
            dev = {}
            discovered_devices.append(dev)
    
        return discovered_devices
    
if __name__ == "__main__":
    if (len(sys.argv) != 2):
        print("usage: python3 client_discover_devices.py [scantime (secs)]")
        sys.exit(1)
        
    scantime = int(sys.argv[1]) * 1000
    
    # dbus initialisation steps
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    bus = dbus.SystemBus()

    Disc = Discovery();
    
    # ask for a list of devices already known to the BlueZ daemon
    print("Listing devices already known to BlueZ:")
    Disc.get_known_devices(bus)
    print("Found ",Disc.managed_objects_found," managed device objects")
    print("Scanning")
    Disc.discover_devices(bus, scantime)

