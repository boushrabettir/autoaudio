# autoaudio
An automatic volume adjustment system for TVs using Arduino.

# to do
- understand all this shiz 🐱 and how it works

# to purchase
1. [Arduino w/usb - 13$](https://www.amazon.com/DORHEA-ATMEGA328P-Module-Micro-Controller-Compatible/dp/B08PZ36KBX/ref=sr_1_5?crid=FVI8JS7YDBGM&keywords=arduino%2Bnano%2Bv3&qid=1690081625&sprefix=arduino%2Bnano%2Bv3%2Caps%2C167&sr=8-5&th=1)
2. [IR Transmitter / Reciever - 7$](https://www.amazon.com/Emitter-Receiver-VS1838B-Infrared-Raspberry/dp/B07TLBJR5J/ref=sr_1_5?keywords=ir%2Btransmitter%2Band%2Breceiver&qid=1690080988&sprefix=ir%2Btransmit%2Caps%2C146&sr=8-5&th=1)
3. [Mic Sensor - 7$](https://www.amazon.com/Comidox-Sensitivity-Microphone-Detection-Arduino/dp/B07J6N734S/ref=sr_1_6?crid=SC0QAPQE5KG7&keywords=mic+sensor&qid=1690081002&sprefix=mic+sensor%2Caps%2C140&sr=8-6)
4. [Small Breadboard - 6.50$](https://www.amazon.com/HiLetgo-SYB-170-Breadboard-Colorful-Plates/dp/B071KCZZ4K/ref=sr_1_8?keywords=breadboard+small&qid=1690082823&sr=8-8)
5. [Wiring/Resistors (has leds) - 12$](https://www.amazon.com/EL-CK-002-Electronic-Breadboard-Capacitor-Potentiometer/dp/B01ERP6WL4/ref=sr_1_3?crid=1YOIUIVXA164Q&keywords=resistors%2Barduino&qid=1690081448&sprefix=resistors%2Barduino%2Caps%2C167&sr=8-3&th=1)
6. Momentary button/switch (later)

**total**: 45.50$

## later
1. momentary button/switch for customization (low/med/high)

# just some notes
learn abt above parts (look at ipad)
connect wiring with eachother
grab hex values (stimulating up and down button) thru ir reciever (decode results)

intial/brute force way probably to have a threshold for how low/high volume is and increase/decrease it when necessary 
(have a pause in between to avoid rapid changes)

could i use a audio jack to get a better picture of the audio itself? (no, we dont have a port for it)
instead i can place the mic sensor below the speakers

would have to reduce outside noise as well

if manually changed, to mute how would that work

later down the line have different thresholds for both my parents, values change dependent

