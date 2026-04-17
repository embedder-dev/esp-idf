/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file curve_fitting_coefficients.c
 * @brief ESP32-C6 ADC calibration curve-fitting coefficients.
 *
 * This file provides the chip-specific polynomial coefficients used by the
 * ADC curve-fitting calibration scheme to correct raw ADC readings on the
 * ESP32-C6. The calibration compensates for non-linearity in the ADC
 * transfer function by applying a second-step error correction polynomial.
 *
 * The error correction formula per attenuation level is:
 *     error = (K0 * X^0) + (K1 * X^1) + (K2 * X^2)
 *
 * where X is the raw ADC reading and K0, K1, K2 are the polynomial
 * coefficients stored in the tables below (each paired with a sign from a
 * separate sign table). Coefficients are stored as absolute values with
 * their signs held separately to avoid issues with unsigned storage.
 *
 * The ESP32-C6 supports two eFuse calibration versions, so there are two
 * full sets of coefficients (one per version). The appropriate set is
 * selected at runtime based on the calibration version burned into eFuse.
 */

#include <stdio.h>
#include <stdint.h>
#include "esp_efuse_rtc_calib.h"
#include "../curve_fitting_coefficients.h"

/**
 * @brief Number of supported eFuse calibration scheme versions for the ESP32-C6.
 *
 * Version 1 provides coefficients for all four attenuation levels.
 * Version 2 only provides coefficients for attenuation levels 2 and 3;
 * levels 0 and 1 are zeroed out (unused).
 */
#define COEFF_VERSION_NUM  2 // Currently C6 has two versions of curve calibration schemes

/**
 * @brief Number of attenuation groups (atten0 through atten3).
 *
 * Each ADC attenuation setting (0 dB, 2.5 dB, 6 dB, 11 dB) has its own
 * set of polynomial coefficients because the ADC non-linearity differs
 * at each attenuation level.
 */
#define COEFF_GROUP_NUM    4

/**
 * @brief Maximum number of polynomial terms (K0, K1, K2) in the error
 * correction formula.
 *
 * The polynomial is second-order, so there are 3 terms:
 *   term 0 -> constant (X^0)
 *   term 1 -> linear   (X^1)
 *   term 2 -> quadratic (X^2)
 */
#define TERM_MAX           3

/**
 * @note Error Calculation
 * Coefficients for calculating the reading voltage error.
 * Four sets of coefficients for atten0 ~ atten3 respectively.
 *
 * For each item, first element is the Coefficient, second element is the Multiple. (Coefficient / Multiple) is the real coefficient.
 *
 * @note {0,0} stands for unused item
 * @note In case of the overflow, these coefficients are recorded as Absolute Value
 * @note For atten0 ~ 3, error = (K0 * X^0) + (K1 * X^1) + (K2 * X^2)
 * @note Above formula is rewritten from the original documentation, please note that the coefficients are re-ordered.
 *
 * Storage format for each term: {numerator, denominator}
 *   - The real coefficient value is (numerator / denominator).
 *   - Large integer numerators and 1e15/1e16 denominators are used to
 *     preserve precision without floating-point constants in the table.
 *   - {0, 0} indicates the term is not used for that attenuation/version.
 *
 * Array dimensions:
 *   [COEFF_VERSION_NUM] - calibration version (index = version - 1)
 *   [COEFF_GROUP_NUM]   - attenuation level (0 = 0 dB, 1 = 2.5 dB, 2 = 6 dB, 3 = 11 dB)
 *   [TERM_MAX]          - polynomial term index (0 = K0/constant, 1 = K1/linear, 2 = K2/quadratic)
 *   [2]                 - {numerator, denominator} pair
 */
const static uint64_t adc1_error_coef_atten[COEFF_VERSION_NUM][COEFF_GROUP_NUM][TERM_MAX][2] = {
    /* Coefficients of calibration version 1 (all four attenuation levels populated) */
    {
        {{487166399931449,   1e15}, {6436483033201,   1e16}, {30410131806, 1e16}},   //atten0 (0 dB)
        {{8665498165817785,  1e16}, {15239070452946,  1e16}, {13818878844, 1e16}},   //atten1 (2.5 dB)
        {{12277821756674387, 1e16}, {22275554717885,  1e16}, {5924302667,  1e16}},   //atten2 (6 dB)
        {{3801417550380255,  1e16}, {6020352420772,   1e16}, {12442478488, 1e16}},   //atten3 (11 dB)
    },
    /* Coefficients of calibration version 2 (only atten2 and atten3 are used) */
    {
        {{0, 0}, {0, 0}, {0, 0}},                                                    //atten0 (0 dB)   - unused in v2
        {{0, 0}, {0, 0}, {0, 0}},                                                    //atten1 (2.5 dB) - unused in v2
        {{12217864764388775, 1e16}, {1954123107752,   1e16}, {6409679727,  1e16}},   //atten2 (6 dB)
        {{3915910437042445, 1e16}, {31536470857564,  1e16}, {12493873014, 1e16}},    //atten3 (11 dB)
    },
};

