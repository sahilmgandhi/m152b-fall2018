
/*******************************************************************
*
* CAUTION: This file is automatically generated by libgen.
* Version: Xilinx EDK 2013.2 EDK_P.68d
* DO NOT EDIT.
*
* Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.

* 
* Description: Driver parameters
*
*******************************************************************/

#define STDIN_BASEADDRESS 0x84000000
#define STDOUT_BASEADDRESS 0x84000000

/******************************************************************/


/* Definitions for peripheral CAM_CTRL_0 */
#define XPAR_CAM_CTRL_0_BASEADDR 0xCFA20000
#define XPAR_CAM_CTRL_0_HIGHADDR 0xCFA2FFFF


/* Definitions for peripheral CAM_CTRL_1 */
#define XPAR_CAM_CTRL_1_BASEADDR 0xCFA00000
#define XPAR_CAM_CTRL_1_HIGHADDR 0xCFA0FFFF


/* Definitions for peripheral DVMA_0 */
#define XPAR_DVMA_0_BASEADDR 0xC7600000
#define XPAR_DVMA_0_HIGHADDR 0xC760FFFF


/* Definitions for peripheral HDMI_0 */
#define XPAR_HDMI_0_BASEADDR 0xCF400000
#define XPAR_HDMI_0_HIGHADDR 0xCF40FFFF


/******************************************************************/

/* Definitions for driver IIC */
#define XPAR_XIIC_NUM_INSTANCES 2

/* Definitions for peripheral CAM_IIC_0 */
#define XPAR_CAM_IIC_0_DEVICE_ID 0
#define XPAR_CAM_IIC_0_BASEADDR 0x81620000
#define XPAR_CAM_IIC_0_HIGHADDR 0x8162FFFF
#define XPAR_CAM_IIC_0_TEN_BIT_ADR 0
#define XPAR_CAM_IIC_0_GPO_WIDTH 1


/* Definitions for peripheral CAM_IIC_1 */
#define XPAR_CAM_IIC_1_DEVICE_ID 1
#define XPAR_CAM_IIC_1_BASEADDR 0x81600000
#define XPAR_CAM_IIC_1_HIGHADDR 0x8160FFFF
#define XPAR_CAM_IIC_1_TEN_BIT_ADR 0
#define XPAR_CAM_IIC_1_GPO_WIDTH 1


/******************************************************************/

/* Canonical definitions for peripheral CAM_IIC_0 */
#define XPAR_IIC_0_DEVICE_ID XPAR_CAM_IIC_0_DEVICE_ID
#define XPAR_IIC_0_BASEADDR 0x81620000
#define XPAR_IIC_0_HIGHADDR 0x8162FFFF
#define XPAR_IIC_0_TEN_BIT_ADR 0
#define XPAR_IIC_0_GPO_WIDTH 1

/* Canonical definitions for peripheral CAM_IIC_1 */
#define XPAR_IIC_1_DEVICE_ID XPAR_CAM_IIC_1_DEVICE_ID
#define XPAR_IIC_1_BASEADDR 0x81600000
#define XPAR_IIC_1_HIGHADDR 0x8160FFFF
#define XPAR_IIC_1_TEN_BIT_ADR 0
#define XPAR_IIC_1_GPO_WIDTH 1


/******************************************************************/

/* Definitions for driver MPMC */
#define XPAR_XMPMC_NUM_INSTANCES 1

/* Definitions for peripheral DDR2_SDRAM */
#define XPAR_DDR2_SDRAM_DEVICE_ID 0
#define XPAR_DDR2_SDRAM_MPMC_CTRL_BASEADDR 0xFFFFFFFF
#define XPAR_DDR2_SDRAM_INCLUDE_ECC_SUPPORT 0
#define XPAR_DDR2_SDRAM_USE_STATIC_PHY 0
#define XPAR_DDR2_SDRAM_PM_ENABLE 0
#define XPAR_DDR2_SDRAM_NUM_PORTS 4
#define XPAR_DDR2_SDRAM_MEM_DATA_WIDTH 64
#define XPAR_DDR2_SDRAM_MEM_PART_NUM_BANK_BITS 2
#define XPAR_DDR2_SDRAM_MEM_PART_NUM_ROW_BITS 13
#define XPAR_DDR2_SDRAM_MEM_PART_NUM_COL_BITS 10
#define XPAR_DDR2_SDRAM_MEM_TYPE DDR2
#define XPAR_DDR2_SDRAM_ECC_SEC_THRESHOLD 1
#define XPAR_DDR2_SDRAM_ECC_DEC_THRESHOLD 1
#define XPAR_DDR2_SDRAM_ECC_PEC_THRESHOLD 1
#define XPAR_DDR2_SDRAM_MEM_DQS_WIDTH 8
#define XPAR_DDR2_SDRAM_MPMC_CLK0_PERIOD_PS 8000


/******************************************************************/


