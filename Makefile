WASM=-s WASM=1
OUT_SUFFIX=wasm

# EMCC_FORCE_STDLIBS: We can make the main module carry all stdlibs, however:
# EMCC_FORCE_STDLIBS=libcxx,libcxxabi: Multiple modules
# EMCC_FORCE_STDLIBS=1 is broken:
# STDLIBS=EMCC_FORCE_STDLIBS=1
# https://github.com/kripken/emscripten/issues/5436

# https://groups.google.com/g/emscripten-discuss/c/nz2rXAp_vuQ?pli=1

EMCC_FORCE_STDLIBS=opencv_core opencv_flann, opencv_imgproc,
	opencv_highgui, opencv_ml, opencv_video,opencv_objdetect, opencv_photo,
	opencv_features2d, opencv_calib3d,opencv_stitching, opencv_videostab,
STDLIBS=EMCC_FORCE_STDLIBS

main:
	mkdir -p OUT
	STDLIBS=${EMCC_FORCE_STDLIBS} emcc src/brisk-detector.cpp -o OUT/brisk-detector.js --bind -g3 -std=c++11 -s MAIN_MODULE=1 -s WASM=1 -s MODULARIZE=1 -s FORCE_FILESYSTEM=1