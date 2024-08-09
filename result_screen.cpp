
// Created by beyza nur tezcan on 3.05.2024.
#include "result_screen.h"
#include <raylib.h>

void ShowResultScreen(int score) {
    // Pencereyi ve görüntüleri başlat
    InitWindow(800, 600, "Sonuç Ekranı");
    SetTargetFPS(60);

    int fontSize = 50; // Yazı boyutunu ayarlayın

    // Yazının boyutunu al
    const char *text = TextFormat("TEBRIKLER\n\n\n\n Oyun Bitti!\n\n\n\t\tScore: %d", score);
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 0);

    // Yazının x ve y koordinatlarını hesapla
    float textX = (GetScreenWidth() - textSize.x) / 2; // Yazının yatay konumunu ayarla
    float textY = (GetScreenHeight() - textSize.y) / 2; // Yazının dikey konumunu ayarla

    // Arka plan resmini yükle
    Texture2D background = LoadTexture("/Users/beyzanurtezcan/CLionProjects/helloRaylib/gorseller/result.png");

    // Yazı tipini yükle
    Font font = LoadFont("/Users/beyzanurtezcan/CLionProjects/helloRaylib/font/Winter Storm.ttf");

    // Ana oyun döngüsü
    while (!WindowShouldClose()) {

        // Ekrana arka planı çiz
        BeginDrawing();

        // Arka plan resmini çiz
        DrawTexture(background, 0, 0, WHITE);

        // Ekrana sonucu yazdır
        DrawTextEx(font, text, Vector2{textX, textY}, fontSize, 0, BLACK);


        EndDrawing();
    }

    // Kullanılan kaynakları temizle
    UnloadTexture(background);
    UnloadFont(font);

    // Raylib penceresini kapat
    CloseWindow();
}
