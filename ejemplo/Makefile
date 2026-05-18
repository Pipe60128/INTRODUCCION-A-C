# ── CONFIGURACIÓN ─────────────────────────────────────
MCU        = atmega16
F_CPU      = 8000000UL
CC      = "C:/Program Files (x86)/Atmel/Studio/7.0/toolchain/avr8/avr8-gnu-toolchain/bin/avr-gcc.exe"
OBJCOPY = "C:/Program Files (x86)/Atmel/Studio/7.0/toolchain/avr8/avr8-gnu-toolchain/bin/avr-objcopy.exe"
AVRDUDE    = avrdude
PROGRAMMER = usbasp
TARGET     = main

# ── ARCHIVOS FUENTE ───────────────────────────────────
SRCS = main.c     

# Genera lista de .o automático desde los .c
OBJS = $(SRCS:.c=.o)

# ── FLAGS ─────────────────────────────────────────────
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall

# ── REGLAS PRINCIPALES ────────────────────────────────
all: $(TARGET).hex

# Compila cada .c → .o
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Linkea todos los .o → .elf
$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Convierte .elf → .hex
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# ── FLASH ─────────────────────────────────────────────
flash: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p m16 -B 20 -U flash:w:$(TARGET).hex:i

# ── FUSES ─────────────────────────────────────────────
fuses-read:
	$(AVRDUDE) -c $(PROGRAMMER) -p m16 \
	-U lfuse:r:-:h \
	-U hfuse:r:-:h \
	-U lock:r:-:h

# ── LIMPIEZA ──────────────────────────────────────────
clean:
	rm -f *.elf *.hex *.o