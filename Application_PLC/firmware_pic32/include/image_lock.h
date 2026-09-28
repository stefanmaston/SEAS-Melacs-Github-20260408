#ifndef IMAGE_LOCK_H
#define IMAGE_LOCK_H

#if defined(__PIC32MX__)
#define image_lock() ((void)0)
#define image_unlock() ((void)0)
#else
void image_lock(void);
void image_unlock(void);
#endif

#endif
