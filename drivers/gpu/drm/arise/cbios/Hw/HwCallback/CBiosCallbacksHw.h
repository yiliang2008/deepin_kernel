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

#ifndef _CBIOS_CALLBACKS_HW_H_
#define _CBIOS_CALLBACKS_HW_H_

#include "../../Device/CBiosShare.h"


typedef enum _CBIOS_GPIO_TYPE
{
    CBIOS_GPIO_GFX  = 0X00,
    CBIOS_GPIO_VSOC = 0x01,
    CBIOS_GPIO_VSUS = 0x02,
    CBIOS_GPIO_AUD  = 0x04,
    CBIOS_GPIO_ISP  = 0x08,
}CBIOS_GPIO_TYPE;

/******Call Back function *********/

//******** general VGA reg access functions ********************
//use MMIO to access VGA registers under NT platforms
//RegisterPort: register port address offset, based on MMIO Base address.
typedef CBIOS_UCHAR   (*CALLBACK_cbReadU8)(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort);
typedef CBIOS_U16     (*CALLBACK_cbReadU16)(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort);
typedef CBIOS_U32     (*CALLBACK_cbReadU32)(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort);
typedef CBIOS_VOID    (*CALLBACK_cbWriteU8)(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort, CBIOS_UCHAR Value);
typedef CBIOS_VOID    (*CALLBACK_cbWriteU16)(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort, CBIOS_U16 Value);
typedef CBIOS_VOID    (*CALLBACK_cbWriteU32)(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort, CBIOS_U32 Value);
//////////////////////////////////////////////////////////////////////////////
//use MMIO to access VGA registers under NT platforms
//IN RegisterPort: register port address
typedef CBIOS_U32     (*CALLBACK_cbReadBufferU32)(PCBIOS_U32 RegisterPort);
typedef CBIOS_VOID    (*CALLBACK_cbWriteBufferU32)(PCBIOS_U32 RegisterPort, CBIOS_U32 Value);

/*use IO to access VGA registers under NT platforms*/
typedef CBIOS_UCHAR   (*CALLBACK_cbReadPortUchar)(PCBIOS_UCHAR RegisterPort);
typedef CBIOS_VOID    (*CALLBACK_cbWritePortUchar)(PCBIOS_UCHAR RegisterPort, CBIOS_UCHAR Value);

typedef CBIOS_VOID    (*CALLBACK_cbWriteRegisterU32)(PCBIOS_VOID  pAdapterContext, CBIOS_REGISTER_BLOCK_TYPE RegType, CBIOS_U32 RegIndex, CBIOS_U32 Value);
typedef CBIOS_U32     (*CALLBACK_cbReadRegisterU32)(PCBIOS_VOID  pAdapterContext, CBIOS_REGISTER_BLOCK_TYPE RegType, CBIOS_U32 RegIndex);
typedef CBIOS_VOID    (*CALLBACK_cbDbgPrintToFile)(CBIOS_U32 DebugPrintLevel, PCBIOS_CHAR DebugMessage, PCBIOS_VOID pBuffer, CBIOS_U32 Size);
//gpio
typedef CBIOS_U32     (*CALLBACK_cbGetSysGPIO)(CBIOS_U32 gpio, CBIOS_U32 GpioType);
typedef CBIOS_VOID    (*CALLBACK_cbSetSysGPIO)(CBIOS_U32 gpio, CBIOS_U32 GpioType,CBIOS_S32 value);
typedef CBIOS_U32     (*CALLBACK_cbRequestSysGPIO)(CBIOS_U32 gpio, CBIOS_U32 GpioType);
typedef CBIOS_VOID    (*CALLBACK_cbFreeSysGPIO)(CBIOS_U32 gpio, CBIOS_U32 GpioType);
typedef CBIOS_U32     (*CALLBACK_cbSysGPIODirectionInput)(CBIOS_U32 gpio, CBIOS_U32 GpioType);
typedef CBIOS_U32     (*CALLBACK_cbSysGPIODirectionOutput)(CBIOS_U32 gpio, CBIOS_U32 GpioType,CBIOS_S32 value);

