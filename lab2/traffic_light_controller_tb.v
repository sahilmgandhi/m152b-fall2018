`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   10:18:27 10/17/2018
// Design Name:   traffic_light_controller
// Module Name:   C:/Users/sahil/Documents/GitHub/m152b_fall2018/lab2/traffic_light_controller_tb.v
// Project Name:  lab2
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: traffic_light_controller
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module traffic_light_controller_tb;

	// Inputs
	reg clk;
	reg sensor;
	reg walkButton;

	// Outputs
	wire mainRed;
	wire mainYellow;
	wire mainGreen;
	wire sideRed;
	wire sideYellow;
	wire sideGreen;
	wire walkLight;

	// Instantiate the Unit Under Test (UUT)
	traffic_light_controller uut (
		.clk(clk), 
		.sensor(sensor), 
		.walkButton(walkButton), 
		.mainRed(mainRed), 
		.mainYellow(mainYellow), 
		.mainGreen(mainGreen), 
		.sideRed(sideRed), 
		.sideYellow(sideYellow), 
		.sideGreen(sideGreen), 
		.walkLight(walkLight)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		sensor = 0;
		walkButton = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here
		walkButton = 1;
		#100
		walkButton = 0;
		
		#600
		sensor = 1;
		#100
		
		sensor = 0;
		
	end
	
	always begin 
		#1 clk = ~clk; 	
	end
      
endmodule