/* Definitions for peripheral DDR2_SDRAM */
#define XPAR_DDR2_SDRAM_MPMC_BASEADDR 0x90000000
#define XPAR_DDR2_SDRAM_MPMC_HIGHADDR 0x9FFFFFFF
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL0 0x000
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL0 0x00b
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL2 0x014
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL2 0x01f
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL3 0x020
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL3 0x027
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL4 0x028
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL4 0x033
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL5 0x034
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL5 0x03b
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL6 0x03c
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL6 0x047
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL7 0x048
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL7 0x04f
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL8 0x050
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL8 0x05d
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL9 0x05e
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL9 0x066
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL10 0x067
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL10 0x078
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL11 0x079
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL11 0x085
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL12 0x086
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL12 0x097
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL13 0x098
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL13 0x0a4
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL14 0x0a5
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL14 0x0b5
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL15 0x0b6
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL15 0x0b7
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL16 0x0d9
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL16 0x0da


/******************************************************************/

/* Canonical definitions for peripheral DDR2_SDRAM */
#define XPAR_MPMC_0_DEVICE_ID XPAR_DDR2_SDRAM_DEVICE_ID
#define XPAR_MPMC_0_MPMC_BASEADDR 0x90000000
#define XPAR_MPMC_0_MPMC_HIGHADDR 0x9FFFFFFF
#define XPAR_MPMC_0_MPMC_CTRL_BASEADDR 0xFFFFFFFF
#define XPAR_MPMC_0_INCLUDE_ECC_SUPPORT 0
#define XPAR_MPMC_0_USE_STATIC_PHY 0
#define XPAR_MPMC_0_PM_ENABLE 0
#define XPAR_MPMC_0_NUM_PORTS 4
#define XPAR_MPMC_0_MEM_DATA_WIDTH 64
#define XPAR_MPMC_0_MEM_PART_NUM_BANK_BITS 2
#define XPAR_MPMC_0_MEM_PART_NUM_ROW_BITS 13
#define XPAR_MPMC_0_MEM_PART_NUM_COL_BITS 10
#define XPAR_MPMC_0_MEM_TYPE DDR2
#define XPAR_MPMC_0_ECC_SEC_THRESHOLD 1
#define XPAR_MPMC_0_ECC_DEC_THRESHOLD 1
#define XPAR_MPMC_0_ECC_PEC_THRESHOLD 1
#define XPAR_MPMC_0_MEM_DQS_WIDTH 8
#define XPAR_MPMC_0_MPMC_CLK0_PERIOD_PS 8000


/******************************************************************/

/* Definitions for driver BRAM */
#define XPAR_XBRAM_NUM_INSTANCES 2

/* Definitions for peripheral DLMB_CNTLR */
#define XPAR_DLMB_CNTLR_DEVICE_ID 0
#define XPAR_DLMB_CNTLR_DATA_WIDTH 32
#define XPAR_DLMB_CNTLR_ECC 0
#define XPAR_DLMB_CNTLR_FAULT_INJECT 0
#define XPAR_DLMB_CNTLR_CE_FAILING_REGISTERS 0
#define XPAR_DLMB_CNTLR_UE_FAILING_REGISTERS 0
#define XPAR_DLMB_CNTLR_ECC_STATUS_REGISTERS 0
#define XPAR_DLMB_CNTLR_CE_COUNTER_WIDTH 0
#define XPAR_DLMB_CNTLR_ECC_ONOFF_REGISTER 0
#define XPAR_DLMB_CNTLR_ECC_ONOFF_RESET_VALUE 0
#define XPAR_DLMB_CNTLR_WRITE_ACCESS 0
#define XPAR_DLMB_CNTLR_BASEADDR 0x00000000
#define XPAR_DLMB_CNTLR_HIGHADDR 0x0000FFFF


/* Definitions for peripheral ILMB_CNTLR */
#define XPAR_ILMB_CNTLR_DEVICE_ID 1
#define XPAR_ILMB_CNTLR_DATA_WIDTH 32
#define XPAR_ILMB_CNTLR_ECC 0
#define XPAR_ILMB_CNTLR_FAULT_INJECT 0
#define XPAR_ILMB_CNTLR_CE_FAILING_REGISTERS 0
#define XPAR_ILMB_CNTLR_UE_FAILING_REGISTERS 0
#define XPAR_ILMB_CNTLR_ECC_STATUS_REGISTERS 0
#define XPAR_ILMB_CNTLR_CE_COUNTER_WIDTH 0
#define XPAR_ILMB_CNTLR_ECC_ONOFF_REGISTER 0
#define XPAR_ILMB_CNTLR_ECC_ONOFF_RESET_VALUE 0
#define XPAR_ILMB_CNTLR_WRITE_ACCESS 0
#define XPAR_ILMB_CNTLR_BASEADDR 0x00000000
#define XPAR_ILMB_CNTLR_HIGHADDR 0x0000FFFF


