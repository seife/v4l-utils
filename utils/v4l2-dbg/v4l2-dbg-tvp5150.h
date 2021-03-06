/*
    Copyright (C) 2008 Mauro Carvalho Chehab <mchehab@kernel.org>
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation version 2 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335  USA
 */

#include "v4l2-dbg.h"

#define TVP5150_IDENT "tvp5150"

/* Register name prefix */
#define TVP5150_PREFIX "TVP5150_"

static struct board_regs tvp5150_regs[] = {
	{0x00, TVP5150_PREFIX "VD_IN_SRC_SEL_1", 1},
	{0x01, TVP5150_PREFIX "ANAL_CHL_CTL", 1},
	{0x02, TVP5150_PREFIX "OP_MODE_CTL", 1},
	{0x03, TVP5150_PREFIX "MISC_CTL", 1},
	{0x04, TVP5150_PREFIX "AUTOSW_MSK", 1},
	{0x06, TVP5150_PREFIX "COLOR_KIL_THSH_CTL", 1},
	{0x07, TVP5150_PREFIX "LUMA_PROC_CTL_1", 1},
	{0x08, TVP5150_PREFIX "LUMA_PROC_CTL_2", 1},
	{0x09, TVP5150_PREFIX "BRIGHT_CTL", 1},
	{0x0a, TVP5150_PREFIX "SATURATION_CTL", 1},
	{0x0b, TVP5150_PREFIX "HUE_CTL", 1},
	{0x0c, TVP5150_PREFIX "CONTRAST_CTL", 1},
	{0x0d, TVP5150_PREFIX "DATA_RATE_SEL", 1},
	{0x0e, TVP5150_PREFIX "LUMA_PROC_CTL_3", 1},
	{0x0f, TVP5150_PREFIX "CONF_SHARED_PIN", 1},
	{0x11, TVP5150_PREFIX "ACT_VD_CROP_ST_MSB", 1},
	{0x12, TVP5150_PREFIX "ACT_VD_CROP_ST_LSB", 1},
	{0x13, TVP5150_PREFIX "ACT_VD_CROP_STP_MSB", 1},
	{0x14, TVP5150_PREFIX "ACT_VD_CROP_STP_LSB", 1},
	{0x15, TVP5150_PREFIX "GENLOCK", 1},
	{0x16, TVP5150_PREFIX "HORIZ_SYNC_START", 1},
	{0x18, TVP5150_PREFIX "VERT_BLANKING_START", 1},
	{0x19, TVP5150_PREFIX "VERT_BLANKING_STOP", 1},
	{0x1a, TVP5150_PREFIX "CHROMA_PROC_CTL_1", 1},
	{0x1b, TVP5150_PREFIX "CHROMA_PROC_CTL_2", 1},
	{0x1c, TVP5150_PREFIX "INT_RESET_REG_B", 1},
	{0x1d, TVP5150_PREFIX "INT_ENABLE_REG_B", 1},
	{0x1e, TVP5150_PREFIX "INTT_CONFIG_REG_B", 1},
	{0x28, TVP5150_PREFIX "VIDEO_STD", 1},
	{0x2c, TVP5150_PREFIX "CB_GAIN_FACT", 1},
	{0x2d, TVP5150_PREFIX "CR_GAIN_FACTOR", 1},
	{0x2e, TVP5150_PREFIX "MACROVISION_ON_CTR", 1},
	{0x2f, TVP5150_PREFIX "MACROVISION_OFF_CTR", 1},
	{0x30, TVP5150_PREFIX "REV_SELECT", 1},
	{0x80, TVP5150_PREFIX "MSB_DEV_ID", 1},
	{0x81, TVP5150_PREFIX "LSB_DEV_ID", 1},
	{0x82, TVP5150_PREFIX "ROM_MAJOR_VER", 1},
	{0x83, TVP5150_PREFIX "ROM_MINOR_VER", 1},
	{0x84, TVP5150_PREFIX "VERT_LN_COUNT_MSB", 1},
	{0x85, TVP5150_PREFIX "VERT_LN_COUNT_LSB", 1},
	{0x86, TVP5150_PREFIX "INT_STATUS_REG_B", 1},
	{0x87, TVP5150_PREFIX "INT_ACTIVE_REG_B", 1},
	{0x88, TVP5150_PREFIX "STATUS_REG_1", 1},
	{0x89, TVP5150_PREFIX "STATUS_REG_2", 1},
	{0x8a, TVP5150_PREFIX "STATUS_REG_3", 1},
	{0x8b, TVP5150_PREFIX "STATUS_REG_4", 1},
	{0x8c, TVP5150_PREFIX "STATUS_REG_5", 1},
	{0x90, TVP5150_PREFIX "CC_DATA", 4},
	{0x94, TVP5150_PREFIX "WSS_DATA", 6},
	{0x9a, TVP5150_PREFIX "VPS_DATA", 13},
	{0xa7, TVP5150_PREFIX "VITC_DATA", 9},
	{0xb0, TVP5150_PREFIX "VBI_FIFO_READ_DATA", 1},
	{0xb1, TVP5150_PREFIX "TELETEXT_FIL1", 5},
	{0xb6, TVP5150_PREFIX "TELETEXT_FIL2", 5},
	{0xbb, TVP5150_PREFIX "TELETEXT_FIL_ENA", 1},
	{0xc0, TVP5150_PREFIX "INT_STATUS_REG_A", 1},
	{0xc1, TVP5150_PREFIX "INT_ENABLE_REG_A", 1},
	{0xc2, TVP5150_PREFIX "INT_CONF", 1},
	{0xc3, TVP5150_PREFIX "VDP_CONF_RAM_DATA", 1},
	{0xc4, TVP5150_PREFIX "CONF_RAM_ADDR_LOW", 1},
	{0xc5, TVP5150_PREFIX "CONF_RAM_ADDR_HIGH", 1},
	{0xc6, TVP5150_PREFIX "VDP_STATUS_REG", 1},
	{0xc7, TVP5150_PREFIX "FIFO_WORD_COUNT", 1},
	{0xc8, TVP5150_PREFIX "FIFO_INT_THRESHOLD", 1},
	{0xc9, TVP5150_PREFIX "FIFO_RESET", 1},
	{0xca, TVP5150_PREFIX "LINE_NUMBER_INT", 1},
	{0xcb, TVP5150_PREFIX "PIX_ALIGN_REG_LOW", 1},
	{0xcc, TVP5150_PREFIX "PIX_ALIGN_REG_HIGH", 1},
	{0xcd, TVP5150_PREFIX "FIFO_OUT_CTRL", 1},
	{0xcf, TVP5150_PREFIX "FULL_FIELD_ENA", 1},
	{0xd0, TVP5150_PREFIX "LINE_MODE", 43},
	{0xfc, TVP5150_PREFIX "FULL_FIELD_MODE_REG", 1},
};
