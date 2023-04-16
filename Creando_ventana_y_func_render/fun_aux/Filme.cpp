
/* ***********************************************************
	el codigo esta altamente inspirado en :
	https://youtu.be/KBK6g6RFgdA
	 donde explican como usar SDL para crear una cavnas para 
	 crear una superficie


***********************************************************/

/* ***********************************************************

Este código corresponde a la implementación de la clase "Filme", 
que se utiliza para representar un archivo de imagen.La clase tiene 
un constructor, un destructor y varios métodos públicos, entre ellos 
Initialize(), SetPixel(), GetXSize(), GetYSize(), Display(), InitTexture(), 
ConvertColor() y ComputeMaxValues().

En el constructor, se inicializan los miembros de datos privados "m_xSize", 
"m_ySize" y "m_pTexture".En el destructor, 
se libera la memoria del objeto "m_pTexture", si no es nulo.
***********************************************************/

#include "Filme.hpp"

Filme::Filme()
{
	m_xSize = 0;
	m_ySize = 0;
	m_pTexture = NULL;
}

Filme::~Filme()
{
	if (m_pTexture != NULL)
		SDL_DestroyTexture(m_pTexture);
}

void Filme::Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer)
{

	//El método Initialize() se utiliza para configurar los datos necesarios para la 
	//representación de la imagen, como el tamaño de la imagen y el objeto "SDL_Renderer".
	//También se inicializan los vectores "m_rChannel", "m_gChannel" y "m_bChannel" con 
	//el tamaño de la imagen y se llama al método InitTexture() para crear un objeto "SDL_Texture".

	m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	
	m_xSize = xSize;
	m_ySize = ySize;
	
	m_pRenderer = pRenderer;
	
	InitTexture();
}

void Filme::SetPixel(const int x, const int y, const double red, const double green, const double blue)
{
	//El método SetPixel() se utiliza para establecer el valor de un píxel en los vectores "m_rChannel", "m_gChannel" y "m_bChannel".

	m_rChannel.at(x).at(y) = red;
	m_gChannel.at(x).at(y) = green;
	m_bChannel.at(x).at(y) = blue;
}

//Los métodos GetXSize() y GetYSize() devuelven el tamaño de la imagen en las direcciones x e y, respectivamente.
int Filme::GetXSize()
{

	return m_xSize;
}
int Filme::GetYSize()
{
	return m_ySize;
}

void Filme::Display()
{
	//El método Display() se utiliza para mostrar la imagen en la ventana.Primero, se llama al método ComputeMaxValues()
	//para calcular los valores máximos de los canales de color.Luego, se crea un objeto "tempPixels" para contener los datos
	//de la imagen en forma de matriz de píxeles.Después de establecer los valores de los píxeles en "tempPixels", se llama a SDL_UpdateTexture() 
	//para actualizar la textura "m_pTexture" con los datos nuevos.Finalmente, se dibuja la textura en la ventana utilizando SDL_RenderCopy().
	ComputeMaxValues();

	Uint32 *tempPixels = new Uint32[m_xSize * m_ySize];
	
	memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));
	
	for (int x=0; x<m_xSize; ++x)
	{
		for (int y=0; y<m_ySize; ++y)
		{
			tempPixels[(y*m_xSize)+x] = ConvertColor(m_rChannel.at(x).at(y), m_gChannel.at(x).at(y), m_bChannel.at(x).at(y));
		}
	}
	
	SDL_UpdateTexture(m_pTexture, NULL, tempPixels, m_xSize * sizeof(Uint32));
	
	delete[] tempPixels;
	
	SDL_Rect srcRect, bounds;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = m_xSize;
	srcRect.h = m_ySize;
	bounds = srcRect;
	SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
}

void Filme::InitTexture()
{
	//El método InitTexture() crea un objeto "SDL_Surface" y utiliza sus datos para crear un objeto "SDL_Texture".
	//Si ya existe un objeto "SDL_Texture", se libera la memoria antes de crear uno nuevo.
	Uint32 rmask, gmask, bmask, amask;
	
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
	#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
	#endif
	
	if (m_pTexture != NULL)
		SDL_DestroyTexture(m_pTexture);
		
	SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);		
}

Uint32 Filme::ConvertColor(const double red, const double green, const double blue)
{
	//El método ConvertColor() convierte los valores de los canales de color a un valor entero de 32 bits que se 
	//puede usar para establecer el color de un píxel.

	unsigned char r = static_cast<unsigned char>((red / m_overallMax) * 255.0);
	unsigned char g = static_cast<unsigned char>((green / m_overallMax) * 255.0);
	unsigned char b = static_cast<unsigned char>((blue / m_overallMax) * 255.0);
	
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
	#else
		Uint32 pixelColor = (255 << 24) + (b << 16) + (g << 8) + r;
	#endif
	
	return pixelColor;
}

void Filme::ComputeMaxValues()
{
	//El método ComputeMaxValues() calcula los valores máximos de los canales de color y el valor máximo general.
	m_maxRed = 0.0;
	m_maxGreen = 0.0;
	m_maxBlue = 0.0;
	m_overallMax = 0.0;
	for (int x=0; x<m_xSize; ++x)
	{
		for (int y=0; y<m_ySize; ++y)
		{
			double redValue		= m_rChannel.at(x).at(y);
			double greenValue	= m_gChannel.at(x).at(y);
			double blueValue	= m_bChannel.at(x).at(y);
			
			if (redValue > m_maxRed)
				m_maxRed = redValue;
				
			if (greenValue > m_maxGreen)
				m_maxGreen = greenValue;
				
			if (blueValue > m_maxBlue)
				m_maxBlue = blueValue;
				
			if (m_maxRed > m_overallMax)
				m_overallMax = m_maxRed;
			
			if (m_maxGreen > m_overallMax)
				m_overallMax = m_maxGreen;
				
			if (m_maxBlue > m_overallMax)
				m_overallMax = m_maxBlue;
		}
	}
}





















