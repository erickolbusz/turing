template = "machine[{n}].move0 = {m0};\nmachine[{n}].write0 = {w0};\nmachine[{n}].next0 = {n0};\nmachine[{n}].move1 = {m1};\nmachine[{n}].write1 = {w1};\nmachine[{n}].next1 = {n1};\n\n"

def convert(s):
    '''converts e.g.
    A: 1,<,B/1,<,@
    B: 0,<,C/1,<,D
    C: 0,>,D/1,<,C
    D: 1,>,E/0,<,A
    E: 1,<,A/0,>,E

    to my form'''
    
    lines = s.split("\n")
    states = [line[0] for line in lines]
    states.append("@")
    transitions = [[half.split(",") for half in line[3:].split("/")] for line in lines]
    for i in range(len(states)-1):
        move0 = 1 if transitions[i][0][1]==">" else -1
        write0 = transitions[i][0][0]
        next0 = states.index(transitions[i][0][2])
        move1 = 1 if transitions[i][1][1]==">" else -1
        write1 = transitions[i][1][0]
        next1 = states.index(transitions[i][1][2])
        print(template.format(n=i, m0=move0, w0=write0, n0=next0, m1=move1, w1=write1, n1=next1))


s='''A: 1,<,C/0,>,B
B: 1,>,C/1,<,@
C: 0,<,D/0,>,D
D: 1,>,A/0,<,E
E: 1,<,D/1,<,E'''

convert(s)
