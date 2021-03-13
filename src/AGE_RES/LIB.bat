@echo off
wmake /f age_res.mak %1
copy age_res.h   c:\language\watcom\h\
copy age_res.lib c:\language\watcom\lib386\

