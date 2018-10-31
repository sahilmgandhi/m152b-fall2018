------------------------------------------------------------------------
--	dvma/user_logic.vhd  -- user logic File for DVMA core
------------------------------------------------------------------------
-- Author:  Tinghui WANG (Steve)
--	Copyright 2001 Digilent, Inc.
------------------------------------------------------------------------
-- Module description
--		Reads pixel data from VFBC interface of MPMC
--		Generate XSVI signals according to software configurations.
--
--  Inputs:
-- 	PIXCLK_I - pixel clock input
--		PLL_LOCKED_I - pixel clock PLL locked signal
--		VFBC_CMD_IDLE - vfbc cmd port idle status signal
-- 	VFBC_CMD_FULL - vfbc cmd port fifo full signal
-- 	VFBC_CMD_ALMOST_FULL - vfbc cmd port fifo almost full signal
-- 	VFBC_RD_DATA - vfbc read fifo data
--		VFBC_RD_EMPTY - vfbc read fifo empty signal
-- 	VFBC_RD_ALMOST_EMPTY - vfbc read fifo empty signal
--		
--  Outputs:
--		VFBC_CMD_CLK - vfbc cmd fifo clock signal
--		VFBC_CMD_RESET - vfbc cmd port reset signal
--		VFBC_CMD_DATA - vfbc cmd signals
--		VFBC_CMD_WRITE - vfbc write cmd signals
--		VFBC_CMD_END - vfbc end cmd signal
-- 	VFBC_RD_CLK - vfbc read fifo clock
-- 	VFBC_RD_RESET - vfbc read fifo reset
-- 	VFBC_RD_FLUSH - vfbc flush read fifo signal
-- 	VFBC_RD_END_BURST -vfbc end burst signals
--		XSVI_PIXCLK - xsvi pixel clock
--		XSVI_HSYNC - horizontal synchronization
--		XSVI_VSYNC - vertical synchronization
--		XSVI_ACTIVE_VIDEO - video data active
--		XSVI_VIDEO_DATA - video data (RGB888)
--		DEBUG_O - debug signals
--
------------------------------------------------------------------------
-- Revision History:
--
--	09Mar2011 (SteveW): v1.0 released
--
------------------------------------------------------------------------

------------------------------------------------------------------------------
-- user_logic.vhd - entity/architecture pair
------------------------------------------------------------------------------
--
-- ***************************************************************************
-- ** Copyright (c) 1995-2010 Xilinx, Inc.  All rights reserved.            **
-- **                                                                       **
-- ** Xilinx, Inc.                                                          **
-- ** XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"         **
-- ** AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND       **
-- ** SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,        **
-- ** OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,        **
-- ** APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION           **
-- ** THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,     **
-- ** AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE      **
-- ** FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY              **
-- ** WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE               **
-- ** IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR        **
-- ** REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF       **
-- ** INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS       **
-- ** FOR A PARTICULAR PURPOSE.                                             **
-- **                                                                       **
-- ***************************************************************************
--
------------------------------------------------------------------------------
-- Filename:          user_logic.vhd
-- Version:           1.00.a
-- Description:       User logic.
-- Date:              Mon Feb 21 10:35:05 2011 (by Create and Import Peripheral Wizard)
-- VHDL Standard:     VHDL'93
------------------------------------------------------------------------------
-- Naming Conventions:
--   active low signals:                    "*_n"
--   clock signals:                         "clk", "clk_div#", "clk_#x"
--   reset signals:                         "rst", "rst_n"
--   generics:                              "C_*"
--   user defined types:                    "*_TYPE"
--   state machine next state:              "*_ns"
--   state machine current state:           "*_cs"
--   combinatorial signals:                 "*_com"
--   pipelined or register delay signals:   "*_d#"
--   counter signals:                       "*cnt*"
--   clock enable signals:                  "*_ce"
--   internal version of output port:       "*_i"
--   device pins:                           "*_pin"
--   ports:                                 "- Names begin with Uppercase"
--   processes:                             "*_PROCESS"
--   component instantiations:              "<ENTITY_>I_<#|FUNC>"
------------------------------------------------------------------------------

