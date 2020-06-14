/***************************************************************/
/*                                                             */
/*   MIPS-32 Instruction Level Simulator                       */
/*                                                             */
/*   SCE212 Ajou University                                    */
/*   parse.c                                                   */
/*   Adapted from CS311@KAIST                                  */
/*                                                             */
/***************************************************************/

#include <stdio.h>

#include "util.h"
#include "parse.h"

int text_size;
int data_size;

//=malloc(sizeof(instruction))
//input파일에 있는 모든 명령어들을 instruction type으로 모두 변환시키는 곳
instruction parsing_instr(const char *buffer, const int index)
{
	
	instruction instr ;
	
	//index에 인스트럭션 한줄한줄의 주소
	unsigned int num = 0;
	for (int i = 0; buffer[i]; i++) {
		num = (num << 1) + buffer[i] - '0';
	}
	//num = fromBinary(buffer);
	
	//opcode잘라내기
	int hi_opcode = (num & 0b11111100000000000000000000000000) >> 26;
	instr.opcode = hi_opcode;
	//R타입
	if (hi_opcode == 0) {
		instr.r_t.r_i.rs = (num & 0b00000011111000000000000000000000) >> 21;
		
		instr.r_t.r_i.rt = (num & 0b00000000000111110000000000000000) >> 16;
		instr.r_t.r_i.r_i.r.rd= (num & 0b00000000000000001111100000000000) >> 11;
		instr.r_t.r_i.r_i.r.shamt = (num & 0b00000000000000000000011111000000) >> 6;
		instr.func_code= (num & 0b00000000000000000000000000111111) ;

	}
	//I 타입 ,S타입, J타입
	else {
		// J타입
		if (hi_opcode == 0b000010 || hi_opcode == 0b000011) {
			unsigned int address = 0;
			//address = ((num & 0b00000011111111111111111111111111) << 2);
			//address = ((CURRENT_STATE.PC & 0b11110000000000000000000000000000) | address);
			//instr.r_t.target = address;
			address = num;
			address = address << 6;
			address = address >> 4;
			//instr.r_t.target= ((num & 0b00000011111111111111111111111111) << 2);
			instr.r_t.target = address;
		
		}
		else {
			// I타입
			//addiu andi beq bne lui lw ori sltiu sw
			instr.r_t.r_i.rs = (num & 0b00000011111000000000000000000000) >> 21;
			instr.r_t.r_i.rt = (num & 0b00000000000111110000000000000000) >> 16;
			instr.r_t.r_i.r_i.imm = (num & 0b00000000000000001111111111111111);
		}
	}
	/** Implement this function */

	
    return instr;
}
//
void parsing_data(const char *buffer, const int index)
{
	/** Implement this function */
	//fromBinary함수 써라 . binary to integer
	//fromBinary(buffer);
	//mem_read_32 랑 mem_write_32써라
	//mem_read_32(index + );
	mem_write_32(MEM_DATA_START+index, fromBinary(buffer));
}

void print_parse_result()
{
    int i;
    printf("Instruction Information\n");

    for(i = 0; i < text_size/4; i++)
    {
        printf("INST_INFO[%d].value : %x\n",i, INST_INFO[i].value);
        printf("INST_INFO[%d].opcode : %d\n",i, INST_INFO[i].opcode);

	    switch(INST_INFO[i].opcode)
        {
            //Type I
            case 0x9:		//(0x001001)ADDIU
            case 0xc:		//(0x001100)ANDI
            case 0xf:		//(0x001111)LUI	
            case 0xd:		//(0x001101)ORI
            case 0xb:		//(0x001011)SLTIU
            case 0x23:		//(0x100011)LW
            case 0x2b:		//(0x101011)SW
            case 0x4:		//(0x000100)BEQ
            case 0x5:		//(0x000101)BNE
                printf("INST_INFO[%d].rs : %d\n",i, INST_INFO[i].r_t.r_i.rs);
                printf("INST_INFO[%d].rt : %d\n",i, INST_INFO[i].r_t.r_i.rt);
                printf("INST_INFO[%d].imm : %d\n",i, INST_INFO[i].r_t.r_i.r_i.imm);
                break;

            //TYPE R
            case 0x0:		//(0x000000)ADDU, AND, NOR, OR, SLTU, SLL, SRL, SUBU  if JR
                printf("INST_INFO[%d].func_code : %d\n",i, INST_INFO[i].func_code);
                printf("INST_INFO[%d].rs : %d\n",i, INST_INFO[i].r_t.r_i.rs);
                printf("INST_INFO[%d].rt : %d\n",i, INST_INFO[i].r_t.r_i.rt);
                printf("INST_INFO[%d].rd : %d\n",i, INST_INFO[i].r_t.r_i.r_i.r.rd);
                printf("INST_INFO[%d].shamt : %d\n",i, INST_INFO[i].r_t.r_i.r_i.r.shamt);
                break;

            //TYPE J
            case 0x2:		//(0x000010)J
            case 0x3:		//(0x000011)JAL
                printf("INST_INFO[%d].target : %d\n",i, INST_INFO[i].r_t.target);
                break;

            default:
                printf("Not available instruction\n");
                assert(0);
        }
    }

    printf("Memory Dump - Text Segment\n");
    for(i = 0; i < text_size; i+=4)
        printf("text_seg[%d] : %x\n", i, mem_read_32(MEM_TEXT_START + i));
    for(i = 0; i < data_size; i+=4)
        printf("data_seg[%d] : %x\n", i, mem_read_32(MEM_DATA_START + i));
    printf("Current PC: %x\n", CURRENT_STATE.PC);
}
