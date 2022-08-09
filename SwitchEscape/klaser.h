class ETAP{
      private:
              DATAFILE* pola;
              DATAFILE* ludki;
              short int zrodlo[wysokosc_planszy*szerokosc_planszy],mapa[wysokosc_planszy*szerokosc_planszy];
              short int x,y,v,ruch;   bool stoi;
              KIERUNEK kierunek;
              DZWIGNIA dzwignia;
              BITMAP* bufor; BITMAP* ludek;
              void przypisz(short int x[wysokosc_planszy*szerokosc_planszy], short int y[wysokosc_planszy*szerokosc_planszy]){
                   for(short int i=0;i<wysokosc_planszy*szerokosc_planszy;i++) x[i]=y[i];}
              short int sprawdz(short int x, short int y){
                    return mapa[y/wysokosc_pola*szerokosc_planszy+x/szerokosc_pola];}
              bool przesun(short int x, short int y, short int dx, short int dy){
                   if(sprawdz(x+dx*szerokosc_pola,y+dy*wysokosc_pola)%(kamien_numer-1)==1)return false;
                   mapa[(y/wysokosc_pola+dy)*szerokosc_planszy+x/szerokosc_pola+dx]=mapa[y/wysokosc_pola*szerokosc_planszy+x/szerokosc_pola];
                   mapa[y/wysokosc_pola*szerokosc_planszy+x/szerokosc_pola]=0;
                   return true;}
      public:
             ETAP(short int cmapa[wysokosc_planszy*szerokosc_planszy], DZWIGNIA cdzwignia){
                          x=50;   y=50;   ruch=0;
                          pola = load_datafile("pola.dat");
                          ludki = load_datafile("ludki.dat");
                          bufor = create_bitmap(szerokosc_planszy*szerokosc_pola,wysokosc_planszy*wysokosc_pola);
                          for(short int i=0;i<wysokosc_planszy*szerokosc_planszy;i++)mapa[i]=cmapa[i];
                          dzwignia=cdzwignia;
                          if(dzwignia.polozenie()) mapa[dzwignia.polozenie()]=dzwignia_lewo_numer;
                          przypisz(zrodlo,mapa);
                          kierunek=przod;}
             ~ETAP(){destroy_bitmap(bufor);}
             void skok(short int a){
                  if(stoi){v-=a; stoi=false;}}
             void przesunwlewo(){
                  kierunek=lewo; ruch++;
                  if(ruch==15) ruch=0;
                  short int a=y+wysokosc_ludka/2;
                  if(sprawdz(x-szybkosc_ludka,a)==kamien_numer)if(przesun(x-szybkosc_ludka,a,-1,0)){
                                        while(przesun(x-szybkosc_ludka-szerokosc_pola,a,0,1))a+=wysokosc_pola;
                                        return;}
                  if(sprawdz(x-szybkosc_ludka,y)%(kamien_numer-1)==1 || sprawdz(x-szybkosc_ludka,y+wysokosc_ludka-3)%(kamien_numer-1)==1)return;
                  x-=szybkosc_ludka;}
             void przesunwprawo(){
                  kierunek=prawo; ruch++;
                  if(ruch==15) ruch=0;
                  short int a=y+wysokosc_ludka/2;
                  if(sprawdz(x+szerokosc_ludka+szybkosc_ludka,a)==kamien_numer)
                  if(przesun(x+szerokosc_ludka+szybkosc_ludka,a,1,0)){
                                               while(przesun(x+szerokosc_ludka+szybkosc_ludka+szerokosc_pola,a,0,1)) a+=wysokosc_pola;
                                               return;}
                  if(sprawdz(x+szerokosc_ludka+szybkosc_ludka,y)%(kamien_numer-1)==1 || sprawdz(x+szerokosc_ludka+szybkosc_ludka,y+wysokosc_ludka-3)%(kamien_numer-1)==1) return;
                  x+=szybkosc_ludka;}
             void spadaj(){
                  v++;
                  for(short int i=0;i<abs(v);i++){
                            if(v>0)if(sprawdz(x,y+wysokosc_ludka-2)%(kamien_numer-1)==1||sprawdz(x+szerokosc_ludka-1,y+wysokosc_ludka-2)%(kamien_numer-1)==1)
                            {v=0; stoi=true; break;}
                            if(v<0)if(sprawdz(x,y-1)%(kamien_numer-1)==1||sprawdz(x+szerokosc_ludka-1,y-1)%(kamien_numer-1)==1)
                            {v=0; break;}
                            y+=v/abs(v);}}
             void gin(){
                  x=40; y=40;
                  przypisz(mapa,zrodlo);
                  v=0;  kierunek=przod;}
             short int rozgladaj(){
                  short int a;
                  a=sprawdz(x+2,y+2); if(a==3||a==2) return a;
                  a=sprawdz(x+2,y+wysokosc_ludka-3); if(a==3||a==2) return a;
                  a=sprawdz(x+szerokosc_ludka-3,y+2); if(a==3||a==2) return a;
                  a=sprawdz(x+szerokosc_ludka-3,y+wysokosc_ludka-3); if(a==3||a==2) return a;
                  return 0;}
             short int uzyj(){
                  if(sprawdz(x+szerokosc_ludka+1,y+wysokosc_ludka/2)==dzwignia_lewo_numer) return dzwignia_lewo_numer;
                  if(sprawdz(x-1,y+wysokosc_ludka/2)==dzwignia_lewo_numer) return dzwignia_lewo_numer;
                  if(sprawdz(x+szerokosc_ludka+1,y+wysokosc_ludka/2)==wyrzutnia_numer) return wyrzutnia_numer;
                  if(sprawdz(x-1,y+wysokosc_ludka/2)==wyrzutnia_numer) return wyrzutnia_numer;
                  return 0;}
             void znalazl(short int a){
                  if(a==dzwignia_lewo_numer){
                                 mapa[dzwignia.polozenie()]=dzwignia_prawo_numer;
                                 mapa[dzwignia.cel()]=0;}
                  if(a==wyrzutnia_numer)skok(sila_wyrzutni);}
             void narysuj(){
                  clear_to_color(bufor,0);
                  for(int i=0;i<szerokosc_planszy*wysokosc_planszy;i++){
                          if(mapa[i]==1)
masked_blit((BITMAP*)pola[sciana_obraz].dat, bufor, 0,0, i%szerokosc_planszy*szerokosc_pola,i/szerokosc_planszy*wysokosc_pola, 40, 40);
                          else if(mapa[i]==ogien_numer)
masked_blit((BITMAP*)pola[ogien_obraz].dat, bufor, 0,0, i%szerokosc_planszy*szerokosc_pola,i/szerokosc_planszy*wysokosc_pola, 40, 40);
                          else if(mapa[i]==cel_numer)
masked_blit((BITMAP*)pola[cel_obraz].dat, bufor, 0,0, i%szerokosc_planszy*szerokosc_pola,i/szerokosc_planszy*wysokosc_pola, 40, 40);
                          else if(mapa[i]==kamien_numer)
masked_blit((BITMAP*)pola[kamien_obraz].dat, bufor, 0,0, i%szerokosc_planszy*szerokosc_pola,i/szerokosc_planszy*wysokosc_pola, 40, 40);
                          else if(mapa[i]==dzwignia_lewo_numer)
masked_blit((BITMAP*)pola[lewadzwignia_obraz].dat, bufor, 0,0, i%szerokosc_planszy*szerokosc_pola,i/szerokosc_planszy*wysokosc_pola, 40, 40);
                          else if(mapa[i]==dzwignia_prawo_numer)
masked_blit((BITMAP*)pola[prawadzwignia_obraz].dat, bufor, 0,0, i%szerokosc_planszy*szerokosc_pola,i/szerokosc_planszy*wysokosc_pola, 40, 40);
                          else if(mapa[i]==wyrzutnia_numer)
masked_blit((BITMAP*)pola[wyrzutnia_obraz].dat, bufor, 0,0, i%szerokosc_planszy*szerokosc_pola+1,i/szerokosc_planszy*wysokosc_pola+1, 40, 40);}
                  if(kierunek==przod) masked_blit((BITMAP*)ludki[ludek_prosto].dat, bufor, 0,0, x,y, szerokosc_ludka, wysokosc_ludka);
                  else if(kierunek==prawo) switch(ruch/5){
                       case 0:{masked_blit((BITMAP*)ludki[ludek_prawo_1].dat, bufor, 0,0, x,y, szerokosc_ludka, wysokosc_ludka); break;}
                       case 1:{masked_blit((BITMAP*)ludki[ludek_prawo_2].dat, bufor, 0,0, x,y, szerokosc_ludka, wysokosc_ludka); break;}
                       case 2:{masked_blit((BITMAP*)ludki[ludek_prawo_3].dat, bufor, 0,0, x,y, szerokosc_ludka, wysokosc_ludka); break;}}
                  else if(kierunek==lewo) switch(ruch/5){
                       case 0:{masked_blit((BITMAP*)ludki[ludek_lewo_1].dat, bufor, 0,0, x,y, szerokosc_ludka, wysokosc_ludka); break;}
                       case 1:{masked_blit((BITMAP*)ludki[ludek_lewo_2].dat, bufor, 0,0, x,y, szerokosc_ludka, wysokosc_ludka); break;}
                       case 2:{masked_blit((BITMAP*)ludki[ludek_lewo_3].dat, bufor, 0,0, x,y, szerokosc_ludka, wysokosc_ludka); break;}}
                  blit(bufor,screen,0,0,0,0,bufor->w,bufor->h);}
                  //blit(bufor,screen,0,0,szerokosc_ekranu/2-x-szerokosc_ludka/2,wysokosc_ekranu/2-y-wysokosc_ludka/2,bufor->w,bufor->h);}
                  };
