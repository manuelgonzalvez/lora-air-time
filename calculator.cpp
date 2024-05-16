#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <algorithm>
#include <cmath>

double calculateAirTime(int payload_len, int preamble_len, int spreading_factor, int bandwidth, int coding_rate, bool crc, bool explicit_header, bool low_data_rate_opt) {
    // Calculate symbol time
    double symbol_time = pow(2, spreading_factor) / bandwidth;

    // Calculate preamble time
    double n_preamble = preamble_len + 4.25;
    double t_preamble = n_preamble * symbol_time;

    // Calculate payload symbols
    double payload_bit = 8 * payload_len;
    payload_bit -= 4 * spreading_factor;
    payload_bit += 8;
    payload_bit += crc ? 16 : 0;
    payload_bit += explicit_header ? 20 : 0;
    payload_bit = std::max(payload_bit, 0.0);
    double bits_per_symbol = low_data_rate_opt ? (spreading_factor - 2) : spreading_factor;
    double payload_symbol = ceil(payload_bit / 4 / bits_per_symbol) * coding_rate;
    payload_symbol += 8;

    // Calculate payload time
    double t_payload = payload_symbol * symbol_time;

    // Calculate total air-time
    double t_total = t_preamble + t_payload;

    return t_total;
}

int main(void)
{
    printf("OUTPUT \n");
    float result = calculateAirTime(16,8,7,125.0,8,true,false,false);
    printf("%.3f\n", result);
    printf("return");
    return result;
}