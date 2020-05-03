# Compiled opencv_4.3.0 Library file
<br>To use  opencv4.3.0 in QT5.14.2,the source of opencv should be compiled fist.
<br>While doing this, I met many annoying questions.So I want to take notes.
##Notice
I compiled the sources on Windows¡Á64 platform.
<br>I do not recommend to compile the source code by self.Many strange errors could be met while building.
<br>So I upload the compiled files so that opencv could used directly with QT. 
## Basic process.
[Following this step](https://blog.csdn.net/qq_36308757/article/details/105083800)

## Errors while building
<br>-----------------------------------------------------------------------------------------------------------------------------------------
	1.mingw32-make[2]: *** [..\CMakeFiles\opencv_world.dir\build.make:11240: modules/world/CMakeFiles/opencv_world.dir/vs_version.rc.obj] Error 1
```javascript
[ 65% ] Building RC object modules/world/CMakeFiles/opencv_world.dir/vs_version.rc.obj
gcc: error: long: No such file or directory
C:\Mingw-w64\mingw32\bin\windres.exe: preprocessing failed.
mingw32-make[2]: *** [modules\world\CMakeFiles\opencv_world.dir\build.make:11240: modules/world/CMakeFiles/opencv_world.dir/vs_version.rc.obj] Error 1
mingw32-make[1]: *** [CMakeFiles\Makefile2:4789: modules/world/CMakeFiles/opencv_world.dir/all] Error 2
mingw32-make: *** [Makefile:179: all] Error 2
  }
```

  This [blog](https://blog.csdn.net/qq_34801642/article/details/105583164) could solve it
  <br>-----------------------------------------------------------------------------------------------------------------------------------------

	2.Problem linking shared library libopencv_core340.dll with MinGW 64
```javascript
[ 41%] Linking CXX shared library ../../bin/libopencv_core340.dll
C:/Rtools/mingw_64/bin/../lib/gcc/x86_64-w64-mingw32/4.9.3/../../../../x86_64-w64-mingw32/bin/ld.exe: i386 architecture of input file `CMakeFiles/opencv_core.dir/objects.a(vs_version.rc.obj)' is incompatible with i386:x86-64 output 
collect2.exe: error: ld returned 1 exit status 
make[2]: *** [bin/libopencv_core340.dll] Error 1
make[1]: *** [modules/core/CMakeFiles/opencv_core.dir/all] Error 2 
make: *** [all] Error 2
  }
```
  This [blog](https://blog.csdn.net/weixin_41698717/article/details/105827305) could solve it
<br>-----------------------------------------------------------------------------------------------------------------------------------------