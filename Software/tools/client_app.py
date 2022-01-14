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

class Descriptor:
    def __init__(self, uuid, name, path):
        self.uuid = uuid
        self.name = name
        self.path = path

class Characteristic:
    def __init__(self, uuid, name, flags, path):
        self.uuid = uuid
        self.name = name
        self.path = path
        self.flags = flags
        self.descriptors = []

    def addDesc(self, desc):
        self.descriptors.append(desc)

    def getLastDesc(self):
        return self.descriptors[len(self.descriptors)-1]


class Service:
    def __init__(self, uuid, name, path):
        self.uuid = uuid
        self.name = name
        self.path = path
        self.characterstics = []

    def addChar(self, char):
        self.characterstics.append(char)

    def addDesc_toLast(self, desc):
        self.characterstics[len(self.characterstics)-1].addDesc(desc)

class Connection:

    def __init__(self, verbose = False, pattern = '.*'):
        dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
        self.bus = dbus.SystemBus()
        self.pattern = pattern
        self.verbose = verbose
        self.discovery = Discovery(verbose=False, re_pattern=self.pattern,bus=self.bus)
        self.bdaddr = None
        self.mainloop = None

        self.services = []

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
        self.device_path = None
        self.device_proxy = None
        self.device_interface = None

    def get_path_uuid(self, uuid):
        for serv in self.services:
            if serv.uuid == uuid:
                path = serv.path
                return path
            for char in serv.characterstics:
                if char.uuid == uuid:
                    path = char.path
                    return path
                for desc in char.descriptors:
                    if desc.uuid == uuid: 
                        path = desc.path
                        return path
        return None

    def read_from_uuid(self, uuid):
        path = self.get_path_uuid(uuid)
        if path != None:
            char_proxy = self.bus.get_object(bluetooth_constants.BLUEZ_SERVICE_NAME, path)
            char_interface = dbus.Interface(char_proxy, bluetooth_constants.GATT_CHARACTERISTIC_INTERFACE)
            try:
                value = char_interface.ReadValue({})
            except Exception as e:
                print("Failed to read temperature")
                print(e.get_dbus_name())
                print(e.get_dbus_message())
                return bluetooth_constants.RESULT_EXCEPTION
            else:
                print(value)
                return value

    def value_received(self, interface, changed, invalidated, path):
        print("HI FROM ISR")
        if 'Value' in changed:
            value = bluetooth_utils.dbus_to_python(changed['Value'])
            print(value)

    def start_notifications_uuid(self, uuid):
        path = self.get_path_uuid(uuid)
        print(path)
        if path != None:
            char_proxy = self.bus.get_object(bluetooth_constants.BLUEZ_SERVICE_NAME,path)
            char_interface = dbus.Interface(char_proxy, bluetooth_constants.GATT_CHARACTERISTIC_INTERFACE)

            self.bus.add_signal_receiver(self.interfaces_added,
                dbus_interface = bluetooth_constants.DBUS_OM_IFACE,
                signal_name = "InterfacesAdded")
            self.bus.add_signal_receiver(self.properties_changed,
                dbus_interface = bluetooth_constants.DBUS_PROPERTIES,
                signal_name = "PropertiesChanged",
                path_keyword = "path")

    
            self.bus.add_signal_receiver(self.value_received,
                dbus_interface = bluetooth_constants.DBUS_PROPERTIES,
                signal_name = "PropertiesChanged",
                path = path,
                path_keyword = "path")
            
            try:
                print("Starting notifications")
                char_interface.StartNotify()
                print("Done starting notifications")
            except Exception as e:
                print("Failed to start temperatue notifications")
                print(e.get_dbus_name())
                print(e.get_dbus_message())
                return bluetooth_constants.RESULT_EXCEPTION
            else:
                self.mainloop = GLib.MainLoop() 
                self.mainloop.run()
                return bluetooth_constants.RESULT_OK


    def write_text_uuid(self, uuid, text):
        path = self.get_path_uuid(uuid)
        char_proxy = bus.get_object(bluetooth_constants.BLUEZ_SERVICE_NAME,path)
        char_interface = dbus.Interface(char_proxy, bluetooth_constants.GATT_CHARACTERISTIC_INTERFACE)
        try:
            ascii = bluetooth_utils.text_to_ascii_array(text)
            value = char_interface.WriteValue(ascii, {})
        except Exception as e:
            print("Failed to write to LED Text")
            print(e.get_dbus_name())
            print(e.get_dbus_message())
            return bluetooth_constants.RESULT_EXCEPTION
        else:
            return bluetooth_constants.RESULT_OK

    def is_connected(self):
        return self.connected

    def is_connected_other(self):
        if not self.connected:
            self.bdaddr = self.discovery.findDevice() 
            if self.bdaddr != None:
                self.device_path = bluetooth_utils.device_address_to_path(self.bdaddr, self.adapter_path)
                self.device_proxy = self.bus.get_object(bluetooth_constants.BLUEZ_SERVICE_NAME,self.device_path)
                self.device_interface = dbus.Interface(self.device_proxy, bluetooth_constants.DEVICE_INTERFACE)
                props_interface = dbus.Interface(self.device_proxy, bluetooth_constants.DBUS_PROPERTIES)
                connected = props_interface.Get(bluetooth_constants.DEVICE_INTERFACE,"Connected")
                return connected 
        return False
    
    def connect(self):
        try:
            self.bdaddr = self.discovery.findDevice()
            if self.bdaddr != None:
                self.device_path = bluetooth_utils.device_address_to_path(self.bdaddr, self.adapter_path)
                self.device_proxy = self.bus.get_object(bluetooth_constants.BLUEZ_SERVICE_NAME,self.device_path)
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

    def service_discovery_completed(self):
        self.bus.remove_signal_receiver(self.interfaces_added,"InterfacesAdded")
        self.bus.remove_signal_receiver(self.properties_changed,"PropertiesChanged")
        self.mainloop.quit()
        
    def properties_changed(self, interface, changed, invalidated, path):
        if path != self.device_path:
            return
    
        if 'ServicesResolved' in changed:
            sr = bluetooth_utils.dbus_to_python(changed['ServicesResolved'])
            if self.verbose:
                print("ServicesResolved  : ", sr)
            if sr == True:
                self.service_discovery_completed()
            
    def interfaces_added(self, path, interfaces):
        if bluetooth_constants.GATT_SERVICE_INTERFACE in interfaces:
            properties = interfaces[bluetooth_constants.GATT_SERVICE_INTERFACE]
            if self.verbose:
                print("--------------------------------------------------------------------------------")
                print("SVC path   :", path)
            if 'UUID' in properties:
                uuid = properties['UUID']
                if self.verbose:
                    print("SVC UUID   : ", bluetooth_utils.dbus_to_python(uuid))
                    print("SVC name   : ", bluetooth_utils.get_name_from_uuid(uuid))
                self.services.append(Service(bluetooth_utils.dbus_to_python(uuid), bluetooth_utils.get_name_from_uuid(uuid), path))
            return
    
        if bluetooth_constants.GATT_CHARACTERISTIC_INTERFACE in interfaces:
            properties = interfaces[bluetooth_constants.GATT_CHARACTERISTIC_INTERFACE]
            if self.verbose:
                print("  CHR path   :", path)
            if 'UUID' in properties:
                uuid = properties['UUID']
                if self.verbose:
                    print("  CHR UUID   : ", bluetooth_utils.dbus_to_python(uuid))
                    print("  CHR name   : ", bluetooth_utils.get_name_from_uuid(uuid))
                flags  = [] 
                for flag in properties['Flags']:
                    flags.append(bluetooth_utils.dbus_to_python(flag))
                if self.verbose:
                    print("  CHR flags  : ", flags)
                self.services[len(self.services) - 1].addChar(Characteristic(bluetooth_utils.dbus_to_python(uuid), bluetooth_utils.get_name_from_uuid(uuid), flags, path))
            return
        
        if bluetooth_constants.GATT_DESCRIPTOR_INTERFACE in interfaces:
            properties = interfaces[bluetooth_constants.GATT_DESCRIPTOR_INTERFACE]
            if self.verbose:
                print("    DSC path   :", path)
            if 'UUID' in properties:
                uuid = properties['UUID']
                if self.verbose:
                    print("    DSC UUID   : ", bluetooth_utils.dbus_to_python(uuid))
                    print("    DSC name   : ", bluetooth_utils.get_name_from_uuid(uuid))
                self.services[len(self.services) - 1].addDesc_toLast(Descriptor(bluetooth_utils.dbus_to_python(uuid), bluetooth_utils.get_name_from_uuid(uuid), path))
            return

    def discoverServices(self):
        if self.connected:
            self.bus.add_signal_receiver(self.interfaces_added,
                dbus_interface = bluetooth_constants.DBUS_OM_IFACE,
                signal_name = "InterfacesAdded")
            self.bus.add_signal_receiver(self.properties_changed,
                dbus_interface = bluetooth_constants.DBUS_PROPERTIES,
                signal_name = "PropertiesChanged",
                path_keyword = "path")
            self.mainloop = GLib.MainLoop() 
            self.mainloop.run()

if __name__ == "__main__":

    conn = Connection(True, 'ESP32')
    print(bool(conn.is_connected_other()))
    
    if conn.is_connected_other():
        print("Sorry - something is already connected to device " + conn.bdaddr)
        sys.exit(1)
        
    print("Connecting to " + conn.pattern)
    conn.connect()
    conn.discoverServices();
    uuid = 'beb5483e-36e1-4688-b7f5-ea07361b26a8'
    #conn.read_from_uuid(uuid)
    conn.start_notifications_uuid(uuid)

    time.sleep(5)
    print("Disconnecting from " + conn.bdaddr)
    conn.disconnect()

