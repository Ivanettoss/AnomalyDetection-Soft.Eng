# Software-Engineering-
Software Engineering project : Anomaly Detection for the year 2023/204  

ToDo   
- Aprire una stream Redis per ogni campo trovato e delegare il compito di calcolare la media e la deviazione standard per quel campo   
- Tutte le stream Redis salveranno i valori calcolati in un DB composto dai campi (Nome_Campo; Media; Dev_Standard) ad es. (CO2; 16.1; 0.4)   

Commit 3 - Log   
Il nostro makefile chiama i makefile di con2db e con2redis/src, tutti builda correttamente, anche se faccio make clean dal nostro file cancella i file ".o" buildati nelle sottocartelle, sistemate anche le librerie e le flag, riusciamo a trovare sia libpq-fe.h che i file di redis (bisogna installare con sudo apt install libhiredis-dev)   


