#pragma once
#include <string>
#include "IL\il.h"
#include "IL\ilu.h"
#include "App.h"

enum EChannelTexture
{
	ERed = 0,
	EGreen,
	EBlue,
	EAlpha,
};

using namespace std;

class NImage
{
public:
	NImage();
	~NImage();

	void CreateImage(uint32 width, uint32 height, uint32 num_channels,byte *data);

	uint32 GetWidth()const { return m_width; }
	uint32 GetHeight()const { return m_height; }
	uint32 GetChannels()const { return m_numChannels; }
	byte *GetData() { return m_bytesImage; }

	void SetWidth(const uint32 width) { m_width = width; }
	void SetHeight(const uint32 height) { m_height = height; }
	void SetChannels(const uint32 channels) { m_numChannels = channels; }
	void SetData(byte *data) { ilBindImage(m_idImage); m_bytesImage = data; }

	bool LoadImage(string file_image, bool is_flip = false);
	bool SaveImage(string file_image);
	byte *GetChannel(EChannelTexture channel);

	bool IsEmpty();
	void Clear();
	void Resize(uint32 width, uint32 height); 
private:

	byte GetChannelPixel(uint32 offset, uint32 width, uint32 height);

	int ConvertChannelToOffset(EChannelTexture channel);
	uint32 m_idImage;
	uint32 m_width;
	uint32 m_height;
	uint32 m_numChannels;
	uint32 m_bytePerPixel;
	byte	 *m_bytesImage;
};

