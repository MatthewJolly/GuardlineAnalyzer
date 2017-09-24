# Guardline Protocol Analyzer
Guardline Protocol Analyzer for Saleae Logic software

This analyzer protocol works with [Guardline Wireless Driveway Sensors](https://www.guardlinesecurity.com/)


# Other Information
The sensors use FSK modulation at 914.8MHz and 20Kbps.

Transmitter chip: Melexis TH72031

Receiver chip: Amiccom A7201B

Has not been tested with the 1/4 mile version of the sensors.

This project is based on the [SampleAnalyzer](https://github.com/saleae/SampleAnalyzer) example from Saleae

# Instructions
1. Build project via Visual Studio files (Windows) or python build scripts (Linux/Mac)
2. Add output path in Logic software under Preferences->Developer in the "Search this path for analyzer plugins" box. 
3. Restart Logic.
