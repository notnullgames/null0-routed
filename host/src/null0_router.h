// Host function-call router for null0.
// Generated on Sun Oct 27 2024 08:36:36 GMT-0700 (Pacific Daylight Time)

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "null0_api.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#define SHARED_MEM_SIZE 1024 * 1024
static unsigned char _shared_mem[SHARED_MEM_SIZE] = {0};

// Shared memory pointer (used in web-host)
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
  unsigned char* ret = (unsigned char*)malloc(size);
  memcpy(ret, (unsigned char*)(&_shared_mem + offset), size);
  return ret;
}

// Global offsets for passing memory back & forth
static unsigned int cart_shared_arg_offset = 0;
static unsigned int cart_shared_ret_offset = 0;

char* cart_get_arg_string() {
  unsigned int len = strlen((char*)&_shared_mem + cart_shared_arg_offset) + 1;
  char* ret = (char*)copy_bytes_from_cart(cart_shared_arg_offset, len);
  cart_shared_arg_offset += len;
  return ret;
}

unsigned int cart_get_arg_u32() {
  unsigned int* ret = (unsigned int*)copy_bytes_from_cart(cart_shared_arg_offset, sizeof(int));
  cart_shared_arg_offset += sizeof(int);
  return *ret;
}

int cart_get_arg_i32() {
  int* ret = (int*)copy_bytes_from_cart(cart_shared_arg_offset, sizeof(int));
  cart_shared_arg_offset += sizeof(int);
  return *ret;
}

Color cart_get_arg_Color() {
  Color* ret = (Color*)copy_bytes_from_cart(cart_shared_arg_offset, sizeof(Color));
  cart_shared_arg_offset += sizeof(Color);
  return *ret;
}

Dimensions cart_get_arg_Dimensions() {
  Dimensions* ret = (Dimensions*)copy_bytes_from_cart(cart_shared_arg_offset, sizeof(Dimensions));
  cart_shared_arg_offset += sizeof(Dimensions);
  return *ret;
}

bool cart_get_arg_bool() {
  bool* ret = (bool*)copy_bytes_from_cart(cart_shared_arg_offset, sizeof(bool));
  cart_shared_arg_offset += sizeof(bool);
  return *ret;
}

SfxParams* cart_get_arg_SfxParams_pointer() {
  SfxParams* ret = (SfxParams*)copy_bytes_from_cart(cart_shared_arg_offset, sizeof(SfxParams));
  cart_shared_arg_offset += sizeof(SfxParams);
  return ret;
}

float cart_get_arg_f32() {
  float* ret = (float*)copy_bytes_from_cart(cart_shared_arg_offset, sizeof(float));
  cart_shared_arg_offset += sizeof(float);
  return *ret;
}

Vector* cart_get_arg_Vector_array(int len) {
  Vector* ret = (Vector*)copy_bytes_from_cart(cart_shared_arg_offset, sizeof(Vector) * len);
  cart_shared_arg_offset += sizeof(Vector);
  return ret;
}

unsigned char* cart_get_arg_bytes(int len) {
  unsigned char* ret = (unsigned char*)copy_bytes_from_cart(cart_shared_arg_offset, len);
  cart_shared_arg_offset += len;
  return ret;
}

void cart_set_ret_string(char* value) {
  unsigned int len = strlen(value);
  copy_bytes_to_cart((void*)value, cart_shared_ret_offset, len+1);
  cart_shared_ret_offset += len+1;
}

void cart_set_ret_bytes(unsigned char* value, int len) {
  copy_bytes_to_cart((void*)value, cart_shared_ret_offset, len);
  cart_shared_ret_offset += len;
}

void cart_set_ret_u64(uint64_t value) {
  copy_bytes_to_cart((void*)&value, cart_shared_ret_offset, sizeof(value));
  cart_shared_ret_offset += sizeof(value);
}

void cart_set_ret_f32(float value) {
  copy_bytes_to_cart((void*)&value, cart_shared_ret_offset, sizeof(value));
  cart_shared_ret_offset += sizeof(value);
}

void cart_set_ret_i32(int value) {
  copy_bytes_to_cart((void*)&value, cart_shared_ret_offset, sizeof(value));
  cart_shared_ret_offset += sizeof(value);
}

