/* Copyright (c) 2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __ARCH_ARM_MACH_MSM_BOARD_MSM8960_H
#define __ARCH_ARM_MACH_MSM_BOARD_MSM8960_H

#include <linux/regulator/gpio-regulator.h>
#include <linux/mfd/pm8xxx/pm8921.h>
#include <linux/i2c.h>
#include <linux/i2c/sx150x.h>
#include <mach/irqs.h>
#include <mach/rpm-regulator.h>
#include <mach/msm_memtypes.h>

/* Macros assume PMIC GPIOs and MPPs start at 1 */
#define PM8921_GPIO_BASE		NR_GPIO_IRQS
#define PM8921_GPIO_PM_TO_SYS(pm_gpio)	(pm_gpio - 1 + PM8921_GPIO_BASE)
#define PM8921_MPP_BASE			(PM8921_GPIO_BASE + PM8921_NR_GPIOS)
#define PM8921_MPP_PM_TO_SYS(pm_gpio)	(pm_gpio - 1 + PM8921_MPP_BASE)
#define PM8921_IRQ_BASE			(NR_MSM_IRQS + NR_GPIO_IRQS)

extern struct pm8xxx_regulator_platform_data
	msm_pm8921_regulator_pdata[] __devinitdata;

extern int msm_pm8921_regulator_pdata_len __devinitdata;

#define GPIO_VREG_ID_EXT_5V		0
#define GPIO_VREG_ID_EXT_L2		1
#define GPIO_VREG_ID_EXT_3P3V		2
#define GPIO_VREG_ID_EXT_OTG_SW		3

extern struct gpio_regulator_platform_data
	msm_gpio_regulator_pdata[] __devinitdata;

extern struct regulator_init_data msm_saw_regulator_pdata_s5;
extern struct regulator_init_data msm_saw_regulator_pdata_s6;

extern struct rpm_regulator_platform_data msm_rpm_regulator_pdata __devinitdata;
#if defined(CONFIG_TOUCHSCREEN_MMS144) || \
	defined(CONFIG_TOUCHSCREEN_MMS136) || \
	defined(CONFIG_TOUCHSCREEN_MMS136_TABLET) || \
	defined(CONFIG_TOUCHSCREEN_MMS134S)
extern void __init mms_tsp_input_init(void);
#endif

#if defined(CONFIG_MACH_ESPRESSO_VZW) || defined(CONFIG_MACH_ESPRESSO_ATT) \
				|| defined(CONFIG_MACH_ESPRESSO10_SPR) \
				|| defined(CONFIG_MACH_ESPRESSO10_VZW) \
				|| defined(CONFIG_MACH_ESPRESSO10_ATT) \
				|| defined(CONFIG_MACH_KONA) \
				|| defined(CONFIG_MACH_ESPRESSO_SPR)
extern void __init usb_switch_init(void);
#endif

#if defined(CONFIG_MACH_JAGUAR) || defined(CONFIG_MACH_M2_VZW) || \
defined(CONFIG_MACH_M2_ATT) || defined(CONFIG_MACH_M2_SPR) || \
defined(CONFIG_MACH_M2_SKT) || defined(CONFIG_MACH_M2_DCM) || \
defined(CONFIG_MACH_M2_KDI)
extern void __init msm8960_cam_init(void);
#endif

#if defined(CONFIG_GPIO_SX150X) || defined(CONFIG_GPIO_SX150X_MODULE)
enum {
	GPIO_EXPANDER_IRQ_BASE = (PM8921_IRQ_BASE + PM8921_NR_IRQS),
	GPIO_EXPANDER_GPIO_BASE = (PM8921_MPP_BASE + PM8921_NR_MPPS),
	/* CAM Expander */
	GPIO_CAM_EXPANDER_BASE = GPIO_EXPANDER_GPIO_BASE,
	GPIO_CAM_GP_STROBE_READY = GPIO_CAM_EXPANDER_BASE,
	GPIO_CAM_GP_AFBUSY,
	GPIO_CAM_GP_STROBE_CE,
	GPIO_CAM_GP_CAM1MP_XCLR,
	GPIO_CAM_GP_CAMIF_RESET_N,
	GPIO_CAM_GP_XMT_FLASH_INT,
	GPIO_CAM_GP_LED_EN1,
	GPIO_CAM_GP_LED_EN2,
	GPIO_LIQUID_EXPANDER_BASE = GPIO_CAM_EXPANDER_BASE + 8,
};
#endif

enum {
	SX150X_CAM,
	SX150X_LIQUID,
};

#endif

#ifdef CONFIG_WACOM_W9001
void __init input_wacom_init(void);
#endif

extern int samsung_cmc624_on(int enable);
extern int samsung_has_cmc624(void);
extern int gpio_rev(unsigned int);
extern void msm_otg_set_cable_state(int);
extern void msm_otg_set_vbus_state(int);
extern void msm_otg_set_charging_state(bool enable);
extern void msm_otg_set_id_state(bool enable);
extern void msm_otg_set_smartdock_state(bool enable);
#ifdef CONFIG_CAMERON_HEALTH
extern bool is_cameron_health_connected;
extern void msm_otg_set_cameronhealth_state(bool enable);
#endif
extern struct sx150x_platform_data msm8960_sx150x_data[];
extern struct msm_camera_board_info msm8960_camera_board_info;
extern unsigned char hdmi_is_primary;

void msm8960_init_cam(void);
void msm8960_init_fb(void);
void msm8960_init_pmic(void);
void msm8960_init_mmc(void);
int msm8960_init_gpiomux(void);
unsigned char msm8960_hdmi_as_primary_selected(void);
void msm8960_allocate_fb_region(void);
void msm8960_set_display_params(char *prim_panel, char *ext_panel);
void msm8960_pm8921_gpio_mpp_init(void);
void msm8960_mdp_writeback(struct memtype_reserve *reserve_table);
int msm8960_get_cable_type(void);
void msm8960_init_battery(void);
int msm8960_get_cable_status(void);
extern int poweroff_charging;

#if defined(CONFIG_BCM4334) || defined(CONFIG_BCM4334_MODULE)
int brcm_wlan_init(void);
int brcm_wifi_status_register(
	void (*callback)(int card_present, void *dev_id), void *dev_id);
#endif
uint32_t msm_rpm_get_swfi_latency(void);
#define PLATFORM_IS_CHARM25() \
	(machine_is_msm8960_cdp() && \
		(socinfo_get_platform_subtype() == 1) \
	)
#define MSM_8960_GSBI8_QUP_I2C_BUS_ID 8
#define MSM_8960_GSBI4_QUP_I2C_BUS_ID 4
#define MSM_8960_GSBI3_QUP_I2C_BUS_ID 3
#define MSM_8960_GSBI10_QUP_I2C_BUS_ID 10