/******************************************************************/

/* Canonical definitions for peripheral DLMB_CNTLR */
#define XPAR_BRAM_0_DEVICE_ID XPAR_DLMB_CNTLR_DEVICE_ID
#define XPAR_BRAM_0_DATA_WIDTH 32
#define XPAR_BRAM_0_ECC 0
#define XPAR_BRAM_0_FAULT_INJECT 0
#define XPAR_BRAM_0_CE_FAILING_REGISTERS 0
#define XPAR_BRAM_0_UE_FAILING_REGISTERS 0
#define XPAR_BRAM_0_ECC_STATUS_REGISTERS 0
#define XPAR_BRAM_0_CE_COUNTER_WIDTH 0
#define XPAR_BRAM_0_ECC_ONOFF_REGISTER 0
#define XPAR_BRAM_0_ECC_ONOFF_RESET_VALUE 0
#define XPAR_BRAM_0_WRITE_ACCESS 0
#define XPAR_BRAM_0_BASEADDR 0x00000000
#define XPAR_BRAM_0_HIGHADDR 0x0000FFFF

/* Canonical definitions for peripheral ILMB_CNTLR */
#define XPAR_BRAM_1_DEVICE_ID XPAR_ILMB_CNTLR_DEVICE_ID
#define XPAR_BRAM_1_DATA_WIDTH 32
#define XPAR_BRAM_1_ECC 0
#define XPAR_BRAM_1_FAULT_INJECT 0
#define XPAR_BRAM_1_CE_FAILING_REGISTERS 0
#define XPAR_BRAM_1_UE_FAILING_REGISTERS 0
#define XPAR_BRAM_1_ECC_STATUS_REGISTERS 0
#define XPAR_BRAM_1_CE_COUNTER_WIDTH 0
#define XPAR_BRAM_1_ECC_ONOFF_REGISTER 0
#define XPAR_BRAM_1_ECC_ONOFF_RESET_VALUE 0
#define XPAR_BRAM_1_WRITE_ACCESS 0
#define XPAR_BRAM_1_BASEADDR 0x00000000
#define XPAR_BRAM_1_HIGHADDR 0x0000FFFF


/******************************************************************/

/* Definitions for driver UARTLITE */
#define XPAR_XUARTLITE_NUM_INSTANCES 2

/* Definitions for peripheral MDM_0 */
#define XPAR_MDM_0_BASEADDR 0x84400000
#define XPAR_MDM_0_HIGHADDR 0x8440FFFF
#define XPAR_MDM_0_DEVICE_ID 0
#define XPAR_MDM_0_BAUDRATE 0
#define XPAR_MDM_0_USE_PARITY 0
#define XPAR_MDM_0_ODD_PARITY 0
#define XPAR_MDM_0_DATA_BITS 0


/* Definitions for peripheral RS232_UART_0 */
#define XPAR_RS232_UART_0_BASEADDR 0x84000000
#define XPAR_RS232_UART_0_HIGHADDR 0x8400FFFF
#define XPAR_RS232_UART_0_DEVICE_ID 1
#define XPAR_RS232_UART_0_BAUDRATE 115200
#define XPAR_RS232_UART_0_USE_PARITY 0
#define XPAR_RS232_UART_0_ODD_PARITY 0
#define XPAR_RS232_UART_0_DATA_BITS 8


/******************************************************************/

/* Canonical definitions for peripheral MDM_0 */
#define XPAR_UARTLITE_0_DEVICE_ID XPAR_MDM_0_DEVICE_ID
#define XPAR_UARTLITE_0_BASEADDR 0x84400000
#define XPAR_UARTLITE_0_HIGHADDR 0x8440FFFF
#define XPAR_UARTLITE_0_BAUDRATE 0
#define XPAR_UARTLITE_0_USE_PARITY 0
#define XPAR_UARTLITE_0_ODD_PARITY 0
#define XPAR_UARTLITE_0_DATA_BITS 0
#define XPAR_UARTLITE_0_SIO_CHAN -1

/* Canonical definitions for peripheral RS232_UART_0 */
#define XPAR_UARTLITE_1_DEVICE_ID XPAR_RS232_UART_0_DEVICE_ID
#define XPAR_UARTLITE_1_BASEADDR 0x84000000
#define XPAR_UARTLITE_1_HIGHADDR 0x8400FFFF
#define XPAR_UARTLITE_1_BAUDRATE 115200
#define XPAR_UARTLITE_1_USE_PARITY 0
#define XPAR_UARTLITE_1_ODD_PARITY 0
#define XPAR_UARTLITE_1_DATA_BITS 8
#define XPAR_UARTLITE_1_SIO_CHAN -1


/******************************************************************/

/* Definitions for bus frequencies */
#define XPAR_CPU_DPLB_FREQ_HZ 125000000
#define XPAR_CPU_IPLB_FREQ_HZ 125000000
/******************************************************************/

