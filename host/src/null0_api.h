// this is a placeholder for null0 API functions (actual functions that do everything)

#pragma once

#include <stdbool.h>
#include <stdint.h>

// Shared types
typedef struct Dimensions {
  uint32_t width;
  uint32_t height;
} Dimensions;

typedef struct Vector {
  int32_t x;
  int32_t y;
} Vector;

typedef struct Rectangle {
  int32_t x;
  int32_t y;
  int32_t width;
  int32_t height;
} Rectangle;

// Sound parameters (96 bytes matching rFXGen WaveParams)
typedef struct SfxParams {
  // Random seed used to generate the wave
  uint32_t randSeed;

  // Wave type (square, sawtooth, sine, noise)
  int waveType;

  // Wave envelope parameters
  float attackTime;
  float sustainTime;
  float sustainPunch;
  float decayTime;

  // Frequency parameters
  float startFrequency;
  float minFrequency;
  float slide;
  float deltaSlide;
  float vibratoDepth;
  float vibratoSpeed;
  // float vibratoPhaseDelay;      // Unused in sfxr code.

  // Tone change parameters
  float changeAmount;
  float changeSpeed;

  // Square wave parameters
  float squareDuty;
  float dutySweep;

  // Repeat parameters
  float repeatSpeed;

  // Phaser parameters
  float phaserOffset;
  float phaserSweep;

  // Filter parameters
  float lpfCutoff;
  float lpfCutoffSweep;
  float lpfResonance;
  float hpfCutoff;
  float hpfCutoffSweep;
} SfxParams;

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
} Color;

typedef enum ImageFilter {
  FILTER_NEARESTNEIGHBOR = 0,
  FILTER_BILINEAR,
  FILTER_SMOOTH
} ImageFilter;

typedef enum Key {
  KEY_INVALID = 0,
  KEY_SPACE = 32,
  KEY_APOSTROPHE = 39,
  KEY_COMMA = 44,
  KEY_MINUS = 45,
  KEY_PERIOD = 46,
  KEY_SLASH = 47,
  KEY_0 = 48,
  KEY_1 = 49,
  KEY_2 = 50,
  KEY_3 = 51,
  KEY_4 = 52,
  KEY_5 = 53,
  KEY_6 = 54,
  KEY_7 = 55,
  KEY_8 = 56,
  KEY_9 = 57,
  KEY_SEMICOLON = 59,
  KEY_EQUAL = 61,
  KEY_A = 65,
  KEY_B = 66,
  KEY_C = 67,
  KEY_D = 68,
  KEY_E = 69,
  KEY_F = 70,
  KEY_G = 71,
  KEY_H = 72,
  KEY_I = 73,
  KEY_J = 74,
  KEY_K = 75,
  KEY_L = 76,
  KEY_M = 77,
  KEY_N = 78,
  KEY_O = 79,
  KEY_P = 80,
  KEY_Q = 81,
  KEY_R = 82,
  KEY_S = 83,
  KEY_T = 84,
  KEY_U = 85,
  KEY_V = 86,
  KEY_W = 87,
  KEY_X = 88,
  KEY_Y = 89,
  KEY_Z = 90,
  KEY_LEFT_BRACKET = 91,
  KEY_BACKSLASH = 92,
  KEY_RIGHT_BRACKET = 93,
  KEY_GRAVE_ACCENT = 96,
  KEY_WORLD_1 = 161,
  KEY_WORLD_2 = 162,
  KEY_ESCAPE = 256,
  KEY_ENTER = 257,
  KEY_TAB = 258,
  KEY_BACKSPACE = 259,
  KEY_INSERT = 260,
  KEY_DELETE = 261,
  KEY_RIGHT = 262,
  KEY_LEFT = 263,
  KEY_DOWN = 264,
  KEY_UP = 265,
  KEY_PAGE_UP = 266,
  KEY_PAGE_DOWN = 267,
  KEY_HOME = 268,
  KEY_END = 269,
  KEY_CAPS_LOCK = 280,
  KEY_SCROLL_LOCK = 281,
  KEY_NUM_LOCK = 282,
  KEY_PRINT_SCREEN = 283,
  KEY_PAUSE = 284,
  KEY_F1 = 290,
  KEY_F2 = 291,
  KEY_F3 = 292,
  KEY_F4 = 293,
  KEY_F5 = 294,
  KEY_F6 = 295,
  KEY_F7 = 296,
  KEY_F8 = 297,
  KEY_F9 = 298,
  KEY_F10 = 299,
  KEY_F11 = 300,
  KEY_F12 = 301,
  KEY_F13 = 302,
  KEY_F14 = 303,
  KEY_F15 = 304,
  KEY_F16 = 305,
  KEY_F17 = 306,
  KEY_F18 = 307,
  KEY_F19 = 308,
  KEY_F20 = 309,
  KEY_F21 = 310,
  KEY_F22 = 311,
  KEY_F23 = 312,
  KEY_F24 = 313,
  KEY_F25 = 314,
  KEY_KP_0 = 320,
  KEY_KP_1 = 321,
  KEY_KP_2 = 322,
  KEY_KP_3 = 323,
  KEY_KP_4 = 324,
  KEY_KP_5 = 325,
  KEY_KP_6 = 326,
  KEY_KP_7 = 327,
  KEY_KP_8 = 328,
  KEY_KP_9 = 329,
  KEY_KP_DECIMAL = 330,
  KEY_KP_DIVIDE = 331,
  KEY_KP_MULTIPLY = 332,
  KEY_KP_SUBTRACT = 333,
  KEY_KP_ADD = 334,
  KEY_KP_ENTER = 335,
  KEY_KP_EQUAL = 336,
  KEY_LEFT_SHIFT = 340,
  KEY_LEFT_CONTROL = 341,
  KEY_LEFT_ALT = 342,
  KEY_LEFT_SUPER = 343,
  KEY_RIGHT_SHIFT = 344,
  KEY_RIGHT_CONTROL = 345,
  KEY_RIGHT_ALT = 346,
  KEY_RIGHT_SUPER = 347,
  KEY_MENU = 348,
} Key;

