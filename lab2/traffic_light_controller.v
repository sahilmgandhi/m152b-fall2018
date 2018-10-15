`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:05:38 10/14/2018 
// Design Name: 
// Module Name:    traffic_light_controller 
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
module traffic_light_controller(
	input clk,
	input Sensor,
	input walkButton,
	
	output reg red1,
	output reg yellow1,
	output reg green1,
	
	output reg red2,
	output reg yellow2,
	output reg green2,
	
	output reg walk_light
    );
	 
	 wire one_sec_clk;
	 wire two_sec_clk;
	 wire three_sec_clk;
	 wire four_sec_clk;
	 
	 clock_divider clockDivider(.clk(clk), .out_clk(one_sec_clk));
	 multiple_clocks multipleClocks(.one_sec_clock(one_sec_clk), .two_sec_clock(two_sec_clk), .three_sec_clock(three_sec_clk), .six_sec_clock(six_sec_clk));
	 
	 always @(posedge one_sec_clk) begin
		// introduce logic here for the FSM
	 end

endmodule
