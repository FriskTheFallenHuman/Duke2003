Exporting your game for Xbox360 is VERY EASY, you don`t even need Xbox360 SDK Installed, just follow the steps below.

##################################################################################

1) Start "UnrealFrontendConsoles" shortcut located at the folder "C:\UDKUltimate\UDKUltimate Desktop Shortcuts". At the left side of the screen, there is a tab called "Profile". Click on "UDK Ultimate Xbox360". Then on the tab "Maps to Cook", click on button "Add..." to add the maps you are going to cook. Important: As for consoles, at least the first map must have it`s name defined on the ini files for setting up a map cycle (for more information please study about gametype programming in UDK). I already setup the first map name to UDK-UDKUltimate. And for the sake of the testing, just add this "UDK-UDKUltimate" map which is a basic Third Person Template I created.

After added your map, click on the small black arrow at the side of the word "Start" located UNDER the first big green button at the top left of Unreal Fronten. After clicking on "Start" a drop-down menu will appear with some options. Click on "Start: Full rebuild and recook" and wait untill the cooking process finishes. You will see a popup message saying that "Debug View are not allowed for consoles", just click on "Ok". If everything worked well, you will see a text message on green color at the bottom of Unreal Frontend saying "ALL PIPELINE STEPS COMPLETED SUCCESSFULLY".

##################################################################################

2) After the cooking process, copy the folder "CookedXbox360" and the file "Xbox360TOC.TXT" from C:\UDKUltimate\UDKGame to the Xbox360 template's "UDKGAME" folder (\UDKUltimate\UDKGame Xbox360 Template\UDKGame). You can delete the old folder CookedXbox360 from the template folder and paste your new folder there.

##################################################################################

3) Now, you are done. Just copy the entire folder C:\UDKUltimate\UDKGame Xbox360 Template to your Xbox360 to an USB Stick (FAT32), plug it on your Xbox360, and then just click on the file C:\UDKUltimate\UDKGame Xbox360 Template\default.xex. I run it with FreeStyleDash File Manager. Also I run it with XEXMenu.

##################################################################################

4) Have fun playing your new Xbox360 game :)