/* Canonical definitions for bus frequencies */
#define XPAR_PROC_BUS_0_FREQ_HZ 125000000
/******************************************************************/

#define XPAR_CPU_CORE_CLOCK_FREQ_HZ 125000000
#define XPAR_MICROBLAZE_CORE_CLOCK_FREQ_HZ 125000000

/******************************************************************/


/* Definitions for peripheral MICROBLAZE_0 */
#define XPAR_MICROBLAZE_0_SCO 0
#define XPAR_MICROBLAZE_0_FREQ 125000000
#define XPAR_MICROBLAZE_0_DATA_SIZE 32
#define XPAR_MICROBLAZE_0_DYNAMIC_BUS_SIZING 1
#define XPAR_MICROBLAZE_0_AVOID_PRIMITIVES 0
#define XPAR_MICROBLAZE_0_FAULT_TOLERANT 0
#define XPAR_MICROBLAZE_0_ECC_USE_CE_EXCEPTION 0
#define XPAR_MICROBLAZE_0_LOCKSTEP_SLAVE 0
#define XPAR_MICROBLAZE_0_ENDIANNESS 0
#define XPAR_MICROBLAZE_0_AREA_OPTIMIZED 0
#define XPAR_MICROBLAZE_0_OPTIMIZATION 0
#define XPAR_MICROBLAZE_0_INTERCONNECT 1
#define XPAR_MICROBLAZE_0_STREAM_INTERCONNECT 0
#define XPAR_MICROBLAZE_0_BASE_VECTORS 0x00000000
#define XPAR_MICROBLAZE_0_DPLB_DWIDTH 64
#define XPAR_MICROBLAZE_0_DPLB_NATIVE_DWIDTH 32
#define XPAR_MICROBLAZE_0_DPLB_BURST_EN 0
#define XPAR_MICROBLAZE_0_DPLB_P2P 0
#define XPAR_MICROBLAZE_0_IPLB_DWIDTH 64
#define XPAR_MICROBLAZE_0_IPLB_NATIVE_DWIDTH 32
#define XPAR_MICROBLAZE_0_IPLB_BURST_EN 0
#define XPAR_MICROBLAZE_0_IPLB_P2P 0
#define XPAR_MICROBLAZE_0_M_AXI_DP_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_0_M_AXI_DP_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_DP_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_0_M_AXI_DP_SUPPORTS_WRITE 1
#define XPAR_MICROBLAZE_0_M_AXI_DP_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_0_M_AXI_DP_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_DP_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_DP_PROTOCOL AXI4LITE
#define XPAR_MICROBLAZE_0_M_AXI_DP_EXCLUSIVE_ACCESS 0
#define XPAR_MICROBLAZE_0_INTERCONNECT_M_AXI_DP_READ_ISSUING 1
#define XPAR_MICROBLAZE_0_INTERCONNECT_M_AXI_DP_WRITE_ISSUING 1
#define XPAR_MICROBLAZE_0_M_AXI_IP_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_0_M_AXI_IP_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_IP_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_0_M_AXI_IP_SUPPORTS_WRITE 0
#define XPAR_MICROBLAZE_0_M_AXI_IP_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_0_M_AXI_IP_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_IP_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_IP_PROTOCOL AXI4LITE
#define XPAR_MICROBLAZE_0_INTERCONNECT_M_AXI_IP_READ_ISSUING 1
#define XPAR_MICROBLAZE_0_D_AXI 0
#define XPAR_MICROBLAZE_0_D_PLB 1
#define XPAR_MICROBLAZE_0_D_LMB 1
#define XPAR_MICROBLAZE_0_I_AXI 0
#define XPAR_MICROBLAZE_0_I_PLB 1
#define XPAR_MICROBLAZE_0_I_LMB 1
#define XPAR_MICROBLAZE_0_USE_MSR_INSTR 1
#define XPAR_MICROBLAZE_0_USE_PCMP_INSTR 1
#define XPAR_MICROBLAZE_0_USE_BARREL 1
#define XPAR_MICROBLAZE_0_USE_DIV 0
#define XPAR_MICROBLAZE_0_USE_HW_MUL 1
#define XPAR_MICROBLAZE_0_USE_FPU 0
#define XPAR_MICROBLAZE_0_USE_REORDER_INSTR 1
#define XPAR_MICROBLAZE_0_UNALIGNED_EXCEPTIONS 0
#define XPAR_MICROBLAZE_0_ILL_OPCODE_EXCEPTION 0
#define XPAR_MICROBLAZE_0_M_AXI_I_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_0_M_AXI_D_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_0_IPLB_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_0_DPLB_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_0_DIV_ZERO_EXCEPTION 0
#define XPAR_MICROBLAZE_0_FPU_EXCEPTION 0
#define XPAR_MICROBLAZE_0_FSL_EXCEPTION 0
#define XPAR_MICROBLAZE_0_USE_STACK_PROTECTION 0
#define XPAR_MICROBLAZE_0_PVR 0
#define XPAR_MICROBLAZE_0_PVR_USER1 0x00
#define XPAR_MICROBLAZE_0_PVR_USER2 0x00000000
#define XPAR_MICROBLAZE_0_DEBUG_ENABLED 1
#define XPAR_MICROBLAZE_0_NUMBER_OF_PC_BRK 1
#define XPAR_MICROBLAZE_0_NUMBER_OF_RD_ADDR_BRK 0
#define XPAR_MICROBLAZE_0_NUMBER_OF_WR_ADDR_BRK 0
#define XPAR_MICROBLAZE_0_INTERRUPT_IS_EDGE 0
#define XPAR_MICROBLAZE_0_EDGE_IS_POSITIVE 1
#define XPAR_MICROBLAZE_0_RESET_MSR 0x00000000
#define XPAR_MICROBLAZE_0_OPCODE_0X0_ILLEGAL 0
#define XPAR_MICROBLAZE_0_FSL_LINKS 0
#define XPAR_MICROBLAZE_0_FSL_DATA_SIZE 32
#define XPAR_MICROBLAZE_0_USE_EXTENDED_FSL_INSTR 0
#define XPAR_MICROBLAZE_0_M0_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S0_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M1_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S1_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M2_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S2_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M3_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S3_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M4_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S4_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M5_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S5_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M6_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S6_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M7_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S7_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M8_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S8_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M9_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S9_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M10_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S10_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M11_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S11_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M12_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S12_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M13_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S13_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M14_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S14_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M15_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S15_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M0_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S0_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M1_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S1_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M2_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S2_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M3_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S3_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M4_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S4_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M5_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S5_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M6_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S6_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M7_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S7_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M8_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S8_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M9_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S9_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M10_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S10_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M11_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S11_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M12_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S12_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M13_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S13_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M14_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S14_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M15_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S15_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_ICACHE_BASEADDR 0x00000000
#define XPAR_MICROBLAZE_0_ICACHE_HIGHADDR 0x3FFFFFFF
#define XPAR_MICROBLAZE_0_USE_ICACHE 0
#define XPAR_MICROBLAZE_0_ALLOW_ICACHE_WR 1
#define XPAR_MICROBLAZE_0_ADDR_TAG_BITS 0
#define XPAR_MICROBLAZE_0_CACHE_BYTE_SIZE 8192
#define XPAR_MICROBLAZE_0_ICACHE_USE_FSL 1
#define XPAR_MICROBLAZE_0_ICACHE_LINE_LEN 4
#define XPAR_MICROBLAZE_0_ICACHE_ALWAYS_USED 0
#define XPAR_MICROBLAZE_0_ICACHE_INTERFACE 0
#define XPAR_MICROBLAZE_0_ICACHE_VICTIMS 0
#define XPAR_MICROBLAZE_0_ICACHE_STREAMS 0
#define XPAR_MICROBLAZE_0_ICACHE_FORCE_TAG_LUTRAM 0
#define XPAR_MICROBLAZE_0_ICACHE_DATA_WIDTH 0
#define XPAR_MICROBLAZE_0_M_AXI_IC_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_0_M_AXI_IC_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_IC_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_0_M_AXI_IC_SUPPORTS_WRITE 0
#define XPAR_MICROBLAZE_0_M_AXI_IC_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_0_M_AXI_IC_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_IC_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_IC_PROTOCOL AXI4
#define XPAR_MICROBLAZE_0_M_AXI_IC_USER_VALUE 0b11111
#define XPAR_MICROBLAZE_0_M_AXI_IC_SUPPORTS_USER_SIGNALS 1
#define XPAR_MICROBLAZE_0_M_AXI_IC_AWUSER_WIDTH 5
#define XPAR_MICROBLAZE_0_M_AXI_IC_ARUSER_WIDTH 5
#define XPAR_MICROBLAZE_0_M_AXI_IC_WUSER_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_IC_RUSER_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_IC_BUSER_WIDTH 1
#define XPAR_MICROBLAZE_0_INTERCONNECT_M_AXI_IC_READ_ISSUING 2
#define XPAR_MICROBLAZE_0_DCACHE_BASEADDR 0x00000000
#define XPAR_MICROBLAZE_0_DCACHE_HIGHADDR 0x3FFFFFFF
#define XPAR_MICROBLAZE_0_USE_DCACHE 0
#define XPAR_MICROBLAZE_0_ALLOW_DCACHE_WR 1
#define XPAR_MICROBLAZE_0_DCACHE_ADDR_TAG 0
#define XPAR_MICROBLAZE_0_DCACHE_BYTE_SIZE 8192
#define XPAR_MICROBLAZE_0_DCACHE_USE_FSL 1
#define XPAR_MICROBLAZE_0_DCACHE_LINE_LEN 4
#define XPAR_MICROBLAZE_0_DCACHE_ALWAYS_USED 0
#define XPAR_MICROBLAZE_0_DCACHE_INTERFACE 0
#define XPAR_MICROBLAZE_0_DCACHE_USE_WRITEBACK 0
#define XPAR_MICROBLAZE_0_DCACHE_VICTIMS 0
#define XPAR_MICROBLAZE_0_DCACHE_FORCE_TAG_LUTRAM 0
#define XPAR_MICROBLAZE_0_DCACHE_DATA_WIDTH 0
#define XPAR_MICROBLAZE_0_M_AXI_DC_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_0_M_AXI_DC_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_DC_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_0_M_AXI_DC_SUPPORTS_WRITE 1
#define XPAR_MICROBLAZE_0_M_AXI_DC_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_0_M_AXI_DC_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_DC_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_DC_PROTOCOL AXI4
#define XPAR_MICROBLAZE_0_M_AXI_DC_EXCLUSIVE_ACCESS 0
#define XPAR_MICROBLAZE_0_M_AXI_DC_USER_VALUE 0b11111
#define XPAR_MICROBLAZE_0_M_AXI_DC_SUPPORTS_USER_SIGNALS 1
#define XPAR_MICROBLAZE_0_M_AXI_DC_AWUSER_WIDTH 5
#define XPAR_MICROBLAZE_0_M_AXI_DC_ARUSER_WIDTH 5
#define XPAR_MICROBLAZE_0_M_AXI_DC_WUSER_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_DC_RUSER_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_DC_BUSER_WIDTH 1
#define XPAR_MICROBLAZE_0_INTERCONNECT_M_AXI_DC_READ_ISSUING 2
#define XPAR_MICROBLAZE_0_INTERCONNECT_M_AXI_DC_WRITE_ISSUING 32
#define XPAR_MICROBLAZE_0_USE_MMU 0
#define XPAR_MICROBLAZE_0_MMU_DTLB_SIZE 4
#define XPAR_MICROBLAZE_0_MMU_ITLB_SIZE 2
#define XPAR_MICROBLAZE_0_MMU_TLB_ACCESS 3
#define XPAR_MICROBLAZE_0_MMU_ZONES 16
#define XPAR_MICROBLAZE_0_MMU_PRIVILEGED_INSTR 0
#define XPAR_MICROBLAZE_0_USE_INTERRUPT 0
#define XPAR_MICROBLAZE_0_USE_EXT_BRK 1
#define XPAR_MICROBLAZE_0_USE_EXT_NM_BRK 1
#define XPAR_MICROBLAZE_0_USE_BRANCH_TARGET_CACHE 0
#define XPAR_MICROBLAZE_0_BRANCH_TARGET_CACHE_SIZE 0
#define XPAR_MICROBLAZE_0_PC_WIDTH 32

