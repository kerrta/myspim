#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{

}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	int i, retval;
	
	for (i = 0; i < MEMSIZE; i++)
	{
		if (PC == Mem[i])
		{
			*instruction = Mem[i];
			retval = 0;
			break;
		} else
			retval = 1;
	}
	
	return retval;	
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
	int halt_true = 0;
	switch(op)
	{
		// Add, Sub, And, Or, Slt, Sltu
		case 0b000000:
			controls->ALUOp = 111;
			controls->MemRead = 0;
			controls->MemWrite = 0;
			controls->RegWrite = 1;
			controls->RegDst = 1;
			controls->Jump = 2;
			controls->Branch = 2;
			controls->MemtoReg = 0;
			controls->ALUsrc = 0;
			break;
		// Lw
		case 0b100011:
			controls->ALUOp = 000;
			controls->MemRead = 1;
			controls->MemWrite = 0;
			controls->RegWrite = 1;
			controls->RegDst = 0;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemtoReg = 1;
			controls->ALUsrc = 1;
			break;
		// Sw
		case 0b101011:
			controls->ALUOp = 000;
			controls->MemRead = 0;
			controls->MemWrite = 1;
			controls->RegWrite = 0;
			controls->RegDst = 0;
			controls->Jump = 2;
			controls->Branch = 2;
			controls->MemtoReg = 1;
			controls->ALUsrc = 1;
			break;
		// Beq
		case 0b000100:
			controls->ALUOp = 001;
			controls->MemRead = 0;
			controls->MemWrite = 0;
			controls->RegWrite = 0;
			controls->RegDst = 0;
			controls->Jump = 2;
			controls->Branch = 1;
			controls->MemtoReg = 0;
			controls->ALUsrc = 1;
			break;
		// Addi
		case 0b001000:
			controls->ALUOp = 000;
			controls->MemRead = 0;
			controls->MemWrite = 0;
			controls->RegWrite = 1;
			controls->RegDst = 0;
			controls->Jump = 2;
			controls->Branch = 2;
			controls->MemtoReg = 0;
			controls->ALUsrc = 1;
			break;
		// Lui
		case 0b001111:
			controls->ALUOp = 000;
			controls->MemRead = 1;
			controls->MemWrite = 0;
			controls->RegWrite = 1;
			controls->RegDst = 0;
			controls->Jump = 2;
			controls->Branch = 2;
			controls->MemtoReg = 1;
			controls->ALUsrc = 1;
			break;
		// Slti
		case 0b001010:
			controls->ALUOp = 010;
			controls->MemRead = 0;
			controls->MemWrite = 0;
			controls->RegWrite = 1;
			controls->RegDst = 0;
			controls->Jump = 2;
			controls->Branch = 2;
			controls->MemtoReg = 0;
			controls->ALUsrc = 1;
			break;
		// Sltiu
		case 0b001001:
			controls->ALUOp = 010;
			controls->MemRead = 0;
			controls->MemWrite = 0;
			controls->RegWrite = 1;
			controls->RegDst = 0;
			controls->Jump = 2;
			controls->Branch = 2;
			controls->MemtoReg = 0;
			controls->ALUsrc = 1;
			break;
		// J
		case 0b000010:
			controls->ALUOp = 000;
			controls->MemRead = 2;
			controls->MemWrite 2;
			controls->RegWrite = 2;
			controls->RegDst = 2;
			controls->Jump = 1;
			controls->Branch = 2;
			controls->MemtoReg = 2;
			controls->ALUsrc = 0;
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

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
	if (MemRead == 1)
	{
		*memdata = Mem[ALUresult];
	} else
	{
		return 1;
	}


	if (MemWrite == 1)
	{
		Mem[ALUresult] = data2;
	} else
	{
		return 1;
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
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
	unsigned tempPC = *PC;
	*PC += 4;

	extended_value = extended_value << 2;

	PC += extended_value;

	if (Branch == 0 || Jump == 0)
	{
		PC = tempPC;
	}
}
