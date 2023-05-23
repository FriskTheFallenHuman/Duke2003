General Info:
-------------

All the executables (Win32 and Win64) are the same, the only diference is about memory limitation. Win32 executable are limited to 4GB of Ram Memory usage, and Win64 executables don`t have this limit. So if you have Windows 64 Bit, so you must use Win64 executables. 

In practical terms, that means if you are going to create a very big and huge map, DON`T use Win32 executables because UDK Ultimate Editor will crash.

However, if you plan to develop for PS3, you must use Win32 executables because PS3 is very limited in Ram Memory (only 256MB), while Xbox360 can use up to 512MB Ram (it is shared between GPU and System Memory). It means that not any map you can get running on Xbox360 will run on PS3, and by using Win32 executables, you will be able to work with low memory in an environment very close to PS3 Memory Limitation.

Most important is creating and testing, extensively testing, because sometimes you need to remove some objects from your map (don`t add too much details) to be able to get the game running smoothly on PS3.

Game Assets Database:
---------------------

The way you access and see your contents inside UDK is by right-clicking on the package name inside UDK and select fully load. So whenever the packages are fully loaded, you can access all assets inside these packages. They are not fully loaded by default, so the thumbnails are not shown by default.

So to make your workflow more efficient, whenever you run the shortcuts UDKGameWin64-GameAssetsDatabase or UDKGameWin32-GameAssetsDatabase, it will create a catalog with thumbnails of all assets you have inside all the upk`s packages stored on the UDKGame/Content folder, so this is invaluable, because you will be able to search and navigate through all of your assets without the need of going one by one and select fully load package.

You can even use the search function on the content browser because it will be able to access all your content inside the upk without fully loading them. If you try to use the seach function whilst the packages are not fully loaded, the search will not find the assets you are looking for, it can only search and find inside the packages that are fully loaded.

So after you select the asset and add this to your map, then it will fully load the package automatically, without the need to you to this (it will load on demand).

It`s recomended to run this comandlet UDKGameWin64-GameAssetsDatabase or UDKGameWin32-GameAssetsDatabase allways whenever you add some new assets to your packages, to keep everything cataloged and with it`s thumbnail.

Engine Crashes:
---------------

UDK Ultimate is a very stable game engine, even more stable than the original UDK Engine, however, as any other software, sometimes it may crash for various reasons. Anyway, you can try the following steps in case of a crash.

* Whenever you add some new content to your UDK folder (new character, weapons, etc), always run UDKGameWin64-ScriptMake and UDKGameWin64-GameAssetsDatabase;

* Whenever you change, edit some actor (like editting your custom gun classes), before running the map (after rebuild scripts), rebuild paths inside UDK Editor;

* Clean Temporary Files from Windows (C:\Users\YourName\AppData\Local\Temp and C:\Windows\Temp);

* Delete Auto Save Files (C:\UDKUltimate\UDKGame\Autosaves);

* Close Programs to free memory (never run Photshop or 3dsmax at the same time you run UDK Ultimate unless you have a huge memory like 12GB);