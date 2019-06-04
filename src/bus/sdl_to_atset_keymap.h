#pragma once

// Attempt to map the USB-ish SDL scancodes to the PC/AT set.
struct Keybinding {
  const char* label;
  uint32_t scancode;
  uint8_t at_set1_code;
  uint8_t at_set2_code;
  uint8_t at_set3_code;
  bool extended;
};

constexpr Keybinding kNoKey{"NONE", 0, 0, 0, 0, false};

constexpr Keybinding keymap[] = {
    {"KEY_ESC", 41, 0x01, 0x76, 0x08, false},
    {"KEY_1", 30, 0x02, 0x16, 0x16, false},
    {"KEY_2", 31, 0x03, 0x1e, 0x1e, false},
    {"KEY_3", 32, 0x04, 0x26, 0x26, false},
    {"KEY_4", 33, 0x05, 0x25, 0x25, false},
    {"KEY_5", 34, 0x06, 0x2e, 0x2e, false},
    {"KEY_6", 35, 0x07, 0x36, 0x36, false},
    {"KEY_7", 36, 0x08, 0x3d, 0x3d, false},
    {"KEY_8", 37, 0x09, 0x3e, 0x3e, false},
    {"KEY_9", 38, 0x0a, 0x46, 0x46, false},
    {"KEY_0", 39, 0x0b, 0x45, 0x45, false},
    {"KEY_MINUS", 45, 0x0c, 0x4e, 0x4e, false},
    {"KEY_EQUAL", 46, 0x0d, 0x55, 0x55, false},
    {"KEY_BACKSPACE", 42, 0x0e, 0x66, 0x66, false},
    {"KEY_TAB", 43, 0x0f, 0x0d, 0x0d, false},
    {"KEY_Q", 20, 0x10, 0x15, 0x15, false},
    {"KEY_W", 26, 0x11, 0x1d, 0x1d, false},
    {"KEY_E", 8, 0x12, 0x24, 0x24, false},
    {"KEY_R", 21, 0x13, 0x2d, 0x2d, false},
    {"KEY_T", 23, 0x14, 0x2c, 0x2c, false},
    {"KEY_Y", 28, 0x15, 0x35, 0x35, false},
    {"KEY_U", 24, 0x16, 0x3c, 0x3c, false},
    {"KEY_I", 12, 0x17, 0x43, 0x43, false},
    {"KEY_O", 18, 0x18, 0x44, 0x44, false},
    {"KEY_P", 19, 0x19, 0x4d, 0x4d, false},
    {"KEY_LEFTBRACE", 47, 0x1a, 0x54, 0x54, false},
    {"KEY_RIGHTBRACE", 48, 0x1b, 0x5b, 0x5b, false},
    {"KEY_ENTER", 40, 0x1c, 0x5a, 0x5a, false},
    {"KEY_LEFTCTRL", 228, 0x1d, 0x14, 0x11, true},
    {"KEY_RIGHTCTRL", 224, 0x1d, 0x14, 0x11, true},
    {"KEY_A", 4, 0x1e, 0x1c, 0x1c, false},
    {"KEY_S", 22, 0x1f, 0x1b, 0x1b, false},
    {"KEY_D", 7, 0x20, 0x23, 0x23, false},
    {"KEY_F", 9, 0x21, 0x2b, 0x2b, false},
    {"KEY_G", 10, 0x22, 0x34, 0x34, false},
    {"KEY_H", 11, 0x23, 0x33, 0x33, false},
    {"KEY_J", 13, 0x24, 0x3b, 0x3b, false},
    {"KEY_K", 14, 0x25, 0x42, 0x42, false},
    {"KEY_L", 15, 0x26, 0x4b, 0x4b, false},
    {"KEY_SEMICOLON", 51, 0x27, 0x4c, 0x4c, false},
    {"KEY_APOSTROPHE", 52, 0x28, 0x52, 0x52, false},
    {"KEY_GRAVE", 53, 0x29, 0x0e, 0x0e, false},
    {"KEY_SHIFT", 225, 0x2a, 0x12, 0x12, true},
    {"KEY_LEFTSHIFT", 225, 0x2a, 0x12, 0x12, false},
    {"KEY_RIGHTSHIFT", 229, 0x36, 0x59, 0x59, false},
    {"KEY_BACKSLASH", 50, 0x2b, 0x5d, 0x5c, false},
    {"KEY_Z", 29, 0x2c, 0x1a, 0x1a, false},
    {"KEY_X", 27, 0x2d, 0x22, 0x22, false},
    {"KEY_C", 6, 0x2e, 0x21, 0x21, false},
    {"KEY_V", 25, 0x2f, 0x2a, 0x2a, false},
    {"KEY_B", 5, 0x30, 0x32, 0x32, false},
    {"KEY_N", 17, 0x31, 0x31, 0x31, false},
    {"KEY_M", 16, 0x32, 0x3a, 0x3a, false},
    {"KEY_COMMA", 54, 0x33, 0x41, 0x41, false},
    {"KEY_DOT", 55, 0x34, 0x49, 0x49, false},
    {"KEY_SLASH", 56, 0x35, 0x4a, 0x4a, false},
    {"KEY_KPASTERISK", 85, 0x37, 0x7c, 0x7e, false},
    {"KEY_LEFTALT", 226, 0x38, 0x11, 0x19, false},
    {"KEY_RIGHTALT", 230, 0x38, 0x11, 0x19, true},
    {"KEY_SPACE", 44, 0x39, 0x29, 0x29, false},
    {"KEY_CAPSLOCK", 57, 0x3a, 0x58, 0x14, false},
    {"KEY_F1", 58, 0x3b, 0x05, 0x07, false},
    {"KEY_F2", 59, 0x3c, 0x06, 0x0f, false},
    {"KEY_F3", 60, 0x3d, 0x04, 0x17, false},
    {"KEY_F4", 61, 0x3e, 0x0c, 0x1f, false},
    {"KEY_F5", 62, 0x3f, 0x03, 0x27, false},
    {"KEY_F6", 63, 0x40, 0x0b, 0x2f, false},
    {"KEY_F7", 64, 0x41, 0x83, 0x37, false},
    {"KEY_F8", 65, 0x42, 0x0a, 0x3f, false},
    {"KEY_F9", 66, 0x43, 0x01, 0x47, false},
    {"KEY_F10", 67, 0x44, 0x09, 0x4f, false},
    {"KEY_NUMLOCK", 83, 0x45, 0x77, 0x76, false},
    {"KEY_SCROLLLOCK", 71, 0x46, 0x7e, 0x5f, false},
    {"KEY_KP7", 95, 0x47, 0x6c, 0x6c, false},
    {"KEY_KP8", 96, 0x48, 0x75, 0x75, false},
    {"KEY_KP9", 97, 0x49, 0x7d, 0x7d, false},
    {"KEY_KPMINUS", 86, 0x4a, 0x7b, 0x4e, false},
    {"KEY_KP4", 92, 0x4b, 0x6b, 0x6b, false},
    {"KEY_KP5", 93, 0x4c, 0x73, 0x73, false},
    {"KEY_KP6", 94, 0x4d, 0x74, 0x74, false},
    {"KEY_KPPLUS", 87, 0x4e, 0x79, 0x7c, false},
    {"KEY_KP1", 89, 0x4f, 0x69, 0x69, false},
    {"KEY_KP2", 90, 0x50, 0x72, 0x72, false},
    {"KEY_KP3", 91, 0x51, 0x7a, 0x7a, false},
    {"KEY_KP0", 98, 0x52, 0x70, 0x70, false},
    {"KEY_KPDOT", 99, 0x53, 0x71, 0x71, false},
    {"KEY_102ND", 100, 0x56, 0x61, 0x13, false},
    {"KEY_F11", 68, 0x57, 0x78, 0x56, false},
    {"KEY_F12", 69, 0x58, 0x07, 0x5e, false},
    {"KEY_SYSRQ", 70, 0x54, 0x7f, 0x57, false},
    {"KEY_F13", 104, 0x5d, 0x2f, 0x7f, false},
    {"KEY_F14", 105, 0x5e, 0x37, 0x80, false},
    {"KEY_F15", 106, 0x5f, 0x3f, 0x81, false},
    {"KEY_COMPOSE", 101, 0x5d, 0x2f, 0x8d, true},
    {"KEY_INSERT", 73, 0x52, 0x70, 0x67, true},
    {"KEY_UP", 82, 0x48, 0x75, 0x63, true},
    {"KEY_DOWN", 81, 0x50, 0x72, 0x60, true},
    {"KEY_LEFT", 80, 0x4b, 0x6b, 0x61, true},
    {"KEY_RIGHT", 79, 0x4d, 0x74, 0x6a, true},
};
