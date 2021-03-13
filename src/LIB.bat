@echo off
wmake /f age.mak %1
copy age.h   c:\language\watcom\h\
copy age.lib c:\language\watcom\lib386\

