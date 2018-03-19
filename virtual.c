#include <stdio.h>
#include "vm.h"

uint16_t dr_reg;    //資料暫存器 16bit
uint16_t ir_reg;    //指令暫存器 16bit
uint16_t ac_reg;    //累加器     16bit
uint16_t tr_reg;    //臨時暫存器 16bit
uint16_t pc_reg;    //程式計數器 12bit
uint16_t ar_reg;    //位置暫存器 12bit
uint8_t  inpr;      //輸入暫存器  8bit
uint8_t  outr;      //輸出暫存器  8bit  
bool     i_ff;      //I正反器1 間接 0直接
bool     e_ff;      //E正反器1 進位 0沒進位

int decode(uint16_t);

void virtual(uint16_t *memory)
{
    int reg = 0;
    dr_reg = ir_reg = ac_reg = pc_reg = ar_reg = i_ff = e_ff = 0;
    while(1)
    {
        ar_reg = pc_reg;
        pc_reg++;
        ir_reg = memory[ar_reg];
        ar_reg = ir_reg & BK_HIGH4;
        i_ff = ir_reg & MSB;
        if(i_ff)
            ar_reg = memory[ar_reg];
        switch(decode(ir_reg))
        {
            case AND:
				ac_reg &= memory[ar_reg];
                break;             
            case ADD:
                ac_reg += memory[ar_reg];
                break;                
            case LDA:
                ac_reg = memory[ar_reg];
                break;
            case STA:
                memory[ar_reg] = ac_reg;
                break;
            case BUN:
                pc_reg = ar_reg;
                break;
            case BSA:
                memory[ar_reg] = pc_reg;
                pc_reg = ar_reg + 1;
                break;
            case ISZ:
                dr_reg = memory[ar_reg];
                dr_reg++;
                memory[ar_reg] = dr_reg;
                if(!dr_reg)
                    pc_reg++;
                break;
            case CLA:
                ac_reg = 0;
				break;
			case CLE:
                e_ff = 0;
				break;
			case CMA:
                ac_reg = ~ac_reg;
				break;
			case CME:
                e_ff = !e_ff;
				break;
			case CIR:
                reg = ac_reg & LSB;
                ac_reg = ac_reg >> 1 + MSB*e_ff;
                e_ff = reg;
                break;
			case CIL:
                reg = ac_reg & MSB;
                ac_reg = ac_reg << 1 + e_ff;
                e_ff = reg;
				break;
			case INC:
                ac_reg++;
				break;
			case SPA:
                if(!(ac_reg & MSB))
                    pc_reg++;
				break;
			case SNA:
                if(ac_reg & MSB)
                    pc_reg++;
				break;
			case SZA:
                if(!ac_reg)
                    pc_reg++;
				break;
			case SZE:
                if(!e_ff)
                    pc_reg++;  
				break;
			case HLT:
                return;
				break;
			case INP:
				break;
			case OUT:
				break;
			case SKI:
				break;
			case SKO:
				break;
			case ION:
				break;
			case IOF:
				break;
        }
    }
}

int decode(uint16_t ir_reg)
{
	if((ir_reg&BK_MSB)>>GET_HIGH4 == 0)
		return 0;
	if((ir_reg&BK_MSB)>>GET_HIGH4 == 1)
		return 1;
	if((ir_reg&BK_MSB)>>GET_HIGH4 == 2)
		return 2;
	if((ir_reg&BK_MSB)>>GET_HIGH4 == 3)
		return 3;
	if((ir_reg&BK_MSB)>>GET_HIGH4 == 4)
		return 4;
	if((ir_reg&BK_MSB)>>GET_HIGH4 == 5)
		return 5;
	if((ir_reg&BK_MSB)>>GET_HIGH4 == 6)
		return 6;
	if(ir_reg == 0x7800)
		return 7;
	if(ir_reg == 0x7400)
		return 8;
	if(ir_reg == 0x7200)
		return 9;
	if(ir_reg == 0x7100)
		return 10;
	if(ir_reg == 0x7080)
		return 11;
	if(ir_reg == 0x7040)
		return 12;
	if(ir_reg == 0x7020)
		return 13;
	if(ir_reg == 0x7010)
		return 14;
	if(ir_reg == 0x7008)
		return 15;
	if(ir_reg == 0x7004)
		return 16;
	if(ir_reg == 0x7002)
		return 17;
	if(ir_reg == 0x7001)
		return 18;
	if(ir_reg == 0xF800)
		return 19;
	if(ir_reg == 0xF400)
		return 20;
	if(ir_reg == 0xF200)
		return 21;
	if(ir_reg == 0xF100)
		return 22;
	if(ir_reg == 0xF800)
		return 23;
	if(ir_reg == 0xF040)
		return 24;
}
