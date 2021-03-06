/***************************************************************************
 *   Copyright (C) 2018 - 2019 by Chen Le <talpachen@gmail.com>            *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#ifndef __USRAPP_H__
#define __USRAPP_H__

#ifdef PROJ_CFG_BOOTLOADER_DFU_MODE
#	include "protocol/dfu/vsfusbd_dfu.h"
#else
#ifdef PROJ_CFG_CMSIS_DAP_V2_SUPPORT
#	include "protocol/cmsis_dap_v2/vsfusbd_cmsis_dap_v2.h"
#endif
#ifdef PROJ_CFG_WEBUSB_SUPPORT
#	include "protocol/webusb/vsfusbd_webusb.h"
#endif
#endif

struct usrapp_t
{
	struct usrapp_usbd_t
	{
		struct vsfusbd_device_t device;
		struct vsfusbd_config_t config[1];
		struct vsfusbd_iface_t ifaces[USBD_INTERFACE_COUNT];

#ifdef PROJ_CFG_BOOTLOADER_DFU_MODE
		struct vsfusbd_dfu_param_t dfu;
#else
#ifdef PROJ_CFG_CMSIS_DAP_V2_SUPPORT
		struct vsfusbd_cmsis_dap_v2_param_t cmsis_dap_v2;
#endif

#ifdef PROJ_CFG_WEBUSB_SUPPORT
		struct vsfusbd_webusb_param_t webusb;
#endif

#ifdef PROJ_CFG_CDCEXT_SUPPORT
		struct vsfusbd_CDCACM_param_t cdcacm_ext;		// -> usart ext
#endif

#ifdef PROJ_CFG_CDCSHELL_SUPPORT
		struct vsfusbd_CDCACM_param_t cdcacm_shell;		// -> shell
#endif
#endif
	} usbd;

#ifndef PROJ_CFG_BOOTLOADER_DFU_MODE
	struct dap_param_t dap_param;

#if PROJ_CFG_USART_EXT_ENABLE
	struct
	{
		struct usart_stream_info_t usart_stream;
		struct vsf_fifostream_t stream_tx;
		struct vsf_fifostream_t stream_rx;
		uint8_t txbuff[128 + 4];
		uint8_t rxbuff[128 + 4];
	} usart_ext;
#endif

#if PROJ_CFG_USART_TRST_SWO_ENABLE
	struct
	{
		struct usart_stream_info_t usart_stream;
		//struct vsf_fifostream_t stream_tx;
		struct vsf_fifostream_t stream_rx;
		//uint8_t txbuff[128 + 4];
		uint8_t rxbuff[SWO_BUFFER_SIZE + 4];
	} usart_trst_swo;
#endif
#endif	// PROJ_CFG_BOOTLOADER_DFU_MODE
};

extern struct usrapp_t usrapp;

void usrapp_reset(uint32_t delay_ms);

void usrapp_initial_init(struct usrapp_t *app);
bool usrapp_cansleep(struct usrapp_t *app);
void usrapp_srt_init(struct usrapp_t *app);
void usrapp_srt_poll(struct usrapp_t *app);
void usrapp_nrt_init(struct usrapp_t *app);
void usrapp_nrt_poll(struct usrapp_t *app);

#endif // __USRAPP_H__

