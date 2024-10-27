This has some ideas around using a simpler WASM interface and routing, for [null0](https://github.com/notnullgames/null0).

I am attempting to simplify things and focus on 100% codegen here. The host is either compiled with emscripten, and used on web, or used in WAMR. The idea is to only need a few functions (memory-sharing and host_run.)

This will eventually look like this:

```c
// shared types and stuff around sharing memory with cart
#include "null0_host_data.h"

// API implementations, this creates routers for every part of API,
// and glues them to underlying functions (pntr/etc)
#include "null0_host_api.h"

int host_run(Op op) {
  cart_shared_arg_offset = 0;
  cart_shared_ret_offset = 0;
  if (host_run_colors(op)) {
    return 1;
  }
  if (host_run_filesystem(op)) {
    return 1;
  }
  if (host_run_graphics(op)) {
    return 1;
  }
  if (host_run_inputs(op)) {
    return 1;
  }
  if (host_run_sound(op)) {
    return 1;
  }
  if (host_run_utilities(op)) {
    return 1;
  }
  fprintf(stderr, "NULL0: Cound not route to op: %d\n", op);
  return 0;
}
```
