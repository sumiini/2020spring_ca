
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/******************************************************
 * Structure Declaration
 *******************************************************/

struct Inst {
	char *name;
	char *op;
	char type;
	char *funct;
};

struct Data {
	int value;
	struct Data *next;
};

struct Text {
	int idx, hi_address, immediate;
	char *d;
	char *s;
	char *t;
	char *real_imm;
	char *shamt;
	unsigned int address;
	struct Text *next;
};

struct Sym {
	char *name;
	int size;
	unsigned int address;
	struct Data *first;
	struct Sym *next;
	struct Data *last;
};


/******************************************************
 * Global Variable Declaration
 *******************************************************/

struct Inst inst[20] = {
	{"addiu",   "001001", 'I', ""},
	{"addu",    "000000", 'R', "100001"},
	{"and",     "000000", 'R', "100100"},
	{"andi",    "001100", 'I', ""},
	{"beq",     "000100", 'I', ""},
	{"bne",     "000101", 'I', ""},
	{"j",       "000010", 'J', ""},
	{"jal",     "000011", 'J', ""},
	{"jr",      "000000", 'R', "001000"},
	{"lui",     "001111", 'I', ""},
	{"lw",      "100011", 'I', ""},
	{"nor",     "000000", 'R', "100111"},
	{"or",      "000000", 'R', "100101"},
	{"ori",     "001101", 'I', ""},
	{"sltiu",   "001011", 'I', ""},
	{"sltu",    "000000", 'R', "101011"},
	{"sll",     "000000", 'S', "000000"},
	{"srl",     "000000", 'S', "000010"},
	{"sw",      "101011", 'I', ""},
	{"subu",    "000000", 'R', "100011"}
};
struct Sym *Symbols;
struct Text *Texts;
int datasize, textsize;


/******************************************************
 * Function Declaration
 *******************************************************/

 /* You may need the following functions */
char* change_file_ext(char *str);
char* num_to_bits(unsigned int num, int len);

/* You may fill the following functions */
void read_asm();
void subst_asm_to_num();
void print_bits();


/******************************************************
 * Function: main
 *
 * Parameters:
 *  int
 *      argc: the number of argument
 *  char*
 *      argv[]: array of a sting argument
 *
 * Return:
 *  return success exit value
 *
 * Info:
 *  The typical main function in C language.
 *  It reads system arguments from terminal (or commands)
 *  and parse an assembly file(*.s).
 *  Then, it converts a certain instruction into
 *  object code which is basically binary code.
 *
 *******************************************************/