-- DO NOT EDIT BELOW THIS LINE --------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library proc_common_v3_00_a;
use proc_common_v3_00_a.proc_common_pkg.all;

-- DO NOT EDIT ABOVE THIS LINE --------------------

--USER libraries added here

------------------------------------------------------------------------------
-- Entity section
------------------------------------------------------------------------------
-- Definition of Generics:
--   C_SLV_DWIDTH                 -- Slave interface data bus width
--   C_NUM_REG                    -- Number of software accessible registers
--
-- Definition of Ports:
--   Bus2IP_Clk                   -- Bus to IP clock
--   Bus2IP_Reset                 -- Bus to IP reset
--   Bus2IP_Data                  -- Bus to IP data bus
--   Bus2IP_BE                    -- Bus to IP byte enables
--   Bus2IP_RdCE                  -- Bus to IP read chip enable
--   Bus2IP_WrCE                  -- Bus to IP write chip enable
--   IP2Bus_Data                  -- IP to Bus data bus
--   IP2Bus_RdAck                 -- IP to Bus read transfer acknowledgement
--   IP2Bus_WrAck                 -- IP to Bus write transfer acknowledgement
--   IP2Bus_Error                 -- IP to Bus error response
------------------------------------------------------------------------------

entity user_logic is
  generic
  (
    -- ADD USER GENERICS BELOW THIS LINE ---------------
    --USER generics added here
	 --VFBC
	 C_VFBC_RDWD_DATA_WIDTH : integer := 16;
	 --XSVI
 	 C_NUM_DATA_CHANNELS : integer := 3;
	 C_DATA_WIDTH : integer := 8;
	 C_DDR_OUT : integer := 0;
    -- ADD USER GENERICS ABOVE THIS LINE ---------------

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol parameters, do not add to or delete
    C_SLV_DWIDTH                   : integer              := 32;
    C_NUM_REG                      : integer              := 32
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );
  port
  (
    -- ADD USER PORTS BELOW THIS LINE ------------------
    --USER ports added here
	 PIXCLK_I : in  std_logic;
	 PLL_LOCKED_I : in std_logic;
	 DEBUG_O : out std_logic_vector (0 to 7);
	 -- VFBC Cmd Ports
	 VFBC_CMD_CLK : out std_logic;
	 VFBC_CMD_IDLE : in std_logic;
	 VFBC_CMD_RESET : out std_logic;
	 VFBC_CMD_DATA : out std_logic_vector (31 downto 0);
	 VFBC_CMD_WRITE : out std_logic;
	 VFBC_CMD_END : out std_logic;
	 VFBC_CMD_FULL : in std_logic;
	 VFBC_CMD_ALMOST_FULL : in std_logic;
	 -- VFBC Read Ports
	 VFBC_RD_CLK : out std_logic;
	 VFBC_RD_RESET : out std_logic;
	 VFBC_RD_FLUSH : out std_logic;
	 VFBC_RD_READ : out std_logic;
	 VFBC_RD_END_BURST : out std_logic;
	 VFBC_RD_DATA : in std_logic_vector (C_VFBC_RDWD_DATA_WIDTH-1 downto 0);
	 VFBC_RD_EMPTY : in std_logic;
	 VFBC_RD_ALMOST_EMPTY : in std_logic;
	 -- VFBC Write Ports
	 --	VFBC_WD_Clk : out std_logic;
	 --	VFBC_WD_Reset : out std_logic;
	 --	VFBC_WD_Flush : out std_logic;
	 --	VFBC_WD_Write : out std_logic;
	 --	VFBC_WD_Data : out std_logic_vector (C_VFBC_RDWD_DATA_WIDTH-1 downto 0);
	 --	VFBC_WD_DataByteEn : out std_logic_vector (C_VFBC_WRDWD_DATA_WIDTH/8-1 downto 0);
	 --	VFBC_WD_EndBurst : out std_logic;
	 --	VFBC_WD_Full : in std_logic;
	 --	VFBC_WD_Almost_Full : in std_logic;
 
 	 -- XSVI Output Ports
	 XSVI_PIXCLK : out std_logic;
	 XSVI_HSYNC : out std_logic;
	 XSVI_VSYNC : out std_logic;
	 XSVI_ACTIVE_VIDEO : out std_logic;
	 XSVI_VIDEO_DATA : out std_logic_vector(23 downto 0);
    -- ADD USER PORTS ABOVE THIS LINE ------------------

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol ports, do not add to or delete
    Bus2IP_Clk                     : in  std_logic;
    Bus2IP_Reset                   : in  std_logic;
    Bus2IP_Data                    : in  std_logic_vector(0 to C_SLV_DWIDTH-1);
    Bus2IP_BE                      : in  std_logic_vector(0 to C_SLV_DWIDTH/8-1);
    Bus2IP_RdCE                    : in  std_logic_vector(0 to C_NUM_REG-1);
    Bus2IP_WrCE                    : in  std_logic_vector(0 to C_NUM_REG-1);
    IP2Bus_Data                    : out std_logic_vector(0 to C_SLV_DWIDTH-1);
    IP2Bus_RdAck                   : out std_logic;
    IP2Bus_WrAck                   : out std_logic;
    IP2Bus_Error                   : out std_logic
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );

  attribute SIGIS : string;
  attribute SIGIS of Bus2IP_Clk    : signal is "CLK";
  attribute SIGIS of Bus2IP_Reset  : signal is "RST";

