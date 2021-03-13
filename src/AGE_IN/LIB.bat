@echo off
wmake /f age_in.mak %1
copy age_in.h   c:\language\watcom\h\
copy age_in.lib c:\language\watcom\lib386\

