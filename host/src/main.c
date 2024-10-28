#include <stdio.h>
#include <stdbool.h>
#include "null0_router.h"

#define SCREEN_WIDTH      320
#define SCREEN_HEIGHT     240

typedef struct {
  unsigned int screen[SCREEN_WIDTH * SCREEN_HEIGHT];
} Null0App;

// use this for setting up native/web
bool null0_init(Null0App* app) {
  return true;
}

// use this for updating native/web
bool null0_update(Null0App* app) {
  return true;
}

int main(int argc, char** argv) {
  Null0App app = {};

  if (!null0_init(&app)) {
    fprintf(stderr, "null0: Could not initialize.\n");
    return 1;
  }

#ifndef EMSCRIPTEN
  while(true) {
    if (!null0_update(&app)) {
      break;
    }
  }
#endif

  return 0;
}
