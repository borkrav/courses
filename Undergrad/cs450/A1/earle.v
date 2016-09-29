/* a xor b integrated with earle latch */
module xor_earle(output z, input a,b,c);

	assign z = (a&~b&c) | (~a&b&c) | (a&~b&z) | (~a&b&z) | (~c&z);

endmodule


/* testbench module */
module xor_earle_tb;
  reg a, b, c;
  wire out;

  xor_earle dut(out,a,b,c); //device under test

  initial begin
    a=0; b=0; c=1; // t0: z should be 0
    #5 a = 1; // t5: z should become 1
    #5 a = 0; // t10: z should become 0
    #5 c = 0;
    #5 a = 1;
    #5 c = 1; // t25: z should become 1
    #5 ;
  end

endmodule
