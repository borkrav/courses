JCC = javac

default: sender.class reciever.class packet.class ackReciever.class


sender.class: sender.java ackReciever.java
	$(JCC) $(JFLAGS) sender.java ackReciever.java

reciever.class: reciever.java
	$(JCC) $(JFLAGS) reciever.java

packet.class: packet.java
	$(JCC) $(JFLAGS) packet.java

clean: 
	$(RM) *.class
