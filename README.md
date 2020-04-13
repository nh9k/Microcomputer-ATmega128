# Microcomputer-ATmega128

## Outline
[1. LED on-off](#1-led-on---off)
[2. Switch debouncing](#2-switch-debouncing)
[3. 7-Segment LED display](#3-7---segment-led-display)
[4. Control motor velocity using PWM](#4-control-motor-velocity-using-pwm)
[5. LCD display and print float type](#5-lcd-display-and-print-float-type)
[6. USART serial communication](#6-usart-serial-communication)
[7. Rhythm game using Ultrasonic sensor](#7-rhythm-game-using-ultrasonic-sensor)

## 1. LED on-off
## 2. Switch debouncing
## 3. 7-Segment LED display
## 4. Control motor velocity using PWM
## 5. LCD display and print float type
## 6. USART serial communication
## 7. Rhythm game using Ultrasonic sensor


**Schematic using OrCAD**
![Schematic](https://user-images.githubusercontent.com/56310078/79130034-45c6ee00-7de1-11ea-91a4-1b0cddefc5f0.JPG)

**Ultrasonic sensor** [datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)

|HC-SR04|electric parameter|
|---|---|
|![1](https://user-images.githubusercontent.com/56310078/79130420-e6b5a900-7de1-11ea-9e1b-0f7b8cf02a26.jpg)|![2](https://user-images.githubusercontent.com/56310078/79130421-e7e6d600-7de1-11ea-95a1-5c7cedfc4f28.png)|

**driving ultrasonic sensor**
1.Input 10us length pulse through TRIGGER pin
2. The sensor transmits ultrasonic waves toward the front
3. Calculate the length of time that the ultrasonic wave reflected by the object
4. The ECHO pin outputs a pulse proportional to the length of time.

**Demo video** [Link](https://serviceapi.nmv.naver.com/flash/convertIframeTag.nhn?vid=F95B2AEE791F629FB60157707F7CE007402B&outKey=V12712b22900b00ecdc5157aa820458275cd72f5cc2f7010330da57aa820458275cd7&width=544&height=306)
![demo-short](https://user-images.githubusercontent.com/56310078/79133356-da801a80-7de6-11ea-8140-8906e32a1719.gif)

### See pdf file(name: Rhythm-game-Reportfile) for details in folder 7-Rhythm-game-using-Ultrasonic-sensor

## 5. Author
Nanhee Kim / [@nh9k ](https://github.com/nh9k)