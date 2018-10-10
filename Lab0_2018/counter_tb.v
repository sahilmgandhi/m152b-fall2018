`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:41:30 10/01/2018 
// Design Name: 
// Module Name:    counter_tb 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module first_counter_tb();

// Declare inputs as regs and outputs as wires
reg clock, reset, enable;
wire [3:0] counter_out;
// Initialize all variables
initial begin
 $display ("time\t clk reset enable counter");
 $monitor ("%g\t %b %b %b %b",
 $time, clock, reset, enable, counter_out);
 clock = 1; // initial value of clock
 reset = 0; // initial value of reset
 enable = 0; // initial value of enable
 #5 reset = 1; // Assert the reset
 #10 reset = 0; // De-assert the reset
 #10 enable = 1; // Assert enable
 //#100 enable = 0; // De-assert enable
 //#5 $finish; // Terminate simulation
end
// Clock generator
always begin
 #5 clock = ~clock; // Toggle clock every 5 ticks
end
// Connect DUT to test bench
counter U_counter (
clock,
reset,
enable,
counter_out
);
endmodule