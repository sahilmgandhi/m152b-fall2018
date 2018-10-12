`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:29:14 10/03/2018 
// Design Name: 
// Module Name:    alu_tb 
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
module alu_tb(
    );
reg [15:0] a, b;
reg [3:0] ctrl;
wire [15:0] s;
wire overflow, zero;
integer i;
// (a,b): (1,1) (-12,12) (-1, Tmin) (Tmin, -1) (Tmax, 1)
initial begin
	for(i = 0; i<16; i=i+1)begin
	ctrl = i[3:0];
	a = 1;
	b = 1;
	#5;
	a = -12;
	b = 12;
	#5;
	a = -2;
	b = 16'b0111111111111111;
	#5;
	a = -1;
	b = 16'b1000000000000000;
	#5;
	a = 16'b1000000000000000;
	b = -1;
	#5;
	a = 16'b0111111111111111;
	b = 1;
	#5;
	end
	/*
	// 00
	ctrl = 4'b0000; // subtraction
	a = 1;
	b = 1;
	#5;
	a = -12;
	b = 12;
	#5;
	a = -1;
	b = 16'b1000000000000000;
	#5;
	a = 16'b1000000000000000;
	b = -1;
	#5;
	a = 16'b0111111111111111;
	b = 1;
	
	#5 ctrl = 4'b0001; // addition
	a = 1;
	b = 1;
	#5;
	a = -12;
	b = 12;
	#5;
	a = -1;
	b = 16'b1000000000000000;
	#5;
	a = 16'b1000000000000000;
	b = -1;
	#5;
	a = 16'b0111111111111111;
	b = 1;
	#5 ctrl = 4'b0010; // bitwise or
	#5 ctrl = 4'b0011; // bitwise and
	// 01
	#5 ctrl = 4'b0100; // decrement
	#5 ctrl = 4'b0101; // increment
	#5 ctrl = 4'b0110; // invert
	#5 ctrl = 4'b0111; // nothing
	// 10 
	#5 ctrl = 4'b1000; // logic shift left
	#5 ctrl = 4'b1001; // set on less equal
	#5 ctrl = 4'b1010; // logic shift right
	#5 ctrl = 4'b1011; // nothing
	// 11
	#5 ctrl = 4'b1100; // arith shift left
	#5 ctrl = 4'b1101; // nothing
	#5 ctrl = 4'b1110; // arith shift right
	#5 ctrl = 4'b1111; // nothing
	#5;
	*/
end
alu_16bit alu_16bit(a, b, ctrl, overflow, zero, s);
endmodule
