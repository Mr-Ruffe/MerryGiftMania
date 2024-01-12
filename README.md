# Merry Gift Mania

Det här är projektuppgiften i kursen CPROG HT23, som går ut på att bygga en spelmotor i C++, samt demonstrera motorn med ett enkelt spel.

<img src="doc/images/doc1.png?" name="doc1">

Spelet går ut på att samla paket så snabbt som möjligt. Spelaren styr en tomte med piltangenterna. Tomten kan gå i sidled (horisontellt), och röra sig vertikalt genom att antingen klättra upp/ner för stegar och åka ner för ruschkanor. Spelet är vunnet när alla paket är samlade: då stannar timern.

Inga menyer eller poängtavlor är implementerade i spelet. Det är självklart någonting som skulle höja spelkvaliteten, men ansågs som något som inte påvisar något ytterligare med spelmotorn utifrån kraven. 

## Förhandskrav
  * C++ 17
  * MinGW64 GCC
  * SDL2
    * SDL_image
    * SDL_ttf
    * SDL_mixer

## Setup

Projektet kompileras med ```make```. Då skapas hela build-mappstrukturen, med build/debug/resources, samt kopierar alla resources till build-mappen (ifall man vill köra direkt via .exe filen). Därefter kan man köra genom att antingen exekvera play.exe i mappen, eller via terminalen (```./build/debug/play``` alternativt ```cd build/debug```och ```./play```).

## Objekt

<img src="doc/images/doc6.png?" name="doc6">

  * **Santa**: Karaktären som spelaren styr.
  * **Ladder**: Stegar som spelaren kan klättra upp- och ner för. 
  * **Slide**: Ruschkanor som spelaren kan åka ner för.
  * **Present**: Objekten som spelaren samlar. 
  * **Gift counter**: Indikerar hur många presenter som spelaren har samlat.
  * **Timer**: Räknaren som håller koll på tiden. Stannar när spelet är vunnet.

## Kontroller

Spelaren styr tomten med piltangenterna. Vänster pil flyttar karaktären till vänster, och höger till höger.

### Samla paket
<img src="doc/images/doc2.png?" name="doc2">

Samla paket görs genom att kollidera karaktären med paketen. Då kommer tomten att göra ett skrockande *"ho ho ho, merry christmas!"*, vilket fryser spelaren för en stund (ingen rörelse är då tillåten), och lägga till ett paket på **gift counter**:n. 

### Klättra stegar
<img src="doc/images/doc3.png?" name="doc3">

Klättra stegar görs genom att använda piltangent upp för att klättra uppåt och piltangent ned för att klättra nedåt. När man påbörjat klättringen måste man antingen klättra högst upp eller längst ner för att avbryta klättringen. Tomten justeras automatiskt mot centrum på stegen när klättringen ska påbörjas, vilket kan innebära en viss rörelse i sidled. 


### Åka ruschkanor
<img src="doc/images/doc4.png?" name="doc4">

Åka ruschkana är väldigt liknande att klättra ner för en stege, fast istället kan man inte vara stilla på vägen ner, samt att det bara går att åka ner och inte upp. Man påbörjar alltså åkandet med att använda piltangent ner, vilket kan innebära viss justering i sidled. Därefter rör sig tomten ner för ruschkanan tills att botten är nådd. 

### Vinna spelet
<img src="doc/images/doc5.png?" name="doc5">

Vinner gör man genom att samla alla paketen, så att räknaren visar 5/5 paket. Då stannas timern, och tomten genomför sin sista *"ho ho ho, merry christmas!"* . Därefter kan vinsttiden skrivas ner, och spelet stängas. 

### Gå för långt?
Vad händer om man glömmer ett paket tidigare på nivån? Jo, genom att gå till vänster i bild så hoppar man automatiskt till högersidan, vilket möjliggör att karaktären kan återgå till starten på nivån. Det fungerar självklart inte från höger till vänster dock, då det skulle innebära en fördel.
