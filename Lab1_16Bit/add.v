`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:24:35 10/05/2018 
// Design Name: 
// Module Name:    add 
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
module add(a, b, overflow, sum);
input [15:0] a, b;
output [15:0] sum;
output overflow;
wire [15:0] add_co; // carry out
assign sum[0] = a[0]^b[0];
assign add_co[0] = a[0]&b[0];
assign sum[1] = a[1]^b[1]^add_co[0];
assign add_co[1] = (a[1]&b[1])|(add_co[0]&(a[1]^b[1]));
assign sum[2] = a[2]^b[2]^add_co[1];
assign add_co[2] = (a[2]&b[2])|(add_co[1]&(a[2]^b[2]));
assign sum[3] = a[3]^b[3]^add_co[2];
assign add_co[3] = (a[3]&b[3])|(add_co[2]&(a[3]^b[3]));
assign sum[4] = a[4]^b[4]^add_co[3];
assign add_co[4] = (a[4]&b[4])|(add_co[3]&(a[4]^b[4]));
assign sum[5] = a[5]^b[5]^add_co[4];
assign add_co[5] = (a[5]&b[5])|(add_co[4]&(a[5]^b[5]));
assign sum[6] = a[6]^b[6]^add_co[5];
assign add_co[6] = (a[6]&b[6])|(add_co[5]&(a[6]^b[6]));
assign sum[7] = a[7]^b[7]^add_co[6];
assign add_co[7] = (a[7]&b[7])|(add_co[6]&(a[7]^b[7]));
assign sum[8] = a[8]^b[8]^add_co[7];
assign add_co[8] = (a[8]&b[8])|(add_co[7]&(a[8]^b[8]));
assign sum[9] = a[9]^b[9]^add_co[8];
assign add_co[9] = (a[9]&b[9])|(add_co[8]&(a[9]^b[9]));
assign sum[10] = a[10]^b[10]^add_co[9];
assign add_co[10] = (a[10]&b[10])|(add_co[9]&(a[10]^b[10]));
assign sum[11] = a[11]^b[11]^add_co[10];
assign add_co[11] = (a[11]&b[11])|(add_co[10]&(a[11]^b[11]));
assign sum[12] = a[12]^b[12]^add_co[11];
assign add_co[12] = (a[12]&b[12])|(add_co[11]&(a[12]^b[12]));
assign sum[13] = a[13]^b[13]^add_co[12];
assign add_co[13] = (a[13]&b[13])|(add_co[12]&(a[13]^b[13]));
assign sum[14] = a[14]^b[14]^add_co[13];
assign add_co[14] = (a[14]&b[14])|(add_co[13]&(a[14]^b[14]));
assign sum[15] = a[15]^b[15]^add_co[14];
assign add_co[15] = (a[15]&b[15])|(add_co[14]&(a[15]^b[15]));
assign overflow = add_co[15];
endmodule
