#this script is used to format files with a wrong formatting to a CVS with ; separator 
import os 



print("Insert the file to format in CSV ")
filename=input()+".csv"



f = open(filename, "r")
print("The "+filename+"file is now opened")
newf=open("output.csv","w")


while(True):
       
    i=f.readline()
    
    if i=="": break

    newline=i.replace(",",";").replace("\n",";;\n")        
     
    newf.write(newline)     
    

f.close()
newf.close()
