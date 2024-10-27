// null0_host.h

#ifndef NULL0_HOST_H
#define NULL0_HOST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

// Basic shared types
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

typedef struct {
    float x;
    float y;
} Vector;

typedef struct {
    unsigned int width;
    unsigned int height;
} Dimensions;

typedef struct {
    float x;
    float y;
    float width;
    float height;
} Rectangle;

// Enums
typedef enum {
    FILTER_NEAREST,
    FILTER_BILINEAR
} ImageFilter;

typedef enum {
    KEY_UNKNOWN = 0,
    KEY_A, KEY_B, KEY_C, // etc...
    // Add all key definitions
} Key;

typedef enum {
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE
} MouseButton;

typedef enum {
    GAMEPAD_BUTTON_UNKNOWN = 0,
    GAMEPAD_BUTTON_A,
    GAMEPAD_BUTTON_B,
    // Add all gamepad button definitions
} GamepadButton;

typedef enum {
    WAVE_SQUARE,
    WAVE_SINE,
    WAVE_TRIANGLE,
    WAVE_SAW
} SfxWaveType;

typedef enum {
    PRESET_PICKUP,
    PRESET_LASER,
    PRESET_EXPLOSION,
    // Add all SFX preset types
} SfxPresetType;

// SFX Parameters
typedef struct {
    SfxWaveType waveType;
    float frequency;
    float attack;
    float decay;
    float sustain;
    float release;
    // Add other SFX parameters
} SfxParams;

// Type getters/setters declarations
char* get_string_arg();
int get_int_arg();
unsigned int get_u32_arg();
float get_float_arg();
bool get_bool_arg();
Color get_Color_arg();
Vector* get_Vector_arg();
Key get_Key_arg();
GamepadButton get_GamepadButton_arg();
MouseButton get_MouseButton_arg();
ImageFilter get_ImageFilter_arg();
SfxParams* get_SfxParams_arg();
SfxPresetType get_SfxPresetType_arg();
SfxWaveType get_SfxWaveType_arg();

void set_int_ret(int value);
void set_float_ret(float value);
void set_bool_ret(bool value);
void set_Color_ret(Color value);
void set_Rectangle_ret(Rectangle value);
void set_Dimensions_ret(Dimensions value);
void set_string_ret(char* value);

