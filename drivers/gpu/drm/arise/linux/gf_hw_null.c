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
#include "gf."
#include "gf_driver.h"
#include "os_interface.h"


/* for elite in ahb bus, only use it to check if current card is primary(0x01) */
int gf_get_command_status16(void *dev, unsigned short *command)
{
    *command = 0x01;
    return 0;
}

int gf_get_command_status32(void *dev, unsigned int *command)
{
    *command = 0x01;
    return 0;
}

/* useless for elite in ahb bus */
int gf_write_command_status16(void *dev, unsigned short command)
{
    return 0;
}

/* useless for elite in ahb bus */
int gf_write_command_status32(void *dev, unsigned int command)
{
    return 0;
}

/* useless for elite in ahb bus */
int gf_get_bar1(void *dev, unsigned int *bar1)
{
    *bar1 = 0x0;
    return 0;
}

/* useless for elite in ahb bus */
int gf_get_rom_save_addr(void *dev, unsigned int *romsave)
{
    *romsave = 0x0;
    return 0;
}

/* useless for elite in ahb bus */
int gf_write_rom_save_addr(void *dev, unsigned int romsave)
{
    return 0;
}

int gf_get_platform_config(void *dev, const char* config_name, int *buffer, int length)
{

    return 0;
}
void gf_get_bus_config(void *dev, bus_config_t *bus)
{
    bus->device_id         = 0x3D00;//E3K
    bus->vendor_id         = 0x1d17;
    bus->command           = 0x01;
    bus->status            = 0;
    bus->revision_id       = 0;
    bus->prog_if           = 0;
    bus->sub_class         = 0;
    bus->base_class        = 0;
    bus->cache_line_size   = 0;
    bus->latency_timer     = 0;
    bus->header_type       = 0;
    bus->bist              = 0;
    bus->sub_sys_vendor_id = 0;
    bus->sub_sys_id        = 0;
    bus->link_status       = 0;

    bus->mem_start_addr[0] = 10*1024*1024;
    bus->mem_end_addr[0]   = 266*1024*1024;

    bus->reg_start_addr[0] = 0;
    bus->reg_start_addr[1] = 0x700*1024*1024;
    bus->reg_start_addr[2] = 0;
    bus->reg_start_addr[3] = 0;
    bus->reg_start_addr[4] = 0;

    bus->reg_end_addr[0]   = 0;
    bus->reg_end_addr[1]   = 0x800*1024*1024ul;//total 256M local reserved in linux kernel
    bus->reg_end_addr[2]   = 0;
    bus->reg_end_addr[3]   = 0;
    bus->reg_end_addr[4]   = 0;
}

/* useless for elite in ahb bus */
unsigned long gf_get_rom_start_addr(void *dev)
{
    return 0;
}

/* useless for elite in ahb bus */
void gf_init_bus_id(gf_card_t *gf)
{
}

static gf_card_t *gf_dev = NULL;

int gf_register_driver(void)
{
    gf_card_t *gf = NULL;

    int result;

    gf = gf_calloc(sizeof(gf_card_t));
    if (!gf) {
        gf_error("register driver failed!\n");
    }
    gf_memset(gf, 0, sizeof(gf_card_t));

    gf_info("gf HW_NULL init driver\n");

    gf_fb_mode = "640x480-32@60";

    result = gf_card_init(gf, NULL);
    gf_dev = gf;
    return result;
}

void gf_unregister_driver(void)
{
    gf_card_t *gf = gf_dev;

    gf_card_deinit(gf);
    gf_free(gf);
    gf_dev = NULL;
}

int gf_register_interrupt(gf_card_t *gf, void *isr)
{
    gf_info("gf interrupt irq :NULL\n");

    return 0;
}

void gf_unregister_interrupt(gf_card_t *gf)
{
}
