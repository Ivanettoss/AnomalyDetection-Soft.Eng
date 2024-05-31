## Descrizione generale
Il sistema di AnomalyDetection da noi sviluppato è organizzato in 3 componenti, un insieme di utils per normalizzare i dati 'csv' da fornire in input, e 5 monitor, di cui 3 agenti sul database postgres.   
Per il corretto funzionamento è necessario installare le seguenti librerie:   
- make
- g++
- postgresql
- redis
- libhiredis-dev
- libpq-dev

Si deve aggiungere un utente postgres così come specificato all'interno dei file main.h presenti dentro i componenti.   
Bisogna inizialmente eseguire ogni componente del sistema in maniera sequenziale con l'obiettivo di creare un modello di riferimento da utilizzare per i calcoli di anomalie da logs inseriti successivamente.   
La tabella delle medie viene usata attivamente nei calcoli delle anomalie riscontrate mentre le tabelle di covarianza sono consultabili mediante i monitor.   

## Funzionamento utils   
ReplacerCSV.py sostituisce i separatori specificati in input con separatori utilizzati dal primo componente.   
randomLog.py genera un file csv utile per il debug del sistema.   

## Funzionamento 'initRedisDataStream'   
Si effettua il build del primo componente dalla cartella chiamando "./install.sh <nome_file.csv>". Dove "nome_file.csv" è il nome del file già normalizzato presente dentro la cartella '/bin' del primo componente. Verrà inizializzata una table "log" all'interno del db e la pipeline Redis verrà riempita dei messaggi (entries) lette dal file csv.   

## Funzionamento 'fillLogFromRedisStream'   
Si effettua il build del secondo componente dalla cartella chiamando "./install.sh". Si eseguono le istruzioni a schermo e si seleziona l'intervallo di dati di interesse. La table "log" del db viene riempita dai messaggi letti dalla pipeline Redis.   

## Funzionamento 'dbModelCalc'   
Si effettua il build del terzo componente dalla cartella chiamando "./install.sh". Si eseguono le istruzioni a schermo e si specificano eventuali simboli di guasto, la tabella "average" di riferimento, le tabelle con i dati sulle "covarianze" calcolate in precedenza, il valore percentuale di tolleranza ammesso.   
