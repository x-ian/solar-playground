### Use cases / problems

Reasons:

1. Saving money
1. Increase power availability with unreliable grid
1. Off-the-grid

Scenarios

1. Solar Power only needed during the day
1. Solar Power mostly needed at evening/night
1. Solar Power needed day and night

Main devices

1. Light
1. CCTV
1. Computers
1. Printers
1. Kitchen equipment
1. ACs

### Charger Controllers

Types:

* MPPT (Maximum Power Point Tracking)
* PWM (Pulse Width Modulation)

MPPT are more efficient, as they can use a surplus of voltage to generate a higher current and therefore charge batteries faster. PWM always brings down the voltage to the currently needed charging level and burn the additional current as heat, e.g. a discharged battery might only have 10.5 V. So 10.5 V * Imp (of the panel) will not use the full potential power of the panel. e.g. for a Vmp = 18 V panel around 40 % loss. The higher the gap between the optimum current of panel and the required batt charge V the higher the loss (e.g. typical between 20 and 40 %).

Sometimes/often contains a LVD (Low Voltage Disconnect) with ideally an adjustable disconnect voltage and also with an adjustable reconnect voltage.

Different charging modes for different batteries types.

Usually charge controllers provide a charge current that is typically 1/10 of the capacity (in Ah) of the battery. Unsure why MPPT then is better as here the current will change depending on the incoming voltage.

"PWM: The PWM charge controller is a good low cost solution for small systems only, when solar cell temperature is moderate to high (between 45°C and 75°C).

MPPT: To fully exploit the potential of the MPPT controller, the array voltage should be substantially higher than the battery voltage. The MPPT controller is the solution of choice for higher power systems (because of the lowest overall system cost due to smaller cable cross sectional areas). The MPPT controller will also harvest substantially more power when the solar cell temperature is low (below 45°C), or very high (above 75°C) (???), or when irradiance is very low."

Dimension:

* Usually with max current, sometimes separated between load, charge, solar?

Options:

* Optionally temperature sensors can be connected (close/to the batteries?).
* Sometimes with LCD display, sometimes with RS232 (434) (VE.bus?), sometimes with Wifi/Ethernet and potentially cloud data logging. Like the VictronEnergy
* Some have an additional circuit/relais to power up another energy source, e.g. a generator.
* Sometimes comes with an AUX Driver / relay driver to switch on and off dump/diversion loads.

Operation/charge modes:

* Charging
* Dump / diversion load

Questions:

* How harmful is a charger which can't be configured for different bat types, e.g. lead acid vs. gel vs. AGM?
* Are batteries still used (and therefore aging), even when enough power (grid or solar) is available and batteries are fully charged?
* For optimal charge current (1/10 of batteries Ah), does the charger need to know the whole capacity of the battery bank?
* When charging (and also discharging) batteries in series, is it always depleting the first cell/bat before using the others?
* Can chargers be put in parallel to scale up charging of a bigger battery bank?
* Can different charger types be put in parallel to provide 'fail-over', e.g. as a default use the solar charger, but if there isn't enough solar generation, top the batteries up with a grid charger?
* What's the impact of the optional temp sensors?
* Does it need to be strong enough to cater for both charging batteries and current consumer load?
* Can PWM chargers fully charge batteries or only MPPT?
* Are all batteries in a battery bank (in series) treated the same? Hence differences in the charge state and quality of a single battery affect the whole bank?

### Inverter

Types:

* square wave
* modified square wave
* pure sine wave

LVD: Low Voltage Disconnect
LVDR: LVD Reconnect

Some Inverters also include a charge controller.

General recommendation seems to wire Inverters straight to the batteries (bypassing charge controller). 

Questions
* When not connected to charge controller, then the inverter needs its own LVD/LVDR threshold.

* Watts
* Surge load
* efficiency?

#### Solar Inverters  (hybrid/multimode)

Take input power from multiple sources, typically either from solar or grid power.

#### Micro Inverter

* Directly connected to panel and produces AC
* higher panel efficiency
* easier & cheaper wiring
* mixing different panel types
* monitoring and isolation faulty panels
* 'grow as you go'
* in the USA 40% of all residential inverters installed in 2013 were Micro Inverters

#### DC Optimizers
	
