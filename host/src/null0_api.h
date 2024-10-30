#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define CVECTOR_LOGARITHMIC_GROWTH
#include "cvector.h"
#include "physfs.h"

static unsigned char* wasmBytes;
static long wasmSize;

// I define these here for pntr to use
unsigned char* null0_file_read(const char* filename, unsigned int* bytesRead);
bool null0_file_write(const char* filename, const unsigned char* data, unsigned int* bytesToWrite);

#define PNTR_LOAD_FILE null0_file_read
#define PNTR_SAVE_FILE null0_file_write

#define PNTR_ENABLE_MATH
#define PNTR_ENABLE_JPEG
#define PNTR_IMPLEMENTATION
#define PNTR_APP_IMPLEMENTATION
#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_ENABLE_TTF
#include <pntr.h>
#include <pntr_app.h>

#define PNTR_APP_SFX_IMPLEMENTATION
#include "pntr_app_sfx.h"

// these are only availble in this file, used to make all the null0 API work
static pntr_app* null0_app;
static pntr_image** images = NULL;
static pntr_sound** sounds = NULL;
static pntr_font** fonts = NULL;

// these helpers are used externally to get access to stuff
pntr_image* null0_getscreen() {
  return images[0];
}
long null0_getWasmSize() {
  return wasmSize;
}
unsigned char* null0_getwasmBytes(){
  return wasmBytes;
}

typedef struct {
  unsigned int width;
  unsigned int height;
} Null0Dimension;

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

typedef enum {
  CART_UNKNOWN,
  CART_WASM,
  CART_ZIP
} Nul0CartType;

typedef enum SfxWaveType SfxWaveType;

void null0_trace(const char* text);
uint64_t null0_current_time(void);
float null0_delta_time(void);
int null0_random_int(int min, int max);
unsigned int null0_load_sound(const char* filename);
void null0_play_sound(unsigned int sound, bool loop);
void null0_stop_sound(unsigned int sound);
unsigned int null0_new_sfx(const SfxParams* params);
void null0_preset_sfx(SfxParams* params, SfxPresetType preset);
void null0_randomize_sfx(SfxParams* params, unsigned int seed);
void null0_mutate_sfx(SfxParams* params, float amount, unsigned int seed);
void null0_load_sfx(SfxParams* params, const char* filename);
void null0_unload_sound(unsigned int sound);
bool null0_key_pressed(pntr_app_key key);
bool null0_key_down(pntr_app_key key);
bool null0_key_released(pntr_app_key key);
bool null0_key_up(pntr_app_key key);
bool null0_gamepad_button_pressed(int gamepad, pntr_app_gamepad_button button);
bool null0_gamepad_button_down(int gamepad, pntr_app_gamepad_button button);
bool null0_gamepad_button_released(int gamepad, pntr_app_gamepad_button button);
pntr_vector null0_mouse_position(void);
bool null0_mouse_button_pressed(pntr_app_mouse_button button);
bool null0_mouse_button_down(pntr_app_mouse_button button);
bool null0_mouse_button_released(pntr_app_mouse_button button);
bool null0_mouse_button_up(pntr_app_mouse_button button);
unsigned int null0_new_image(int width, int height, pntr_color color);
unsigned int null0_image_copy(unsigned int image);
unsigned int null0_image_subimage(unsigned int image, int x, int y, int width, int height);
void null0_clear(pntr_color color) {
  pntr_clear_background(images[0], color);
}
void null0_draw_point(int x, int y, pntr_color color);
void null0_draw_line(int x1, int y1, int x2, int y2, pntr_color color);
void null0_draw_rectangle(int x, int y, int width, int height, pntr_color color);
void null0_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, pntr_color color);
void null0_draw_circle(int x, int y, int radius, pntr_color color) {
  pntr_draw_circle_fill(images[0], x, y, radius, color);
}
void null0_draw_ellipse(int x, int y, int width, int height, pntr_color color);
void null0_draw_polygon(const pntr_vector* points, pntr_color color);
void null0_draw_polyline(const pntr_vector* points, pntr_color color);
void null0_draw_arc(int x, int y, float startAngle, float endAngle, float radius, int segments, pntr_color color);
void null0_draw_rectangle_rounded(int x, int y, int width, int height, int radius, pntr_color color);
bool null0_file_append(const char* filename, const unsigned char* data);
PHYSFS_Stat null0_file_info(const char* filename);
char** null0_file_list(const char* path);
const char* null0_get_write_dir(void);
pntr_color null0_color_tint(pntr_color color, pntr_color tint);
pntr_color null0_color_fade(pntr_color color, float alpha);
pntr_color null0_color_brightness(pntr_color color, float factor);
pntr_color null0_color_invert(pntr_color color);
pntr_color null0_color_alpha_blend(pntr_color dst, pntr_color src);
pntr_color null0_color_contrast(pntr_color color, float contrast);
pntr_color null0_color_bilinear_interpolate(pntr_color c00, pntr_color c10, pntr_color c01, pntr_color c11, float tx, float ty);

