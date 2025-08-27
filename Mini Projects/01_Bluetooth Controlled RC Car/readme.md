# LPC21xx UART Motor Control

This project demonstrates **DC motor direction control** using an **LPC21xx ARM7 microcontroller** with UART communication.  
Commands are sent from a PC (via UART) to control two motors connected through an H-Bridge (e.g., L293D / L298N).

---

## 🛠 Features
- UART0 interrupt-based command reception  
- Controls two motors independently  
- Supports **Forward, Backward, Stop, Left, Right** operations  
- Echoes received command back to terminal (for debugging)  

---

## 📜 Motor Control Truth Table

### Motor Input Control Table
| IN1 | IN2 | IN3 | IN4 | Spinning Direction | Char |
|-----|-----|-----|-----|---------------------|------|
|  0  |  0  |  0  |  0  | Motor OFF           |  S   |
|  1  |  0  |  1  |  0  | Forward             |  F   |
|  0  |  1  |  0  |  1  | Backward            |  B   |
|  0  |  0  |  1  |  0  | Left                |  L   |
|  1  |  0  |  0  |  0  | Right               |  R   |

---

## 🎮 Commands

Send one character over UART to control the robot:

| Command | Action      | Motor1 | Motor2 |
|---------|-------------|--------|--------|
| `F`     | Forward     | Fwd    | Fwd    |
| `B`     | Backward    | Rev    | Rev    |
| `S`     | Stop        | Stop   | Stop   |
| `L`     | Left Turn   | Stop   | Fwd    |
| `R`     | Right Turn  | Fwd    | Stop   |

---

## 🔧 Hardware Setup
- **MCU**: LPC21xx (tested on LPC2129 / LPC2148)  
- **Driver IC**: L293D / L298N (H-Bridge)  
- **Motors**: 2 DC Motors  
- **UART**: Connected to PC (via USB-to-Serial / RS232)  

### Pin Mapping
| LPC21xx Pin | Signal | Description |
|-------------|--------|-------------|
| P0.4        | IN1    | Motor1 Input A |
| P0.5        | IN2    | Motor1 Input B |
| P0.6        | IN3    | Motor2 Input A |
| P0.7        | IN4    | Motor2 Input B |

---

## 📂 Files
- `main.c` → Motor control + UART ISR logic  
- `UART.h` → UART initialization functions  

---

## ▶️ How to Run
1. Flash the code to LPC21xx using Keil/FlashMagic.  
2. Connect UART0 to PC (baudrate: **9600 8N1**).  
3. Open Serial Terminal (e.g., PuTTY, TeraTerm).  
4. Send commands (`F`, `B`, `S`, `L`, `R`).  
5. Observe motor response.  

---

## ⚠️ Notes
- Unknown characters default to **Stop** for safety.  
- Ensure external motor supply voltage matches motor rating.  
- Swap IN1/IN2 or IN3/IN4 if motor spins in the wrong direction.  

---

## 📸 Demo
(You can add wiring diagram or test GIF here)

---

## ✍️ Author
Developed by **Prahadeeshwaran K** 🚀  
