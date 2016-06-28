import random
topN = [10 ** 5, 10 ** 100, 10 ** 500]
for i in xrange(1, 43):
    x = random.randint(1, topN[0]);
    y = random.randint(1, topN[0]);
    if(x > y):
        print y,x;
    else:
        print x,y;

for i in xrange(1, 5):
    x = random.randint(1, topN[1]);
    y = random.randint(1, topN[1]);
    if(x > y):
        print y,x;
    else:
        print x,y;


for i in xrange(1, 2):
    x = random.randint(1, topN[2]);
    y = random.randint(1, topN[2]);
    if(x > y):
        print y,x;
    else:
        print x,y;
