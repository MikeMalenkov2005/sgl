#ifndef SGL_BUTTONS_H
#define SGL_BUTTONS_H

#define SGLB_NONE                   0

#define SGLB_MOUSE_1                1
#define SGLB_MOUSE_2                2
#define SGLB_MOUSE_3                3
#define SGLB_MOUSE_4                4
#define SGLB_MOUSE_5                5
#define SGLB_MOUSE_6                6
#define SGLB_MOUSE_7                7
#define SGLB_MOUSE_8                8

#define SGLB_MOUSE_LEFT             SGLB_MOUSE_1
#define SGLB_MOUSE_RIGHT            SGLB_MOUSE_2
#define SGLB_MOUSE_MIDDLE           SGLB_MOUSE_3

#define SGLB_MOUSE_LAST             SGLB_MOUSE_8

#define SGLB_KEY_SPACE              32
#define SGLB_KEY_APOSTROPHE         39  /* ' */
#define SGLB_KEY_COMMA              44  /* , */
#define SGLB_KEY_MINUS              45  /* - */
#define SGLB_KEY_PERIOD             46  /* . */
#define SGLB_KEY_SLASH              47  /* / */
#define SGLB_KEY_0                  48
#define SGLB_KEY_1                  49
#define SGLB_KEY_2                  50
#define SGLB_KEY_3                  51
#define SGLB_KEY_4                  52
#define SGLB_KEY_5                  53
#define SGLB_KEY_6                  54
#define SGLB_KEY_7                  55
#define SGLB_KEY_8                  56
#define SGLB_KEY_9                  57
#define SGLB_KEY_SEMICOLON          59  /* ; */
#define SGLB_KEY_EQUAL              61  /* = */
#define SGLB_KEY_A                  65
#define SGLB_KEY_B                  66
#define SGLB_KEY_C                  67
#define SGLB_KEY_D                  68
#define SGLB_KEY_E                  69
#define SGLB_KEY_F                  70
#define SGLB_KEY_G                  71
#define SGLB_KEY_H                  72
#define SGLB_KEY_I                  73
#define SGLB_KEY_J                  74
#define SGLB_KEY_K                  75
#define SGLB_KEY_L                  76
#define SGLB_KEY_M                  77
#define SGLB_KEY_N                  78
#define SGLB_KEY_O                  79
#define SGLB_KEY_P                  80
#define SGLB_KEY_Q                  81
#define SGLB_KEY_R                  82
#define SGLB_KEY_S                  83
#define SGLB_KEY_T                  84
#define SGLB_KEY_U                  85
#define SGLB_KEY_V                  86
#define SGLB_KEY_W                  87
#define SGLB_KEY_X                  88
#define SGLB_KEY_Y                  89
#define SGLB_KEY_Z                  90
#define SGLB_KEY_LEFT_BRACKET       91  /* [ */
#define SGLB_KEY_BACKSLASH          92  /* \ */
#define SGLB_KEY_RIGHT_BRACKET      93  /* ] */
#define SGLB_KEY_GRAVE_ACCENT       96  /* ` */
#define SGLB_KEY_WORLD_1            161 /* non-US #1 */
#define SGLB_KEY_WORLD_2            162 /* non-US #2 */

#define SGLB_KEY_ESCAPE             256
#define SGLB_KEY_ENTER              257
#define SGLB_KEY_TAB                258
#define SGLB_KEY_BACKSPACE          259
#define SGLB_KEY_INSERT             260
#define SGLB_KEY_DELETE             261
#define SGLB_KEY_RIGHT              262
#define SGLB_KEY_LEFT               263
#define SGLB_KEY_DOWN               264
#define SGLB_KEY_UP                 265
#define SGLB_KEY_PAGE_UP            266
#define SGLB_KEY_PAGE_DOWN          267
#define SGLB_KEY_HOME               268
#define SGLB_KEY_END                269
#define SGLB_KEY_CAPS_LOCK          280
#define SGLB_KEY_SCROLL_LOCK        281
#define SGLB_KEY_NUM_LOCK           282
#define SGLB_KEY_PRINT_SCREEN       283
#define SGLB_KEY_PAUSE              284
#define SGLB_KEY_F1                 290
#define SGLB_KEY_F2                 291
#define SGLB_KEY_F3                 292
#define SGLB_KEY_F4                 293
#define SGLB_KEY_F5                 294
#define SGLB_KEY_F6                 295
#define SGLB_KEY_F7                 296
#define SGLB_KEY_F8                 297
#define SGLB_KEY_F9                 298
#define SGLB_KEY_F10                299
#define SGLB_KEY_F11                300
#define SGLB_KEY_F12                301
#define SGLB_KEY_F13                302
#define SGLB_KEY_F14                303
#define SGLB_KEY_F15                304
#define SGLB_KEY_F16                305
#define SGLB_KEY_F17                306
#define SGLB_KEY_F18                307
#define SGLB_KEY_F19                308
#define SGLB_KEY_F20                309
#define SGLB_KEY_F21                310
#define SGLB_KEY_F22                311
#define SGLB_KEY_F23                312
#define SGLB_KEY_F24                313
#define SGLB_KEY_F25                314
#define SGLB_KEY_KP_0               320
#define SGLB_KEY_KP_1               321
#define SGLB_KEY_KP_2               322
#define SGLB_KEY_KP_3               323
#define SGLB_KEY_KP_4               324
#define SGLB_KEY_KP_5               325
#define SGLB_KEY_KP_6               326
#define SGLB_KEY_KP_7               327
#define SGLB_KEY_KP_8               328
#define SGLB_KEY_KP_9               329
#define SGLB_KEY_KP_DECIMAL         330
#define SGLB_KEY_KP_DIVIDE          331
#define SGLB_KEY_KP_MULTIPLY        332
#define SGLB_KEY_KP_SUBTRACT        333
#define SGLB_KEY_KP_ADD             334
#define SGLB_KEY_KP_ENTER           335
#define SGLB_KEY_KP_EQUAL           336
#define SGLB_KEY_LEFT_SHIFT         340
#define SGLB_KEY_LEFT_CONTROL       341
#define SGLB_KEY_LEFT_ALT           342
#define SGLB_KEY_LEFT_SUPER         343
#define SGLB_KEY_RIGHT_SHIFT        344
#define SGLB_KEY_RIGHT_CONTROL      345
#define SGLB_KEY_RIGHT_ALT          346
#define SGLB_KEY_RIGHT_SUPER        347
#define SGLB_KEY_MENU               348

#define SGLB_KEY_LAST               SGLB_KEY_MENU

#define SGLB_MOD_SHIFT              0x0001
#define SGLB_MOD_CONTROL            0x0002
#define SGLB_MOD_ALT                0x0004
#define SGLB_MOD_SUPER              0x0008
#define SGLB_MOD_CAPS_LOCK          0x0010
#define SGLB_MOD_NUM_LOCK           0x0020

#define SGLB_RELEASE                0
#define SGLB_PRESS                  1
#define SGLB_REPEAT                 2

#endif