void cart_set_ret_bool(bool value) {
  copy_bytes_to_cart((void*)&value, cart_shared_ret_offset, sizeof(value));
  cart_shared_ret_offset += sizeof(value);
}

void cart_set_ret_Color(Color value) {
  copy_bytes_to_cart((void*)&value, cart_shared_ret_offset, sizeof(value));
  cart_shared_ret_offset += sizeof(value);
}

void cart_set_ret_Dimensions(Dimensions value) {
  copy_bytes_to_cart((void*)&value, cart_shared_ret_offset, sizeof(value));
  cart_shared_ret_offset += sizeof(value);
}

void cart_set_ret_u32(unsigned int value) {
  copy_bytes_to_cart((void*)&value, cart_shared_ret_offset, sizeof(value));
  cart_shared_ret_offset += sizeof(value);
}

void cart_set_ret_Vector(Vector value) {
  copy_bytes_to_cart((void*)&value, cart_shared_ret_offset, sizeof(value));
  cart_shared_ret_offset += sizeof(value);
}

void cart_set_ret_Rectangle(Rectangle value) {
  copy_bytes_to_cart((void*)&value, cart_shared_ret_offset, sizeof(value));
  cart_shared_ret_offset += sizeof(value);
}

void cart_set_ret_FileInfo(FileInfo value) {
  copy_bytes_to_cart((void*)&value, cart_shared_ret_offset, sizeof(value));
  cart_shared_ret_offset += sizeof(value);
}

// These are special-cases because they need len
void cart_handle_edgecase_file_read() {
  char* filename = cart_get_arg_string();
  unsigned int byteSize = 0;
  unsigned char* bytes = null0_file_read(filename, &byteSize);
  cart_set_ret_u32(byteSize);
  cart_set_ret_bytes(bytes, byteSize);
}
void cart_handle_edgecase_file_write() {
  char* filename = cart_get_arg_string();
  unsigned int byteSize = cart_get_arg_u32();
  unsigned char* bytes = cart_get_arg_bytes(byteSize);
  cart_set_ret_bool(null0_file_write(filename, byteSize, bytes));
}
void cart_handle_edgecase_file_append() {
  char* filename = cart_get_arg_string();
  unsigned int byteSize = cart_get_arg_u32();
  unsigned char* bytes = cart_get_arg_bytes(byteSize);
  cart_set_ret_bool(null0_file_append(filename, byteSize, bytes));
}

// these are special-cases since arrays are a bit tricky
void cart_handle_edgecase_draw_polygon() {}
void cart_handle_edgecase_draw_polyline(){}
void cart_handle_edgecase_draw_polygon_on_image(){}
void cart_handle_edgecase_draw_polyline_on_image(){}
void cart_handle_edgecase_draw_polygon_outline(){}
void cart_handle_edgecase_draw_polygon_outline_on_image(){}



