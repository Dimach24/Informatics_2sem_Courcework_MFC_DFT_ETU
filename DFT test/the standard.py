import numpy as np
from random import random as rnd

def generate_sequence(n):
    """ 
    generates sequence of numbers in  [0.0, 1.0)
    with length n and returns np.array of them
    """
    result = np.array([],dtype=np.double)
    result.resize(n)
    for i in range(n):
        result[i] = rnd()
    return result
    
def generate_test(test_amount, n, filename):
    """
    creates file 'name' and writes to 
    it 'testamount' pairs of 'n' elements -
    samples of the signal and DFT
    """
    with open(filename, 'w') as f:
        for i in range(test_amount):
            s = generate_sequence(n)
            string = ' '.join(map(str,s))
            f.write(string)
            f.write('\n')
            dft = np.absolute(np.fft.fft(s))
            string = ' '.join(map(str,dft))
            f.write(string)
            f.write('\n')
generate_test(100,1000,'./test.txt')
