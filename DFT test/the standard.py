#
# the standard.py
#

# including lib for dft
import numpy as np
# including lib for generating pseudo random numbers
from random import random as rnd

# define the function of 1 argument
def generate_sequence(n):
    """ 
    generates sequence of numbers in  [0.0, 1.0)
    with length 'n' and returns 'np.array' of them
    """
    # result array
    result = np.array([],dtype=np.double) 
    # reserving memory
    result.resize(n)
    # repeat for each i = 0, 1, 2, ..., n-1
    for i in range(n):
        # assign array item to random number
        result[i] = rnd()
    # return result array
    return result

# define the function of 3 arguments    
def generate_test(test_amount, n, filename):
    """
    creates file 'filename' and writes to 
    it 'testamount'*2 strings of 'n' elements
    alternating source samples and resulting DFT
    """
    # open the file 
    with open(filename, 'w') as f:
        # for each i = 0, 1, 2, ..., 'test_amount'-1
        for i in range(test_amount):
            # get sequence of random numbers
            s = generate_sequence(n)

            # convert numbers to the strings
            # and write it to string with space separtion
            string = ' '.join(map(str,s))

            # write a line
            f.write(string)
            f.write('\n')

            # calculate DFT using library Fast 
            # Fourier transform function
            dft = np.absolute(np.fft.fft(s))

            # convert numbers to the strings
            # and write it to string with space separtion
            string = ' '.join(map(str,dft))

            # write a line
            f.write(string)
            f.write('\n')

# call the function
""" 
    create file 'text.txt' in current 
    path and write 100 numbers sequences
    DFT's with length 1000 to it
"""
generate_test(100,1000,'./test.txt')
