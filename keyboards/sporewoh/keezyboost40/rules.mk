PICO_INTRINSICS_ENABLED = no # ATM Unsupported by ChibiOS!

SRC += kicub.qgf.c
SRC += iosevka11.qff.c

QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS = st7789_spi
