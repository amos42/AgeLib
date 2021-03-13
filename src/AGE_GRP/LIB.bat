@echo off
wmake /f age_grp.mak %1
copy age_grp.h   c:\language\watcom\h\
copy age_grp.lib c:\language\watcom\lib386\

