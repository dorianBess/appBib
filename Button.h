#pragma once
#include <SDL.h>
#include <iostream>
#include <functional>
#include <SDL_ttf.h>

class Button {
public:
    // Constructeur
    Button(SDL_Renderer* renderer, int x, int y, int width, int height);

    // Fonction pour dessiner le bouton avec des arguments optionnels pour la couleur
    void draw(Uint8 red = 0, Uint8 green = 0, Uint8 blue = 0, Uint8 alpha = 255);

    // Fonction pour vérifier si les coordonnées (x, y) sont à l'intérieur du bouton
    bool isClicked(int x, int y) const;

    // Fonction à appeler lorsque le bouton est cliqué
    void setOnClick(std::function<void()> onClick);

    // Fonction pour gérer le changement de couleur pendant un certain délai
    void switchColor();

    void onClick();

    // Définir le texte à afficher sur le bouton
    void setText(const std::string& text);

    void loadFont();

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    std::function<void()> onClickAction;  // Fonction à appeler lors du clic
    bool isPressed = false;
    std::string buttonText;  // Texte à afficher sur le bouton
    TTF_Font* font;  // Police de caractères
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
};

