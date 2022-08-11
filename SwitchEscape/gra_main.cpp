#include <allegro.h>

#define szerokosc_ekranu  1024
#define wysokosc_ekranu    600
#define szerokosc_planszy   20
#define wysokosc_planszy    10
#define szerokosc_pola      40
#define wysokosc_pola       40
#define szerokosc_ludka     20
#define wysokosc_ludka      30
#define szybkosc_ludka       3

#define ilosc_etapow         9
#define sila_skoku          15
#define sila_wyrzutni       25
#define opoznienie          30

#define ogien_numer          2
#define cel_numer            3
#define kamien_numer         4
#define dzwignia_lewo_numer  5
#define dzwignia_prawo_numer 6
#define wyrzutnia_numer      8

#define cel_obraz            0
#define kamien_obraz         1
#define lewadzwignia_obraz   2
#define ogien_obraz          3
#define prawadzwignia_obraz  4
#define sciana_obraz         5
#define wyrzutnia_obraz      6

#define ludek_prosto         0
#define ludek_lewo_1         1
#define ludek_lewo_2         2
#define ludek_lewo_3         3
#define ludek_prawo_1        4
#define ludek_prawo_2        5
#define ludek_prawo_3        6

enum KIERUNEK{prawo,lewo,przod};

class DZWIGNIA{
       private:
       short int dx,dy,cx,cy;
       public:
       DZWIGNIA(){}
       ~DZWIGNIA(){}
       void ustaw(short int x,short int y,short int xx,short int yy){
             dx=x;   dy=y;   cx=xx;   cy=yy;}
       short int polozenie(){
            return dy*szerokosc_planszy+dx;}
       short int cel(){
            return cy*szerokosc_planszy+cx;}};
       
#include "klaser.h"

int main(){
    allegro_init();
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,szerokosc_ekranu,wysokosc_ekranu,0,0);
    install_keyboard();
    clear_to_color(screen,makecol(255,255,255));
    #include "mapa.h"
    ETAP* etap[ilosc_etapow];
    for(int i=0;i<ilosc_etapow;i++) etap[i] = new ETAP(mapa[i],dzwignia[i]);
    short int a,level=0;
    while(!key[KEY_ESC]){
                         rest(opoznienie);
                         if(key[KEY_RIGHT]) etap[level]->przesunwprawo();
                         if(key[KEY_LEFT])  etap[level]->przesunwlewo();
                         if(key[KEY_Z]) etap[level]->znalazl(etap[level]->uzyj());
                         if(key[KEY_R])     etap[level]->gin();
                         etap[level]->spadaj();
                         if(key[KEY_UP]) etap[level]->skok(sila_skoku);
                         a=etap[level]->rozgladaj();
                         etap[level]->narysuj();
                         if(a==2){
                                  rest(opoznienie*20);
                                  etap[level]->gin();
                                  etap[level]->narysuj();
                                  rest(opoznienie*10);}
                         if(a==3){rest(opoznienie*10);level++;}
                         if(level==ilosc_etapow)break;}
    for(int i=0;i<ilosc_etapow;i++){
            delete etap[i];} 
    clear_keybuf();
    allegro_exit();
	return 0;}
END_OF_MAIN()
