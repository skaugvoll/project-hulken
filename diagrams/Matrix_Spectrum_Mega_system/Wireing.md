# How to wire; Spectrum, 32x16 and Arduino Mega.

## Spectrum
### Power
Hook the; 

- SHIELD:
	- `5v`, 
	- `3.3v` and 
	- `GND`

- Arduino Mega:
	-  to the according on the `Arduino mega`

### Analog pins
Connect the;

- `SHIELD: A0 --> Arduino Mega A8`
 - In the code: `#define DC_One A8`
- `SHIELD: A1 --> Arduino Mega A9`
 - In the code: `#define DC_Two A9`

### Digital pins
- `4` is **Strobe** on the shield to `4` on the `Arduino Mega`
- `5` on the shield to `5` on the `Arduino Mega`: I do not think this do anything, but think i read that it do somewere. Better safe than sorry.
- `6` is **reset** on the shield to `6` on the `Arduino Mega`.

 
## 32x16 Matrix
