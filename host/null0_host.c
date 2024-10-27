
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#define SHARED_MEM_SIZE 1024 * 1024
unsigned char _shared_mem[SHARED_MEM_SIZE] = {0};

// Shared memory pointer
void* shared_pointer() { return (void*)&_shared_mem; }

// Memory copying functions
#ifdef EMSCRIPTEN
EM_JS(void, __copy_bytes_to_cart, (void* val, unsigned int offset, unsigned int size), {
  for (let i = 0; i < size; i++) {
    Module.cart.view.setUint8(offset + Module.cart.shared_loc + i, Module.HEAPU8[offset + Module.shared_loc + i])
  }
});
#else
void __copy_bytes_to_cart(void* val, unsigned int offset, unsigned int size) {
  // TODO: implement for WAMR
}
#endif

void copy_bytes_to_cart(void* val, unsigned int offset, unsigned int size) {
  memcpy(&_shared_mem, val, size);
  __copy_bytes_to_cart(val, offset, size);
}

unsigned char* copy_bytes_from_cart(unsigned int offset, unsigned int size) {
  unsigned char* ret = malloc(size);
  memcpy(ret, (unsigned char*)(&_shared_mem + offset), size);
  return ret;
}

// Shared types
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

typedef enum { FILTER_NEAREST, FILTER_BILINEAR } ImageFilter;

typedef struct {
  float x;
  float y;
  float width;
  float height;
} Rectangle;

// Global offsets
unsigned int cart_shared_arg_offset = 0;
unsigned int cart_shared_ret_offset = 0;

// Type getters/setters
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

void null0_trace(char* str) {}

void null0_current_time() {}

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

void null0_mouse_position() {}

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

bool null0_file_write(char* filename, unsigned char* data, unsigned int byteSize) {
  bool ret = {0};
  return ret;
}

bool null0_file_append(char* filename, unsigned char* data, unsigned int byteSize) {
  bool ret = {0};
  return ret;
}

void null0_file_info(char* filename) {}

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

