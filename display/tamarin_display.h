#ifndef TAMARIN_DISPLAY_H
#define TAMARIN_DISPLAY_H

#include "ssd1306.h"

extern ssd1306_t display;

void tamarin_display_init(void);
void tamarin_display_clear(void);
void tamarin_display_status(const char* title, const char* line1, const char* line2, const char* line3);
void tamarin_display_simple_status(const char* status);

#endif // TAMARIN_DISPLAY_H