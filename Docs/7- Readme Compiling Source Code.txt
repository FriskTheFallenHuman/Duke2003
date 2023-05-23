THERE IS ABSOLUTELY NO NEED TO RECOMPILE THE SOURCE CODE UNLESS YOU WANT TO ADD SOME NEW FEATURE TO UDK ULTIMATE. THE ENGINE IS READY FOR USE AS SOON AS YOU DOWNLOAD IT. ANYWAY, IF YOU WANT, FOLLOW THE STEPS BELOW:

You will need the following softwares:

###############################################################################################################

Basic Development Setup:
------------------------

* Playstation 3 Oficial SDK 3.00
- https://mega.nz/#F!rZMTwLZb!F-6TurTf_TfBcSRLMm9ifQ

* XBox360 SDK 20871 + Visual Studio 2010 Ultimate - You need to instal VS2010 Ultimate to be able to instal the Xbox360 SDK
- https://mega.nz/#F!qE80FRxK!LNXXT1uuS37qLM4_lQUcKA

* Visual Studio 2008 Professional

* Microsoft Visual Studio 2008 Service Pack 1
http://www.microsoft.com/en-us/download/details.aspx?id=10986

* DirectX Software Development Kit
http://www.microsoft.com/en-us/download/details.aspx?id=6812

