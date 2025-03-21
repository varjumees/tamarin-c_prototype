#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "tamarin_hw.h"

// Global display object
ssd1306_t display;

void tamarin_display_init() {
    // Initialize I2C for the display
    // Using I2C1 on GP26 (SDA) and GP27 (SCL)
    i2c_init(i2c1, 400000);
    gpio_set_function(26, GPIO_FUNC_I2C);
    gpio_set_function(27, GPIO_FUNC_I2C);
    gpio_pull_up(26);
    gpio_pull_up(27);
    
    // Initialize the display (128x32 resolution)
    display.external_vcc = false;
    ssd1306_init(&display, 128, 32, 0x3C, i2c1);
    ssd1306_clear(&display);
    ssd1306_show(&display);
}

void tamarin_display_status(const char* title, const char* line1, const char* line2, const char* line3) {
    ssd1306_clear(&display);
    
    // Title on first line
    ssd1306_draw_string(&display, 0, 0, 1, title);
    
    // Additional lines (if provided)
    if (line1) ssd1306_draw_string(&display, 0, 8, 1, line1);
    if (line2) ssd1306_draw_string(&display, 0, 16, 1, line2);
    if (line3) ssd1306_draw_string(&display, 0, 24, 1, line3);
    
    ssd1306_show(&display);
}

// Simplified version for single line status
void tamarin_display_simple_status(const char* status) {
    tamarin_display_status(status, NULL, NULL, NULL);
}