// this will generate the wamr host router (used in emscripten and WAMR)

import fs from 'fs/promises'
import { glob } from 'glob'
import YAML from 'yaml'

const out = []

out.push(`// Host function-call router for null0.
// Generated on ${new Date()}

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

`)

const routerOutput = []
const ops = []

// Single loop to process API files
for (const y of await glob('api/**/*.yml')) {
  const api = YAML.parse(await fs.readFile(y, 'utf8'))
  const [, catName] = /^api\/(.+)\.yml/g.exec(y)

  // Process each function in the API
  for (const [fname, fdef] of Object.entries(api)) {
    // Add to ops enum list
    ops.push(`NULL0_OP_${fname.toUpperCase()}`)

    // Generate router case
    routerOutput.push(`    case NULL0_OP_${fname.toUpperCase()}: {`)

    // handle edge-cases
    if (fname === 'file_read') {
      routerOutput.push(`      cart_handle_edgecase_file_read();
    break;
  }`)
      continue
    }

    if (fname === 'file_write') {
      routerOutput.push(`      cart_handle_edgecase_file_write();
    break;
  }`)
      continue
    }

    if (fname === 'file_append') {
      routerOutput.push(`      cart_handle_edgecase_file_append();
    break;
  }`)
      continue
    }

    if (fname === 'draw_polygon') {
      routerOutput.push(`      cart_handle_edgecase_draw_polygon();
    break;
  }`)
      continue
    }

    if (fname === 'draw_polygon_on_image') {
      routerOutput.push(`      cart_handle_edgecase_draw_polygon_on_image();
    break;
  }`)
      continue
    }

    if (fname === 'draw_polyline') {
      routerOutput.push(`      cart_handle_edgecase_draw_polyline();
    break;
  }`)
      continue
    }

    if (fname === 'draw_polyline_on_image') {
      routerOutput.push(`      cart_handle_edgecase_draw_polyline_on_image();
    break;
  }`)
      continue
    }

    if (fname === 'draw_polygon_outline') {
      routerOutput.push(`      cart_handle_edgecase_draw_polygon_outline();
    break;
  }`)
      continue
    }

    if (fname === 'draw_polygon_outline_on_image') {
      routerOutput.push(`      cart_handle_edgecase_draw_polygon_outline_on_image();
    break;
  }`)
      continue
    }

    // Generate argument collection
    const args = []
    let sizeArg
    if (fdef.args) {
      for (const [argName, argType] of Object.entries(fdef.args)) {
        switch (argType) {
          case 'string':
            args.push(`cart_get_arg_string()`)
            break
          case 'i32':
            args.push(`cart_get_arg_i32()`)
            break
          case 'u32':
            args.push(`cart_get_arg_u32()`)
            break
          case 'f32':
            args.push(`cart_get_arg_f32()`)
            break
          case 'bool':
            args.push(`cart_get_arg_bool()`)
            break
          case 'Color':
            args.push(`cart_get_arg_Color()`)
            break
          case 'Image':
            args.push(`cart_get_arg_u32()`)
            break
          case 'Font':
            args.push(`cart_get_arg_u32()`)
            break
          case 'Vector[]':
            // use previous arg as size
            sizeArg = args.pop()
            args.push(`cart_get_arg_Vector_array(${sizeArg})`) // Assumes length is previous arg
            break
          case 'ImageFilter':
            args.push(`cart_get_arg_u32()`)
            break
          case 'Sound':
            args.push(`cart_get_arg_u32()`)
            break
          case 'SfxParams*':
            args.push(`cart_get_arg_SfxParams_pointer()`)
            break
          case 'SfxPresetType':
            args.push(`cart_get_arg_u32()`)
            break
          case 'SfxWaveType':
            args.push(`cart_get_arg_u32()`)
            break
          case 'Key':
            args.push(`cart_get_arg_u32()`)
            break
          case 'GamepadButton':
            args.push(`cart_get_arg_u32()`)
            break
          case 'MouseButton':
            args.push(`cart_get_arg_u32()`)
            break
          case 'u32*':
            args.push(`cart_get_arg_u32_pointer()`)
            break
          case 'bytes':
            // use previous arg as size
            sizeArg = args.pop()
            args.push(`cart_get_arg_bytes(${sizeArg})`)
            break
          default:
            console.warn(`Unknown type: ${argType} in ${fname}`)
            args.push(`cart_get_arg_u32()`) // fallback
        }
      }
    }

    // Generate function call and return value handling
    if (fdef.returns && fdef.returns !== 'void') {
      const funcCall = `null0_${fname}(${args.join(', ')})`
      switch (fdef.returns) {
        case 'Image':
        case 'Font':
        case 'u32':
          routerOutput.push(`      cart_set_ret_u32(${funcCall});`)
          break
        case 'i32':
          routerOutput.push(`      cart_set_ret_i32(${funcCall});`)
          break
        case 'f32':
          routerOutput.push(`      cart_set_ret_f32(${funcCall});`)
          break
        case 'bool':
          routerOutput.push(`      cart_set_ret_bool(${funcCall});`)
          break
        case 'Color':
          routerOutput.push(`      cart_set_ret_Color(${funcCall});`)
          break
        case 'Dimensions':
          routerOutput.push(`      cart_set_ret_Dimensions(${funcCall});`)
          break
        case 'Rectangle':
          routerOutput.push(`      cart_set_ret_Rectangle(${funcCall});`)
          break
        case 'u64':
          routerOutput.push(`      cart_set_ret_u64(${funcCall});`)
          break
        case 'Sound':
          routerOutput.push(`      cart_set_ret_u32(${funcCall});`)
          break
        case 'Vector':
          routerOutput.push(`      cart_set_ret_Vector(${funcCall});`)
          break
        case 'bytes':
          routerOutput.push(`      cart_set_ret_bytes(${funcCall}, len);`) // Assumes len is available
          break
        case 'FileInfo':
          routerOutput.push(`      cart_set_ret_FileInfo(${funcCall});`)
          break
        case 'string':
          routerOutput.push(`      cart_set_ret_string(${funcCall});`)
          break
        default:
          console.warn(`Unknown return type: ${fdef.returns} in ${fname}`)
          routerOutput.push(`      cart_set_ret_u32(${funcCall});`)
      }
    } else {
      routerOutput.push(`      null0_${fname}(${args.join(', ')});`)
    }

    routerOutput.push(`      break;
    }`)
  }
}

// Add enum definition to main output
out.push(`
typedef enum {
  ${ops.map((o) => `  ${o}`).join(',\n  ')}
} Null0Op;
`)

// Add router definition to main output
out.push(`
void null0_call(Null0Op op) {
  cart_shared_arg_offset = 0;
  cart_shared_ret_offset = 0;

  switch(op) {
${routerOutput.join('\n')}
    default:
      fprintf(stderr, "Unknown op: %d\\n", op);
  }
}`)

await fs.writeFile('host/src/null0_router.h', out.join('\n'))