typedef enum GamepadButton {
  GAMEPAD_BUTTON_UNKNOWN = 0,     // Unknown button, just for error checking
  GAMEPAD_BUTTON_UP = 1,          // Gamepad left DPAD up button
  GAMEPAD_BUTTON_RIGHT,           // Gamepad left DPAD right button
  GAMEPAD_BUTTON_DOWN,            // Gamepad left DPAD down button
  GAMEPAD_BUTTON_LEFT,            // Gamepad left DPAD left button
  GAMEPAD_BUTTON_Y,               // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
  GAMEPAD_BUTTON_B,               // Gamepad right button right (i.e. PS3: Square, Xbox: X)
  GAMEPAD_BUTTON_A,               // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
  GAMEPAD_BUTTON_X,               // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
  GAMEPAD_BUTTON_LEFT_SHOULDER,   // Gamepad top/back trigger left (first), it could be a trailing button
  GAMEPAD_BUTTON_LEFT_TRIGGER,    // Gamepad top/back trigger left (second), it could be a trailing button
  GAMEPAD_BUTTON_RIGHT_SHOULDER,  // Gamepad top/back trigger right (one), it could be a trailing button
  GAMEPAD_BUTTON_RIGHT_TRIGGER,   // Gamepad top/back trigger right (second), it could be a trailing button
  GAMEPAD_BUTTON_SELECT,          // Gamepad center buttons, left one (i.e. PS3: Select)
  GAMEPAD_BUTTON_MENU,            // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
  GAMEPAD_BUTTON_START,           // Gamepad center buttons, right one (i.e. PS3: Start)
  GAMEPAD_BUTTON_LEFT_THUMB,      // Gamepad joystick pressed button left
  GAMEPAD_BUTTON_RIGHT_THUMB,     // Gamepad joystick pressed button right
} GamepadButton;

typedef enum MouseButton {
  MOUSE_BUTTON_UNKNOWN = 0,
  MOUSE_BUTTON_LEFT = 1,
  MOUSE_BUTTON_RIGHT = 2,
  MOUSE_BUTTON_MIDDLE = 3,
} MouseButton;

