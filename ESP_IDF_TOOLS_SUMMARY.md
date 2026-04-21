# ESP-IDF Tools Summary

## Top-Level Scripts

| Script | Purpose |
|--------|---------|
| `install.sh/.bat/.fish/.ps1` | Install ESP-IDF tools, compilers, and Python environment |
| `export.sh/.bat/.fish/.ps1` | Activate ESP-IDF development environment (must be sourced) |
| `add_path.sh` | Append esptool, espcoredump, partition_table, and tools directory to PATH |
| `CMakeLists.txt` | Root CMake configuration: compiler flags, component build system, bootloader builds |
| `Kconfig` | Root menuconfig configuration: SoC capabilities, compiler options, toolchain selection |

---

## Core Build & Development Tools

### `tools/idf.py`
Top-level CLI for ESP-IDF projects. Wraps CMake and provides subcommands: `build`, `flash`, `monitor`, `menuconfig`, `clean`, and more. Loads extensions from `idf_py_actions/`.

### `tools/idf_tools.py`
Tool installation and environment manager. Downloads/installs compilers, debuggers, esptool. Creates Python virtual environments. Handles version management and exports environment variables.

### `tools/activate.py`
Python virtual environment activation wrapper. Validates Python version and launches `activate_venv.py`.

---

## idf.py Extensions (`tools/idf_py_actions/`)

| Module | Description |
|--------|-------------|
| `core_ext.py` | Core build commands: build, clean, fullclean, reconfigure |
| `serial_ext.py` | Serial port operations: flash, monitor, erase_flash |
| `debug_ext.py` | Debugging: GDB and OpenOCD integration |
| `create_ext.py` | Project creation and templates |
| `dfu_ext.py` | DFU (Device Firmware Update) support |
| `uf2_ext.py` | UF2 format support |
| `qemu_ext.py` | QEMU emulation support |
| `diag_ext.py` | Diagnostic tools |
| `mcp_ext.py` | MCP (Model Context Protocol) support |
| `tools.py` | Utility functions and helpers |

---

## CMake Build System (`tools/cmake/`)

| File | Description |
|------|-------------|
| `build.cmake` | Main build logic |
| `project.cmake` | Project-level configuration |
| `component.cmake` | Component build configuration |
| `kconfig.cmake` | Kconfig integration |
| `ldgen.cmake` | Linker script generation |
| `toolchain.cmake` | Toolchain configuration |
| `utilities.cmake` | Helper functions |
| `toolchain-*.cmake` | Target-specific toolchains (esp32, esp32s3, esp32c3, esp32c6, etc.) |
| `flash_targets.cmake` | Flash operation targets |
| `gdbinit.cmake` | GDB initialization |
| `dfu.cmake` / `uf2.cmake` | DFU and UF2 build support |

---

## Linker Script Generator (`tools/ldgen/`)

Converts linker fragment files into final linker scripts. Modules include entity definitions, fragment parsing, output command generation, and sdkconfig evaluation.

---

## Environment Export Utilities (`tools/export_utils/`)

| File | Description |
|------|-------------|
| `activate_venv.py` | Virtual environment activation |
| `shell_types.py` | Shell detection and compatibility |
| `console_output.py` | Output formatting |
| `utils.py` | General utilities |

---

## Standalone Python Tools

| Tool | Description |
|------|-------------|
| `bsasm.py` | BitScrambler assembler for ESP32-P4 ULP coprocessor |
| `mkdfu.py` | Creates DFU archives in CPIO format |
| `mkuf2.py` | Converts firmware binaries to UF2 format for USB flashing |
| `gen_esp_err_to_name.py` | Generates error code-to-name lookup tables from headers |
| `idf_size.py` | Wrapper for binary size and memory usage analysis |
| `idf_monitor.py` | Wrapper for serial port monitoring and log decoding |
| `gdb_panic_server.py` | Decodes panic/crash information from devices |
| `check_python_dependencies.py` | Validates Python package dependencies |
| `install_util.py` | Parses install script arguments (targets, features) |
| `split_paths_by_spaces.py` | Converts space-separated paths to CMake semicolon-separated lists |
| `python_version_checker.py` | Validates Python version compatibility |
| `check_term.py` | Detects terminal capabilities (color support, etc.) |
| `format.sh` | Runs code formatters on source |
| `detect_python.sh/.fish` | Finds a compatible Python installation |
| `set-submodules-to-github.sh` | Switches git submodule URLs to GitHub |

---

## SoC Capabilities Generator (`tools/gen_soc_caps_kconfig/`)

Converts `soc_caps.h` header defines into Kconfig variables automatically.

---

## Kconfig Configuration System (`tools/kconfig_new/`)

| File | Description |
|------|-------------|
| `confgen.py` | Configuration generator |
| `confserver.py` | Configuration server (for menuconfig) |
| `prepare_kconfig_files.py` | Prepares Kconfig input files |

