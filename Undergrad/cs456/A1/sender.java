import java.io.FileReader;
import java.io.IOException;
import java.util.*; 
import java.io.*; 
import java.net.*; 
import java.util.concurrent.*;

class sender{

	//the timeout value for the timer, in ms
	public static int timeoutValue = 10;

	//my window, implemented as a synchronized blocking bounded queue
	public static ArrayBlockingQueue<Integer> window = 
						new ArrayBlockingQueue<Integer>(10);

	//the object I'm using to synchronize
	public static Object lock = new Object();

	public static resendTimer rt = null;
	public static resendTimer noAck = null;
	public static volatile int nextPacket = 0;
	public static volatile int acked = 0; //keeps track of how many packets have been ACKed so far

	public static void main(String[] args) {



		//check and set command line arguments
		if (args.length != 4) {		
			System.err.println("Usage: sender <emulatorHost> <emulatorPort> <senderPort> <file>");		
			return;
		}

		String eHost = args[0];
		int ePort = Integer.parseInt(args[1]);
		int sPort = Integer.parseInt(args[2]);
		String file = args[3];

		//read in the file. Every element in contents holds 500 chars
		ArrayList<String> contents = readFile(file);


		try {

			//the writer for the log
			BufferedWriter seqnumLog = new BufferedWriter(new FileWriter("seqnum.log"));

			DatagramSocket serverSocket = new DatagramSocket(sPort); 

			InetAddress IPAddress = InetAddress.getByName(eHost);
		
			//starts a new thread to recieve acks
			new ackReciever(serverSocket);

 			byte[] sendData = new byte[1024]; 

			boolean done = false;

			while (!done){

				//need synchronization here, as only one thread at a time should be modifying 
				//the window queue
				synchronized (lock){

					//check if the window queue can accept the next packet. If not, it's full
					if (nextPacket < contents.size() && window.offer(nextPacket%32)){

						seqnumLog.write(Integer.toString(nextPacket%32) + "\n");

						//start timer, if it hasn't been started before
						if (rt == null) rt = new resendTimer(timeoutValue);

						//send the packet
						packet data = packet.createPacket(nextPacket,contents.get(nextPacket));
						sendData = data.getUDPdata();

						DatagramPacket sendPacket = 
			 								new DatagramPacket(sendData, sendData.length, IPAddress, ePort); 

			 			serverSocket.send(sendPacket);

						nextPacket++;
					}

					//if everything has been sent and acked
					else if (acked == contents.size()){
						rt.cancelTimer();	
						
						//send the EOT packet and quit
						packet data = packet.createEOT(0);

						sendData = data.getUDPdata();

						DatagramPacket sendPacket = 
			 								new DatagramPacket(sendData, sendData.length, IPAddress, 
			 			ePort); 

			 			serverSocket.send(sendPacket);
					
						done = true;
						seqnumLog.close();
					}

				}
			}
	

		} catch (Exception e){
			e.printStackTrace();
		}

	}


	public static ArrayList<String> readFile(String file) {

		//Note, this code assumes default ASCII encoding

		ArrayList<String> contents = new ArrayList<String>();
		FileReader input = null;

		String p = null;
		int counter = 0;		


		try {
			//read in the file, 500 charecters at a time, buffering results into contents array
			input = new FileReader(file);
			int c;
			while((c= input.read()) != -1){
				
				if (p == null) p = String.valueOf((char) c);
 				else p+=	String.valueOf((char) c);

				counter++;

				if (counter == 500){
					contents.add(p);
					p = null;
					counter = 0;
				}
			}

			contents.add(p);
		
		} catch (Exception e) {
			e.printStackTrace();
		}finally {
			if (input != null){
				try { 
					input.close();
				} catch (Exception e){
					e.printStackTrace();
				}
			}
		}
		return contents;
	}

}
