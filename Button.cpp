#include "Button.h"
#include <iostream>

// D�finition du constructeur
Button::Button(SDL_Renderer* renderer, int x, int y, int width, int height) :
	renderer(renderer), rect{ x, y, width, height } {}

// Fonction pour charger la police de caract�res
void Button::loadFont() {
	font = TTF_OpenFont("/Library/Fonts/OpenSans-Regular.ttf", 16);  // Remplacez par le chemin de votre police de caract�res et la taille
	if (!font) {
		// G�rer l'�chec du chargement de la police
		std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
	}
}

// D�finition de la fonction pour dessiner le bouton avec des arguments optionnels pour la couleur
void Button::draw(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
	SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
	SDL_RenderFillRect(renderer, &rect);
	// Dessiner le texte au centre du bouton
	if (font) {
		SDL_Color textColor = { 255, 255, 255 };  // Couleur du texte (blanc)
		textSurface = TTF_RenderText_Solid(font, buttonText.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

		int textWidth, textHeight;
		SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

		SDL_Rect textRect = {
			rect.x + (rect.w - textWidth) / 2,
			rect.y + (rect.h - textHeight) / 2,
			textWidth,
			textHeight
		};

		SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
	}
	SDL_RenderPresent(renderer);
}

// D�finition de la fonction pour v�rifier si les coordonn�es (x, y) sont � l'int�rieur du bouton
bool Button::isClicked(int x, int y) const {
	return (x >= rect.x && x <= rect.x + rect.w &&
		y >= rect.y && y <= rect.y + rect.h);
}

// D�finition de la fonction � appeler lorsque le bouton est cliqu�
void Button::setOnClick(std::function<void()> onClick) {
	onClickAction = onClick;
}

void Button::switchColor() {
	if (!isPressed) isPressed = false;
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	draw(255 - r, 255 - g, 255 - b, a);
}

// Appel� lors du clic sur le bouton
void Button::onClick() {
	// Effectuez l'action associ�e au clic
	if (onClickAction) {
		onClickAction();
	}

	isPressed = true;
}

// D�finir le texte � afficher sur le bouton
void Button::setText(const std::string& text) {
	buttonText = text;
	loadFont();  // Chargez la police de caract�res lorsque le texte est d�fini
}

