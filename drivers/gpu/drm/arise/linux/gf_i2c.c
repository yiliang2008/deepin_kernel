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
#include "gf_disp.h"
#include "gf_cbios.h"
#include "os_interface.h"
#include "gf_i2c.h"
static int gf_i2c_xfer(struct i2c_adapter *i2c_adapter, struct i2c_msg *msgs, int num)
{
    struct gf_i2c_adapter *gf_adapter = i2c_get_adapdata(i2c_adapter);
    struct drm_device *dev = gf_adapter->dev;
    gf_connector_t *gf_connector = (gf_connector_t *)(gf_adapter->pgf_connector);
    gf_card_t *gf_card = dev->dev_private;
    disp_info_t *disp_info = (disp_info_t *)gf_card->disp_info;
    gf_i2c_param_t i2c_param;
    int i = 0, retval = 0;

    if (gf_connector->base_connector.status != connector_status_connected)
    {
        DRM_DEBUG_DRIVER("invalid i2c request as connector(0x%x) is not connected",
                         gf_connector->output_type);
        return -EIO;
    }

    for (i = 0; i < num; i++)
    {
        DRM_DEBUG_DRIVER("xfer: num: %d/%d, len:%d, flags:%#x\n\n", i + 1,
                      num, msgs[i].len, msgs[i].flags);
        gf_memset(&i2c_param, 0, sizeof(gf_i2c_param_t));
        i2c_param.use_dev_type = 1;
        i2c_param.device_id = gf_connector->output_type;
        i2c_param.slave_addr = ((msgs[i].addr)<<1);
        i2c_param.offset =  0;
        i2c_param.buf = msgs[i].buf;
        i2c_param.buf_len = msgs[i].len;
        i2c_param.request_type = GF_I2C_ERR_TYPE;
        if(i2c_param.slave_addr == 0x6E) //DDC operation
        {
            i2c_param.request_type = GF_I2C_DDCCI;
        }
        if (msgs[i].flags & I2C_M_RD)
            i2c_param.op = GF_I2C_READ;
        else
            i2c_param.op = GF_I2C_WRITE;

        //if i2c operation is write, but not used to adjust brightness, just skip it
        if ((i2c_param.op == GF_I2C_WRITE) && (i2c_param.request_type != GF_I2C_DDCCI))
        {
            continue;
        }

        gf_mutex_lock(gf_connector->conn_mutex);
        retval = disp_cbios_i2c_ctrl(disp_info, &i2c_param);
        gf_mutex_unlock(gf_connector->conn_mutex);
        if (retval < 0)
            return retval;
    }
    return num;
}

static u32 gf_i2c_func(struct i2c_adapter *adapter)
{
    return I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
}

static const struct i2c_algorithm gf_i2c_algo =
{
    .master_xfer = gf_i2c_xfer,
    .functionality = gf_i2c_func,
};

struct gf_i2c_adapter *gf_i2c_adapter_create(struct drm_device *dev, struct drm_connector *connector)
{
    struct i2c_adapter *adapter;
    struct gf_i2c_adapter *gf_adapter;
    gf_connector_t *gf_connector = to_gf_connector(connector);
    char *name = NULL;
    int ret = 0;

    switch (gf_connector->output_type)
    {
    case DISP_OUTPUT_CRT:
    {
        name = "CRT";
    }
    break;
    case DISP_OUTPUT_DP1:
    {
        name = "DP1";
    }
    break;
    case DISP_OUTPUT_DP2:
    {
        name = "DP2";
    }
    break;
    case DISP_OUTPUT_DP3:
    {
        name = "DP3";
    }
    break;
    case DISP_OUTPUT_DP4:
    {
        name = "DP4";
    }
    break;
    default:
    {
        DRM_DEBUG_KMS("skip create i2c adapter for output 0x%x\n", gf_connector->output_type);
        return NULL;
    }
    }

    gf_adapter = gf_calloc(sizeof(struct gf_i2c_adapter));
    if (!gf_adapter)
    {
        DRM_ERROR("failed to allo gf_adapter\n");
        return ERR_PTR(-ENOMEM);
    }

    adapter = &gf_adapter->adapter;
    adapter->owner = THIS_MODULE;
#if DRM_VERSION_CODE < KERNEL_VERSION(6,8,0)
    adapter->class = I2C_CLASS_DDC;
#endif
    adapter->dev.parent = dev->dev;
    gf_adapter->dev = dev;
    gf_adapter->pgf_connector = (void *)gf_connector;
    i2c_set_adapdata(adapter, gf_adapter);

    gf_vsnprintf(adapter->name, sizeof(adapter->name), "gf_i2c_%s", name);

    adapter->algo = &gf_i2c_algo;

    ret = i2c_add_adapter(adapter);
    if (ret)
    {
        DRM_ERROR("failed to register i2c adapter\n");

        gf_free(gf_adapter);
        gf_adapter = NULL;

        return ERR_PTR(ret);
    }

    gf_connector->i2c_adapter = gf_adapter;

    return gf_adapter;
}

void gf_i2c_adapter_destroy(struct gf_i2c_adapter *gf_adapter)
{
    if (!gf_adapter)
    {
        return;
    }

    i2c_del_adapter(&gf_adapter->adapter);

    gf_free(gf_adapter);
}
