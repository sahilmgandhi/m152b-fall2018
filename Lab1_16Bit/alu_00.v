`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:08:49 10/03/2018 
// Design Name: 
// Module Name:    alu_00 
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
module alu_00(a, b, op, overflow, s);
input [15:0] a, b;
input [1:0] op;
output [15:0] s;
output overflow;

wire [15:0] subtraction, addition, bit_or, bit_and;
// { most significant, ..., least significant } 
wire [15:0] s_mux [3:0];
assign s_mux[0] = subtraction;
assign s_mux[1] = addition;
assign s_mux[2] = bit_or;
assign s_mux[3] = bit_and;
wire overflow_mux [3:0];

assign s = s_mux[op];
assign overflow = overflow_mux[op]; 

// Subtract
wire [15:0] invert_b;
wire invert_b_overflow; //ignore later
wire subtract_overflow;
wire [15:0] negative_b;
inversion Invert_B(b, invert_b);
add Negative_B(invert_b, 16'b1, invert_b_overflow, negative_b);
add Subtract(a, negative_b, subtract_overflow, subtraction);
assign overflow_mux[0] = (a[15]^b[15])&~(b[15]^subtraction[15]);

// Add
wire add_overflow;
add Add(a, b, add_overflow, addition);
assign overflow_mux[1] = ~(a[15]^b[15])&(b[15]^addition[15]); 

// Bitwise OR
assign bit_or[0] = a[0]|b[0];
assign bit_or[1] = a[1]|b[1];
assign bit_or[2] = a[2]|b[2];
assign bit_or[3] = a[3]|b[3];
assign bit_or[4] = a[4]|b[4];
assign bit_or[5] = a[5]|b[5];
assign bit_or[6] = a[6]|b[6];
assign bit_or[7] = a[7]|b[7];
assign bit_or[8] = a[8]|b[8];
assign bit_or[9] = a[9]|b[9];
assign bit_or[10] = a[10]|b[10];
assign bit_or[11] = a[11]|b[11];
assign bit_or[12] = a[12]|b[12];
assign bit_or[13] = a[13]|b[13];
assign bit_or[14] = a[14]|b[14];
assign bit_or[15] = a[15]|b[15];
assign overflow_mux[2] = 0;

// Bitwise AND
assign bit_and[0] = a[0]&b[0];
assign bit_and[1] = a[1]&b[1];
assign bit_and[2] = a[2]&b[2];
assign bit_and[3] = a[3]&b[3];
assign bit_and[4] = a[4]&b[4];
assign bit_and[5] = a[5]&b[5];
assign bit_and[6] = a[6]&b[6];
assign bit_and[7] = a[7]&b[7];
assign bit_and[8] = a[8]&b[8];
assign bit_and[9] = a[9]&b[9];
assign bit_and[10] = a[10]&b[10];
assign bit_and[11] = a[11]&b[11];
assign bit_and[12] = a[12]&b[12];
assign bit_and[13] = a[13]&b[13];
assign bit_and[14] = a[14]&b[14];
assign bit_and[15] = a[15]&b[15];
assign overflow_mux[3] = 0;

endmodule
