`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:09:07 10/03/2018 
// Design Name: 
// Module Name:    alu_01 
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
module alu_01(a, b, op, overflow, s);
input [15:0] a, b;
input [1:0] op;
output [15:0] s;
output overflow;
wire [15:0] decrement, increment, invert;

// { most significant, ..., least significant } 
wire [15:0] s_mux [3:0];
assign s_mux[0] = decrement;
assign s_mux[1] = increment;
assign s_mux[2] = invert;
wire overflow_mux [3:0];

assign s = s_mux[op];
assign overflow = overflow_mux[op]; 

// Decrement
wire decrement_overflow;
add Decrement(a, 16'b1111111111111111, decrement_overflow, decrement);
assign overflow_mux[0] = a[15]&~decrement[15];

// Increment
wire increment_overflow;
add Increment(a, 16'b1, increment_overflow, increment);
assign overflow_mux[1] = ~a[15]&increment[15];

// Invert
inversion Invert(a, invert);
assign overflow_mux[2] = 0;

endmodule
