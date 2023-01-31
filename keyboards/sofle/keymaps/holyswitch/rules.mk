VIA_ENABLE = yes
VIAL_ENABLE = yes

OLED_ENABLE = yes
OLED_DRIVER = SSD1306

VIAL_ENCODERS_ENABLE = yes
VIAL_INSECURE = yes

EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = no

RGBLIGHT_ENABLE = yes
RGBLIGHT_MODE = underglow

SWAP_HANDS_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
BOOTMAGIC_ENABLE = no
COMMAND_ENABLE = no
CONSOLE_ENABLE = no
QMK_SETTINGS = no

LTO_ENABLE = yes

LOGO_ENABLE = yes

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += ../common/oled.c
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

ifeq ($(strip $(MASTER_RIGHT)), yes)
    OPT_DEFS += -DMASTER_RIGHT
endif

ifeq ($(strip $(LOGO_ENABLE)), yes)
    OPT_DEFS += -DLOGO_ENABLE
endif


