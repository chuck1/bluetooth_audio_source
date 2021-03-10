
# Guitar

In this project I am setting out to build a digital electric guitar. 
I know there are products in existance that are called digital electric guitars but I dont know if my definition is the same.
My device will work as follows

    pickup                         OPTIONAL               
    (just like      --> OP AMP --> dedicated ADC chip --> microcontroller --> bluetooth module ))) -> bluetooth speaker
    tradtional
    electric guitar)                                        ^
                                                            |
                                         -------------------+
                                         |                  |
                                         v                  v
                                      OPTIONAL             OPTIONAL
                                      memory chip for      FPGA for fast DSP
                                      playback and other

The pickup will be constructed just like a traditional electric guitar pickup.
I dont know if I will need or want a humbucker pickup or multiple pickups.
I dont yet know the purpose of having multiple pickups.

The OP AMP will increase the voltage of the signal from the pick, which should be in the 10s to 100s of millivolts.
It will be increased to the range of the ADC which will be a few volts.

I might want to get a dedicated ADC chip. 
This would allow me to sample the pickup at higher frequency and with higher precision than just the microcontroller can provide.
I would first need to determine if this would improve the sound quality.
It would also be helpful for certain effects.
For example, if I wanted to stretch the input signal, reducing its pitch, I would just sample at higher frequency than the output.
Also, filtering functions and other effects could benefit from having additional samples between output frames.

The microcontroller is, of course, the control center of the system.
It will either do the ADC sampling or commuicate twith the ADC chip to get the signal from the pickup.
It will perform DSP operations.
It will communicate with the BT module to configure it and it will send I2S data to the BT module.

See discussion of BT module below.

## Plan

### Proof of Concept: Pickup

I am going to build a crude pickup using some magnets I have on hand and wire I salvaged from a small electric motor.
I dont know if I will get enough signal to be detectable or have sufficient SNR even for testing.

I will try connecting this directly to the Arduino Uno to see if anything is detected.
I will also build an amplifier.
I have never built an amplifier before, so this will probably take alot of time experimenting.

The Arduino Uno will send data to the computer.
I will write a C++ program that will read the serial data and play the sound.

I will use Lincoln's toy guitar.

### Proof of Concept: Bluetooth Audio

For this I will need the Arduino Due, the BT module, and a BT speaker.
I need the Arduino Due because it is capable of I2S communication.
There are other Arduino boards that do I2S but the Due would be a good platform for doing other
projects in the future.

The goal of this step is to demonstrate that I can configure the BT module, get it to connect to the BT speaker
and stream audio from the Arduino to the BT speaker.
I will just send a sine wave for testing.

### Prototype 0

Next would be the first prototype. It would consist of a wooden rig to which I could attach guitar strings and mount the pickup.
I would then test out the entire electrical system.

### Prototype 1

Next I would build an actual guitar body.

## Bluetooth Audio Source

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

### Promising Devices

* RN4678
* BM83
* RN42 (old, replaced by RN4678)
* CYW20715 (inexpensive)

### Research TODO

* read core spec HCI commands regarding L2CAP
* for a device that says it contains an L2CAP stack, can you send standard HCI commands to control the L2CAP functionality? Does that make sense?
* Can standard HCI commands be used to implement L2CAP/AVDTOP/A2DP?

## Parts

### Pickup Wire

Typically 42 or 43 AWG copper with poly coating. Sold in spools of about 25000 feet. 
That is enough for 4-5 regular pickups or 2-3 humbucker pickups.

### Pickup magnets

typically Alnico 5, 5 mm (0.195 inch) diameter by 16 to 18 mm (.6 to .7 inch) long

## Sourcing

## Blog

### 2021-03-09

Tried out my python analog plotter, works well.

Output of the 741 seems to be limited to a narrow rage around 4V.

### 2021-03-10

Asked about my op amp issues on electronics stack exchange.
Got answers.
The 741 is an old design and is designed to be used with a much larger source voltage, something like +/- 12 or 18 V.
They suggested getting a modern rail-to-rail op amp (possibly CMOS) with approapriate source voltage.