void call(Op op) {
  cart_shared_arg_offset = 0;
  cart_shared_ret_offset = 0;

  switch (op) {
    case OP_TRACE:
      null0_trace(get_string_arg());
      break;

    case OP_CURRENT_TIME:
      null0_current_time();
      break;

    case OP_DELTA_TIME:
      set_float_ret(null0_delta_time());
      break;

    case OP_RANDOM_INT:
      set_int_ret(null0_random_int(get_i32_arg(), get_i32_arg()));
      break;

    case OP_LOAD_SOUND:
      set_int_ret(null0_load_sound(get_string_arg()));
      break;

    case OP_PLAY_SOUND:
      null0_play_sound(get_Sound_arg(), get_bool_arg());
      break;

    case OP_STOP_SOUND:
      null0_stop_sound(get_Sound_arg());
      break;

    case OP_NEW_SFX:
      set_int_ret(null0_new_sfx(get_SfxParams_arg()));
      break;

    case OP_PRESET_SFX:
      null0_preset_sfx(get_SfxParams_arg(), get_SfxPresetType_arg());
      break;

    case OP_RANDOMIZE_SFX:
      null0_randomize_sfx(get_SfxParams_arg(), get_SfxWaveType_arg());
      break;

    case OP_MUTATE_SFX:
      null0_mutate_sfx(get_SfxParams_arg(), get_f32_arg(), get_u32_arg());
      break;

    case OP_LOAD_SFX:
      null0_load_sfx(get_SfxParams_arg(), get_string_arg());
      break;

    case OP_UNLOAD_SOUND:
      null0_unload_sound(get_Sound_arg());
      break;

    case OP_KEY_PRESSED:
      set_bool_ret(null0_key_pressed(get_Key_arg()));
      break;

    case OP_KEY_DOWN:
      set_bool_ret(null0_key_down(get_Key_arg()));
      break;

    case OP_KEY_RELEASED:
      set_bool_ret(null0_key_released(get_Key_arg()));
      break;

    case OP_KEY_UP:
      set_bool_ret(null0_key_up(get_Key_arg()));
      break;

    case OP_GAMEPAD_BUTTON_PRESSED:
      set_bool_ret(null0_gamepad_button_pressed(get_i32_arg(), get_GamepadButton_arg()));
      break;

    case OP_GAMEPAD_BUTTON_DOWN:
      set_bool_ret(null0_gamepad_button_down(get_i32_arg(), get_GamepadButton_arg()));
      break;

    case OP_GAMEPAD_BUTTON_RELEASED:
      set_bool_ret(null0_gamepad_button_released(get_i32_arg(), get_GamepadButton_arg()));
      break;

    case OP_MOUSE_POSITION:
      null0_mouse_position();
      break;

    case OP_MOUSE_BUTTON_PRESSED:
      set_bool_ret(null0_mouse_button_pressed(get_MouseButton_arg()));
      break;

    case OP_MOUSE_BUTTON_DOWN:
      set_bool_ret(null0_mouse_button_down(get_MouseButton_arg()));
      break;

    case OP_MOUSE_BUTTON_RELEASED:
      set_bool_ret(null0_mouse_button_released(get_MouseButton_arg()));
      break;

    case OP_MOUSE_BUTTON_UP:
      set_bool_ret(null0_mouse_button_up(get_MouseButton_arg()));
      break;

    case OP_NEW_IMAGE:
      set_int_ret(null0_new_image(get_i32_arg(), get_i32_arg(), get_Color_arg()));
      break;

    case OP_IMAGE_COPY:
      set_int_ret(null0_image_copy(get_Image_arg()));
      break;

    case OP_IMAGE_SUBIMAGE:
      set_int_ret(null0_image_subimage(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg()));
      break;

    case OP_CLEAR:
      null0_clear(get_Color_arg());
      break;

    case OP_DRAW_POINT:
      null0_draw_point(get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_LINE:
      null0_draw_line(get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE:
      null0_draw_rectangle(get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_TRIANGLE:
      null0_draw_triangle(get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_ELLIPSE:
      null0_draw_ellipse(get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_CIRCLE:
      null0_draw_circle(get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_POLYGON:
      null0_draw_polygon(get_Vector_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_POLYLINE:
      null0_draw_polyline(get_Vector_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_ARC:
      null0_draw_arc(get_i32_arg(), get_i32_arg(), get_f32_arg(), get_f32_arg(), get_f32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE_ROUNDED:
      null0_draw_rectangle_rounded(get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_IMAGE:
      null0_draw_image(get_Image_arg(), get_i32_arg(), get_i32_arg());
      break;

    case OP_DRAW_IMAGE_TINT:
      null0_draw_image_tint(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_IMAGE_ROTATED:
      null0_draw_image_rotated(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_f32_arg(), get_f32_arg(), get_f32_arg(), get_ImageFilter_arg());
      break;

    case OP_DRAW_IMAGE_FLIPPED:
      null0_draw_image_flipped(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_bool_arg(), get_bool_arg(), get_bool_arg());
      break;

    case OP_DRAW_IMAGE_SCALED:
      null0_draw_image_scaled(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_f32_arg(), get_f32_arg(), get_f32_arg(), get_f32_arg(), get_ImageFilter_arg());
      break;

    case OP_DRAW_TEXT:
      null0_draw_text(get_Font_arg(), get_string_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_SAVE_IMAGE:
      null0_save_image(get_Image_arg(), get_string_arg());
      break;

    case OP_LOAD_IMAGE:
      set_int_ret(null0_load_image(get_string_arg()));
      break;

    case OP_IMAGE_RESIZE:
      null0_image_resize(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_IMAGE_SCALE:
      null0_image_scale(get_Image_arg(), get_f32_arg(), get_f32_arg(), get_ImageFilter_arg());
      break;

    case OP_IMAGE_COLOR_REPLACE:
      null0_image_color_replace(get_Image_arg(), get_Color_arg(), get_Color_arg());
      break;

    case OP_IMAGE_COLOR_TINT:
      null0_image_color_tint(get_Image_arg(), get_Color_arg());
      break;

    case OP_IMAGE_COLOR_FADE:
      null0_image_color_fade(get_Image_arg(), get_f32_arg());
      break;

    case OP_FONT_COPY:
      set_int_ret(null0_font_copy(get_Font_arg()));
      break;

    case OP_FONT_SCALE:
      set_int_ret(null0_font_scale(get_Font_arg(), get_f32_arg(), get_f32_arg(), get_ImageFilter_arg()));
      break;

    case OP_LOAD_FONT_BMF:
      set_int_ret(null0_load_font_bmf(get_string_arg(), get_string_arg()));
      break;

    case OP_LOAD_FONT_BMF_FROM_IMAGE:
      set_int_ret(null0_load_font_bmf_from_image(get_Image_arg(), get_string_arg()));
      break;

    case OP_MEASURE_TEXT:
      set_Dimensions_ret(null0_measure_text(get_Font_arg(), get_string_arg()));
      break;

    case OP_MEASURE_IMAGE:
      set_Dimensions_ret(null0_measure_image(get_Image_arg()));
      break;

    case OP_LOAD_FONT_TTY:
      set_int_ret(null0_load_font_tty(get_string_arg(), get_i32_arg(), get_i32_arg(), get_string_arg()));
      break;

    case OP_LOAD_FONT_TTY_FROM_IMAGE:
      set_int_ret(null0_load_font_tty_from_image(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_string_arg()));
      break;

    case OP_LOAD_FONT_TTF:
      set_int_ret(null0_load_font_ttf(get_string_arg(), get_i32_arg()));
      break;

    case OP_IMAGE_COLOR_INVERT:
      null0_image_color_invert(get_Image_arg());
      break;

    case OP_IMAGE_ALPHA_BORDER:
      set_Rectangle_ret(null0_image_alpha_border(get_Image_arg(), get_f32_arg()));
      break;

    case OP_IMAGE_CROP:
      null0_image_crop(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg());
      break;

    case OP_IMAGE_ALPHA_CROP:
      null0_image_alpha_crop(get_Image_arg(), get_f32_arg());
      break;

    case OP_IMAGE_COLOR_BRIGHTNESS:
      null0_image_color_brightness(get_Image_arg(), get_f32_arg());
      break;

    case OP_IMAGE_FLIP:
      null0_image_flip(get_Image_arg(), get_bool_arg(), get_bool_arg());
      break;

    case OP_IMAGE_COLOR_CONTRAST:
      null0_image_color_contrast(get_Image_arg(), get_f32_arg());
      break;

    case OP_IMAGE_ALPHA_MASK:
      null0_image_alpha_mask(get_Image_arg(), get_Image_arg(), get_i32_arg(), get_i32_arg());
      break;

    case OP_IMAGE_ROTATE:
      set_int_ret(null0_image_rotate(get_Image_arg(), get_f32_arg(), get_ImageFilter_arg()));
      break;

    case OP_IMAGE_GRADIENT:
      set_int_ret(null0_image_gradient(get_i32_arg(), get_i32_arg(), get_Color_arg(), get_Color_arg(), get_Color_arg(), get_Color_arg()));
      break;

    case OP_UNLOAD_IMAGE:
      null0_unload_image(get_Image_arg());
      break;

    case OP_UNLOAD_FONT:
      null0_unload_font(get_Font_arg());
      break;

    case OP_CLEAR_ON_IMAGE:
      null0_clear_on_image(get_Image_arg(), get_Color_arg());
      break;

    case OP_DRAW_POINT_ON_IMAGE:
      null0_draw_point_on_image(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_LINE_ON_IMAGE:
      null0_draw_line_on_image(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE_ON_IMAGE:
      null0_draw_rectangle_on_image(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_TRIANGLE_ON_IMAGE:
      null0_draw_triangle_on_image(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_ELLIPSE_ON_IMAGE:
      null0_draw_ellipse_on_image(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_CIRCLE_ON_IMAGE:
      null0_draw_circle_on_image(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_POLYGON_ON_IMAGE:
      null0_draw_polygon_on_image(get_Image_arg(), get_Vector_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_POLYLINE_ON_IMAGE:
      null0_draw_polyline_on_image(get_Image_arg(), get_Vector_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE_ROUNDED_ON_IMAGE:
      null0_draw_rectangle_rounded_on_image(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_IMAGE_ON_IMAGE:
      null0_draw_image_on_image(get_Image_arg(), get_Image_arg(), get_i32_arg(), get_i32_arg());
      break;

    case OP_DRAW_IMAGE_TINT_ON_IMAGE:
      null0_draw_image_tint_on_image(get_Image_arg(), get_Image_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_IMAGE_ROTATED_ON_IMAGE:
      null0_draw_image_rotated_on_image(get_Image_arg(), get_Image_arg(), get_i32_arg(), get_i32_arg(), get_f32_arg(), get_f32_arg(), get_f32_arg(), get_ImageFilter_arg());
      break;

    case OP_DRAW_IMAGE_FLIPPED_ON_IMAGE:
      null0_draw_image_flipped_on_image(get_Image_arg(), get_Image_arg(), get_i32_arg(), get_i32_arg(), get_bool_arg(), get_bool_arg(), get_bool_arg());
      break;

    case OP_DRAW_IMAGE_SCALED_ON_IMAGE:
      null0_draw_image_scaled_on_image(get_Image_arg(), get_Image_arg(), get_i32_arg(), get_i32_arg(), get_f32_arg(), get_f32_arg(), get_f32_arg(), get_f32_arg(), get_ImageFilter_arg());
      break;

    case OP_DRAW_TEXT_ON_IMAGE:
      null0_draw_text_on_image(get_Image_arg(), get_Font_arg(), get_string_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE_OUTLINE:
      null0_draw_rectangle_outline(get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_TRIANGLE_OUTLINE:
      null0_draw_triangle_outline(get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_ELLIPSE_OUTLINE:
      null0_draw_ellipse_outline(get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_CIRCLE_OUTLINE:
      null0_draw_circle_outline(get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_POLYGON_OUTLINE:
      null0_draw_polygon_outline(get_Vector_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_ARC_OUTLINE:
      null0_draw_arc_outline(get_i32_arg(), get_i32_arg(), get_f32_arg(), get_f32_arg(), get_f32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE_ROUNDED_OUTLINE:
      null0_draw_rectangle_rounded_outline(get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE_OUTLINE_ON_IMAGE:
      null0_draw_rectangle_outline_on_image(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_TRIANGLE_OUTLINE_ON_IMAGE:
      null0_draw_triangle_outline_on_image(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_ELLIPSE_OUTLINE_ON_IMAGE:
      null0_draw_ellipse_outline_on_image(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_CIRCLE_OUTLINE_ON_IMAGE:
      null0_draw_circle_outline_on_image(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_POLYGON_OUTLINE_ON_IMAGE:
      null0_draw_polygon_outline_on_image(get_Image_arg(), get_Vector_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE_ROUNDED_OUTLINE_ON_IMAGE:
      null0_draw_rectangle_rounded_outline_on_image(get_Image_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_i32_arg(), get_Color_arg());
      break;

    case OP_FILE_READ:
      set_char* _ret(null0_file_read(get_string_arg(), get_u32_arg()));
      break;

    case OP_FILE_WRITE:
      set_bool_ret(null0_file_write(get_string_arg(), get_bytes_arg(), get_u32_arg()));
      break;

    case OP_FILE_APPEND:
      set_bool_ret(null0_file_append(get_string_arg(), get_bytes_arg(), get_u32_arg()));
      break;

    case OP_FILE_INFO:
      null0_file_info(get_string_arg());
      break;

    case OP_GET_WRITE_DIR:
      set_char* _ret(null0_get_write_dir());
      break;

    case OP_COLOR_TINT:
      set_Color_ret(null0_color_tint(get_Color_arg(), get_Color_arg()));
      break;

    case OP_COLOR_FADE:
      set_Color_ret(null0_color_fade(get_Color_arg(), get_f32_arg()));
      break;

    case OP_COLOR_BRIGHTNESS:
      set_Color_ret(null0_color_brightness(get_Color_arg(), get_f32_arg()));
      break;

    case OP_COLOR_INVERT:
      set_Color_ret(null0_color_invert(get_Color_arg()));
      break;

    case OP_COLOR_ALPHA_BLEND:
      set_Color_ret(null0_color_alpha_blend(get_Color_arg(), get_Color_arg()));
      break;

    case OP_COLOR_CONTRAST:
      set_Color_ret(null0_color_contrast(get_Color_arg(), get_f32_arg()));
      break;

    case OP_COLOR_BILINEAR_INTERPOLATE:
      set_Color_ret(null0_color_bilinear_interpolate(get_Color_arg(), get_Color_arg(), get_Color_arg(), get_Color_arg(), get_f32_arg(), get_f32_arg()));
      break;

    default:
      fprintf(stderr, "Unknown op: %d\n", op);
  }
}
