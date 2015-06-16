#! /usr/bin/env python2.5
# -*- coding:utf-8 -*-

import pylab
import sys
import numpy

def func(x, X, Y):
	sum = 0
	k = len(X)
	for j in range(0, k):
		temp = 1
		for i in range(0, k):
			if i != j:
				temp = temp * (x - X[i])/(X[j] - X[i])
		sum = sum + temp*Y[j]
	return sum	
	

def show (X, Y, xlabel, ylabel, title):
	B = numpy.arange(X[0], X[-1], len(X)/100.0)
	K = [func(x, X, Y) for x in B]	
	pylab.plot(B, K)
	pylab.title(title)
	pylab.ylabel(ylabel)
	pylab.xlabel(xlabel)
	pylab.grid(True)
	pylab.show()

def graph1():
	X = []	
	Y = []

	for i in sys.argv[1:]:
		B = open(i, 'r')
		L = B.readlines()
		Y.append(max([float((a.split(':')[-1])[1:-1]) for a in L]))
		X.append(int(i.split('/')[-1][0:-5]))

	print X
	print Y
	show(X, Y, 'Range (Metros)', 'Tempo medio de duracao (minutos)', ' ')				

def graph2():
	X = []
	Y = []

	for i in sys.argv[1:]:
		B = open(i, 'r')
		L = B.readlines()
		Y.append(max([int((x.split("->"))[1].split('|')[0]) for x in L]))
		X.append(int(i.split('/')[-1][0:-5]))
	print X
	print Y
	show(X, Y, 'Range (metros)', 'Maior quantidade de componentes', ' ')

def graph3():
	X = []
	Y = []

	for i in sys.argv[1:]:
		B = open(i, 'r')
		Y.append(float((B.readlines()[-1].split(':')[-1])[1:-1]))
		X.append(int(i.split('/')[-1][0:-5]))
	print X
	print Y
	show(X, Y, 'Range (metros)', 'Tempo medio do maior componente', ' ');


if __name__ == "__main__":
	graph3()
