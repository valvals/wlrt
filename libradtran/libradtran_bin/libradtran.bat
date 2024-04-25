@echo off
setlocal
cd /d %~dp0
cd libradtran_2.0.4
uvspec.exe < libradtran.inp > ../_out/libradtran.txt  2> uvspec.err
