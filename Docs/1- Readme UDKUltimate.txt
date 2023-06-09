UDKUltimate Engine for PS3, Xbox360, PC

Follow me at:

https://sites.google.com/view/udkultimate/
https://www.psxhax.com/threads/udk-ultimate-the-free-multi-platform-homebrew-3d-game-engine.84/
https://www.youtube.com/channel/UCAatBXORFDZ419V5X6UYnCg
https://plus.google.com/u/0/113186317863664115029
http://www.indiedb.com/members/udkultimate/blogs/udkultimate-engine-for-ps3-xbox360-pc
http://www.moddb.com/members/udkultimate/blogs/udkultimate-engine-for-ps3-xbox360-pc
https://github.com/udkultimate/UDKUltimateEngine

############################################################################

Getting Started:

If you are reading this readme is because you already downloaded and "installed" UDKUltimate. For the sake of commodity I created a folder called "UDKUltimate Desktop Shortcuts", which contains all the shortcuts setup for ALL the tools you are going to use, like recompile script, start editor, testgame, cook game, and so on. So as soon as you "install" UDKUltimate, you just open this folder (I recommend you to send a shortcut to your desktop to make it more accessible), and click first on UDKGameWin64-ScriptMake (or Win32), to recompile all the game scripts. Then you click on UDKGameWin64-GameAssetsDatabase (or Win32), to update the game assets database, and for last you click on UDKGameWin64-StartEditor (or Win32), to start UDKUltimate Editor. If everything runs fine and you don`t receive any error message it means that UDKUltimate is correctly "installed" and "ready to rock".

However, remember that UDKUltimate is an enhanced version of original UDK Engine (Unreal Development Kit) from Epic Games (Unreal Engine 3), and to you be able to use it you need to study Unreal Engine 3. There are plenty of youtube video tutorials about UDK, and aswell Epic has a very usefull website, Unreal Developers Network (https://docs.unrealengine.com/udk/Three/WebHome.html) with plenty of information and usefull tutorials aswell.

As for beginners, I recommend this series of tutorials from World of Level Design (these are the same tutorials I studied whenever I first learned about UDK/UE3):

https://www.youtube.com/playlist?list=PLA59F1E61EB00AF17

As for other details like exporting your game to consoles (PS3 and Xbox360), continue reading the other readme files from "UDKUltimate\Docs" folder.

Any doubts and support, feel free to contact me at udkultimate@gmail.com, though I can`t guarantee to answer all emails.

Cheers

:)

############################################################################

1- WHAT IS UDK ULTIMATE? 

This is a modified version of EPIC`s UDK (Unreal Development Kit) Game Engine which supports exporting your game for XBOX360/PS3/PC WITHOUT the need to be a Registered Game Developer for Sony (Playstation) or Microsoft (XBOX360), something that a LOT of folks always dreamed with. 

############################################################################

2- CAN I CREATE A GAME FOR XBOX360 AND PS3? 

On the first release, only exporting for Xbox360 was fully supported. You can create a game and play it on any RGH/JTAG Xbox360 console. As for PS3, thanks to EpicError and PixelButts, PS3 CFW is fully supported now (they fixed the issue with PS3 Exporting, and that`s the main reason for this new release), so the games created with UDK Ultimate now can be exported to PS3 and run on ANY CFW, no need for devkit. 

############################################################################

3- DO I NEED A DEVKIT, OR PS3/XBOX360 SDK?

No, you don't need any console devkit. For Xbox360, you don't need nothing, not even the Xbox360 SDK!!! But for PS3, unfortunatelly, you need to have the PS3 SDK 3.0 Installed and Configured Correctly, even for just cooking the maps for PS3. 

############################################################################

4- CAN I PLAY THESE GAMES ON ANY RETAIL CONSOLE?

No, the games created in UDK Ultimate only run on Hacked Consoles (because only these can run unsigned/unnoficial code). It runs on any XBOX360 JTAG/RGH (Slim and Slim E). You can even run the games from a USB Stick, by using a Xbox360 File Manager Utility (XEXMenu, FreeStyle Dash,...). As for PS3, it must be installed to the HD as a PKG game using a package manager utility.

############################################################################

5- DO I NEED TO KNOW C++ PROGRAMMING?

No, the exporting process for consoles is very easy, is ALMOST like "Menu > Export > XBOX360 / PS3". But you do need to learn how to use UDK/Unreal Engine 3 to be able to create a game using UDK Ultimate, you need to study unreal scripting, 3D Modelling, Animations, and so on. Youtube is your best friend. 

