#include "bus.h"

#include <string.h>

void a26_bus_init(A26Bus *bus) {
    memset(bus, 0, sizeof *bus);
    a26_riot_init(&bus->riot);
    bus->cpu.bus = bus;
    bus->cpu.decimal_enabled = 1;
}

static void tick(A26Bus *bus) {
    a26_riot_tick(&bus->riot);
    if (bus->tia_tick) {
        bus->tia_tick(bus->tia);
        bus->tia_tick(bus->tia);
        bus->tia_tick(bus->tia);
    }
}

uint8_t cpu_read(Cpu *cpu, uint16_t address) {
    A26Bus *bus = cpu->bus;
    address &= 0x1FFF;
    while (bus->tia_ready && !bus->tia_ready(bus->tia)) {
        tick(bus);
        cpu->cycles++;
    }
    tick(bus);
    uint8_t value;
    if (address & 0x1000) value = a26_cart_read(&bus->cart, address);
    else if (address & 0x80) value = a26_riot_read(&bus->riot, address);
    else value = bus->tia_read ? bus->tia_read(bus->tia, address, cpu->open_bus) : cpu->open_bus;
    return cpu->open_bus = value;
}

void cpu_write(Cpu *cpu, uint16_t address, uint8_t value) {
    A26Bus *bus = cpu->bus;
    address &= 0x1FFF;
    tick(bus);
    cpu->open_bus = value;
    if (address & 0x1000) a26_cart_write(&bus->cart, address, value);
    else if (address & 0x80) a26_riot_write(&bus->riot, address, value);
    else {
        a26_cart_tia_write(&bus->cart, address, value);  /* 3F's bank register sits at $00-$3F */
        if (bus->tia_write) bus->tia_write(bus->tia, address, value);
    }
}