int main(int argc, char* argv[]) {

	FILE *input, *output;
	char *filename;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <*.s>\n", argv[0]);
		fprintf(stderr, "Example: %s sample_input/example?.s\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// reading the input file
	input = freopen(argv[1], "r", stdin);
	if (input == NULL) {
		perror("ERROR");
		exit(EXIT_FAILURE);
	}

	// creating the output file (*.o)
	filename = strdup(argv[1]); // strdup() is not a standard C library but fairy used a lot.
	if (change_file_ext(filename) == NULL) {
		fprintf(stderr, "'%s' file is not an assembly file.\n", filename);
		exit(EXIT_FAILURE);
	}

	output = freopen(filename, "w", stdout);
	if (output == NULL) {
		perror("ERROR");
		exit(EXIT_FAILURE);
	}

	Symbols = (struct Sym *)malloc(sizeof(struct Sym));
	Texts = (struct Text *)malloc(sizeof(struct Text));

	/******************************************************
	 *  Let's complete the below functions!
	 *
	 *  read_asm(): Read the assmebly code.
	 *  subst_asm_to_num(): Convert the assembly code to num.
	 *  print_bits(): Print the results of assemble.
	 *
	 *******************************************************/
	read_asm();
	subst_asm_to_num();
	print_bits();

	// freeing the memory
	free(filename);
	free(Symbols);
	free(Texts);

	fclose(input);
	fclose(output);
	exit(EXIT_SUCCESS);
}

/******************************************************
 * Function: change_file_ext
 *
 * Parameters:
 *  char
 *      *str: a raw filename (without path)
 *
 * Return:
 *  return NULL if a file is not an assembly file.
 *  return empty string
 *
 * Info:
 *  This function reads filename and converts it into
 *  object extention name, *.o
 *
 *******************************************************/
char* change_file_ext(char *str) {
	char *dot = strrchr(str, '.');

	if (!dot || dot == str || (strcmp(dot, ".s") != 0))
		return NULL;

	str[strlen(str) - 1] = 'o';
	return "";
}

/******************************************************
 * Function: num_to_bits
 *
 * Parameters:
 *  unsigned int
 *      num: a decimal number to be converted to binary bits
 *  int
 *      len: a length of bits
 *
 * Return:
 *  return string of binary bits
 *
 * Info:
 *  This function reads an integer number and converts it into
 *  binary bits represented by string.
 *
 *******************************************************/
 /*
 char* num_to_bits(unsigned int num, int len) {
	 char* bits = (char *)malloc(len + 1);
	 int idx = len - 1, i;

	 while (num > 0 && idx >= 0) {
		 if (num % 2 == 1) {
			 bits[idx--] = '1';
		 }
		 else {
			 bits[idx--] = '0';
		 }
		 num /= 2;
	 }

	 for (i = idx; i >= 0; i--) {
		 bits[i] = '0';
	 }

	 return bits;
 }
 */

char* num_to_bits(unsigned int num, int len) {
	char* bits = (char *)malloc(len + 1);
	int idx = len - 1, i;


	
	
		while (num > 0 && idx >= 0) {
			if (num % 2 == 1) {
				bits[idx--] = '1';
			}
			else {
				bits[idx--] = '0';
			}
			num /= 2;
		}

		for (i = idx; i >= 0; i--) {
			bits[i] = '0';
		}
		return bits;
	
}
int hex_to_dec(char hexadecimal[]) {
	int decimal = 0;
	int position = 1;

	for (int i = strlen(hexadecimal) - 1; i >= 0; i--)  // 문자열을 역순으로 반복
	{
		char ch = hexadecimal[i];                  // 각 자릿수에 해당하는 문자

		if (ch >= 48 && ch <= 57)                  // 문자가 0~9 이면 
		{
			decimal += (ch - 48) * position;
			position = position * 16;      // 문자 0을 빼고 16 제곱
		}
		else if (ch >= 65 && ch <= 70)               // 문자가 때문자 A ~ F 이면 
		{
			decimal += (ch - (65 - 10)) * position;
			position = position * 16; // 문자 10 빼고 16제곱
		}
		else if (ch >= 97 && ch <= 102)               // 문자가 소문자 a~f 이면
		{
			decimal += (ch - (97 - 10)) * position;
			position = position * 16; // 문자 10 빼고  16제곱
		}

	}
	return decimal;
}
char *minus_to_bits(int num, int len) {
	int i = 0;
	int bin[31];
	num++;
	num *= -1;
	while (num > 0) {
		bin[i] = num % 2;
		num /= 2;
		i++;
	}
	return bin;
}


/******************************************************
 * Function: read_asm
 *
 * Info:
 *  This function reads assembly code and saves the
 *  information into struct Sym, Data, Text, respectively.
 *
 *******************************************************/
struct Text *next_text = NULL;
void read_asm() {
	int tmp, i;
	unsigned int address;
	char temp[0x1000] = { 0 };
	struct Sym *temp_sym = NULL;
	struct Data *temp_data = NULL;
	struct Text *temp_text = NULL;

	struct Sym *next_sym = NULL;
	struct Data *next_data = NULL;

	next_sym = Symbols;

	//Read .data region
	address = 0x10000000;
	for (i = 0; scanf("%s", temp) == 1;) {
		if (strcmp(temp, ".text") == 0) {
			/* blank */
			//next_sym->size = address - (next_sym->address);
			break;

		}
		else if (temp[strlen(temp) - 1] == ':') {
			/* blank */
			char *arr1 = strtok(temp, ":");
			if (address == 0x10000000) {

				//fprintf(stderr, "\n\n\n\  11111111111111111111111111111111111111111111111111111 \n\n\n\n");


				next_sym = Symbols;
				Symbols->name = (char*)malloc(strlen(arr1));
				strcpy(Symbols->name, arr1);
				Symbols->address = address;
				Symbols->size = 0;


			}
			else {
				//fprintf(stderr, "\n\n\n\ 222222222222222222222222222222222222222222222222222222222 \n\n\n\n");
				temp_sym = (struct Sym *)malloc(sizeof(struct Sym));
				next_sym->next = temp_sym;
				//next_sym->size = address - (next_sym->address);
				next_sym = temp_sym;
				next_sym->size = 0;
				temp_sym->name = (char*)malloc(strlen(arr1));
				strcpy(temp_sym->name, arr1);
				temp_sym->address = address;
				temp_sym->size = 0;

			}


		}
		else if (strcmp(temp, ".word") == 0) {
			/* blank */
			scanf("%s", temp);

			if (next_sym->address == address) {


				temp_data = (struct Data *)malloc(sizeof(struct Data *));
				next_sym->first = temp_data;
				next_sym->last = temp_data;

				//(next_sym->first)->next = temp_data;
				next_data = temp_data;

				if (temp[1] == 'x') {
					temp_data->value = hex_to_dec(temp);
				}
				else {
					temp_data->value = atoi(temp);
				}

			}
			else {

				temp_data = (struct Data *)malloc(sizeof(struct Data *));
				next_data->next = temp_data;
				next_data = temp_data;
				next_sym->last = temp_data;

				//temp_data->next = temp_data;
				if (temp[1] == 'x') {
					temp_data->value = hex_to_dec(temp);
				}
				else {
					temp_data->value = atoi(temp);
				}
			}
			address += 4;
			next_sym->size += 4;

			//fprintf(stderr, "\n\n\n\ next_sym->name  ::  %s,next_sym->size  ::  %d \n\n\n\n",next_sym->name,next_sym->size);


		}
	}

	//address += 4;

	datasize = address - 0x10000000;

	//fprintf(stderr, "\n\n\n\ datasize :: %d\n\n\n\n", datasize);



	//Read .text region
	address = 0x400000;
	for (i = 0; scanf("%s", temp) == 1;) {
		if (temp[strlen(temp) - 1] == ':') {
			/* blank */
			//fprintf(stderr, "\n\n\n\ 333333333333333333333333333333333333333333333 \n\n\n\n");
			if (!(next_sym->name)) {


				//fprintf(stderr, "\n\n\n\ 44444444444444444444444444444444444444444444 \n\n\n\n");
				char *arr2 = strtok(temp, ":");
				temp_sym = (struct Sym *)malloc(sizeof(struct Sym));

				//next_sym->next = temp_sym;
				Symbols = temp_sym;
				//next_sym = Symbols;
				temp_sym->address = address;
				temp_sym->name = (char*)malloc(sizeof(strlen(arr2)));
				temp_sym->size = 0;
				strcpy(temp_sym->name, arr2);
				next_sym = Symbols;


				//fprintf(stderr, "\n\n\n\ next :: %s Symbols :: %s  temp :: %s \n\n\n\n",next_sym->name, Symbols->name, temp_sym->name);


				continue;
			}
			else {
				char *arr2 = strtok(temp, ":");
				temp_sym = (struct Sym *)malloc(sizeof(struct Sym));
				//next_sym->size = address - (next_sym->address);
				next_sym->next = temp_sym;
				next_sym = temp_sym;
				temp_sym->address = address;
				temp_sym->name = (char*)malloc(sizeof(strlen(arr2)));
				strcpy(temp_sym->name, arr2);
				temp_sym->size = 0;
				continue;
			}


		}
		else {
			/* blank */
			if (address == 0x400000) {
				next_text = Texts;
			}
			else {
				temp_text = (struct Text *)malloc(sizeof(struct Text));
				next_text->next = temp_text;
				next_text = temp_text;
			}

			next_text->address = address;

			for (int i = 0; i < 20; i++) {
				if (strcmp(temp, inst[i].name) == 0) {
					next_text->idx = i;
					break;
				}
			}
		}

		//fprintf(stderr, "\n\n\n\  next_sym->name : %s , %d \n\n\n\n", next_sym->name, next_sym->address);

		//fprintf(stderr, "\n\n\n\ temp : %s \n\n\n\n", temp);





		// la 의 경우

		char rs[100];
		char rt[100];
		char jump_to[100];





		if (strcmp(temp, "la") == 0) {
			char  la_str1[100];
			char  la_str2[100];
			scanf("%s", la_str1);
			scanf("%s", la_str2);


			//fprintf(stderr, "\n\n\n\ inside  hi : la2 \n\n\n\n");

			char *mi_rt = strtok(la_str1, ",");//$8

			if (mi_rt[0] == '$')
				mi_rt = &(mi_rt[1]);

			char *hi = mi_rt;

			//temp_text = (struct Text *)malloc(sizeof(struct Text));
			//next_text->t = (char *)malloc(sizeof(char) * 50);
			//strcpy(temp_text->t, hi);
			//temp_text->la_hi = (char *)malloc(sizeof(char) * 50);

			struct Sym *find_sym = Symbols;

			while (find_sym->next) {
				if (strcmp(find_sym->name, la_str2) == 0) {
					next_text->hi_address = find_sym->address;
					break;
				}


				find_sym = find_sym->next;

			}



			if ((next_text->hi_address) < 0x10000004) {
				unsigned int shift_int = next_text->hi_address;
				shift_int = shift_int >> 16;
				next_text->idx = 9;

				//temp_text = (struct Text *)malloc(sizeof(struct Text));
				next_text->t = (char *)malloc(sizeof(char) * 50);
				//next_text->immediate = (char *)malloc(sizeof(char) * 50);
				strcpy(next_text->t, hi);
				next_text->immediate = shift_int;
				//fprintf(stderr, "\n\n\n\ next_text->adress : %d, next_text->t : %s, next_text->imm : %d \n\n\n\n", next_text->address, next_text->t, next_text->immediate);


			}
			else {
				unsigned int temp_int = next_text->hi_address;
				unsigned int shift_int = next_text->hi_address;

				//fprintf(stderr, "\n\n\n\n^^^^^^^^^^^^^^6 temp_int-> %d, shift_int : %d \n\n\n\n", temp_int, shift_int);

				temp_int = temp_int << 16;
				temp_int = temp_int >> 16;
				shift_int = shift_int >> 16;



				//fprintf(stderr, "\n\n\n\ temp_int-> %d, shift_int : %d \n\n\n\n", temp_int, shift_int);






				next_text->idx = 9;
				next_text->t = (char *)malloc(sizeof(char) * 50);
				strcpy(next_text->t, hi);
				next_text->immediate = shift_int;


				address += 4;

				temp_text = (struct Text *)malloc(sizeof(struct Text));
				next_text->next = temp_text;
				next_text = temp_text;
				next_text->idx = 13;
				next_text->address = address;


				//temp_text = (struct Text *)malloc(sizeof(struct Text));
				next_text->t = (char *)malloc(sizeof(char) * 50);
				next_text->s = (char *)malloc(sizeof(char) * 50);
				//next_text->immediate = (char *)malloc(sizeof(char) * 50);

				strcpy(next_text->t, hi);
				strcpy(next_text->s, hi);
				next_text->immediate = temp_int;

				//fprintf(stderr, "\n\n\n\ next_text->adress : %d, next_text->t : %s, next_text->s : %s ,next_text->imm : %d \n\n\n\n", next_text->address, next_text->t, next_text->s, next_text->immediate);


			}




		}

		// R


		else if (inst[next_text->idx].type == 'R') {

			//fprintf(stderr, "\n\n\n\ inside  hi : R \n\n\n\n");


			// jr -> $8
			if (next_text->idx == 8) {
				scanf("%s", temp);
				//fprintf(stderr, "\n\n\n\  %s \n\n\n\n", temp);

				char hi[10] = { 0 };

				char* pch;
				//pch = strtok(NULL, " $");
				//fprintf(stderr, "\n\n\n\  %s \n\n\n\n", pch);

				pch = strtok(temp, "$");
				//fprintf(stderr, "\n\n\n\  %s \n\n\n\n", pch);
				next_text->s = (char*)malloc(100);
				strcpy(next_text->s, pch);

				//fprintf(stderr, "\n\n\n\ inside  hi : R \n\n\n\n");


				//strcpy(next_text->s, temp);
				//fprintf(stderr, "\n\n\n\ //////////////// \n\n\n\n");

				//fprintf(stderr, "\n\n\n\  %s \n\n\n\n", next_text->s);

			}
			else {
				for (i = 0; i < 3; i++) {
					scanf("%s", temp);
					char *mi_rt = strtok(temp, ",");//$8
					char hi[10] = { 0 };
					for (int j = 0; j < strlen(mi_rt); j++) {
						if (strcmp(&mi_rt[j], "$") == 0) {
							continue;
						}
						else {
							hi[j - 1] = mi_rt[j];
						}
					}
					if (i == 0) {
						next_text->d = (char*)malloc(sizeof(char)*strlen(hi));
						strcpy(next_text->d, hi);
					}
					else if (i == 1) {
						next_text->s = (char*)malloc(sizeof(char)*strlen(hi));
						strcpy(next_text->s, hi);
					}
					else {
						next_text->t = (char*)malloc(sizeof(char)*strlen(hi));
						strcpy(next_text->t, hi);
					}


				}
				//fprintf(stderr, "\n\n\n\ next_text address-> %d, d : %s s : %s t : %s \n\n\n\n", next_text->address, next_text->d, next_text->s, next_text->t);


			}
		}

		// I 의 경우


		else if (inst[next_text->idx].type == 'I') {
			//bne beq 4 5 
			//fprintf(stderr, "\n\n\n\ inside  hi : l \n\n\n\n");

			if (next_text->idx == 4 || next_text->idx == 5) {
				//   beq   $9, $0, lab4




				scanf("%s", rs); //$
				scanf("%s", rt); //$
				scanf("%s", jump_to);
				char *mi_rs = strtok(rs, ",");
				char hi[10] = { 0 };
				for (int i = 0; i < strlen(mi_rs); i++) {
					if (strcmp(&mi_rs[i], "$") == 0) {
						continue;
					}
					else {
						hi[i - 1] = mi_rs[i];
					}
				}

				char *mi_rt = strtok(rt, ",");
				char hi2[10] = { 0 };
				for (int i = 0; i < strlen(mi_rt); i++) {
					if (strcmp(&mi_rt[i], "$") == 0) {
						continue;
					}
					else {
						hi2[i - 1] = mi_rt[i];
					}
				}
				//temp_text = (struct Text *)malloc(sizeof(struct Text));
				next_text->s = (char *)malloc(sizeof(char) * 50);
				next_text->t = (char *)malloc(sizeof(char) * 50);
				next_text->d = (char *)malloc(sizeof(char) * 50);
				strcpy(next_text->s, hi);
				strcpy(next_text->t, hi2);
				strcpy(next_text->d, jump_to);

				/*
				struct Sym *find_sym = Symbols;

				while (1) {
					//fprintf(stderr, "\n\n\n\ jump : %s \n\n\n\n",jump_to);
					fprintf(stderr, "\n\n\n\ find_sym->name : %s, find_sym->address : %d \n\n\n\n", find_sym->name, find_sym->address);

					if (strcmp(find_sym->name, jump_to) == 0) {
						fprintf(stderr, "\n\n\n\****************** \n\n\n\n");

						next_text->hi_address = find_sym->address;
						fprintf(stderr, "\n\n\n\ find_sym->name : %s, find_sym->address : %d \n\n\n\n", find_sym->name,find_sym->address);

						break;
					}


					find_sym = find_sym->next;

				}

				next_text->immediate = next_text->hi_address;
				*/

				//fprintf(stderr, "\n\n\n\ next_text address-> %d, s : %s t : %s imm : %d \n\n\n\n", next_text->address, next_text->s, next_text->t, next_text->immediate);
			}



			// lui   9
			else if (next_text->idx == 9) {
				//lui
				//   lui   $17, 100
				//2번 $
				scanf("%s", rt); //$
				scanf("%s", jump_to);


				char *mi_rt = strtok(rt, ",");//$8

				if (mi_rt[0] == '$')
					mi_rt = &(mi_rt[1]);

				char *hi = mi_rt;



				//temp_text = (struct Text *)malloc(sizeof(struct Text));
				next_text->t = (char *)malloc(sizeof(char) * 50);
				//next_text->immediate = (char *)malloc(sizeof(char) * 50);
				strcpy(next_text->t, hi);
				//char hell[100];
				if (jump_to[1] == 'x') {
					next_text->immediate = hex_to_dec(jump_to);
				}
				else {
					next_text->immediate = atoi(jump_to);
				}

				//fprintf(stderr, "\n\n\n\ next_text address-> %d, t : %s imme : %d \n\n\n\n", next_text->address, next_text->t, next_text->immediate);
			}



			//lw sw 10  18

			else if (next_text->idx == 10 || next_text->idx == 18) {
				scanf("%s", rt);
				scanf("%s", rs);
				// fprintf(stderr, "rs=%s, rt=%s\n", rs, rt);

				char *mi_rs = strtok(rs, ")");
				//fprintf(stderr, "mi_rs=%s\n", mi_rs);
				//char *ext = strtok(rs, "(");
				char *mi_rt = strtok(rt, ",");
				char hi[10] = { 0 };
				for (int i = 0; i < strlen(mi_rt); i++) {
					if (strcmp(&mi_rt[i], "$") == 0) {
						continue;
					}
					else {
						hi[i - 1] = mi_rt[i];
					}
				}
				//                        0 1 2 3
				char hi2[10] = { 0 };
				for (i = 0; i < strlen(mi_rs); i++) {

					if (mi_rs[i] == '$') {
						strcpy(hi2, mi_rs + i + 1);

					}

				}
				char *ext = strtok(rs, "(");


				//temp_text = (struct Text *)malloc(sizeof(struct Text));
				next_text->t = (char *)malloc(sizeof(char) * 50);
				next_text->s = (char *)malloc(sizeof(char) * 50);
				//next_text->immediate = (char *)malloc(sizeof(char) * 50);

				strcpy(next_text->t, hi);
				strcpy(next_text->s, hi2);

				next_text->immediate = atoi(rs);

				//fprintf(stderr, "\n\n\n\ next_text address-> %d,  t : %s s : %s  imme : %d\n\n\n\n", next_text->address, next_text->t, next_text->s, next_text->immediate);
			}

			else {
				//나머지 I
				scanf("%s", rt); //$
				scanf("%s", rs); //$
				scanf("%s", jump_to);

				char *mi_rt = strtok(rt, ",");
				char hi[10] = { 0 };
				for (int i = 0; i < strlen(mi_rt); i++) {
					if (strcmp(&mi_rt[i], "$") == 0) {
						continue;
					}
					else {
						hi[i - 1] = mi_rt[i];
					}
				}
				char *mi_rs = strtok(rs, ",");
				char hi2[10] = { 0 };
				for (int i = 0; i < strlen(mi_rs); i++) {
					if (strcmp(&mi_rs[i], "$") == 0) {
						continue;
					}
					else {
						hi2[i - 1] = mi_rs[i];
					}
				}

				//temp_text = (struct Text *)malloc(sizeof(struct Text));
				next_text->t = (char *)malloc(sizeof(char) * 50);
				next_text->s = (char *)malloc(sizeof(char) * 50);
				//next_text->immediate = (char *)malloc(sizeof(char) * 50);

				strcpy(next_text->t, hi);
				strcpy(next_text->s, hi2);
				if (jump_to[1] == 'x') {
					next_text->immediate = hex_to_dec(jump_to);
				}
				else {
					next_text->immediate = atoi(jump_to);
				}


				//fprintf(stderr, "\n\n\n\ next_text address-> %d,  t : %s s : %s imme : %d \n\n\n\n", next_text->address, next_text->t, next_text->s, next_text->immediate);
			}
		}

		// S 의 경우


		else if (inst[next_text->idx].type == 'S') {



		//fprintf(stderr, "\n\n\n\ inside  hi : S \n\n\n\n");
			//srl sll
			char rd[100];
			scanf("%s", rd);//$
			scanf("%s", rt);//$
			scanf("%s", jump_to);


			char *mi_rd = strtok(rd, ",");
			char hi[10] = { 0 };
			for (int i = 0; i < strlen(mi_rd); i++) {
				if (strcmp(&mi_rd[i], "$") == 0) {
					continue;
				}
				else {
					hi[i - 1] = mi_rd[i];
				}
			}

			char *mi_rt = strtok(rt, ",");
			char hi2[10] = { 0 };
			for (int i = 0; i < strlen(mi_rt); i++) {
				if (strcmp(&mi_rt[i], "$") == 0) {
					continue;
				}
				else {
					hi2[i - 1] = mi_rt[i];
				}
			}
			//next_text = (struct Text *)malloc(sizeof(struct Text));
			next_text->d = (char *)malloc(sizeof(char) * 50);
			next_text->t = (char *)malloc(sizeof(char) * 50);
			next_text->shamt = (char *)malloc(sizeof(char) * 50);
			strcpy(next_text->d, hi);
			strcpy(next_text->t, hi2);
			strcpy(next_text->shamt, jump_to);


			//fprintf(stderr, "\n\n\n\ next_text address-> %d, d : %s t : %s sham : %s \n\n\n\n", next_text->address, next_text->d, next_text->t, next_text->shamt);

		}


		// J 의 경우


		else if (inst[next_text->idx].type == 'J') {


		//fprintf(stderr, "\n\n\n\ inside  hi : J \n\n\n\n");

			scanf("%s", temp);
			//d가 jump _To ~~
			//temp_text = (struct Text *)malloc(sizeof(struct Text));
			next_text->d = (char*)malloc(sizeof(char) * 50);
			strcpy(next_text->d, temp);


			/*
			struct Sym *find_sym = Symbols;

			while (1) {
				//fprintf(stderr, "\n\n\n\ jump : %s \n\n\n\n",jump_to);
				fprintf(stderr, "\n\n\n\ find_sym->name : %s, find_sym->address : %d \n\n\n\n", find_sym->name, find_sym->address);

				if (strcmp(find_sym->name, temp) == 0) {
					fprintf(stderr, "\n\n\n\****************** \n\n\n\n");

					next_text->hi_address = find_sym->address;
					fprintf(stderr, "\n\n\n\ find_sym->name : %s, find_sym->address : %d \n\n\n\n", find_sym->name, find_sym->address);

					break;
				}


				find_sym = find_sym->next;

			}

			next_text->immediate = next_text->hi_address;
			*/
			//fprintf(stderr, "\n\n\n\ next_text address-> %d, hi_addre : %d  \n\n\n\n", next_text->address, next_text->hi_address);
		}


		// la 의 경우
		next_sym->size += 4;


		address += 4;
		//fprintf(stderr, "\n\n\n\ address :  %d\n\n\n\n", address);

		//Symbols = next_sym;

	}

	//address -= 4;

	//next_sym->size = address - (next_sym->address);

	//fprintf(stderr, "\n\n\n\SSSSSSSyyyyyymmmmmmmmmmmmm Size :: %d \n\n\n\n", next_sym->size);



	textsize = address - 0x400000;
	//fprintf(stderr, "\n\n\n\TTTTTTEEEEEEEEEXXXXXXXXXXXTTTTTTTTTTTTTT Size :: %d \n\n\n\n", textsize);


	struct Sym* sym;
	//struct Data* data;
	sym = Symbols;

	while (1) {
		//fprintf(stderr, "\n\n\n\ Symbols->  : %s address :: %d \n\n\n\n", sym->name,sym->address);


		sym = sym->next;
		if (sym) {
			continue;
		}
		else {
			break;
		}

		//fprintf(stderr, "\n\n\n*********************Symbols->  : %s Size :: %d \n\n\n\n", sym->name, sym->size);


	}

	struct Text* text;
	//struct Data* data;
	text = Texts;

	while (1) {
		//fprintf(stderr, "\n\n\n\ Text address :: %d \n\n\n\n", text->address);


		text = text->next;
		if (text) {
			continue;
		}
		else {
			break;
		}

		//fprintf(stderr, "\n\n\n*********************Symbols->  : %s Size :: %d \n\n\n\n", sym->name, sym->size);


	}


	//fprintf(stderr, "\n\n\n\ textsize :: %d \n\n\n\n", textsize);








}


/******************************************************
 * Function: subst_asm_to_num
 *
 * Info:
 *  This function converts assembly code to numbers.
 *
 *******************************************************/
void subst_asm_to_num() {
	struct Text *text;
	struct Sym* sym;
	// num_to_bits쓰면된다.
	//fprintf(stderr, "hellllllllllll--------zzzzzzzzzzzzzzzzzzzzzz\n");
	for (text = Texts; text != NULL; text = text->next) {
		/* blank */
		//fprintf(stderr, "hello--------zzzzzzzzzzzzzzzzzzzzzz\n");
		if (inst[text->idx].type == 'R') {
			if (text->idx == 8) {
				//jr
				//ok

				//fprintf(stderr, "\nR--- text_idx : %d \n", text->idx);

				//fprintf(stderr, "\nR--- before text_s : %s \n", text->s);
				strcpy(text->s, num_to_bits(atoi(text->s), 5));
				//strcpy(text->t, num_to_bits(0, 5));
				//strcpy(text->d, num_to_bits(0, 5));
				//fprintf(stderr, "JR--------zzzzzzzzzzzzzzzzzzzzzz\n");
			}
			else {
				//r타입애들jr빼고 //얘는 된다.
				//ok
				//fprintf(stderr, "\nR--- text_idx : %d \n", text->idx);

				//fprintf(stderr, "\nR--- before text_d : %s \n", text->d);
				strcpy(text->d, num_to_bits(atoi(text->d), 5));
				//fprintf(stderr, "\nR--- text_d : %s \n", text->d);

				//fprintf(stderr, "\nR--- before text_s : %s \n", text->s);
				strcpy(text->s, num_to_bits(atoi(text->s), 5));
				//fprintf(stderr, "\nR--- text_s : %s \n", text->s);


				//fprintf(stderr, "\nR--- before text_t : %s \n", text->t);
				strcpy(text->t, num_to_bits(atoi(text->t), 5));
				//fprintf(stderr, "\nR--- text_t : %s \n", text->t);


				//fprintf(stderr, "R----------zzzzzzzzzzzzzzzzzzzzzz\n");

			}

		}

		else if (inst[text->idx].type == 'I') {
			if (text->idx == 9) {
				//lui
				//ok
				//fprintf(stderr, "\nlui--- text_idx : %d \n", text->idx);
				unsigned int zero = 0;

				//strcpy(text->s, num_to_bits(zero, 5));
				strcpy(text->t, num_to_bits(atoi(text->t), 5));

				text->real_imm = (char *)malloc(sizeof(char) * 50);
				text->real_imm = num_to_bits(text->immediate, 16);
				//fprintf
				//fprintf(stderr, "\ni---text : t %s, imee : %s \n", text->t, text->real_imm);

				//fprintf(stderr, "LUI---------zzzzzzzzzzzzzzzzzzzzzz\n");
			}
			else if (text->idx == 10 || text->idx == 18) {
				//lw sw
				//ok

				//fprintf(stderr, "\nlw sw-- text_idx : %d \n", text->idx);


				//fprintf(stderr, "\ni--- before text_s : %s \n", text->s);
				strcpy(text->s, num_to_bits(atoi(text->s), 5));
				//fprintf(stderr, "\ni--- text_s : %s \n", text->s);

				//fprintf(stderr, "\ni--- before text_t : %s \n", text->t);
				strcpy(text->t, num_to_bits(atoi(text->t), 5));
				//fprintf(stderr, "\ni--- text_t : %s \n", text->t);

				//fprintf(stderr, "\ni--- before text_imm : %d \n", text->immediate);

				//text->immediate = atoi(num_to_bits(text->immediate, 16));
				text->real_imm = (char *)malloc(sizeof(char) * 50);
				strcpy(text->real_imm, (num_to_bits(text->immediate, 16)));
				//text->immediate = atoi(num_to_bits(text->immediate, 16));
				//fprintf(stderr, "\ni--- text_real_imm : %s \n", text->real_imm);

				//fprintf(stderr, "LW---------SW-----------zzzzzzzzzzzzzzzzzzzzzz\n");
			}
			else if (text->idx == 4 || text->idx == 5) {
				//bne beq
				//수정해야함
				//fprintf(stderr, "\nbne beq--- text_idx : %d \n", text->idx);
				//fprintf(stderr, "\nbne beq--- before text_s : %s \n", text->s);
				strcpy(text->s, num_to_bits(atoi(text->s), 5));
				//fprintf(stderr, "\nbne beq--- text_s : %s \n", text->s);

				//fprintf(stderr, "\nbne beq--- before text_t : %s \n", text->t);
				strcpy(text->t, num_to_bits(atoi(text->t), 5));
				//fprintf(stderr, "\nbne beq--- text_t : %s \n", text->t);
				//d에 점프값 넣어둠
				struct Sym *find_sym = Symbols;

				//fprintf(stderr, "\n\n\n\****find_sym :: %s***** \n\n\n\n", find_sym->name);

				//fprintf(stderr, "\n\n\n\****************** \n\n\n\n");

				//fprintf(stderr, "\n\n\n\****text_d :: %s***** \n\n\n\n", text->d);

				while (1) {
					//fprintf(stderr, "\n\n\n\ jump : %s \n\n\n\n",jump_to);


					//fprintf(stderr, "\n\n\n\****find_sym :: %s***** \n\n\n\n", find_sym->name);
					//fprintf(stderr, "\n\n\n\****************** \n\n\n\n");

					//fprintf(stderr, "\n\n\n\****text_d :: %s***** \n\n\n\n", text->d);

					//fprintf(stderr, "\n\n\n\****text_d  add :: %d***** \n\n\n\n", text->address);
					if (strcmp(find_sym->name, text->d) == 0) {

						//fprintf(stderr, "\n\n\n\****find_sym :: %s***** \n\n\n\n", find_sym->name);
						//fprintf(stderr, "\n\n\n\****************** \n\n\n\n");
						//fprintf(stderr, "\n\n\n\ find_sym->name : %s find_sym->address : %d \n\n\n\n", find_sym->name, find_sym->address);
						text->hi_address = find_sym->address;
						//fprintf(stderr, "\n\n\n\ find_sym->name : %s, find_sym->address : %d \n\n\n\n", find_sym->name, find_sym->address);

						break;
					}

					find_sym = find_sym->next;



					if (find_sym) {
						continue;
					}
					else {
						break;
					}


					//find_sym = find_sym->next;

				}

				//text->immediate = ((text->address) - (text->hi_address))/4;
				text->immediate = ((text->hi_address) - (((int)(text->address))+4)) / 4;


				//fprintf(stderr, "\n text->hi_address : %d  text->address %d \n", text->hi_address, text->address);


				//fprintf(stderr, "\n%%%%%%%%%%%%%%%%%% add : %d %%%%%%%%%%%%%%%%%%\n", text->immediate);

				
				text->real_imm = (char *)malloc(sizeof(char) * 50);
				strcpy(text->real_imm , num_to_bits(text->immediate, 16));//여기

				//fprintf(stderr, "BNE---BEQ----------zzzzzzzzzzzzzzzzzzzzzz\n");
			}

			else if (text->idx == 0 || text->idx == 3 || text->idx == 13 || text->idx == 14) {
				// I 나머지
				//ok
				//fprintf(stderr, "\niii--- text_idx : %d \n", text->idx);


				//fprintf(stderr, "\ni--- before text_s : %s \n", text->s);
				strcpy(text->s, num_to_bits(atoi(text->s), 5));

				//fprintf(stderr, "\ni--- text_s : %s \n", text->s);

				//fprintf(stderr, "\ni--- before text_t : %s \n", text->t);
				strcpy(text->t, num_to_bits(atoi(text->t), 5));

				//fprintf(stderr, "\ni--- text_t : %s \n", text->t);


				//fprintf(stderr, "\ni--- beforeimme : %d \n", text->immediate);
				text->real_imm = (char *)malloc(sizeof(char) * 50);
				text->real_imm = num_to_bits(text->immediate, 16);

				//fprintf(stderr, "\ni--- imee : %s \n", text->real_imm);
				//fprintf(stderr, "I-------------zzzzzzzzzzzzzzzzzzzzzz\n");
			}

		}
		else if (inst[text->idx].type == 'S') {
			if (text->idx == 16 || text->idx == 17) {
				//srl sll
				//ok
				//fprintf(stderr, "\nsss-- text_idx : %d \n", text->idx);

				//fprintf(stderr, "\ni--- before text_s : %s \n", text->s);
				//strcpy(text->s, num_to_bits(0, 5));
				//fprintf(stderr, "\ni--- text_s : %s \n", text->s);
				// s부분은 00000
				//fprintf(stderr, "\ni--- before text_s : %s \n", text->d);
				strcpy(text->d, num_to_bits(atoi(text->d), 5));

				//fprintf(stderr, "\ni--- text_d : %s \n", text->d);

				//fprintf(stderr, "\ni--- before text_t : %s \n", text->t);
				strcpy(text->t, num_to_bits(atoi(text->t), 5));

				//fprintf(stderr, "\ni--- text_t : %s \n", text->t);

				//fprintf(stderr, "\ni--- before shamt : %s \n", text->shamt);
				strcpy(text->shamt, num_to_bits(atoi(text->shamt), 5));

				//fprintf(stderr, "\ni--- shamt: %s \n", text->shamt);

				//fprintf(stderr, "S-----------zzzzzzzzzzzzzzzzzzzzzz\n");
			}
		}


		else if (inst[text->idx].type == 'J') {
			//j jal
			//수정해야한다.
			//fprintf(stderr, "\njjj--- text_idx : %d \n", text->idx);

			struct Sym *find_sym = Symbols;

			//fprintf(stderr, "\n\n\n\****find_sym :: %s***** \n\n\n\n", find_sym->name);	

			//fprintf(stderr, "\n\n\n\****************** \n\n\n\n");

			//fprintf(stderr, "\n\n\n\****text_d :: %s***** \n\n\n\n", text->d);

			while(1) {
				//fprintf(stderr, "\n\n\n\ jump : %s \n\n\n\n",jump_to);


				//fprintf(stderr, "\n\n\n\****find_sym :: %s***** \n\n\n\n", find_sym->name);
				//fprintf(stderr, "\n\n\n\****************** \n\n\n\n");

				//fprintf(stderr, "\n\n\n\****text_d :: %s***** \n\n\n\n", text->d);

				//fprintf(stderr, "\n\n\n\****text_d  add :: %d***** \n\n\n\n", text->address);
				if (strcmp(find_sym->name, text->d) == 0) {

					//fprintf(stderr, "\n\n\n\****find_sym :: %s***** \n\n\n\n", find_sym->name);
					//fprintf(stderr, "\n\n\n\****************** \n\n\n\n");
					//fprintf(stderr, "\n\n\n\ find_sym->name : %s find_sym->address : %d \n\n\n\n", find_sym->name, find_sym->address);
					text->hi_address = find_sym->address;
					//fprintf(stderr, "\n\n\n\ find_sym->name : %s, find_sym->address : %d \n\n\n\n", find_sym->name, find_sym->address);

					break;
				}

				find_sym = find_sym->next;



				if (find_sym) {
					continue;
				}
				else {
					break;
				}


				//find_sym = find_sym->next;

			}

			//text->immediate = ((text->hi_address) - (((int)(text->address)) + 4)) / 4;

			text->immediate = text->hi_address;
			unsigned int temp_imm = text->immediate;

			temp_imm = temp_imm << 4;
			temp_imm = temp_imm >> 6;

			//fprintf(stderr, "\ntext->immediate : %d \n", text->immediate);

			fprintf(stderr, "\ntemp_imm : %d \n", temp_imm);


			//fprintf(stderr, "\n%%%%%%%%%%%%%%%%%% add : %d %%%%%%%%%%%%%%%%%%\n", text->immediate);


			

			text->d = num_to_bits(temp_imm, 26);

			//fprintf(stderr, "\ni--- text_Add: %s \n", text->d);
		}

	


	}

}


/******************************************************
 * Function: print_bits
 *
 * Info:
 *  This function prints binary bit string converted by
 *  assembler. It will make binary object file of assembly code.
 *
 *******************************************************/
void print_bits() {
	struct Text* text;
	struct Sym* sym;
	struct Data* data;

	// print the header
	printf("%s", num_to_bits(textsize, 32));
	printf("%s", num_to_bits(datasize, 32));

	// print the body
	for (text = Texts; text != NULL; text = text->next) {
		printf("%s", inst[text->idx].op);

		if (inst[text->idx].type == 'R') {
			/* blank */
			if (text->idx == 8) {
				printf("%s", text->s);
				printf("00000");
				
				printf("00000");
				printf("00000");
				printf("%s", inst[text->idx].funct);
			}
			else {
				printf("%s", text->s);
				printf("%s", text->t);
				printf("%s", text->d);
				printf("00000");
				printf("%s", inst[text->idx].funct);
			}

		}
		else if (inst[text->idx].type == 'I') {
			/* blank */
			if (text->idx == 9) {
				//lui
				printf("00000");
				printf("%s", text->t);
				printf("%s", text->real_imm);
			}
			else if (text->idx == 10 || text->idx == 18) {
				//lw sw
				printf("%s", text->s);
				printf("%s", text->t);
				printf("%s", text->real_imm);
			}
			else if (text->idx == 4 || text->idx == 5) {
				//bne beq
				printf("%s", text->s);
				printf("%s", text->t);
				printf("%s", text->real_imm);
			}
			else if (text->idx == 0 || text->idx == 3 || text->idx == 13 || text->idx == 14) {
				// i포맷의 나머지
				printf("%s", text->s);
				printf("%s", text->t);
				printf("%s", text->real_imm);
			}


		}
		else if (inst[text->idx].type == 'S') {
			/* blank */
			printf("00000");
			printf("%s", text->t);
			printf("%s", text->d);
			printf("%s", text->shamt);
			printf("%s", inst[text->idx].funct);


		}
		else if (inst[text->idx].type == 'J') {
			// j 포맷
			printf("%s", text->d);
		}
	
	}
	if (datasize != 0) {
		for (sym = Symbols; sym != NULL; sym = sym->next) {
			/* blank */
			 //blank
			char* str;
			int data_temp = -4;
			struct Data* will_print_data;
			will_print_data = sym->first;

			fprintf(stderr, "\sym->first :: %u  sym->last :: %u \n", (sym->first), (sym->last));
			fprintf(stderr, "\sym->first :: %d  break :: %d \n", (sym->address), (0x10000000 + datasize - 4));

			while (1) {
				printf("%s", num_to_bits(will_print_data->value, 32));


				fprintf(stderr, "\sym->last->value :: %d   will_print_data->value :: %d \n", (sym->last->value), will_print_data->value);
				data_temp += 4;

				fprintf(stderr, "\n  data_temp :: %d \n", data_temp);

				if (sym->last == will_print_data) {
					fprintf(stderr, "\n  bbbbbbbbbbbbbbrrrrrrrrrrrrrrrrrr \n");
					break;
				}
				else {

					will_print_data = will_print_data->next;
					continue;
				}
			}
			if (sym->address + data_temp == (0x10000000 + datasize - 4)) {

				fprintf(stderr, "\n  bbrrr \n");

				break;
			}





			/*
			data = (struct Data*)malloc(sizeof(struct Data));
			for (data = sym->first; data != NULL; data = data->next) {
				str = num_to_bits(data->value, 32);
				//printf("");
				printf("%s", str);
			}
			*/

		}
	}
	printf("\n"); // To exclude "No newline at end of file"
}
