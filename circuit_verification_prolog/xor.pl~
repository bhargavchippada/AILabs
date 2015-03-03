:- [general].
xor(A,B):-or(and(A,not(B)),and(not(A),B)).
xor([]):-false.
xor([A|B]):-xor(A, xor(B)).
