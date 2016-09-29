import java.io.*; 
import java.net.*; 
import java.util.concurrent.*;
import java.util.Timer;
import java.util.TimerTask;

class resendTimer {
    Timer timer;

	//this is a regular timer that fires after n miliseconds
	public resendTimer(int n) {
		timer = new Timer();
		timer.schedule(new resendTask(), n);
	}

	//this is a "beeping" timer that fires every interval milliseconds after n milliseconds have 	passed
	public resendTimer (int n, int interval){
		timer = new Timer();
		timer.scheduleAtFixedRate(new resendTaskAndRepeat(), n, interval);
	}

	public void cancelTimer(){
		timer.cancel();
	}	

	class resendTask extends TimerTask {
		public void run() {
			
			//need synchronization to modify the window
			synchronized (sender.lock){
				sender.nextPacket -= sender.window.size();
				sender.window.clear();
			}

			timer.cancel(); //Terminate the timer thread
		}
	}

	class resendTaskAndRepeat extends TimerTask {
		public void run() {
			
			//need synchronization to modify the window
			synchronized (sender.lock){
				sender.nextPacket -= sender.window.size();
				sender.window.clear();
			}
		}
	}
}


class ackReciever implements Runnable {

	Thread t;
	private DatagramSocket serverSocket;

	//creates a new ackReciever thread
	ackReciever(DatagramSocket ss) {
		t = new Thread(this, "Ack Thread");
		serverSocket = ss;
		t.start(); 
	}

	public void run() {
		
		try {

			BufferedWriter ackLog = new BufferedWriter(new FileWriter("ack.log"));
     
			byte[] receiveData = new byte[1024]; 
			boolean done = false;

			while (!done){

				DatagramPacket receivePacket = 
			 			new DatagramPacket(receiveData, receiveData.length); 
	
				/*since receive blocks until it gets something, I put in a beeping timer here
					that is created before I get something and destroyed right after. This is in 
					case there's high network loss (p >= 0.8), so all acks from the reciever are lost. If 					that's the case, I should continuosly resend the window until something gets through. 					Note, if there reciever is not running, or if there's no network, the sender will 					keep trying forever
				*/

				sender.noAck = new resendTimer(2*sender.timeoutValue,2*sender.timeoutValue);

				serverSocket.receive(receivePacket);

				sender.noAck.cancelTimer();
				

				packet rec = packet.parseUDPdata(receiveData);

				//if I got an ACK
				if (rec.getType() == 0){

					int ack = rec.getSeqNum();

					ackLog.write(Integer.toString(ack) + "\n");

					//need synchronization to modify the window
					synchronized (sender.lock){

						//if the ACK I got is inside the window (therefore not stale)
						if (sender.window.contains(ack)){
						
							//remove all packets in the window that are before the ACKed packet
							while (sender.window.peek() != ack) {
									sender.window.take();
									sender.acked++;
							}
							sender.window.take();
							sender.acked++;

							//cancel the timer if there's nothing left in the window
							if (sender.window.isEmpty()){
								 sender.rt.cancelTimer();
							}

							//reset the timer if there's something else in the window
							else {
								sender.rt.cancelTimer();
								sender.rt = new resendTimer(sender.timeoutValue);
							}
						}

						else {
							//acking something out of the window, so ACK is stale and invalid, so I do nothing
						}
					}
				}

				//the EOT is ACKed so quit
				else if (rec.getType() == 2){
					done = true;
					ackLog.close();
				}
			
			}

		} catch (Exception e){
			e.printStackTrace();
		}


	}

}
