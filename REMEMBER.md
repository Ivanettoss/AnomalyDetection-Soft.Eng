se l'utente mette no per ogni campo rilevato dire che c'è un errore e chiudere il programma.

lasciare nei main.h solo le funzioni che servono a quel processo (ALLA FINE)
Funzione che converte da xlsv a csv (cerca libreria online) (ALLA FINE)


TERZO PROCESSO
Se non è presente un log riporta un errore, dice all'utente che bisogna caricare almeno un LOG
Se è presente: lo scopo è leggere dal db la table log.
    Se non trova un modello:    
        (1) lo dice all'utente, chiede all'utente se si vuole costruire il modello (calcolo delle covarianze e delle medie)
    Se si trova un modello (medie e covarianze):
        chiedere se si vuole usarlo:
            chiedere tolleranza e costruire una table Anomalies con riportati gli id delle misure affette da anomalie
        chiedere se si vuole sovrascrivere:
            richiama (1)


Abbiamo considerato che quando un sensore smette di funzionare registra un segnale di guasto che è noto ai costruttori
Quello che vogliamo invece andare a considerare noi come ANOMALIA è un valore che si discosta di una percentuale scelta dall'utente dalla media calcolata su un modello che non coinvolge i dati affetti da guasti
