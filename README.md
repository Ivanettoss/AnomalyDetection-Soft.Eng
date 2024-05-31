## Descrizione generale
Il progetto di AnomalyDetection da noi sviluppato è organizzato in 3 componenti, un insieme di utils per normalizzare i dati 'csv' da fornire in input, e 5 monitor, di cui 3 agenti sul database postgres.   
Per il corretto funzionamento è necessario installare le seguenti librerie:   
- make
- g++
- postgresql
- redis
- libhiredis-dev
- libpq-dev

Si deve aggiungere un utente postgres così come specificato all'interno dei file main.h presenti dentro i componenti.