/******************************************************************/

#define XPAR_CPU_ID 0
#define XPAR_MICROBLAZE_ID 0
#define XPAR_MICROBLAZE_SCO 0
#define XPAR_MICROBLAZE_FREQ 125000000
#define XPAR_MICROBLAZE_DATA_SIZE 32
#define XPAR_MICROBLAZE_DYNAMIC_BUS_SIZING 1
#define XPAR_MICROBLAZE_AVOID_PRIMITIVES 0
#define XPAR_MICROBLAZE_FAULT_TOLERANT 0
#define XPAR_MICROBLAZE_ECC_USE_CE_EXCEPTION 0
#define XPAR_MICROBLAZE_LOCKSTEP_SLAVE 0
#define XPAR_MICROBLAZE_ENDIANNESS 0
#define XPAR_MICROBLAZE_AREA_OPTIMIZED 0
#define XPAR_MICROBLAZE_OPTIMIZATION 0
#define XPAR_MICROBLAZE_INTERCONNECT 1
#define XPAR_MICROBLAZE_STREAM_INTERCONNECT 0
#define XPAR_MICROBLAZE_BASE_VECTORS 0x00000000
#define XPAR_MICROBLAZE_DPLB_DWIDTH 64
#define XPAR_MICROBLAZE_DPLB_NATIVE_DWIDTH 32
#define XPAR_MICROBLAZE_DPLB_BURST_EN 0
#define XPAR_MICROBLAZE_DPLB_P2P 0
#define XPAR_MICROBLAZE_IPLB_DWIDTH 64
#define XPAR_MICROBLAZE_IPLB_NATIVE_DWIDTH 32
#define XPAR_MICROBLAZE_IPLB_BURST_EN 0
#define XPAR_MICROBLAZE_IPLB_P2P 0
#define XPAR_MICROBLAZE_M_AXI_DP_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_M_AXI_DP_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_DP_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_M_AXI_DP_SUPPORTS_WRITE 1
#define XPAR_MICROBLAZE_M_AXI_DP_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_M_AXI_DP_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_DP_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_DP_PROTOCOL AXI4LITE
#define XPAR_MICROBLAZE_M_AXI_DP_EXCLUSIVE_ACCESS 0
#define XPAR_MICROBLAZE_INTERCONNECT_M_AXI_DP_READ_ISSUING 1
#define XPAR_MICROBLAZE_INTERCONNECT_M_AXI_DP_WRITE_ISSUING 1
#define XPAR_MICROBLAZE_M_AXI_IP_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_M_AXI_IP_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_IP_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_M_AXI_IP_SUPPORTS_WRITE 0
#define XPAR_MICROBLAZE_M_AXI_IP_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_M_AXI_IP_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_IP_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_IP_PROTOCOL AXI4LITE
#define XPAR_MICROBLAZE_INTERCONNECT_M_AXI_IP_READ_ISSUING 1
#define XPAR_MICROBLAZE_D_AXI 0
#define XPAR_MICROBLAZE_D_PLB 1
#define XPAR_MICROBLAZE_D_LMB 1
#define XPAR_MICROBLAZE_I_AXI 0
#define XPAR_MICROBLAZE_I_PLB 1
#define XPAR_MICROBLAZE_I_LMB 1
#define XPAR_MICROBLAZE_USE_MSR_INSTR 1
#define XPAR_MICROBLAZE_USE_PCMP_INSTR 1
#define XPAR_MICROBLAZE_USE_BARREL 1
#define XPAR_MICROBLAZE_USE_DIV 0
#define XPAR_MICROBLAZE_USE_HW_MUL 1
#define XPAR_MICROBLAZE_USE_FPU 0
#define XPAR_MICROBLAZE_USE_REORDER_INSTR 1
#define XPAR_MICROBLAZE_UNALIGNED_EXCEPTIONS 0
#define XPAR_MICROBLAZE_ILL_OPCODE_EXCEPTION 0
#define XPAR_MICROBLAZE_M_AXI_I_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_M_AXI_D_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_IPLB_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_DPLB_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_DIV_ZERO_EXCEPTION 0
#define XPAR_MICROBLAZE_FPU_EXCEPTION 0
#define XPAR_MICROBLAZE_FSL_EXCEPTION 0
#define XPAR_MICROBLAZE_USE_STACK_PROTECTION 0
#define XPAR_MICROBLAZE_PVR 0
#define XPAR_MICROBLAZE_PVR_USER1 0x00
#define XPAR_MICROBLAZE_PVR_USER2 0x00000000
#define XPAR_MICROBLAZE_DEBUG_ENABLED 1
#define XPAR_MICROBLAZE_NUMBER_OF_PC_BRK 1
#define XPAR_MICROBLAZE_NUMBER_OF_RD_ADDR_BRK 0
#define XPAR_MICROBLAZE_NUMBER_OF_WR_ADDR_BRK 0
#define XPAR_MICROBLAZE_INTERRUPT_IS_EDGE 0
#define XPAR_MICROBLAZE_EDGE_IS_POSITIVE 1
#define XPAR_MICROBLAZE_RESET_MSR 0x00000000
#define XPAR_MICROBLAZE_OPCODE_0X0_ILLEGAL 0
#define XPAR_MICROBLAZE_FSL_LINKS 0
#define XPAR_MICROBLAZE_FSL_DATA_SIZE 32
#define XPAR_MICROBLAZE_USE_EXTENDED_FSL_INSTR 0
#define XPAR_MICROBLAZE_M0_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S0_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M1_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S1_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M2_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S2_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M3_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S3_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M4_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S4_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M5_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S5_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M6_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S6_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M7_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S7_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M8_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S8_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M9_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S9_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M10_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S10_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M11_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S11_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M12_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S12_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M13_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S13_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M14_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S14_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M15_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S15_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M0_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S0_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M1_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S1_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M2_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S2_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M3_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S3_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M4_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S4_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M5_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S5_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M6_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S6_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M7_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S7_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M8_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S8_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M9_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S9_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M10_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S10_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M11_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S11_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M12_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S12_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M13_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S13_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M14_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S14_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M15_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S15_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_ICACHE_BASEADDR 0x00000000
#define XPAR_MICROBLAZE_ICACHE_HIGHADDR 0x3FFFFFFF
#define XPAR_MICROBLAZE_USE_ICACHE 0
#define XPAR_MICROBLAZE_ALLOW_ICACHE_WR 1
#define XPAR_MICROBLAZE_ADDR_TAG_BITS 0
#define XPAR_MICROBLAZE_CACHE_BYTE_SIZE 8192
#define XPAR_MICROBLAZE_ICACHE_USE_FSL 1
#define XPAR_MICROBLAZE_ICACHE_LINE_LEN 4
#define XPAR_MICROBLAZE_ICACHE_ALWAYS_USED 0
#define XPAR_MICROBLAZE_ICACHE_INTERFACE 0
#define XPAR_MICROBLAZE_ICACHE_VICTIMS 0
#define XPAR_MICROBLAZE_ICACHE_STREAMS 0
#define XPAR_MICROBLAZE_ICACHE_FORCE_TAG_LUTRAM 0
#define XPAR_MICROBLAZE_ICACHE_DATA_WIDTH 0
#define XPAR_MICROBLAZE_M_AXI_IC_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_M_AXI_IC_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_IC_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_M_AXI_IC_SUPPORTS_WRITE 0
#define XPAR_MICROBLAZE_M_AXI_IC_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_M_AXI_IC_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_IC_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_IC_PROTOCOL AXI4
#define XPAR_MICROBLAZE_M_AXI_IC_USER_VALUE 0b11111
#define XPAR_MICROBLAZE_M_AXI_IC_SUPPORTS_USER_SIGNALS 1
#define XPAR_MICROBLAZE_M_AXI_IC_AWUSER_WIDTH 5
#define XPAR_MICROBLAZE_M_AXI_IC_ARUSER_WIDTH 5
#define XPAR_MICROBLAZE_M_AXI_IC_WUSER_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_IC_RUSER_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_IC_BUSER_WIDTH 1
#define XPAR_MICROBLAZE_INTERCONNECT_M_AXI_IC_READ_ISSUING 2
#define XPAR_MICROBLAZE_DCACHE_BASEADDR 0x00000000
#define XPAR_MICROBLAZE_DCACHE_HIGHADDR 0x3FFFFFFF
#define XPAR_MICROBLAZE_USE_DCACHE 0
#define XPAR_MICROBLAZE_ALLOW_DCACHE_WR 1
#define XPAR_MICROBLAZE_DCACHE_ADDR_TAG 0
#define XPAR_MICROBLAZE_DCACHE_BYTE_SIZE 8192
#define XPAR_MICROBLAZE_DCACHE_USE_FSL 1
#define XPAR_MICROBLAZE_DCACHE_LINE_LEN 4
#define XPAR_MICROBLAZE_DCACHE_ALWAYS_USED 0
#define XPAR_MICROBLAZE_DCACHE_INTERFACE 0
#define XPAR_MICROBLAZE_DCACHE_USE_WRITEBACK 0
#define XPAR_MICROBLAZE_DCACHE_VICTIMS 0
#define XPAR_MICROBLAZE_DCACHE_FORCE_TAG_LUTRAM 0
#define XPAR_MICROBLAZE_DCACHE_DATA_WIDTH 0
#define XPAR_MICROBLAZE_M_AXI_DC_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_M_AXI_DC_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_DC_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_M_AXI_DC_SUPPORTS_WRITE 1
#define XPAR_MICROBLAZE_M_AXI_DC_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_M_AXI_DC_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_DC_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_DC_PROTOCOL AXI4
#define XPAR_MICROBLAZE_M_AXI_DC_EXCLUSIVE_ACCESS 0
#define XPAR_MICROBLAZE_M_AXI_DC_USER_VALUE 0b11111
#define XPAR_MICROBLAZE_M_AXI_DC_SUPPORTS_USER_SIGNALS 1
#define XPAR_MICROBLAZE_M_AXI_DC_AWUSER_WIDTH 5
#define XPAR_MICROBLAZE_M_AXI_DC_ARUSER_WIDTH 5
#define XPAR_MICROBLAZE_M_AXI_DC_WUSER_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_DC_RUSER_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_DC_BUSER_WIDTH 1
#define XPAR_MICROBLAZE_INTERCONNECT_M_AXI_DC_READ_ISSUING 2
#define XPAR_MICROBLAZE_INTERCONNECT_M_AXI_DC_WRITE_ISSUING 32
#define XPAR_MICROBLAZE_USE_MMU 0
#define XPAR_MICROBLAZE_MMU_DTLB_SIZE 4
#define XPAR_MICROBLAZE_MMU_ITLB_SIZE 2
#define XPAR_MICROBLAZE_MMU_TLB_ACCESS 3
#define XPAR_MICROBLAZE_MMU_ZONES 16
#define XPAR_MICROBLAZE_MMU_PRIVILEGED_INSTR 0
#define XPAR_MICROBLAZE_USE_INTERRUPT 0
#define XPAR_MICROBLAZE_USE_EXT_BRK 1
#define XPAR_MICROBLAZE_USE_EXT_NM_BRK 1
#define XPAR_MICROBLAZE_USE_BRANCH_TARGET_CACHE 0
#define XPAR_MICROBLAZE_BRANCH_TARGET_CACHE_SIZE 0
#define XPAR_MICROBLAZE_PC_WIDTH 32
#define XPAR_MICROBLAZE_HW_VER "8.50.b"

/******************************************************************/
