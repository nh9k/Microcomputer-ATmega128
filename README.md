# Microcomputer-ATmega128

## Outline

|||
|---|---|
|[1. LED on-off](#1-led-on-off)|[Detail report](https://github.com/nh9k/Microcomputer-ATmega128/blob/master/1-LED-on-off/1-LED-on-off.pdf)|
|[2. Switch debouncing](#2-switch-debouncing)|[Detail report](https://github.com/nh9k/Microcomputer-ATmega128/blob/master/2-Switch-debouncing/2-Switch-debouncing.pdf)|
|[3. 7-Segment LED display](#3-7-segment-led-display)|[Detail report](https://github.com/nh9k/Microcomputer-ATmega128/blob/master/3-7-Segment-LED-display/3.%207-Segment%20LED%20display.pdf)|
|[4. Control motor velocity using PWM](#4-control-motor-velocity-using-pwm)|[Detail report](https://github.com/nh9k/Microcomputer-ATmega128/blob/master/4-Control-motor-velocity-using-PWM/4-Control-motor-velocity-using-PWM.pdf)|
|[5. LCD display and print float type](#5-lcd-display-and-print-float-type)|[Detail report](https://github.com/nh9k/Microcomputer-ATmega128/blob/master/5-LCD-display-and-print-float-type/5-LCD-Reportfile.pdf)|
|[6. USART serial communication](#6-usart-serial-communication)|[Detail report](https://github.com/nh9k/Microcomputer-ATmega128/blob/master/6-USART-serial-communication/6-USART-Reportfile.pdf)|
|[7. Rhythm game using Ultrasonic sensor](#7-rhythm-game-using-ultrasonic-sensor)|[Detail report](https://github.com/nh9k/Microcomputer-ATmega128/blob/master/7-Rhythm-game-using-Ultrasonic-sensor/Rhythm-game-Reportfile.pdf)|
|[8. Author](#8-author)|[All Demo video](https://blog.naver.com/kimnanhee97/221847029738)|

## 1. LED on-off

1. Just on/off LED
2. Using Interrupt for on/off LED  
![figure1](https://user-images.githubusercontent.com/56310078/79585373-ad937680-810a-11ea-8339-ec56df92bf73.png)   

**[Full Demo video Link](https://serviceapi.nmv.naver.com/flash/convertIframeTag.nhn?vid=DCA537E5669DC44F3F90CA28F2899DA55244&outKey=V125e91609d591d6ca5475d241b37b14007b5d91738df1bc823c75d241b37b14007b5&width=544&height=306)**  
**See [pdf file]() for details in folder `1-LED-on-off`**  

## 2. Switch debouncing

|Measure the phenomenon|Bounce|
|---|---|
|![figure1](https://user-images.githubusercontent.com/56310078/79584566-88eacf00-8109-11ea-9627-292841ef5f79.png)|![figure2](https://user-images.githubusercontent.com/56310078/79584577-8be5bf80-8109-11ea-89e7-15dafcbe7696.png)|

**Debouncing**
1. Using Delay - Software way
2. Using Capacior - Hardware way

**[Full Demo video Link](https://serviceapi.nmv.naver.com/flash/convertIframeTag.nhn?vid=691CCECBED56E0EA05FE1B6811099841C5E0&outKey=V1299abd73f00b54d60a4062e833f97b7da2eadf972d751ed849d062e833f97b7da2e&width=544&height=306)**    
**See [pdf file](https://github.com/nh9k/Microcomputer-ATmega128/blob/master/2-Switch-debouncing/2-Switch-debouncing.pdf) for details in folder `2-Switch-debouncing`**

## 3. 7-Segment LED display

**Schematic**  
![figure1](https://user-images.githubusercontent.com/56310078/79276292-bb66b300-7ee2-11ea-9d11-a3e3af0ca072.png)

|7-Segment|Common Anode Type|S-5263ASR1|
|---|---|---|
|![figure2](https://user-images.githubusercontent.com/56310078/79276300-bd307680-7ee2-11ea-9997-f4a99b3496b7.png)|![figure3](https://user-images.githubusercontent.com/56310078/79276305-bdc90d00-7ee2-11ea-90ea-a984ed135cd9.png)|![figure4](https://user-images.githubusercontent.com/56310078/79276309-be61a380-7ee2-11ea-9852-69c6a2b1036f.png)|   

|Transistor||MPS2907A|
|---|---|---|
|![figure5](https://user-images.githubusercontent.com/56310078/79276311-be61a380-7ee2-11ea-9893-a76861f92e89.png)|![figure6](https://user-images.githubusercontent.com/56310078/79276315-befa3a00-7ee2-11ea-9dfc-32fc3ef6c9be.png)|![figure7](https://user-images.githubusercontent.com/56310078/79276317-befa3a00-7ee2-11ea-8552-20aba60d085f.png)|

**[Full Demo video Link](https://serviceapi.nmv.naver.com/flash/convertIframeTag.nhn?vid=2722AF99EF7D1581E586FE15C28C08CD95CD&outKey=V1210cf905e6d5085454cded0b06bbc892e14c49e0bd6793f1a84ded0b06bbc892e14&width=544&height=306)**  
![short-demo](https://user-images.githubusercontent.com/56310078/79276875-b6563380-7ee3-11ea-89a3-377d67822083.gif)

**See [pdf file](https://github.com/nh9k/Microcomputer-ATmega128/blob/master/3-7-Segment-LED-display/3.%207-Segment%20LED%20display.pdf) for details in folder `3-7-Segment-LED-display`**

## 4. Control motor velocity using PWM

|Driving motor|Schematic for 7 Segment|
|---|---|
|![figure2](https://user-images.githubusercontent.com/56310078/79275025-69249280-7ee0-11ea-9cf3-76d8aac0a691.png)|![figure1](https://user-images.githubusercontent.com/56310078/79275022-688bfc00-7ee0-11ea-8e54-5a2de54095b8.png)|

**[Full Demo video Link](https://serviceapi.nmv.naver.com/flash/convertIframeTag.nhn?vid=470622877CD84642DBDFEC25CE200635557F&outKey=V12866437910e650e9b759039a26491935ecc3dd0462b46e33e729039a26491935ecc&width=544&height=306)**  
![frame_242](https://user-images.githubusercontent.com/56310078/79275624-8017b480-7ee1-11ea-8695-904cc9a62110.gif)

**See [pdf file](https://github.com/nh9k/Microcomputer-ATmega128/blob/master/4-Control-motor-velocity-using-PWM/4-Control-motor-velocity-using-PWM.pdf) for details in folder `4-Control-motor-velocity-using-PWM`**

## 5. LCD display and print float type

**Schematic**
![figure1](https://user-images.githubusercontent.com/56310078/79136685-621c5800-7dec-11ea-89fd-7f95d4c0df86.png)

|Potentiometer|3362 Series (50k ohm) 3362P-1-503|
|---|---|
|![figure2](https://user-images.githubusercontent.com/56310078/79136689-634d8500-7dec-11ea-9a15-ded6921b30d0.png)|![figure3](https://user-images.githubusercontent.com/56310078/79136692-63e61b80-7dec-11ea-8583-30ce20e0c998.png)|

**[Full Demo video Link](https://serviceapi.nmv.naver.com/flash/convertIframeTag.nhn?vid=0FF636ABF0A9DC5567B43C2EA90D5CE167C2&outKey=V12107dbf2e4648a5afc75ee249d9bdd3f46e7fd8068a80eccde05ee249d9bdd3f46e&width=544&height=306)**  
![frame](https://user-images.githubusercontent.com/56310078/79276022-367b9980-7ee2-11ea-90d9-599908c47695.gif)

**See [pdf file](https://github.com/nh9k/Microcomputer-ATmega128/blob/master/5-LCD-display-and-print-float-type/5-LCD-Reportfile.pdf) for details in folder `5-LCD-display-and-print-float-type`**  

## 6. USART serial communication

**[Full Demo video Link](https://serviceapi.nmv.naver.com/flash/convertIframeTag.nhn?vid=FF16E407DCCD34D582C2C10964006B52B35C&outKey=V124f3d035867b5c8ac9766fb526a2c868b1e404e0324d1904be966fb526a2c868b1e&width=544&height=306)**  

![demo-short](https://user-images.githubusercontent.com/56310078/79135647-a6a6f400-7dea-11ea-92fa-b635e3ef9372.gif)

**See [pdf file](https://github.com/nh9k/Microcomputer-ATmega128/blob/master/6-USART-serial-communication/6-USART-Reportfile.pdf) for details in folder `6-USART-serial-communication`**

## 7. Rhythm game using Ultrasonic sensor


**Schematic using OrCAD**
![Schematic](https://user-images.githubusercontent.com/56310078/79130034-45c6ee00-7de1-11ea-91a4-1b0cddefc5f0.JPG)

**Ultrasonic sensor** [datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)

|HC-SR04|electric parameter|
|---|---|
|![1](https://user-images.githubusercontent.com/56310078/79130420-e6b5a900-7de1-11ea-9e1b-0f7b8cf02a26.jpg)|![2](https://user-images.githubusercontent.com/56310078/79130421-e7e6d600-7de1-11ea-95a1-5c7cedfc4f28.png)|

**driving ultrasonic sensor**  
1. Input 10us length pulse through TRIGGER pin  
2. The sensor transmits ultrasonic waves toward the front  
3. Calculate the length of time that the ultrasonic wave reflected by the object  
4. The ECHO pin outputs a pulse proportional to the length of time.  

**[Full Demo video Link](https://serviceapi.nmv.naver.com/flash/convertIframeTag.nhn?vid=F95B2AEE791F629FB60157707F7CE007402B&outKey=V12712b22900b00ecdc5157aa820458275cd72f5cc2f7010330da57aa820458275cd7&width=544&height=306)**  

![demo-short](https://user-images.githubusercontent.com/56310078/79133356-da801a80-7de6-11ea-8140-8906e32a1719.gif)

**See [pdf file](https://github.com/nh9k/Microcomputer-ATmega128/blob/master/7-Rhythm-game-using-Ultrasonic-sensor/Rhythm-game-Reportfile.pdf) for details in folder `7-Rhythm-game-using-Ultrasonic-sensor`**


## 8. Author
Nanhee Kim / [@nh9k ](https://github.com/nh9k) / [PersonalBlog](https://blog.naver.com/kimnanhee97)
