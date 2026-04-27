# EMBEDDER.md

## Project Overview

- **Project**: ESP-IDF (Espressif IoT Development Framework)
- **Board**: Arduino Nano ESP32
- **MCU**: ESP32-S3
- **Framework**: ESP-IDF (CMake-based build system)
- **Language**: C / C++ / Assembly

## About Embedder

Embedder is an AI-powered firmware and embedded software engineering agent. It assists with reading, writing, building, flashing, and debugging embedded projects directly from the IDE. It has access to project files, serial monitors, hardware documentation, and web resources to help develop, troubleshoot, and optimize firmware.

## Build

```bash
idf.py set-target esp32s3
idf.py build
```

## Flash

```bash
idf.py -p /dev/ttyUSB0 flash
```

## Monitor

```bash
idf.py -p /dev/ttyUSB0 monitor
```

## Debug

Use OpenOCD + GDB via the built-in JTAG interface on the ESP32-S3 (USB).

## Code Style

- Follow the [ESP-IDF contribution guide](CONTRIBUTING.md).
- Use `esp_err_t` return codes and ESP-IDF logging macros (`ESP_LOGI`, `ESP_LOGW`, `ESP_LOGE`).
- Prefix public API functions with the component name (e.g., `esp_wifi_`, `gpio_`).
- Use Kconfig for compile-time configuration options.
