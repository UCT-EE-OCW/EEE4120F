`timescale 1ns / 1ps



module WallClock(
	//inputs - these will depend on your board's constraint files

	//outputs - these will depend on your board's constraint files
	
);

	//Add the reset


	//Add and debounce the buttons
	wire MButton;
	wire HButton;
	
	// Instantiate Debounce modules here
	
	// registers for storing the time
    	reg [3:0]hours1=4'd0;
	reg [3:0]hours2=4'd0;
	reg [3:0]mins1=4'd0;
	reg [3:0]mins1=4'd0;
    
	//Initialize seven segment
	// You will need to change some signals depending on you constraints
	SS_Driver SS_Driver1(
		<clock_signal>, <reset_signal>,
		4’d1, 4’d2, 4’d3, 4’d4, // Use temporary test values before adding hours2, hours1, mins2, mins1
		SegmentDrivers, SevenSegment
	);
	
	//The main logic
	always @(posedge CLK100MHZ) begin
		// implement your logic here
	end
endmodule  
