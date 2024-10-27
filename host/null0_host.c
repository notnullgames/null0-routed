
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>

// Shared memory pointer
void* shared_pointer() {
  return (void*) &_shared_mem;
}

unsigned char* copy_bytes_from_cart(unsigned int offset, unsigned int size){
  unsigned char* ret = malloc(size);
  memcpy(ret, (unsigned char*) (&_shared_mem + offset), size);
  return ret;
}

// Memory copying functions
EM_JS(void, __copy_bytes_to_cart, (void* val, unsigned int offset, unsigned int size), {
  for (let i=0;i<size;i++) {
    Module.cart.view.setUint8(offset + Module.cart.shared_loc + i, Module.HEAPU8[offset + Module.shared_loc + i])
  }
});
#else
void __copy_bytes_to_cart(void* val, unsigned int offset, unsigned int size){
  // TODO: implement for WAMR
}
#endif

void copy_bytes_to_cart(void* val, unsigned int offset, unsigned int size) {
  memcpy(&_shared_mem, val, size);
  __copy_bytes_to_cart(val, offset, size);
}

void call(Op op) {
  cart_shared_arg_offset = 0;
  cart_shared_ret_offset = 0;

  switch(op) {
    case OP_TRACE:
      null0_trace(get_char_arg());
      break;

    case OP_CURRENT_TIME:
      null0_current_time();
      break;

    case OP_DELTA_TIME:
      set_float_ret(null0_delta_time());
      break;

    case OP_RANDOM_INT:
      set_int_ret(null0_random_int(get_int_arg(),
      get_int_arg()));
      break;

    case OP_LOAD_SOUND:
      set_int_ret(null0_load_sound(get_char_arg()));
      break;

    case OP_PLAY_SOUND:
      null0_play_sound(get_int_arg(),
      get_bool_arg());
      break;

    case OP_STOP_SOUND:
      null0_stop_sound(get_int_arg());
      break;

    case OP_NEW_SFX:
      set_int_ret(null0_new_sfx(get_SfxParams_arg()));
      break;

    case OP_PRESET_SFX:
      null0_preset_sfx(get_SfxParams_arg(),
      get_SfxPresetType_arg());
      break;

    case OP_RANDOMIZE_SFX:
      null0_randomize_sfx(get_SfxParams_arg(),
      get_SfxWaveType_arg());
      break;

    case OP_MUTATE_SFX:
      null0_mutate_sfx(get_SfxParams_arg(),
      get_float_arg(),
      get_int_arg());
      break;

    case OP_LOAD_SFX:
      null0_load_sfx(get_SfxParams_arg(),
      get_char_arg());
      break;

    case OP_UNLOAD_SOUND:
      null0_unload_sound(get_int_arg());
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
      set_bool_ret(null0_gamepad_button_pressed(get_int_arg(),
      get_GamepadButton_arg()));
      break;

    case OP_GAMEPAD_BUTTON_DOWN:
      set_bool_ret(null0_gamepad_button_down(get_int_arg(),
      get_GamepadButton_arg()));
      break;

    case OP_GAMEPAD_BUTTON_RELEASED:
      set_bool_ret(null0_gamepad_button_released(get_int_arg(),
      get_GamepadButton_arg()));
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
      set_int_ret(null0_new_image(get_int_arg(),
      get_int_arg(),
      get_Color_arg()));
      break;

    case OP_IMAGE_COPY:
      set_int_ret(null0_image_copy(get_int_arg()));
      break;

    case OP_IMAGE_SUBIMAGE:
      set_int_ret(null0_image_subimage(get_int_arg(),
      get_int_arg(),
      get_int_arg(),
      get_int_arg(),
      get_int_arg()));
      break;

    case OP_CLEAR:
      null0_clear(get_Color_arg());
      break;

    case OP_DRAW_POINT:
        null0_draw_point(get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_LINE:
      null0_draw_line(get_int_arg(),
      get_int_arg(),
      get_int_arg(),
      get_int_arg(),
      get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE:
null0_draw_rectangle(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_TRIANGLE:
null0_draw_triangle(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_ELLIPSE:
null0_draw_ellipse(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_CIRCLE:
null0_draw_circle(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_POLYGON:
null0_draw_polygon(get_Vector_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_POLYLINE:
null0_draw_polyline(get_Vector_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_ARC:
null0_draw_arc(get_int_arg(),
        get_int_arg(),
        get_float_arg(),
        get_float_arg(),
        get_float_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE_ROUNDED:
null0_draw_rectangle_rounded(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_IMAGE:
null0_draw_image(get_int_arg(),
        get_int_arg(),
        get_int_arg());
      break;

    case OP_DRAW_IMAGE_TINT:
null0_draw_image_tint(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_IMAGE_ROTATED:
null0_draw_image_rotated(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_float_arg(),
        get_float_arg(),
        get_float_arg(),
        get_ImageFilter_arg());
      break;

    case OP_DRAW_IMAGE_FLIPPED:
null0_draw_image_flipped(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_bool_arg(),
        get_bool_arg(),
        get_bool_arg());
      break;

    case OP_DRAW_IMAGE_SCALED:
null0_draw_image_scaled(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_float_arg(),
        get_float_arg(),
        get_float_arg(),
        get_float_arg(),
        get_ImageFilter_arg());
      break;

    case OP_DRAW_TEXT:
null0_draw_text(get_int_arg(),
        get_char_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_SAVE_IMAGE:
null0_save_image(get_int_arg(),
        get_char_arg());
      break;

    case OP_LOAD_IMAGE:
      set_int_ret(null0_load_image(get_char_arg()));
      break;

    case OP_IMAGE_RESIZE:
null0_image_resize(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_IMAGE_SCALE:
null0_image_scale(get_int_arg(),
        get_float_arg(),
        get_float_arg(),
        get_ImageFilter_arg());
      break;

    case OP_IMAGE_COLOR_REPLACE:
null0_image_color_replace(get_int_arg(),
        get_Color_arg(),
        get_Color_arg());
      break;

    case OP_IMAGE_COLOR_TINT:
null0_image_color_tint(get_int_arg(),
        get_Color_arg());
      break;

    case OP_IMAGE_COLOR_FADE:
null0_image_color_fade(get_int_arg(),
        get_float_arg());
      break;

    case OP_FONT_COPY:
      set_int_ret(null0_font_copy(get_int_arg()));
      break;

    case OP_FONT_SCALE:
      set_int_ret(null0_font_scale(get_int_arg(),
        get_float_arg(),
        get_float_arg(),
        get_ImageFilter_arg()));
      break;

    case OP_LOAD_FONT_BMF:
      set_int_ret(null0_load_font_bmf(get_char_arg(),
        get_char_arg()));
      break;

    case OP_LOAD_FONT_BMF_FROM_IMAGE:
      set_int_ret(null0_load_font_bmf_from_image(get_int_arg(),
        get_char_arg()));
      break;

    case OP_MEASURE_TEXT:
      set_Dimensions_ret(null0_measure_text(get_int_arg(),
        get_char_arg()));
      break;

    case OP_MEASURE_IMAGE:
      set_Dimensions_ret(null0_measure_image(get_int_arg()));
      break;

    case OP_LOAD_FONT_TTY:
      set_int_ret(null0_load_font_tty(get_char_arg(),
        get_int_arg(),
        get_int_arg(),
        get_char_arg()));
      break;

    case OP_LOAD_FONT_TTY_FROM_IMAGE:
      set_int_ret(null0_load_font_tty_from_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_char_arg()));
      break;

    case OP_LOAD_FONT_TTF:
      set_int_ret(null0_load_font_ttf(get_char_arg(),
        get_int_arg()));
      break;

    case OP_IMAGE_COLOR_INVERT:
null0_image_color_invert(get_int_arg());
      break;

    case OP_IMAGE_ALPHA_BORDER:
      set_Rectangle_ret(null0_image_alpha_border(get_int_arg(),
        get_float_arg()));
      break;

    case OP_IMAGE_CROP:
null0_image_crop(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg());
      break;

    case OP_IMAGE_ALPHA_CROP:
null0_image_alpha_crop(get_int_arg(),
        get_float_arg());
      break;

    case OP_IMAGE_COLOR_BRIGHTNESS:
null0_image_color_brightness(get_int_arg(),
        get_float_arg());
      break;

    case OP_IMAGE_FLIP:
null0_image_flip(get_int_arg(),
        get_bool_arg(),
        get_bool_arg());
      break;

    case OP_IMAGE_COLOR_CONTRAST:
null0_image_color_contrast(get_int_arg(),
        get_float_arg());
      break;

    case OP_IMAGE_ALPHA_MASK:
null0_image_alpha_mask(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg());
      break;

    case OP_IMAGE_ROTATE:
      set_int_ret(null0_image_rotate(get_int_arg(),
        get_float_arg(),
        get_ImageFilter_arg()));
      break;

    case OP_IMAGE_GRADIENT:
      set_int_ret(null0_image_gradient(get_int_arg(),
        get_int_arg(),
        get_Color_arg(),
        get_Color_arg(),
        get_Color_arg(),
        get_Color_arg()));
      break;

    case OP_UNLOAD_IMAGE:
null0_unload_image(get_int_arg());
      break;

    case OP_UNLOAD_FONT:
null0_unload_font(get_int_arg());
      break;

    case OP_CLEAR_ON_IMAGE:
null0_clear_on_image(get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_POINT_ON_IMAGE:
null0_draw_point_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_LINE_ON_IMAGE:
null0_draw_line_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE_ON_IMAGE:
null0_draw_rectangle_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_TRIANGLE_ON_IMAGE:
null0_draw_triangle_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_ELLIPSE_ON_IMAGE:
null0_draw_ellipse_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_CIRCLE_ON_IMAGE:
null0_draw_circle_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_POLYGON_ON_IMAGE:
null0_draw_polygon_on_image(get_int_arg(),
        get_Vector_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_POLYLINE_ON_IMAGE:
null0_draw_polyline_on_image(get_int_arg(),
        get_Vector_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE_ROUNDED_ON_IMAGE:
null0_draw_rectangle_rounded_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_IMAGE_ON_IMAGE:
null0_draw_image_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg());
      break;

    case OP_DRAW_IMAGE_TINT_ON_IMAGE:
null0_draw_image_tint_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_IMAGE_ROTATED_ON_IMAGE:
null0_draw_image_rotated_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_float_arg(),
        get_float_arg(),
        get_float_arg(),
        get_ImageFilter_arg());
      break;

    case OP_DRAW_IMAGE_FLIPPED_ON_IMAGE:
null0_draw_image_flipped_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_bool_arg(),
        get_bool_arg(),
        get_bool_arg());
      break;

    case OP_DRAW_IMAGE_SCALED_ON_IMAGE:
null0_draw_image_scaled_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_float_arg(),
        get_float_arg(),
        get_float_arg(),
        get_float_arg(),
        get_ImageFilter_arg());
      break;

    case OP_DRAW_TEXT_ON_IMAGE:
null0_draw_text_on_image(get_int_arg(),
        get_int_arg(),
        get_char_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE_OUTLINE:
null0_draw_rectangle_outline(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_TRIANGLE_OUTLINE:
null0_draw_triangle_outline(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_ELLIPSE_OUTLINE:
null0_draw_ellipse_outline(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_CIRCLE_OUTLINE:
null0_draw_circle_outline(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_POLYGON_OUTLINE:
null0_draw_polygon_outline(get_Vector_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_ARC_OUTLINE:
null0_draw_arc_outline(get_int_arg(),
        get_int_arg(),
        get_float_arg(),
        get_float_arg(),
        get_float_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE_ROUNDED_OUTLINE:
null0_draw_rectangle_rounded_outline(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE_OUTLINE_ON_IMAGE:
null0_draw_rectangle_outline_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_TRIANGLE_OUTLINE_ON_IMAGE:
null0_draw_triangle_outline_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_ELLIPSE_OUTLINE_ON_IMAGE:
null0_draw_ellipse_outline_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_CIRCLE_OUTLINE_ON_IMAGE:
null0_draw_circle_outline_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_POLYGON_OUTLINE_ON_IMAGE:
null0_draw_polygon_outline_on_image(get_int_arg(),
        get_Vector_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_DRAW_RECTANGLE_ROUNDED_OUTLINE_ON_IMAGE:
null0_draw_rectangle_rounded_outline_on_image(get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_int_arg(),
        get_Color_arg());
      break;

    case OP_FILE_READ:
      string_ret(null0_file_read(get_char_arg(),
        get_int_arg()));
      break;

    case OP_FILE_WRITE:
      set_bool_ret(null0_file_write(get_char_arg(),
        get_char_arg(),
        get_int_arg()));
      break;

    case OP_FILE_APPEND:
      set_bool_ret(null0_file_append(get_char_arg(),
        get_char_arg(),
        get_int_arg()));
      break;

    case OP_FILE_INFO:
null0_file_info(get_char_arg());
      break;

    case OP_GET_WRITE_DIR:
      string_ret(null0_get_write_dir());
      break;

    case OP_COLOR_TINT:
      set_Color_ret(null0_color_tint(get_Color_arg(),
        get_Color_arg()));
      break;

    case OP_COLOR_FADE:
      set_Color_ret(null0_color_fade(get_Color_arg(),
        get_float_arg()));
      break;

    case OP_COLOR_BRIGHTNESS:
      set_Color_ret(null0_color_brightness(get_Color_arg(),
        get_float_arg()));
      break;

    case OP_COLOR_INVERT:
      set_Color_ret(null0_color_invert(get_Color_arg()));
      break;

    case OP_COLOR_ALPHA_BLEND:
      set_Color_ret(null0_color_alpha_blend(get_Color_arg(),
        get_Color_arg()));
      break;

    case OP_COLOR_CONTRAST:
      set_Color_ret(null0_color_contrast(get_Color_arg(),
        get_float_arg()));
      break;

    case OP_COLOR_BILINEAR_INTERPOLATE:
      set_Color_ret(null0_color_bilinear_interpolate(get_Color_arg(),
        get_Color_arg(),
        get_Color_arg(),
        get_Color_arg(),
        get_float_arg(),
        get_float_arg()));
      break;


    default:
      fprintf(stderr, "Unknown op: %d\n", op);
  }
}
