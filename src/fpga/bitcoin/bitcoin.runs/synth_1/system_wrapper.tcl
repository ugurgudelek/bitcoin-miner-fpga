# 
# Synthesis run script generated by Vivado
# 

set_param xicom.use_bs_reader 1
set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
set_msg_config -id {Synth 8-256} -limit 10000
set_msg_config -id {Synth 8-638} -limit 10000
create_project -in_memory -part xc7z020clg484-1

set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_msg_config -source 4 -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property webtalk.parent_dir C:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.cache/wt [current_project]
set_property parent.project_path C:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.xpr [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language VHDL [current_project]
set_property board_part em.avnet.com:zed:part0:1.3 [current_project]
set_property vhdl_version vhdl_2k [current_fileset]
add_files C:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.srcs/sources_1/bd/system/system.bd
set_property used_in_implementation false [get_files -all c:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.srcs/sources_1/bd/system/ip/system_processing_system7_0_1/system_processing_system7_0_1.xdc]
set_property used_in_implementation false [get_files -all c:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.srcs/sources_1/bd/system/ip/system_axi_timer_0_0/system_axi_timer_0_0.xdc]
set_property used_in_implementation false [get_files -all c:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.srcs/sources_1/bd/system/ip/system_axi_timer_0_0/system_axi_timer_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.srcs/sources_1/bd/system/ip/system_rst_processing_system7_0_100M_0/system_rst_processing_system7_0_100M_0_board.xdc]
set_property used_in_implementation false [get_files -all c:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.srcs/sources_1/bd/system/ip/system_rst_processing_system7_0_100M_0/system_rst_processing_system7_0_100M_0.xdc]
set_property used_in_implementation false [get_files -all c:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.srcs/sources_1/bd/system/ip/system_rst_processing_system7_0_100M_0/system_rst_processing_system7_0_100M_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.srcs/sources_1/bd/system/ip/system_auto_pc_0/system_auto_pc_0_ooc.xdc]
set_property used_in_implementation false [get_files -all C:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.srcs/sources_1/bd/system/system_ooc.xdc]
set_property is_locked true [get_files C:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.srcs/sources_1/bd/system/system.bd]

read_vhdl -library xil_defaultlib C:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.srcs/sources_1/bd/system/hdl/system_wrapper.vhd
read_xdc C:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.srcs/constrs_1/new/pins.xdc
set_property used_in_implementation false [get_files C:/Users/ugurg/OneDrive/Learnings/Courses/BIL569_Embedded/bitcoin/bitcoin.srcs/constrs_1/new/pins.xdc]

read_xdc dont_touch.xdc
set_property used_in_implementation false [get_files dont_touch.xdc]
synth_design -top system_wrapper -part xc7z020clg484-1
write_checkpoint -noxdef system_wrapper.dcp
catch { report_utilization -file system_wrapper_utilization_synth.rpt -pb system_wrapper_utilization_synth.pb }
