# PIRSensorDemo

A PIR sensor demo based on Raspberry Pi and an ADS1115 ADC module

## Connection

### PIR Sensor to ADS1115 module
| PIR Sensor | ADS1115 |
| --- | --- |
| Analog Output | A0 |
| Comparator Output | A1 |

### ADS1115 module to Raspberry Pi
| ADS1115 | Raspberry Pi |
| --- | --- |
| VDD | 3.3V |	
| GND | GND |
| SCL | SCL |
| SDA |	SDA |

## Requirement
Please install Qt before compiling.

Basically you will need `qt5-default` and `qt5-qmake` package. 

Use `qmake` directly to compile.

Run with `./PIRSensorDemo` in terminal.

---
Refer: https://learn.sparkfun.com/tutorials/raspberry-gpio for Raspberry Pi pin layout.

