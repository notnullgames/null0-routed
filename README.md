The idea with this project is a multi-wasm host for null0.

It will have these parts:

- host - this is used with WAMR or (emscripten-compiled) web-host. It has a router that calls game functions & marshals params/returns over wasm, to simplify things.
- cart - this is user code that calls host-router


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
# build the native host
xmake build null0

# build the web-host
xmake f -p wasm
xmake
```
