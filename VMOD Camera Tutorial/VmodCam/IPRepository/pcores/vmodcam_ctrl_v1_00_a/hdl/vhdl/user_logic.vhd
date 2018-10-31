------------------------------------------------------------------------
--	vmodcam_ctrl/user_logic.vhd  -- Camera Controller user logic
------------------------------------------------------------------------
-- Author:  Tinghui WANG (Steve)
--	Copyright 2001 Digilent, Inc.
------------------------------------------------------------------------
-- Module description
--		Reads pixel data from VFBC interface of MPMC
--		Generate XSVI signals according to software configurations.
--
--  Inputs:
-- 	Clk24M_I - 24 MHz Clock input
--		CLK24M_LOCKED_I - 24 MHz clock locked signal
--		CAM_PCLK - camera pixel clock
--		CAM_FV - camera frame synchronization
-- 	CAM_LV - camera line sychronization
--		CAM_DATA - 8 bit camera data input
--		VFBC_CMD_IDLE - vfbc cmd port idle status signal
-- 	VFBC_CMD_FULL - vfbc cmd port fifo full signal
-- 	VFBC_CMD_ALMOST_FULL - vfbc cmd port fifo almost full signal
--		VFBC_WD_FULL - vfbc write fifo empty signal
-- 	VFBC_WD_ALMOST_EFULL - vfbc write fifo empty signal
--		
--  Outputs:
--		CAM_MCLK : camera master clock
--		CAM_RST_N : camera reset signal (active low)
--		CAM_POWERDOWN : camera powerdown signal (active high)
--		VFBC_CMD_CLK - vfbc cmd fifo clock signal
--		VFBC_CMD_RESET - vfbc cmd port reset signal
--		VFBC_CMD_DATA - vfbc cmd signals
--		VFBC_CMD_WRITE - vfbc write cmd signals
--		VFBC_CMD_END - vfbc end cmd signal
-- 	VFBC_WD_CLK - vfbc write fifo clock
-- 	VFBC_WD_RESET - vfbc write fifo reset
-- 	VFBC_WD_FLUSH - vfbc flush write fifo signal
--		VFBC_WD_WRITE - vfbc write write fifo signal
--		VFBC_WD_DATA - vfbc write fifo data
-- 	VFBC_WD_DATA_BE - Byte enable signal for vfbc write fifo data (not used)
-- 	VFBC_WD_END_BURST -vfbc end burst signals
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
-- Date:              Fri Mar  4 19:09:14 2011 (by Create and Import Peripheral Wizard)
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
library UNISIM;
use UNISIM.vcomponents.all;

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
	 C_VFBC_RDWD_DATA_WIDTH : integer := 8;
    -- ADD USER GENERICS ABOVE THIS LINE ---------------

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol parameters, do not add to or delete
    C_SLV_DWIDTH                   : integer              := 32;
    C_NUM_REG                      : integer              := 16
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );
  port
  (
    -- ADD USER PORTS BELOW THIS LINE ------------------
    --USER ports added here
	 -- Clock Signals
	 Clk24M_I : in std_logic;
	 CLK24M_LOCKED_I : in std_logic;
	 DEBUG_O : out std_logic_vector(7 downto 0);
	 -- Camera Ports
	 CAM_MCLK : out std_logic;
	 CAM_RST_N : out std_logic;
	 CAM_POWERDOWN : out std_logic;
 	 CAM_PCLK : in std_logic;
	 CAM_FV : in std_logic;
	 CAM_LV : in std_logic;
	 CAM_DATA : in std_logic_vector (7 downto 0);
	 -- VFBC Command Signals
	 VFBC_CMD_CLK : out std_logic;
	 VFBC_CMD_IDLE : in std_logic;
	 VFBC_CMD_RESET : out std_logic;
	 VFBC_CMD_DATA : out std_logic_vector (31 downto 0);
	 VFBC_CMD_WRITE : out std_logic;
	 VFBC_CMD_END : out std_logic;
	 VFBC_CMD_FULL : in std_logic;
	 VFBC_CMD_ALMOST_FULL : in std_logic;
	 -- VFBC Write Signals
	 VFBC_WD_CLK : out std_logic;
	 VFBC_WD_RESET : out std_logic;
	 VFBC_WD_FLUSH : out std_logic;
	 VFBC_WD_WRITE : out std_logic;
	 VFBC_WD_DATA : out std_logic_vector (C_VFBC_RDWD_DATA_WIDTH-1 downto 0);
	 VFBC_WD_DATA_BE : out std_logic_vector (C_VFBC_RDWD_DATA_WIDTH/8-1 downto 0);
	 VFBC_WD_END_BURST : out std_logic;
	 VFBC_WD_FULL : in std_logic;
	 VFBC_WD_ALMOST_FULL : in std_logic;
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
  -- Cam Control
  signal cam_lv_buf : std_logic;
  signal cam_fv_buf : std_logic;
  signal cam_vcnt : std_logic_vector(15 downto 0);
  signal cam_hcnt : std_logic_vector(15 downto 0);
  signal cam_hcnt_total : std_logic_vector(23 downto 0);
  
  signal cam_data_invalid_cnt : std_logic_vector(20 downto 0);
  
  signal vfbc_cmd_data_i : std_logic_vector(31 downto 0);
  signal vfbc_cmd_write_i : std_logic;
  
  signal vfbc_cmd0 : std_logic_vector(31 downto 0);
  signal vfbc_cmd1 : std_logic_vector(31 downto 0);
  signal vfbc_cmd2 : std_logic_vector(31 downto 0);
  signal vfbc_cmd3 : std_logic_vector(31 downto 0);
  
  signal vfbc_wd_reset_i : std_logic;
  signal vfbc_wd_data_i : std_logic_vector(7 downto 0);
  signal vfbc_wd_write_i : std_logic;
  signal vfbc_wd_write_aligned_i : std_logic;
  
  signal cam_ctrl_frdr_i : std_logic_vector(0 to 31);

  ------------------------------------------
  -- Signals for user logic slave model s/w accessible register example
  ------------------------------------------
  signal cam_ctrl_cr                    : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal cam_ctrl_fwr                   : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal cam_ctrl_fhr                   : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal cam_ctrl_fbar                  : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal cam_ctrl_flsr                  : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal cam_ctrl_fwdr                  : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal cam_ctrl_fhdr                  : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal cam_ctrl_frdr                  : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg8                       : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg9                       : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg10                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg11                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg12                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg13                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg14                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg15                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg_write_sel              : std_logic_vector(0 to 15);
  signal slv_reg_read_sel               : std_logic_vector(0 to 15);
  signal slv_ip2bus_data                : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_read_ack                   : std_logic;
  signal slv_write_ack                  : std_logic;

begin

  --USER logic implementation added here

  VFBC_CNT_PROCESS: process (CAM_PCLK) is
  begin
	if CAM_PCLK'event and CAM_PCLK = '1' then
		if Bus2IP_Reset = '1' or cam_ctrl_cr(C_SLV_DWIDTH-1) = '0' or CLK24M_LOCKED_I = '0' then
			cam_data_invalid_cnt <= (others => '0');
		elsif CAM_FV = '0' and cam_data_invalid_cnt < 300 then
			cam_data_invalid_cnt <= cam_data_invalid_cnt + 1;
		elsif CAM_FV = '0' and cam_data_invalid_cnt > 299 then
			cam_data_invalid_cnt <= cam_data_invalid_cnt;
		else
			cam_data_invalid_cnt <= (others => '0');
		end if;
	end if;
  end process VFBC_CNT_PROCESS;

  --------------------------------
  -- VFBC Command Logic
  --------------------------------

  VFBC_CMD_CLK <= CAM_PCLK;
  VFBC_CMD_RESET <= '1' when Bus2IP_Reset = '1' or cam_ctrl_cr(C_SLV_DWIDTH-1) = '0' else
						  '0'; -- reset at the very beginning
  VFBC_CMD_DATA <= vfbc_cmd_data_i;
  VFBC_CMD_WRITE <= vfbc_cmd_write_i;
  VFBC_CMD_END <= '0'; -- never ends
  
  -- Generate command according to registers, 2 bytes per pixel
  vfbc_cmd0 <= x"0000" & cam_ctrl_fwr(C_SLV_DWIDTH-15 to C_SLV_DWIDTH-1) & '0';
  vfbc_cmd1 <= '1' & cam_ctrl_fbar(1 to C_SLV_DWIDTH-1);
  vfbc_cmd2 <= x"0000" & cam_ctrl_fhr(C_SLV_DWIDTH-16 to C_SLV_DWIDTH-1);
  vfbc_cmd3 <= x"0000" & cam_ctrl_flsr(C_SLV_DWIDTH-15 to C_SLV_DWIDTH-1) & '0';

  -- Feed command into VFBC Cmd Port at the beginning of each frame
  VFBC_FEED_CMD_PROCESS: process (CAM_PCLK) is
  begin
	if CAM_PCLK'event and CAM_PCLK = '1' then
		if cam_data_invalid_cnt < 200 then
			vfbc_cmd_data_i <= (others => '0');
			vfbc_cmd_write_i <= '0';
		elsif cam_data_invalid_cnt = 200 then
			vfbc_cmd_data_i <= vfbc_cmd0;
			vfbc_cmd_write_i <= '1';
		elsif cam_data_invalid_cnt = 201 then
			vfbc_cmd_data_i <= vfbc_cmd1;
			vfbc_cmd_write_i <= '1';
		elsif cam_data_invalid_cnt = 202 then
			vfbc_cmd_data_i <= vfbc_cmd2;
			vfbc_cmd_write_i <= '1';
		elsif cam_data_invalid_cnt = 203 then
			vfbc_cmd_data_i <= vfbc_cmd3;
			vfbc_cmd_write_i <= '1';
		else
			vfbc_cmd_data_i <= (others=>'0');
			vfbc_cmd_write_i <= '0';
		end if;
	end if;
  end process VFBC_FEED_CMD_PROCESS;
  
  --------------------------------
  -- VFBC Write Logic
  --------------------------------
  VFBC_WD_CLK <= CAM_PCLK;
  VFBC_WD_RESET <= vfbc_wd_reset_i;
  VFBC_WD_FLUSH <= '0';
  VFBC_WD_WRITE <= vfbc_wd_write_i when cam_ctrl_cr(C_SLV_DWIDTH-2) = '0' else
						vfbc_wd_write_aligned_i;
  VFBC_WD_DATA <= vfbc_wd_data_i;
  VFBC_WD_DATA_BE <= (others => '1');
  VFBC_WD_END_BURST <= '0';
  
  -- Generate vfbc_wd_write_aligned_i signal
  -- it is the 64Byte aligned version of vfbc_wd_write_i
  VFBC_WRITE_ALIGNED_PROC : process (CAM_PCLK) is
  begin
	if CAM_PCLK'event and CAM_PCLK = '1' then
		if cam_hcnt_total(6 downto 0) = "0000000" then
			vfbc_wd_write_aligned_i <= CAM_FV and CAM_LV;
		elsif cam_lv_buf = '0' and CAM_LV = '1' then
			vfbc_wd_write_aligned_i <= CAM_FV and CAM_LV;
		end if;
	end if;
  end process VFBC_WRITE_ALIGNED_PROC;
  
  -- Generate vfbc_wd_data and vfbc_wd_write signal
  -- These signals do not check alignment
  VFBC_WRITE_DATA_PROC : process (CAM_PCLK) is
  begin
	if CAM_PCLK'event and CAM_PCLK = '1' then
		vfbc_wd_data_i <= CAM_DATA;
		vfbc_wd_write_i <= CAM_FV and CAM_LV;
	end if;
  end process VFBC_WRITE_DATA_PROC;
  
  -- Reset write fifo at the beginning of every frame
  VFBC_WRITE_RESET_PROC : process (CAM_PCLK) is
  begin
	if CAM_PCLK'event and CAM_PCLK = '1' then
		if Bus2IP_Reset = '1' or cam_ctrl_cr(C_SLV_DWIDTH-1) = '0' then
			vfbc_wd_reset_i <= '1';
		elsif cam_data_invalid_cnt < 150 and cam_data_invalid_cnt > 100 then
			vfbc_wd_reset_i <= '1';
		else
			vfbc_wd_reset_i <= '0';
		end if;
	end if;
  end process VFBC_WRITE_RESET_PROC;
  
  -- Buffer lv and fv to detect rising edge
  -- since lv and fv cannot be mapped as a clock in FPGA
  LV_FV_BUFFER_PROC : process (CAM_PCLK) is
  begin
	if CAM_PCLK'event and CAM_PCLK = '1' then
		if Bus2IP_Reset = '1' then
			cam_lv_buf <= '0';
			cam_fv_buf <= '0';
		else
			cam_lv_buf <= CAM_LV;
			cam_fv_buf <= CAM_FV;
		end if;
	end if;
  end process LV_FV_BUFFER_PROC;
  
  -- Count how many pixels per line
  -- Updates the pixel counts to registers every line
  PIXEL_CNT_PROC : process (CAM_PCLK) is
  begin
	if CAM_PCLK'event and CAM_PCLK = '1' then
		if Bus2IP_Reset = '1' then
			cam_hcnt <= (others => '0');
			cam_ctrl_fwdr <= (others => '0');
		elsif Cam_LV = '1' then
			cam_hcnt <= cam_hcnt + 1;
		elsif cam_lv_buf = '1' and CAM_LV = '0' then
			cam_ctrl_fwdr <= x"0000" & '0' & cam_hcnt(15 downto 1);
			cam_hcnt <= (others => '0');
		end if;
	end if;
  end process PIXEL_CNT_PROC;
    
  -- Count how many lines per frame
  -- Updates the line counts to registers every frame
  LINE_CNT_PROC : process (CAM_PCLK) is
  begin
	if CAM_PCLK'event and CAM_PCLK = '1' then
		if Bus2IP_Reset = '1' then
			cam_ctrl_fhdr <= (others => '0');
			cam_vcnt <= (others => '0');
		elsif cam_fv_buf = '1' and CAM_FV = '0' then
			cam_ctrl_fhdr <= x"0000" & cam_vcnt;
			cam_vcnt <= (others => '0');
		elsif cam_lv_buf = '0' and CAM_LV = '1' and CAM_FV = '1' then
			cam_vcnt <= cam_vcnt + 1;
		end if;
	end if;
  end process LINE_CNT_PROC;
  
  -- Count how many clock cycles per frame
  -- the register is used for frame rate calculation
  FRAME_CNT_PROC : process (CAM_PClk) is
  begin
	if CAM_PClk'event and CAM_PClk = '1' then
		if Bus2IP_Reset = '1' then
			cam_ctrl_frdr_i <= (others => '0');
			cam_ctrl_frdr <= (others => '0');
		elsif cam_fv_buf = '0' and CAM_FV = '1' then 
			cam_ctrl_frdr_i <= x"00000001";
			cam_ctrl_frdr <= cam_ctrl_frdr_i;
		else
			cam_ctrl_frdr_i <= cam_ctrl_frdr_i + 1;
		end if;
	end if;
  end process FRAME_CNT_PROC;

  -- Count the whole line
  -- used for 64byte alignment
  LINE_CNT_TOTAL_PROC : process (CAM_PCLK) is
  begin
	if CAM_PCLK'event and CAM_PCLK = '1' then
		if Bus2IP_Reset = '1' then
			cam_hcnt_total <= (others => '0');
		elsif cam_lv_buf = '0' and CAM_LV = '1' then
			cam_hcnt_total <= x"000001";
		else
			cam_hcnt_total <= cam_hcnt_total + 1;
		end if;
	end if;
  end process LINE_CNT_TOTAL_PROC;

  ------------------------------------------
  -- Signals for Camera
  ------------------------------------------

  CAM_RST_N <= not Bus2IP_Reset;
  CAM_POWERDOWN <= '0';	-- Always power on.

  CAM_MCLK_ODDR_O : ODDR
   generic map
	(
     DDR_CLK_EDGE => "SAME_EDGE",
     INIT => '0',
     SRTYPE => "SYNC"
	)
   port map 
	(
     Q => CAM_MCLK,
     C => CLK24M_I,
     CE => '1',
     D1 => '1',
     D2 => '0',
     R => (not CLK24M_LOCKED_I),
     S => '0'
   );

  -- Debug Ports
  DEBUG_O(0) <= VFBC_CMD_FULL;
  DEBUG_O(1) <= VFBC_CMD_IDLE;
  DEBUG_O(2) <= VFBC_WD_FULL;
  DEBUG_O(3) <= vfbc_wd_reset_i;
  DEBUG_O(4) <= CAM_FV; 
  DEBUG_O(5) <= CAM_LV;
  DEBUG_O(6) <= '1';
  DEBUG_O(7) <= '0';

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
  slv_reg_write_sel <= Bus2IP_WrCE(0 to 15);
  slv_reg_read_sel  <= Bus2IP_RdCE(0 to 15);
  slv_write_ack     <= Bus2IP_WrCE(0) or Bus2IP_WrCE(1) or Bus2IP_WrCE(2) or Bus2IP_WrCE(3) or Bus2IP_WrCE(4) or Bus2IP_WrCE(5) or Bus2IP_WrCE(6) or Bus2IP_WrCE(7) or Bus2IP_WrCE(8) or Bus2IP_WrCE(9) or Bus2IP_WrCE(10) or Bus2IP_WrCE(11) or Bus2IP_WrCE(12) or Bus2IP_WrCE(13) or Bus2IP_WrCE(14) or Bus2IP_WrCE(15);
  slv_read_ack      <= Bus2IP_RdCE(0) or Bus2IP_RdCE(1) or Bus2IP_RdCE(2) or Bus2IP_RdCE(3) or Bus2IP_RdCE(4) or Bus2IP_RdCE(5) or Bus2IP_RdCE(6) or Bus2IP_RdCE(7) or Bus2IP_RdCE(8) or Bus2IP_RdCE(9) or Bus2IP_RdCE(10) or Bus2IP_RdCE(11) or Bus2IP_RdCE(12) or Bus2IP_RdCE(13) or Bus2IP_RdCE(14) or Bus2IP_RdCE(15);

  -- implement slave model software accessible register(s)
  SLAVE_REG_WRITE_PROC : process( Bus2IP_Clk ) is
  begin
    if Bus2IP_Clk'event and Bus2IP_Clk = '1' then
      if Bus2IP_Reset = '1' then
        cam_ctrl_cr <= (others => '0');
        cam_ctrl_fwr <= (others => '0');
        cam_ctrl_fhr <= (others => '0');
        cam_ctrl_fbar <= (others => '0');
        cam_ctrl_flsr <= (others => '0');
--        cam_ctrl_fwdr <= (others => '0');
--        cam_ctrl_fhdr <= (others => '0');
--        cam_ctrl_frdr <= (others => '0');
        slv_reg8 <= (others => '0');
        slv_reg9 <= (others => '0');
        slv_reg10 <= (others => '0');
        slv_reg11 <= (others => '0');
        slv_reg12 <= (others => '0');
        slv_reg13 <= (others => '0');
        slv_reg14 <= (others => '0');
        slv_reg15 <= (others => '0');
      else
        case slv_reg_write_sel is
          when "1000000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                cam_ctrl_cr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0100000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                cam_ctrl_fwr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0010000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                cam_ctrl_fhr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0001000000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                cam_ctrl_fbar(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0000100000000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                cam_ctrl_flsr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
				-- cam_ctrl_fwdr, cam_ctrl_fhdr, cam_ctrl_frdr are read only
--          when "0000010000000000" =>
--            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
--              if ( Bus2IP_BE(byte_index) = '1' ) then
--                cam_ctrl_fwdr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
--              end if;
--            end loop;
--          when "0000001000000000" =>
--            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
--              if ( Bus2IP_BE(byte_index) = '1' ) then
--                cam_ctrl_fhdr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
--              end if;
--            end loop;
--          when "0000000100000000" =>
--            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
--              if ( Bus2IP_BE(byte_index) = '1' ) then
--                cam_ctrl_frdr(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
--              end if;
--            end loop;
          when "0000000010000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg8(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0000000001000000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg9(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0000000000100000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg10(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0000000000010000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg11(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0000000000001000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg12(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0000000000000100" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg13(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0000000000000010" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg14(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0000000000000001" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg15(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when others => null;
        end case;
      end if;
    end if;

  end process SLAVE_REG_WRITE_PROC;

  -- implement slave model software accessible register(s) read mux
  SLAVE_REG_READ_PROC : process( slv_reg_read_sel, cam_ctrl_cr, cam_ctrl_fwr, cam_ctrl_fhr, cam_ctrl_fbar, cam_ctrl_flsr, cam_ctrl_fwdr, cam_ctrl_fhdr, cam_ctrl_frdr, slv_reg8, slv_reg9, slv_reg10, slv_reg11, slv_reg12, slv_reg13, slv_reg14, slv_reg15 ) is
  begin

    case slv_reg_read_sel is
      when "1000000000000000" => slv_ip2bus_data <= cam_ctrl_cr;
      when "0100000000000000" => slv_ip2bus_data <= cam_ctrl_fwr;
      when "0010000000000000" => slv_ip2bus_data <= cam_ctrl_fhr;
      when "0001000000000000" => slv_ip2bus_data <= cam_ctrl_fbar;
      when "0000100000000000" => slv_ip2bus_data <= cam_ctrl_flsr;
      when "0000010000000000" => slv_ip2bus_data <= cam_ctrl_fwdr;
      when "0000001000000000" => slv_ip2bus_data <= cam_ctrl_fhdr;
      when "0000000100000000" => slv_ip2bus_data <= cam_ctrl_frdr;
      when "0000000010000000" => slv_ip2bus_data <= slv_reg8;
      when "0000000001000000" => slv_ip2bus_data <= slv_reg9;
      when "0000000000100000" => slv_ip2bus_data <= slv_reg10;
      when "0000000000010000" => slv_ip2bus_data <= slv_reg11;
      when "0000000000001000" => slv_ip2bus_data <= slv_reg12;
      when "0000000000000100" => slv_ip2bus_data <= slv_reg13;
      when "0000000000000010" => slv_ip2bus_data <= slv_reg14;
      when "0000000000000001" => slv_ip2bus_data <= slv_reg15;
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
