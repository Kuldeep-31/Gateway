# Gateway
Device sending data to Gateway

Information about the repo
1) gateway folder contains files for the server which will receive parameter value from device. It contains the source code as well as the makefile to build the code. The output gateway to be executed on linux terminal.
2) device folder contains files for the device which will send data to the gateway(server) in a periodic manner. It contains the source code as well as the Makefile to build. The output file device needs to be executed on linux terminal. 

Steps to build
1) Run make command in resepective folders to generate the respective output files.

Execute the build
1) In case of gateway you just need to run the output file on terminal
./gateway

2) In case of device you just need to run the output file along with an argument which will be used as an device identifier. The identifier will be an integer value.
./device 1

3) you can run as many instance of device on different terminal

To view the data received on the server, the server will ask you to enter 'd' or 'D' to display the record. User just needs to enter the letter and it will display the following list on terminal

1) device identifier
2) latest parameter value send by device.
3) Number of values send by device
4) total number of different devices connected to the server
