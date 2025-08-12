# LPC21xx ARM7 Microcontroller Projects

Welcome to the repository dedicated to hands-on embedded systems development using the **LPC21xx** series microcontrollers based on the **ARM7TDMI-S** core from NXP (formerly Philips).

---

## 🧠 About LPC2129 Series

The **LPC21xx** family is a range of 32-bit ARM7 microcontrollers designed for real-time embedded applications. Known for their balance of performance, memory, and peripheral integration, they are widely used in:

- 🏭 Industrial automation  
- 📱 Consumer electronics  
- 🤖 Robotics  
- 📡 Communication systems  

### 🔧 Key Features

# ⚡ ARM7TDMI-S Based High-Performance 32-bit RISC Microcontroller

## 🧠 Core Architecture
- 🖥 **ARM7TDMI-S** 32-bit RISC core  
  - Supports **ARM (32-bit)** and **Thumb (16-bit)** instruction sets for higher code density  
  - **Three-stage pipeline** for efficient instruction execution  
  - **Von Neumann architecture** – shared instruction & data bus  
- ⚡ **CPU clock up to 60 MHz** for high-speed processing  
- 🔄 **On-chip crystal oscillator** (1 MHz to 25 MHz input range)  
- ⛓ **On-chip PLL** for frequency multiplication (configurable)  

## 💾 Memory System
- 📦 **256 KB on-chip Flash ROM**  
  - 🔧 **In-System Programming (ISP)**: program/update via serial interface without removing from the system  
  - 🛠 **In-Application Programming (IAP)**: allows firmware updates during runtime  
- 🗂 **16 KB on-chip SRAM** for data and stack storage  
- 🚀 **Zero-wait-state** operation for most instructions when running from internal memory  

## 🔔 Interrupt & Control
- 🎯 **Vectored Interrupt Controller (VIC)**  
  - Up to **32 interrupt sources**  
  - Prioritized vectoring for minimal ISR latency  
- 🕹 **Reset and power management** features for low-power modes  

## 📡 Communication Interfaces
- 🔌 **Two UARTs** (full-duplex, with FIFO buffers) – supports RS-232, RS-485, IrDA  
- 🔗 **I²C interface** – supports master and slave modes, up to 400 kHz  
- 🔄 **Two SPI interfaces** – full-duplex, up to several Mbps, supports master/slave  
- 📡 **Two CAN channels** – compliant with ISO 11898-1, supports standard & extended frames  

## ⏱ Timers & PWM
- ⏳ **Two 32-bit timers**  
  - Each with **capture** and **compare** capabilities  
  - **7 capture/compare channels** total  
- 🎵 **PWM unit** – up to **6 independent outputs**  
  - Useful for motor control, signal generation, dimming control  

## 📊 Analog Features
- 🎚 **4-channel, 10-bit ADC**  
  - Supports up to **400 kSamples/s** conversion rate  
  - Single-ended input mode  

## ⏰ Timekeeping & Safety
- ⏱ **Real-Time Clock (RTC)**  
  - Runs on separate 32.768 kHz crystal for accurate timekeeping  
- 🛡 **Watchdog Timer (WDT)** to reset system on software failure  

## 🔌 General Purpose I/O
- 🛠 **General-purpose I/O pins** (up to 46)  
  - Multiple pin functions (GPIO, peripheral control, interrupts)  
  - Configurable pull-up/pull-down resistors  

---

### 📋 Summary Table

| Feature | Details |
|---------|---------|
| **Core** | ARM7TDMI-S, 32-bit RISC with Thumb |
| **Max Clock** | 60 MHz |
| **Flash Memory** | 256 KB (ISP, IAP) |
| **RAM** | 16 KB SRAM |
| **Timers** | 2 × 32-bit timers (7 capture/compare channels) |
| **PWM** | Up to 6 outputs |
| **ADC** | 4 channels, 10-bit |
| **UART** | 2 ports |
| **I²C** | 1 port |
| **SPI** | 2 ports |
| **CAN** | 2 channels |
| **RTC** | Yes |
| **WDT** | Yes |
| **GPIO** | Up to 46 pins |
| **Interrupts** | Vectored, up to 32 sources |

---

## 🚀 Getting Started

### ✅ Requirements

- 🧱 LPC21xx Development Board (e.g., LPC2129, LPC2148)  
- 🛠 Keil µVision4 or µVision5 IDE  
- 🔃 Flash Magic (for UART flashing)  
- 🔌 USB-UART or JTAG debugger  

### 🧪 How to Use

1. 📂 Open the `.uvproj` file in Keil uVision  
2. 🧠 Write or modify code  
3. 🧰 Build and generate `.hex`  
4. 🔥 Flash using Flash Magic  
5. 👀 Observe output via LED, UART, etc.

---

## 📚 Resources

- 📄 [NXP LPC21xx Datasheets](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/lpc2000-arm7:MC_30190)  
- 🛠 [Keil uVision IDE](https://www.keil.com/)  
- 🔥 [Flash Magic](https://www.flashmagictool.com/)  
- 📘 ARM7TDMI Technical Reference Manual  

---

## 📜 License

This project is open-source under the **MIT License**.  
Feel free to use it for learning, academic, or personal purposes. 😊

---

## 🤝 Contributing

Got improvements or new projects?  
✨ Fork the repo, push your code, and submit a pull request — contributions are always welcome!

