#include <stdio.h>
#define CRC32C_POLY 0x82F63B78

typedef unsigned int u32;
typedef unsigned char u8;
u32 crc32c(const void *buf, u32 len)
{
    const u8 *cbuf = (const u8 *)buf;
    u32 crc = 0xFFFFFFFF;
    while (len--)
    {
        crc ^= *cbuf++;
        for (int i = 0; i < 8; i++)
            crc = crc & 1 ? (crc >> 1) ^ CRC32C_POLY : crc >> 1;
    }
    return ~crc;
}

int main() {
	FILE * fp = fopen("kernel.bin", "rb");
	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	printf("file size: %d\n", sz);
	char * buf = malloc(sz);
	fread(buf, 1, sz, fp);
	fclose(fp);
	u32 val = crc32c(buf, sz);
	printf("crc32c: %x \n", val);
	return 0;
}
