-------------------------------------------------------------------------------
-- system_cam_ctrl_0_wrapper.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library vmodcam_ctrl_v1_00_a;
use vmodcam_ctrl_v1_00_a.all;

entity system_cam_ctrl_0_wrapper is
  port (
    SPLB_Clk : in std_logic;
    SPLB_Rst : in std_logic;
    PLB_ABus : in std_logic_vector(0 to 31);
    PLB_UABus : in std_logic_vector(0 to 31);
    PLB_PAValid : in std_logic;
    PLB_SAValid : in std_logic;
    PLB_rdPrim : in std_logic;
    PLB_wrPrim : in std_logic;
    PLB_masterID : in std_logic_vector(0 to 0);
    PLB_abort : in std_logic;
    PLB_busLock : in std_logic;
    PLB_RNW : in std_logic;
    PLB_BE : in std_logic_vector(0 to 7);
    PLB_MSize : in std_logic_vector(0 to 1);
    PLB_size : in std_logic_vector(0 to 3);
    PLB_type : in std_logic_vector(0 to 2);
    PLB_lockErr : in std_logic;
    PLB_wrDBus : in std_logic_vector(0 to 63);
    PLB_wrBurst : in std_logic;
    PLB_rdBurst : in std_logic;
    PLB_wrPendReq : in std_logic;
    PLB_rdPendReq : in std_logic;
    PLB_wrPendPri : in std_logic_vector(0 to 1);
    PLB_rdPendPri : in std_logic_vector(0 to 1);
    PLB_reqPri : in std_logic_vector(0 to 1);
    PLB_TAttribute : in std_logic_vector(0 to 15);
    Sl_addrAck : out std_logic;
    Sl_SSize : out std_logic_vector(0 to 1);
    Sl_wait : out std_logic;
    Sl_rearbitrate : out std_logic;
    Sl_wrDAck : out std_logic;
    Sl_wrComp : out std_logic;
    Sl_wrBTerm : out std_logic;
    Sl_rdDBus : out std_logic_vector(0 to 63);
    Sl_rdWdAddr : out std_logic_vector(0 to 3);
    Sl_rdDAck : out std_logic;
    Sl_rdComp : out std_logic;
    Sl_rdBTerm : out std_logic;
    Sl_MBusy : out std_logic_vector(0 to 1);
    Sl_MWrErr : out std_logic_vector(0 to 1);
    Sl_MRdErr : out std_logic_vector(0 to 1);
    Sl_MIRQ : out std_logic_vector(0 to 1);
    Clk24M_I : in std_logic;
    CLK24M_LOCKED_I : in std_logic;
    DEBUG_O : out std_logic_vector(7 downto 0);
    VFBC_CMD_CLK : out std_logic;
    VFBC_CMD_RESET : out std_logic;
    VFBC_CMD_DATA : out std_logic_vector(31 downto 0);
    VFBC_CMD_WRITE : out std_logic;
    VFBC_CMD_END : out std_logic;
    VFBC_CMD_FULL : in std_logic;
    VFBC_CMD_ALMOST_FULL : in std_logic;
    VFBC_CMD_IDLE : in std_logic;
    VFBC_WD_CLK : out std_logic;
    VFBC_WD_RESET : out std_logic;
    VFBC_WD_WRITE : out std_logic;
    VFBC_WD_END_BURST : out std_logic;
    VFBC_WD_FLUSH : out std_logic;
    VFBC_WD_DATA : out std_logic_vector(7 downto 0);
    VFBC_WD_DATA_BE : out std_logic_vector(0 to 0);
    VFBC_WD_FULL : in std_logic;
    VFBC_WD_ALMOST_FULL : in std_logic;
    CAM_MCLK : out std_logic;
    CAM_RST_N : out std_logic;
    CAM_POWERDOWN : out std_logic;
    CAM_PCLK : in std_logic;
    CAM_FV : in std_logic;
    CAM_LV : in std_logic;
    CAM_DATA : in std_logic_vector(7 downto 0)
  );
end system_cam_ctrl_0_wrapper;

