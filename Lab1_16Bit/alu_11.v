`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:09:23 10/03/2018 
// Design Name: 
// Module Name:    alu_11 
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
module alu_11(a, b, op, overflow, s);
input signed[15:0] a, b;
input [1:0] op;
output [15:0] s;
output overflow;
wire [15:0] arith_left, arith_right;
// { most significant, ..., least significant } 
wire [15:0] s_mux [3:0];
assign s_mux[0] = arith_left;
assign s_mux[2] = arith_right;
wire overflow_mux [3:0];

assign arith_left = a <<< b;
assign arith_right = a >>> b;
assign overflow_mux[0] = a[15]^arith_left[15];
assign overflow_mux[2] = a[15]^arith_right[15];

assign s = s_mux[op];
assign overflow = overflow_mux[op];

endmodule
