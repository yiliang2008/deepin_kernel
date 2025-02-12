/*
 * Copyright © 2021 Glenfly Tech Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#ifndef _CBIOS_HW_INTERFACE_H_
#define _CBIOS_HW_INTERFACE_H_

#include "../CBiosChipFunc.h"

CBIOS_STATUS cbHWInit(PCBIOS_VOID pvcbe);
CBIOS_VOID   cbHWInitChipAttribute(PCBIOS_VOID pvcbe, CBIOS_U32 ChipID);
CBIOS_BOOL   cbHWIsChipEnable(PCBIOS_VOID pvcbe);
CBIOS_BOOL   cbHWIsChipPost(PCBIOS_VOID pvcbe);
CBIOS_STATUS cbHWSetChipPostFlag(PCBIOS_VOID pvcbe);
CBIOS_STATUS cbHWSetMmioEndianMode(PCBIOS_VOID pAdapterContext);
CBIOS_STATUS cbHWUnload(PCBIOS_VOID pvcbe);
CBIOS_STATUS cbHWSetIgaScreenOnOffState(PCBIOS_VOID pvcbe, CBIOS_BOOL status, CBIOS_U8 IGAIndex);
CBIOS_STATUS cbHWSetIgaOnOffState(PCBIOS_VOID pvcbe, CBIOS_BOOL status, CBIOS_U8 IGAIndex);
CBIOS_STATUS cbHWResetBlock(PCBIOS_VOID pvcbe, CBIOS_HW_BLOCK HWBlock);
CBIOS_STATUS cbHWDumpReg(PCBIOS_VOID pvcbe, PCBIOS_PARAM_DUMP_REG pCBParamDumpReg);
CBIOS_STATUS cbHWReadReg(PCBIOS_VOID pvcbe, CBIOS_U8 type, CBIOS_U8 index, PCBIOS_U8 result);
CBIOS_STATUS cbHWWriteReg(PCBIOS_VOID pvcbe, CBIOS_U8 type, CBIOS_U8 index, CBIOS_U8 value, CBIOS_U8 mask);
CBIOS_BOOL   cbHWReadEDID(PCBIOS_VOID pvcbe, CBIOS_U8 I2CBUSNum, CBIOS_U8 EDIDData[], CBIOS_U32 ulReadEdidOffset, CBIOS_U32 ulBufferSize, CBIOS_U8 nSegNum);
CBIOS_STATUS cbHWGetClockByType(PCBIOS_VOID pvcbe, PCBios_GetClock_Params PCBiosGetClockParams);
CBIOS_STATUS cbHWSetClockByType(PCBIOS_VOID pvcbe, PCBios_SetClock_Params PCBiosSetClockParams);
CBIOS_STATUS cbHWGetVBiosInfo(PCBIOS_VOID pvcbe, PCBIOS_VBINFO_PARAM pVbiosInfo);
CBIOS_STATUS  cbHwSyncDataWithVbios(PCBIOS_VOID  pvcbe, PCBIOS_VBIOS_DATA_PARAM  pDataPara);
CBIOS_STATUS cbHWI2CDataRead(PCBIOS_VOID pvcbe, PCBIOS_PARAM_I2C_DATA pCBParamI2CData);
CBIOS_STATUS cbHWI2CDataWrite(PCBIOS_VOID pvcbe, PCBIOS_PARAM_I2C_DATA pCBParamI2CData);
CBIOS_BOOL   cbHWDumpInfo(PCBIOS_VOID pvcbe, CBIOS_DUMP_TYPE RegType);
CBIOS_STATUS cbHWSetWriteback(PCBIOS_VOID pvcbe, PCBIOS_WB_PARA pWBPara);
CBIOS_VOID   cbHWSetPwm(PCBIOS_VOID pvcbe, CBIOS_U32 on, CBIOS_U32 def);
CBIOS_STATUS cbHWCECTransmitMessage(PCBIOS_VOID pvcbe, PCBIOS_CEC_MESSAGE pCECMessage, CBIOS_CEC_INDEX CECIndex);
CBIOS_STATUS cbHWCECReceiveMessage(PCBIOS_VOID pvcbe, PCBIOS_CEC_MESSAGE pCECMessage, CBIOS_CEC_INDEX CECIndex);
CBIOS_STATUS cbHwI2CDDCCIOpen(PCBIOS_VOID pvcbe, CBIOS_BOOL bOpen, PCBIOS_I2CCONTROL pI2CControl, CBIOS_U8 I2CBUSNum);
CBIOS_STATUS cbHwI2CDDCCIAccess(PCBIOS_VOID pvcbe, PCBIOS_I2CCONTROL pI2CControl, CBIOS_U8 I2CBUSNum);
CBIOS_VOID   cbHwUpdateActDeviceToReg(PCBIOS_VOID pvcbe, PCBIOS_DISPLAY_MANAGER pDispMgr);
CBIOS_U32    cbHwGetActDeviceFromReg(PCBIOS_VOID pvcbe);
CBIOS_VOID   cbHwSetModeToIGA(PCBIOS_VOID pvcbe, PCBIOS_DISP_MODE_PARAMS pModeParams);
CBIOS_STATUS cbHwGetCounter(PCBIOS_VOID  pvcbe, PCBIOS_GET_HW_COUNTER  pGetCounter);
CBIOS_STATUS cbHwGetMemInfo(PCBIOS_VOID pvcbe, PCBIOS_VBINFO_PARAM pVbiosInfo);

CBIOS_STATUS cbGetInterruptInfo(PCBIOS_VOID pvcbe, PCBIOS_INTERRUPT_INFO pIntInfo);
CBIOS_STATUS cbGetCECInterruptInfo(PCBIOS_VOID pvcbe, PCBIOS_CEC_INTERRUPT_INFO pCECIntInfo);
CBIOS_STATUS cbGetHDCPInterruptInfo(PCBIOS_VOID pvcbe, PCBIOS_HDCP_INFO_PARA pHdcpInfoParam);
CBIOS_STATUS cbGetHDACInterruptInfo(PCBIOS_VOID pvcbe, PCBIOS_HDAC_INFO_PARA pHdacInfoParam);

CBIOS_STATUS cbHWVIPCtl(PCBIOS_VOID pvcbe, PCBIOS_VIP_CTRL_DATA pCbiosVIPCtlData);

#endif
