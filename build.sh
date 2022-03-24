#!/bin/sh

flags="-O0 --memory-init-file 0 -fno-exceptions "

EMCC_FORCE_STDLIBS=libc,libcxx,libcxxabi em++ ${flags} -s SIDE_MODULE=1 -s WASM=1 -o brisk-detector.wasm src/brisk-detector.cpp

# build for node.js
# EMCC_FORCE_STDLIBS=libc,libcxx,libcxxabi em++ ${flags} \
# -s WASM=1 -s MAIN_MODULE=1 -o main.js null.cc --pre-js pre.js

# build for firefox and chrome, then run server.js
# and open http://localhost:8080 in your browser
# EMCC_FORCE_STDLIBS=libc,libcxx,libcxxabi em++ ${flags} \
# -s WASM=1 -s MAIN_MODULE=1 --proxy-to-worker -o index.html \
# null.cc --pre-js pre.js