# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.IrrXML.Debug:
/Users/aroberd/Documents/Neon-Engine/lib/Debug/libIrrXML.a:
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/lib/Debug/libIrrXML.a


PostBuild.assimp.Debug:
PostBuild.IrrXML.Debug: /Users/aroberd/Documents/Neon-Engine/lib/Debug/libassimp.dylib
/Users/aroberd/Documents/Neon-Engine/lib/Debug/libassimp.dylib:\
	/usr/lib/libz.dylib\
	/Users/aroberd/Documents/Neon-Engine/lib/Debug/libIrrXML.a
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/lib/Debug/libassimp.dylib


PostBuild.assimp_cmd.Debug:
PostBuild.assimp.Debug: /Users/aroberd/Documents/Neon-Engine/bin/Debug/assimp
PostBuild.IrrXML.Debug: /Users/aroberd/Documents/Neon-Engine/bin/Debug/assimp
/Users/aroberd/Documents/Neon-Engine/bin/Debug/assimp:\
	/Users/aroberd/Documents/Neon-Engine/lib/Debug/libassimp.4.1.0.dylib\
	/usr/lib/libz.dylib\
	/Users/aroberd/Documents/Neon-Engine/lib/Debug/libIrrXML.a
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/bin/Debug/assimp


PostBuild.unit.Debug:
PostBuild.assimp.Debug: /Users/aroberd/Documents/Neon-Engine/bin/Debug/unit
PostBuild.IrrXML.Debug: /Users/aroberd/Documents/Neon-Engine/bin/Debug/unit
/Users/aroberd/Documents/Neon-Engine/bin/Debug/unit:\
	/Users/aroberd/Documents/Neon-Engine/lib/Debug/libassimp.4.1.0.dylib\
	/usr/lib/libz.dylib\
	/Users/aroberd/Documents/Neon-Engine/lib/Debug/libIrrXML.a
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/bin/Debug/unit


PostBuild.IrrXML.Release:
/Users/aroberd/Documents/Neon-Engine/lib/Release/libIrrXML.a:
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/lib/Release/libIrrXML.a


PostBuild.assimp.Release:
PostBuild.IrrXML.Release: /Users/aroberd/Documents/Neon-Engine/lib/Release/libassimp.dylib
/Users/aroberd/Documents/Neon-Engine/lib/Release/libassimp.dylib:\
	/usr/lib/libz.dylib\
	/Users/aroberd/Documents/Neon-Engine/lib/Release/libIrrXML.a
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/lib/Release/libassimp.dylib


PostBuild.assimp_cmd.Release:
PostBuild.assimp.Release: /Users/aroberd/Documents/Neon-Engine/bin/Release/assimp
PostBuild.IrrXML.Release: /Users/aroberd/Documents/Neon-Engine/bin/Release/assimp
/Users/aroberd/Documents/Neon-Engine/bin/Release/assimp:\
	/Users/aroberd/Documents/Neon-Engine/lib/Release/libassimp.4.1.0.dylib\
	/usr/lib/libz.dylib\
	/Users/aroberd/Documents/Neon-Engine/lib/Release/libIrrXML.a
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/bin/Release/assimp


PostBuild.unit.Release:
PostBuild.assimp.Release: /Users/aroberd/Documents/Neon-Engine/bin/Release/unit
PostBuild.IrrXML.Release: /Users/aroberd/Documents/Neon-Engine/bin/Release/unit
/Users/aroberd/Documents/Neon-Engine/bin/Release/unit:\
	/Users/aroberd/Documents/Neon-Engine/lib/Release/libassimp.4.1.0.dylib\
	/usr/lib/libz.dylib\
	/Users/aroberd/Documents/Neon-Engine/lib/Release/libIrrXML.a
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/bin/Release/unit


PostBuild.IrrXML.MinSizeRel:
/Users/aroberd/Documents/Neon-Engine/lib/MinSizeRel/libIrrXML.a:
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/lib/MinSizeRel/libIrrXML.a


PostBuild.assimp.MinSizeRel:
PostBuild.IrrXML.MinSizeRel: /Users/aroberd/Documents/Neon-Engine/lib/MinSizeRel/libassimp.dylib
/Users/aroberd/Documents/Neon-Engine/lib/MinSizeRel/libassimp.dylib:\
	/usr/lib/libz.dylib\
	/Users/aroberd/Documents/Neon-Engine/lib/MinSizeRel/libIrrXML.a
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/lib/MinSizeRel/libassimp.dylib