architecture STRUCTURE of system_cam_ctrl_0_wrapper is

  component vmodcam_ctrl is
    generic (
      C_BASEADDR : std_logic_vector;
      C_HIGHADDR : std_logic_vector;
      C_SPLB_AWIDTH : INTEGER;
      C_SPLB_DWIDTH : INTEGER;
      C_SPLB_NUM_MASTERS : INTEGER;
      C_SPLB_MID_WIDTH : INTEGER;
      C_SPLB_NATIVE_DWIDTH : INTEGER;
      C_SPLB_P2P : INTEGER;
      C_SPLB_SUPPORT_BURSTS : INTEGER;
      C_SPLB_SMALLEST_MASTER : INTEGER;
      C_SPLB_CLK_PERIOD_PS : INTEGER;
      C_INCLUDE_DPHASE_TIMER : INTEGER;
      C_FAMILY : STRING;
      C_VFBC_RDWD_DATA_WIDTH : INTEGER
    );
    port (
      SPLB_Clk : in std_logic;
      SPLB_Rst : in std_logic;
      PLB_ABus : in std_logic_vector(0 to 31);
      PLB_UABus : in std_logic_vector(0 to 31);
      PLB_PAValid : in std_logic;
      PLB_SAValid : in std_logic;
      PLB_rdPrim : in std_logic;
      PLB_wrPrim : in std_logic;
      PLB_masterID : in std_logic_vector(0 to (C_SPLB_MID_WIDTH-1));
      PLB_abort : in std_logic;
      PLB_busLock : in std_logic;
      PLB_RNW : in std_logic;
      PLB_BE : in std_logic_vector(0 to ((C_SPLB_DWIDTH/8)-1));
      PLB_MSize : in std_logic_vector(0 to 1);
      PLB_size : in std_logic_vector(0 to 3);
      PLB_type : in std_logic_vector(0 to 2);
      PLB_lockErr : in std_logic;
      PLB_wrDBus : in std_logic_vector(0 to (C_SPLB_DWIDTH-1));
      PLB_wrBurst : in std_logic;
      PLB_rdBurst : in std_logic;
      PLB_wrPendReq : in std_logic;
      PLB_rdPendReq : in std_logic;
      PLB_wrPendPri : in std_logic_vector(0 to 1);
      PLB_rdPendPri : in std_logic_vector(0 to 1);
      PLB_reqPri : in std_logic_vector(0 to 1);
      PLB_TAttribute : in std_logic_vector(0 to 15);
      Sl_addrAck : out std_logic;
      Sl_SSize : out std_logic_vector(0 to 1);
      Sl_wait : out std_logic;
      Sl_rearbitrate : out std_logic;
      Sl_wrDAck : out std_logic;
      Sl_wrComp : out std_logic;
      Sl_wrBTerm : out std_logic;
      Sl_rdDBus : out std_logic_vector(0 to (C_SPLB_DWIDTH-1));
      Sl_rdWdAddr : out std_logic_vector(0 to 3);
      Sl_rdDAck : out std_logic;
      Sl_rdComp : out std_logic;
      Sl_rdBTerm : out std_logic;
      Sl_MBusy : out std_logic_vector(0 to (C_SPLB_NUM_MASTERS-1));
      Sl_MWrErr : out std_logic_vector(0 to (C_SPLB_NUM_MASTERS-1));
      Sl_MRdErr : out std_logic_vector(0 to (C_SPLB_NUM_MASTERS-1));
      Sl_MIRQ : out std_logic_vector(0 to (C_SPLB_NUM_MASTERS-1));
      Clk24M_I : in std_logic;
      CLK24M_LOCKED_I : in std_logic;
      DEBUG_O : out std_logic_vector(7 downto 0);
      VFBC_CMD_CLK : out std_logic;
      VFBC_CMD_RESET : out std_logic;
      VFBC_CMD_DATA : out std_logic_vector(31 downto 0);
      VFBC_CMD_WRITE : out std_logic;
      VFBC_CMD_END : out std_logic;
      VFBC_CMD_FULL : in std_logic;
      VFBC_CMD_ALMOST_FULL : in std_logic;
      VFBC_CMD_IDLE : in std_logic;
      VFBC_WD_CLK : out std_logic;
      VFBC_WD_RESET : out std_logic;
      VFBC_WD_WRITE : out std_logic;
      VFBC_WD_END_BURST : out std_logic;
      VFBC_WD_FLUSH : out std_logic;
      VFBC_WD_DATA : out std_logic_vector(C_VFBC_RDWD_DATA_WIDTH-1 downto 0);
      VFBC_WD_DATA_BE : out std_logic_vector(C_VFBC_RDWD_DATA_WIDTH/8-1 to 0);
      VFBC_WD_FULL : in std_logic;
      VFBC_WD_ALMOST_FULL : in std_logic;
      CAM_MCLK : out std_logic;
      CAM_RST_N : out std_logic;
      CAM_POWERDOWN : out std_logic;
      CAM_PCLK : in std_logic;
      CAM_FV : in std_logic;
      CAM_LV : in std_logic;
      CAM_DATA : in std_logic_vector(7 downto 0)
    );
  end component;

