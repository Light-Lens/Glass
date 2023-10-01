@ECHO OFF
TITLE Compile Glass

IF EXIST scripts ( CD scripts )
CALL python Link.py %~1 %~2 %~3
CD ..
