f16 = [[long(i) for i in line.split("\t")] for line in open("16/lengths.txt").read().strip().split("\n")]
f19 = [[long(i) for i in line.split("\t")] for line in open("19/lengths.txt").read().strip().split("\n")]

step16 = [i[0] for i in f16]
len16 = [i[1] for i in f16]
step19 = [i[0] for i in f19]
len19 = [i[1] for i in f19]

#locate flat parts of 16
i = 0
while i < len(f16)-1:
    if len16[i] == len16[i+1]:
        #identify left and right bounds
        left = step16[i]
        value = len16[i]
        while len16[i+1] == value:
            i += 1
        right = step16[i]

        #now find the same in 19
        #seems to be 19 = 16 - 2
        value19 = value-2
        js = [j for j in range(len(f19)) if len19[j] == value19]
        print "HNR16 Steps %d to %d:\t%d"%(left,right,value)
        if len(js) == 0:
            print "No match in HNR19\n"
        else:
            print "HNR19 Steps %d to %d:\t%d\n"%(step19[min(js)],step19[max(js)],value19)
    else:
        i += 1
