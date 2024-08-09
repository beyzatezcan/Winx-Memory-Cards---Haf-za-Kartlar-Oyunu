
#include <raylib.h>
#include <vector>
#include <random>
#include "loading_screen.h"
#include "result_screen.h"

#define KART_BOŞLUK_X 10 // Kartlar arası boşluk miktarı x ekseninde
#define KART_BOŞLUK_Y 10 // Kartlar arası boşluk miktarı y ekseninde

// Kart sınıfı
class Kart {
public:
    Texture2D önGörüntü; // Kartın ön yüzü için görüntü
    Texture2D kapalıGörüntü; // Kartın kapalı arka yüzü için görüntü
    bool açık; // Kartın açık olup olmadığını belirten bir ifade
};

// Oyun tahtası sınıfı
class OyunTahtası {
public:
    OyunTahtası(const std::vector<Texture2D>& görseller, Texture2D kapalıGörüntü, int rows, int cols)
        : rows(rows), cols(cols), kapalıGörüntü(kapalıGörüntü), açıkKart1(nullptr), açıkKart2(nullptr), kartAçıkSayısı(0), puan(0) {
        // Kartları oluştur ve karıştır
        std::vector<Kart> karışıkKartlar;
        for (const Texture2D& tex : görseller) {
            karışıkKartlar.push_back({tex, kapalıGörüntü, false}); // Her kartın bir çifti var
            karışıkKartlar.push_back({tex, kapalıGörüntü, false});
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(karışıkKartlar.begin(), karışıkKartlar.end(), gen);

        // Oyun tahtasını oluştur
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int index = i * cols + j;
                kartlar_[i][j] = karışıkKartlar[index];
            }
        }
    }

    // Kart seçme
    Kart* seç(int x, int y) {
        if (x >= 0 && x < cols && y >= 0 && y < rows) {
            Kart* kart = &kartlar_[y][x];
            if (!kart->açık && kartAçıkSayısı < 2) {
                kart->açık = true;
                kartAçıkSayısı++;
                if (kartAçıkSayısı == 1) {
                    açıkKart1 = kart;
                } else {
                    açıkKart2 = kart;
                }
                return kart;
            }
        }
        return nullptr;
    }

    // Eşleşen kartları kontrol etme
    bool eşleştir() {
        if (açıkKart1 && açıkKart2) {
            if (açıkKart1->önGörüntü.id == açıkKart2->önGörüntü.id) {
                // Eşleşen kartlar
                açıkKart1 = açıkKart2 = nullptr;
                kartAçıkSayısı = 0;
                puan += 10; // Eşleşme durumunda 10 puan ekle
                return true;
            } else {
                // Eşleşmeyen kartlar
                açıkKart1->açık = açıkKart2->açık = false;
                açıkKart1 = açıkKart2 = nullptr;
                kartAçıkSayısı = 0;
                if (puan >= 2) {
                    puan -= 2; // Eşleşmeyen durumda 2 puan düş
                }
                return false;
            }
        }
        return false;
    }

    // Tüm kartların eşleşip eşleşmediğini kontrol etme
    bool tümKartlarEşleşti() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!kartlar_[i][j].açık) {
                    return false;
                }
            }
        }
        return true;
    }

    // Getter fonksiyonları
    int getRows() const { return rows; } //oyun tahtasının satır sayısını döndürür
    int getCols() const { return cols; } //oyun tahtasının sütun sayısını döndürür
    int getPuan() const { return puan; }
    const Kart& getKart(int row, int col) const { return kartlar_[row][col]; } //belirli bir satır ve sütundaki kartı döndürür

private:
    int rows;
    int cols;
    Texture2D kapalıGörüntü;
    Kart kartlar_[4][4];
    Kart* açıkKart1;
    Kart* açıkKart2;
    int kartAçıkSayısı;
    int puan;
};

