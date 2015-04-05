notop(false).
notop(false,true).
notop(true,false).

orop(true,true).
orop(true,false).
orop(false,true).
orop(true,true,true).
orop(true,false,true).
orop(false,true,true).
orop(false,false,false).

andop(true,true).
andop(true,true,true).
andop(true,false,false).
andop(false,true,false).
andop(false,false,false).

xorop(A,B):-notop(B,X), notop(A,Y), andop(A,X,Z), andop(Y,B,W), orop(Z,W).
