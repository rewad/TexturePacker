#include "texturepacker.h"
#include "qpushbutton.h"
#include "qmessagebox.h"
#include "App.h"
#include "Il\il.h"
#include "Il\ilu.h"

uint32 TexturePacker::m_notifyChangeChannel = -1;
TexturePacker::TexturePacker(QWidget *parent)
	: QMainWindow(parent)
{


	ilInit();
	iluInit();

	ui.setupUi(this);

	p_mainApplicationLayout = new QHBoxLayout(ui.centralWidget);
	p_dataPreview = nullptr;
	m_numChannels = 4;

	p_saveButton = new QPushButton(ui.centralWidget);
	p_saveButton->setText("Save image"); 
	connect(p_saveButton, SIGNAL(clicked()), this, SLOT(SaveFile()));

	p_imageLabel = new QLabel();
	p_mainApplicationLayout->addWidget(p_imageLabel);
	
	p_channelsLayout = new QVBoxLayout();
	p_mainApplicationLayout->addLayout(p_channelsLayout);

	for (int32 i = 0; i < 4; i++)
	{
		p_textures[i] = new NChannelWidget();
		p_textures[i]->SetText("Texture");
		p_textures[i]->SetID(i);
		p_channelsLayout->addWidget(p_textures[i]);
		connect(p_textures[i], &NChannelWidget::UpdateChannelSignal, this, &TexturePacker::NotifyUpdateChannel);
	}
	CreatePreview();
}

TexturePacker::~TexturePacker()
{
	SAFE_DELETE(p_mainApplicationLayout);
	SAFE_DELETE(p_dataPreview);
}

void TexturePacker::UpdateImage()
{
	QImage image_temp(p_dataPreview, 512, 512, QImage::Format::Format_RGBA8888);
	p_imageLabel->setPixmap(QPixmap::fromImage(image_temp));
}

void TexturePacker::SaveFile()
{
	QString file_name = QFileDialog::getSaveFileName();
	if (file_name != "")
	{
		NImage img;
		uint32 width = p_textures[0]->GetWidth();
		uint32 height = p_textures[0]->GetHeight();
		uint32 channels = p_textures[0]->GetNumChannels();
		byte *pre_data[4] = { nullptr };

		for (int i = 0; i < channels; i++)
		{
			pre_data[i] = p_textures[i]->GetByte();
		}
		unsigned char* data = new unsigned char[width*height*channels];

		for (int i = 0; i < width*height; i++)
		{
			for (int j = 0; j < channels; j++)
				data[i*channels + j] = pre_data[j][i];
		}

		img.CreateImage(width, height, channels, data);
		img.SaveImage(file_name.toStdString());
		img.Clear();
		for (int i = 0; i < 4; i++)
		{
			SAFE_DELETE(pre_data[i]);
		}
	}
}

void TexturePacker::NotifyUpdateChannel(uint32 channel)
{
	if (channel > 3)
	{
		WARNING("Channel bad");
		return;
	}
	byte* data = p_textures[channel]->GetBigPreview();
	if (m_numChannels <= channel)
	{
		SAFE_DELETE(data);
		WARNING("Channel bad in range");
		return;
	}


	for (int32 i = 0; i < 512 * 512; i++)
	{
		p_dataPreview[i*m_numChannels + channel] = data[i];
	}
	SAFE_DELETE(data)
	UpdateImage();
}

void TexturePacker::CreatePreview()
{
	SAFE_DELETE(p_dataPreview);
	p_dataPreview = new byte[512 * 512 * m_numChannels];
	memset(p_dataPreview, 255, 512 * 512 * m_numChannels);
}

