#include "MiniFB.h"
#include <stdio.h>
#include <stdbool.h>
#include "null0_router.h"

#define SCREEN_WIDTH      320
#define SCREEN_HEIGHT     240

typedef struct mfb_window Window;

typedef struct {
  Window* window;
  unsigned int screen[SCREEN_WIDTH * SCREEN_HEIGHT];
} Null0App;

// use this for setting up native/web
bool null0_init(Null0App* app) {
  app->window = mfb_open_ex("null0", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (!app->window){
    return false;
  }
  return true;
}

// use this for updating native/web
bool null0_update(Null0App* app) {
  int state = mfb_update_ex(app->window, app->screen, SCREEN_WIDTH, SCREEN_HEIGHT);
  if (state < 0) {
    app->window = NULL;
    return false;
  }
  return true;
}

int main(int argc, char** argv) {
  Null0App app = {};

  if (!null0_init(&app)) {
    fprintf(stderr, "null0: Could not initialize.\n");
    return 1;
  }

  mfb_set_user_data(app.window, (void *) &app);

#ifndef EMSCRIPTEN
  while(mfb_wait_sync(app.window)) {
    if (!null0_update(&app)) {
      break;
    }
  }
#endif

  return 0;
}
