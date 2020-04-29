/*
 * The Clear BSD License
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 * that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_flexspi_nor_flash.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(__CC_ARM) || defined(__GNUC__)
    __attribute__((section(".boot_hdr.conf")))
#elif defined(__ICCARM__)
#pragma location=".boot_hdr.conf"
#endif

#ifdef BOARD_OMVRT1
const flexspi_nor_config_t Qspiflash_config =
{
    .memConfig =
    {
        .tag = FLEXSPI_CFG_BLK_TAG,
        .version = FLEXSPI_CFG_BLK_VERSION,
        .readSampleClkSrc = kFlexSPIReadSampleClk_LoopbackFromDqsPad,//kFlexSPIReadSampleClk_LoopbackInternally,//
        .csHoldTime = 3u,
        .csSetupTime = 3u,
        .deviceType = kFlexSpiDeviceType_SerialNOR,
        .sflashPadType = kSerialFlash_4Pads,
        .serialClkFreq = kFlexSpiSerialClk_100MHz,
        .sflashA1Size = 4u * 1024u * 1024u,//4MBytes
        .dataValidTime = {16u, 16u},
        .lookupTable =
		    {
		      //Quad Input/output read sequence
		      [0]   = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0xEB, RADDR_SDR, FLEXSPI_4PAD, 0x18),
		      [1]   = FLEXSPI_LUT_SEQ(DUMMY_SDR, FLEXSPI_4PAD, 0x06, READ_SDR, FLEXSPI_4PAD, 0x04),
		      [2]   = FLEXSPI_LUT_SEQ(0, 0, 0, 0, 0, 0),
		    },
    },
    .pageSize = 256u,
    .sectorSize = 4u * 1024u,
}; 
#else
	#if defined(EVK1050_60_QSPI) || defined(EVK1060_QSPI) || defined(EVK1050_QSPI)
		const flexspi_nor_config_t qspiflash_config = {
			.memConfig =
				{
				  .tag = FLEXSPI_CFG_BLK_TAG,
				  .version = FLEXSPI_CFG_BLK_VERSION,
				  .readSampleClkSrc = kFlexSPIReadSampleClk_LoopbackFromDqsPad,
				  .csHoldTime = 3u,
				  .csSetupTime = 3u,
				  .columnAddressWidth = 0u,
				  .configCmdEnable = 0u,
				  .controllerMiscOption = 0u,
				  .deviceType = kFlexSpiDeviceType_SerialNOR,
				  .sflashPadType = kSerialFlash_4Pads,
				  .serialClkFreq = kFlexSpiSerialClk_133MHz,
				  .lutCustomSeqEnable = 0u,
				  .sflashA1Size = 0x00800000u, /* 8MB/64Mbit */
				  .lookupTable = 
					  {
						// Fast read sequence
						[0] = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0xEB, RADDR_SDR, FLEXSPI_4PAD, 0x18),
						[1] = FLEXSPI_LUT_SEQ(DUMMY_SDR, FLEXSPI_4PAD, 0x06, READ_SDR, FLEXSPI_4PAD, 0x02),
						[2] = FLEXSPI_LUT_SEQ(STOP, 0, 0, STOP, 0, 0),
						[3] = FLEXSPI_LUT_SEQ(STOP, 0, 0, STOP, 0, 0),
					  },
				},
		};