end entity user_logic;

------------------------------------------------------------------------------
-- Architecture section
------------------------------------------------------------------------------

architecture IMP of user_logic is

  --USER signal declarations added here, as needed for user logic
  signal hcnt : std_logic_vector(0 to 13);
  signal vcnt : std_logic_vector(0 to 13);
  
  signal xsvi_hsync_i : std_logic;
  signal xsvi_vsync_i : std_logic;
  signal xsvi_hsync_d1 : std_logic;
  signal xsvi_vsync_d1 : std_logic;
  signal xsvi_hblank_i : std_logic;
  signal xsvi_vblank_i : std_logic;
  signal xsvi_active_video_i : std_logic;
  signal xsvi_video_data_i : std_logic_vector(23 downto 0);
  
  signal vfbc_cmd0 : std_logic_vector(31 downto 0);
  signal vfbc_cmd1 : std_logic_vector(31 downto 0);
  signal vfbc_cmd2 : std_logic_vector(31 downto 0);
  signal vfbc_cmd3 : std_logic_vector(31 downto 0);
  
  signal vfbc_cmd_data_i : std_logic_vector(31 downto 0);
  signal vfbc_cmd_write_i : std_logic;
  
  signal vfbc_rd_reset_i : std_logic;
  
  ------------------------------------------
  -- Signals for user logic slave model s/w accessible register example
  ------------------------------------------
  signal dvma_cr                        : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal dvma_fwr                       : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal dvma_fhr                       : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal dvma_fbar                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal dvma_flsr                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal dvma_hsr                       : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal dvma_hfpr                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal dvma_hbpr                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal dvma_htr                       : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal dvma_vsr                       : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal dvma_vfpr                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal dvma_vbpr                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal dvma_vtr                       : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg13                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg14                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg15                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg16                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg17                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg18                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg19                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg20                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg21                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg22                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg23                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg24                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg25                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg26                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg27                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg28                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg29                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg30                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg31                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg_write_sel              : std_logic_vector(0 to 31);
  signal slv_reg_read_sel               : std_logic_vector(0 to 31);
  signal slv_ip2bus_data                : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_read_ack                   : std_logic;
  signal slv_write_ack                  : std_logic;

