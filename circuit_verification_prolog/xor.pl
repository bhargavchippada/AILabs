:- [general].

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
