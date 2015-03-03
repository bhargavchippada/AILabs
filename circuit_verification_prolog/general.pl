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

verify(xor,L,B):- B, !, xor(L).
verify(xor,L,B):- not(xor(L)).

