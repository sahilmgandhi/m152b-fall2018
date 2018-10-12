`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:29:45 10/05/2018 
// Design Name: 
// Module Name:    register_file 
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
module register_file(Ra, Rb, Rw, WrEn, busW, clk, rst, busA, busB);

  input wire [4:0] Ra;
  input wire [4:0] Rb;
  input wire [4:0] Rw; 
  input wire WrEn, clk, rst;
  input wire [15:0] busW;
  output reg [15:0] busA; 
  output reg [15:0] busB;
  parameter size = 31;
  
  reg [15:0] data [size:0];
    
  //assign busA[15:0] = data[Ra];
  //assign busB[15:0] = data[Rb];
  
  integer i;
  
  always @(posedge clk) begin
	 if(rst)
	   begin
			for (i = 0; i <= size; i=i+1) begin
				data[i] <= 0;
			end
	   end
    else if(WrEn) 
      begin
   	    //Write enabled, write busW to Rw.
        data[Rw] = busW[15:0];
      end
	  
	  busA[15:0] <= data[Ra];
	  busB[15:0] <= data[Rb];
  end
  
endmodule
