# Available Documentation Summary

This document catalogs the documentation available in the Embedder document search for this project.

## ESP32 & ESP-IDF Documentation

### 1. ESP32 Technical Reference Manual
The comprehensive hardware reference for the ESP32 SoC. Covers all on-chip peripherals, registers, and subsystems including:
- CPU and memory architecture (dual-core Xtensa LX6, memory map, caches)
- Interrupt matrix and exception handling
- GPIO and IO MUX / RTC IO MUX pin multiplexing
- UART, SPI, I2C, I2S peripheral controllers
- Timer groups and watchdog timers
- ADC (SAR ADC) and DAC
- DMA controllers
- LED PWM (LEDC), MCPWM, pulse counter, remote control (RMT)
- SDIO/SD/MMC host and slave interfaces
- Ethernet MAC (EMAC)
- Flash encryption and secure boot
- eFuse controller
- ULP co-processor
- Power management and clock configuration

### 2. ESP32 Datasheet
The device datasheet with electrical specifications and functional overview:
- Pin definitions and package information
- Electrical characteristics (operating voltage, current consumption, absolute maximum ratings)
- RF performance specifications (Wi-Fi and Bluetooth)
- Peripheral overview and feature summary
- Strapping pin configurations
- Module ordering information

### 3. ESP32-SOLO-1 Datasheet
Datasheet for the ESP32-SOLO-1 module (single-core ESP32 variant):
- Module pinout and dimensions
- Single-core Xtensa LX6 processor specifications
- Integrated flash memory details
- Antenna design and RF characteristics
- Recommended operating conditions
- Module schematic and PCB layout information

### 4. ESP32 Errata
Known silicon bugs and hardware issues with documented workarounds:
- Identified errata items per silicon revision
- Affected peripherals and conditions that trigger issues
- Software or hardware workarounds for each erratum

### 5. ESP32 Hardware Design Guidelines
PCB design and hardware integration reference:
- Power supply design and decoupling recommendations
- Crystal oscillator circuit design
- Antenna design guidelines (PCB antenna, external antenna)
- Strapping pin configuration and boot mode selection
- Flash and PSRAM interface design
- EMC/EMI considerations
- Schematic checklist and layout guidelines
- Thermal considerations

### 6. ESP-IDF Programming Guide
The software development framework documentation for ESP-IDF:
- Build system (CMake) configuration and usage
- Project structure and component architecture
- API reference for all ESP-IDF components (drivers, protocols, system)
- Peripheral driver APIs (GPIO, UART, SPI, I2C, ADC, etc.)
- Wi-Fi and Bluetooth programming
- FreeRTOS integration and task management
- Partition tables and OTA update mechanisms
- NVS (Non-Volatile Storage) usage
- Logging, error handling, and debugging
- Kconfig system and sdkconfig options
- Bootloader and flash encryption
- Power management APIs

## ESP-AT Documentation

### 7. ESP-AT User Guide
Guide for using the ESP-AT firmware for controlling ESP32 via AT commands:
- AT firmware flashing and setup
- Communication interface configuration
- AT command syntax and response format
- Custom AT command development

### 8. ESP32 AT Command Set
Complete reference of all supported AT commands:
- Basic AT commands (system info, restart, version)
- Wi-Fi AT commands (station/AP mode, scanning, connection)
- TCP/IP AT commands (socket, HTTP, MQTT, etc.)
- Bluetooth AT commands (BLE, Classic BT)
- Hardware-related AT commands (GPIO, ADC, UART)

## Testing Documentation

### 9. ESP Test Tools User Guide
Guide for ESP-IDF testing infrastructure and tools:
- pytest-based testing framework for ESP-IDF
- Hardware-in-the-loop test configuration
- Test case organization and execution
- CI/CD integration for automated testing

## External Peripheral Documentation

### 10. ADS1115
Datasheet/reference for the Texas Instruments ADS1115 16-bit ADC:
- 16-bit delta-sigma ADC with programmable gain amplifier (PGA)
- 4 single-ended or 2 differential input channels
- I2C interface (addresses 0x48-0x4B)
- Programmable data rates (8 SPS to 860 SPS)
- Internal voltage reference
- Comparator with programmable thresholds
- Register map and configuration
- Conversion modes (single-shot and continuous)

---

*Note: These documents are indexed in the Embedder document search and can be queried semantically for specific topics, register details, pin configurations, API usage, and more.*
