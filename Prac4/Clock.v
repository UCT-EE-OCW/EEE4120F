`timescale 1ns / 1ps



module WallClock(
	// inputs

	//outputs
);

	//Add the reset


	//Add and debounce the buttons
	
	
	// registers for storing the time
    
    
	//Initialize seven segment
	SS_Driver SS_Driver1(
		Clk_100M, Reset,
		4’d1, 4’d2, 4’d3, 4’d4, // Use temporary test values
		SegmentDrivers, SevenSegment
	);
	
	//The main logic
	always @(posedge CLK100MHZ) begin
		// implement your logic here
	end
endmodule  