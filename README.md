# Guardline Protocol Analyzer
Guardline Protocol Analyzer for Saleae Logic software

This analyzer protocol works with [Guardline Wireless Driveway Sensors](https://www.guardlinesecurity.com/)


# Other Information
The sensors use FSK modulation at 914.8MHz and 20Kbps.

Transmitter chip: **Melexis TH72031**

Receiver chip: **Amiccom A7201B**

Has not been tested with the 1/4 mile version of the sensors.

This project is based on the [SampleAnalyzer](https://github.com/saleae/SampleAnalyzer) example from Saleae

# Instructions
1. Build project via Visual Studio files (Windows) or python build scripts (Linux/Mac)
2. Add output path in Logic software under Preferences->Developer in the "Search this path for analyzer plugins" box. 
3. Restart Logic.

# Protocol
The Guardline protocol seems to consist of a 24bit ID + 1 extra bit. 

Each bit in the ID is represented by one symbol, or 3 bits in the data stream.

Symbols follow the pattern **X10** where X is the data bit and the trailing 1 and 0 is for communication reliability (I assume).

So the symbols we are looking for are **010** and **110** to represent HIGH/LOW.

The ID will repeat 30+ times when the sensors transmit.

# Usage
The **Serial** channel is the channel the data will be on

The **Label** channel is just used to display bit information for the data on the Serial channel

**Period** is the average time in microseconds for one bit in a symbol.

**Gap Time** is the time between each ID repetition. 

# Example
![Example data stream](https://github.com/MatthewJolly/GuardlineAnalyzer/raw/master/example.png)