int main() {

    InitAudioDevice();
    Sound fxOgg = LoadSound("/Users/beyzanurtezcan/CLionProjects/helloRaylib/music/Winx-Club-Sezon-1-Açılış-şarkısı.ogg");
    PlaySound(fxOgg);
    ShowLoadingScreen();
    double loadingTime = 3.0; // 3 saniye bekleme süresi
    double startTime = GetTime();

    while (!WindowShouldClose() && (GetTime() - startTime) < loadingTime) {
      // Oyunun başlamasından yana geçen süre 3 saniyeyi geçmişse ana oyuna geç
    }
    // Pencereyi ve görüntüleri başlat
    InitWindow(800, 600, "Hafıza Oyunu");
    SetTargetFPS(60); //oyunun hızını ve performansını belirtir

    // Kapalı kart görüntüsünü yükle
    Texture2D kapalıGörüntü = LoadTexture("/Users/beyzanurtezcan/CLionProjects/helloRaylib/gorseller/backcard.png");

    // Görselleri yükle
    std::vector<Texture2D> görseller;
    görseller.push_back(LoadTexture("/Users/beyzanurtezcan/CLionProjects/helloRaylib/gorseller/gorsel1.png"));
    görseller.push_back(LoadTexture("/Users/beyzanurtezcan/CLionProjects/helloRaylib/gorseller/gorsel2.png"));
    görseller.push_back(LoadTexture("/Users/beyzanurtezcan/CLionProjects/helloRaylib/gorseller/gorsel3.png"));
    görseller.push_back(LoadTexture("/Users/beyzanurtezcan/CLionProjects/helloRaylib/gorseller/gorsel4.png"));
    görseller.push_back(LoadTexture("/Users/beyzanurtezcan/CLionProjects/helloRaylib/gorseller/gorsel5.png"));
    görseller.push_back(LoadTexture("/Users/beyzanurtezcan/CLionProjects/helloRaylib/gorseller/gorsel6.png"));
    görseller.push_back(LoadTexture("/Users/beyzanurtezcan/CLionProjects/helloRaylib/gorseller/gorsel7.png"));
    görseller.push_back(LoadTexture("/Users/beyzanurtezcan/CLionProjects/helloRaylib/gorseller/gorsel8.png"));

    // Kartların boyutunu al
    int kartGenişlik = kapalıGörüntü.width;
    int kartYükseklik = kapalıGörüntü.height;

    // Kartların toplam genişliği ve yüksekliği
    int toplamGenişlik = 4 * kartGenişlik + 3 * KART_BOŞLUK_X;
    int toplamYükseklik = 4 * kartYükseklik + 3 * KART_BOŞLUK_Y;

    // Başlangıç konumu
    int başlangıçX = (GetScreenWidth() - toplamGenişlik)/2 ;
    int başlangıçY = (GetScreenHeight() - toplamYükseklik)/2 ;

    // Oyun tahtasını oluştur
    OyunTahtası tahta(görseller, kapalıGörüntü, 4, 4);

    // Oyun süresi
    double oyunSüresi = 60.0;
    double sonGüncellemeZamanı = GetTime();

    // Ana oyun döngüsü
    while (!WindowShouldClose() && oyunSüresi > 0) {
        // Süreyi güncelle
        double şuankiZaman = GetTime();
        double geçenZaman = şuankiZaman - sonGüncellemeZamanı;
        if (geçenZaman >= 1.0) {
            // Zamanı bir saniye azalt
            oyunSüresi--;
            sonGüncellemeZamanı = şuankiZaman;
        }

        // Oyun tahtasını çiz
        BeginDrawing();
        ClearBackground(PINK);
        for (int i = 0; i < tahta.getRows(); ++i) {
          for(int j= 0; j <tahta.getCols();++j) {
              int kartX= başlangıçX+j*(kartGenişlik+ KART_BOŞLUK_X);
              int kartY= başlangıçY+i*(kartYükseklik+ KART_BOŞLUK_Y);
              DrawTexture(tahta.getKart(i,j ).açık ? tahta.getKart(i, j).önGörüntü: kapalıGörüntü, kartX,kartY,WHITE);
          }
        }
        DrawText(TextFormat("Time: %.0f", oyunSüresi), 10, 10, 20, BLACK); // Zaman metnini çiz
        DrawText(TextFormat("Score: %d", tahta.getPuan()),
            10, 30, 20, BLACK); // Puan metnini çiz

        EndDrawing();


        \



        // Oyunun olaylarını isle
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Fare tıklaması konumunu al
            Vector2 mousePos = GetMousePosition();
            // Fare tıklaması konumuna göre hangi kartın seçildiğini bul
            int x = static_cast<int>((mousePos.x - başlangıçX) / (kartGenişlik + KART_BOŞLUK_X));
            int y = static_cast<int>((mousePos.y - başlangıçY) / (kartYükseklik + KART_BOŞLUK_Y));
            Kart* seçilenKart = tahta.seç(x, y);
            // Eğer eşleşme bulunduysa, eşleşen kartları kontrol et
            if (tahta.eşleştir()) {
                // Eşleşen kartları işle
            }
        }

        // Tüm kartlar eşleşti mi kontrol et
        if (tahta.tümKartlarEşleşti()) {
            break; // Eğer tüm kartlar eşleştiyse sürenin dolmasını beklemeden döngüden çık
        }
    }

    ShowResultScreen(tahta.getPuan());
    // Kullanılan kaynakları serbest bırak
    UnloadSound(fxOgg);
    CloseAudioDevice();
    UnloadTexture(kapalıGörüntü);
    for (const auto& tex : görseller) {
        UnloadTexture(tex);
    }

    // Raylib penceresini kapat
    CloseWindow();

    return 0;
}
