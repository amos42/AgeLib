@echo off
wmake /f age_obj.mak %1
copy age_obj.h   c:\language\watcom\h\
copy age_obj.lib c:\language\watcom\lib386\