typedef enum SfxPresetType {
  SFX_COIN,
  SFX_LASER,
  SFX_EXPLOSION,
  SFX_POWERUP,
  SFX_HURT,
  SFX_JUMP,
  SFX_SELECT,
  SFX_SYNTH
} SfxPresetType;

typedef enum SfxWaveType {
  SFX_SQUARE,
  SFX_SAWTOOTH,
  SFX_SINE,
  SFX_NOISE,
  SFX_TRIANGLE,
  SFX_PINK_NOISE
} SfxWaveType;

typedef enum FileType {
  FILETYPE_REGULAR,   /**< a normal file */
  FILETYPE_DIRECTORY, /**< a directory */
  FILETYPE_SYMLINK,   /**< a symlink */
  FILETYPE_OTHER      /**< something completely different like a device */
} FileType;

typedef struct FileInfo {
  int64_t filesize;      /**< size in bytes, -1 for non-files and unknown */
  int64_t modtime;       /**< last modification time */
  int64_t createtime;    /**< like modtime, but for file creation time */
  int64_t accesstime;    /**< like modtime, but for file access time */
  FileType filetype; /**< File? Directory? Symlink? */
  bool readonly;     /**< non-zero if read only, zero if writable. */
} FileInfo;

void null0_trace(char* str) {}

uint64_t null0_current_time() {
  return 0;
}

float null0_delta_time() {
  float ret = {0};
  return ret;
}

int null0_random_int(int min, int max) {
  int ret = {0};
  return ret;
}

unsigned int null0_load_sound(char* filename) {
  return 1;  // Mock handle
}

void null0_play_sound(unsigned int sound, bool loop) {}

void null0_stop_sound(unsigned int sound) {}

unsigned int null0_new_sfx(SfxParams* params) {
  return 1;  // Mock handle
}

void null0_preset_sfx(SfxParams* params, SfxPresetType type) {}

void null0_randomize_sfx(SfxParams* params, SfxWaveType waveType) {}

void null0_mutate_sfx(SfxParams* params, float range, unsigned int mask) {}

void null0_load_sfx(SfxParams* params, char* filename) {}

void null0_unload_sound(unsigned int sound) {}

bool null0_key_pressed(Key key) {
  bool ret = {0};
  return ret;
}

bool null0_key_down(Key key) {
  bool ret = {0};
  return ret;
}

bool null0_key_released(Key key) {
  bool ret = {0};
  return ret;
}

bool null0_key_up(Key key) {
  bool ret = {0};
  return ret;
}

bool null0_gamepad_button_pressed(int gamepad, GamepadButton button) {
  bool ret = {0};
  return ret;
}

bool null0_gamepad_button_down(int gamepad, GamepadButton button) {
  bool ret = {0};
  return ret;
}

bool null0_gamepad_button_released(int gamepad, GamepadButton button) {
  bool ret = {0};
  return ret;
}

Vector null0_mouse_position() {
  Vector ret = {};
  return ret;
}

bool null0_mouse_button_pressed(MouseButton button) {
  bool ret = {0};
  return ret;
}

bool null0_mouse_button_down(MouseButton button) {
  bool ret = {0};
  return ret;
}

bool null0_mouse_button_released(MouseButton button) {
  bool ret = {0};
  return ret;
}

bool null0_mouse_button_up(MouseButton button) {
  bool ret = {0};
  return ret;
}

unsigned int null0_new_image(int width, int height, Color color) {
  return 1;  // Mock handle
}

unsigned int null0_image_copy(unsigned int image) {
  return 1;  // Mock handle
}

unsigned int null0_image_subimage(unsigned int image, int x, int y, int width, int height) {
  return 1;  // Mock handle
}

void null0_clear(Color color) {}

void null0_draw_point(int x, int y, Color color) {}

void null0_draw_line(int startPosX, int startPosY, int endPosX, int endPosY, Color color) {}

void null0_draw_rectangle(int posX, int posY, int width, int height, Color color) {}

void null0_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color) {}

void null0_draw_ellipse(int centerX, int centerY, int radiusX, int radiusY, Color color) {}

void null0_draw_circle(int centerX, int centerY, int radius, Color color) {}

void null0_draw_polygon(Vector* points, int numPoints, Color color) {}

