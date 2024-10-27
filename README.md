The idea with this project is a multi-wasm host for null0.

It will have these parts:

- host - basic WASM host that just exposes framebuffer, sound callback, input utils, WASI, etc. (web, via emscripten or WAMR)
- adapter - a wasm that converts higher-level functions into low-level host functions. An example is "use WASI to load image file that can be displayed on screen"
- cart - this is user code that calls adapter functions


## Building

### xmake

This uses [xmake](https://xmake.io/). To install:

#### curl

```bash
curl -fsSL https://xmake.io/shget.text | bash
```

#### wget

```bash
wget https://xmake.io/shget.text -O - | bash
```

#### powershell

```powershell
Invoke-Expression (Invoke-Webrequest 'https://xmake.io/psget.text' -UseBasicParsing).Content
```

Now you can do this:

```
# build all
xmake

# build just the host
xmake build null0

# run
xmake run
```