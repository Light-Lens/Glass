@ECHO OFF
title Build C++

if EXIST scripts (
    cd scripts
)

call Link.py

echo Locating Glass.exe
echo Opening Glass in Folder

cd ..\bin
start .
