# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.glfw.Debug:
/Users/aroberd/Documents/Neon-Engine/Dependencies/glfw/src/Debug/libglfw.dylib:
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/Dependencies/glfw/src/Debug/libglfw.dylib


PostBuild.glfw.Release:
/Users/aroberd/Documents/Neon-Engine/Dependencies/glfw/src/Release/libglfw.dylib:
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/Dependencies/glfw/src/Release/libglfw.dylib


PostBuild.glfw.MinSizeRel:
/Users/aroberd/Documents/Neon-Engine/Dependencies/glfw/src/MinSizeRel/libglfw.dylib:
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/Dependencies/glfw/src/MinSizeRel/libglfw.dylib


PostBuild.glfw.RelWithDebInfo:
/Users/aroberd/Documents/Neon-Engine/Dependencies/glfw/src/RelWithDebInfo/libglfw.dylib:
	/bin/rm -f /Users/aroberd/Documents/Neon-Engine/Dependencies/glfw/src/RelWithDebInfo/libglfw.dylib




# For each target create a dummy ruleso the target does not have to exist
