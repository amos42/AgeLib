@echo off
wmake /f age_low.mak %1
copy age_low.h   c:\language\watcom\h\
copy age_low.lib c:\language\watcom\lib386\

