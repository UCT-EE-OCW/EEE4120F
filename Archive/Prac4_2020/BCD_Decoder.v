module BCD_Decoder(
    input [3:0]BCD,
    output reg [6:0]SevenSegment
);
//------------------------------------------------------------------------------
// Combinational circuit to convert BCD input to seven-segment output
always @(BCD) 
begin
case(BCD)
    // gfedcba
    4'd0 : SevenSegment <= 7'b0111111;  //     a
    4'd1 : SevenSegment <= 7'b0000110;  //    ----
    4'd2 : SevenSegment <= 7'b1011011;  //   |   |
    4'd3 : SevenSegment <= 7'b1001111;  //  f| g |b
    4'd4 : SevenSegment <= 7'b1100110;  //    ----
    4'd5 : SevenSegment <= 7'b1101101;  //   |   |
    4'd6 : SevenSegment <= 7'b1111101;  //  e|   |c
    4'd7 : SevenSegment <= 7'b0000111;  //    ----
    4'd8 : SevenSegment <= 7'b1111111;  //      d
    4'd9 : SevenSegment <= 7'b1101111;
default: SevenSegment <= 7'b0000000;
endcase
end
//--------------------------------------------------------------
endmodule 