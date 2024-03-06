voglio avere writer e reader
Funzione che converte da xlsv a csv (cerca libreria online)
nel main.h eliminare "std::"
abbiamo tolerance, redis lo dovrà usare

FATTOFINORA:
    1 Dal main si accede direttamente al database AnomalyDetection creato da terminale, lollo ha tutti i privilegi
        init_log riceve i campi che ci interessano e crea la table iniziando una connessione con il db
    2 Ora devo inizializzare una table che si chiama LOG, non un db.
        Riempio il log da init.cpp usando redis e passandogli le entry che voglio processare
    6 ok
    7 init_log.cpp crea la table correttamente

