# ESP8266_controlled_car
This project is part of our IoT elective. This project provides an ESP8266 enabled DIY car which can be controlled using laptop or voice commands.
### Use case of the project:
The project aims at solving the issue of reaching un-reachable places. Home automation can easily be ported to this project with suitable changes in the hardware.
### Potential Users
Anyone who is facing the issue of tracking/surveying a large area with limited manpower can easily modify this project to track whatever is necessary
### Brief Technical Description
This project aims at imparting a DIY car with the ability to be controlled using laptop or voice commands. Both voice and laptop instructions are sent to the ESP8266 module on the car which acts a controller of the car. The ESP8266 module controls the 4 BO motors attached to the wheel via L298n H-bridge motor drivers. We are using UDP protocol to communicate between the laptop and the esp module. A MQTT protocol was used to send instructions in voice mode.    
### Contributors
* Srivatsav Gunisetty AM.EN.U4CSE16028
  * Contribution to the project
    * Worked on the setting up the car with ESP8266 and L298n H-bridge motor driver
  * Learning from the project
    * Learnt how to set up pins in the ESP8266
    * Learnt how to read hardware description
* Surya Chaitanya Palepu AM.EN.U4CSE16147
  * Contributon to the project
    * Worked on the setting up the car with ESP8266 and L298n H-bridge motor driver
    * Initiator of the project
  * Learning from the project
    * Learnt how to wire things up
    * Learnt how to google things about hardware
* Roshan Patnaik M P AM.EN.U4CSE16040
  * Contribution to the project
    * Set up UDP protocol to communicate with the ESP8266 in the RC Car
  * Learning from the project
    * Learnt about UDP protocol
    * Learnt how to write python scripts
* Sandesh Ghanta AM.EN.U4CSE16254
  * Contribution to the project
    * Set up the voice enabled service for the ESP8266 through google assistant
  * Learning from the project
    * Learnt about mqtt protocol
    * Learnt about ifttt, adafruit and how to integrate them
