#include "Button.h"
#include <iostream>

// Définition du constructeur
Button::Button(SDL_Renderer* renderer, int x, int y, int width, int height) :
	renderer(renderer), rect{ x, y, width, height } {}

// Fonction pour charger la police de caractères
void Button::loadFont() {
	font = TTF_OpenFont("/Library/Fonts/OpenSans-Regular.ttf", 16);  // Remplacez par le chemin de votre police de caractères et la taille
	if (!font) {
		// Gérer l'échec du chargement de la police
		std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
	}
}

// Définition de la fonction pour dessiner le bouton avec des arguments optionnels pour la couleur
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

// Définition de la fonction pour vérifier si les coordonnées (x, y) sont à l'intérieur du bouton
bool Button::isClicked(int x, int y) const {
	return (x >= rect.x && x <= rect.x + rect.w &&
		y >= rect.y && y <= rect.y + rect.h);
}

// Définition de la fonction à appeler lorsque le bouton est cliqué
void Button::setOnClick(std::function<void()> onClick) {
	onClickAction = onClick;
}

void Button::switchColor() {
	if (!isPressed) isPressed = false;
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	draw(255 - r, 255 - g, 255 - b, a);
}

// Appelé lors du clic sur le bouton
void Button::onClick() {
	// Effectuez l'action associée au clic
	if (onClickAction) {
		onClickAction();
	}

	isPressed = true;
}

// Définir le texte à afficher sur le bouton
void Button::setText(const std::string& text) {
	buttonText = text;
	loadFont();  // Chargez la police de caractères lorsque le texte est défini
}

