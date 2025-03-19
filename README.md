# Arduino-Robot.Asistent
# Robot Asistent pentru Persoane Nevăzătoare 

Un proiect realizat pentru a sprijini persoanele cu deficiențe de vedere, printr-un robot autonom capabil să urmeze utilizatorul și să evite obstacolele. Proiectul este destinat unei aplicații practice în mobilitatea asistată, fiind totodată un prototip educațional.

## 📌 Descriere generală

Acest robot este capabil să detecteze mișcarea utilizatorului din spate,moment in care porneste deplasarea, evitând în același timp obstacolele din față. Utilizează senzori IR, senzori ultrasonici și un buzzer pentru alertare sonoră. Robotul este echipat cu un mâner de sprijin pentru a ghida utilizatorul în siguranță.

##  Componente hardware

- Arduino UNO
- Shield control motoare L293D
- 4 x Motoare DC + roți
- Servomotor SG90
- Senzor ultrasonic HC-SR04
- Senzori IR (frontal și laterali)
- Modul buzzer activ
- Întrerupător on/off cu LED
- Suport baterii + 6 baterii AA
- Mâner de sprijin

##  Funcționare

1. **Pornire automată**: senzorul IR din spate detectează mișcarea utilizatorului și activează robotul.
2. **Urmărirea direcției**: control diferențial al motoarelor pentru direcționare.
3. **Evitarea obstacolelor**: senzorul ultrasonic montat pe servomotor scanează în lateral și alege cel mai bun traseu.
4. **Alertare**: la detectarea obstacolelor, buzzer-ul emite un sunet de avertizare.
5. **Ghidaj fizic**: utilizatorul se poate sprijini de robot prin mânerul integrat.

## Rezultate și observații

Robotul funcționează corespunzător într-un mediu de testare, dar se pot aduce îmbunătățiri prin utilizarea unor senzori mai preciși (LiDAR, accelerometru etc.). În anumite condiții de iluminare, senzorii IR laterali pot da erori minore.

## Posibile îmbunătățiri viitoare

- Integrare senzori LiDAR
- Navigație GPS
- Adăugarea unui accelerometru pe utilizator
- Comunicație Bluetooth pentru urmărire precisă



