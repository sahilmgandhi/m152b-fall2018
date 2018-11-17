-------------------------------------------------------------------------------
-- system_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity system_stub is
  port (
    fpga_0_RS232_Uart_0_RX_pin : in std_logic;
    fpga_0_RS232_Uart_0_TX_pin : out std_logic;
    fpga_0_DDR2_SDRAM_DDR2_Clk_pin : out std_logic_vector(1 downto 0);
    fpga_0_DDR2_SDRAM_DDR2_Clk_n_pin : out std_logic_vector(1 downto 0);
    fpga_0_DDR2_SDRAM_DDR2_CE_pin : out std_logic_vector(1 downto 0);
    fpga_0_DDR2_SDRAM_DDR2_CS_n_pin : out std_logic_vector(1 downto 0);
    fpga_0_DDR2_SDRAM_DDR2_ODT_pin : out std_logic_vector(1 downto 0);
    fpga_0_DDR2_SDRAM_DDR2_RAS_n_pin : out std_logic;
    fpga_0_DDR2_SDRAM_DDR2_CAS_n_pin : out std_logic;
    fpga_0_DDR2_SDRAM_DDR2_WE_n_pin : out std_logic;
    fpga_0_DDR2_SDRAM_DDR2_BankAddr_pin : out std_logic_vector(1 downto 0);
    fpga_0_DDR2_SDRAM_DDR2_Addr_pin : out std_logic_vector(12 downto 0);
    fpga_0_DDR2_SDRAM_DDR2_DQ_pin : inout std_logic_vector(63 downto 0);
    fpga_0_DDR2_SDRAM_DDR2_DM_pin : out std_logic_vector(7 downto 0);
    fpga_0_DDR2_SDRAM_DDR2_DQS_pin : inout std_logic_vector(7 downto 0);
    fpga_0_DDR2_SDRAM_DDR2_DQS_n_pin : inout std_logic_vector(7 downto 0);
    fpga_0_enc_sig_a_pin : inout std_logic;
    fpga_0_enc_sig_b_pin : inout std_logic;
    fpga_0_Button_In_pin : inout std_logic;
    fpga_0_clk_1_sys_clk_pin : in std_logic;
    fpga_0_rst_1_sys_rst_pin : in std_logic;
    hdmi_0_CH7301_clk_p_pin : out std_logic;
    hdmi_0_CH7301_clk_n_pin : out std_logic;
    hdmi_0_CH7301_data_pin : out std_logic_vector(11 downto 0);
    hdmi_0_CH7301_h_sync_pin : out std_logic;
    hdmi_0_CH7301_v_sync_pin : out std_logic;
    hdmi_0_CH7301_de_pin : out std_logic;
    hdmi_0_CH7301_scl_pin : out std_logic;
    hdmi_0_CH7301_sda_pin : out std_logic;
    hdmi_0_CH7301_rstn_pin : out std_logic;
    Cam_Ctrl_0_CAM_MCLK_pin : out std_logic;
    Cam_Ctrl_0_CAM_RST_N_pin : out std_logic;
    Cam_Ctrl_0_CAM_POWERDOWN_pin : out std_logic;
    Cam_Ctrl_0_CAM_PCLK_pin : in std_logic;
    Cam_Ctrl_0_CAM_FV_pin : in std_logic;
    Cam_Ctrl_0_CAM_LV_pin : in std_logic;
    Cam_Ctrl_0_CAM_DATA_pin : in std_logic_vector(7 downto 0);
    Cam_Ctrl_1_CAM_MCLK_pin : out std_logic;
    Cam_Ctrl_1_CAM_RST_N_pin : out std_logic;
    Cam_Ctrl_1_CAM_POWERDOWN_pin : out std_logic;
    Cam_Ctrl_1_CAM_PCLK_pin : in std_logic;
    Cam_Ctrl_1_CAM_FV_pin : in std_logic;
    Cam_Ctrl_1_CAM_LV_pin : in std_logic;
    Cam_Ctrl_1_CAM_DATA_pin : in std_logic_vector(7 downto 0);
    Cam_Iic_0_Sda_pin : inout std_logic;
    Cam_Iic_0_Scl_pin : inout std_logic;
    Cam_Iic_1_Sda_pin : inout std_logic;
    Cam_Iic_1_Scl_pin : inout std_logic;
    xps_spi_0_IP2INTC_Irpt_pin : out std_logic;
    xps_spi_0_MOSI_pin : inout std_logic;
    xps_spi_0_SS_pin : inout std_logic;
    xps_spi_0_MISO_pin : inout std_logic;
    xps_spi_0_SCK_pin : inout std_logic;
    xps_spi_0_SPISEL_pin : in std_logic
  );
