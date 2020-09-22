![Eyeglass logo](https://raw.githubusercontent.com/CristianoNarducci/Eyeglass/master/docs/Eyeglass_logo.png)
# Eyeglass
[English version](https://github.com/CristianoNarducci/Eyeglass/blob/master/README_en.md)

Eyeglass e' uno strumento grafico FOSS per visualizzare e comparare immagini.   
Formati supportati: .bmp .png .jpg .gif .pcx .pnm .tiff .tga .iff .xpm .ico .cur .ani


### Descrizione
Questo programma permette di caricare delle immagini e mantenerle in memoria, poi sceglierne due dalla lista e avviare la comparazione.   
Siccome la lista di immagini caricate puo' facilmente perdere il focus, quindi la selezione, viene introdotto il concetto di 'immagini attive'.   
In pratica, c'e' un pulsante che marca le prime due immagini selezionate (o solo una se la selezione e' singola) e le mantiene in mostra. Comparira' un numero nella parte destra della lista che segnala l'immagine attiva, e il relativo numero.   

Il numero aiuta anche ad identificare dov'e' l'immagine. La vista ha un design responsivo e si riorganizza per permettere una miglior visualizzazione dei dati.   
* quando l'area sulla destra della finestra e' piu' larga che alta, il contenuto si dispone orizzontalmente. La prima immagine sara' sulla sinistra, la seconda sulla destra.
* quando l'opposto e' vero, il contenuto sara' disposto verticalmente quindi la prima immagine sara' in cima, la seconda in basso.
Se i tab lo permettono, quando una sola immagine e' attiva, questa potrebbe prendere per se' tutto lo spazio loro dedicato.

L'area sulla destra, come accennato nel paragrafo precedente, e' la parte dove vengono mostrati i risultati ed e' suddivisa in tab.   
Al momento ci sono quattro viste e possono essere scambiate a piacimento:
* immagini originali	- mostra le immagini cosi' come sono. Funziona con solo un'immagine o con due immagini attive per volta.
* lista di differenze	- visualizza una lista testuale delle differenze scoperte dalla comparazione.
* vista sovrapposta		- uno slider permette di vedere piu' o meno delle immagini. Piu' si va a destra, meno si vede della seconda immagine. Piu' si va a sinistra, meno si vede della prima.
* heatmap				- mostra solo una versione in scala di grigi, leggermente scurita, della prima immagine. Dopo una comparazione, i pixel differenti tra le due immagini sono ricolorati con un gradiente dal verde al rosso. Il gradiente e' mappato alla differenza percentuale. Rosso acceso significa differenza massima, mentre verde spento significa bassa percentuale di differenza.

La comparazione e' manipolata dai parametri inseriti in fondo a sinistra.   
Uno slider controlla il punto di stacco, la tolleranza sotto la quale le differenze sono ignorate, mentre il menu' a tendina permette di selezionare i differenti aspetti da comparare.   
Attualmente e' possibile comparare il canale alpha, i colori nello spazio RGB e nello spazio HSV.


### Modificare Eyeglass
Eyeglass e' stato sviluppato in C++ 11 ma dovrebbe compilare fino al C++ 20 senza problemi.   
Le dipendenze sono:
* CMake (v3.17)			- usato per compilare il programma.
* Google Tests			- provvede ai test.
* wxWidgets (v3.0.0)	- il framework usato per creare l'intero programma.

Eyeglass e wxWidgets sono virtualmente inseparabili, senza una totale riscrittura del codice, dato che wx provvede metodi di accesso a tutto il necessario. Inizialmente l'idea era quella di usare ImageMagick (Magick++) per la gestione delle immagini, ma il mix non era appetibile.

Per aggiungere un tab personalizzato, e' necessario che questo sia modellato sulla classe astratta ViewTab e che sia registrato nel wxNotebook (nel metodo View::generateTabs). Dopodiche', l'implementazione sta a te.   

Aggiungere un metodo di comparazione e' un po' piu' complicato. Se vuoi fare come per gli altri metodi, devi aggiungere la funzione di comparazione pixel nella libreria ImageUtils.   
Poi c'e' il Model, dove va inserita la funzione che esegue la comparazione tra immagini, chiamando la funzione di comparazione pixel precedentemente implementata, su ogni pixel delle immagini.   
Dopo questo, va aggiunta la chiamata 'proxy' al controller e va aggiunta la selezione alla View.   

Se non e' stato' alterato, ogni tab dovrebbe svolgere il suo lavoro senza problemi con ogni metodo di comparazione, in quanto il programma salva le differenze in modo agnostico rispetto al metodo di comparazione usato (coordinate x, y e la percentuale di differenza).
