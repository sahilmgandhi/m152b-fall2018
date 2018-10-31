@ECHO OFF
@REM ###########################################
@REM # Script file to run the flow 
@REM # 
@REM ###########################################
@REM #
@REM # Command line for ngdbuild
@REM #
ngdbuild -p xc5vlx50tff1136-1 -nt timestamp -bm Lab3_new.bmm "C:/Users/CS152B/Documents/m152b_fall2018/implementation/Lab3_new.ngc" -uc Lab3_new.ucf Lab3_new.ngd 

@REM #
@REM # Command line for map
@REM #
map -o Lab3_new_map.ncd -w -pr b -ol high -timing -detail Lab3_new.ngd Lab3_new.pcf 

@REM #
@REM # Command line for par
@REM #
par -w -ol high Lab3_new_map.ncd Lab3_new.ncd Lab3_new.pcf 

@REM #
@REM # Command line for post_par_trce
@REM #
trce -e 3 -xml Lab3_new.twx Lab3_new.ncd Lab3_new.pcf 

