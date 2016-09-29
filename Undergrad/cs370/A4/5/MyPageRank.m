function [x] = MyPageRank(G,a)

[w,w] = size(G);

deg = [];

for i=1:w
    deg = [deg 1/(sum(G(:, i:i)))];
end

D = diag(deg);

P = G*D;
R = w;

e = ones(w, 1);
I = eye(w,w);

RHS = ((1-a)/R)*e;
LHS = (I-a*P);


x = bslashtx(LHS, RHS);


end

