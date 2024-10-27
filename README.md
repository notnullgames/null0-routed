This has some ideas around using a simpler WASM interface and routing, for [null0](https://github.com/notnullgames/null0).

I am attempting to simplify things and focus on 100% codegen here. The host is either compiled with emscripten, and used on web, or used in WAMR. The idea is to only need a few functions (memory-sharing and `null0_host_call`.)

I'd like to eventually split up the build-systems for each host-type (native/retro/web/carts) and greatly simplify:

## build-system

```
# configure: just native Raylib host
cmake -GNinja -B build -DNULL0_HOST=RAYLIB

# configure: just native SDL2 host
cmake -GNinja -B build -DNULL0_HOST=SDL2

# configure: just native libretro core
cmake -GNinja -B build -DNULL0_HOST=RETRO

# configure: just web host, it's recommended to use a different dir than native builds
emcmake cmake -GNinja -B wbuild

# configure: just carts, no host
cmake -GNinja -B build -DCARTS=ON -DNULL0_BUILD_HOST=OFF

# build project
cmake --build build
```

## goals


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

At some point, I think I would also like to move to WASI component-model. [This video](https://www.youtube.com/watch?v=tAACYA1Mwv4&t=2s) has some great conceptual ideas. There are also some very good reasons not to.

Here are some things to look into more:

- Create wit to describe null0 & carts
- Auto-generate headers for carts and (including stub) host from that
- [wasi-virt](https://github.com/bytecodealliance/WASI-Virt) might help lock down the API a bit more.
- [linking modules](https://docs.wasmtime.dev/examples-c-linking.html) - I'd rather not compile outputted WASM to need a lot inside it (host should provide WASI+null0) but it might be good for the memory-share portion (utils for passing mem)
- multi-memory to share memory between cart & host
- WASI with zip filesystem for all hosts. Could this be done as a host-sidecar in wasm? (load wasm, point it at zip, it exposes some WASI functions for cart/host)
- jco - it can create a shim for wasi-components, and other things
- would [this](https://github.com/bytecodealliance/wamr-app-framework/blob/main/app-framework/app-native-shared/restful_utils.c) be useful for memory-marshalling?
- put memory functions into central data-tyep wrangler (like [this](https://github.com/konsumer/wasm-memshare/blob/main/cartas/src/null0.ts#L31-L55) assemblyscript example, where you give it a type) types could be sent as an enum param:

```c
typedef enum {
  MT_STRING,
  MT_U32,
  ...etc
} MarshalType;

void set_arg(MarshalType type, void* val)
void* get_arg(MarshalType type)
void set_ret(MarshalType type, void* val)
void* get_ret(MarshalType type)
```

I could make a shared header for host/C-cart.

language support (cart)

- c (wasi-sdk)
- assemblyscript
- rust
- nim
- zig
- wat
- [js](https://porffor.dev/)
- [go](https://tinygo.org/)
- [python](https://github.com/rafi16jan/micropython-wasm)
- [COBOL](https://github.com/cloudflare/cobweb)
- [lua](https://nelua.io/)
- [scheme](https://spritely.institute/hoot/)
- Interpretors compiled as sidecars
