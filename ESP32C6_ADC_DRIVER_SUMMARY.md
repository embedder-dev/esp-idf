# ESP32-C6 ADC Driver Summary

## Hardware Overview

The ESP32-C6 has **1 ADC unit** (ADC1) with **7 channels** (CH0-CH6) mapped to **GPIO 0-6**. Resolution is fixed at **12 bits** (0-4095). Sampling rate in continuous mode ranges from 611 Hz to 83.3 kHz. It supports DMA-based continuous conversion, IIR digital filtering, and hardware monitoring.

## Architecture

The driver is structured in three layers within the `esp_adc` component:

- **SOC layer** (`soc/`) -- chip-specific capabilities, channel-to-GPIO mapping
- **HAL layer** (`hal/`) -- register-level abstraction
- **Driver layer** (`esp_adc/`) -- user-facing API with two operating modes

## Oneshot Mode

Single on-demand conversions. Thread-safe.

```c
// 1. Init unit
adc_oneshot_unit_init_cfg_t cfg = { .unit_id = ADC_UNIT_1 };
adc_oneshot_unit_handle_t handle;
adc_oneshot_new_unit(&cfg, &handle);

// 2. Configure channel (attenuation + bitwidth)
adc_oneshot_chan_cfg_t chan_cfg = {
    .atten = ADC_ATTEN_DB_12,       // ~0-3100 mV range
    .bitwidth = ADC_BITWIDTH_12,
};
adc_oneshot_config_channel(handle, ADC_CHANNEL_0, &chan_cfg);

// 3. Read
int raw;
adc_oneshot_read(handle, ADC_CHANNEL_0, &raw);

// 4. Cleanup
adc_oneshot_del_unit(handle);
```

## Continuous Mode

DMA-driven sampling at a configured rate. Data arrives in **conversion frames** (configurable size in bytes), each containing multiple 4-byte results with unit, channel, and raw value.

```c
// 1. Create handle (set buffer sizes)
adc_continuous_handle_cfg_t hdl_cfg = {
    .max_store_buf_size = 1024,
    .conv_frame_size = 256,
};
adc_continuous_handle_t handle;
adc_continuous_new_handle(&hdl_cfg, &handle);

// 2. Configure channels and sample rate
adc_digi_pattern_config_t pattern = {
    .atten = ADC_ATTEN_DB_12,
    .channel = ADC_CHANNEL_0,
    .unit = ADC_UNIT_1,
    .bit_width = ADC_BITWIDTH_12,
};
adc_continuous_config_t cfg = {
    .pattern_num = 1,
    .adc_pattern = &pattern,
    .sample_freq_hz = 20000,
    .conv_mode = ADC_CONV_SINGLE_UNIT_1,
};
adc_continuous_config(handle, &cfg);

// 3. Register callbacks (on_conv_done, on_pool_ovf) -- ISR context
// 4. Start, read, stop
adc_continuous_start(handle);
adc_continuous_read(handle, buf, sizeof(buf), &out_len, timeout_ms);
adc_continuous_stop(handle);
adc_continuous_deinit(handle);
```

## Attenuation Settings

| Setting          | Approx. Measurable Range |
|------------------|--------------------------|
| `ADC_ATTEN_DB_0`   | 0 ~ 750 mV             |
| `ADC_ATTEN_DB_2_5` | 0 ~ 1050 mV            |
| `ADC_ATTEN_DB_6`   | 0 ~ 1300 mV            |
| `ADC_ATTEN_DB_12`  | 0 ~ 3100 mV            |

## Calibration

The ESP32-C6 supports the **curve fitting** calibration scheme. It converts raw ADC readings to millivolt values using factory-burned eFuse calibration data.

```c
adc_cali_curve_fitting_config_t cali_cfg = {
    .unit_id = ADC_UNIT_1,
    .atten = ADC_ATTEN_DB_12,
    .bitwidth = ADC_BITWIDTH_12,
};
adc_cali_handle_t cali_handle;
adc_cali_create_scheme_curve_fitting(&cali_cfg, &cali_handle);

// Convert raw -> mV
int voltage_mv;
adc_cali_raw_to_voltage(cali_handle, raw, &voltage_mv);

// Or use the convenience function (oneshot mode):
adc_oneshot_get_calibrated_result(handle, cali_handle, ADC_CHANNEL_0, &voltage_mv);
```

## Additional Features (ESP32-C6)

- **IIR digital filter** -- 2 hardware filters for noise reduction in continuous mode
- **Hardware monitor** -- 2 monitors that can trigger alerts on threshold crossings
- **Shared power domain** -- ADC power is shared with the temperature sensor
