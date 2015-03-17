:- [general].

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

type(g1,not).
type(g2,not).
type(g3,and).
type(g4,and).
type(g5,or).

output :- out(g5).
