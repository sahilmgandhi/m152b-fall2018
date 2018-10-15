`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:52:16 10/14/2018 
// Design Name: 
// Module Name:    clock_divider 
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
module clock_divider(
	input clk,
	input rst,
	output reg out_clk=0
);
reg [31:0] count=0;

always @ (posedge(clk))
begin
	if(rst==1)begin
		count<=0;
	end
	else begin
		count <= count + 1;
		if (count == 50000000) 
		begin
			count <= 32'b0;
			out_clk <= !out_clk;
		end
	end
end

endmodule
