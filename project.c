#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
	switch(ALUControl)
	{
		case 000:
				*ALUresult == A + B;
				break;
		case 001:
				*ALUresult == A - B;
				break;
		case 010:
				if(A < B)
					*ALUresult = 1;
				else
					*ALUresult = 0;
				break;
		case 011:
				if(A < B)
					*ALUresult = 1;
				else
					*ALUresult = 0;
				break;
		case 100:
				*ALUresult = A & B;
				break;
		case 101:
				*ALUresult = A | B;
				break;
		case 110:
				B << 16;
				break;
		case 111:
				*ALUresult = ~A;
				break;
	}

}

int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{

}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
	*op = instruction >> 26;
	*r1 = (instruction << 6) >> 27;
	*r2 = (instruction << 10) >> 27;
	*r3 = (instruction << 16) >> 27;
	*funct = (instruction << 26) >> 26;
	*offset = (instruction << 16) >> 16;
	*jsec = (instruction << 6) >> 6;
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
	*data1 = Reg[r1];
	*data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
	switch(ALUOp)
	{
		case 000:
				if(ALUSrc == 1)	
					*ALUresult = data1 + extended_value;
				else
					*ALUresult = data1 + data2;
				return 0;
		case 001:
				if(ALUSrc == 1)
					*ALUresult = data1 - extended_value;
				else
					*ALUresult = data1 - data2;
				return 0;
		case 010:
				if(ALUSrc == 1)
				{
					if(data1 < extended_value)
						*ALUresult = 1;
					else
						*ALUresult = 0;
				}
				else
				{
					if(data1 < data2)
						*ALUresult = 1;
					else
						*ALUresult = 0;
				}
				return 0;
		case 011:
				if(ALUSrc == 1)
				{
					if(data1 > extended_value)
						*ALUresult = 1;
					else
						*ALUresult = 0;
				}
				else
				{
					if(data1 > data2)
						*ALUresult = 1;
					else
						*ALUresult = 0;
				}
				return 0;
		case 100:
				if(ALUSrc == 1)
					*ALUresult = data1 & extended_value;
				else
					*ALUresult = data1 & data2;
				return 0;
		case 101:
				if(ALUSrc == 1)
					*ALUresult = data1 | extended_value;
				else
					*ALUresult = data1 | data2;
				return 0;
		case 110:
				if(ALUSrc == 1)
					extended_value << 16;
				else
					data2 << 16;
				return 0;
		case 111:
				if(funct == 100000)
				{
					if(ALUSrc == 1)	
						*ALUresult = data1 + extended_value;
					else
						*ALUresult = data1 + data2;
					return 0;
				}
				else if(funct == 100100)
				{
					if(ALUSrc == 1)
						*ALUresult = data1 & extended_value;
					else
						*ALUresult = data1 & data2;
					return 0;
				}
				else if(funct == 100101)
				{
					if(ALUSrc == 1)
						*ALUresult = data1 | extended_value;
					else
						*ALUresult = data1 | data2;
					return 0;
				}
				else if((funct == 101010) | (funct == 101011))
				{
					if(ALUSrc == 1)
					{
						if(data1 < extended_value)
							*ALUresult = 1;
						else
							*ALUresult = 0;
					}
					else
					{
						if(data1 < data2)
							*ALUresult = 1;
						else
							*ALUresult = 0;
					}
					return 0;
				}
				else if(funct == 100010)
				{
					if(ALUSrc == 1)
						*ALUresult = data1 - extended_value;
					else
						*ALUresult = data1 - data2;
					return 0;
				}
		default:
				return 1;
	}
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

