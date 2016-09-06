#include "NImage.h"
#include "App.h"

NImage::NImage()
{
	m_width = 0;
	m_height = 0;
	m_numChannels = 0;
	m_bytePerPixel = 0;
	m_idImage = -1;
	m_bytesImage = nullptr;
}


NImage::~NImage()
{
	Clear();
}

void NImage::CreateImage(uint32 width, uint32 height, uint32 num_channels, byte *data)
{
	m_idImage = ilGenImage();
	ilBindImage(m_idImage);

	m_width = width;
	m_height = height;
	m_numChannels = num_channels;
	uint32 num_byte = m_width*m_height*m_numChannels;
	m_bytesImage = new byte[num_byte];
	memcpy(m_bytesImage, data, num_byte);
}

bool NImage::LoadImage(string file_image, bool is_flip)
{
	Clear();
	if (is_flip)
	{
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT / IL_ORIGIN_UPPER_LEFT);
	}
	else
	{
		ilDisable(IL_ORIGIN_SET);
	}

	m_idImage = ilGenImage();
	ilBindImage(m_idImage);
	bool is_load = ilLoadImage(file_image.c_str());
	if (!is_load)
	{
		WARNING("Failed Load Image");
		return false;
	}
	m_width = ilGetInteger(IL_IMAGE_WIDTH);
	m_height = ilGetInteger(IL_IMAGE_HEIGHT);
	m_numChannels = ilGetInteger(IL_IMAGE_CHANNELS);
	m_bytePerPixel = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	m_bytesImage = ilGetData();
	return true;
}


bool NImage::SaveImage(string file_image)
{
	m_idImage = ilGenImage();
	ilBindImage(m_idImage);
	if (ilTexImage(m_width, m_height, 1, m_numChannels, m_numChannels == 3 ? IL_RGB : IL_RGBA, IL_UNSIGNED_BYTE, m_bytesImage))
	{
		ilEnable(IL_FILE_OVERWRITE);
		ilSaveImage(file_image.c_str());

	}
	WARNING("Bad create image");
	ILenum error = ilGetError();
	return false;
}

byte NImage::GetChannelPixel(uint32 offset, uint32 width, uint32 height)
{
	int position_pixel = height * m_width + width;
	position_pixel *= m_bytePerPixel;
	return m_bytesImage[position_pixel + offset];
}

byte * NImage::GetChannel(EChannelTexture channel)
{
	ilBindImage(m_idImage);
	byte *new_channel = new byte[m_width * m_height];
	int offset = ConvertChannelToOffset(channel);
	int sz = ilGetInteger(IL_IMAGE_SIZE_OF_DATA);
	for (int i = 0; i < m_height*m_width; i++)
	{
		new_channel[i] = m_bytesImage[i*m_numChannels + offset];
	}

	return new_channel;
}

bool NImage::IsEmpty()
{
	return GetWidth() < 1 || GetHeight() < 1;
}

void NImage::Clear()
{
	if (m_idImage != -1)
	{
		ilBindImage(m_idImage);
		ilDeleteImage(1);
	}
}

void NImage::Resize(uint32 width, uint32 height)
{
	ilBindImage(m_idImage);
	iluScale(width, height, 1);
	m_width = ilGetInteger(IL_IMAGE_WIDTH);
	m_height = ilGetInteger(IL_IMAGE_HEIGHT);
	m_numChannels = ilGetInteger(IL_IMAGE_CHANNELS);
	m_bytePerPixel = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	m_bytesImage = ilGetData();
}



int NImage::ConvertChannelToOffset(EChannelTexture channel)
{
	int offset = 0;
	switch (channel)
	{
	case EChannelTexture::EGreen:
		offset = 1;
		break;
	case EChannelTexture::EBlue:
		offset = 2;
		break;
	case EChannelTexture::EAlpha:
		offset = 3;
		break;
	default:
		offset = 0;
		break;
	}
	return offset;
}