/**
 * @brief Sign multipliers for each polynomial term in the error correction.
 *
 * Because the coefficient magnitudes in @c adc1_error_coef_atten are stored
 * as absolute (unsigned) values, a separate sign table is needed to indicate
 * whether each term should be added (+1) or subtracted (-1).
 *
 * A sign of 0 means the term is unused (corresponding coefficient is {0,0}).
 *
 * Array dimensions mirror @c adc1_error_coef_atten:
 *   [COEFF_VERSION_NUM] - calibration version
 *   [COEFF_GROUP_NUM]   - attenuation level
 *   [TERM_MAX]          - polynomial term index (K0, K1, K2)
 */
const static int32_t adc1_error_sign[COEFF_VERSION_NUM][COEFF_GROUP_NUM][TERM_MAX] = {
    /* Coefficient sign of calibration version 1 */
    {
        {-1,  1,  1}, //atten0 (0 dB):   error = -K0 + K1*X + K2*X^2
        {-1,  1,  1}, //atten1 (2.5 dB): error = -K0 + K1*X + K2*X^2
        {-1,  1,  1}, //atten2 (6 dB):   error = -K0 + K1*X + K2*X^2
        {-1, -1,  1}, //atten3 (11 dB):  error = -K0 - K1*X + K2*X^2
    },
    /* Coefficient sign of calibration version 2 */
    {
        { 0,  0,  0}, //atten0 (0 dB)   - unused in v2
        { 0,  0,  0}, //atten1 (2.5 dB) - unused in v2
        {-1, -1,  1}, //atten2 (6 dB):   error = -K0 - K1*X + K2*X^2
        {-1, -1,  1}, //atten3 (11 dB):  error = -K0 - K1*X + K2*X^2
    },
};

/**
 * @brief Populate the second-step calibration context with the appropriate
 *        curve-fitting coefficients for the current chip and configuration.
 *
 * This function reads the ADC calibration version from eFuse and selects
 * the matching row of polynomial coefficients and signs for the requested
 * attenuation level. The caller uses the returned context to apply the
 * second-step error correction to raw ADC readings.
 *
 * Special case for calibration version 2:
 *   Attenuation levels 0 and 1 have no version-2 coefficients. In that
 *   case the function sets @c term_num to 0 and the coefficient/sign
 *   pointers to NULL, indicating no second-step correction should be
 *   applied.
 *
 * @param[in]  config  Curve fitting calibration configuration containing the
 *                     desired attenuation level.
 * @param[out] ctx     Second-step calibration context to fill in. On return:
 *                     - @c term_num: number of polynomial terms (0 or 3).
 *                     - @c coeff:    pointer to the coefficient row in
 *                                    @c adc1_error_coef_atten, or NULL.
 *                     - @c sign:     pointer to the sign row in
 *                                    @c adc1_error_sign, or NULL.
 */
void curve_fitting_get_second_step_coeff(const adc_cali_curve_fitting_config_t *config, cali_chars_second_step_t *ctx)
{
    /* Read the ADC calibration version burned into this chip's eFuse */
    uint32_t adc_calib_ver = esp_efuse_rtc_calib_get_ver();

    /* Validate that the eFuse version is within the supported range.
     * For ESP32-C6: VER_MIN = 1 (ESP_EFUSE_ADC_CALIB_VER1),
     *               VER_MAX = 2 (ESP_EFUSE_ADC_CALIB_VER2). */
    assert((adc_calib_ver >= ESP_EFUSE_ADC_CALIB_VER_MIN) &&
           (adc_calib_ver <= ESP_EFUSE_ADC_CALIB_VER_MAX));

    if (adc_calib_ver == ESP_EFUSE_ADC_CALIB_VER2 && config->atten < 2) {
        /*
         * Calibration version 2 does not provide error correction coefficients
         * for attenuation levels 0 (0 dB) and 1 (2.5 dB). Set term_num to 0
         * so the caller knows to skip the second-step correction entirely.
         */
        ctx->term_num = 0;
        ctx->coeff = NULL;
        ctx->sign = NULL;
    } else {
        /*
         * For all other valid combinations, load the 3-term polynomial
         * coefficients and their signs for the requested attenuation level.
         *
         * VER2IDX() converts the 1-based eFuse version number to a 0-based
         * array index (i.e., version - 1).
         */
        ctx->term_num = 3;
        ctx->coeff = adc1_error_coef_atten[VER2IDX(adc_calib_ver)][config->atten];
        ctx->sign = adc1_error_sign[VER2IDX(adc_calib_ver)][config->atten];
    }
}