end system_stub;

architecture STRUCTURE of system_stub is

  component system is
    port (
      fpga_0_RS232_Uart_0_RX_pin : in std_logic;
      fpga_0_RS232_Uart_0_TX_pin : out std_logic;
      fpga_0_DDR2_SDRAM_DDR2_Clk_pin : out std_logic_vector(1 downto 0);
      fpga_0_DDR2_SDRAM_DDR2_Clk_n_pin : out std_logic_vector(1 downto 0);
      fpga_0_DDR2_SDRAM_DDR2_CE_pin : out std_logic_vector(1 downto 0);
      fpga_0_DDR2_SDRAM_DDR2_CS_n_pin : out std_logic_vector(1 downto 0);
      fpga_0_DDR2_SDRAM_DDR2_ODT_pin : out std_logic_vector(1 downto 0);
      fpga_0_DDR2_SDRAM_DDR2_RAS_n_pin : out std_logic;
      fpga_0_DDR2_SDRAM_DDR2_CAS_n_pin : out std_logic;
      fpga_0_DDR2_SDRAM_DDR2_WE_n_pin : out std_logic;
      fpga_0_DDR2_SDRAM_DDR2_BankAddr_pin : out std_logic_vector(1 downto 0);
      fpga_0_DDR2_SDRAM_DDR2_Addr_pin : out std_logic_vector(12 downto 0);
      fpga_0_DDR2_SDRAM_DDR2_DQ_pin : inout std_logic_vector(63 downto 0);
      fpga_0_DDR2_SDRAM_DDR2_DM_pin : out std_logic_vector(7 downto 0);
      fpga_0_DDR2_SDRAM_DDR2_DQS_pin : inout std_logic_vector(7 downto 0);
      fpga_0_DDR2_SDRAM_DDR2_DQS_n_pin : inout std_logic_vector(7 downto 0);
      fpga_0_enc_sig_a_pin : inout std_logic;
      fpga_0_enc_sig_b_pin : inout std_logic;
      fpga_0_Button_In_pin : inout std_logic;
      fpga_0_clk_1_sys_clk_pin : in std_logic;
      fpga_0_rst_1_sys_rst_pin : in std_logic;
      hdmi_0_CH7301_clk_p_pin : out std_logic;
      hdmi_0_CH7301_clk_n_pin : out std_logic;
      hdmi_0_CH7301_data_pin : out std_logic_vector(11 downto 0);
      hdmi_0_CH7301_h_sync_pin : out std_logic;
      hdmi_0_CH7301_v_sync_pin : out std_logic;
      hdmi_0_CH7301_de_pin : out std_logic;
      hdmi_0_CH7301_scl_pin : out std_logic;
      hdmi_0_CH7301_sda_pin : out std_logic;
      hdmi_0_CH7301_rstn_pin : out std_logic;
      Cam_Ctrl_0_CAM_MCLK_pin : out std_logic;
      Cam_Ctrl_0_CAM_RST_N_pin : out std_logic;
      Cam_Ctrl_0_CAM_POWERDOWN_pin : out std_logic;
      Cam_Ctrl_0_CAM_PCLK_pin : in std_logic;
      Cam_Ctrl_0_CAM_FV_pin : in std_logic;
      Cam_Ctrl_0_CAM_LV_pin : in std_logic;
      Cam_Ctrl_0_CAM_DATA_pin : in std_logic_vector(7 downto 0);
      Cam_Ctrl_1_CAM_MCLK_pin : out std_logic;
      Cam_Ctrl_1_CAM_RST_N_pin : out std_logic;
      Cam_Ctrl_1_CAM_POWERDOWN_pin : out std_logic;
      Cam_Ctrl_1_CAM_PCLK_pin : in std_logic;
      Cam_Ctrl_1_CAM_FV_pin : in std_logic;
      Cam_Ctrl_1_CAM_LV_pin : in std_logic;
      Cam_Ctrl_1_CAM_DATA_pin : in std_logic_vector(7 downto 0);
      Cam_Iic_0_Sda_pin : inout std_logic;
      Cam_Iic_0_Scl_pin : inout std_logic;
      Cam_Iic_1_Sda_pin : inout std_logic;
      Cam_Iic_1_Scl_pin : inout std_logic;
      xps_spi_0_IP2INTC_Irpt_pin : out std_logic;
      xps_spi_0_MOSI_pin : inout std_logic;
      xps_spi_0_SS_pin : inout std_logic;
      xps_spi_0_MISO_pin : inout std_logic;
      xps_spi_0_SCK_pin : inout std_logic;
      xps_spi_0_SPISEL_pin : in std_logic
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of system : component is "user_black_box";

begin

  system_i : system
    port map (
      fpga_0_RS232_Uart_0_RX_pin => fpga_0_RS232_Uart_0_RX_pin,
      fpga_0_RS232_Uart_0_TX_pin => fpga_0_RS232_Uart_0_TX_pin,
      fpga_0_DDR2_SDRAM_DDR2_Clk_pin => fpga_0_DDR2_SDRAM_DDR2_Clk_pin,
      fpga_0_DDR2_SDRAM_DDR2_Clk_n_pin => fpga_0_DDR2_SDRAM_DDR2_Clk_n_pin,
      fpga_0_DDR2_SDRAM_DDR2_CE_pin => fpga_0_DDR2_SDRAM_DDR2_CE_pin,
      fpga_0_DDR2_SDRAM_DDR2_CS_n_pin => fpga_0_DDR2_SDRAM_DDR2_CS_n_pin,
      fpga_0_DDR2_SDRAM_DDR2_ODT_pin => fpga_0_DDR2_SDRAM_DDR2_ODT_pin,
      fpga_0_DDR2_SDRAM_DDR2_RAS_n_pin => fpga_0_DDR2_SDRAM_DDR2_RAS_n_pin,
      fpga_0_DDR2_SDRAM_DDR2_CAS_n_pin => fpga_0_DDR2_SDRAM_DDR2_CAS_n_pin,
      fpga_0_DDR2_SDRAM_DDR2_WE_n_pin => fpga_0_DDR2_SDRAM_DDR2_WE_n_pin,
      fpga_0_DDR2_SDRAM_DDR2_BankAddr_pin => fpga_0_DDR2_SDRAM_DDR2_BankAddr_pin,
      fpga_0_DDR2_SDRAM_DDR2_Addr_pin => fpga_0_DDR2_SDRAM_DDR2_Addr_pin,
      fpga_0_DDR2_SDRAM_DDR2_DQ_pin => fpga_0_DDR2_SDRAM_DDR2_DQ_pin,
      fpga_0_DDR2_SDRAM_DDR2_DM_pin => fpga_0_DDR2_SDRAM_DDR2_DM_pin,
      fpga_0_DDR2_SDRAM_DDR2_DQS_pin => fpga_0_DDR2_SDRAM_DDR2_DQS_pin,
      fpga_0_DDR2_SDRAM_DDR2_DQS_n_pin => fpga_0_DDR2_SDRAM_DDR2_DQS_n_pin,
      fpga_0_enc_sig_a_pin => fpga_0_enc_sig_a_pin,
      fpga_0_enc_sig_b_pin => fpga_0_enc_sig_b_pin,
      fpga_0_Button_In_pin => fpga_0_Button_In_pin,
      fpga_0_clk_1_sys_clk_pin => fpga_0_clk_1_sys_clk_pin,
      fpga_0_rst_1_sys_rst_pin => fpga_0_rst_1_sys_rst_pin,
      hdmi_0_CH7301_clk_p_pin => hdmi_0_CH7301_clk_p_pin,
      hdmi_0_CH7301_clk_n_pin => hdmi_0_CH7301_clk_n_pin,
      hdmi_0_CH7301_data_pin => hdmi_0_CH7301_data_pin,
      hdmi_0_CH7301_h_sync_pin => hdmi_0_CH7301_h_sync_pin,
      hdmi_0_CH7301_v_sync_pin => hdmi_0_CH7301_v_sync_pin,
      hdmi_0_CH7301_de_pin => hdmi_0_CH7301_de_pin,
      hdmi_0_CH7301_scl_pin => hdmi_0_CH7301_scl_pin,
      hdmi_0_CH7301_sda_pin => hdmi_0_CH7301_sda_pin,
      hdmi_0_CH7301_rstn_pin => hdmi_0_CH7301_rstn_pin,
      Cam_Ctrl_0_CAM_MCLK_pin => Cam_Ctrl_0_CAM_MCLK_pin,
      Cam_Ctrl_0_CAM_RST_N_pin => Cam_Ctrl_0_CAM_RST_N_pin,
      Cam_Ctrl_0_CAM_POWERDOWN_pin => Cam_Ctrl_0_CAM_POWERDOWN_pin,
      Cam_Ctrl_0_CAM_PCLK_pin => Cam_Ctrl_0_CAM_PCLK_pin,
      Cam_Ctrl_0_CAM_FV_pin => Cam_Ctrl_0_CAM_FV_pin,
      Cam_Ctrl_0_CAM_LV_pin => Cam_Ctrl_0_CAM_LV_pin,
      Cam_Ctrl_0_CAM_DATA_pin => Cam_Ctrl_0_CAM_DATA_pin,
      Cam_Ctrl_1_CAM_MCLK_pin => Cam_Ctrl_1_CAM_MCLK_pin,
      Cam_Ctrl_1_CAM_RST_N_pin => Cam_Ctrl_1_CAM_RST_N_pin,
      Cam_Ctrl_1_CAM_POWERDOWN_pin => Cam_Ctrl_1_CAM_POWERDOWN_pin,
      Cam_Ctrl_1_CAM_PCLK_pin => Cam_Ctrl_1_CAM_PCLK_pin,
      Cam_Ctrl_1_CAM_FV_pin => Cam_Ctrl_1_CAM_FV_pin,
      Cam_Ctrl_1_CAM_LV_pin => Cam_Ctrl_1_CAM_LV_pin,
      Cam_Ctrl_1_CAM_DATA_pin => Cam_Ctrl_1_CAM_DATA_pin,
      Cam_Iic_0_Sda_pin => Cam_Iic_0_Sda_pin,
      Cam_Iic_0_Scl_pin => Cam_Iic_0_Scl_pin,
      Cam_Iic_1_Sda_pin => Cam_Iic_1_Sda_pin,
      Cam_Iic_1_Scl_pin => Cam_Iic_1_Scl_pin,
      xps_spi_0_IP2INTC_Irpt_pin => xps_spi_0_IP2INTC_Irpt_pin,
      xps_spi_0_MOSI_pin => xps_spi_0_MOSI_pin,
      xps_spi_0_SS_pin => xps_spi_0_SS_pin,
      xps_spi_0_MISO_pin => xps_spi_0_MISO_pin,
      xps_spi_0_SCK_pin => xps_spi_0_SCK_pin,
      xps_spi_0_SPISEL_pin => xps_spi_0_SPISEL_pin
    );

end architecture STRUCTURE;

