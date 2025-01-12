#include <stdio.h>
#include <stdlib.h>

typedef enum {// tablodaki verinin enum olarak hafizaya alinmasi
    RANGE_2G = 0b00,
    RANGE_4G = 0b01,
    RANGE_8G = 0b10,
    RANGE_16G = 0b11
} AccelRange;

typedef enum {
    BW_7_81HZ = 0b00,
    BW_15_63HZ = 0b001,
    BW_31_25HZ = 0b010,
    BW_62_5HZ = 0b011,
    BW_125HZ = 0b100,
    BW_250HZ = 0b101,
    BW_500HZ = 0b110,
    BW_1000HZ = 0b111
} Bandwidth;

typedef enum {
    MODE_NORMAL = 0b000,
    MODE_SUSPEND = 0b001,
    MODE_LOW_POWER_1 = 0b010,
    MODE_STANDBY = 0b011,
    MODE_LOW_POWER_2 = 0b100,
    MODE_DEEP_SUSPEND = 0b101
} OperationMode;

typedef struct { //secili modlarin sakladigi struct yapisi
    AccelRange range;
    Bandwidth bandwidth;
    OperationMode mode;
    unsigned char AccConfigValue;
} SensorConfig;

unsigned char calculateAccConfigValue(SensorConfig config) { //AccConfigValue olusturan fonksiyon
    return (config.mode << 5) | (config.bandwidth << 2) | config.range;
}


void printConfigValue(unsigned char value) { // istenen formatlarda accconfigvalue yazdiran fonksiyon
    printf(" -Decimal: %d\n", value);
    printf(" -Hexadecimal: 0x%X\n", value);

    printf(" -Binary: 0b");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

int main() {
    SensorConfig config;//burada modlari hazir olarak sectim bu degerler kullanicidan da alinabilir, soruda tam ne isteniyor anlamadim.
    config.range = RANGE_8G;
    config.bandwidth = BW_31_25HZ;
    config.mode = MODE_NORMAL;

    config.AccConfigValue = calculateAccConfigValue(config);

    printf("Configuration Values:\n");
    printf("G Range: RANGE_8G\n");
    printf("Bandwidth: BW_31_25HZ\n");
    printf("Operation Mode: MODE_NORMAL\n");
    printf("AccConfigValue:\n");
    printConfigValue(config.AccConfigValue);

    return 0;
}