---

## Mass Manufacturing Tool (`tools/mass_mfg/`)

`mfg_gen.py` generates manufacturing data for bulk device provisioning. Includes sample configurations and documentation.

---

## Application Tracing Tools (`tools/esp_app_trace/`)

| Tool | Description |
|------|-------------|
| `gcov_capture.py` | Code coverage capture |
| `logtrace_proc.py` | Log trace processing |
| `sysviewtrace_proc.py` | SystemView trace processing |
| `espytrace/` | Python tracing utility library |

---

## Bluetooth Tools

### BLE Utilities (`tools/ble/`)
- `lib_ble_client.py` — BLE client library
- `lib_gatt.py` — GATT protocol implementation
- `lib_gap.py` — GAP (Generic Access Profile) implementation

### BT Utilities (`tools/bt/`)
- `ble_log_console/` — BLE logging console
- `bt_hci_to_btsnoop/` — HCI to Btsnoop format converter
- `safe_unity/` — Unity test framework integration

---

## Testing Infrastructure

### Component Mocks (`tools/mocks/`)
Mock implementations for Linux-based host testing. Covers: bootloader_support, driver, esp_event, esp_netif, esp_partition, esp_timer, esp_wifi, freertos, http_parser, lwip, spi_flash, tcp_transport, and more.

### Test Suites
| Directory | Description |
|-----------|-------------|
| `tools/test_apps/` | Comprehensive test applications (build system, components, protocols, security, storage, system) |
| `tools/test_bsasm/` | BitScrambler assembler tests |
| `tools/test_build_system/` | CMake build system tests |
| `tools/test_idf_diag/` | Diagnostic tool tests |
| `tools/test_idf_py/` | idf.py CLI tests |
| `tools/test_idf_size/` | Binary size analysis tests |
| `tools/test_idf_tools/` | Tool installation tests |
| `tools/test_mkdfu/` | DFU generation tests |

---

## CI/CD Infrastructure (`tools/ci/`)

Validation scripts (`check_*.py`), local CI environment setup, pytest integration, dynamic pipeline generation, metrics collection, and SonarQube rules.

---

## Docker Support (`tools/docker/`)

Dockerfile and entrypoint for containerized ESP-IDF development environments.

---

## Project Templates (`tools/templates/`)

- `sample_project/` — Template for new ESP-IDF projects
- `sample_component/` — Template for new components

---

## Configuration Files

| File | Description |
|------|-------------|
| `tools.json` | Metadata for all downloadable tools (GDB, compilers, esptool, etc.) |
| `tools_schema.json` | JSON schema for tools.json validation |
| `requirements.json` | Python package requirements definition |
| `requirements_schema.json` | JSON schema for requirements.json |
| `requirements/*.txt` | Python dependencies (core, CI, docs, IDE, MCP, test-specific) |

---

## Examples Directory

| Category | Description | Example Count |
|----------|-------------|---------------|
| `get-started/` | Hello world, blink | 2+ |
| `peripherals/` | ADC, DAC, GPIO, I2C, I2S, SPI, UART, USB, LEDC, timers, touch, TWAI, RMT, MCPWM, PCNT, camera, LCD, DMA, JPEG, and more | 30+ |
| `protocols/` | HTTP/HTTPS, MQTT, DNS, SNTP, sockets, ICMP, SMTP, TLS | 20+ |
| `wifi/` | Advanced WiFi features | Multiple |
| `bluetooth/` | Bluedroid, NimBLE, BLE Mesh, HCI, HID, BluFi | Multiple |
| `ethernet/` | Ethernet connectivity | Multiple |
| `mesh/` | WiFi Mesh networking | Multiple |
| `openthread/` | Thread protocol | Multiple |
| `ieee802154/` | Low-power wireless (802.15.4) | Multiple |
| `zigbee/` | Zigbee IoT protocol | Multiple |
| `storage/` | NVS, SPIFFS, LittleFS, FAT, SD card, eMMC, wear levelling | 13+ |
| `security/` | Flash encryption, NVS encryption, key management, TEE | 6+ |
| `system/` | OTA, deep/light sleep, FreeRTOS, events, timers, console, GDB, tracing, ULP, watchdog, and more | 30+ |
| `cxx/` | C++ language features and experimental components | Multiple |
| `build_system/` | CMake and build configuration | Multiple |
| `custom_bootloader/` | Bootloader customization | Multiple |

---

## Supported Targets

ESP32, ESP32-S2, ESP32-S3, ESP32-C2, ESP32-C3, ESP32-C5, ESP32-C6, ESP32-H2, ESP32-H4, ESP32-P4

## Supported Toolchains

GCC and Clang for both Xtensa and RISC-V architectures.
