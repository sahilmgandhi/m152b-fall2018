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
  input sensor,
  input walkButton,
  
  output reg mainRed,
  output reg mainYellow,
  output reg mainGreen,
  
  output reg sideRed,
  output reg sideYellow,
  output reg sideGreen,
  
  output reg walkLight
  );
   
  wire one_sec_clk;

  clock_divider clockDivider(.clk(clk), .outClk(one_sec_clk));

  parameter MAIN_ST_G_NONSENS = 8'b0000_0000;
  parameter MAIN_ST_G = 8'b0000_0001;
  parameter MAIN_ST_SENS = 8'b0000_0010;
  parameter MAIN_ST_Y = 8'b0000_0100;
  parameter PED_WALK_ON = 8'b0000_1000;
  parameter SIDE_ST_G = 8'b0001_0000;
  parameter SIDE_ST_SENS = 8'b0010_0000;
  parameter SIDE_ST_Y = 8'b0100_0000;


  parameter state_bits = 8;
  reg [state_bits - 1:0] curr_state = MAIN_ST_G;
  reg [state_bits - 1:0] next_state = 0;
  reg [3:0] counter = 12;
  reg [3:0] next_counter = 0;

  wire walk_light_button;
  wire side_sensor;

  reg walk_light = 0;

  // Button debouncer should instead act more like a latch!
  button_debouncer walkLatch(.button(walkButton), .clk(clk), .actualPressed(walk_light_button));

  assign side_sensor = sensor;

  // Counter to count down. Useful for the 6 second, 3 second and 2 second clocks
  always @(posedge one_sec_clk) begin
    counter = counter - 1;
	 if (curr_state == MAIN_ST_G && counter == 7 && side_sensor) begin
			curr_state <= MAIN_ST_SENS;
			counter = 3;
	 end
	 if (curr_state == SIDE_ST_G && counter == 0 && side_sensor) begin
			curr_state <= SIDE_ST_SENS;
			counter = 3;
	 end
    if (counter == 0) begin
      curr_state <= next_state;
      counter = next_counter;
    end
  end

  // When the side sensor is on during the greenlight portion, we need to wait for 3 extra seconds (but what if we notice the side sensor as high several times)
  // The walk button should only work AFTER the main street light's yellow -> thus maybe it should be a latch?
  always @(curr_state or side_sensor or walk_light_button) begin
    if (walk_light_button == 1) begin
      walk_light = 1;
    end

    case (curr_state)
	 
	 // TODO FIX THIs
      MAIN_ST_G: begin
        next_state <= MAIN_ST_G_NONSENS;
		  next_counter <= 6; 
		  
		  /*
        // if we noticed a sensor of high then the next counter should be 3 to remain at the green light
        if (side_sensor && counter == 1) begin
          next_counter <= 3;
        end
        else begin
          next_state <= MAIN_ST_Y;
          next_counter <= 2;
        end
		  */
      end
		
		// TODO ADD MAIN_ST_G_NONSENS

      MAIN_ST_SENS: begin
        next_state <= MAIN_ST_Y;
        next_counter <= 2;
      end

      MAIN_ST_Y: begin
        next_state <= SIDE_ST_G;
        next_counter <= 6;
        if (walk_light) begin
          next_counter <= 3;
          next_state <= PED_WALK_ON;
        end
      end
		
		// TODO FIX THIS

      SIDE_ST_G: begin
        next_state <= SIDE_ST_SENS;
        
        // Same as the MAIN_ST_G state
        if (side_sensor && counter == 1) begin
          next_counter <= 3;
        end
        else begin
          next_state <= SIDE_ST_Y;
          next_counter <= 2;
        end
      end
		
		// TODO: fix this

      SIDE_ST_SENS: begin
        next_state <= SIDE_ST_Y;
        next_counter <= 2;
      end

      SIDE_ST_Y: begin
        // Walk light does NOT affect the side street's yellow
        next_state <= MAIN_ST_G;
        next_counter <= 12;
      end

      PED_WALK_ON: begin
        // reset register to reset the pedestrian walk light latch
        walk_light = 0;  

        next_state <= SIDE_ST_G;	 
        next_counter <= 6;
      end

    endcase
  end

  // Set the output based on the new state value
  always @(curr_state) begin
    // Switching the new state:
    case (curr_state)
      MAIN_ST_G: begin
        mainGreen = 1;
        mainRed = 0;
        mainYellow = 0;
        sideGreen = 0;
        sideYellow = 0;
        sideRed = 1;
        walkLight = 0;
      end
      MAIN_ST_Y: begin
        mainGreen = 0;
        mainRed = 0;
        mainYellow = 1;
        sideGreen = 0;
        sideYellow = 0;
        sideRed = 1;
        walkLight = 0;
      end
      MAIN_ST_SENS: begin
        mainGreen = 1;
        mainRed = 0;
        mainYellow = 0;
        sideGreen = 0;
        sideYellow = 0;
        sideRed = 1;
        walkLight = 0;
      end
		MAIN_ST_G_NONSENS: begin
        mainGreen = 1;
        mainRed = 0;
        mainYellow = 0;
        sideGreen = 0;
        sideYellow = 0;
        sideRed = 1;
        walkLight = 0;
      end

      SIDE_ST_G: begin
        mainGreen = 0;
        mainRed = 1;
        mainYellow = 0;
        sideGreen = 1;
        sideYellow = 0;
        sideRed = 0;
        walkLight = 0;
      end
      SIDE_ST_Y: begin
        mainGreen = 0;
        mainRed = 1;
        mainYellow = 0;
        sideGreen = 0;
        sideYellow = 1;
        sideRed = 0;
        walkLight = 0;
      end
      SIDE_ST_SENS: begin
        mainGreen = 0;
        mainRed = 1;
        mainYellow = 0;
        sideGreen = 1;
        sideYellow = 0;
        sideRed = 0;
        walkLight = 0;
      end

      // On pedestrian walk, set all red lights on!
      PED_WALK_ON: begin
        mainGreen = 0;
        mainRed = 1;
        mainYellow = 0;
        sideGreen = 0;
        sideYellow = 0;
        sideRed = 1;
        walkLight = 1;
      end
    endcase
  end

endmodule
