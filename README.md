# 74HC165-Microcontroller-Input-Expansion

This project explores how to use the **74HC165 shift register** to expand the number of digital **inputs** available on an **ESP8266**, using only 3 GPIO pins. It’s built with **PlatformIO**, but it’s also compatible with the **Arduino IDE**.

The example reads 8 parallel inputs (like buttons or switches) and prints their values to the serial monitor. It uses **parallel-to-serial** communication to achieve input expansion with minimal pin usage.

---

### 🧩 This Project is Part of a Shift Register I/O Expansion Series

This repository is the **second part** of a series exploring how to expand the I/O capabilities of microcontrollers using shift registers:

- **Part 1**: [74HC595-Microcontroller-Output-Expansion](https://github.com/Yamil-Serrano/74HC595-Microcontroller-Output-Expansion)  
- **Part 2**: [74HC165-Microcontroller-Input-Expansion (this repo)](https://github.com/Yamil-Serrano/74HC165-Microcontroller-Input-Expansion)

In Part 1, I explain how to use the 74HC595 to control 8 outputs using serial data.  
This project is the *reverse* — it reads multiple digital inputs using the **74HC165** via **parallel-to-serial** communication.

---

## What You'll Learn

- What the 74HC165 does and how it works  
- How to read multiple digital inputs using a shift register  
- How to connect the 74HC165 to an ESP8266  
- How to use clock, latch, and data pins to capture and shift input states  

---

## How It Works

The **74HC165** reads 8 parallel inputs (D0–D7) and shifts them out serially through a single `QH` pin. You control the data flow using 3 pins:

- **PL (Parallel Load)**: Captures the current state of the input pins  
- **CLK (Clock)**: Shifts bits one by one to the output  
- **QH**: The serial output line, connected to the ESP8266

By toggling these lines, you can read 8 (or more, if cascaded) inputs using just a few GPIOs.

---

## Hardware Used

- ESP8266 (NodeMCU / Wemos D1 mini)  
- 74HC165 Shift Register  
- Breadboard + Jumper Wires  
- Push Buttons or Switches  
- Optional: Pull-down resistors (10kΩ)  

---

## Wiring Table

| 74HC165 Pin | Connected To (ESP8266) | Purpose         |
|-------------|-------------------------|-----------------|
| QH (9)      | D5 (GPIO14)             | Serial Data Out |
| CLK (2)     | D2 (GPIO4)              | Clock           |
| PL (1)      | D1 (GPIO5)              | Parallel Load   |
| CE (15)     | GND                     | Enable (Active Low) |
| GND         | GND                     | Ground          |
| VCC         | 3.3V or 5V              | Power Supply    |
| D0–D7       | Input Devices (Buttons) | Input Pins      |

> ⚠️ Remember to connect **pull-down resistors** on each button or input line to ensure a clean LOW signal when not pressed.

---

## Code Overview

The `readShiftRegister()` function handles:

1. Loading the inputs by pulsing `PL` LOW then HIGH  
2. Shifting bits out by toggling the `CP` clock pin  
3. Reading each bit from `QH`

See `src/main.cpp` for the full implementation.

---

## Diagram

![image](https://github.com/user-attachments/assets/7a26a4ef-fbca-4140-bd5b-d94dc830f609)



---

## License

This project is licensed under the MIT License – see the [LICENSE](LICENSE.md) file for details.

---

## Contact

If you have any questions or suggestions, feel free to reach out to me:

GitHub: [Neowizen](https://github.com/Yamil-Serrano)
