The idea with this project is a multi-wasm host for null0.

It will have these parts:

- host - this is used with WAMR or (emscripten-compiled) web-host. It has a router that calls game functions & marshals params/returns over wasm, to simplify things.
- cart - this is user code that calls host-router

### build

```
export MAKEFLAGS=-j$(nproc)

# build native host & carts
cmake -B build
cmake --build build

# build web-host
emcmake cmake -B wbuild
cmake --build wbuild
```