Directly connected to each panel, optimizes each panel, prevents bringing down a whole string because one panel is shaded

### Water heater

Using surplus solar power to heat up a water tank (e.g. with an electrical geyser).

Questions:

* What is a typical power consumption for a geyser in Malawi?
* Measuring water temperature required?

Companies

* Helios [[https://helioswaterheater.com/o6/]]

### Sensors

Current

* AC and/or DC, max Amp (peak vs ongoing), max Voltage
* Either down via hall based sensors or shunt resistor
* Shunt resistor theory http://www.vwlowen.co.uk/arduino/current/current.htm
* Hall-effect DC sensing could also come as a non-invasive clamp
* AttoPilot Voltage and Current Sense Breakout - 90A [[https://www.sparkfun.com/products/9028]] 180A [[https://www.sparkfun.com/products/10644]]
* ACS 712 (5A) example [[http://shelvin.de/den-acs-712-5a-strom-sensor-am-arduino-auslesen/]]
* ACS 715 [[https://www.hacktronics.com/Tutorials/arduino-current-sensor.html]]
* ACS 709 (75A) [[https://www.pololu.com/product/2199]] [[http://forum.arduino.cc/index.php?topic=382784.0]]

Voltage

Temperature

OpenEnergyMonitor [[openenergymonitor.org]] has a PV app. But it seems to only measure 2 AC lines, one for incoming PV after the inverter, another one for consumers / load.

WattMeter-like projects

* http://www.instructables.com/id/DIY-Amp-Hour-Meter-Arduino/
* http://meettechniek.info/diy-instruments/arduino-wattmeter.html

#### ACS 709

* -/+ 75 A
* optimized accuracy for currents from -37.5 A to 37.5 A
* tolerate 50 A for 20 seconds or 37.5 A for 150 seconds before exceeding its maximum temperature rating of 150°C
* Supply voltage 3 - 5.5 V
* 9 €

#### ACS 712

* AC & DC, +/- 5, 20, 30 A
* Supply Voltage 5 V

#### ACS 715

* 0 - 30 A, max 30 V
* 5 V supply voltage
* 9 €

#### CSLA2CD Honeywell  Stromsensor Halleffect  72A

* AC & DC, +/- 72 A
* Supply voltage 6 - 12 VDC
* Not for Arduino as Offset voltage is Supply voltage / 2, max Input voltage therefore equals Supply Voltage?
* ~30 €, http://www.ebay.de/itm/231933371993

#### Current Transducers

* [[LEM  LA 100-P/SP13  Current Transducer, LA Series, 10A, -160A to 160A, 0.7 %, Closed Loop Output, 12 Vdc to 15 Vdc][http://uk.farnell.com/lem/la-100-p-sp13/current-transducer-100a-pcb/dp/1617427]]

#### ACS 758

* +/-50 AMP, Panel Mount Version.
* Betriebsspannung: 5 V DC geregelt, oder 8 ~ 35 V DC.


### Connectivity

Raspi USB GSM

* [[http://tutorials-raspberrypi.de/raspberry-pi-gsm-modul-mobiles-internet/]]
* [[https://www.emnify.com/2015/06/18/how-to-fit-a-raspberry-pi-with-mobile-connectivity/]]
* Dedicated Raspi LTE [[https://www.heise.de/newsticker/meldung/Raspberry-Pi-Bezahlbares-LTE-Funkmodul-im-Anmarsch-3530126.html]]

Raspi Zero

* Works with Huawei 3372 USB Stick [[https://www.raspberrypi.org/forums/viewtopic.php?t=159344&p=1034969]], e.g. from [[http://www.ebay.de/itm/Huawei-E3372-4G-LTE-150Mbit-s-USB-Surfstick-LTE-V-HiLink-Megafon-ohne-Simlock-/162278073671?hash=item25c886e547:g:5KoAAOSwx2dYJv7j]]

### Misc devices

Programmable load: To simulate a load, it is possible to put multiple old-school light bulbs into series, e.g. 10 x 75 watts?

Enclosures?

### General stuff about serial connection

* Default is that serial communication is tide to a serial console to remotely monitor and log into a Raspi via serial communication
* Raspi 3 serial / UART/ GPIO ports appear to be messed up. Mostly cause now an embedded bluetooth also is present (and overlaps/conflicts with old serial port)
* http://spellfoundry.com/2016/05/29/configuring-gpio-serial-port-raspbian-jessie-including-pi-3/
* http://elinux.org/RPi_Serial_Connection

### Raspi Mobile connectivity

Tested with onboard USB of Raspi 3b, unclear if Raspi zero also works.

General tools:

* lsusb
* usb-devices

Often (always?) package usb-nodeswitch is needed.

Maybe other (generic) and less config-intense way is to use an ordinary USB mobile Wifi (MiFi) dongle.

#### Huawei E3372 4G LTE

* ~ 45 €
* Needs package usb-modeswitch, afterwards ID 12d1:14dc is used for modem
* Offers Ethernet adapter, doesn't need additional configs
* http://alexanderhoughton.co.uk/blog/guide-sending-an-sms-with-raspberry-pilinux-huawei-e303-mobile-dongle/

#### XS Stick P14

* xs stick p14 uses USB ID 1c9e:9605 (unclear if before or after usb-modeswitch)
* Needs additional packages ppp, network-manager, network-manager-gnome
* Command-line option nmcli for Non-UI usage [[https://www.desgehtfei.net/?p=30]]
* Graphical UI to configure network connections might require root privileges
* Use nm-applet and nm-connection-editor to start UI
* stores configs under /etc/NetworkManager/
* NetworkManager ignores all interfaces configured in /etc/network/interfaces

#### Iteadstudio Raspberry Pi GMS Addon V2.0

* https://www.itead.cc/wiki/RPI_SIM800_GSM/GPRS_ADD-ON_V2.0
* https://www.itead.cc/blog/raspberry-pi-3-add-on-supplementary-document

Itead talks about their Segnix library to talk to the Addon. Itead also provides another (dedicated?) library just for the GSM add-on. Didn’t get both to work (but this was also before knowing all the serial port issues with Raspi 3). So maybe it would work once the port is properly configured. 
* https://github.com/itead/Segnix
* ftp://imall.iteadstudio.com/Modules/IM131224002/Library_Raspberry_sim900.zip

Under https://github.com/lamondlab/IteadSIM800 a python 3 lib making use of the serial connection is available. The SMS test worked out of the box with proper serial port configs, so this might be the easiest go-to solution.

For quick and dirty test the command line tool minicom should also work for invoking AT commands.

#### SIM800C Quad-band Wireless GPRS GSM Modul 

Appears to be similar to Iteads GSM Addon shield. At least https://github.com/lamondlab/IteadSIM800 is also able to talk to it once all serial port things are cleared

#### Raspberry Pi Zero

* USB OTG Networking [[https://github.com/alexellis/docker-arm/blob/master/OTG.md]]

### Batteries

* Lead acid batteries need to rest after being charged
* Ambient temp is relevant for charge cycles
* In lead-acid cells, the electrolyte (sulfuric acid) participates in the cell’s normal charge/discharge reactions. As the cells are discharged, the sulfate ions are bonded to the plates - sulfuric acid leaves the electrolyte. The process is reversed when the cell is recharged.
* A fully charged lead-acid cell has an electrolyte that is a 25% solution of sulfuric acid in water (specific gravity about 1.26). A fully discharged lead-acid cell has virtually no sulfuric acid in its almost pure water electrolyte (specific gravity about 1.00). As the sulfuric acid concentration in the electrolyte changes so does the electrical resistance of the electrolyte, which in turn changes the internal resistance of the entire cell.
* Store Lead acid batteries fully charged and not above 25 C (high self-discharge)
* Don’t freeze when discharged
* Charge level vs charge capacity. Charge level by open circuit voltage or hydrometer
* Lead acid bats need to settle after charge
* Charge cycle up to 14 hours
* Wet cell, Flooded vs maintenance free/sealed/VRLA (AGM, Gel)

### Solar panels

monokristallinen (efficiency 25,6 %), polykristallinen (efficiency 20,8 %) und amorphen (9-10 % efficiency)

#### Sun-tracking installation

Testinstallation in Germany (tracking vs. stationary):

* sunny Tag +35%
* half-day cloudy +30% (~ -45% for both stationary and tracking installation compared to sunny day)
* overcast +7% (~ -65% for both stationary and tracking installation compared to sunny day)
* biggest gain beginning and end of day