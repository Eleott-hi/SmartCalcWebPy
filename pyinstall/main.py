# main.py
import importlib

def main():
    print("Main script is running")
    
    # Dynamically load the helper module
    helper_module = importlib.import_module('helper')
    helper_module.greet()

if __name__ == "__main__":
    main()
