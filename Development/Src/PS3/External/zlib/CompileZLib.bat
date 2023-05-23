make -C ../../../../External/zlib/Src CC=ppu-lv2-gcc "AR=ppu-lv2-ar r" RANLIB=ppu-lv2-ranlib CFLAGS=-O3 clean
make -C ../../../../External/zlib/Src CC=ppu-lv2-gcc "AR=ppu-lv2-ar r" RANLIB=ppu-lv2-ranlib CFLAGS=-O3 libz.a
move /Y ..\..\..\..\External\zlib\Src\libz.a lib\libz.a
pause
