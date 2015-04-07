:- [test].

terminal(1).
terminal(2).
connected(1,in(1,g3)).
connected(1,in(1,g2)).
connected(2,in(1,g1)).
connected(2,in(1,g4)).
connected(g1,in(2,g3)).
connected(g2,in(2,g4)).
connected(g3,in(1,g5)).
connected(g4,in(2,g5)).

type(g1,notop).
type(g2,notop).
type(g3,andop).
type(g4,andop).
type(g5,orop).

output :- out(g5).