typedef CBIOS_BOOL    (*CALLBACK_cbGetPlatformConfigU32)(PCBIOS_VOID pAdapterContext, const CBIOS_U8 *pName, CBIOS_U32* pBuffer, CBIOS_U32 Length);
//regulator
typedef PCBIOS_VOID   (*CALLBACK_cbRegulatorGet)(PCBIOS_VOID pAdapterContext, PCBIOS_CHAR id);
typedef CBIOS_S32     (*CALLBACK_cbRegulatorEnable)(PCBIOS_VOID Regulator);
typedef CBIOS_S32     (*CALLBACK_cbRegulatorDisable)(PCBIOS_VOID Regulator);
typedef CBIOS_S32     (*CALLBACK_cbRegulatorIsEnabled)(PCBIOS_VOID Regulator);
typedef CBIOS_S32     (*CALLBACK_cbRegulatorGetVoltage)(PCBIOS_VOID Regulator);
typedef CBIOS_S32     (*CALLBACK_cbRegulatorSetVoltage)(PCBIOS_VOID Regulator, CBIOS_S32 min_uV,CBIOS_S32 max_uV);
typedef CBIOS_VOID    (*CALLBACK_cbRegulatorPut)(PCBIOS_VOID Regulator);


CBIOS_UCHAR cb_ReadU8(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort);
CBIOS_U16 cb_ReadU16(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort);
CBIOS_U32 cb_ReadU32(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort);

CBIOS_VOID cb_WriteU8(PCBIOS_VOID pAdapterContext, CBIOS_U32 RegisterPort, CBIOS_UCHAR Value);
CBIOS_VOID cb_WriteU16(PCBIOS_VOID pAdapterContext, CBIOS_U32 RegisterPort, CBIOS_U16 Value);
CBIOS_VOID cb_WriteU32(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort, CBIOS_U32 Value);

/*use IO to access VGA registers under NT platforms*/
CBIOS_UCHAR cb_ReadPortUchar(PCBIOS_UCHAR RegisterPort);
CBIOS_VOID cb_WritePortUchar(PCBIOS_UCHAR RegisterPort, CBIOS_UCHAR Value);

CBIOS_VOID cbWriteRegisterU32(PCBIOS_VOID pvcbe, CBIOS_REGISTER_BLOCK_TYPE RegType, CBIOS_U32 RegIndex, CBIOS_U32 Value );
CBIOS_VOID cbWriteRegisterU32WithMask(PCBIOS_VOID pvcbe, CBIOS_REGISTER_BLOCK_TYPE RegType, CBIOS_U32 RegIndex, CBIOS_U32 Value, CBIOS_U32 Mask);
CBIOS_U32 cbReadRegisterU32(PCBIOS_VOID pvcbe, CBIOS_REGISTER_BLOCK_TYPE RegType, CBIOS_U32 RegIndex);

//gpio
CBIOS_STATUS cbRequestGPIO(PCBIOS_VOID pvcbe, CBIOS_GPIO_TYPE GPIOType, CBIOS_U32 GPIOIndex);
CBIOS_VOID cbFreeGPIO(PCBIOS_VOID pvcbe, CBIOS_GPIO_TYPE GPIOType, CBIOS_U32 GPIOIndex);
CBIOS_STATUS cbSetGPIODirectionOutput(PCBIOS_VOID pvcbe, CBIOS_GPIO_TYPE GPIOType, CBIOS_U32 GPIOIndex, CBIOS_U32 Value);
CBIOS_STATUS cbSetGPIODirectionInput(PCBIOS_VOID pvcbe, CBIOS_GPIO_TYPE GPIOType, CBIOS_U32 GPIOIndex);
CBIOS_U32 cbReadGPIO(PCBIOS_VOID pvcbe, CBIOS_GPIO_TYPE GPIOType, CBIOS_U32 GPIOIndex);
CBIOS_VOID cbWriteGPIO(PCBIOS_VOID pvcbe, CBIOS_GPIO_TYPE GPIOType, CBIOS_U32 GPIOIndex, CBIOS_U32 Value);

//regulator
PCBIOS_VOID cbRegulatorGet(PCBIOS_VOID pvcbe, PCBIOS_CHAR id);
CBIOS_STATUS   cbRegulatorEnable(PCBIOS_VOID Regulator);
CBIOS_STATUS   cbRegulatorDisable(PCBIOS_VOID Regulator);
CBIOS_S32   cbRegulatorIsEnabled(PCBIOS_VOID Regulator);
CBIOS_S32   cbRegulatorGetVoltage(PCBIOS_VOID Regulator);
CBIOS_STATUS   cbRegulatorSetVoltage(PCBIOS_VOID Regulator, CBIOS_S32 min_uV,CBIOS_S32 max_uV);
CBIOS_VOID  cbRegulatorPut(PCBIOS_VOID Regulator);

#endif
