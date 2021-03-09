
from ctypes import *
from ctypes import util

so_file = util.find_library("trinity")
trinity = CDLL(so_file)
trinity.sim.argtypes = [c_double, c_double, c_double, c_int] 
trinity.sim.restype = c_double;

success_ratio = trinity.sim(1000000, 40000, 0.15, 30);
print("{:.2%}".format(success_ratio));
