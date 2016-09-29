// name: Boris Kravchenko
// uwuserid: bkravche
// compiler: ModelSim
// pipelined?: No
module w450(mem_wr_data, mem_wr_addr, mem_wr_en, mem_rd_data1, mem_rd_addr1,
	mem_rd_data2, mem_rd_addr2, reset, clk);
	parameter n=8;
	output [n-1:0] mem_wr_data;
	output [n-1:0] mem_wr_addr;
	output mem_wr_en;
	input [n-1:0] mem_rd_data1;
	output [n-1:0] mem_rd_addr1;
	input [n-1:0] mem_rd_data2;
	output [n-1:0] mem_rd_addr2;
	input reset;
	input clk;

	parameter [2:0]
		st_if  = 3'b000,
		st_id  = 3'b001,
		st_l1  = 3'b010,
		st_l2  = 3'b011,
		st_ex  = 3'b100,
		st_wb  = 3'b101;

	reg[2:0] state;

	// processor regs
	reg[n-1:0] PC; // program counter
	reg[n-1:0] IR; // instruction register
	reg[n-1:0] REG [3:0]; // general-purpose registers r0-r3

	//decoded instruction
	reg[2:0] opcode;
	reg[1:0] reg1;
	reg[1:0] reg0;
	reg[0:0] dst;
	
	reg[n-1:0] dataFromMemory; //store memory loaded here
	reg[0:0] memoryRead; //boolean flag
	
	reg[n-1:0] dataToMemory; //store memory to be written here
	reg[n-1:0] addressToWrite; //store memory to be written here
	reg[0:0] memoryWrite; //boolean flag

	//hook up outputs to registers
	reg[n-1:0] rd_addr;
	reg[n-1:0] wr_addr;
	reg[n-1:0] wr_data;
	reg wr_en;

	assign mem_rd_addr2 = rd_addr;
	assign mem_wr_addr = wr_addr;
	assign mem_wr_data = wr_data;
	assign mem_wr_en = wr_en;

	assign mem_rd_addr1 = PC; // read port 1 is for instructions

	// opcodes for various instructions
	parameter add = 3'b000;
	parameter addi = 3'b001;
	parameter sub = 3'b010;
	parameter subi = 3'b011;
	parameter mov = 3'b100;
	parameter movi = 3'b101;
	parameter beq = 3'b110;
	parameter blt = 3'b111;
	
	
	// useful for indexing in IR - modify as needed...
	parameter ir_opcode_hi = 7;
	parameter ir_opcode_lo = 5;
	parameter ir_reg1_hi = 4;
	parameter ir_reg1_lo = 3;
	parameter ir_reg0_hi = 2;
	parameter ir_dst = 0;
	parameter ir_reg0_lo = 1;

	//Pipeline:
	//IF -> ID -> L1 -> L2 -> EX -> WB
	
	
	always@(posedge clk or posedge reset) begin // stages
		if(reset) begin
			state <= st_if;
			PC <= 8'h 00;
		end
		else
		case(state)
			st_if: begin
				//INSTRUCTION FETCH
				IR <= mem_rd_data1;
				PC <= PC + 1;
				memoryRead <= 0;
				memoryWrite <= 0;
				state <= st_id;
				wr_en <= 0;
			end

			st_id: begin
				//INSTRUCTION DECODE
				//decode the instruction
				opcode <= IR[ir_opcode_hi:ir_opcode_lo];
				reg1 <= IR[ir_reg1_hi:ir_reg1_lo];
				reg0 <= IR[ir_reg0_hi:ir_reg0_lo];
				dst <= IR[ir_dst:ir_dst];

				state <= st_l1; 
				
			end
			
			st_l1: begin
				//LOAD1
				//this stage sends request to memory
						
				if (opcode == add || opcode == sub || opcode == mov) begin
					// if R0 is in reg0 then I have to load data
					if (reg0 == 0) begin
					//assign read port 2 to R0
						rd_addr <= REG[0];	
						memoryRead <= 1;
					end				
				end
				
				//else need to load next line for instructions that use immediate
				else begin
					rd_addr <= PC;
					PC <= PC + 1;
					dataFromMemory <= mem_rd_data1;
					//memoryRead <= 1'b1;
				end
				
				state <= st_l2;
			
			end
			
			st_l2: begin
				//LOAD2
				//this stage receives data from memory	
				
				if(memoryRead == 1) begin
					dataFromMemory <= mem_rd_data2;
				end
	
				state <= st_ex;
			
			end
			
			st_ex: begin
				//EXECUTE
				//All the instructions are implemented here
			
				if(opcode == add) begin
					if(dst == 0) begin
						if(reg0 == 0) begin
							dataToMemory <= dataFromMemory + REG[reg1];
							addressToWrite <= REG[0];
							memoryWrite <= 1;
						end
						else begin
							REG[reg0] <= REG[reg0] + REG[reg1];
						end
					end
					else if(dst == 1) begin
						if(reg0 == 0) begin
							REG[reg1] <= REG[reg1] + dataFromMemory;
						end
						else begin
							REG[reg1] <= REG[reg1] + REG[reg0];
						end
					end
				end
				
				if(opcode == addi) begin
					REG[reg1] <= REG[reg1] + dataFromMemory;
				end
			
				if(opcode == sub) begin
					if(dst == 0) begin
						if(reg0 == 0) begin
							dataToMemory <= dataFromMemory - REG[reg1];
							addressToWrite <= REG[0];
							memoryWrite <= 1;
						end
						else begin
							REG[reg0] <= REG[reg0] - REG[reg1];
						end
					end
					else if(dst == 1) begin
						if(reg0 == 0) begin
							REG[reg1] <= REG[reg1] - dataFromMemory;
						end
						else begin
							REG[reg1] <= REG[reg1] - REG[reg0];
						end
					end
				end
				
				if(opcode == subi) begin
					REG[reg1] <= REG[reg1] - dataFromMemory;
				end

				if(opcode == mov) begin
					if(dst == 0) begin
						if(reg0 == 0) begin
							dataToMemory <= REG[reg1];
							addressToWrite <= REG[0];
							memoryWrite <= 1;
						end
						else begin
							REG[reg0] <= REG[reg1];
						end
					end
					else if(dst == 1) begin
						if(reg0 == 0) begin
							REG[reg1] <= dataFromMemory;
						end
						else begin
							REG[reg1] <= REG[reg0];
						end
					end
				end
					
				if(opcode == movi) begin
					REG[reg1] <= dataFromMemory;
				end
			
				if(opcode == beq) begin
					if(REG[reg1] == REG[reg0]) begin
						PC <= PC + dataFromMemory;
					end
				end
				
				if(opcode == blt) begin
					if(REG[reg1] < REG[reg0]) begin
						PC <= PC + dataFromMemory;
					end
				end
			
				state <= st_wb;
				
			end
			
			st_wb: begin
				//WRITEBACK
				//Writes back to memory
				if(memoryWrite == 1) begin
					wr_en <= 1;
					wr_addr <= addressToWrite;
					wr_data <= dataToMemory;
				end
			
				state <= st_if;

			end
			
			default: state <= st_if;
		endcase
	end
endmodule
