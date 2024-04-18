# the function asks for an entry and a fields number and generates a random CSV
# The file created is ready to be analyzed by AnomalyDetection

import random
import os
fluttValue=5
def main():
    print("This program creates a random csv file")
   
    fieldsQuantity = input("Please input how many fields you want to generate\n")

    while not fieldsQuantity.isdigit():
        fieldsQuantity = input("Invalid number, try again\n")

    fieldsQuantity = int(fieldsQuantity)
    entryQuantity = input("Please input how many entries you want to generate\n")

    while not entryQuantity.isdigit():
        entryQuantity = input("Invalid number, try again\n")

    entryQuantity = int(entryQuantity)
    
    cur_dir = os.getcwd()
    file = open(cur_dir + "/random.csv", "w")
    s = ""
    ref = []
    refString = ""

    for i in range(fieldsQuantity):
        s += "FIELD_" + str(i+1) + ";"
        
        elt = random.randint(0,100000)
        ref.append(elt)
        refString += str(elt) + ";"
    
    file.write(s + "\n" + refString + "\n")

    for i in range(entryQuantity):
        temp = ""
        for j in range(fieldsQuantity):
           
            flutt = random.randint(0, 100)
            if flutt < fluttValue:
          
                sign = random.randint(0,1)
                if sign == 0:
                   
                    temp += str(random.randint(int(ref[j] + ref[j]*2), int(ref[j] + ref[j]*3))) + ";"
                else:
                  
                    temp += str(random.randint(int(- ref[j] - ref[j]*0.07), int(- ref[j] - ref[j]*0.02))) + ";"
            
            else:
              
                temp += str(random.randint(int(ref[j] - ref[j] * 0.01), int(ref[j] + ref[j] * 0.01))) + ";"
                
        file.write(temp + "\n")
    file.close()
    print("\nDONE!\n")
    return 0

if __name__ == "__main__":
    main() 
