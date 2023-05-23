@mkdir build
@del lib\libFaceFX.a
@del build\*.o

@set MODULE=../../../../../External/FaceFX/FxSDK

@cd build
ppu-lv2-g++ -I%MODULE%/Inc -I%CELL_SDK%/target/ppu/include -I%MODULE%/../../../Src/Engine/FaceFX -g -D PS3 -D "__UNREAL__" -fshort-wchar -fno-rtti -fno-exceptions -fpermissive -Wfatal-errors -c %MODULE%/Src/*.cpp
@cd ..

@ppu-lv2-ar r lib\libFaceFX.a build\*.o
@ppu-lv2-ranlib lib\libFaceFX.a
@pause
