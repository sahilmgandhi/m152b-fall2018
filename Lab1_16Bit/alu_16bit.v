`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:50:30 10/03/2018 
// Design Name: 
// Module Name:    alu_16bit 
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
module alu_16bit(a, b, ctrl, overflow, zero, s);
input [15:0] a, b;
input [3:0] ctrl;
output [15:0] s;
output overflow, zero;

wire [1:0] upper_ctrl = ctrl[3:2];
wire [1:0] lower_ctrl = ctrl[1:0];

// muxs to control value of overflow and s
wire overflow_mux[3:0];
wire [15:0] s_mux[3:0];

alu_00 alu_00(a, b, lower_ctrl, overflow_mux[0], s_mux[0]);
alu_01 alu_01(a, b, lower_ctrl, overflow_mux[1], s_mux[1]);
alu_10 alu_10(a, b, lower_ctrl, overflow_mux[2], s_mux[2]);
alu_11 alu_11(a, b, lower_ctrl, overflow_mux[3], s_mux[3]);

assign s = s_mux[upper_ctrl];
assign overflow = overflow_mux[upper_ctrl];
assign zero = ~(s[0]|s[1]|s[2]|s[3]|s[4]|s[5]|s[6]|s[7]|s[8]|s[9]|s[10]|s[11]|s[12]|s[13]|s[14]|s[15]);
endmodule
