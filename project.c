#include "spimcore.h"

/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
	unsigned temp;
	switch(ALUControl)
	{
		case 0:
				*ALUresult = A + B;
				break;
		case 1:
				*ALUresult = A - B;
				break;
		case 2:
				if(A < B)
					*ALUresult = 1;
				else
					*ALUresult = 0;
				break;
		case 3:
				if(A < B)
					*ALUresult = 1;
				else
					*ALUresult = 0;
				break;
		case 4:
				*ALUresult = A & B;
				break;
		case 5:
				*ALUresult = A | B;
				break;
		case 6:
				*ALUresult = B;
				*ALUresult <<= 16;
				break;
		case 7:
				*ALUresult = ~A;
				break;

		if (!*ALUresult)
			*Zero = 1;
	}

}

int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	PC = PC >> 2;

	if (PC >= 100000000000000)
		return 1;

	*instruction = Mem[PC];
	return 0;	
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
	*op = instruction >> 26;
	*r1 = (instruction << 6) >> 27;
	*r2 = (instruction << 11) >> 27;
	*r3 = (instruction << 16) >> 27;
	*funct = (instruction << 26) >> 26;
	*offset = (instruction << 16) >> 16;
	*jsec = (instruction << 6) >> 6;
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
	int halt_true = 0;

	switch(op)
	{
		// Add, Sub, And, Or, Slt, Sltu
		case 0:
			controls->ALUOp = 7;
			controls->MemRead = 0;
			controls->MemWrite = 0;
			controls->RegWrite = 1;
			controls->RegDst = 1;
			controls->Jump = 2;
			controls->Branch = 2;
			controls->MemtoReg = 0;
			controls->ALUSrc = 0;
			break;
		// Lw
		case 35:
			controls->ALUOp = 0;
			controls->MemRead = 1;
			controls->MemWrite = 0;
			controls->RegWrite = 1;
			controls->RegDst = 0;
			controls->Jump = 2;
			controls->Branch = 2;
			controls->MemtoReg = 1;
			controls->ALUSrc = 1;
			break;
		// Sw
		case 43:
			controls->ALUOp = 0;
			controls->MemRead = 0;
			controls->MemWrite = 1;
			controls->RegWrite = 0;
			controls->RegDst = 0;
			controls->Jump = 2;
			controls->Branch = 2;
			controls->MemtoReg = 1;
			controls->ALUSrc = 1;
			break;
		// Beq
		case 4:
			controls->ALUOp = 1;
			controls->MemRead = 0;
			controls->MemWrite = 0;
			controls->RegWrite = 0;
			controls->RegDst = 0;
			controls->Jump = 2;
			controls->Branch = 1;
			controls->MemtoReg = 0;
			controls->ALUSrc = 1;
			break;
		// Addi
		case 8:
			controls->ALUOp = 0;
			controls->MemRead = 0;
			controls->MemWrite = 0;
			controls->RegWrite = 1;
			controls->RegDst = 0;
			controls->Jump = 2;
			controls->Branch = 2;
			controls->MemtoReg = 0;
			controls->ALUSrc = 1;
			break;
		// Lui
		case 15:
			controls->ALUOp = 6;
			controls->MemRead = 0;
			controls->MemWrite = 0;
			controls->RegWrite = 1;
			controls->RegDst = 0;
			controls->Jump = 2;
			controls->Branch = 2;
			controls->MemtoReg = 0;
			controls->ALUSrc = 1;
			break;
		// Slti
		case 10:
			controls->ALUOp = 0;
			controls->MemRead = 0;
			controls->MemWrite = 0;
			controls->RegWrite = 1;
			controls->RegDst = 0;
			controls->Jump = 2;
			controls->Branch = 2;
			controls->MemtoReg = 0;
			controls->ALUSrc = 1;
			break;
		// Sltiu
		case 9:
			controls->ALUOp = 0;
			controls->MemRead = 0;
			controls->MemWrite = 0;
			controls->RegWrite = 1;
			controls->RegDst = 0;
			controls->Jump = 2;
			controls->Branch = 2;
			controls->MemtoReg = 0;
			controls->ALUSrc = 1;
			break;
		// J
		case 2:
			controls->ALUOp = 0;
			controls->MemRead = 2;
			controls->MemWrite = 2;
			controls->RegWrite = 2;
			controls->RegDst = 2;
			controls->Jump = 1;
			controls->Branch = 2;
			controls->MemtoReg = 2;
			controls->ALUSrc = 0;
			break;
		default:
			halt_true = 1;
	}

	return halt_true;
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
	unsigned temp = offset;
	int i;

	temp = temp >> 15;

	if (!temp)
	{
		*extended_value = offset | 0;
	} else 
	{
		temp = ~0;
		temp = temp << 16;
		temp += offset;
		*extended_value = temp;
	}
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

	int retval = 0;

	switch(ALUOp)
	{
		case 0:
				if(ALUSrc == 1)	
					ALU(data1, extended_value, ALUOp, ALUresult, Zero);
				else
					ALU(data1, data2, ALUOp, ALUresult, Zero);
				return retval;
		case 1:
				if(ALUSrc == 1)
					ALU(data1, extended_value, ALUOp, ALUresult, Zero);
				else
					ALU(data1, data2, ALUOp, ALUresult, Zero);
				return retval;
		case 2:
				if(ALUSrc == 1)
					ALU(data1, extended_value, ALUOp, ALUresult, Zero);
				else
					ALU(data1, data2, ALUOp, ALUresult, Zero);
				return retval;
		case 3:
				if(ALUSrc == 1)
					ALU(data1, extended_value, ALUOp, ALUresult, Zero);
				else
					ALU(data1, data2, ALUOp, ALUresult, Zero);
				return retval;
		case 4:
				if(ALUSrc == 1)
					ALU(data1, extended_value, ALUOp, ALUresult, Zero);
				else
					ALU(data1, data2, ALUOp, ALUresult, Zero);
				return retval;
		case 5:
				if(ALUSrc == 1)
					ALU(data1, extended_value, ALUOp, ALUresult, Zero);
				else
					ALU(data1, data2, ALUOp, ALUresult, Zero);
				return retval;
		case 6:
				if(ALUSrc == 1)
					ALU(data1, extended_value, ALUOp, ALUresult, Zero);
				else
					ALU(data1, data2, ALUOp, ALUresult, Zero);
				return retval;
		case 7:
				if(funct == 32)
				{
					ALUOp = 0;
					if(ALUSrc == 1)	
						ALU(data1, extended_value, ALUOp, ALUresult, Zero);
					else
						ALU(data1, data2, ALUOp, ALUresult, Zero);
					return retval;
				}
				else if(funct == 36)
				{
					ALUOp = 4;
					if(ALUSrc == 1)
						ALU(data1, extended_value, ALUOp, ALUresult, Zero);
					else
						ALU(data1, data2, ALUOp, ALUresult, Zero);
					return retval;
				}
				else if(funct == 37)
				{
					ALUOp = 5;
					if(ALUSrc == 1)
						ALU(data1, extended_value, ALUOp, ALUresult, Zero);
					else
						ALU(data1, data2, ALUOp, ALUresult, Zero);
					return retval;
				}
				else if(funct == 42)
				{
					ALUOp = 2;
					if(ALUSrc == 1)
						ALU(data1, extended_value, ALUOp, ALUresult, Zero);
					else
						ALU(data1, data2, ALUOp, ALUresult, Zero);
					return retval;
				}
				else if (funct == 43)
				{
					ALUOp = 3;
					if (ALUSrc == 1)
						ALU(data1, extended_value,ALUOp, ALUresult, Zero);
					else
						ALU(data1, data2, ALUOp, ALUresult, Zero);
					return retval;
				}
				else if(funct == 34)
				{
					ALUOp = 1;
					if(ALUSrc == 1)
						ALU(data1, extended_value, ALUOp, ALUresult, Zero);
					else
						ALU(data1, data2, ALUOp, ALUresult, Zero);
					return retval;
				}
				break;
		default:
			retval = 1;
	}

	return retval;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
	unsigned temp = ALUresult % 4;

	if (MemRead == 1)
	{
		if (temp != 0)
			return 1;
		*memdata = Mem[ALUresult / 4];
	}

	if (MemWrite == 1)
	{
		if (temp != 0)
			return 1;
		Mem[ALUresult / 4] = data2;
	}

	return 0;
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
	if (RegWrite == 1 && RegDst == 1)
	{
		if (MemtoReg == 0)
			Reg[r3]= ALUresult;
		else
			Reg[r3] = memdata;
	}

	if (RegWrite == 1 && RegDst == 0)
	{
		if (MemtoReg == 0)
			Reg[r2] = ALUresult;
		else
			Reg[r2] = memdata;
	}

	Reg[0] = 0;
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
	unsigned tempPC = *PC + 4, newJsec = tempPC;

	extended_value <<= 2;
	jsec <<= 2;
	newJsec >>= 28;
	newJsec <<= 28;

	newJsec += jsec;

	if (Branch == 2 && Jump == 2)
		*PC = tempPC;
	else if (Branch == 1 && Zero == 1)
	{
		*PC += extended_value;
		
		if (Jump == 0)
			return;
	}
	else if (Branch == 0 || Zero == 0)
	{	
		*PC = tempPC;
		return;
	}


	if (Jump == 1)
		*PC = newJsec;
}
