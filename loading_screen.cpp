#include "loading_screen.h"
#include <raylib.h>

// Loading ekranını göstermek için bir fonksiyon
void ShowLoadingScreen() {
    // Pencereyi ve görüntüleri başlat
    InitWindow(800, 600, "Yüklenme ekranı");
    SetTargetFPS(60);

    // Başlık metni
    const char* title = "\t\t\tWINX\n\n\nESLESTIRME\n\n\nYUKLENIYOR..";

    // yüklenme ekranı süresi
    const float loadingTime = 3.0f; // 3 saniye

    // Başlangıç zamanı
    double startTime = GetTime();

    // Arka plan resmini yükledik
    Texture2D background = LoadTexture("/Users/beyzanurtezcan/CLionProjects/helloRaylib/gorseller/background.png");

    // Yazı tipini yükledik
    Font font = LoadFont("/Users/beyzanurtezcan/CLionProjects/helloRaylib/font/Winter Storm.ttf");

    // "Start" butonunun koordinatlarını hesapla
    const float buttonWidth = 200;
    const float buttonHeight = 50;
    float buttonX = (GetScreenWidth() - buttonWidth) /2 ;
    float buttonY = (GetScreenHeight() - buttonHeight) /2 +100;

    // Ana oyun döngüsü
    while (!WindowShouldClose()) {
        // Süre kontrolü
        double currentTime = GetTime();
        if ((currentTime - startTime) >= loadingTime) {
            // Eğer yüklenme ekranı süresi dolduysa, "Start" butonunu aktif hale getir
            Rectangle startButton = { static_cast<float>((GetScreenWidth() - 200) / 2), static_cast<float>((GetScreenHeight() - 50) / 2 + 100), 200, 50 };
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, startButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                break; // Döngüden çık ve oyun ekranına geç
            }

        }

        // Loading ekranını çiz
        BeginDrawing();

        DrawTexture(background, 0, 0, WHITE);
        // Başlık metnini ölç
        Vector2 titleSize = MeasureTextEx(font, title, 48, 0);
        // Başlık metnini çiz (ortalanmış)
        Vector2 titlePosition = { (GetScreenWidth() - titleSize.x) / 2, (GetScreenHeight() - titleSize.y) / 2 };
        DrawTextEx(font, title, titlePosition, 48, 0, BLACK);

        // "Start" butonunu çiz
        Rectangle startButton = { buttonX, buttonY, buttonWidth, buttonHeight };
        DrawRectangleLinesEx(startButton, 5, BLACK);
        DrawText("BASLA", startButton.x + 50, startButton.y + 10, 30, BLACK);

        EndDrawing();
    }

    // Kullanılan kaynakları temizle
    UnloadTexture(background);
    UnloadFont(font);

    // Raylib penceresini kapat
    CloseWindow();
}
