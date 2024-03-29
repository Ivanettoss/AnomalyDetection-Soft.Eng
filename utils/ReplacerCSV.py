# programma che apre in file csv-like e lo converte usando come separatori ; 
# aggiunge alla fine di ogni riga un ;
import os

DEBUG = 0

def main(p, separator):
    
    if separator == ";":
        print("There is no need to replace anything, exiting...")
        return 0
    pathOutput = os.path.dirname(p) + "/output.csv"
    
    try:
        output = open(pathOutput, "w")
        
    except PermissionError:
        print("Permission Denied: unable to open " + pathOutput)
        return 1
    except OSError:
        print("Invalid argument: unable to open " + pathOutput)
        return 1

    with open(p, "r") as original:
        line = original.readline()
        while line and len(line)>1:
            line = line.replace(sep, ";").replace("\n", ";\n")
            if line.find("\n") == -1:
                line += ";"
            output.write(line)
            line = original.readline()
    output.close()
    print("\nDONE!\n")
    return 0


if __name__ == "__main__":
    print("The following program converts CSV files into files readable by our anomaly detection system.")
    print("\nPlease input file path")
    path = input()
    path = path.replace("\\", "/")
    path = path.replace("\"", "")
    sep = input("Input separator character currently used, it will be replaces with \";\"\n")
    main(path, sep)
    
    if DEBUG:
        with open(os.path.dirname(path) + "/output.csv", "r") as f:
            for line in f.readlines():
                print(line)
    input("Press any key to close program.")
    
