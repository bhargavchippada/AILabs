not(A):- A, !, fail.
not(A).

and(A,B):- A, !, B.
 
or(A,B):- A, !, true.
or(A,B):- B, !, true.

xor(A,B):-or(and(A,not(B)),and(not(A),B)).