typedef enum {
    NULL0_OP_TRACE,
    NULL0_OP_CURRENT_TIME,
    NULL0_OP_DELTA_TIME,
    NULL0_OP_RANDOM_INT,
    NULL0_OP_LOAD_SOUND,
    NULL0_OP_PLAY_SOUND,
    NULL0_OP_STOP_SOUND,
    NULL0_OP_NEW_SFX,
    NULL0_OP_PRESET_SFX,
    NULL0_OP_RANDOMIZE_SFX,
    NULL0_OP_MUTATE_SFX,
    NULL0_OP_LOAD_SFX,
    NULL0_OP_UNLOAD_SOUND,
    NULL0_OP_KEY_PRESSED,
    NULL0_OP_KEY_DOWN,
    NULL0_OP_KEY_RELEASED,
    NULL0_OP_KEY_UP,
    NULL0_OP_GAMEPAD_BUTTON_PRESSED,
    NULL0_OP_GAMEPAD_BUTTON_DOWN,
    NULL0_OP_GAMEPAD_BUTTON_RELEASED,
    NULL0_OP_MOUSE_POSITION,
    NULL0_OP_MOUSE_BUTTON_PRESSED,
    NULL0_OP_MOUSE_BUTTON_DOWN,
    NULL0_OP_MOUSE_BUTTON_RELEASED,
    NULL0_OP_MOUSE_BUTTON_UP,
    NULL0_OP_NEW_IMAGE,
    NULL0_OP_IMAGE_COPY,
    NULL0_OP_IMAGE_SUBIMAGE,
    NULL0_OP_CLEAR,
    NULL0_OP_DRAW_POINT,
    NULL0_OP_DRAW_LINE,
    NULL0_OP_DRAW_RECTANGLE,
    NULL0_OP_DRAW_TRIANGLE,
    NULL0_OP_DRAW_ELLIPSE,
    NULL0_OP_DRAW_CIRCLE,
    NULL0_OP_DRAW_POLYGON,
    NULL0_OP_DRAW_POLYLINE,
    NULL0_OP_DRAW_ARC,
    NULL0_OP_DRAW_RECTANGLE_ROUNDED,
    NULL0_OP_DRAW_IMAGE,
    NULL0_OP_DRAW_IMAGE_TINT,
    NULL0_OP_DRAW_IMAGE_ROTATED,
    NULL0_OP_DRAW_IMAGE_FLIPPED,
    NULL0_OP_DRAW_IMAGE_SCALED,
    NULL0_OP_DRAW_TEXT,
    NULL0_OP_SAVE_IMAGE,
    NULL0_OP_LOAD_IMAGE,
    NULL0_OP_IMAGE_RESIZE,
    NULL0_OP_IMAGE_SCALE,
    NULL0_OP_IMAGE_COLOR_REPLACE,
    NULL0_OP_IMAGE_COLOR_TINT,
    NULL0_OP_IMAGE_COLOR_FADE,
    NULL0_OP_FONT_COPY,
    NULL0_OP_FONT_SCALE,
    NULL0_OP_LOAD_FONT_BMF,
    NULL0_OP_LOAD_FONT_BMF_FROM_IMAGE,
    NULL0_OP_MEASURE_TEXT,
    NULL0_OP_MEASURE_IMAGE,
    NULL0_OP_LOAD_FONT_TTY,
    NULL0_OP_LOAD_FONT_TTY_FROM_IMAGE,
    NULL0_OP_LOAD_FONT_TTF,
    NULL0_OP_IMAGE_COLOR_INVERT,
    NULL0_OP_IMAGE_ALPHA_BORDER,
    NULL0_OP_IMAGE_CROP,
    NULL0_OP_IMAGE_ALPHA_CROP,
    NULL0_OP_IMAGE_COLOR_BRIGHTNESS,
    NULL0_OP_IMAGE_FLIP,
    NULL0_OP_IMAGE_COLOR_CONTRAST,
    NULL0_OP_IMAGE_ALPHA_MASK,
    NULL0_OP_IMAGE_ROTATE,
    NULL0_OP_IMAGE_GRADIENT,
    NULL0_OP_UNLOAD_IMAGE,
    NULL0_OP_UNLOAD_FONT,
    NULL0_OP_CLEAR_ON_IMAGE,
    NULL0_OP_DRAW_POINT_ON_IMAGE,
    NULL0_OP_DRAW_LINE_ON_IMAGE,
    NULL0_OP_DRAW_RECTANGLE_ON_IMAGE,
    NULL0_OP_DRAW_TRIANGLE_ON_IMAGE,
    NULL0_OP_DRAW_ELLIPSE_ON_IMAGE,
    NULL0_OP_DRAW_CIRCLE_ON_IMAGE,
    NULL0_OP_DRAW_POLYGON_ON_IMAGE,
    NULL0_OP_DRAW_POLYLINE_ON_IMAGE,
    NULL0_OP_DRAW_RECTANGLE_ROUNDED_ON_IMAGE,
    NULL0_OP_DRAW_IMAGE_ON_IMAGE,
    NULL0_OP_DRAW_IMAGE_TINT_ON_IMAGE,
    NULL0_OP_DRAW_IMAGE_ROTATED_ON_IMAGE,
    NULL0_OP_DRAW_IMAGE_FLIPPED_ON_IMAGE,
    NULL0_OP_DRAW_IMAGE_SCALED_ON_IMAGE,
    NULL0_OP_DRAW_TEXT_ON_IMAGE,
    NULL0_OP_DRAW_RECTANGLE_OUTLINE,
    NULL0_OP_DRAW_TRIANGLE_OUTLINE,
    NULL0_OP_DRAW_ELLIPSE_OUTLINE,
    NULL0_OP_DRAW_CIRCLE_OUTLINE,
    NULL0_OP_DRAW_POLYGON_OUTLINE,
    NULL0_OP_DRAW_ARC_OUTLINE,
    NULL0_OP_DRAW_RECTANGLE_ROUNDED_OUTLINE,
    NULL0_OP_DRAW_RECTANGLE_OUTLINE_ON_IMAGE,
    NULL0_OP_DRAW_TRIANGLE_OUTLINE_ON_IMAGE,
    NULL0_OP_DRAW_ELLIPSE_OUTLINE_ON_IMAGE,
    NULL0_OP_DRAW_CIRCLE_OUTLINE_ON_IMAGE,
    NULL0_OP_DRAW_POLYGON_OUTLINE_ON_IMAGE,
    NULL0_OP_DRAW_RECTANGLE_ROUNDED_OUTLINE_ON_IMAGE,
    NULL0_OP_FILE_READ,
    NULL0_OP_FILE_WRITE,
    NULL0_OP_FILE_APPEND,
    NULL0_OP_FILE_INFO,
    NULL0_OP_GET_WRITE_DIR,
    NULL0_OP_COLOR_TINT,
    NULL0_OP_COLOR_FADE,
    NULL0_OP_COLOR_BRIGHTNESS,
    NULL0_OP_COLOR_INVERT,
    NULL0_OP_COLOR_ALPHA_BLEND,
    NULL0_OP_COLOR_CONTRAST,
    NULL0_OP_COLOR_BILINEAR_INTERPOLATE
} Null0Op;


