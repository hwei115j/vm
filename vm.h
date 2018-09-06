#ifndef __VM_H__
#define __VM_H_

#define GET_HIGH4 12
#define BK_HIGH4  0x0FFF
#define BK_HIGH8  0x00FF
#define BK_MSB    0x7FFF
#define MSB       0x8000
#define LSB       0x0001

void virtual(uint16_t *);
#endif
