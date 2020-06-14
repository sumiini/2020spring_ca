/***************************************************************/
/*                                                             */
/*   MIPS-32 Instruction Level Simulator                       */
/*                                                             */
/*   SCE212 Ajou University                                    */
/*   run.c                                                     */
/*   Adapted from CS311@KAIST                                  */
/*                                                             */
/***************************************************************/

#include <stdio.h>

#include "util.h"
#include "run.h"

/***************************************************************/
/*                                                             */
/* Procedure: get_inst_info                                    */
/*                                                             */
/* Purpose: Read insturction information                       */
/*                                                             */
/***************************************************************/
instruction* get_inst_info(uint32_t pc)
{
    return &INST_INFO[(pc - MEM_TEXT_START) >> 2];
}

/***************************************************************/
/*                                                             */
/* Procedure: process_instruction                              */
/*                                                             */
/* Purpose: Process one instrction                             */
/*                                                             */
/***************************************************************/
void process_instruction()
{

	//R타입
	if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0) {

		//addu !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x21) {
			fprintf(stderr, "\n ADDU OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

			CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] + CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))];
			
		}

		//subu !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x23) {
			fprintf(stderr, "\n SUBU OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

			CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))]  = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] - CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))];
			
		}

		// and !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x24) {
			fprintf(stderr, "\n ANDOPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

			CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] & CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))];
			
		}

		//or !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x25) {
			fprintf(stderr, "\n OR OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

			CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] | CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))];
			
		}

		//nor !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x27) {
			fprintf(stderr, "\n NOR OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

			CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))]= ~(CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] | CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]);
			
		}

		//sll !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x00) {
			fprintf(stderr, "\n SLL OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

			CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))]= CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] << SHAMT(get_inst_info(CURRENT_STATE.PC));
			
		}

		//srl !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x02) {
			fprintf(stderr, "\n SRL OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

			CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] >> SHAMT(get_inst_info(CURRENT_STATE.PC));
			
		}

		//sltu !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x2b) {
			fprintf(stderr, "\n SLTU OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

			if (CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] < CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]) {
				CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = 1;
			}
			else {
				CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = 0;
			}
		}

		//jr !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x08) {
			fprintf(stderr, "\n JR OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

			CURRENT_STATE.PC = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))];
		}




	}
	// J 타입 I타입
	else {

		// J타입
		if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0b000010 || OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0b000011) {
			fprintf(stderr, "\n J-OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

			if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0b000010) {
				fprintf(stderr, "\n J OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

				JUMP_INST(TARGET(get_inst_info(CURRENT_STATE.PC)));
				//CURRENT_STATE.PC = TARGET(get_inst_info(CURRENT_STATE.PC));
			}
			// jal
			if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0b000011) {
				fprintf(stderr, "\n JAL OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

				CURRENT_STATE.REGS[31] = CURRENT_STATE.PC;
				JUMP_INST(TARGET(get_inst_info(CURRENT_STATE.PC)));
				//CURRENT_STATE.PC = TARGET(get_inst_info(CURRENT_STATE.PC));
			}
		}

		else {

			//addiu
			if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0x9) {
				fprintf(stderr, "\n ADDIU-OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

				CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] + IMM(get_inst_info(CURRENT_STATE.PC));
				
			}

			//andi
			if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0xc) {
				fprintf(stderr, "\n ANDI-OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

				CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] & SIGN_EX(IMM(get_inst_info(CURRENT_STATE.PC)));
				
			}

			//lui
			if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0xf) {
				fprintf(stderr, "\n LUI-OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

				CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = SIGN_EX(IMM(get_inst_info(CURRENT_STATE.PC)));
				
			}

			//ori
			if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0xd) {
				fprintf(stderr, "\n ORI-OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

				CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] | SIGN_EX(IMM(get_inst_info(CURRENT_STATE.PC)));
				
			}

			//sltiu
			if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0xb) {
				fprintf(stderr, "\n SLTIU-OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

				if (CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] < SIGN_EX(IMM(get_inst_info(CURRENT_STATE.PC)))) {
					CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = 1;
				}
				else {
					
					CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = 0;
				}
			}

			//lw 메모리에 있는것을 레지스터로
			if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0x23) {
				fprintf(stderr, "\n LW-OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

				CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = mem_read_32(CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] + SIGN_EX(IMM(get_inst_info(CURRENT_STATE.PC))));
			}

			//sw 레지스터에 있는것을 메모리로
			// M[R[rs]+SignExtImm] = R[rt]
			if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0x2b) {
				fprintf(stderr, "\n SW-OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));

				mem_write_32(CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] + SIGN_EX(IMM(get_inst_info(CURRENT_STATE.PC))), CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]);

			}
			//beq
			if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0x4) {
				fprintf(stderr, "\n BEQ-OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));
				BRANCH_INST(CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] == CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))], (IMM(get_inst_info(CURRENT_STATE.PC)) * 4) + CURRENT_STATE.PC,NULL);
}
				

			}
			//bne
			if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0x5) {
				fprintf(stderr, "\n BNE-OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));
				BRANCH_INST(CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] != CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))], (IMM(get_inst_info(CURRENT_STATE.PC)) * 4) + CURRENT_STATE.PC,NULL);

				
			}
		}
	

	CURRENT_STATE.PC += 4;
	

}