// Operation enum (all your existing operations)
typedef enum {
  OP_TRACE,
  OP_CURRENT_TIME,
  OP_DELTA_TIME,
  OP_RANDOM_INT,
  OP_LOAD_SOUND,
  OP_PLAY_SOUND,
  OP_STOP_SOUND,
  OP_NEW_SFX,
  OP_PRESET_SFX,
  OP_RANDOMIZE_SFX,
  OP_MUTATE_SFX,
  OP_LOAD_SFX,
  OP_UNLOAD_SOUND,
  OP_KEY_PRESSED,
  OP_KEY_DOWN,
  OP_KEY_RELEASED,
  OP_KEY_UP,
  OP_GAMEPAD_BUTTON_PRESSED,
  OP_GAMEPAD_BUTTON_DOWN,
  OP_GAMEPAD_BUTTON_RELEASED,
  OP_MOUSE_POSITION,
  OP_MOUSE_BUTTON_PRESSED,
  OP_MOUSE_BUTTON_DOWN,
  OP_MOUSE_BUTTON_RELEASED,
  OP_MOUSE_BUTTON_UP,
  OP_NEW_IMAGE,
  OP_IMAGE_COPY,
  OP_IMAGE_SUBIMAGE,
  OP_CLEAR,
  OP_DRAW_POINT,
  OP_DRAW_LINE,
  OP_DRAW_RECTANGLE,
  OP_DRAW_TRIANGLE,
  OP_DRAW_ELLIPSE,
  OP_DRAW_CIRCLE,
  OP_DRAW_POLYGON,
  OP_DRAW_POLYLINE,
  OP_DRAW_ARC,
  OP_DRAW_RECTANGLE_ROUNDED,
  OP_DRAW_IMAGE,
  OP_DRAW_IMAGE_TINT,
  OP_DRAW_IMAGE_ROTATED,
  OP_DRAW_IMAGE_FLIPPED,
  OP_DRAW_IMAGE_SCALED,
  OP_DRAW_TEXT,
  OP_SAVE_IMAGE,
  OP_LOAD_IMAGE,
  OP_IMAGE_RESIZE,
  OP_IMAGE_SCALE,
  OP_IMAGE_COLOR_REPLACE,
  OP_IMAGE_COLOR_TINT,
  OP_IMAGE_COLOR_FADE,
  OP_FONT_COPY,
  OP_FONT_SCALE,
  OP_LOAD_FONT_BMF,
  OP_LOAD_FONT_BMF_FROM_IMAGE,
  OP_MEASURE_TEXT,
  OP_MEASURE_IMAGE,
  OP_LOAD_FONT_TTY,
  OP_LOAD_FONT_TTY_FROM_IMAGE,
  OP_LOAD_FONT_TTF,
  OP_IMAGE_COLOR_INVERT,
  OP_IMAGE_ALPHA_BORDER,
  OP_IMAGE_CROP,
  OP_IMAGE_ALPHA_CROP,
  OP_IMAGE_COLOR_BRIGHTNESS,
  OP_IMAGE_FLIP,
  OP_IMAGE_COLOR_CONTRAST,
  OP_IMAGE_ALPHA_MASK,
  OP_IMAGE_ROTATE,
  OP_IMAGE_GRADIENT,
  OP_UNLOAD_IMAGE,
  OP_UNLOAD_FONT,
  OP_CLEAR_ON_IMAGE,
  OP_DRAW_POINT_ON_IMAGE,
  OP_DRAW_LINE_ON_IMAGE,
  OP_DRAW_RECTANGLE_ON_IMAGE,
  OP_DRAW_TRIANGLE_ON_IMAGE,
  OP_DRAW_ELLIPSE_ON_IMAGE,
  OP_DRAW_CIRCLE_ON_IMAGE,
  OP_DRAW_POLYGON_ON_IMAGE,
  OP_DRAW_POLYLINE_ON_IMAGE,
  OP_DRAW_RECTANGLE_ROUNDED_ON_IMAGE,
  OP_DRAW_IMAGE_ON_IMAGE,
  OP_DRAW_IMAGE_TINT_ON_IMAGE,
  OP_DRAW_IMAGE_ROTATED_ON_IMAGE,
  OP_DRAW_IMAGE_FLIPPED_ON_IMAGE,
  OP_DRAW_IMAGE_SCALED_ON_IMAGE,
  OP_DRAW_TEXT_ON_IMAGE,
  OP_DRAW_RECTANGLE_OUTLINE,
  OP_DRAW_TRIANGLE_OUTLINE,
  OP_DRAW_ELLIPSE_OUTLINE,
  OP_DRAW_CIRCLE_OUTLINE,
  OP_DRAW_POLYGON_OUTLINE,
  OP_DRAW_ARC_OUTLINE,
  OP_DRAW_RECTANGLE_ROUNDED_OUTLINE,
  OP_DRAW_RECTANGLE_OUTLINE_ON_IMAGE,
  OP_DRAW_TRIANGLE_OUTLINE_ON_IMAGE,
  OP_DRAW_ELLIPSE_OUTLINE_ON_IMAGE,
  OP_DRAW_CIRCLE_OUTLINE_ON_IMAGE,
  OP_DRAW_POLYGON_OUTLINE_ON_IMAGE,
  OP_DRAW_RECTANGLE_ROUNDED_OUTLINE_ON_IMAGE,
  OP_FILE_READ,
  OP_FILE_WRITE,
  OP_FILE_APPEND,
  OP_FILE_INFO,
  OP_GET_WRITE_DIR,
  OP_COLOR_TINT,
  OP_COLOR_FADE,
  OP_COLOR_BRIGHTNESS,
  OP_COLOR_INVERT,
  OP_COLOR_ALPHA_BLEND,
  OP_COLOR_CONTRAST,
  OP_COLOR_BILINEAR_INTERPOLATE,
} Op;

// Global offsets for passing args/returns
unsigned int cart_shared_arg_offset = 0;
unsigned int cart_shared_ret_offset = 0;

#define SHARED_MEM_SIZE 1024*1024
unsigned char _shared_mem[SHARED_MEM_SIZE] = {0};

// Memory management functions
void* shared_pointer();
void copy_bytes_to_cart(void* val, unsigned int offset, unsigned int size);
unsigned char* copy_bytes_from_cart(unsigned int offset, unsigned int size);

// Main operation handler
void call(Op op);

#endif // NULL0_HOST_H
