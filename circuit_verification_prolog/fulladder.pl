:-[test].

terminal(1).
terminal(2).
terminal(3).

connected(1,in(1,g1)).
connected(1,in(1,g2)).
connected(2,in(2,g1)).
connected(2,in(2,g2)).
connected(3,in(2,g3)).
connected(3,in(2,g4)).
connected(g1,in(1,g3)).
connected(g1,in(1,g4)).
connected(g2,in(2,g5)).
connected(g4,in(1,g5)).

type(g1,xorop).
type(g2,andop).
type(g3,xorop).
type(g4,andop).
type(g5,orop).

output :- out(g5).



