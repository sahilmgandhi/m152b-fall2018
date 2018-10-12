`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:09:35 10/03/2018 
// Design Name: 
// Module Name:    alu_10 
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
module alu_10(a, b, op, overflow, s);
input [15:0] a, b;
input [1:0] op;
output [15:0] s;
output overflow;
wire [15:0] logic_left, logic_right, set_less_equal;
// { most significant, ..., least significant } 
wire [15:0] s_mux [3:0];
assign s_mux[0] = logic_left;
assign s_mux[1] = set_less_equal;
assign s_mux[2] = logic_right;
wire overflow_mux [3:0];

assign logic_left = a << b;
assign logic_right = a >> b;
assign overflow_mux[0] = 1'b0;
assign overflow_mux[1] = 1'b0;
assign overflow_mux[2] = 1'b0;

// Subtract
wire [15:0] invert_a, negative_a, subtraction;
wire invert_a_overflow, subtract_overflow;
inversion Invert_A(a, invert_a);
add Negative_A(invert_a, 16'b1, invert_a_overflow, negative_a);
add Subtract(b, negative_a, subtract_overflow, subtraction);
assign set_less_equal[15:1] = 15'b0;
assign set_less_equal[0] = (a[15]&(~b[15]))|~subtraction[15];

assign s = s_mux[op];
assign overflow = overflow_mux[op];

endmodule
