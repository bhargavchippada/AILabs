notop(false).
notop(true):-fail.

notop(false,true).
notop(true,false).

notop(A):- A, !, fail.
notop(A).

orop(true,true).
orop(true,false).
orop(false,true).
orop(false,false):-fail.

orop(true,true,true).
orop(true,false,true).
orop(false,true,true).
orop(false,false,false).

orop(A,B):- A, !, true.
orop(A,B):- B, !, true.	

andop(true,true).
andop(true,false):-fail.
andop(false,true):-fail.
andop(false,false):-fail.

andop(true,true,true).
andop(true,false,false).
andop(false,true,false).
andop(false,false,false).

andop(A,B):- A, !, B.

xorop(A,B):-notop(B,X), notop(A,Y), andop(A,X,Z), andop(Y,B,W), orop(Z,W).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

in(N, X):- andop(connected(A, in(N, X)), terminal(A)), !, signal(A).
in(N, X):- connected(A, in(N, X)), !, out(A).
 
out(X):- type(X, andop), connected(A,in(1,X)), connected(B,in(2,X)), !, andop(in(1,X), in(2, X)).
out(X):- type(X, andop), write('circuit is open'),!.
out(X):- type(X, orop), connected(A,in(1,X)), connected(B,in(2,X)), !, orop(in(1,X), in(2, X)).
out(X):- type(X, orop), write('circuit is open'),!.
out(X):- type(X, notop), connected(A,in(1,X)), !, notop(in(1,X)).
out(X):- type(X, notop), write('circuit is open'),!.
out(X):- type(X, xorop), connected(A,in(1,X)), connected(B,in(2,X)), !, xorop(in(1,X), in(2, X)).
out(X):- type(X, xorop), write('circuit is open'),!.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

increment(X,Y):-Y is X+1.

goal(A,X):-retractall(signal(_)),fn(A,1),!,check(X).
fn([], L).
fn([A|B],L):-A,!,assert(signal(L)), increment(L,L1), fn(B, L1).
fn([A|B],L):-increment(L,L1), fn(B, L1).
check(false):-notop(output),!.
check(true):-output,!.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
