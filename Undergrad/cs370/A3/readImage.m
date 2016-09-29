I = imread('catBW.jpg');
I = im2double(I);


[A, drop] = Compress(I, 0);
[B, drop] = Compress(I, 0.009);
[C, drop] = Compress(I, 0.015);
[D, drop] = Compress(I, 0.060);

subplot(2,2,1);imshow(A);title('tol 0, drop 0');
subplot(2,2,2);imshow(B);title('tol 0.009, drop 0.4');
subplot(2,2,3);imshow(C);title('tol 0.015, drop 0.5');
subplot(2,2,4);imshow(D);title('tol 0.060, drop 0.7');



erra = sqrt(((mean2(I-A))^2)/((mean2(I))^2));
errb = sqrt(((mean2(I-B))^2)/((mean2(I))^2));
errc = sqrt(((mean2(I-C))^2)/((mean2(I))^2));
errd = sqrt(((mean2(I-D))^2)/((mean2(I))^2));



errors = [erra, errb, errc, errd];
drops = [0, 0.4, 0.5, 0.7];

plot(drops,errors); xlabel('Drop Ratio'); ylabel('NMSE'); title('NMSE vs Drop Ratio')

