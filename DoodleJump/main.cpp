#include "Game.h"

int main(int argc, char** argv) {
    Game* game = new Game;

    /* ========== INITIALIZE GAME ELEMENTS ========== */
    try { game->init(); }
    catch (ERROR_CODE code) {
        std::cout << "Game initialization failed.\n";
        return static_cast<int>(code);
    }

    /* ========== RUNNING GAME LOOP ========== */
    try {
        const int FRAME_DELAY = 1000 / 60;
        while (true) {
            Uint32 frame_start = SDL_GetTicks();
            game->run();
            int frame_time = SDL_GetTicks() - frame_start;
            if (FRAME_DELAY > frame_time) {
                SDL_Delay(FRAME_DELAY - frame_time);
            }
        }
    }
    catch (ERROR_CODE code) {
        if (code == BRAVO) {
            std::cout << "\n---------- NICELY DONE! ----------\n";
            std::cout << "* Game ended successfully!\n";
        } else {
            std::cout << "\n---------- FATAL ERROR! ----------\n";
            switch (code) {
            case TEXTURE_ERROR:
                std::cout << "! Failed to load a texture.\n";
                break;
            case AUDIO_ERROR:
                std::cout << "! Failed to load an audio.\n";
                break;
            case ADDING_PADDLE:
                std::cout << "! An exception occurred while trying to add a paddle.\n";
                break;
            default:
                std::cout << "! An unexpected error has occured.\n";
                break;
            }
            std::cout << "! Exiting game loop...\n";
        }
        return game->quit(), static_cast<int>(code);
    }
}