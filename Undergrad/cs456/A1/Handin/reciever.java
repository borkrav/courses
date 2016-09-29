import java.io.*; 
import java.net.*; 

class reciever{

	public static void main(String[] args) {


		//check and set command line arguments
		if (args.length != 4) {		
			System.err.println("Usage: reciever <emulatorHost> <emulatorPort> <recieverPort> <file>");		
			return;
		}

		String eHost = args[0];
		int ePort = Integer.parseInt(args[1]);
		int rPort = Integer.parseInt(args[2]);
		String file = args[3];


		try {

			BufferedWriter arrivalLog = new BufferedWriter(new FileWriter("arrival.log"));

			DatagramSocket clientSocket = new DatagramSocket(rPort); 

			String result = ""; //this holds the charecters recieved so far

			InetAddress IPAddress = InetAddress.getByName(eHost);

			byte[] sendData = new byte[1024]; 
	 		byte[] receiveData = new byte[1024]; 

			int expectedSeq = 0;

			boolean done = false;

			while (!done) {

	 			DatagramPacket receivePacket = 
	 			new DatagramPacket(receiveData, receiveData.length); 

				clientSocket.receive(receivePacket); 

				packet rec = packet.parseUDPdata(receiveData);

				//if I got a data packet
				if (rec.getType() == 1){

					arrivalLog.write(Integer.toString(rec.getSeqNum()) + "\n");

					//if the sequence number is the one I expected
					if (expectedSeq%32 == rec.getSeqNum()){
					
						//append the data to the result string
						String s = new String(rec.getData());
						result += s;

						//send the ACK for the packet						
						packet ack = packet.createACK(expectedSeq);
						sendData = ack.getUDPdata();

						DatagramPacket sendPacket = 
	 									new DatagramPacket(sendData, sendData.length, IPAddress, ePort); 

	 					clientSocket.send(sendPacket); 
				
						expectedSeq++;

					}

					//unexpected sequence number
					else {

						//send ACK for the previous correct packet
						packet ack = packet.createACK(expectedSeq-1);

						sendData = ack.getUDPdata();

						DatagramPacket sendPacket = 
	 									new DatagramPacket(sendData, sendData.length, IPAddress, 
	 					ePort); 

	 					clientSocket.send(sendPacket); 

					}			
				}
				
				//if I got an EOT packet
				else if (rec.getType() == 2){

					//send an EOT packet
					packet data = packet.createEOT(0);
					sendData = data.getUDPdata();

					DatagramPacket sendPacket = 
		 								new DatagramPacket(sendData, sendData.length, IPAddress, ePort); 

			 		clientSocket.send(sendPacket);

					//finish
					done = true;

				}
	
			}

			//write the result string to the output file and close all writers
			BufferedWriter output = new BufferedWriter(new FileWriter(file));
			output.write(result);
			output.close();
			arrivalLog.close();

		} catch (Exception e){
			e.printStackTrace();
		}

	}
}