PostBuild.assimp_cmd.MinSizeRel:
PostBuild.assimp.MinSizeRel: /Users/aroberd/Documents/Neon-Engine/bin/MinSizeRel/assimp
PostBuild.IrrXML.MinSizeRel: /Users/aroberd/Documents/Neon-Engine/bin/MinSizeRel/assimp
/Users/aroberd/Documents/Neon-Engine/bin/MinSizeRel/assimp:\
	/Users/aroberd/Documents/Neon-Engine/lib/MinSizeRel/libassimp.4.1.0.dylib\
	/usr/lib/libz.dylib\
	/Users/aroberd/Documents/Neon-Engine/lib/MinSizeRel/libIrrXML.a
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/bin/MinSizeRel/assimp


PostBuild.unit.MinSizeRel:
PostBuild.assimp.MinSizeRel: /Users/aroberd/Documents/Neon-Engine/bin/MinSizeRel/unit
PostBuild.IrrXML.MinSizeRel: /Users/aroberd/Documents/Neon-Engine/bin/MinSizeRel/unit
/Users/aroberd/Documents/Neon-Engine/bin/MinSizeRel/unit:\
	/Users/aroberd/Documents/Neon-Engine/lib/MinSizeRel/libassimp.4.1.0.dylib\
	/usr/lib/libz.dylib\
	/Users/aroberd/Documents/Neon-Engine/lib/MinSizeRel/libIrrXML.a
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/bin/MinSizeRel/unit


PostBuild.IrrXML.RelWithDebInfo:
/Users/aroberd/Documents/Neon-Engine/lib/RelWithDebInfo/libIrrXML.a:
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/lib/RelWithDebInfo/libIrrXML.a


PostBuild.assimp.RelWithDebInfo:
PostBuild.IrrXML.RelWithDebInfo: /Users/aroberd/Documents/Neon-Engine/lib/RelWithDebInfo/libassimp.dylib
/Users/aroberd/Documents/Neon-Engine/lib/RelWithDebInfo/libassimp.dylib:\
	/usr/lib/libz.dylib\
	/Users/aroberd/Documents/Neon-Engine/lib/RelWithDebInfo/libIrrXML.a
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/lib/RelWithDebInfo/libassimp.dylib


PostBuild.assimp_cmd.RelWithDebInfo:
PostBuild.assimp.RelWithDebInfo: /Users/aroberd/Documents/Neon-Engine/bin/RelWithDebInfo/assimp
PostBuild.IrrXML.RelWithDebInfo: /Users/aroberd/Documents/Neon-Engine/bin/RelWithDebInfo/assimp
/Users/aroberd/Documents/Neon-Engine/bin/RelWithDebInfo/assimp:\
	/Users/aroberd/Documents/Neon-Engine/lib/RelWithDebInfo/libassimp.4.1.0.dylib\
	/usr/lib/libz.dylib\
	/Users/aroberd/Documents/Neon-Engine/lib/RelWithDebInfo/libIrrXML.a
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/bin/RelWithDebInfo/assimp


PostBuild.unit.RelWithDebInfo:
PostBuild.assimp.RelWithDebInfo: /Users/aroberd/Documents/Neon-Engine/bin/RelWithDebInfo/unit
PostBuild.IrrXML.RelWithDebInfo: /Users/aroberd/Documents/Neon-Engine/bin/RelWithDebInfo/unit
/Users/aroberd/Documents/Neon-Engine/bin/RelWithDebInfo/unit:\
	/Users/aroberd/Documents/Neon-Engine/lib/RelWithDebInfo/libassimp.4.1.0.dylib\
	/usr/lib/libz.dylib\
	/Users/aroberd/Documents/Neon-Engine/lib/RelWithDebInfo/libIrrXML.a
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/bin/RelWithDebInfo/unit




# For each target create a dummy ruleso the target does not have to exist
/Users/aroberd/Documents/Neon-Engine/lib/Debug/libIrrXML.a:
/Users/aroberd/Documents/Neon-Engine/lib/Debug/libassimp.4.1.0.dylib:
/Users/aroberd/Documents/Neon-Engine/lib/MinSizeRel/libIrrXML.a:
/Users/aroberd/Documents/Neon-Engine/lib/MinSizeRel/libassimp.4.1.0.dylib:
/Users/aroberd/Documents/Neon-Engine/lib/RelWithDebInfo/libIrrXML.a:
/Users/aroberd/Documents/Neon-Engine/lib/RelWithDebInfo/libassimp.4.1.0.dylib:
/Users/aroberd/Documents/Neon-Engine/lib/Release/libIrrXML.a:
/Users/aroberd/Documents/Neon-Engine/lib/Release/libassimp.4.1.0.dylib:
/usr/lib/libz.dylib:
