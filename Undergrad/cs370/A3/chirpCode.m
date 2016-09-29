load chirp;
y=y';


seg1=y(1:1500);
seg2=y(1501:3000);
seg3=y(3001:4700);
seg4=y(4701:6000);
seg5=y(6001:7800);
seg6=y(7801:9000);
seg7=y(9001:11200);
seg8=y(11201:13129);

N1 = length(seg1);
N2 = length(seg2);
N3 = length(seg3);
N4 = length(seg4);
N5 = length(seg5);
N6 = length(seg6);
N7 = length(seg7);
N8 = length(seg8);

Y1=fft(seg1);
Y2=fft(seg2);
Y3=fft(seg3);
Y4=fft(seg4);
Y5=fft(seg5);
Y6=fft(seg6);
Y7=fft(seg7);
Y8=fft(seg8);

f1=(0:floor(N1/2))*Fs/N1;
f2=(0:floor(N2/2))*Fs/N2;
f3=(0:floor(N3/2))*Fs/N3;
f4=(0:floor(N4/2))*Fs/N4;
f5=(0:floor(N5/2))*Fs/N5;
f6=(0:floor(N6/2))*Fs/N6;
f7=(0:floor(N7/2))*Fs/N7;
f8=(0:floor(N8/2))*Fs/N8;

pow1=abs(Y1(1:floor(N1/2)+1));
pow2=abs(Y2(1:floor(N2/2)+1));
pow3=abs(Y3(1:floor(N3/2)+1));
pow4=abs(Y4(1:floor(N4/2)+1));
pow5=abs(Y5(1:floor(N5/2)+1));
pow6=abs(Y6(1:floor(N6/2)+1));
pow7=abs(Y7(1:floor(N7/2)+1));
pow8=abs(Y8(1:floor(N8/2)+1));

subplot(4,2,1);
plot([f1;f1],[0*pow1;pow1],'c-',f1,pow1,'b.','linewidth',2,'markersize',1);
xlabel('Hz'); ylabel('power'); title('Segment 1');axis([2000 4000 0 30]);

subplot(4,2,2);
plot([f2;f2],[0*pow2;pow2],'c-',f2,pow2,'b.','linewidth',2,'markersize',1);
xlabel('Hz'); ylabel('power'); title('Segment 2');axis([2000 4000 0 30]);

subplot(4,2,3);
plot([f3;f3],[0*pow3;pow3],'c-',f3,pow3,'b.','linewidth',2,'markersize',1);
xlabel('Hz'); ylabel('power'); title('Segment 3');axis([2000 4000 0 30]);

subplot(4,2,4);
plot([f4;f4],[0*pow4;pow4],'c-',f4,pow4,'b.','linewidth',2,'markersize',1);
xlabel('Hz'); ylabel('power'); title('Segment 4');axis([2000 4000 0 30]);

subplot(4,2,5);
plot([f5;f5],[0*pow5;pow5],'c-',f5,pow5,'b.','linewidth',2,'markersize',1);
xlabel('Hz'); ylabel('power'); title('Segment 5');axis([2000 4000 0 30]);

subplot(4,2,6);
plot([f6;f6],[0*pow6;pow6],'c-',f6,pow6,'b.','linewidth',2,'markersize',1);
xlabel('Hz'); ylabel('power'); title('Segment 6');axis([2000 4000 0 30]);

subplot(4,2,7);
plot([f7;f7],[0*pow7;pow7],'c-',f7,pow7,'b.','linewidth',2,'markersize',1);
xlabel('Hz'); ylabel('power'); title('Segment 7');axis([2000 4000 0 30]);

subplot(4,2,8);
plot([f8;f8],[0*pow8;pow8],'c-',f8,pow8,'b.','linewidth',2,'markersize',1);
xlabel('Hz'); ylabel('power'); title('Segment 8');axis([2000 4000 0 30]);