//		const flexspi_nor_config_t qspiflash_config = {
//			.memConfig =
//				{
//					.tag = FLEXSPI_CFG_BLK_TAG,
//					.version = FLEXSPI_CFG_BLK_VERSION,
//					.readSampleClkSrc = kFlexSPIReadSampleClk_LoopbackFromDqsPad,
//					.csHoldTime = 3u,
//					.csSetupTime = 3u,
//					// Enable DDR mode, Wordaddassable, Safe configuration, Differential clock
//					.sflashPadType = kSerialFlash_4Pads,
//					.serialClkFreq = kFlexSpiSerialClk_100MHz,
//					.sflashA1Size = 8u * 1024u * 1024u,
//					.lookupTable =
//						{
//							// Read LUTs
//							FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0xEB, RADDR_SDR, FLEXSPI_4PAD, 0x18),
//							FLEXSPI_LUT_SEQ(DUMMY_SDR, FLEXSPI_4PAD, 0x06, READ_SDR, FLEXSPI_4PAD, 0x04),
//						},
//				},
//			.pageSize = 256u,
//			.sectorSize = 4u * 1024u,
//			.blockSize = 256u * 1024u,
//			.isUniformBlockSize = false,
//		};
	#elif defined(EVK1064_QSPI)
		const flexspi_nor_config_t qspiflash_config = {
			.memConfig =
				{
				  .tag = FLEXSPI_CFG_BLK_TAG,
				  .version = FLEXSPI_CFG_BLK_VERSION,
				  .readSampleClkSrc = kFlexSPIReadSampleClk_LoopbackFromDqsPad,
				  .csHoldTime = 3u,
				  .csSetupTime = 3u,
				  .columnAddressWidth = 0u,
				  .configCmdEnable = 0u,
				  .controllerMiscOption = 0u,
				  .deviceType = kFlexSpiDeviceType_SerialNOR,
				  .sflashPadType = kSerialFlash_4Pads,
				  .serialClkFreq = kFlexSpiSerialClk_166MHz,
				  .lutCustomSeqEnable = 0u,
				  .sflashA1Size = 0x00800000u, /* 8MB/64Mbit */
				  .lookupTable = 
					  {
						// Fast read sequence
						[0] = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0xEB, RADDR_SDR, FLEXSPI_4PAD, 0x18),
						[1] = FLEXSPI_LUT_SEQ(DUMMY_SDR, FLEXSPI_4PAD, 0x06, READ_SDR, FLEXSPI_4PAD, 0x02),
						[2] = FLEXSPI_LUT_SEQ(STOP, 0, 0, STOP, 0, 0),
						[3] = FLEXSPI_LUT_SEQ(STOP, 0, 0, STOP, 0, 0),
					  },
				},
		};	
	#else
		const flexspi_nor_config_t hyperflash_config =
		{
			.memConfig =
			{
				.tag = FLEXSPI_CFG_BLK_TAG,
				.version = FLEXSPI_CFG_BLK_VERSION,
				.readSampleClkSrc = kFlexSPIReadSampleClk_ExternalInputFromDqsPad,
				.csHoldTime = 3u,
				.csSetupTime = 3u,
				.columnAddressWidth = 3u,
				// Enable DDR mode, Wordaddassable, Safe configuration, Differential clock
				.controllerMiscOption = (1u << kFlexSpiMiscOffset_DdrModeEnable) |
										(1u << kFlexSpiMiscOffset_WordAddressableEnable) |
										(1u << kFlexSpiMiscOffset_SafeConfigFreqEnable) |
										(1u << kFlexSpiMiscOffset_DiffClkEnable),
				.sflashPadType = kSerialFlash_8Pads,
				.serialClkFreq = kFlexSpiSerialClk_133MHz,
				.sflashA1Size = 64u * 1024u * 1024u,
				.dataValidTime = {16u, 16u},
				.lookupTable =
					{
						// Read LUTs
						FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0xA0, RADDR_DDR, FLEXSPI_8PAD, 0x18),
						FLEXSPI_LUT_SEQ(CADDR_DDR, FLEXSPI_8PAD, 0x10, DUMMY_DDR, FLEXSPI_8PAD, 0x06),
						FLEXSPI_LUT_SEQ(READ_DDR, FLEXSPI_8PAD, 0x04, STOP, FLEXSPI_1PAD, 0x0),
					},
			},
			.pageSize = 512u,
			.sectorSize = 256u * 1024u,
			.blockSize = 256u * 1024u,
			.isUniformBlockSize = true,
		};
	#endif
#endif
