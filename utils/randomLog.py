# voglio fare una funzione che chiede il numero di campi e il numero di entry e genera un csv randomico con valori da analizzare
# il file sarà così pronto per il sistema di AnomalyDetection

import random
import os

def main():
    print("This program creates a random csv file")
    # l'utente deve inserire il numero di campi n
    fieldsQuantity = input("Please input how many fields you want to generate\n")
    while not fieldsQuantity.isdigit():
        fieldsQuantity = input("Invalid number, try again\n")
    fieldsQuantity = int(fieldsQuantity)
    # l'utente inserisce il numero di entry
    entryQuantity = input("Please input how many entries you want to generate\n")
    while not entryQuantity.isdigit():
        entryQuantity = input("Invalid number, try again\n")
    entryQuantity = int(entryQuantity)
    # viene aperto un file random.txt in scrittura
    cur_dir = os.getcwd()
    file = open(cur_dir + "/random.csv", "w")
    s = ""
    ref = []
    refString = ""
    for i in range(fieldsQuantity):
        s += "FIELD_" + str(i+1) + ";"
        # genero i primi valori che mi faranno da riferimento
        elt = random.randint(0,100000)
        ref.append(elt)
        refString += str(elt) + ";"
    # viene scritta questa stringa
    file.write(s + "\n" + refString + "\n")
    # numero di entry volte
    for i in range(entryQuantity):
        # n volte
        temp = ""
        for j in range(fieldsQuantity):
            # genera un numero flutt (0,100)
            flutt = random.randint(0, 100)
            if flutt < 5:
            # se flutt < 5
                sign = random.randint(0,1)
                if sign == 0:
                    # guasto in positivo, ovvero il ref[j] + tra il 20 e il 70 % in più
                    temp += str(random.randint(int(ref[j] + ref[j]*2), int(ref[j] + ref[j]*3))) + ";"
                else:
                    # guasto in negativo
                    temp += str(random.randint(int(- ref[j] - ref[j]*0.07), int(- ref[j] - ref[j]*0.02))) + ";"
            # else
            else:
                # genera un valore nel range del 10% di prima sotto e sopra SOLO se non c'è stata una anomalia
                temp += str(random.randint(int(ref[j] - ref[j] * 0.01), int(ref[j] + ref[j] * 0.01))) + ";"
                # aggiungilo
        file.write(temp + "\n")
    file.close()
    print("\nDONE!\n")
    return 0

if __name__ == "__main__":
    main()  
    