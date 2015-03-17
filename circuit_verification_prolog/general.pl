not(A):- A, !, fail.
not(A).
verify(not,[L],B):- B, !, not(L).
verify(not,[L],B):- not(not(L)).

and(A,B):- A, !, B.
and([]).
and([A|B]):- and(A, and(B)).
verify(and,L,B):- B, !, and(L).
verify(and,L,B):- not(and(L)).

or(A,B):- A, !, true.
or(A,B):- B, !, true.
or([]):- false.
or([A|B]):- or(A, or(B)).
verify(or,L,B):- B, !, or(L).
verify(or,L,B):- not(or(L)).

xor(A,B):-or(and(A,not(B)),and(not(A),B)).
xor([]):-false.
xor([A|B]):-xor(A, xor(B)).

verify(xor,L,B):- B, !, xor(L).
verify(xor,L,B):- not(xor(L)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

in(N, X):- and(connected(A, in(N, X)), terminal(A)), !, signal(A).
in(N, X):- connected(A, in(N, X)), !, out(A).
 
out(X):- type(X, and), connected(A,in(1,X)), connected(B,in(2,X)), !, and(in(1,X), in(2, X)).
out(X):- type(X, and), write('circuit is open'),!.
out(X):- type(X, or), connected(A,in(1,X)), connected(B,in(2,X)), !, or(in(1,X), in(2, X)).
out(X):- type(X, or), write('circuit is open'),!.
out(X):- type(X, not), connected(A,in(1,X)), !, not(in(1,X)).
out(X):- type(X, not), write('circuit is open'),!.
out(X):- type(X, xor), connected(A,in(1,X)), connected(B,in(2,X)), !, xor(in(1,X), in(2, X)).
out(X):- type(X, xor), write('circuit is open'),!.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

increment(X,Y):-Y is X+1.

goal(A,X):-retractall(signal(_)),fn(A,1),!,check(X).
fn([], L).
fn([A|B],L):-A,!,assert(signal(L)), increment(L,L1), fn(B, L1).
fn([A|B],L):-increment(L,L1), fn(B, L1).
check(X):-not(xor(output,X)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


