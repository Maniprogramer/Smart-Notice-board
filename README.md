# Arduino GSM Module Control

This Arduino sketch demonstrates how to use a GSM module to send and receive text messages (SMS). It includes functionalities to initialize the GSM module, receive messages, and send messages using a P10 LED display for visual feedback.
 
## Table of Contents

+ Components Required
+ Circuit Diagram
+ Setup Instructions
+ Usage
+ Contributing
+ License
## Components Required

+ Arduino board
+ GSM module (e.g., **SIM800L**)
+ P10 LED display module
+ Jumper wires
## Circuit Diagram

+ Insert a circuit diagram image here showing how the components are connected.

## Setup Instructions

+ Connect the GSM module to the Arduino board using jumper wires.
+ Connect the P10 LED display module to the Arduino board using jumper wires.
+ Upload the provided Arduino sketch to the Arduino board using the Arduino IDE or any compatible development environment.
+ Ensure that the GSM module is powered on and properly connected to the network.
## Usage

+ Open the serial monitor in the Arduino IDE or any serial monitor application.
+ Power on the Arduino board.
+ The sketch will initialize the GSM module and display "**System Ready**" on the serial monitor once ready.
+ Press the button connected to pin 2 to display the startup message on the P10 LED display.
+ The GSM module is set to receiving mode **(AT+CNMI=2,2,0,0,0)** and text mode **(AT+CMGF=1)** for SMS handling.
+ When a message is received __("*" character detected in the message)__, it will be displayed on the serial monitor and the P10 LED display.
+ To send a message, modify the phone number __(AT+CMGS="your_phone_number")__ in the SendMessage function and the message content __(msg variable)__.
+ Press the button connected to pin 2 again to send the message using the GSM module.
+ The sent message will be displayed on the serial monitor, and you should receive it on the specified phone number.
## Contributing

+ Contributions to improve and expand the functionality of this code are welcome. You can submit issues for bugs or suggestions for enhancements. Pull requests are also appreciated.

## License

+ This project is licensed under the MIT License - see the LICENSE file for details.
