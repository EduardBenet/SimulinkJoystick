Once you finished connecting to the raspberry, you need to pair the controller. You can do that from a direct shell on the Pi, or you can open a shell with these commands:
```
>> r = raspberrypi
>> openShell(r)
```
### Update the PI and add necessary libraries.
```
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install libusb-dev
```
### Download and compile the sixpair code. For reference, and in case it stopped being available. The code sixpair.c is available in this repository.
```
mkdir ~/sixpair
cd ~/sixpair
wget http://www.pabr.org/sixlinux/sixpair.c
```
This command will tell the GCC compiler to compile the code.
```
gcc -o sixpair sixpair.c -lusb
```
### With Sixpair now compiled on our Raspberry Pi, we need to plug our PS3 Controller into the Raspberry Pi using the USB mini cable. The four leds will start blinking.
### Once the controller has been plugged in, we can run sixpair by running the command below. Sixpair will re-configure the controller so that it will talk with our Bluetooth device.
```
sudo ~/sixpair/sixpair
```
### Unplug the controller
### To finally pair the controller you can run:
```
sudo bluetoothctl
agent on
default-agent
discoverable on
scan on
```
### Press the PS button
```
connect <MAC-ADDRESS>
trust <MAC-ADDRESS>
quit
sudo reboot
```
You might have to do this a few ties until it finally works
