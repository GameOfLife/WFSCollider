GameOfLife WFSCollider - Wave Field Synthesis spatialization for SuperCollider.
===============================================================================

GameOfLife WFSCollider is an adapted version of SuperCollider, the audio synthesis engine and programming language, for Wave Field Synthesis spatialization.

It's currently being used in the 192 speakers system of the [Game Of Life Foundation](http://gameoflife.nl/en), based in The Hague, the Netherlands.

WFSCollider consists of an audio spatialization engine that places individual sound sources in space according to the principles of [Wave Field Synthesis](http://en.wikipedia.org/wiki/Wave_field_synthesis).

The system allows soundfiles, live input and synthesis processes to be placed in a score editor where start times, and durations can be set and trajectories or positions assigned to each event. It also allows realtime changement of parameters and on the fly starting and stopping of events via GUI or OSC control. Each event can be composed of varous objects ("units") in a processing chain.

Score files are saved as executable SuperCollider code. The system is setup in a modular way and can be scripted and expanded using the SuperCollider language.

## Getting Help ##

Start WFSCollider, in the menubar go to Help->SuperColliderHelp then click on "Home" and then "WFSCollider V2.0 Overview"

A full PDF manual is available [here](http://sourceforge.net/projects/wfscollider/files/WFSCollider%20Manual/Working%20with%20WFSCollider%20v2.pdf/download)

## System Requirements ##

Mac OS X 10.6 or greater

## Download ##

A prepackaged version is available [here](https://sourceforge.net/projects/wfscollider/).

## Installation ##

To install, just drag the application to your applications folder.

## Building ##

Run the following commands:

```
git clone git://github.com/GameOfLife/WFSCollider.git
cd WFSCollider/
git checkout -b origin/3.5sampleJune2012
git submodule init
git submodule update
cd submodules/sc3-plugins
git submodule init
git submodule update
mkdir build
cd build
cmake -DSC_PATH=../../../ ..
make -j4
make install
cd ../../../
mkdir build
cd build
cmake -D standalone:string=WFSCollider -DSC_QT=OFF -DWFS=GAMEOFLIFE -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_SYSROOT="/Developer/SDKs/MacOSX10.6.sdk" ..
make -j8
make install
cd WFSCollider
dylibbundler -of -b -x WFSCollider.app/Contents/MacOS/WFSCollider -p @executable_path/../Resources/ -d WFSCollider.app/Contents/Resources/
open WFSCollider.app
```

for dual cores use -j4 for quad cores -j8, etc. The application will then be in ./build/WFSCollider/

Depending on the situation change the cmake line:

For development work do

    cmake -D standalone:string=WFSCollider -DSC_QT=OFF -DWFS=DEV -DCMAKE_BUILD_TYPE=Release ..

For deployment to the GOL system:

    cmake -D standalone:string=WFSCollider -DSC_QT=OFF -DWFS=GAMEOFLIFE -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_SYSROOT="/Developer/SDKs/MacOSX10.6.sdk" ..

For release

With supernova:

    cmake -D standalone:string=WFSCollider -DSC_QT=OFF -DWFS=OFFLINE -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES='i386;x86_64' -DSUPERNOVA=ON -DCMAKE_OSX_SYSROOT=Developer/SDKs/MacOSX10.6.sdk ..

without supernova:

    cmake -D standalone:string=WFSCollider -DSC_QT=OFF -DWFS=OFFLINE -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES='i386;x86_64' -DCMAKE_OSX_SYSROOT="/Developer/SDKs/MacOSX10.6.sdk" ..

    cmake -D standalone:string=WFSCollider -DSC_QT=OFF -DWFS=OFFLINE -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES='i386;x86_64' -DCMAKE_OSX_SYSROOT="/Developer/SDKs/MacOSX10.5.sdk" ..

for release this should be run on the standalone:
WFSPrePanSynthDefs.generateAll;
WFSPreviewSynthDefs.generateAll;

And until 3.5 lib bundling is fixed:
    dylibbundler -of -b -x WFSCollider.app/Contents/MacOS/WFSCollider -p @executable_path/../Resources/ -d WFSCollider.app/Contents/Resources/    

## Acknowledgments ##
WFSCollider was conceived by the Game Of Life Foundation, and developed by W. Snoei, R. Ganchrow and J. Truetzschler and M. Negrão.

## License ##
Both SuperCollider and the WFSCollider library are licensed under the GNU GENERAL PUBLIC LICENSE Version 3.  

