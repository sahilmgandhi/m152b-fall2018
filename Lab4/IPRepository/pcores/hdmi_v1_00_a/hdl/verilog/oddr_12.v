//  ***************************************************************************
//  **  Copyright(C) 2008 by Xilinx, Inc. All rights reserved.               **
//  **                                                                       **
//  **  This text contains proprietary, confidential                         **
//  **  information of Xilinx, Inc. , is distributed by                      **
//  **  under license from Xilinx, Inc., and may be used,                    **
//  **  copied and/or disclosed only pursuant to the terms                   **
//  **  of a valid license agreement with Xilinx, Inc.                       **
//  **                                                                       **
//  **  Unmodified source code is guaranteed to place and route,             **
//  **  function and run at speed according to the datasheet                 **
//  **  specification. Source code is provided "as-is", with no              **
//  **  obligation on the part of Xilinx to provide support.                 **
//  **                                                                       **
//  **  Xilinx Hotline support of source code IP shall only include          **
//  **  standard level Xilinx Hotline support, and will only address         **
//  **  issues and questions related to the standard released Netlist        **
//  **  version of the core (and thus indirectly, the original core source). **
//  **                                                                       **
//  **  The Xilinx Support Hotline does not have access to source            **
//  **  code and therefore cannot answer specific questions related          **
//  **  to source HDL. The Xilinx Support Hotline will only be able          **
//  **  to confirm the problem in the Netlist version of the core.           **
//  **                                                                       **
//  **  This copyright and support notice must be retained as part           **
//  **  of this text at all times.                                           **
//  ***************************************************************************

///////////////////////////////////////////////////////////////////////////////
// Module Declaration
///////////////////////////////////////////////////////////////////////////////
 `timescale 1 ps / 1 ps
module oddr_12( 
  Clk,                          // Clock input
  Reset,                      // Reset input
  D1_12,                        
  D2_12,                        
  Q_12
  );

input  Clk;
input  Reset;
input [11:0] D1_12;
input [11:0] D2_12;
output [11:0] Q_12;

ODDR #(
	.DDR_CLK_EDGE("SAME_EDGE"),
	.INIT(1'b0),
	.SRTYPE("SYNC")
) oddr_inst_0 (
	.Q(Q_12[0]),
	.C(Clk),
	.CE(1'b1),
	.D1(D1_12[0]),
	.D2(D2_12[0]),
	.R(Reset),
	.S(1'b0)
);

ODDR #(
	.DDR_CLK_EDGE("SAME_EDGE"),
	.INIT(1'b0),
	.SRTYPE("SYNC")
) oddr_inst_1 (
	.Q(Q_12[1]),
	.C(Clk),
	.CE(1'b1),
	.D1(D1_12[1]),
	.D2(D2_12[1]),
	.R(Reset),
	.S(1'b0)
);

ODDR #(
	.DDR_CLK_EDGE("SAME_EDGE"),
	.INIT(1'b0),
	.SRTYPE("SYNC")
) oddr_inst_2 (
	.Q(Q_12[2]),
	.C(Clk),
	.CE(1'b1),
	.D1(D1_12[2]),
	.D2(D2_12[2]),
	.R(Reset),
	.S(1'b0)
);

ODDR #(
	.DDR_CLK_EDGE("SAME_EDGE"),
	.INIT(1'b0),
	.SRTYPE("SYNC")
) oddr_inst_3 (
	.Q(Q_12[3]),
	.C(Clk),
	.CE(1'b1),
	.D1(D1_12[3]),
	.D2(D2_12[3]),
	.R(Reset),
	.S(1'b0)
);

ODDR #(
	.DDR_CLK_EDGE("SAME_EDGE"),
	.INIT(1'b0),
	.SRTYPE("SYNC")
) oddr_inst_4 (
	.Q(Q_12[4]),
	.C(Clk),
	.CE(1'b1),
	.D1(D1_12[4]),
	.D2(D2_12[4]),
	.R(Reset),
	.S(1'b0)
);

ODDR #(
	.DDR_CLK_EDGE("SAME_EDGE"),
	.INIT(1'b0),
	.SRTYPE("SYNC")
) oddr_inst_5 (
	.Q(Q_12[5]),
	.C(Clk),
	.CE(1'b1),
	.D1(D1_12[5]),
	.D2(D2_12[5]),
	.R(Reset),
	.S(1'b0)
);

ODDR #(
	.DDR_CLK_EDGE("SAME_EDGE"),
	.INIT(1'b0),
	.SRTYPE("SYNC")
) oddr_inst_6 (
	.Q(Q_12[6]),
	.C(Clk),
	.CE(1'b1),
	.D1(D1_12[6]),
	.D2(D2_12[6]),
	.R(Reset),
	.S(1'b0)
);

ODDR #(
	.DDR_CLK_EDGE("SAME_EDGE"),
	.INIT(1'b0),
	.SRTYPE("SYNC")
) oddr_inst_7 (
	.Q(Q_12[7]),
	.C(Clk),
	.CE(1'b1),
	.D1(D1_12[7]),
	.D2(D2_12[7]),
	.R(Reset),
	.S(1'b0)
);

ODDR #(
	.DDR_CLK_EDGE("SAME_EDGE"),
	.INIT(1'b0),
	.SRTYPE("SYNC")
) oddr_inst_8 (
	.Q(Q_12[8]),
	.C(Clk),
	.CE(1'b1),
	.D1(D1_12[8]),
	.D2(D2_12[8]),
	.R(Reset),
	.S(1'b0)
);

ODDR #(
	.DDR_CLK_EDGE("SAME_EDGE"),
	.INIT(1'b0),
	.SRTYPE("SYNC")
) oddr_inst_9 (
	.Q(Q_12[9]),
	.C(Clk),
	.CE(1'b1),
	.D1(D1_12[9]),
	.D2(D2_12[9]),
	.R(Reset),
	.S(1'b0)
);
          
ODDR #(
	.DDR_CLK_EDGE("SAME_EDGE"),
	.INIT(1'b0),
	.SRTYPE("SYNC")
) oddr_inst_10 (
	.Q(Q_12[10]),
	.C(Clk),
	.CE(1'b1),
	.D1(D1_12[10]),
	.D2(D2_12[10]),
	.R(Reset),
	.S(1'b0)
);

ODDR #(
	.DDR_CLK_EDGE("SAME_EDGE"),
	.INIT(1'b0),
	.SRTYPE("SYNC")
) oddr_inst_11 (
	.Q(Q_12[11]),
	.C(Clk),
	.CE(1'b1),
	.D1(D1_12[11]),
	.D2(D2_12[11]),
	.R(Reset),
	.S(1'b0)
);

endmodule
