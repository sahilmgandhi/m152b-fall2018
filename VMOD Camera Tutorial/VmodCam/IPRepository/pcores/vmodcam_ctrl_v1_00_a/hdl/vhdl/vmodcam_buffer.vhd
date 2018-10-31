------------------------------------------------------------------------
--	vmodcam_buffer.vhd  -- Input Buffer for VmodCAM Signals
------------------------------------------------------------------------
-- Author:  Tinghui WANG (Steve)
--	Copyright 2001 Digilent, Inc.
------------------------------------------------------------------------
-- Module description
--		Buffer the external clock with IBUFG
--		Buffer the other cmaera signals with D Flip-flop
--
--  Inputs:
--		CAM_PCLK_I - camera pixel clock
--		CAM_FV_I - camera frame synchronization
-- 	CAM_LV_I - camera line sychronization
--		CAM_DATA_I - 8 bit camera data input
--		
--  Outputs:
--		CAM_PCLK_O - camera pixel clock
--		CAM_FV_O - camera frame synchronization
-- 	CAM_LV_O - camera line sychronization
--		CAM_DATA_O - 8 bit camera data input
--
------------------------------------------------------------------------
-- Revision History:
--
--	26Apr2011 (SteveW): v1.0 released
--
------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library UNISIM;
use UNISIM.VComponents.all;

entity vmodcam_buffer is
  port (
	 -- Camera External Inputs
 	 CAM_PCLK_I : in std_logic;
	 CAM_FV_I : in std_logic;
	 CAM_LV_I : in std_logic;
	 CAM_DATA_I : in std_logic_vector (7 downto 0);
	 -- Buffered Outputs
	 CAM_PCLK_O : out std_logic;
	 CAM_FV_O : out std_logic;
	 CAM_LV_O : out std_logic;
	 CAM_DATA_O : out std_logic_vector (7 downto 0)
	 );
end entity vmodcam_buffer;

architecture Behavior of vmodcam_buffer is

signal pclk_i : std_logic;

begin

  CAM_PCLK_IBUFG_INST : IBUFG
	generic map(
		IBUF_LOW_PWR => TRUE,
		IOSTANDARD => "DEFAULT")
	port map (
		O => pclk_i,
		I => CAM_PCLK_I
	);
	
  
  CAM_DATA_REG_GEN: for i in 0 to 7 generate
	begin
		CAM_DATA_REG: FD
		generic map (
			INIT => '0')
		port map (
			Q => CAM_DATA_O(i),
			C => pclk_i,
			D => CAM_DATA_I(i)
		);
  end generate CAM_DATA_REG_GEN;
  
  CAM_LV_REG: FD
	generic map (
		INIT => '0')
	port map (
		Q => CAM_LV_O,
		C => pclk_i,
		D => CAM_LV_I
	);

  CAM_FV_REG: FD
	generic map (
		INIT => '0')
	port map (
		Q => CAM_FV_O,
		C => pclk_i,
		D => CAM_FV_I
	);

  CAM_PCLK_O <= pclk_i;

end Behavior;
