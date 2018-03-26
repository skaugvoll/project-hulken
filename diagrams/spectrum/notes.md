# Spectrum shield

## Pins needed to work
- 5v power
- 3.3v Power
- GND ground power
- A0 - something
- A1 - something
- 4 - Strobe
- 5 (optinally I think)
- 6 - Reset
- TX
- RX

## Power
Hook the `5v`, `3.3v` and `GND` on the shield to the according on the `Arduino mega`

## Analog pins
In all examples and sketches found online, the shields `DC\_One` and `DC\_Two` are connected to `A0` and `A1`, but I have found that they **can be connected to arbitrary Analog pins**. 

- `#define DC\_One A0   --> Ax`
- `#define DC\_Two A1   --> Ax + 1` 

I choose to use `x = 8` --> `A8` and `A9`.

### Spectrum shield and matrix
The **matrix** `uses A0 -> A3`, thus I use `A8` and `A9` for the spectrum shield

## Digital pins
- `4` is **Strobe** on the shield to `4` on the `Arduino Mega`
- `5` on the shield to `5` on the `Arduino Mega`: I do not think this do anything, but think i read that it do somewere. Better safe than sorry.
- `6` is **reset** on the shield to `6` on the `Arduino Mega`.
