# Conclusie
Op basis van alle voorgaande fases — discovery, definition en de drie develop-fases — is OXYBloom uitgegroeid tot een concept dat erin slaagt een complex en vaak onzichtbaar probleem (een slecht geventileerde, energieverslindende woning) op een laagdrempelige en aantrekkelijke manier zichtbaar en behapbaar te maken voor de gebruiker.

Het finale concept is een slimme, plantvormige luchtkwaliteitsmonitor die via een combinatie van CO₂- en vochtsensoren continu de binnenlucht opvolgt. Wanneer de luchtkwaliteit achteruitgaat, communiceert het product dit op een subtiele, niet-storende manier: via kleurveranderingen, een lichte beweging van de "bladeren" en optionele voice feedback. Een bijhorende app biedt extra diepgang voor wie dat wenst (grafieken, beloningssysteem, personalisatie), maar is nooit een vereiste — het product blijft volledig stand-alone bruikbaar. Hiermee wordt voldaan aan een groot deel van de design requirements die doorheen het traject werden opgesteld (zie Design Requirements).

Dit concept vormt een sterk onderbouwde oplossing voor het geschetste probleem, om verschillende redenen:

Het sluit aan bij een reëel en aangetoond probleem. Uit de discovery-fase bleek dat ongeveer de helft van de respondenten zich niet bewust is van het verband tussen ventilatiegedrag en energieverbruik. Een product dat dit verband op een tastbare manier zichtbaar maakt, speelt direct in op die kennis- en gedragskloof.

De metafoor van de bloem werkt. Waar bestaande oplossingen op de markt vaak technisch, klinisch en weinig "gezellig" aanvoelen (zoals bleek uit de benchmarking), kiest Oxybloom voor een vorm die mensen graag permanent in hun leefruimte plaatsen. Uit de testen in de definition-fase en develop 1 bleek dat de bloem zowel qua esthetiek als qua "bereidheid tot actie" beter scoorde dan alternatieve metaforen (zoals de parkiet) of een digitale interface.

De interactie is doordacht en getest op echte gebruikers. Doorheen develop 1 en 2 werd stap voor stap gebouwd aan een product waarbij voice feedback, knoppositie, knoptype en de algemene ergonomie steeds opnieuw getest en bijgestuurd werden. Dit heeft geleid tot een ontwerp dat zonder uitleg te begrijpen en te bedienen is — een van de centrale usability goals van het project.

De detaillering is afgestemd op wat gebruikers echt waarderen. Develop 3 toonde aan dat gebruikers een balans zoeken tussen technologie en natuur: realistische, plant-achtige details (bladvorm, textuur, bodemplaat met steentjes) gecombineerd met subtiele, geïntegreerde technologie (verlichting, ventilatie). Deze inzichten zijn rechtstreeks verwerkt in de finale CMF-keuzes.

Het concept is praktisch en functioneel uitgewerkt. Het prototype is niet enkel esthetisch, maar ook functioneel: voorzien van werkende elektronica en code, een herbruikbaar en goed te vullen waterreservoir, en een duidelijke materiaalkeuze. De volledige technische uitwerking is terug te vinden in de Bill of Materials.

Kortom: OXYBloom combineert een wetenschappelijk onderbouwd probleem, een emotioneel aansprekende metafoor, een getest en gebruiksvriendelijk interactieontwerp, en een esthetisch afgewerkt eindproduct. Suggesties voor verder onderzoek en mogelijke verbeterpunten (zoals prijsbepaling, een Pro-versie, of uitbreidingen met externe sensoren) worden besproken in de kritische reflectie.

## Toekomstperspectief
Hoewel het huidige prototype een goed onderbouwde en functionele oplossing biedt, zijn er nog verschillende richtingen waarin het concept verder kan groeien. Op basis van de feedback uit de verschillende testfases en het gesprek met studenten in Gent, zien we vooral potentieel in de volgende aspecten:

