string matching has three algorithms, namely Naive, Rabin-Karp, Finite Automaton, Knuth-Morris-Pratt
differing in their preprocessing time and matching time. 
This table summarizes their respective complexity 

Algorithms         Preprocessing Time           Matching Time
--------------------------------------------------------------
   Naive                 0                       O((n-m+1)m)
Rabin-Karp              O(m)                     O((n-m+1)m)
Finite Automaton      O(m*sigma)                    O(n)
    KMP                 O(m)                        O(n)
--------------------------------------------------------------    