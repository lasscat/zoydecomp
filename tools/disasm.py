"""Small Capstone 5 adapter; register fields and instruction order are retained."""
import ctypes as C
import ctypes.util


class Insn(C.Structure):
    _fields_ = [("id", C.c_uint), ("address", C.c_uint64), ("size", C.c_uint16),
                ("bytes", C.c_ubyte * 24), ("mnemonic", C.c_char * 32),
                ("op_str", C.c_char * 160), ("detail", C.c_void_p)]


def decode(data, address, mode):
    if mode not in ("arm", "thumb"):
        raise ValueError("unknown instruction mode")
    lib = C.CDLL(ctypes.util.find_library("capstone") or "libcapstone.so.5")
    lib.cs_version.argtypes = [C.POINTER(C.c_int), C.POINTER(C.c_int)]
    major, minor = C.c_int(), C.c_int()
    lib.cs_version(C.byref(major), C.byref(minor))
    if major.value != 5:
        raise ValueError("Capstone 5 required by this ABI adapter")
    lib.cs_open.argtypes = [C.c_int, C.c_int, C.POINTER(C.c_size_t)]
    lib.cs_disasm.argtypes = [C.c_size_t, C.c_void_p, C.c_size_t, C.c_uint64,
                             C.c_size_t, C.POINTER(C.POINTER(Insn))]
    lib.cs_disasm.restype = C.c_size_t
    lib.cs_free.argtypes = [C.POINTER(Insn), C.c_size_t]
    lib.cs_close.argtypes = [C.POINTER(C.c_size_t)]
    handle = C.c_size_t()
    if lib.cs_open(0, 16 if mode == "thumb" else 0, C.byref(handle)):
        raise ValueError("Capstone open failed")
    ptr = C.POINTER(Insn)()
    try:
        count = lib.cs_disasm(handle.value, data, len(data), address, 0, C.byref(ptr))
        result = [(i.address, bytes(i.bytes[:i.size]), i.mnemonic.decode(),
                   i.op_str.decode()) for i in ptr[:count]]
        if sum(len(i[1]) for i in result) != len(data):
            raise ValueError("undecodable bytes; code/data boundaries require review")
        return result
    finally:
        if ptr:
            lib.cs_free(ptr, count)
        lib.cs_close(C.byref(handle))