bool null0_file_write(const char* filename, const unsigned char* data, unsigned int* bytesToWrite) {
  return false;
}

// Read a file from cart
unsigned char* null0_file_read(const char* filename, unsigned int* bytesRead) {
  PHYSFS_File* f = PHYSFS_openRead(filename);
  PHYSFS_Stat i = {};
  PHYSFS_stat(filename, &i);
  unsigned char* b = (unsigned char*)malloc(i.filesize);
  PHYSFS_sint64 br = PHYSFS_readBytes(f, b, i.filesize);
  *bytesRead = br;
  PHYSFS_close(f);
  return b;
}

Nul0CartType null0_detect_cart_type(unsigned char* bytes) {
  if (bytes[0] == 0x00 && bytes[1] == 0x61 && bytes[2] == 0x73 && bytes[3] == 0x6D) {
    return CART_WASM;
  }
  if ((bytes[0] == 0x50 && bytes[1] == 0x4B && bytes[2] == 0x03 && bytes[3] == 0x04) ||
    (bytes[0] == 0x50 && bytes[1] == 0x4B && bytes[2] == 0x05 && bytes[3] == 0x06) ||
    (bytes[0] == 0x50 && bytes[1] == 0x4B && bytes[2] == 0x07 && bytes[3] == 0x08)) {
    return CART_ZIP;
  }
  return CART_UNKNOWN;
}

int null0_cart_setup(char* cart, pntr_app* app) {
  unsigned char* fourbytes = malloc(4);
  FILE* f = fopen(cart, "rb");
  if (f == NULL) {
    fprintf(stderr, "Could not open %s.\n", cart);
    return 1;
  }
  fread(fourbytes, 4, 1, f);
  fclose(f);
  Nul0CartType ctype = null0_detect_cart_type(fourbytes);

  if (ctype == CART_UNKNOWN) {
    fprintf(stderr, "%s is unknown file-format. Use zip or wasm.\n", cart);
    return 1;
  }

  if (!PHYSFS_init("/")) {
    fprintf(stderr, "Could not init filesystem.\n");
    return 1;
  }

  if (ctype == CART_ZIP) {
    if (!PHYSFS_mount(cart, NULL, 1)) {
      PHYSFS_deinit();
      fprintf(stderr, "Could not mount filesystem from %s.\n", cart);
      return 1;
    }
    unsigned int bytesRead = 0;
    wasmBytes = null0_file_read("main.wasm", &bytesRead);
    if (bytesRead == 0 || null0_detect_cart_type(wasmBytes) != CART_WASM) {
      PHYSFS_deinit();
      fprintf(stderr, "Could not find valid main.wasm in %s.\n", cart);
      return 1;
    }
    wasmSize = (long)bytesRead;
  } else {
    FILE* fp = fopen(cart, "rb");
    if (fp == NULL) {
      PHYSFS_deinit();
      fprintf(stderr, "Could not open %s.\n", cart);
      return 1;
    }
    fseek(fp, 0L, SEEK_END);
    wasmSize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    wasmBytes = (unsigned char*)malloc(wasmSize);
    fread(wasmBytes, sizeof(char), wasmSize, fp);
    fclose(fp);
  }

  null0_app = app;

  // screen is images[0]
  cvector_push_back(images, app->screen);

  // default font is fonts[0]
  cvector_push_back(fonts, pntr_load_font_default());

  return 0;
}

