set_project("null0")
set_version("0.0.1")
set_license("Zlib")

add_rules("mode.debug", "mode.release")

-- this is not working with wasm-target, for now
-- see https://github.com/xmake-io/xmake-repo/issues/5589
-- add_requires("minifb")

target("null0")
-- add_packages("minifb")
    set_kind("binary")
    set_default(true)
    add_files("host/src/*.c")
    if is_plat("wasm") then
        set_extension(".mjs")
        set_toolchains("emcc")
        add_cflags("--no-entry")
        add_ldflags("-sFORCE_FILESYSTEM -sEXPORTED_RUNTIME_METHODS=FS,stringToUTF8")
    end

    
