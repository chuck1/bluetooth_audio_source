# Bluetooth Audio Source

To stream audio you need a bluetooth module or IC that support EDR/BR, sometimes called classic. Bluetooth Low Energy (BLE) is not meant for audio streaming.

Bluetooth devices usually have a serial command set that an external MCU can use to control the device.
There is something called HCI. 
I'm not entirely sure but it might be a standardized command set for this type of communication.
The Core Spec defines some HCI commands.

A2DP is a bluetooth profile for audio streaming. 
What does that mean? 
I think a bluetooth profile is a desciption of how two devices should communicate in order to implement an application such as audio streaming.
A2DP builds on AVDTP.
AVDTP uses L2CAP channels to communicate.

Researching L2CAP has been frustrating. 
I have found BT devices that say they include a L2CAP stack but I find no reference of how to command those devices to create L2CAP channels.

# Promising Devices

* RN4678
* BM83
* RN42 (old, replaced by RN4678)
* CYW20715 (inexpensive)

# Research TODO

* read core spec HCI commands regarding L2CAP
* for a device that says it contains an L2CAP stack, can you send standard HCI commands to control the L2CAP functionality? Does that make sense?
* Can standard HCI commands be used to implement L2CAP/AVDTOP/A2DP?


