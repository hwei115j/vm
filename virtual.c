#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "vm.h"

uint16_t dr_reg;    //資料暫存器 16bit
uint16_t ir_reg;    //指令暫存器 16bit
uint16_t ac_reg;    //累加器     16bit
uint16_t tr_reg;    //臨時暫存器 16bit
uint16_t pc_reg;    //程式計數器 12bit
uint16_t ar_reg;    //位置暫存器 12bit
uint8_t  inpr_reg;  //輸入暫存器  8bit
uint8_t  outr_reg;  //輸出暫存器  8bit  
bool     i_ff;      //I正反器1 間接 0直接
bool     s_ff;      //S正反器1 啟動 0關閉
bool     e_ff;      //E正反器1 進位 0沒進位
bool     r_ff;
bool     ien_ff;
bool     fgi_ff;
bool     fgo_ff;

enum Code
{
    AND, ADD, LDA, STA, BUN, BSA, ISZ,
    CLA = 0x7800,
    CLE = 0x7400,
    CMA = 0x7200, 
    CME = 0x7100, 
    CIR = 0x7080, 
    CIL = 0x7040, 
    INC = 0x7020, 
    SPA = 0x7010, 
    SNA = 0x7008, 
    SZA = 0x7004, 
    SZE = 0x7002, 
    HLT = 0x7001,
    INP = 0xF800, 
    OUT = 0xF400, 
    SKI = 0xF200, 
    SKO = 0xF100, 
    ION = 0xF080, 
    IOF = 0xF040, 
};

static int decode(uint16_t);

void virtual(uint16_t *memory)
{
    int reg = 0;
    enum Code code;

    dr_reg = ir_reg = ac_reg = pc_reg = ar_reg = 0;
    e_ff = r_ff = ien_ff = fgi_ff = fgo_ff = 0;
    s_ff = 1;

    while(s_ff)
    {
        if(r_ff)    //岔斷週期
        {
            ar_reg = 0;
            tr_reg = pc_reg;
            pc_reg = 0;
            memory[ar_reg] = tr_reg;
            pc_reg++;
            ien_ff = 0;
            r_ff = 0;
        }
        if(fgi_ff || fgo_ff) //檢查是否有中斷
            r_ff = 1;
        ar_reg = pc_reg++;
        ir_reg = memory[ar_reg];
        ar_reg = ir_reg & BK_HIGH4;
        if(i_ff = ir_reg & MSB)
            ar_reg = memory[ar_reg] & BK_HIGH4;
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
                ac_reg = (ac_reg >> 1) + MSB*e_ff;
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
                if((ac_reg & MSB)) pc_reg++;
				break;
			case SNA:
                if(!(ac_reg & MSB)) pc_reg++;
				break;
			case SZA:
                if(!ac_reg) pc_reg++;
				break;
			case SZE:
                if(!e_ff) pc_reg++;  
				break;
			case HLT:
                s_ff = 0;
				break;
			case INP:
                ac_reg = inpr_reg;
                fgi_ff = 0;
				break;
			case OUT:
                outr_reg = ac_reg & BK_HIGH8;
                fgo_ff = 0;
				break;
			case SKI:
                if(fgi_ff) pc_reg++;
				break;
			case SKO:
                if(fgo_ff) pc_reg++;
				break;
			case ION:
                ien_ff = 1;
				break;
			case IOF:
                ien_ff = 0;
				break;
        }
    }

    return ;
}

int decode(uint16_t ir_reg)
{
    if((ir_reg & BK_MSB) >> GET_HIGH4 != 7)
        return (ir_reg & BK_MSB) >> GET_HIGH4;
    return ir_reg;
}
