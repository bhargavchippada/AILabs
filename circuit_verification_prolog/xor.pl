:- [general].
xor(A,B):-or(and(A,not(B)),and(not(A),B)).
xor([]):-false.
xor([A|B]):-xor(A, xor(B)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

in(N, X):- and(connected(A, in(N, X)), terminal(A)), !, signal(A).
in(N, X):- connected(A, in(N, X)), !, out(A).
 
out(X):- type(X, and), !, and(in(1,X), in(2, X)).
out(X):- type(X, or), !, or(in(1,X), in(2, X)).
out(X):- type(X, not), !, not(in(1,X)).
out(X):- type(X, xor), !, xor(in(1,X), in(2, X)). 

terminal(a).
terminal(b).
connected(a,in(1,g3)).
connected(a,in(1,g2)).
connected(b,in(1,g1)).
connected(b,in(1,g4)).
connected(g1,in(2,g3)).
connected(g2,in(2,g4)).
connected(g3,in(1,g5)).
connected(g4,in(2,g5)).
type(g1,not).
type(g2,not).
type(g3,and).
type(g4,and).
type(g5,or).

signal(a).
signal(b).
