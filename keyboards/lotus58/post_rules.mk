ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += ../common/oled.c
endif

ifeq ($(strip $(BOOTMAGIC_ENABLE)), yes)
    SRC += ../common/bootmagic_lite.c
endif

ifeq ($(strip $(RGBLIGHT_MODE)), underglow)
    OPT_DEFS += -DRGBLIGHT_MODE_UNDERGLOW
endif
ifeq ($(strip $(RGBLIGHT_MODE)), backlight)
    OPT_DEFS += -DRGBLIGHT_MODE_BACKLIGHT
endif
ifeq ($(strip $(RGBLIGHT_MODE)), full)
    OPT_DEFS += -DRGBLIGHT_MODE_FULL
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
    VIAL_ENCODERS_ENABLE = yes
endif

ifeq ($(strip $(LOGO_ENABLE)), yes)
    OPT_DEFS += -DLOGO_ENABLE
endif
