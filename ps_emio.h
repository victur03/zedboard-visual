#ifndef __PS_EMIO_H__
#define __PS_EMIO_H__

#define EMIO_PIN_OLED_RES  54
#define EMIO_PIN_OLED_DC   55

int init_ps_emio();

void cleanup_ps_emio();

void oled_printstr(char *str);

#endif
