#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

const int BUS_NUMBER = 0;
const int I2C_ADDR = 0x52;
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

void poll(int file) {
        int32_t res, i, n;
        char buf[6];

        res = i2c_smbus_write_byte_data(file, 0xf0, 0x55u);
        if (res < 0 ) {perror("0xf055"); exit(-1);}
        res = i2c_smbus_write_word_data(file, 0xfb, 0x00u);
        if (res < 0 ) {perror("0xfb00"); exit(-1);}
        i = 0;
        while(1) {
                buf[i] = i2c_smbus_read_byte(file);
                if (++i % 6) continue;
                i = 0;
                printf("   jx:%-3d  jy:%-3d  ", buf[0], buf[1]);  // joystick x/y values
                printf("%c %c  ", buf[5]&1 ? '.' : 'Z', buf[5]&2 ? '.' : 'C');  // keys Z/C
                for(n=1; n<=3; n++) 
                        printf("a%c:%-4d ", 'w'+n, (buf[n+1]<<2)+((buf[5]>>(n+n))&3));         // acces
                printf("\n");
                i2c_smbus_write_byte(file, 0);
                //write(file, "", 1);
        }
}

int main(int argc, char** argv) {
        int file = setup();
        poll(file);
}
