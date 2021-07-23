Space Math este un soft educațional de calcul  matematic cu limita de timp. Space Math combină exersarea/învățarea și divertismentul interactiv într-o aplicație compactă, ușor de folosit pentru un domeniu larg de categorii de utilizatori. 
La momentul actual, jocul conține următoarele categorii: calcul matematic simplu (operații aritmetice elementare), rezolvarea unor ecuații de gradul 1, trigonometrie și un mod care include toate tipurile anterioare. 
De asemenea, jocul conține și un mod multiplayer, perfect pentru a exersa calculul matematic și pentru a intra într-o atmosfera competitivă cu prietenii tăi care sunt interesați de calcul matematic. 


Modul singleplayer

Scopul jocului este de a proteja ”nava mamă” de navele inamice generate în mod aleatoriu de aplicație. În funcție de categoria selectată, interfața oferă la fiecare moment un exercițiu matematic iar utilizatorul trebuie să editeze rezultatul obținut prin calcul matematic (mintal). Fiecare “răspuns” corect  va elimina cea mai apropiată navă inamică și va actualiza scorul jucătorului. Cu cat scorul creste, cu atât creste și dificultatea jocului. 
Jocul se sfarseste atunci cand "nava mama" se deterioreaza si explodeaza. Ulterior, daca scorul este un nou record, acesta se memoreaza (pentru fiecare categorie).
Jucătorul trebuie să se folosească de cunoștințele de matematica, dar și de abilitățile din joc pentru a realiza un scor cat mai mare:
   - Anumite intrebari sunt marcate cu o steluta care poate fi colectata daca raspunsul este scris suficient de rapid.
   - Daca jucatorul aduna 3 stelute se va activa o bariera care apara nava de gloantele inamice temporar.

Modul multiplayer

   - Daca jucatorul doreste sa se joace cu prietenii de la departare (retele diferite), atunci acesta poate folosi un VPN, care sa stabileasca legaturi directe intre calculatoare. (ex: Hamachi, ZeroTier, Evolve, etc.)
   - Pentru a juca multiplayer in reteaua locala, jucatorul care se conecteaza poate sa introduca comanda "LOCALHOST" sau IP-ul local la sectiunea "Adress".
   - Dupa ce jucatorii se conecteaza, acestia vor primi acelasi set de intrebari si inamici. Scopul modului multiplayer este de a ramane ultimul in viata.


Descriere Tehnică:

Jocul a fost realizat integral in C++ folosind biblioteca SFML pentru grafica, audio și networking.
Arhitectura jocului consta într-o stiva de stări (meniu principal, joc, etc.), ce reprezintă un automat finit. 
Jocul rulează la o performanta ridicata, deoarece desenările se fac eficient (sprite batch-uri). Codul este abstractizat si modularizat, întrucât am folosit programare orientata pe obiecte.

Jocul poate fi descarcat din sectiunea Releases din repository-ul de pe Github.

![Barrier](https://github.com/tMario2111/Space-Math/blob/main/Screenshots/barrier.png)
![Equations](https://github.com/tMario2111/Space-Math/blob/main/Screenshots/gigel%20vs%20costel.png)
![Multiplayer](https://github.com/tMario2111/Space-Math/blob/main/Screenshots/gigel%20vs%20costell.png)

