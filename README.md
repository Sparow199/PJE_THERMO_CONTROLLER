# ThermoController
![Logo](https://cloud.githubusercontent.com/assets/22281426/26443924/978eaa02-413a-11e7-9483-25eaf016deba.png)

# Authors
  - Mohamed ADANSAR => a1h@hotmail.fr
  - Moncef AOUDIA 

ThermoController is an application that is part of our master project of the Web of Thing module at Lille University. The application runs on a Smews server (stands for Smart & Mobile Embedded Web Server).
An embedded web server is a web server intended to be used on an embedded system and allowing to consult and act on it as on any element of the web.
The application is divided into two main parts:

# Structure

```
Go to apps/

thermocontroller
|____index.html
|____css
| |____jqueryui.css
| |____rangeslider.css
| |____logo.png
| |____style.css
|____js
| |____rangeslider.min.js
| |____jquery.knob.min.js
| |____index.js
| |____alertify.js
|____thermostat.c

```
##### 1-Client Part:
 It is a web interface (HTML, CSS, JS) that offers the user a multitude of functions:

![Docum](https://cloud.githubusercontent.com/assets/22281426/26443928/993c2a14-413a-11e7-9a1e-b9fe97390c9d.png)


  - C1: the logo of our application (RGB)
  - C2: the temperature display (return by the remote sensor).
  - C3: date and time display.
  - C4: on / off button for the controller (heating and alarm).
  - C5: control bar for alarm thresholds (min and max temperature).
  - C6: control bars for programmable mode (heating)
  - C7: rotary knob for manual heating control.
  - C8: temperature alert notification system (not available on the screenshoot).
  - C9: button to activate the smart mode.
  (Screenshot will be update soon)
  
##### 2-Server part:
This part is coded in language C and has the following functionalities:
  - F1: captures and sends the temperature to the client.
  - F2: Automatic and manual alarm triggering.
  - F3: temperature display on a 4digit.
  - F4: color display (with led rgb) depending on temperature.
  - F5: heating power level display (via 4leds led).
  - F6: control of heating and alarm via the client (remote).
  - F7: heating level control with the rotary knob (soon to be added).


# Installation

##### prerequisites

  - SMEWS (included in the project repot with all the drivers)
  - A compiler [GCC ARM].
  - Python version 2.5 minimum.
  - SCons version 0.96 minimum.

##### Compilation

1-Download the compilation string **[GNU ARM Embedded Toolchain]**

2-Place the compilation string at a desired location and add to your `.bash_aliases` file:`export GCC_ARM_TOOLCHAIN= LOCATION`with`LOCATION` = the absolute address of your folder containing the compilation string.


3-Then, in the `.bash_aliases` file, add:`export PATH=$PATH:$GCC_ARM_TOOLCHAIN/gcc-arm-none-eabi-*/bin`. **Attention** : You must specify the version of the `gcc-arm-none-eabi-*` compilation string.

4-Start the following commands:
In the room TIIR (Lille) it is necessary to start by executing this:

```sh
$ ifconfig -a
$ sudo ifconfig nomcarteréseau up
$ sudo ifconfig nomcarteréseau 192.168.1.0/24
```
Then:

```sh
$ git clone https://gitlab-etu.fil.univ-lille1.fr/aoudia/Projet_WOT.git
$ cd ./Projet_WOT
$ scons ipaddr=192.168.1.127 target=mbed_ethernet apps=:thermostat
```

You can put in **ipaddr** an ip address of your choice.

To clean up the project build:
```sh
$ scons -c
```

5-Copy the `.bin` file located in the `Project_WOT/bin /mbed_ethernet/` folder on your MBED.


6-Restart your MBEB (the `.bin` file will be loaded).

##### Editing

  - Connect the **TEMPERATURE SENSOR** to the connector **A0**
  - Connect the **4DIGITS** to the connection **D7**.
  - Connect the **LEDRGB** to the connection **D3**.
  - Connect the **BUZZER** to the connection **A3**.
  - Connect the **BUTTON** to the connection **A1**.
  - Connect the **ROTARY BUTTON** to the connection **A2**.


   [GCC ARM]: <https://launchpad.net/gcc-arm-embedded>
   [GNU ARM Embedded Toolchain]: <https://launchpad.net/gcc-arm-embedded>


  