And also, i think (i`m not sure), but maybe you need to install these Windows Components (is very good have them installed if you want to develop games). If you have a 64 bit system (Win7 64 bit), you should install the two versions (x86 and x64):

* Microsoft Visual C++ 2005 Redistributable Package (x86) 
http://www.microsoft.com/en-us/download/details.aspx?id=3387

* Microsoft Visual C++ 2005 Redistributable Package (x64)
http://www.microsoft.com/en-us/download/details.aspx?id=21254

* Microsoft Visual C++ 2008 Redistributable Package (x64)
http://www.microsoft.com/en-us/download/details.aspx?id=15336

* Microsoft Visual C++ 2008 Redistributable Package (x86) 
http://www.microsoft.com/en-us/download/details.aspx?id=29

* Microsoft Visual C++ 2010 Redistributable Package (x64)
http://www.microsoft.com/en-us/download/details.aspx?id=14632

* Microsoft Visual C++ 2010 Redistributable Package (x86)
http://www.microsoft.com/en-us/download/details.aspx?id=5555

* Microsoft Windows SDK for Windows 7 and .NET Framework 4
http://www.microsoft.com/en-us/download/details.aspx?id=8279

* Microsoft .NET Framework 4
http://www.microsoft.com/en-us/download/details.aspx?id=17851

Important: maybe you experience an error on Installing Directx SDK (it happened with me), and this may be probally the cause of the error, and also the solution, and i confirm that this worked for me:

https://support.microsoft.com/en-us/kb/2728613

You will need a good text editor to edit the cpp files and headers. I am using Notepad++, and i trully recomend it for you to download:
https://notepad-plus-plus.org/

###############################################################################################################

PS3 SDK Intall:
---------------

* Extract the multipart .rar files:
- PS3 SDK Installer.part1.rar 
- PS3 SDK Installer.part2.rar
- PS3 SDK Installer.part3.rar
- PS3 SDK Installer.part4.rar
- PS3 SDK Installer.part5.rar
- PS3 SDK Installer.part6.rar
- PS3 SDK Installer.part7.rar

* Run PS3SdkInstaller.exe from the extracted folder PS3 SDK Installer:
- On the first screen click Next
- Then click on Install (Offline)
- Click on checkbox SDK 300 to select ALL components
- Set the installation folder to C:\usr\local\cell
- Always click on next and wait untill installation finishes (ignore any error messages)

* Install Playstation Egde Graphics SDK:

- Extract the archives [63]-edge_1_2_0.7z, [63]-edge_1_2_0.7z.002, [63]-edge_1_2_0.7z.003, [63]-edge_1_2_0.7z.004, [63]-edge_1_2_0.7z.005. After extracting these archives you will have an archive named [63]-edge_1_2_0.zip. Inside this zip file there is a folder called "cell". Just copy this folder to "C:\usr\local\" and overwrite the cell folder inside there (if you receive a message asking to overwrite)

* Move the subdirectories (host-win32, SDK_doc, target) from C:\usr\local\cell\Tools\GPAD\cell to C:\usr\local\cell (overwrite)

* Copy C:\usr\local\cell\host-win32\Cg\include to C:\Program Files (x86)\SN Systems\PS3\sdk\include (overwrite)

* Copy C:\usr\local\cell\host-win32\Cg\include to C:\usr\local\cell\target\common\include (overwrite)

* Copy C:\usr\local\cell\host-win32\Cg\include to C:\usr\local\cell\host-common\include (overwrite)

* Copy C:\usr\local\cell\target\common\include\edge to C:\Program Files (x86)\SN Systems\PS3\sdk\include\edge (overwrite)

* Copy C:\usr\local\cell\host-common\include\edge to C:\Program Files (x86)\SN Systems\PS3\sdk\include\edge (overwrite)

* Exract the archive lame_enc.zip and copy the extracted lame_enc.dll to C:\Program Files (x86)\SCE\Multistream Tools\MSEnc (overwrite)

* Copy C:\Program Files (x86)\SCE\Multistream Tools\MSEnc to C:\usr\local\cell\host-win32\bin (overwrite)

###############################################################################################################

Xbox360 SDK Intall:
-------------------

* As for Xbox360, there is no need to configure the SDK (like PS3), just you install First Visual Studio Ultimate 2010 (xbox360 sdk needs VS2010 installed), then you install Xbox360 SDK by running the installer and you are done.

###############################################################################################################

UDK Ultimate VS2008 Compiling:
------------------------------

* After you installed all the above softwares (Windows Components and Consoles SDK), you are ready to compile the UDK Ultimate Source Code.

* Run Visual Studio 2008 as admin (you should always run VS2008 as admin), open the Visual Studio Solution UDKUltimate: 

C:\UDKUltimate\Development\Src\UDKUltimate 2017 Final.sln

* As you can see, everything is already compiled (built), and all the Visual C++ Projects are organized by category (Unreal Engine Base, Console Platform, and so on...). If you have setup everything right (installed VS2008, DirectXSDK, PS3SDK, Xbox360SDK, and so on), you just right-click on the Solution UDKUltimate Final inside VS2008, and select "Rebuild Solution". Then after some time (it can be long), you will have generated the Xbox360 and PS3 Binaries, which will be located at C:\UDKUltimate\Binaries\PS3 and C:\UDKUltimate\Binaries\Xbox360

OBS: As for PS3 compiling, you need first change the file C:\UDKUltimate\Development\Src\Core\Inc\Licensee\BaseInclude.h to define epic_internal to 0

#define EPIC_INTERNAL 0

Whenever you set EPIC_INTERNAL to 1 it will add bink video support to UDKUltimate PC and Xbox360. As for PS3, Bink is not supported on this UE3 Source Code Version. So because this whenever you want to compile PS3 Binaries, you need to set EPIC_INTERNAL 0 then rebuild the solution. By doing this you will have compiled PS3 Binaries, however, PC and Xbox360 Binaries will have lost Bink Video Support. To fix that you need to set again EPIC_INTERNAL to 1, then unmark PS3 Projects from compiling, then rebuild another time the solution.

###############################################################################################################

Consoles Binaries:
------------------ 

Xbox360 Binaries - The file called default.xex (C:\UDKUltimate\Binaries\Xbox360\default.xex) which is the xbox360 executable game itself IS NOT GENERATED in the compiling process. This is just the file UDKGame-Xbox360-Shipping.xex renamed to default.xex. However, after you rename this file to default.xex, YOU MUST PATCH it using a tool called X360GameHack v6.6 from xorloser for this tool run into a retail jtag/rgh console. Just select make retail (leaving all other options untouched).

PS3 Binaries - The file called EBOOT.bin (C:\UDKUltimate\Binaries\PS3\EBOOT.bin) which is the ps3 executable game itself IS NOT GENERATED in the compiling process. This is just the file UDKGAME-PS3-SHIPPING.elf renamed to EBOOT.bin.

* Navigate to "\UDKUltimate\Binaries\PS3" and select UDKGAME-PS3-SHIPPING.elf. Copy and rename the copy to "EBOOT.BIN" (UPPERCASE)

* Move EBOOT.BIN into the Resigner folder (\UDKUltimate\UDKGame PS3 Template\Trueancestor resigner). Open the resigner and select option 10

* You will now have an EBOOT.ELF file in this folder. With the resigner still open select option 3 and choose a ContentID for your game (UP9000-TEST12345_00-0000000000000000 for the template)

* You will now have a NEW EBOOT.BIN with your original renamed to EBOOT.BIN.bak. Take the NEW EBOOT.BIN and place it in the package template directory USRDIR (\UDKUltimate\UDKGame PS3 Template\Build Package\TEST12345\USRDIR)

* If you are NOT using "TEST12345, edit the PARAM.SFO in a Hex Editor. Near the bottom you will see "TEST12345". Change this to whatever you have chosen for your game's TitleID (can be TEST00001, BLES00200, doesnt matter, but must be 9 digit long)

###############################################################################################################

Observation: 
------------

After the compiling process you will receive just one error messages

Error	28	error PRJ0019: A tool returned an error code from "Performing Makefile project actions"	UDKGame Xbox360	UDKGame Xbox360

This error (UDKGame Xbox360) is meaningless, because this error is just because the compiler could not deploy the files to the Xbox360 Devkit, however the xbox executables were generated correctly (just look inside C:\UDKUltimate\Binaries\Xbox360).

Good luck!!!