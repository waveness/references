# -*- coding: utf-8 -*-
#
# OneEuroFilterComparator.py -
#
# Author: Nicolas Roussel (nicolas.roussel@inria.fr)

from OneEuroFilter import OneEuroFilter

import math

class OneEuroFilterComparator(object):

    def __init__(self):
        self.__clear()

    def __clear(self):
        self.source = "<unknown>"
        self.config = {}
        self.timestamps = []
        self.svalues = [] # signal
        self.nvalues = [] # noisy signal
        self.fvalues = [] # filtered signal
        self.Fvalues = [] # signal filtered with OneEuroFilter(**config), for comparison
        
    def load(self, filename):
        self.__clear()
        with open(filename) as fd:
            data = []
            for line in fd:
                if line.startswith("#SRC"):
                    self.source = line.strip()[5:]
                elif line.startswith("#CFG"):
                    self.config = eval(line.strip()[5:])
                elif line.startswith("#LOG"):
                    signature = line.strip()[5:]
                    if signature!='timestamp, signal, noisy, filtered':
                        print "Bad log format: '%s'"%signature
                else:
                    data.append(map(float, line.strip().split(',')))
            self.timestamps, self.svalues, self.nvalues, self.fvalues = zip(*data)
            f = OneEuroFilter(**self.config)
            for timestamp, noisy in zip(self.timestamps, self.nvalues):
                self.Fvalues.append(f(noisy, timestamp))

    def compare(self, epsilon=0.0):
        print "Comparing %d filtered values..."%len(self.timestamps)
        diffs = []
        for timestamp, filtered, reference in zip(self.timestamps, self.fvalues, self.Fvalues):
            diff = math.fabs(filtered-reference)
            if diff>epsilon:
                diffs.append((timestamp, filtered, reference, diff))
        if diffs:
            percentage = 100.0*len(diffs)/len(self.timestamps)
            print "Found %d significant differences (%f%%, epsilon=%e)"%(len(diffs),percentage,epsilon)
        else:
            print "Found no significant difference (epsilon=%e)"%epsilon

    def plot(self):
        fig = pyplot.figure()
        pyplot.plot(self.timestamps, self.nvalues, color="lightgrey", label="noisy")
        pyplot.plot(self.timestamps, self.svalues, color="black", label="signal")
        pyplot.plot(self.timestamps, self.fvalues, color="red", label=self.source)
        pyplot.plot(self.timestamps, self.Fvalues, color="blue", label="OneEuroFilter.py")
        pyplot.legend(loc="lower left")
        return fig

if __name__=="__main__":

    import sys
    import random
    
    comp = OneEuroFilterComparator()
    comp.load(sys.argv[1])
    comp.compare(float(sys.argv[2]))
    
    try:
        from matplotlib import pyplot
        comp.plot()
        pyplot.show()
    except ImportError:
        print "matplotlib missing, can't plot"
