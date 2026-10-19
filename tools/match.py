"""Compatibility entry point; status is read-only and verify always builds the output."""
import sys
sys.dont_write_bytecode = True
from workflow import main

if __name__ == "__main__":
    raise SystemExit(main())
