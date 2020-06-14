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



	//RUN_BIT = TRUE;
	//R타입
	//////fprintf(stderr, "\n hi OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));
	//////fprintf(stderr, "\n ***********nice \n");
	//////fprintf(stderr, "\n\t  CURRENT_STATE.PC :: %d \t OPCODE %d \n", CURRENT_STATE.PC,OPCODE(get_inst_info(CURRENT_STATE.PC)));
	//CURRENT_STATE.PC += 4;

	

	if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0) {

		//addu !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x21) {
			CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] + CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))];
			//////fprintf(stderr, "\n addu _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);


		}

		//subu !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x23) {
			CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] - CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))];
			//////fprintf(stderr, "\n subu _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		}

		// and !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x24) {
			CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] & CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))];
			//////fprintf(stderr, "\n and _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);
		}

		//or !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x25) {
			CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] | CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))];
			//////fprintf(stderr, "\n or _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		}

		//nor !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x27) {
			CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = ~(CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] | CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]);
			//////fprintf(stderr, "\n nor _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		}

		//sll !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x00) {
			CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] << SHAMT(get_inst_info(CURRENT_STATE.PC));
			//////fprintf(stderr, "\n sll _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		}

		//srl !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x02) {
			CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] >> SHAMT(get_inst_info(CURRENT_STATE.PC));
			//////fprintf(stderr, "\n srl _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		}

		//sltu !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x2b) {
			if ((unsigned)CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] < (unsigned)CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]) {
				CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = 1;
			}
			else {
				CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] = 0;
			}
			//////fprintf(stderr, "\n sltu _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		}

		//jr !
		if (FUNC(get_inst_info(CURRENT_STATE.PC)) == 0x08) {
			//JUMP_INST(CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))]);
			//CURRENT_STATE.REGS[31] = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))];
			//////fprintf(stderr, "\n jr _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

			CURRENT_STATE.PC = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] ;
			return;
			//CURRENT_STATE.PC = CURRENT_STATE.PC-4;
			//////fprintf(stderr, "\n RS %d RD %d RT %d \n", RS(get_inst_info(CURRENT_STATE.PC)), RD(get_inst_info(CURRENT_STATE.PC)), RT(get_inst_info(CURRENT_STATE.PC)));
			////fprintf(stderr, "\n 31 register %d \n", CURRENT_STATE.REGS[31]);
			////fprintf(stderr, "\n jr _ target CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);
		}

		//fprintf(stderr, "\n RS %d RD %d RT %d Shamt %d \n", RS(get_inst_info(CURRENT_STATE.PC)), RD(get_inst_info(CURRENT_STATE.PC)), RT(get_inst_info(CURRENT_STATE.PC)), SHAMT(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n r _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		//fprintf(stderr, "\n CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))]);
		//fprintf(stderr, "\n CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]);
		//fprintf(stderr, "\n CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RD(get_inst_info(CURRENT_STATE.PC))]);

	}
	// J 타입 I타입


		// J타입

	if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0x2) {

		//////fprintf(stderr, "\n\nCURRENT_STATE.PC ::: %d , target ::: %d \n\n", CURRENT_STATE.PC, TARGET(get_inst_info(CURRENT_STATE.PC)));
		//CURRENT_STATE.PC -= 4;
		////fprintf(stderr, "\n j _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);
		TARGET(get_inst_info(CURRENT_STATE.PC));
		JUMP_INST(TARGET(get_inst_info(CURRENT_STATE.PC)));
		//CURRENT_STATE.PC = CURRENT_STATE.PC-4;
		//CURRENT_STATE.PC += 4;
		//fprintf(stderr, "\n\n TARGET %d \n\n", TARGET(get_inst_info(CURRENT_STATE.PC)));



	}
	// jal
	if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0x3) {
		//////fprintf(stderr, "\n JAL OPCODE : %d \n", OPCODE(get_inst_info(CURRENT_STATE.PC)));
		//////fprintf(stderr, "\n\n TARGET %d \n\n", TARGET(get_inst_info(CURRENT_STATE.PC)));
		//JUMP_INST(TARGET(get_inst_info(CURRENT_STATE.PC)));
		//TARGET(get_inst_info(CURRENT_STATE.PC));

		//fprintf(stderr, "\n jal _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		CURRENT_STATE.REGS[31] = (CURRENT_STATE.PC + 8);
		//fprintf(stderr, "\n CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);
		TARGET(get_inst_info(CURRENT_STATE.PC)) = TARGET(get_inst_info(CURRENT_STATE.PC));
		////fprintf(stderr, "\n TARGET %d \n", TARGET(get_inst_info(CURRENT_STATE.PC)));
		//if (TARGET(get_inst_info(CURRENT_STATE.PC)) == 4194300) {
		//	TARGET(get_inst_info(CURRENT_STATE.PC)) = TARGET(get_inst_info(CURRENT_STATE.PC)) + 4;
			//CURRENT_STATE.PC = CURRENT_STATE.PC + 4;
		//}
		//CURRENT_STATE.PC = CURRENT_STATE.PC;
		JUMP_INST(TARGET(get_inst_info(CURRENT_STATE.PC)));
		////fprintf(stderr, "\n byegggg \n");

		//fprintf(stderr, "\n target CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		//TARGET(get_inst_info(CURRENT_STATE.PC)) = TARGET(get_inst_info(CURRENT_STATE.PC)) + 4;

		////fprintf(stderr, "\n plzzzzzzzzzzz \n");
		//CURRENT_STATE.PC -= 4;
		//CURRENT_STATE.PC = CURRENT_STATE.PC;
		////fprintf(stderr, "\nTARGET %d \n", TARGET(get_inst_info(CURRENT_STATE.PC)));

		////fprintf(stderr, "\n target CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		return;

	}

	//addiu
	if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0x9) {
		CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] + SIGN_EX(IMM(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n imm %d \n", IMM(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n RS %d \n", RS(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n RT %d \n", RT(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n addiu _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		//fprintf(stderr, "\n CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))]);
		//fprintf(stderr, "\n CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]);

	}

	//andi
	if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0xc) {
		CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] & SIGN_EX(IMM(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n\n imm %d \n\n", IMM(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n\n RS %d \n\n", RS(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n\n RT %d \n\n", RT(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n andiu _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		//fprintf(stderr, "\n CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))]);
		//fprintf(stderr, "\n CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]);

	}

	//lui
	if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0xf) {
		int sift = IMM(get_inst_info(CURRENT_STATE.PC)) << 16;
		int fin = sift & 0b11111111111111110000000000000000;
		CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = fin & 0b11111111111111110000000000000000;
		//fprintf(stderr, "\n\n imm %d \n\n", IMM(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n\n RS %d \n\n", RS(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n\n RT %d \n\n", RT(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n lui _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		//fprintf(stderr, "\n CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))]);
		//fprintf(stderr, "\n CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]);

	}
	//ori
	if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0xd) {
		CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] | SIGN_EX(IMM(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n imm %d \n", IMM(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n RS %d \n", RS(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n RT %d \n", RT(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n ori _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		//fprintf(stderr, "\n CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))]);
		//fprintf(stderr, "\n CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]);

	}
	//sltiu
	if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0xb) {
		int temp = CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))];
		unsigned int un_temp = ((unsigned int)temp);
		if (temp < 0) {
			temp = (-1)*temp;
		}
		if (temp < (unsigned int)(SIGN_EX(IMM(get_inst_info(CURRENT_STATE.PC))))) {
			CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = 1;
		}
		else {

			CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = 0;
		}
		//fprintf(stderr, "\n TEMP %d \n", temp);
		//fprintf(stderr, "\n un_temp %d \n", un_temp);

		//fprintf(stderr, "\n RS %d \n", CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))]);
		//fprintf(stderr, "\n RT %d \n", CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]);

		//fprintf(stderr, "\n imm %d \n", IMM(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n RS %d \n", RS(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n RT %d \n", RT(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n sltiu _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

	}
	//lw 메모리에 있는것을 레지스터로
	//R[rt] = M[R[rs]+SignExtImm]
	if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0x23) {
		//CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = MEM_REGIONS[CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] + SIGN_EX(IMM(get_inst_info(CURRENT_STATE.PC)))];



		CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] = mem_read_32(CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] + SIGN_EX(IMM(get_inst_info(CURRENT_STATE.PC))));
		//fprintf(stderr, "\n imm %d \n", IMM(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n RS %d \n", RS(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n RT %d \n", RT(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n lw _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		//fprintf(stderr, "\n CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))]);
		//fprintf(stderr, "\n CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]);

	}

	//sw 레지스터에 있는것을 메모리로
	// M[R[rs]+SignExtImm] = R[rt]
	if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0x2b) {

		mem_write_32(CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] + SIGN_EX(IMM(get_inst_info(CURRENT_STATE.PC))), CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]);
		//fprintf(stderr, "\n imm %d \n", IMM(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n RS %d \n", RS(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n RT %d \n", RT(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n sw _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		//fprintf(stderr, "\n CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))]);
		//fprintf(stderr, "\n CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]);

	}
	//beq
	if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0x4) {
		BRANCH_INST(CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] == CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))], (IMM(get_inst_info(CURRENT_STATE.PC)) * 4) + CURRENT_STATE.PC, NULL);
		//fprintf(stderr, "\n imm %d \n", IMM(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n RS %d \n", RS(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n RT %d \n", RT(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n beq _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);

		//fprintf(stderr, "\n CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))]);
		//fprintf(stderr, "\n CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]);
		//if (CURRENT_STATE.PC == 4194316) {
		//	CURRENT_STATE.PC = 4194312;
		//}
	}
	//bne
	if (OPCODE(get_inst_info(CURRENT_STATE.PC)) == 0x5) {
		BRANCH_INST(CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] != CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))], (IMM(get_inst_info(CURRENT_STATE.PC)) * 4) + CURRENT_STATE.PC, NULL);
		//fprintf(stderr, "\n imm %d \n", IMM(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n RS %d \n", RS(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n RT %d \n", RT(get_inst_info(CURRENT_STATE.PC)));
		//fprintf(stderr, "\n bne _ CURRENT_STATE.PC %d \n", CURRENT_STATE.PC);
		//fprintf(stderr, "\n CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RS(get_inst_info(CURRENT_STATE.PC))]);
		//fprintf(stderr, "\n CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))] %d \n", CURRENT_STATE.REGS[RT(get_inst_info(CURRENT_STATE.PC))]);


	}

	
	//if (CURRENT_STATE.REGS[4] == 0xffffffe8) {
	//	CURRENT_STATE.REGS[4] = 0xffffffec;
	//}
	CURRENT_STATE.PC += 4;
	if (((CURRENT_STATE.PC - MEM_TEXT_START) / 4) >= NUM_INST) {
		
		RUN_BIT = FALSE;
	}
	

}