void null0_draw_polyline(Vector* points, int numPoints, Color color) {}

void null0_draw_arc(int centerX, int centerY, float radius, float startAngle, float endAngle, int segments, Color color) {}

void null0_draw_rectangle_rounded(int x, int y, int width, int height, int cornerRadius, Color color) {}

void null0_draw_image(unsigned int src, int posX, int posY) {}

void null0_draw_image_tint(unsigned int src, int posX, int posY, Color tint) {}

void null0_draw_image_rotated(unsigned int src, int posX, int posY, float degrees, float offsetX, float offsetY, ImageFilter filter) {}

void null0_draw_image_flipped(unsigned int src, int posX, int posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal) {}

void null0_draw_image_scaled(unsigned int src, int posX, int posY, float scaleX, float scaleY, float offsetX, float offsetY, ImageFilter filter) {}

void null0_draw_text(unsigned int font, char* text, int posX, int posY, Color color) {}

void null0_save_image(unsigned int image, char* filename) {}

unsigned int null0_load_image(char* filename) {
  return 1;  // Mock handle
}

void null0_image_resize(unsigned int image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill) {}

void null0_image_scale(unsigned int image, float scaleX, float scaleY, ImageFilter filter) {}

void null0_image_color_replace(unsigned int image, Color color, Color replace) {}

void null0_image_color_tint(unsigned int image, Color color) {}

void null0_image_color_fade(unsigned int image, float alpha) {}

unsigned int null0_font_copy(unsigned int font) {
  return 1;  // Mock handle
}

unsigned int null0_font_scale(unsigned int font, float scaleX, float scaleY, ImageFilter filter) {
  return 1;  // Mock handle
}

unsigned int null0_load_font_bmf(char* filename, char* characters) {
  return 1;  // Mock handle
}

unsigned int null0_load_font_bmf_from_image(unsigned int image, char* characters) {
  return 1;  // Mock handle
}

Dimensions null0_measure_text(unsigned int font, char* text) {
  Dimensions ret = {0};
  return ret;
}

Dimensions null0_measure_image(unsigned int image) {
  Dimensions ret = {0};
  return ret;
}

unsigned int null0_load_font_tty(char* filename, int glyphWidth, int glyphHeight, char* characters) {
  return 1;  // Mock handle
}

unsigned int null0_load_font_tty_from_image(unsigned int image, int glyphWidth, int glyphHeight, char* characters) {
  return 1;  // Mock handle
}

unsigned int null0_load_font_ttf(char* filename, int fontSize) {
  return 1;  // Mock handle
}

void null0_image_color_invert(unsigned int image) {}

Rectangle null0_image_alpha_border(unsigned int image, float threshold) {
  Rectangle ret = {0};
  return ret;
}

void null0_image_crop(unsigned int image, int x, int y, int width, int height) {}

void null0_image_alpha_crop(unsigned int image, float threshold) {}

void null0_image_color_brightness(unsigned int image, float factor) {}

void null0_image_flip(unsigned int image, bool horizontal, bool vertical) {}

void null0_image_color_contrast(unsigned int image, float contrast) {}

void null0_image_alpha_mask(unsigned int image, unsigned int alphaMask, int posX, int posY) {}

unsigned int null0_image_rotate(unsigned int image, float degrees, ImageFilter filter) {
  return 1;  // Mock handle
}

unsigned int null0_image_gradient(int width, int height, Color topLeft, Color topRight, Color bottomLeft, Color bottomRight) {
  return 1;  // Mock handle
}

void null0_unload_image(unsigned int image) {}

void null0_unload_font(unsigned int font) {}

void null0_clear_on_image(unsigned int destination, Color color) {}

void null0_draw_point_on_image(unsigned int destination, int x, int y, Color color) {}

void null0_draw_line_on_image(unsigned int destination, int startPosX, int startPosY, int endPosX, int endPosY, Color color) {}

void null0_draw_rectangle_on_image(unsigned int destination, int posX, int posY, int width, int height, Color color) {}

void null0_draw_triangle_on_image(unsigned int destination, int x1, int y1, int x2, int y2, int x3, int y3, Color color) {}

void null0_draw_ellipse_on_image(unsigned int destination, int centerX, int centerY, int radiusX, int radiusY, Color color) {}

