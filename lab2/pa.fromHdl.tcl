
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name lab2 -dir "C:/Users/sahil/Documents/GitHub/m152b_fall2018/lab2/planAhead_run_1" -part xc5vlx50tff1136-2
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property target_constrs_file "traffic_light_controller.ucf" [current_fileset -constrset]
set hdlfile [add_files [list {clock_divider.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {button_debouncer.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {traffic_light_controller.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set_property top traffic_light_controller $srcset
add_files [list {traffic_light_controller.ucf}] -fileset [get_property constrset [current_run]]
open_rtl_design -part xc5vlx50tff1136-2