void null0_call(Null0Op op) {
  cart_shared_arg_offset = 0;
  cart_shared_ret_offset = 0;

  switch(op) {
    case NULL0_OP_TRACE: {
      null0_trace(cart_get_arg_string());
      break;
    }
    case NULL0_OP_CURRENT_TIME: {
      cart_set_ret_u64(null0_current_time());
      break;
    }
    case NULL0_OP_DELTA_TIME: {
      cart_set_ret_f32(null0_delta_time());
      break;
    }
    case NULL0_OP_RANDOM_INT: {
      cart_set_ret_i32(null0_random_int(cart_get_arg_i32(), cart_get_arg_i32()));
      break;
    }
    case NULL0_OP_LOAD_SOUND: {
      cart_set_ret_u32(null0_load_sound(cart_get_arg_string()));
      break;
    }
    case NULL0_OP_PLAY_SOUND: {
      null0_play_sound(cart_get_arg_u32(), cart_get_arg_bool());
      break;
    }
    case NULL0_OP_STOP_SOUND: {
      null0_stop_sound(cart_get_arg_u32());
      break;
    }
    case NULL0_OP_NEW_SFX: {
      cart_set_ret_u32(null0_new_sfx(cart_get_arg_SfxParams_pointer()));
      break;
    }
    case NULL0_OP_PRESET_SFX: {
      null0_preset_sfx(cart_get_arg_SfxParams_pointer(), cart_get_arg_u32());
      break;
    }
    case NULL0_OP_RANDOMIZE_SFX: {
      null0_randomize_sfx(cart_get_arg_SfxParams_pointer(), cart_get_arg_u32());
      break;
    }
    case NULL0_OP_MUTATE_SFX: {
      null0_mutate_sfx(cart_get_arg_SfxParams_pointer(), cart_get_arg_f32(), cart_get_arg_u32());
      break;
    }
    case NULL0_OP_LOAD_SFX: {
      null0_load_sfx(cart_get_arg_SfxParams_pointer(), cart_get_arg_string());
      break;
    }
    case NULL0_OP_UNLOAD_SOUND: {
      null0_unload_sound(cart_get_arg_u32());
      break;
    }
    case NULL0_OP_KEY_PRESSED: {
      cart_set_ret_bool(null0_key_pressed(cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_KEY_DOWN: {
      cart_set_ret_bool(null0_key_down(cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_KEY_RELEASED: {
      cart_set_ret_bool(null0_key_released(cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_KEY_UP: {
      cart_set_ret_bool(null0_key_up(cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_GAMEPAD_BUTTON_PRESSED: {
      cart_set_ret_bool(null0_gamepad_button_pressed(cart_get_arg_i32(), cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_GAMEPAD_BUTTON_DOWN: {
      cart_set_ret_bool(null0_gamepad_button_down(cart_get_arg_i32(), cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_GAMEPAD_BUTTON_RELEASED: {
      cart_set_ret_bool(null0_gamepad_button_released(cart_get_arg_i32(), cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_MOUSE_POSITION: {
      cart_set_ret_Vector(null0_mouse_position());
      break;
    }
    case NULL0_OP_MOUSE_BUTTON_PRESSED: {
      cart_set_ret_bool(null0_mouse_button_pressed(cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_MOUSE_BUTTON_DOWN: {
      cart_set_ret_bool(null0_mouse_button_down(cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_MOUSE_BUTTON_RELEASED: {
      cart_set_ret_bool(null0_mouse_button_released(cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_MOUSE_BUTTON_UP: {
      cart_set_ret_bool(null0_mouse_button_up(cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_NEW_IMAGE: {
      cart_set_ret_u32(null0_new_image(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color()));
      break;
    }
    case NULL0_OP_IMAGE_COPY: {
      cart_set_ret_u32(null0_image_copy(cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_IMAGE_SUBIMAGE: {
      cart_set_ret_u32(null0_image_subimage(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32()));
      break;
    }
    case NULL0_OP_CLEAR: {
      null0_clear(cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_POINT: {
      null0_draw_point(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_LINE: {
      null0_draw_line(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_RECTANGLE: {
      null0_draw_rectangle(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_TRIANGLE: {
      null0_draw_triangle(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_ELLIPSE: {
      null0_draw_ellipse(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_CIRCLE: {
      null0_draw_circle(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_POLYGON: {
      cart_handle_edgecase_draw_polygon();
    break;
  }
    case NULL0_OP_DRAW_POLYLINE: {
      cart_handle_edgecase_draw_polyline();
    break;
  }
    case NULL0_OP_DRAW_ARC: {
      null0_draw_arc(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_RECTANGLE_ROUNDED: {
      null0_draw_rectangle_rounded(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_IMAGE: {
      null0_draw_image(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32());
      break;
    }
    case NULL0_OP_DRAW_IMAGE_TINT: {
      null0_draw_image_tint(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_IMAGE_ROTATED: {
      null0_draw_image_rotated(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_u32());
      break;
    }
    case NULL0_OP_DRAW_IMAGE_FLIPPED: {
      null0_draw_image_flipped(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_bool(), cart_get_arg_bool(), cart_get_arg_bool());
      break;
    }
    case NULL0_OP_DRAW_IMAGE_SCALED: {
      null0_draw_image_scaled(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_u32());
      break;
    }
    case NULL0_OP_DRAW_TEXT: {
      null0_draw_text(cart_get_arg_u32(), cart_get_arg_string(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_SAVE_IMAGE: {
      null0_save_image(cart_get_arg_u32(), cart_get_arg_string());
      break;
    }
    case NULL0_OP_LOAD_IMAGE: {
      cart_set_ret_u32(null0_load_image(cart_get_arg_string()));
      break;
    }
    case NULL0_OP_IMAGE_RESIZE: {
      null0_image_resize(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_IMAGE_SCALE: {
      null0_image_scale(cart_get_arg_u32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_u32());
      break;
    }
    case NULL0_OP_IMAGE_COLOR_REPLACE: {
      null0_image_color_replace(cart_get_arg_u32(), cart_get_arg_Color(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_IMAGE_COLOR_TINT: {
      null0_image_color_tint(cart_get_arg_u32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_IMAGE_COLOR_FADE: {
      null0_image_color_fade(cart_get_arg_u32(), cart_get_arg_f32());
      break;
    }
    case NULL0_OP_FONT_COPY: {
      cart_set_ret_u32(null0_font_copy(cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_FONT_SCALE: {
      cart_set_ret_u32(null0_font_scale(cart_get_arg_u32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_LOAD_FONT_BMF: {
      cart_set_ret_u32(null0_load_font_bmf(cart_get_arg_string(), cart_get_arg_string()));
      break;
    }
    case NULL0_OP_LOAD_FONT_BMF_FROM_IMAGE: {
      cart_set_ret_u32(null0_load_font_bmf_from_image(cart_get_arg_u32(), cart_get_arg_string()));
      break;
    }
    case NULL0_OP_MEASURE_TEXT: {
      cart_set_ret_Dimensions(null0_measure_text(cart_get_arg_u32(), cart_get_arg_string()));
      break;
    }
    case NULL0_OP_MEASURE_IMAGE: {
      cart_set_ret_Dimensions(null0_measure_image(cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_LOAD_FONT_TTY: {
      cart_set_ret_u32(null0_load_font_tty(cart_get_arg_string(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_string()));
      break;
    }
    case NULL0_OP_LOAD_FONT_TTY_FROM_IMAGE: {
      cart_set_ret_u32(null0_load_font_tty_from_image(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_string()));
      break;
    }
    case NULL0_OP_LOAD_FONT_TTF: {
      cart_set_ret_u32(null0_load_font_ttf(cart_get_arg_string(), cart_get_arg_i32()));
      break;
    }
    case NULL0_OP_IMAGE_COLOR_INVERT: {
      null0_image_color_invert(cart_get_arg_u32());
      break;
    }
    case NULL0_OP_IMAGE_ALPHA_BORDER: {
      cart_set_ret_Rectangle(null0_image_alpha_border(cart_get_arg_u32(), cart_get_arg_f32()));
      break;
    }
    case NULL0_OP_IMAGE_CROP: {
      null0_image_crop(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32());
      break;
    }
    case NULL0_OP_IMAGE_ALPHA_CROP: {
      null0_image_alpha_crop(cart_get_arg_u32(), cart_get_arg_f32());
      break;
    }
    case NULL0_OP_IMAGE_COLOR_BRIGHTNESS: {
      null0_image_color_brightness(cart_get_arg_u32(), cart_get_arg_f32());
      break;
    }
    case NULL0_OP_IMAGE_FLIP: {
      null0_image_flip(cart_get_arg_u32(), cart_get_arg_bool(), cart_get_arg_bool());
      break;
    }
    case NULL0_OP_IMAGE_COLOR_CONTRAST: {
      null0_image_color_contrast(cart_get_arg_u32(), cart_get_arg_f32());
      break;
    }
    case NULL0_OP_IMAGE_ALPHA_MASK: {
      null0_image_alpha_mask(cart_get_arg_u32(), cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32());
      break;
    }
    case NULL0_OP_IMAGE_ROTATE: {
      cart_set_ret_u32(null0_image_rotate(cart_get_arg_u32(), cart_get_arg_f32(), cart_get_arg_u32()));
      break;
    }
    case NULL0_OP_IMAGE_GRADIENT: {
      cart_set_ret_u32(null0_image_gradient(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color(), cart_get_arg_Color(), cart_get_arg_Color(), cart_get_arg_Color()));
      break;
    }
    case NULL0_OP_UNLOAD_IMAGE: {
      null0_unload_image(cart_get_arg_u32());
      break;
    }
    case NULL0_OP_UNLOAD_FONT: {
      null0_unload_font(cart_get_arg_u32());
      break;
    }
    case NULL0_OP_CLEAR_ON_IMAGE: {
      null0_clear_on_image(cart_get_arg_u32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_POINT_ON_IMAGE: {
      null0_draw_point_on_image(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_LINE_ON_IMAGE: {
      null0_draw_line_on_image(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_RECTANGLE_ON_IMAGE: {
      null0_draw_rectangle_on_image(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_TRIANGLE_ON_IMAGE: {
      null0_draw_triangle_on_image(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_ELLIPSE_ON_IMAGE: {
      null0_draw_ellipse_on_image(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_CIRCLE_ON_IMAGE: {
      null0_draw_circle_on_image(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_POLYGON_ON_IMAGE: {
      cart_handle_edgecase_draw_polygon_on_image();
    break;
  }
    case NULL0_OP_DRAW_POLYLINE_ON_IMAGE: {
      cart_handle_edgecase_draw_polyline_on_image();
    break;
  }
    case NULL0_OP_DRAW_RECTANGLE_ROUNDED_ON_IMAGE: {
      null0_draw_rectangle_rounded_on_image(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_IMAGE_ON_IMAGE: {
      null0_draw_image_on_image(cart_get_arg_u32(), cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32());
      break;
    }
    case NULL0_OP_DRAW_IMAGE_TINT_ON_IMAGE: {
      null0_draw_image_tint_on_image(cart_get_arg_u32(), cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_IMAGE_ROTATED_ON_IMAGE: {
      null0_draw_image_rotated_on_image(cart_get_arg_u32(), cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_u32());
      break;
    }
    case NULL0_OP_DRAW_IMAGE_FLIPPED_ON_IMAGE: {
      null0_draw_image_flipped_on_image(cart_get_arg_u32(), cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_bool(), cart_get_arg_bool(), cart_get_arg_bool());
      break;
    }
    case NULL0_OP_DRAW_IMAGE_SCALED_ON_IMAGE: {
      null0_draw_image_scaled_on_image(cart_get_arg_u32(), cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_u32());
      break;
    }
    case NULL0_OP_DRAW_TEXT_ON_IMAGE: {
      null0_draw_text_on_image(cart_get_arg_u32(), cart_get_arg_u32(), cart_get_arg_string(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_RECTANGLE_OUTLINE: {
      null0_draw_rectangle_outline(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_TRIANGLE_OUTLINE: {
      null0_draw_triangle_outline(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_ELLIPSE_OUTLINE: {
      null0_draw_ellipse_outline(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_CIRCLE_OUTLINE: {
      null0_draw_circle_outline(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_POLYGON_OUTLINE: {
      cart_handle_edgecase_draw_polygon_outline();
    break;
  }
    case NULL0_OP_DRAW_ARC_OUTLINE: {
      null0_draw_arc_outline(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_f32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_RECTANGLE_ROUNDED_OUTLINE: {
      null0_draw_rectangle_rounded_outline(cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_RECTANGLE_OUTLINE_ON_IMAGE: {
      null0_draw_rectangle_outline_on_image(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_TRIANGLE_OUTLINE_ON_IMAGE: {
      null0_draw_triangle_outline_on_image(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_ELLIPSE_OUTLINE_ON_IMAGE: {
      null0_draw_ellipse_outline_on_image(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_CIRCLE_OUTLINE_ON_IMAGE: {
      null0_draw_circle_outline_on_image(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_DRAW_POLYGON_OUTLINE_ON_IMAGE: {
      cart_handle_edgecase_draw_polygon_outline_on_image();
    break;
  }
    case NULL0_OP_DRAW_RECTANGLE_ROUNDED_OUTLINE_ON_IMAGE: {
      null0_draw_rectangle_rounded_outline_on_image(cart_get_arg_u32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_i32(), cart_get_arg_Color());
      break;
    }
    case NULL0_OP_FILE_READ: {
      cart_handle_edgecase_file_read();
    break;
  }
    case NULL0_OP_FILE_WRITE: {
      cart_handle_edgecase_file_write();
    break;
  }
    case NULL0_OP_FILE_APPEND: {
      cart_handle_edgecase_file_append();
    break;
  }
    case NULL0_OP_FILE_INFO: {
      cart_set_ret_FileInfo(null0_file_info(cart_get_arg_string()));
      break;
    }
    case NULL0_OP_GET_WRITE_DIR: {
      cart_set_ret_string(null0_get_write_dir());
      break;
    }
    case NULL0_OP_COLOR_TINT: {
      cart_set_ret_Color(null0_color_tint(cart_get_arg_Color(), cart_get_arg_Color()));
      break;
    }
    case NULL0_OP_COLOR_FADE: {
      cart_set_ret_Color(null0_color_fade(cart_get_arg_Color(), cart_get_arg_f32()));
      break;
    }
    case NULL0_OP_COLOR_BRIGHTNESS: {
      cart_set_ret_Color(null0_color_brightness(cart_get_arg_Color(), cart_get_arg_f32()));
      break;
    }
    case NULL0_OP_COLOR_INVERT: {
      cart_set_ret_Color(null0_color_invert(cart_get_arg_Color()));
      break;
    }
    case NULL0_OP_COLOR_ALPHA_BLEND: {
      cart_set_ret_Color(null0_color_alpha_blend(cart_get_arg_Color(), cart_get_arg_Color()));
      break;
    }
    case NULL0_OP_COLOR_CONTRAST: {
      cart_set_ret_Color(null0_color_contrast(cart_get_arg_Color(), cart_get_arg_f32()));
      break;
    }
    case NULL0_OP_COLOR_BILINEAR_INTERPOLATE: {
      cart_set_ret_Color(null0_color_bilinear_interpolate(cart_get_arg_Color(), cart_get_arg_Color(), cart_get_arg_Color(), cart_get_arg_Color(), cart_get_arg_f32(), cart_get_arg_f32()));
      break;
    }
    default:
      fprintf(stderr, "Unknown op: %d\n", op);
  }
}