############################################################################

6- WHAT ABOUT THE LEGALITY OF UDK ULTIMATE?

It falls under the category of Homebrew Development, which everyone knows is not Supported, nor Authorized by the Game/Softwares Companies. However, i am sure no Company will ever do something about this, untill this begins to cause them damage. And the most common type of damage is financial, which means, when you use their software illegally for making profit (money) with it. It means, NEVER SELL ANY GAME CREATED WITH UDK ULTIMATE WITHOUT EPIC/SONY/MICROSOFT LICENSE. There are a lot of people in the Homebrew Development Scene, which create and share their own games for PS3 and XBOX360, and I never heard about someone who suffered any legal consequences for creating and sharing a homebrew game (so long as it does not use any copyrighted material, like 3D models from comercial games, and the like).

############################################################################

7- WHO ARE YOU AND WHY YOU DID IT?

I can`t reveal my real identity, I use a lot of nicknames over the internet. But I am a normal guy, I love Gaming, I am a trully passionate Game Designer by hobby and Web Designer/Developer by Profession. I love my Wife, I love my son, I love Maths (I am graduated on Mathmatics), I love Games. And my love for Game Development, my extreme passion is what motivated me for doing this. I always had a dream to be able to create and play a game on consoles, from since Super Nintendo. Althought today PC is a very good platform for gaming, anyway, I think consoles still hold a special place on the hearts of many gamers, especially the older ones (like me :) ) who grew up playing game consoles in front of a TV screen. However, I was only able to do this with the help of a lot of folks who supported me from since the beginning of this project almost 2 years ago, which i will credit them below. 

############################################################################

8- CREDITS:

I would like to thank all these guys below, because i was only able to complete this project with their valuable help and support.

GOD for giving me a brain to think and learn things;

PSXHax Admin, which was the guy who supported me by giving me the complete PS3 SDK 3.00, and also a lot of PS3 material and stuff which was also essencial to me be able to compile UE3 for PS3. Also, he helped me with promoting my Project on his Website. This Project is sponsored by psxhax.com

Beta (Gh0stBlade) from Beta Archive, which helped me with my first contact with C++ and Visual Studio, and also oriented me on where to go and what to do to compile Unreal Engine 3 Source Code, and recently he was the responsible for fixing up Bink Video Source Code for PC and Xbox360;

Bradez from Beta Archive, which was the guy who helped me to port UDK to Xbox360, because he is a Xbox360 dev, he owns a Xbox360 Devkit, and he was essencial in fixing a lot of bugs and errors on the UE3 Xbox360 Source Code;

Pixelbutts and EpicError from AssemblerGames for fixing PS3 Support and Compiling;

TheUE3unimatrix from ObscureGamers for giving me some updated Unreal Engine 3 source code components;

aerossoul94 from Next Generation Update, which was the guy who first helped me to port UDK to PS3 and make it run first on his PS3 Devkit. He also helped me with testing and debugging it on his PS3 Devkit;

SockNastez and xetafin from PSXHax.com for testing and debugging UDKGame on their PS3 CFW;

Voxel Studios from AssemblerGames for testing and debugging UDKGame on his PS3 CFW;

hexxellor, spyro2670 and SuperSaiyen from PSXHax.com, which were the first people to help me with testing the UDKGame on PS3 CFW;

Snipe34 and 661gaz from Unreal Engine Forums for helping me with Unreal Scripting and recreating the GOW Chainsaw Execution in UDK;

Shindiggity and TKBS from Unreal Engine Forums for helping me with Unreal Scripting and implementing Hitmask Effect to simulate blood wound on enemies body;

############################################################################

9- UDK ULTIMATE 2017 CHANGELOG AND IMPROVEMENTS:

- Recompiled UDKGame Binaries both 32 and 64 Bits;

- Improved Stability and Compatibility over last UDK Engine (Feb 2015 Build) thanks to recompiling of the binaries with EPIC_INTERNAL_FLAG (no random crashes);

- Fully PS3 CFW Support, improved PC and Xbox360 support;

- Fully Adobe Flash Scaleform support for all platforms;

- Added Bink Video Loading Support for PC and Xbox360. As PS3, unfortunatelly we could not fix the Bink Video Source Code to work on PS3;

- Removed iOS support because UE3 2011 Source Code is know to have a bug for exporting to iOS (use UDK Engine February 2015 for iOS export);

- Completely new and revamped UI made in Flash / Scaleform (source flash files included for easy editing);

- Added basic gameover screen which resets game (kismet and flash scaleform);

- Improved FBX Material Import, autoset double sided materials on imported meshes which have one side poly (avoid unwanted poly culling);

- Improved FBX Mesh Import, autoset "Enable PolyColl and Shadow Casting" for multiple meshe`s ID (multi material meshes). This is very handsome whenever importing too many FBX meshes for modular level design, no need to manually set this for each imported mesh;

