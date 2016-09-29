/*
* sequential multiplier
* - multiplies two n-bit inputs (a and b) to produce 2*n-bit product d
* - parameter n and it's log_2 are defined here but can be overridden
*   in the testbench
* - log2n may be useful for declaring a counter
*/
module seq_mult(d, done, clk, a, b, go, reset);
  parameter n=4, log2n=2;
  output [2*n-1:0] d;
  output reg done;
	input clk;
	input [n-1:0] a, b;
	input go, reset;

	reg c = 0;
	reg [n-1:0] p, q, m;
	reg [log2n:0]count;
	
	reg [n:0] sum;
	
	always @(posedge clk, posedge reset)
	
		if(reset == 1) begin
			done <= 0;
		end
		
    else if(reset == 0) begin
			if(go) begin
				c <= 0;
        p <= 0;
				q <= a;
				m <= b;
				done <= 0;
				count <= n;
      end
						
			else if (!done) begin
			
				if (q[0] == 0) begin
					sum = 0 + p; 
				end
				else begin
					sum = m + p; 
				end
				
				c = sum[n];
				p = sum[n-1:0];
						
				{c,p,q} = {c,p,q} >> 1;
									
				count = count - 1;
				
				if (count == 0) begin
					done <= 1;
				end
				
			end
	
		end
		
	assign d = {p,q};
	
endmodule

// the testbench
module seq_mult_tb;
  reg clk, reset, go;
  reg [3:0] a, b;
  wire [7:0] d;
  wire done;
  
  // multiplier instantiation - the parameters n and log2n in seq_mult
  // can be overridden using the #(...) structure shown here
  seq_mult #(.n(4),.log2n(2)) m(.d(d), .done(done),
	  .clk(clk), .a(a), .b(b), .go(go),
	  .reset(reset));
  
  initial begin
    clk = 0; forever #5 clk = ~clk;
  end

  initial begin
    reset = 1;
    #10 reset = 0; a = 4'b0110; b = 4'b0110; go = 1; // 6 * 3
    #10 go = 0;
    wait(done==1)
	    ; // should see 18 (= 0x12) on d

    #10 a = 4'b0111; b = 4'b1010; go = 1; // 7 * 10
    #10 go = 0;
    wait(done==1)
	    #10 $stop ; // should see 70 (= 0x46) on d
  end
endmodule
