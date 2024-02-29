# Smart-Parking-System
Smart Parking Syetem works with 2 ultrasonic sensor because IR sensors are analoug and really hard to calibrate.
so the system is to cound the car and there are 7 max car that enter the parking system and then the gate of the parking will not open . Untill any of the car from the parking exit.

There are 2 Ultrasonic sensors. one in the beguining of the gate and one after the gate first sensor detect the comming cars into the parking and microcontroller count the number and display the data othe OLED/LCD display. 

IMPORTANT NOTE
The ulrasonic sensor and the servo motors consume more power then the voltage regulator of the arduino can produce it is recomanded to connect a external power source to both ultrasonic sensors and servo motors.
