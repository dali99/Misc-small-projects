import math

def f(m, s, x):
  fraction = 1/(math.sqrt(2*math.pi)*s)
  brackets = -(1.0/2.0)*((x-m)/s)**2
  return fraction*math.exp(brackets)
  
print f(0.0, 2.0, 1.0)
