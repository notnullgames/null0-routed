add_rules("mode.debug", "mode.release")

add_requires("minifb")

target("null0")
    set_kind("binary")
    add_files("host/src/*.c")
    add_packages("minifb")
