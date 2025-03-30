# Infrared Wireless Communication System

This project documents the design and implementation of a low-cost infrared (IR) transmitter and receiver system suitable for industrial wireless communication. Developed using off-the-shelf components and Arduino Nanos, this system demonstrates how reliable data transfer can be achieved using IR light over short distances.

---

## Project Objective
Design and prototype a wireless IR communication system that is:
- Inexpensive and reliable.
- Easy to assemble and scale for mass production.
- Capable of operating at 1500 baud over a distance of at least 1 meter.

---

## System Overview

### Transmitter Circuit
- **Microcontroller**: Arduino Nano.
- **IR LEDs**: 3× TSAL6100 in series.
- **Amplification**: LM318 configured as a non-inverting op-amp.
- **Control**: 2N2222 BJT to switch LEDs based on digital input.

**Design Highlights:**
- Voltage gain achieved via resistor ratio (R1 = 1.5kΩ, R2 = 1kΩ).
- Resistors chosen to supply ~100mA to LEDs.
- Op-amp boosts Arduino 5V signal to 12V.

### Receiver Circuit
- **Microcontroller**: Arduino Nano.
- **Sensor**: QSD124 phototransistor.
- **Load Resistor**: 200Ω to operate in switch mode.

**Design Highlights:**
- Analog pin (A0) reads voltage changes caused by IR detection.
- Minimal component count for compact and scalable design.

---

## Implementation

## Hardware
- Initial testing on breadboards.
- Final circuit soldered onto vector boards for reliability.
- Transmitter powered via 12V supply; receiver powered via Arduino Nano 5V pin.

### Software

#### Transmitter
- Serial interface to enter messages.
- Converts ASCII characters into 8-bit binary with parity and stop bits.
- Maintains precise bit timing (667μs per bit) for 1500 baud using `delayMicroseconds()`.
- Includes `"bit rate"` command to evaluate timing and transmission efficiency.

#### Receiver
- Continuously samples IR signal via analog pin.
- Uses FIFO buffer to store and decode bits.
- Validates transmission using parity and stop bits.
- Reports transition count and bit error rate (BER) for diagnostics.

---

## Testing & Evaluation

### Lab Setup
- Distance: ~1 meter between transmitter and receiver.
- Both connected to separate serial monitors.
- Aligned IR LEDs and phototransistor for accurate line-of-sight.

### Results
- **Transmission Distance**: Just over 1 meter before BER increased significantly.
- **Bit Rate**:
  - Transmitter: ~1450 bps
  - Receiver: ~1350 bps
- **Bit Error Rate**: ~5% within 1 meter range.

### Interpretation
- Acceptable performance for low-bandwidth applications.
- Distance can be extended with:
  - More IR LEDs in series.
  - Higher current sources (beyond op-amp capabilities).
  - Multiple phototransistors to increase reception angle.

---

## Conclusion

The project successfully demonstrated wireless IR data transmission over short distances using low-cost components. With additional enhancements, such as increased signal power and receiver sensitivity, this design could be adapted for broader industrial use cases.

---

## References
1. Texas Instruments, "High-Performance Operational Amplifiers datasheet", SLOS063B, 2002
2. Vishay, "High Power Infrared Emitting Diode, 940 nm", 81009 datasheet, 2014
3. onsemi, "Plastic Silicon Infrared Phototransistor", QSD123/D, 2023
4. onsemi, "Amplifier Transistors", P2N2222A/D, 2013
5. Arduino, "Arduino Nano Pinout", A000005, 2021
6. Electronics Notes, "Phototransistor Applications & Circuit Configurations"

---

> **Authors**: Conner Glazner, Evan Day, Max Djafarov, Vincent Dick  
> **Skills Demonstrated**: Circuit Design, Embedded C++, Signal Processing, Infrared Communication, Arduino Development