- Custom Gore System: blood spills from enemies on shoot, bloody wounds on enemies body, blood splash on walls, custom physical gibs system. However, Hitmask (bloody wounds on enemies body) don`t work on PS3 (it crashes the system). I think it happens because Hitmask component of UE3 Source Code is not ported to PS3;

- Added basic Gears of War 3rd Person Shooter Gameplay Template;

- Added default UTGame First Person Shooter Gameplay Template;

- Enhanced Characters Animation Tree (new animations included);

- Basic Melee Execution System: Gears of War Saw Execution;

- Gears of War Model Pack: Characters, Weapons and Environmental Objects (props). Important: as for PS3, everything works perfectly (GOW Weapons and Characters), except GOW props (static meshes). That`s because GOW Static Meshes were extracted directly from upk and recooked in UDK Ultimate, but for PS3, the PS3Tools.dll can`t cook a recooked static mesh, that means if you want to use some Gears of War Props on PS3, you need the extract this prop using Unreal Model Viewer (included on the download), then import this prop on 3dsmax, then export it to UDK Ultimate as FBX, and recreate the package. As for PC and Xbox360, they are ready for use;

- Realistic Balistic Weapons: All GOW guns shoot real bullets influenced by physics;

- Added bullet shell eject effect on All Custom GOW Guns;

- Basic TeamGame Match Setup: Gears of War Heroes x Locust Army;

- Basic Cutscene Matinee Animation Template with kismet;

- Full Unreal Tournament 3 Script (Classes) Source Included;

- Many Unreal Tournament 3 Models, Animations and Effects Pack ported to UDK;

- All other UDK Engine Features included (except some new features like substance procedural materials system);

- Included usefull Third-Party Tools like Unreal Engine Model Viewer, Unreal Engine Scripts Decompiler, Unreal X-Editor, UnrealScript Plugin for Notepad++;

- All custom Art Assets included, like Gears of War 3D Models in 3dsmax format, all custom logos, banners, wallpapers and icons in Photoshop format, all promo material included the Release Trailer in After Effects format and Adobe Premiere Editing;

- New Docs folder with more complete instructions on how to install and use UDKUltimate;

############################################################################

10- COPYRIGHTS INFORMATION

- Epic Games, Inc. All rights reserved. Epic, Epic Games, the Epic Games logo, Unreal, Unreal Engine, Unreal Development Kit, UDK, Unreal Tournament, and the Unreal Tournament 3 logo are trademarks or registered trademarks of Epic Games, Inc. in the United States of America and elsewhere;

- SCE, Inc. All rights reserved. PlayStation, Playstation 3 and PS3 Logo are trademarks or registered trademarks of Sony Computer Entertainment Inc. in Japan and elsewhere;

- Microsoft Corporation. Microsoft, Windows, Windows 7, the Windows logo, Xbox360 and Xbox "Sphere" logo are trademarks or registered trademarks of Microsoft Corporation in the United States of America and elsewhere;

- UDKFrontend by user research  from Epic Games Forum: https://forums.epicgames.com/udk/udk-community/community-content-tools-and-tutorials/208471-udk-frontend-v1-0-6-5;

- UEViewer by Gildor: http://www.gildor.org/en/projects/umodel;

- UE Explorer by Eliot: http://eliotvu.com/portfolio/view/21/ue-explorer;

- UnrealXEditor and Unreal Script Wizard by ryanjon2040: https://unrealxeditor.wordpress.com/;

- Unreal Tournament 3 and Gears of War Assets by EPIC Games: https://www.epicgames.com;

- GOW Content for UT3 by UX.Loki: https://forums.beyondunreal.com/threads/gears-of-war-content-for-ut3-editor.180779/;

- SK3 Gears of War Weapons UT3MOD: https://www.gamewatcher.com/mods/unreal-tournament-iii-mod/gears-of-war-character-and-weapons;