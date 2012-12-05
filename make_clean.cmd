cd /d %~d0%~p0
attrib -h *.suo
del *.suo
del *.sdf
del *.vcxproj.user
rmdir /s /q Debug
rmdir /s /q ipch
