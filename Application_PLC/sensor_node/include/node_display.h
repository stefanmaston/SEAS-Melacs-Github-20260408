#ifndef NODE_DISPLAY_H
#define NODE_DISPLAY_H

#include <stdint.h>

#define NODE_FB_W 128
#define NODE_FB_H 64
#define NODE_FB_SIZE (NODE_FB_W * NODE_FB_H / 8)

/* Namnet ritas en gång. Bara sifferfältet ritas om när värdet ändras. */
#define NODE_POINT_NAME "MATPUNKT"

void display_begin(uint8_t *fb);
void display_set_c10(uint8_t *fb, int16_t c10);
int display_dirty(void);
void display_clear_dirty(void);

#endif
