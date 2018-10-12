`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   12:53:09 10/05/2018
// Design Name:   register_file
// Module Name:   C:/Users/TA/Desktop/SJD/Lab1_2018/register_file_tb.v
// Project Name:  Lab1_2018
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: register_file
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module register_file_tb;

	// Inputs
	reg [4:0] Ra;
	reg [4:0] Rb;
	reg [4:0] Rw;
	reg WrEn;
	reg [15:0] busW;
	reg clk;
	reg rst;

	// Outputs
	wire [15:0] busA;
	wire [15:0] busB;

	// Instantiate the Unit Under Test (UUT)
	register_file uut (
		.Ra(Ra), 
		.Rb(Rb), 
		.Rw(Rw), 
		.WrEn(WrEn), 
		.busW(busW), 
		.clk(clk), 
		.rst(rst), 
		.busA(busA), 
		.busB(busB)
	);

	initial begin
		// Initialize Inputs
		$display("BEGIN %m");
		Ra = 6;
		Rb = 0;
		Rw = 0;
		WrEn = 0;
		busW = 0;
		clk = 0;
		rst = 0;
		
		rst = 1;
		clk = 1;
		#5
		clk = 0;
		rst = 0;

		// Wait 100 ns for global reset to finish
		#100
        
		// Add stimulus here
		
		//Write 12 to register 6.
		WrEn = 1;
		Rw = 6;
		busW = 12;
		#10
		
		//Read register 6 to expect 12.
		WrEn = 0;
		Ra = 6;
		#5
		if(busA != 16'b0000000000001100) begin 
			$display("ASSERTION FAILED in %m");
			$finish;
		end
		#5
		
		//Write 123 to register 31 and read from register 31 siumultaneously
		WrEn = 1;
		Ra = 31;
		Rw = 31;
		busW = 123;
		#10
		
		//Read register 0 which was assigned to zero at reset signal.
		WrEn = 0;
		busW = 0;
		
		#10
		Ra = 0;
		#5
		if(busA != 16'b0000000000000000) begin 
			$display("ASSERTION FAILED in %m");
			$finish;
		end
		#5
		
		//Read register 31 to expect 123.
		WrEn = 0;
		Ra = 31;
		#5
		if(busA != 16'b0000000001111011) begin 
			$display("ASSERTION FAILED in %m");
			$finish;
		end
		#5
		
		//Read register 6 and register 31 at the same time.
		WrEn = 0;
		Ra = 6;
		Rb = 31;
		#5
		if(busB != 16'b0000000001111011) begin 
			$display("ASSERTION FAILED in %m");
			$finish;
		end
		if(busA != 16'b0000000000001100) begin 
			$display("ASSERTION FAILED in %m");
			$finish;
		end
		#5
		
		rst = 1;
		
		// Reset everything, should be 0
		#10;
		rst = 0;
		Ra = 6;
		Rb = 31;
		
		/* 
		if(busB != 16'b0000000000000000) begin 
			$display("ASSERTION FAILED in %m");
			$finish;
		end
		if(busA != 16'b0000000000000000) begin 
			$display("ASSERTION FAILED in %m");
			$finish;
		end
		*/
		
		
		$display("All test cases passed in in %m");
		#20 $finish;
		
	end
	
	always begin 
		#5 clk = ~clk;
	end
      
endmodule

