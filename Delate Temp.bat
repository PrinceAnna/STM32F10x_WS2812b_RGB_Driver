copy EWARM\Debug\Exe\*.hex Debug.hex
copy EWARM\Release\Exe\*.hex Release.hex

del /Q EWARM\Debug\Exe\*.*
del /Q EWARM\Debug\List\*.*
del /Q EWARM\Debug\Obj\*.*

del /Q EWARM\Release\Exe\*.*
del /Q EWARM\Release\List\*.*
del /Q EWARM\Release\Obj\*.*

del /Q EWARM\settings\*.*

del /Q EWARM\*.dep
del /Q EWARM\*.ewt

exit