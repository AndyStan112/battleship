This project uses the `SFML` c++ graphics library, version 2.5.1 as seen here: https://www.sfml-dev.org/download/sfml/2.5.1/

It is **_very_** important that you use the **_exact same_** gcc compiler that `SFML` was built with, in this case: [**_GCC 7.3.0_**](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/), otherwise you will not be able to run this program!

The run command is sh start.sh. It will show an error that can be safely ignored because on the first iteration it hasn't build the executable for the client but the second iteration finishes the build.