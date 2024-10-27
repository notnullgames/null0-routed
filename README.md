This has some ideas around using a simpler WASM interface and routing, for [null0](https://github.com/notnullgames/null0).

I am attempting to simplify things and focus on 100% codegen here. The host is either compiled with emscripten, and used on web, or used in WAMR. The idea is to only need a few functions (memory-sharing and `null0_host_call`.)

I'd like to eventually split up the build-systems for each host-type (native/retro/web/carts) and greatly simplify:

## build-system

```
# configure: just native Raylib host
cmake -GNinja -B build -DNULL0=RAYLIB

# configure: just native SDL2 host
cmake -GNinja -B build -DNULL0=SDL2

# configure: just native libretro core
cmake -GNinja -B build -DNULL0=RETRO

# configure: just web
emcmake cmake -GNinja -B build

# configure: just carts
emcmake cmake -GNinja -B build -DCARTS=ON

# build project
cmake --build build
```

## goal


This will eventually look like this:

```c
// shared types and helpers/defs around sharing memory with cart
#include "null0_host_data.h"

// API implementations, this creates routers for every part of API,
// and glues them to underlying functions (pntr/etc)
#include "null0_host_api.h"

int null0_host_call(Op op) {
  cart_shared_arg_offset = 0;
  cart_shared_ret_offset = 0;
  switch(op) {
    case case OP_TRACE:
      null0_trace(get_string_arg());
      return 1;
    // ...many more here
    default:
      fprintf(stderr, "NULL0: Cound not route to op: %d\n", op);
      return 0;
  }
}
```
