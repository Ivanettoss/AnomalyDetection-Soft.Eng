Aggiungere richiesta all'utente circa l'ampiezza w dei dati da trattare, l'utente sceglie il t(iniziale) e il t(finale) espressi come misurazione numero #

Flusso per il db:
    1 Quando faccio partire il main succede che viene chiamata una funzione init, che chiama init_log
    2 Questa funzione inizializza una table che si chiama LOG dove metterà tutti i dati del file excel
    3 Si ritorna in init
    4 Se non ci sono errori si prosegue
    5 init inizia a leggere le colonne, le fa escludere all'utente e passa l'array di quelle volute a init_log.cpp
    6 init_log.cpp prende in input il nome del database e l'array dei campi che costituiranno la table
    7 init_log.cpp crea la table
        Con redis devo leggere da quel db tutti i campi che diventeranno chiave primaria della table per i valori medi
        Con redis leggo i campi (sensori) e faccio le tables da 2 campi per ognuno
    8 si ritorna su init, mentre vengono letti i record c'è una fifo con un processo con redis che scrive tutto sulla table

FATTOFINORA:
    1 Dal main si accede direttamente al database AnomalyDetection creato da terminale, lollo ha tutti i privilegi
        init_log riceve i campi che ci interessano e crea la table iniziando una connessione con il db
    2 Ora devo inizializzare una table che si chiama LOG, non un db, e lo deve fare redis