Uitbreiding met externe sensoren en hardware. Een apart, buiten geplaatst apparaat zou bijkomende data (zoals de buitenluchtkwaliteit) kunnen verzamelen, wat de adviezen van Oxybloom nog accurater zou maken. Daarnaast zou de overstap van een Arduino Mega naar een specifiek ontworpen PCB een belangrijke stap voorwaarts zijn op het vlak van compactheid en betrouwbaarheid. Ook het upgraden van componenten, zoals een stappenmotor die zijn positie nauwkeurig kan bepalen of leds die geleidelijk in helderheid en kleur veranderen in plaats van abrupt, zou bijdragen aan een vloeiendere en esthetisch verfijndere werking van het product.

Modulariteit en duurzaamheid. Vervangbare onderdelen en een eventueel geïntegreerd CO2-filter zouden de levensduur van het product verlengen en het op termijn volledig zelfstandig kunnen laten functioneren.

Verdere personalisatie en toegankelijkheid. Functies zoals een trilfunctie in de app, ten behoeve van  gebruikers met een visuele beperking, of een visuele indicatie van de luchtkwaliteit aan de hand van een balkje, kunnen de toegankelijkheid van het product verder vergroten.
Bijkomende functionaliteit. Een diffuser zou bijvoorbeeld ook ingezet kunnen worden om geuren te verspreiden, wat de meerwaarde van het product verder zou vergroten.

Businessmodel en prijsbepaling. Prijs blijft een belangrijke drempel voor een breed publiek. Verder onderzoek naar een haalbaar prijspunt, en naar de manier waarop eventuele Pro-functies aangeboden kunnen worden zonder dat gebruikers van de basisversie het gevoel krijgen iets te missen, is noodzakelijk voor een succesvolle marktintroductie. Hieronder is een tabel met een schatting van wat het prototype nu kost.
| Onderdeel | Aantal | Prijs/stuk | Totaal |
|------------|:------:|-----------:|--------:|
| Arduino Mega 2560 | 1 | €25,00 | €25,00 |
| Stappenmotor 4-fase 5V (28BYJ-48) | 2 | €3,00 | €6,00 |
| ULN2003 driver | 2 | €1,50 | €3,00 |
| DHT11 (vocht/temp) | 1 | €1,50 | €1,50 |
| MQ-135 (CO₂) | 1 | €3,00 | €3,00 |
| RGB LED | 2 | €0,30 | €0,60 |
| Weerstand 220 Ω | 4 | €0,05 | €0,20 |
| Weerstand 1 kΩ | 3 | €0,05 | €0,15 |
| Drukknop | 2 | €0,20 | €0,40 |
| Potentiometer | 2 | €0,50 | €1,00 |
| DFPlayer Mini (DFR0299) | 1 | €3,00 | €3,00 |
| Micro SD-kaart | 1 | €5,00 | €5,00 |
| Speaker 8 Ω | 1 | €2,00 | €2,00 |
| Kabels | - | €2,00 | €2,00 |
| Batterij 9V | 1 | €2,00 | €2,00 |
| 9V batterijclip naar 2,1 mm DC | 1 | €1,50 | €1,50 |
| Mini breadboard | 1 | €2,00 | €2,00 |
| Half breadboard | 1 | €3,50 | €3,50 |
| **3D-print (PLA, 700 g)** | - | €20/kg | €14,00 |
| M3 imbusbout | 6 | €0,15 | €0,90 |
| M3 zeskantmoer | 6 | €0,10 | €0,60 |
| M3 sluitring | 6 | €0,05 | €0,30 |
| **Totaal** |  |  | **≈ €77,65** |

Deze elementen vormen geen onderdeel van het huidige prototype, maar bieden waardevolle aanknopingspunten voor een vervolgtraject of een volgende iteratie van Oxybloom.
## Evolutie Prototypes
<p align="left">
  <img src="../img/Prot.jpg" width="100%">
</p>

## Filmpje

In dit [Filmpje](https://www.youtube.com/shorts/xmFyi1Ips3s) wordt het proces die doorlopen is en het gebruik van de OXYBloom uitgelegd.
