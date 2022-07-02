//kullanılan kütüphaneler
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include<conio.h>

//kullandığımız metotlararın tanımlanması
char fpeek(FILE *);
FILE *dosya_okuma(char linkler[200][500],int girdi,int girdiSayisi);
void append(char link[1], char ch);

int main() {
    //renklendirme için kullanılan metotlar
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //kullanılacak değişkenlerin tanımlanması ve değer atamalarını yapılması
    char ch= {0} ;
    char str1[] = "red";
    char str2[] = "blue";
    char linkler[200][500]={};
    strcpy(linkler[1],"PL2.txt");
    int girdi =1;
    int girdiSayisi=0;
    FILE * dosya;

    //kullanıcı '0' girdisi alınana kadar dönen while döngüsü
    while(girdi){
        int i=0;
        girdiSayisi++; //ilk başta atanan linkten dolayı girdi sayısı arttırımı
        dosya = dosya_okuma(linkler,girdi,girdiSayisi); //dosya okuma metodunun çağırılması

        //dosya sonuna kadar karakter karakter okuma işleminin yapılması
        while((ch = fgetc(dosya)) != EOF) {

            //yorum satırı kontrolü
            if (ch == '/' && fpeek(dosya) == '*') {

                fgetc(dosya);
                while ((ch = fgetc(dosya)) != EOF) {
                    if (ch == '*' && fpeek(dosya) == '/') {
                        fgetc(dosya);
                        break;
                    }
                }

                ch = fgetc(dosya);
            }

            //metnin hangi renkte olacağı kontrolü
            else if(ch=='['){

                char token[20] = {0}; //token char arrayinin tanımlanması
                int tokenSize = 0; //tokenın boyutunu tutacak tokenSize değişkeninin tanımlanması

                //içinde red tokenını oluşturacağımızı düşündüğümüz koşul
                if(fpeek(dosya)== 'r')
                {
                    //içinde r'den sonra gelen ve ']' karakterine kadar olan karakterleri token char arrayinde biriktirdiğimiz while döngüsü
                    while (ch != ']' && fpeek(dosya) != ']') {

                        token[tokenSize] = fpeek(dosya);
                        tokenSize++;
                        ch = fgetc(dosya);
                    }
                    fgetc(dosya);

                    //oluşan tokenın red olup olmadığının kontrolü
                    if (strcmp(str1, token) == 0) {

                        ch = fgetc(dosya);
                        //kırmızı olduğu anlaşılan metnin karakterlerinin kırmızı yazdırılmasını sağlayan while döngüsü
                        while (ch != '[') {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                            printf("%c", ch);
                            ch = fgetc(dosya);
                        }

                        //rengin resetlenmesi
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                        ch = fgetc(dosya);

                        //end red kısmını atlamak için koşul ve döngü
                        if (ch == 'e') {

                            while (ch != ']') {

                                ch = fgetc(dosya);
                            }
                        }
                        ch = fgetc(dosya);

                    }
                        //r ile başlayan ama tokenı red olmayan metin için kontrol
                    else{
                        ch = fgetc(dosya);
                        while(ch != '['){

                            printf("%c",ch);
                            ch= fgetc(dosya);

                        }

                        while(ch != ']'){

                            ch = fgetc(dosya);

                        }
                        ch = fgetc(dosya);
                    }

                }

                    //içinde blue tokenını oluşturacağımızı düşündüğümüz koşul
                else if(fpeek(dosya)==  'b')
                {
                    //içinde b'den sonra gelen ve ']' karakterine kadar olan karakterleri token char arrayinde biriktirdiğimiz while döngüsü
                    while (ch != ']' && fpeek(dosya) != ']') {

                        token[tokenSize] = fpeek(dosya);
                        tokenSize++;
                        ch = fgetc(dosya);

                    }


                    fgetc(dosya);

                    //oluşan tokenın 'blue' olup olmadığnın kontrolü
                    if(strcmp(str2,token)==0){

                        ch = fgetc(dosya);

                        //mavi olduğu anlaşılan metnin karakterlerinin mavi yazdırılmasını sağlayan while döngüsü
                        while(ch!='['){

                            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                            printf("%c",ch);
                            ch= fgetc(dosya);

                        }

                        //rengin resetlenmesi
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                        ch = fgetc(dosya);

                        //end blue kısmını atlamak için koşul ve döngü
                        if(ch == 'e'){
                            while(ch != ']'){

                                ch= fgetc(dosya);

                            }

                        }
                        ch= fgetc(dosya);

                    }
                        //b ile başlayan ama tokenı blue olmayan metin için kontrol
                    else{
                        ch = fgetc(dosya);
                        while(ch != '['){

                            printf("%c",ch);
                            ch= fgetc(dosya);

                        }
                        while(ch != ']'){
                            ch = fgetc(dosya);

                        }
                        ch = fgetc(dosya);

                    }
                }

                    //metnimizin kırmızı ya da mavi olmadığı durum (yeşil olduğu durum)
                else{
                    i++;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    char link[100] ={};
                    printf("%d%c",i,'.'); //linklere numara verme

                    //link olduğu belli olan metnin karakterlerinin yeşil yazdırılmasını sağlayan while döngüsü
                    while (ch!=']'){
                        append(link,ch);
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        printf("%c",ch);
                        ch = fgetc(dosya);

                    }

                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    printf("%c",ch);

                    append(link,ch);//karakterin link char arrayine eklenmesi
                    ch= fgetc(dosya);

                    //rengin resetlenmesi
                    SetConsoleTextAttribute(hConsole, saved_attributes);

                    char txt[100] ={};//her dosya için linklerin isim kısmını tutan char arrayi

                    for(int m=0;m< strlen(link);m++){

                        while (link[m]!='|'){

                            m+=1;

                        }

                        if(link[m]=='|'){
                            m+=1;
                            while(link[m]!=']'){
                                append(txt,link[m]);
                                m+=1;

                            }

                        }

                    }

                    strcpy(linkler[i+1],txt);
                }

            }

            printf("%c",ch);

        }

        printf("Bir sayi giriniz: ");//ulaşılmak istenen link numarasının kullanıcıdan girdi olarak istenmesi
        scanf("%d",&girdi);
        if(girdi>i){

        printf("Lutfen gecerli link numarasi giriniz: ");
        scanf("%d",&girdi);
            while (girdi>i){ //ulaşılamayan link numarası girildiği için tekrardan link numarası istenmesi

                printf("Lutfen gecerli link numarasi giriniz: ");
                scanf("%d",&girdi);

            }
        }

        system("cls");//terminal ekranını temizleme

    }

}

//gelen s char arrayinin sonuna yeni karakter eklememizi sağlayan metot
void append(char* s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

//File tipindeki stream'den sıradaki karakteri alıp bir sonraki karaktere geçmemesi(aynı karakterde kalması) için hazırlanan metot
char fpeek(FILE *stream) {
    char c;

    c = fgetc(stream);
    ungetc(c, stream);
    return c;
}


//kullanıcının girdiği link numarasına göre yukarıda oluşturduğumuz arraydaki linkleri okutan ve dosyayı döndüren metot
FILE *dosya_okuma(char linkler[200][500],int girdi,int girdiSayisi){
    FILE *dosya;

    if(girdiSayisi==1){//henüz 1 girdi olduğu durum için dosya okuma işlemi yapılması
        dosya = fopen(linkler[1], "r");

    }

    else{//1'den fazla girdi olduğu durum için dosya okuma işlemi yapılması
        dosya = fopen(linkler[girdi+1], "r");

        if(dosya == NULL ){ //dosyanın boş olduğu durum için hata mesajı yazdırılması
            printf("Error while opening the file\n");
            exit(1);
        }
        return dosya;

    }
}
