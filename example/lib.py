import ctypes
from ctypes import *
import numpy as np

so_file = "../bin/bus.so"
lib = CDLL(so_file)

# Declare the function signature
lib.solution.argtypes = [
    ctypes.POINTER(ctypes.POINTER(ctypes.c_int)),  # U argument type
    ctypes.POINTER(ctypes.POINTER(ctypes.c_int)),  # S argument type
    ctypes.c_int,  # n_users argument type
    ctypes.c_int  # n_seats argument type
]
lib.solution.restype = ctypes.POINTER(ctypes.c_int)  # Return type


def bus_sitter(U: list[list[int]], A: list[list[int]]) -> list[int]:
    sol = lib.solution(
        (ctypes.POINTER(ctypes.c_int) * len(U))(*[ctypes.cast((ctypes.c_int * len(row))(*row), ctypes.POINTER(ctypes.c_int)) for row in U]),
        (ctypes.POINTER(ctypes.c_int) * len(A))(*[ctypes.cast((ctypes.c_int * len(row))(*row), ctypes.POINTER(ctypes.c_int)) for row in A]),
        ctypes.c_int(len(U)),
        ctypes.c_int(len(A))
    )

    return [sol[i] for i in range(1, len(U))]
