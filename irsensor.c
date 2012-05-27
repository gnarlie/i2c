#include <stdio.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

const int BUS_NUMBER = 0;
const int I2C_ADDR = 0x20;
int setup() {
        char filename[20];
        int file;
        snprintf(filename, sizeof(filename)-1, "/dev/i2c-%d", BUS_NUMBER);
        file = open(filename, O_RDWR);
        if (file < 0) {
                perror("open");
                exit(1);
        }

        if (ioctl(file, I2C_SLAVE, I2C_ADDR) < 0) {
                perror("I2C_SLAVE");
                exit(1);
        }

        return file;
}

const int CONFIGURATION_REGISTER = 3;
const int INPUT_PIN_MASK = 1;
const int OUTPUT_PIN_MASK = 3;
void poll(int file) {
        int32_t res, i, n;

        res = i2c_smbus_write_byte_data(file, CONFIGURATION_REGISTER, INPUT_PIN_MASK );
        if (res < 0 ) {perror("0x03fe"); exit(-1);}
        while(1) {
                uint8_t b = i2c_smbus_read_byte_data(file, 0);
		if (b & OUTPUT_PIN_MASK)
			printf("Far\n"); 
		else 
			printf("Close\n");
        }
}

int main(int argc, char** argv) {
        int file = setup();
        poll(file);
}