begin

  Cam_Ctrl_0 : vmodcam_ctrl
    generic map (
      C_BASEADDR => X"cfa20000",
      C_HIGHADDR => X"cfa2ffff",
      C_SPLB_AWIDTH => 32,
      C_SPLB_DWIDTH => 64,
      C_SPLB_NUM_MASTERS => 2,
      C_SPLB_MID_WIDTH => 1,
      C_SPLB_NATIVE_DWIDTH => 32,
      C_SPLB_P2P => 0,
      C_SPLB_SUPPORT_BURSTS => 0,
      C_SPLB_SMALLEST_MASTER => 32,
      C_SPLB_CLK_PERIOD_PS => 8000,
      C_INCLUDE_DPHASE_TIMER => 0,
      C_FAMILY => "virtex5",
      C_VFBC_RDWD_DATA_WIDTH => 8
    )
    port map (
      SPLB_Clk => SPLB_Clk,
      SPLB_Rst => SPLB_Rst,
      PLB_ABus => PLB_ABus,
      PLB_UABus => PLB_UABus,
      PLB_PAValid => PLB_PAValid,
      PLB_SAValid => PLB_SAValid,
      PLB_rdPrim => PLB_rdPrim,
      PLB_wrPrim => PLB_wrPrim,
      PLB_masterID => PLB_masterID,
      PLB_abort => PLB_abort,
      PLB_busLock => PLB_busLock,
      PLB_RNW => PLB_RNW,
      PLB_BE => PLB_BE,
      PLB_MSize => PLB_MSize,
      PLB_size => PLB_size,
      PLB_type => PLB_type,
      PLB_lockErr => PLB_lockErr,
      PLB_wrDBus => PLB_wrDBus,
      PLB_wrBurst => PLB_wrBurst,
      PLB_rdBurst => PLB_rdBurst,
      PLB_wrPendReq => PLB_wrPendReq,
      PLB_rdPendReq => PLB_rdPendReq,
      PLB_wrPendPri => PLB_wrPendPri,
      PLB_rdPendPri => PLB_rdPendPri,
      PLB_reqPri => PLB_reqPri,
      PLB_TAttribute => PLB_TAttribute,
      Sl_addrAck => Sl_addrAck,
      Sl_SSize => Sl_SSize,
      Sl_wait => Sl_wait,
      Sl_rearbitrate => Sl_rearbitrate,
      Sl_wrDAck => Sl_wrDAck,
      Sl_wrComp => Sl_wrComp,
      Sl_wrBTerm => Sl_wrBTerm,
      Sl_rdDBus => Sl_rdDBus,
      Sl_rdWdAddr => Sl_rdWdAddr,
      Sl_rdDAck => Sl_rdDAck,
      Sl_rdComp => Sl_rdComp,
      Sl_rdBTerm => Sl_rdBTerm,
      Sl_MBusy => Sl_MBusy,
      Sl_MWrErr => Sl_MWrErr,
      Sl_MRdErr => Sl_MRdErr,
      Sl_MIRQ => Sl_MIRQ,
      Clk24M_I => Clk24M_I,
      CLK24M_LOCKED_I => CLK24M_LOCKED_I,
      DEBUG_O => DEBUG_O,
      VFBC_CMD_CLK => VFBC_CMD_CLK,
      VFBC_CMD_RESET => VFBC_CMD_RESET,
      VFBC_CMD_DATA => VFBC_CMD_DATA,
      VFBC_CMD_WRITE => VFBC_CMD_WRITE,
      VFBC_CMD_END => VFBC_CMD_END,
      VFBC_CMD_FULL => VFBC_CMD_FULL,
      VFBC_CMD_ALMOST_FULL => VFBC_CMD_ALMOST_FULL,
      VFBC_CMD_IDLE => VFBC_CMD_IDLE,
      VFBC_WD_CLK => VFBC_WD_CLK,
      VFBC_WD_RESET => VFBC_WD_RESET,
      VFBC_WD_WRITE => VFBC_WD_WRITE,
      VFBC_WD_END_BURST => VFBC_WD_END_BURST,
      VFBC_WD_FLUSH => VFBC_WD_FLUSH,
      VFBC_WD_DATA => VFBC_WD_DATA,
      VFBC_WD_DATA_BE => VFBC_WD_DATA_BE,
      VFBC_WD_FULL => VFBC_WD_FULL,
      VFBC_WD_ALMOST_FULL => VFBC_WD_ALMOST_FULL,
      CAM_MCLK => CAM_MCLK,
      CAM_RST_N => CAM_RST_N,
      CAM_POWERDOWN => CAM_POWERDOWN,
      CAM_PCLK => CAM_PCLK,
      CAM_FV => CAM_FV,
      CAM_LV => CAM_LV,
      CAM_DATA => CAM_DATA
    );

end architecture STRUCTURE;

