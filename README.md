# Software-Engineering-
Software Engineering project : Anomaly Detection for the year 2023/2024   

Last Commit - REDUX 18/03/2024   

Ci sono 3 processi. Il primo scrive su una stream redis i dati che legge da un file csv. Il secondo legge dalla stessa stream redis e inizializza la tabella di log sul database. Il terzo processo crea i modelli se non esistono o li sovrascrive se l'utente lo specifica, successivamente basandosi sul log e sui dati della media calcolati esegue il check delle anomalie (malfunzionamenti dei sensori, guasti, cambiamenti improvvisi dell'ambiente in esame). Nel terzo processo è possibile specificare la tolleranza in percentuale oltre la quale i dati sono considerabili anomalie.   
Creo un utente postgresql lollo con password lollo, e creo un database chiamato AnomalyDetection dove gode di tutti i diritti per poter usare il sistema.   
    
Final Commit - REDUX 03/04/2024

Implementati i monitor nella cartella monitor, vengono spiegati in un file di testo apposito


