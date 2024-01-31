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

    // Fonction pour v�rifier si les coordonn�es (x, y) sont � l'int�rieur du bouton
    bool isClicked(int x, int y) const;

    // Fonction � appeler lorsque le bouton est cliqu�
    void setOnClick(std::function<void()> onClick);

    // Fonction pour g�rer le changement de couleur pendant un certain d�lai
    void switchColor();

    void onClick();

    // D�finir le texte � afficher sur le bouton
    void setText(const std::string& text);

    void loadFont();

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    std::function<void()> onClickAction;  // Fonction � appeler lors du clic
    bool isPressed = false;
    std::string buttonText;  // Texte � afficher sur le bouton
    TTF_Font* font;  // Police de caract�res
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
};

