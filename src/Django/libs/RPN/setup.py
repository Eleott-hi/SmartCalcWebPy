# Available at setup time due to pyproject.toml
from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup
from glob import glob


__version__ = "3.0.0"

setup(
    version=__version__,
    ext_modules=[
        Pybind11Extension("PybindRPN",
                          #   ["main.cpp"],
                          sorted(glob("*.cc")),
                          define_macros=[('DEBUG', 1)],
                          ),
    ],
    cmdclass={"build_ext": build_ext},
)
