#ifndef QBIMAGE_H
#define QBIMAGE_H

#include <string>
#include <vector>

class Filme
{
public:
	Filme();
	~Filme();

	// Function to initialize.
	void Initialize(const int xSize, const int ySize);

	// Function to set pixels.
	void SetPixel(const int x, const int y, const double red, const double green, const double blue);

	// Function to return the image for display.
	void Display();

private:
	Uint32 ConvertColor(const double red, const double green, const double blue);
	void InitTexture();

private:
	// Arrays to store image data.
	std::vector<std::vector<double>> m_rChannel;
	std::vector<std::vector<double>> m_gChannel;
	std::vector<std::vector<double>> m_bChannel;

	// And store the size of the image.
	int m_xSize, m_ySize;

	// SDL2 stuff.
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;

};