begin

  --USER logic implementation added here
  
  --HV_CNT_PROC : horizontal and vertical counter
  HV_CNT_PROC: process (PIXCLK_I) is
  begin
	if PIXCLK_I'event and PIXCLK_I = '1' then
		if Bus2IP_Reset = '1' or PLL_LOCKED_I = '0' or dvma_cr(C_SLV_DWIDTH-1) = '0' then
			hcnt <= (others => '0');
			vcnt <= (others => '0');
		else
			if hcnt < dvma_htr then
				hcnt <= hcnt + 1;
			else
				hcnt <= (others => '0');
				if vcnt < dvma_vtr then
					vcnt <= vcnt + 1;
				else
					vcnt <= (others => '0');
				end if;
			end if;
		end if;
	end if;
  end process HV_CNT_PROC;

  --Assign ALL XSVI Signals
  xsvi_hsync_i <= '1' when (hcnt < dvma_hsr) else
						'0';
  xsvi_vsync_i <= '1' when (vcnt < dvma_vsr) else
						'0';
  xsvi_hblank_i <= '1' when (hcnt >= dvma_hbpr) and (hcnt < dvma_hfpr) else
						 '0';
  xsvi_vblank_i <= '1' when (vcnt >= dvma_vbpr) and (vcnt < dvma_vfpr) else
						 '0';
  xsvi_active_video_i <= xsvi_hblank_i and xsvi_vblank_i;
  
  --DELAYED OUTPUT for ALL XSVI Signals
  XSVI_DELAY_PROC : process (PIXCLK_I) is
  begin
	if PIXCLK_I'event and PIXCLK_I = '1' then
		if Bus2IP_Reset = '1' or PLL_LOCKED_I = '0' or dvma_cr(C_SLV_DWIDTH-1) = '0' then
			XSVI_HSYNC <= '0';
			XSVI_VSYNC <= '0';
			xsvi_hsync_d1 <= '0';
			xsvi_vsync_d1 <= '0';
			XSVI_ACTIVE_VIDEO <= '0';
			XSVI_VIDEO_DATA <= (others => '0');
		else
			XSVI_HSYNC <= xsvi_hsync_d1;
			xsvi_hsync_d1 <= xsvi_hsync_i;
			XSVI_VSYNC <= xsvi_vsync_d1;
			xsvi_vsync_d1 <= xsvi_vsync_i;
			XSVI_ACTIVE_VIDEO <= xsvi_active_video_i;
			XSVI_VIDEO_DATA <= xsvi_video_data_i;
		end if;
	end if;
  end process XSVI_DELAY_PROC;
  
  XSVI_PIXCLK <= PIXCLK_I;
  xsvi_video_data_i <= VFBC_RD_DATA(3 downto 0) & x"0" & VFBC_RD_DATA(15 downto 12) & x"0" & VFBC_RD_DATA(11 downto 8) & x"0";

  --------------------------------
  -- VFBC Command Logic
  --------------------------------

  VFBC_CMD_CLK <= PIXCLK_I;
  VFBC_CMD_RESET <= '1' when Bus2IP_Reset = '1' or PLL_LOCKED_I = '0' else
						  '0'; -- reset at the very beginning
  VFBC_CMD_DATA <= vfbc_cmd_data_i;
  VFBC_CMD_WRITE <= vfbc_cmd_write_i;
  VFBC_CMD_END <= '0'; -- never ends
  
  -- Generate command according to registers, 2 bytes per pixel
  vfbc_cmd0 <= x"0000" & dvma_fwr(C_SLV_DWIDTH-15 to C_SLV_DWIDTH-1) & '0';
  vfbc_cmd1 <= '0' & dvma_fbar(1 to C_SLV_DWIDTH-1);
  vfbc_cmd2 <= x"0000" & dvma_fhr(C_SLV_DWIDTH-16 to C_SLV_DWIDTH-1);
  vfbc_cmd3 <= x"0000" & dvma_flsr(C_SLV_DWIDTH-15 to C_SLV_DWIDTH-1) & '0';
  
  -- Feed command into VFBC Cmd Port at the beginning of each frame
  VFBC_FEED_CMD_PROC : process (PIXCLK_I) is
  begin
	if PIXCLK_I'event and PIXCLK_I = '1' then
		if vcnt = 0 and hcnt = 1 then
			vfbc_cmd_data_i <= vfbc_cmd0;
			vfbc_cmd_write_i <= '1';
		elsif vcnt = 0 and hcnt = 2 then
			vfbc_cmd_data_i <= vfbc_cmd1;
			vfbc_cmd_write_i <= '1';
		elsif vcnt = 0 and hcnt = 3 then
			vfbc_cmd_data_i <= vfbc_cmd2;
			vfbc_cmd_write_i <= '1';
		elsif vcnt = 0 and hcnt = 4 then
			vfbc_cmd_data_i <= vfbc_cmd3;
			vfbc_cmd_write_i <= '1';
		else
			vfbc_cmd_data_i <= (others=>'0');
			vfbc_cmd_write_i <= '0';
		end if;
	end if;
  end process VFBC_FEED_CMD_PROC;
  
  --------------------------------
  -- VFBC Read Logic
  --------------------------------
  VFBC_RD_CLK <= PIXCLK_I;
  VFBC_RD_RESET <= vfbc_rd_reset_i;
  VFBC_RD_FLUSH <= '0';
  VFBC_RD_READ <= xsvi_active_video_i;
  VFBC_RD_END_BURST <= '0';
  
  -- Reset VFBC Read Port at the beginning of each frame
  VFBC_READ_DATA_PROC : process (PIXCLK_I) is
  begin
	if PIXCLK_I'event and PIXCLK_I = '1' then
		if vcnt = 0 and hcnt < 10 then
			vfbc_rd_reset_i <= '1';
		else
			vfbc_rd_reset_i <= '0';
		end if;
	end if;
  end process VFBC_READ_DATA_PROC;
  
  -- Debug Ports
  DEBUG_O(0) <= vfbc_cmd_full;
  DEBUG_O(1) <= vfbc_cmd_almost_full;
  DEBUG_O(2) <= vfbc_cmd_idle;
  DEBUG_O(3) <= vfbc_rd_empty;
  DEBUG_O(4) <= vfbc_rd_almost_empty; 
  DEBUG_O(5) <= vfbc_rd_reset_i;
  DEBUG_O(6) <= '1';
  DEBUG_O(7) <= xsvi_active_video_i;
  
  ------------------------------------------
  -- Example code to read/write user logic slave model s/w accessible registers
  -- 
  -- Note:
  -- The example code presented here is to show you one way of reading/writing
  -- software accessible registers implemented in the user logic slave model.
  -- Each bit of the Bus2IP_WrCE/Bus2IP_RdCE signals is configured to correspond
  -- to one software accessible register by the top level template. For example,
  -- if you have four 32 bit software accessible registers in the user logic,
  -- you are basically operating on the following memory mapped registers:
  -- 
  --    Bus2IP_WrCE/Bus2IP_RdCE   Memory Mapped Register
  --                     "1000"   C_BASEADDR + 0x0
  --                     "0100"   C_BASEADDR + 0x4
  --                     "0010"   C_BASEADDR + 0x8
  --                     "0001"   C_BASEADDR + 0xC
  -- 
  ------------------------------------------
  slv_reg_write_sel <= Bus2IP_WrCE(0 to 31);
  slv_reg_read_sel  <= Bus2IP_RdCE(0 to 31);
  slv_write_ack     <= Bus2IP_WrCE(0) or Bus2IP_WrCE(1) or Bus2IP_WrCE(2) or Bus2IP_WrCE(3) or Bus2IP_WrCE(4) or Bus2IP_WrCE(5) or Bus2IP_WrCE(6) or Bus2IP_WrCE(7) or Bus2IP_WrCE(8) or Bus2IP_WrCE(9) or Bus2IP_WrCE(10) or Bus2IP_WrCE(11) or Bus2IP_WrCE(12) or Bus2IP_WrCE(13) or Bus2IP_WrCE(14) or Bus2IP_WrCE(15) or Bus2IP_WrCE(16) or Bus2IP_WrCE(17) or Bus2IP_WrCE(18) or Bus2IP_WrCE(19) or Bus2IP_WrCE(20) or Bus2IP_WrCE(21) or Bus2IP_WrCE(22) or Bus2IP_WrCE(23) or Bus2IP_WrCE(24) or Bus2IP_WrCE(25) or Bus2IP_WrCE(26) or Bus2IP_WrCE(27) or Bus2IP_WrCE(28) or Bus2IP_WrCE(29) or Bus2IP_WrCE(30) or Bus2IP_WrCE(31);
  slv_read_ack      <= Bus2IP_RdCE(0) or Bus2IP_RdCE(1) or Bus2IP_RdCE(2) or Bus2IP_RdCE(3) or Bus2IP_RdCE(4) or Bus2IP_RdCE(5) or Bus2IP_RdCE(6) or Bus2IP_RdCE(7) or Bus2IP_RdCE(8) or Bus2IP_RdCE(9) or Bus2IP_RdCE(10) or Bus2IP_RdCE(11) or Bus2IP_RdCE(12) or Bus2IP_RdCE(13) or Bus2IP_RdCE(14) or Bus2IP_RdCE(15) or Bus2IP_RdCE(16) or Bus2IP_RdCE(17) or Bus2IP_RdCE(18) or Bus2IP_RdCE(19) or Bus2IP_RdCE(20) or Bus2IP_RdCE(21) or Bus2IP_RdCE(22) or Bus2IP_RdCE(23) or Bus2IP_RdCE(24) or Bus2IP_RdCE(25) or Bus2IP_RdCE(26) or Bus2IP_RdCE(27) or Bus2IP_RdCE(28) or Bus2IP_RdCE(29) or Bus2IP_RdCE(30) or Bus2IP_RdCE(31);

  -- implement slave model software accessible register(s)
  SLAVE_REG_WRITE_PROC : process( Bus2IP_Clk ) is
  begin

    if Bus2IP_Clk'event and Bus2IP_Clk = '1' then
      if Bus2IP_Reset = '1' then
        dvma_cr <= (others => '0');
        dvma_fwr <= (others => '0');
        dvma_fhr <= (others => '0');
        dvma_fbar <= (others => '0');
        dvma_flsr <= (others => '0');
        dvma_hsr <= (others => '0');
        dvma_hfpr <= (others => '0');
        dvma_hbpr <= (others => '0');
        dvma_htr <= (others => '0');
        dvma_vsr <= (others => '0');
        dvma_vfpr <= (others => '0');
        dvma_vbpr <= (others => '0');
        dvma_vtr <= (others => '0');
        slv_reg13 <= (others => '0');
        slv_reg14 <= (others => '0');
        slv_reg15 <= (others => '0');
        slv_reg16 <= (others => '0');
        slv_reg17 <= (others => '0');
        slv_reg18 <= (others => '0');
        slv_reg19 <= (others => '0');
        slv_reg20 <= (others => '0');
        slv_reg21 <= (others => '0');
        slv_reg22 <= (others => '0');
        slv_reg23 <= (others => '0');
        slv_reg24 <= (others => '0');
        slv_reg25 <= (others => '0');
        slv_reg26 <= (others => '0');
        slv_reg27 <= (others => '0');
        slv_reg28 <= (others => '0');
        slv_reg29 <= (others => '0');
        slv_reg30 <= (others => '0');
        slv_reg31 <= (others => '0');
      else
        case slv_reg_write_sel is
          when "10000000000000000000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                dvma_cr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "01000000000000000000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                dvma_fwr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00100000000000000000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                dvma_fhr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00010000000000000000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                dvma_fbar(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00001000000000000000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                dvma_flsr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000100000000000000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                dvma_hsr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000010000000000000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                dvma_hbpr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000001000000000000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                dvma_hfpr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000100000000000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                dvma_htr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000010000000000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                dvma_vsr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000001000000000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                dvma_vbpr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000100000000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                dvma_vfpr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000010000000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                dvma_vtr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000001000000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg13(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000100000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg14(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000010000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg15(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000001000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg16(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000100000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg17(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000010000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg18(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000001000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg19(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000000100000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg20(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000000010000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg21(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000000001000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg22(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000000000100000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg23(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000000000010000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg24(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000000000001000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg25(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000000000000100000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg26(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000000000000010000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg27(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000000000000001000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg28(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000000000000000100" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg29(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000000000000000010" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg30(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "00000000000000000000000000000001" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg31(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when others => null;
        end case;
      end if;
    end if;

  end process SLAVE_REG_WRITE_PROC;

  -- implement slave model software accessible register(s) read mux
  SLAVE_REG_READ_PROC : process( slv_reg_read_sel, dvma_cr, dvma_fwr, dvma_fhr, dvma_fbar, dvma_flsr, dvma_hsr, dvma_hbpr, dvma_hfpr, dvma_htr, dvma_vsr, dvma_vbpr, dvma_vfpr, dvma_vtr, slv_reg13, slv_reg14, slv_reg15, slv_reg16, slv_reg17, slv_reg18, slv_reg19, slv_reg20, slv_reg21, slv_reg22, slv_reg23, slv_reg24, slv_reg25, slv_reg26, slv_reg27, slv_reg28, slv_reg29, slv_reg30, slv_reg31 ) is
  begin

    case slv_reg_read_sel is
      when "10000000000000000000000000000000" => slv_ip2bus_data <= dvma_cr;
      when "01000000000000000000000000000000" => slv_ip2bus_data <= dvma_fwr;
      when "00100000000000000000000000000000" => slv_ip2bus_data <= dvma_fhr;
      when "00010000000000000000000000000000" => slv_ip2bus_data <= dvma_fbar;
      when "00001000000000000000000000000000" => slv_ip2bus_data <= dvma_flsr;
      when "00000100000000000000000000000000" => slv_ip2bus_data <= dvma_hsr;
      when "00000010000000000000000000000000" => slv_ip2bus_data <= dvma_hbpr;
      when "00000001000000000000000000000000" => slv_ip2bus_data <= dvma_hfpr;
      when "00000000100000000000000000000000" => slv_ip2bus_data <= dvma_vtr;
      when "00000000010000000000000000000000" => slv_ip2bus_data <= dvma_vsr;
      when "00000000001000000000000000000000" => slv_ip2bus_data <= dvma_vbpr;
      when "00000000000100000000000000000000" => slv_ip2bus_data <= dvma_vfpr;
      when "00000000000010000000000000000000" => slv_ip2bus_data <= dvma_vtr;
      when "00000000000001000000000000000000" => slv_ip2bus_data <= slv_reg13;
      when "00000000000000100000000000000000" => slv_ip2bus_data <= slv_reg14;
      when "00000000000000010000000000000000" => slv_ip2bus_data <= slv_reg15;
      when "00000000000000001000000000000000" => slv_ip2bus_data <= slv_reg16;
      when "00000000000000000100000000000000" => slv_ip2bus_data <= slv_reg17;
      when "00000000000000000010000000000000" => slv_ip2bus_data <= slv_reg18;
      when "00000000000000000001000000000000" => slv_ip2bus_data <= slv_reg19;
      when "00000000000000000000100000000000" => slv_ip2bus_data <= slv_reg20;
      when "00000000000000000000010000000000" => slv_ip2bus_data <= slv_reg21;
      when "00000000000000000000001000000000" => slv_ip2bus_data <= slv_reg22;
      when "00000000000000000000000100000000" => slv_ip2bus_data <= slv_reg23;
      when "00000000000000000000000010000000" => slv_ip2bus_data <= slv_reg24;
      when "00000000000000000000000001000000" => slv_ip2bus_data <= slv_reg25;
      when "00000000000000000000000000100000" => slv_ip2bus_data <= slv_reg26;
      when "00000000000000000000000000010000" => slv_ip2bus_data <= slv_reg27;
      when "00000000000000000000000000001000" => slv_ip2bus_data <= slv_reg28;
      when "00000000000000000000000000000100" => slv_ip2bus_data <= slv_reg29;
      when "00000000000000000000000000000010" => slv_ip2bus_data <= slv_reg30;
      when "00000000000000000000000000000001" => slv_ip2bus_data <= slv_reg31;
      when others => slv_ip2bus_data <= (others => '0');
    end case;

  end process SLAVE_REG_READ_PROC;

  ------------------------------------------
  -- Example code to drive IP to Bus signals
  ------------------------------------------
  IP2Bus_Data  <= slv_ip2bus_data when slv_read_ack = '1' else
                  (others => '0');

  IP2Bus_WrAck <= slv_write_ack;
  IP2Bus_RdAck <= slv_read_ack;
  IP2Bus_Error <= '0';

end IMP;
