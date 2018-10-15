`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:55:34 10/14/2018 
// Design Name: 
// Module Name:    multiple_clocks 
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
module multiple_clocks(
	input oneSecClock, 
	input rst,
	output reg twoSecClock = 0,
	output reg threeSecClock = 0,
	output reg sixSecClock = 0
    );
	 
	 reg [1:0] two_count;
	 reg [1:0] three_count;
	 reg [2:0] six_count;
	 
	 always @(posedge oneSecClock) begin
		if (rst) begin
			two_count <= 0;
			three_count <= 0;
			six_count <= 0;
		end
		else begin
			two_count <= two_count + 1;
			three_count <= three_count + 1;
			six_count <= six_count + 1;
			
			if (two_count >= 2) begin
				two_count = 0;
				twoSecClock = !twoSecClock;
			end
			if (three_count >= 3) begin
				three_count = 0;
				threeSecClock = !threeSecClock;
			end
			if (six_count >= 6) begin
				six_count = 0;
				sixSecClock = !sixSecClock;
			end
		end
		
	 end

endmodule
