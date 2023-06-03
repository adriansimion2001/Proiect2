# Proiect2 2022-2023
Joc de memorie de tip “Simon Says”, cu afișaj şi tastatură utilizând procesorul AT Mega 164 folosind compilatorul CodeVisionAVR
Coordonator științific: Prof. dr. ing. Mihai Stanciu 
Membrii echipei: Filotti Teodora-Maria, Simion Adrian-Nicolae


Cuprins proiect

1.   Modul de implementare

2.   Descrierea hardware

3.   Descrierea software

4.   Rezultate și concluzii

5.   Bibliografie

Modul de implementare

 

  Proiectul constă în crearea unui joc de memorie de tip "Simon Says" pe o placă de dezvoltare ATMega164, utilizând mediul CodeVisionAVR și limbajul de
programare C. Jocul va folosi un ecran LCD alfanumeric 16*4 pentru a afișa o serie de culori diferite, pe care jucătorul trebuie să le rețină 
și să le reintroducă în aceeași ordine, folosind o tastatură formată din butoane colorate (creata de noi). Exista 4 nivele de dificultate,
din care jucatorul poate alege, confrom meniului afisat. Dificultatea nivelelor consta in cresterea numarului initial de culori, cat si a frecventei 
de afisare. Culorile trebuie să fie memorate și introduse corect. Jocul se va încheia atunci când jucătorul apasă un buton cu o culoare greșită.

Am realizat tastatura din 4 butoane in configuratie buton + “pull-up” rezistor. Pentru a diminua efectul de “bounce” al butonului am conectat in paralel
un condensator care permite incarcarea mai lenta pe rezistenta.

În codul sursă al jocului, este implementată logica pentru a verifica stadiul jocului, cum ar fi corectitudinea răspunsurilor utilizatorului în raport
cu succesiunea afișată anterior pe ecran. Dacă se introduce secventa gresit, jucatorul este trimis catre meniul initial. De asemenea, modulul LCD este
controlat de microcontroller-ul ATMega164 prin intermediul liniilor de cod. Acestea sunt sunt conectate la pinii specifici ai microcontroller-ului și la pinii
corespunzători ai ecranului LCD, permițând astfel afișarea culorilor și a informațiilor pe ecran.


| Clasa          | Referinta               | Valoarea | Descriere                      | Furnizor, Cod produs | Cantitate |
|----------------|-------------------------|----------|--------------------------------|----------------------|-----------|
| Rezistor       | R2                      | 470 ohm  | SMD                            | UPD                  | 1         |
| Rezistor       | R1,R3,R4,R5,R6          | 10 kohm  | SMD                            | UPB                  | 5         |
| Rezistor       | R7                      | 1 kohm   | THD                            | UPB                  | 1         |
| Rezistor       | R8                      | 5 kohm   | THD                            | UPB                  | 1         |
| Condesator     | C1                      | 1 uF     | THD                            | UPB                  | 1         |
| Condesnator    | C2,C3                   | 18 pF    | SMD                            | UPB                  | 2         |
| Condensator    | C5,C6,C11,C12,C13       | 100 nF   | SMD                            | UPB                  | 5         |
| Condensator    | C14,C15,C16,C17         | 220 nF   | THD                            | UPB                  | 4         |
| LED            | D2                      |          | Culoare: Rosu                  | UPB                  | 1         |
| Buton          | SW1,SW2,SW3,SW4,SW5,SW6 |          |                                | UPB,hobbymarket.ro   | 1         |
| Cuart          | X1                      |          | U                              | UPB                  | 1         |
| USB TTL        | TTL - USB               |          | Modulul convertor CH340G       | ardushop.ro          | 1         |
|                |                         |          | USB la UART                    |                      |           |
|                |                         |          | Tensiunea de intrare: 3.3V/5V, |                      |           |
|                |                         |          | Chip CH340G                    |                      |           |
| ECRAN LCD 1604 | LCD 1604                |          | 16x4                           | hobbymarket.ro       | 1         |


Pinii microcontroller-ului:

Port B: este folosit pentru Data LCD.

Port D: PD2 este conectat la pinul de Enable de la Ecranul LCD, PD3 este conectat la pinul Read/Write de la ecranul LCD, PD5 la Switch 1 (USR pe placa),
iar PD6 este conectat la LED.

Port C: PC0 este Register Select

Port A: pinii de la PA0 la PA3 sunt configurati ca intrari pentru butoanele colorate.


Descriere software


Am configurat ca intrari digitale: pinul 5 din portul D, pinii 0,1,2,3 din portul A.

Am configurat ca iesiri digitale: portul B, pinii 2, 3,  6 (LED) din portul D si pinul 0 din portul C.

Memorie Flash estimata: 156 bytes

Memorie RAM estimata: 226 bytes


Rezultate și concluzii

  In realizarea proiectului am intampinat probleme legate de comunicatia seriala a primului nostru ecran LCD Color; ca urmare, am folosit
un ecran Alfanumeric 16*4. Pe parcursul testarii, cateva fire s-au desprins, nu am putut sa le mai lipim in acelasi loc, asa ca a trebuit
sa folosim alti pini. Pe partea de soft, am incercat sa retinem valorile generate aleator in vectori alocati dinamic,
dar in conditia de verificare a secventei introduse, rezulta intotdeauna victorie. Am rezolvat problema folosind alocarea statica a vectorilor.


  Pentru reglarea contrastului am folosit un potentiometru, am masurat valoarea tensiunii si l-am inlocuit cu un divizor de tensiune.

  Pentru implementarea randului de butoane am facut un debounce hardware, folosind condensatoare.

  Proiectul este portabil, poate functiona pe o baterie de 9V; am confectionat o carcasa dintr-un suport de bureti.

 
Bibliografie

  https://www.electronicwings.com/

  https://en.wikipedia.org/wiki/Simon_Says

  http://ham.elcom.pub.ro/proiect2/index.html

  https://hackaday.com/2015/12/09/embed-with-elliot-debounce-your-noisy-buttons-part-i/

  http://ham.elcom.pub.ro/proiect2/files/ATmega164A_Datasheet.pdf

 
