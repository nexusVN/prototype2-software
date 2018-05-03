# prototype2-software
The software provides:
Display UI includes:
+ LOAD & PROGRESS: load gcode file (32MB limited) from USB/SDCARD then extract to data and stored (PROGRESS) in BBB memory
+ REMOVE: remove loaded gcode file
+ PRINT: feeding coord packet data from CPU to MCU 
+ RESET: Reset printing progress and print again.
+ CANCEL: Cancel printing progress and discard current printing file.