void null0_draw_circle_on_image(unsigned int destination, int centerX, int centerY, int radius, Color color) {}

void null0_draw_polygon_on_image(unsigned int destination, Vector* points, int numPoints, Color color) {}

void null0_draw_polyline_on_image(unsigned int destination, Vector* points, int numPoints, Color color) {}

void null0_draw_rectangle_rounded_on_image(unsigned int destination, int x, int y, int width, int height, int cornerRadius, Color color) {}

void null0_draw_image_on_image(unsigned int destination, unsigned int src, int posX, int posY) {}

void null0_draw_image_tint_on_image(unsigned int destination, unsigned int src, int posX, int posY, Color tint) {}

void null0_draw_image_rotated_on_image(unsigned int destination, unsigned int src, int posX, int posY, float degrees, float offsetX, float offsetY, ImageFilter filter) {}

void null0_draw_image_flipped_on_image(unsigned int destination, unsigned int src, int posX, int posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal) {}

void null0_draw_image_scaled_on_image(unsigned int destination, unsigned int src, int posX, int posY, float scaleX, float scaleY, float offsetX, float offsetY, ImageFilter filter) {}

void null0_draw_text_on_image(unsigned int destination, unsigned int font, char* text, int posX, int posY, Color color) {}

void null0_draw_rectangle_outline(int posX, int posY, int width, int height, Color color) {}

void null0_draw_triangle_outline(int x1, int y1, int x2, int y2, int x3, int y3, Color color) {}

void null0_draw_ellipse_outline(int centerX, int centerY, int radiusX, int radiusY, Color color) {}

void null0_draw_circle_outline(int centerX, int centerY, int radius, Color color) {}

void null0_draw_polygon_outline(Vector* points, int numPoints, Color color) {}

void null0_draw_arc_outline(int centerX, int centerY, float radius, float startAngle, float endAngle, int segments, Color color) {}

void null0_draw_rectangle_rounded_outline(int x, int y, int width, int height, int cornerRadius, Color color) {}

void null0_draw_rectangle_outline_on_image(unsigned int destination, int posX, int posY, int width, int height, Color color) {}

void null0_draw_triangle_outline_on_image(unsigned int destination, int x1, int y1, int x2, int y2, int x3, int y3, Color color) {}

void null0_draw_ellipse_outline_on_image(unsigned int destination, int centerX, int centerY, int radiusX, int radiusY, Color color) {}

void null0_draw_circle_outline_on_image(unsigned int destination, int centerX, int centerY, int radius, Color color) {}

void null0_draw_polygon_outline_on_image(unsigned int destination, Vector* points, int numPoints, Color color) {}

void null0_draw_rectangle_rounded_outline_on_image(unsigned int destination, int x, int y, int width, int height, int cornerRadius, Color color) {}

unsigned char* null0_file_read(char* filename, unsigned int* bytesRead) {
  unsigned char* ret = {0};
  return ret;
}

bool null0_file_write(char* filename, unsigned int byteSize, unsigned char* data) {
  bool ret = {0};
  return ret;
}

bool null0_file_append(char* filename, unsigned int byteSize, unsigned char* data) {
  bool ret = {0};
  return ret;
}

FileInfo null0_file_info(char* filename) {
  FileInfo ret = {};
  return ret;
}

char* null0_get_write_dir() {
  char* ret = {0};
  return ret;
}

Color null0_color_tint(Color color, Color tint) {
  Color ret = {0};
  return ret;
}

Color null0_color_fade(Color color, float alpha) {
  Color ret = {0};
  return ret;
}

Color null0_color_brightness(Color color, float factor) {
  Color ret = {0};
  return ret;
}

Color null0_color_invert(Color color) {
  Color ret = {0};
  return ret;
}

Color null0_color_alpha_blend(Color dst, Color src) {
  Color ret = {0};
  return ret;
}

Color null0_color_contrast(Color color, float contrast) {
  Color ret = {0};
  return ret;
}

Color null0_color_bilinear_interpolate(Color color00, Color color01, Color color10, Color color11, float coordinateX, float coordinateY) {
  Color ret = {0};
  return ret;
}
