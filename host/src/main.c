#define PNTR_APP_IMPLEMENTATION
#include "null0_api.h"

#ifndef EMSCRIPTEN
#include "null0_wamr.h"
#endif

bool Init(pntr_app* app) {
  char* cartName = pntr_app_userdata(app);
  if (strcmp(cartName, "") == 0) {
    fprintf(stderr, "Usage: null0 <CART>\n");
    return false;
  }
#ifdef EMSCRIPTEN
  return null0_cart_setup(cartName, app) == 0;
#else
  return null0_wamr_load() == 0 && null0_cart_setup(cartName, app) == 0;
#endif
}

bool Update(pntr_app* app, pntr_image* screen) {
#ifdef EMSCRIPTEN
  return true;
#else
  return null0_wamr_update() == 0;
#endif
}

void Close(pntr_app* app) {
}

pntr_app Main(int argc, char* argv[]) {
#ifdef PNTR_APP_RAYLIB
  SetTraceLogLevel(LOG_ERROR); 
#endif
  pntr_app app = (pntr_app) {
    .width = 320,
    .height = 240,
    .title = "null0",
    .init = Init,
    .update = Update,
    .close = Close,
    .fps = 60
  };
  char* cartName = "";
  if (argc == 2) {
    cartName = argv[1];
  }
  pntr_app_set_userdata(&app, (void*) cartName);
  return app;
}