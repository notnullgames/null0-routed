import path from "path";
import fs from "fs/promises";
import YAML from "yaml";
import { glob } from "glob";

// Type mapping from YAML types to C types
const typeMap = {
  i32: "int",
  u32: "unsigned int",
  f32: "float",
  string: "char*",
  bool: "bool",
  void: "void",
  Image: "unsigned int", // Image handle
  Font: "unsigned int", // Font handle
  Color: "Color",
  Sound: "unsigned int",
  "Vector*": "Vector*",
  Rectangle: "Rectangle",
  Dimensions: "Dimensions",
  ImageFilter: "ImageFilter",
  "SfxParams*": "SfxParams*",
  SfxPresetType: "SfxPresetType",
  SfxWaveType: "SfxWaveType",
  Key: "Key",
  GamepadButton: "GamepadButton",
  MouseButton: "MouseButton",
  "u32*": "unsigned int*",
  bytes: "unsigned char*",
};

// Generate type getter function
function generateTypeGetter(type) {
  const baseName = type.replace("*", "").replace("unsigned ", "");
  return `${type} get_${baseName}_arg() {
    ${type}* ret = (${type}*)copy_bytes_from_cart(cart_shared_arg_offset, sizeof(${type}));
    cart_shared_arg_offset += sizeof(${type});
    printf("HOST get_${baseName}_arg: %p\\n", (void*)ret);
    return *ret;
}\n`;
}

// Generate type setter function
function generateTypeSetter(type) {
  const baseName = type.replace("*", "").replace("unsigned ", "");
  return `void set_${baseName}_ret(${type} value) {
    copy_bytes_to_cart((void*)&value, cart_shared_ret_offset, sizeof(value));
    cart_shared_ret_offset += sizeof(value);
    printf("HOST set_${baseName}_ret: %p\\n", (void*)&value);
}\n`;
}

async function generateCode(yamlFiles) {
  let output = `
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#define SHARED_MEM_SIZE 1024*1024
unsigned char _shared_mem[SHARED_MEM_SIZE] = {0};

// Shared memory pointer
void* shared_pointer() {
  return (void*) &_shared_mem;
}

// Memory copying functions
#ifdef EMSCRIPTEN
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

unsigned char* copy_bytes_from_cart(unsigned int offset, unsigned int size){
  unsigned char* ret = malloc(size);
  memcpy(ret, (unsigned char*) (&_shared_mem + offset), size);
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

typedef enum {
  FILTER_NEAREST,
  FILTER_BILINEAR
} ImageFilter;

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
`;

  // Generate enum for operations
  let opEnum = "typedef enum {\n";
  let mockImpls = "";
  let switchCases = "";

  // Process each YAML file
  for (const file of yamlFiles) {
    const content = YAML.parse(await fs.readFile(file, "utf8"));

    // Track unique types for getter/setter generation
    const types = new Set();

    // Process each function in the YAML
    Object.entries(content).forEach(([funcName, func]) => {
      const opName = `OP_${funcName.toUpperCase()}`;
      opEnum += `  ${opName},\n`;

      // Generate mock implementation
      const args = func.args || {};
      const argList = Object.entries(args)
        .map(([name, type]) => `${typeMap[type]} ${name}`)
        .join(", ");

      const returnType = typeMap[func.returns] || "void";
      types.add(returnType);

      Object.values(args).forEach((type) => types.add(typeMap[type]));

      mockImpls += `${returnType} null0_${funcName}(${argList}) {\n`;
      if (returnType !== "void") {
        if (returnType === "unsigned int") {
          mockImpls += `  return 1; // Mock handle\n`;
        } else {
          mockImpls += `  ${returnType} ret = {0};\n  return ret;\n`;
        }
      }
      mockImpls += `}\n\n`;

      // Generate switch case
      switchCases += `    case ${opName}:\n`;
      if (returnType !== "void") {
        switchCases += `      set_${returnType.replace("unsigned ", "")}_ret(`;
      }
      switchCases += `null0_${funcName}(`;

      const argCalls = Object.entries(args)
        .map(
          ([name, type]) =>
            `get_${typeMap[type].replace("*", "").replace("unsigned ", "")}_arg()`,
        )
        .join(",\n        ");

      switchCases += argCalls + ")";
      if (returnType !== "void") {
        switchCases += ")";
      }
      switchCases += ";\n      break;\n\n";
    });
  }

  opEnum += "} Op;\n\n";

  // Generate final switch function
  const switchFunc = `
void call(Op op) {
  cart_shared_arg_offset = 0;
  cart_shared_ret_offset = 0;

  switch(op) {
${switchCases}
    default:
      fprintf(stderr, "Unknown op: %d\\n", op);
  }
}\n`;

  return output + opEnum + mockImpls + switchFunc;
}

const code = await generateCode(await glob("api/*.yml"));
await fs.writeFile("host/null0_host.c", code);
