not(A):- A, !, fail.
not(A).

and(A,B):- A, !, B.
and([]).
and([A|B]):- and(A, and(B)).

or(A,B):- A, !, true.
or(A,B):- B, !, true.
or([]):- false.
or([A|B]):- or(A, or(B)).
