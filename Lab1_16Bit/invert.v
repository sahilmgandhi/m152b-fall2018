`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:19:43 10/05/2018 
// Design Name: 
// Module Name:    invert 
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
module inversion(in, invert);
input [15:0] in;
output [15:0] invert;
assign invert[0] = ~in[0];
assign invert[1] = ~in[1];
assign invert[2] = ~in[2];
assign invert[3] = ~in[3];
assign invert[4] = ~in[4];
assign invert[5] = ~in[5];
assign invert[6] = ~in[6];
assign invert[7] = ~in[7];
assign invert[8] = ~in[8];
assign invert[9] = ~in[9];
assign invert[10] = ~in[10];
assign invert[11] = ~in[11];
assign invert[12] = ~in[12];
assign invert[13] = ~in[13];
assign invert[14] = ~in[14];
assign invert[15] = ~in[15];

endmodule
