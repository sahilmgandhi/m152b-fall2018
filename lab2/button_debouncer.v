`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:41:39 10/12/2018 
// Design Name: 
// Module Name:    button_debouncer 
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
module button_debouncer(
    input button,
    input clk,
    input reset,
    output wire actualPressed
    );
	 
    wire [17:0] clk_dv_inc;
    reg [16:0]  clk_dv = 0;
    reg         clk_en = 0;
    reg         clk_en_d = 0;
    reg         inst_vld = 0;
    reg [2:0]   step_d = 0;
	 
	assign clk_dv_inc = clk_dv + 1;

   always @ (posedge clk) begin
      clk_dv   <= clk_dv_inc[16:0];
      clk_en   <= clk_dv_inc[17];
      clk_en_d <= clk_en;
   end
	 
	always @ (posedge clk) begin
    if (clk_en)
       begin
          step_d[2:0]  <= {button, step_d[2:1]};
       end
	end

   always @ (posedge clk) begin
       inst_vld <= ~step_d[0] & step_d[1] & clk_en_d;
	end
	
    assign actualPressed = inst_vld;

endmodule
