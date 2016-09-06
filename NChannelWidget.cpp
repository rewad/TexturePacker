#include "NChannelWidget.h"
#include "qradiobutton.h" 
#include "NImage.h"
#include "qimage.h"
#include "qfiledialog.h"
NChannelWidget::NChannelWidget(QWidget *parent) :QWidget(parent)
{

	m_sizeHalfPreview = 128;
	m_sizePreview = 512;
	m_dataPreview = nullptr;

	p_mainLayout = new QHBoxLayout(this);
	p_mainLayout->setMargin(0);

	p_imageLabel = new QLabel();
	p_imageLabel->setMaximumWidth(128);
	p_imageLabel->setMaximumHeight(128);
	p_mainLayout->addWidget(p_imageLabel);

	p_openImage = new QPushButton();
	p_openImage->setText("Open file image");
	p_mainLayout->addWidget(p_openImage);

	p_channelLayout = new QVBoxLayout();
	p_mainLayout->addLayout(p_channelLayout);

	p_nameLabel = new QLabel();
	p_channelLayout->addWidget(p_nameLabel);

	p_redChannel = new QRadioButton();
	p_redChannel->setText("Red");
	p_channelLayout->addWidget(p_redChannel);

	p_greenChannel = new QRadioButton();
	p_greenChannel->setText("Green");
	p_channelLayout->addWidget(p_greenChannel);

	p_blueChannel = new QRadioButton();
	p_blueChannel->setText("Blue");
	p_channelLayout->addWidget(p_blueChannel);

	p_alphaChannel = new QRadioButton();
	p_alphaChannel->setText("Alpha");
	p_channelLayout->addWidget(p_alphaChannel);

	connect(p_redChannel, SIGNAL(toggled(bool)), this, SLOT(RedClick(bool)));
	connect(p_greenChannel, SIGNAL(toggled(bool)), this, SLOT(GreenClick(bool)));
	connect(p_blueChannel, SIGNAL(toggled(bool)), this, SLOT(BlueClick(bool)));
	connect(p_alphaChannel, SIGNAL(toggled(bool)), this, SLOT(AlphaClick(bool)));
	connect(p_openImage, SIGNAL(clicked()), this, SLOT(OpenFile()));

}


NChannelWidget::~NChannelWidget()
{
	SAFE_DELETE(p_mainLayout);
	SAFE_DELETE(m_dataPreview);
}

void NChannelWidget::SetText(const QString & title)
{
	if (p_nameLabel)
		p_nameLabel->setText(title);
}

EChannelTexture NChannelWidget::GetChannedlActive() const
{
	return m_currentChannel;
}

void NChannelWidget::LoadImage(string file_name)
{
	SAFE_DELETE(m_dataPreview);
	m_nameImage = file_name;

	m_halfPreviewImage.LoadImage(m_nameImage);
	m_bigPreviewImage.LoadImage(m_nameImage);
	m_mainImage.LoadImage(m_nameImage, true);

	p_alphaChannel->setDisabled(m_mainImage.GetChannels() == 3);

}


void NChannelWidget::RedClick(bool checked)
{
	CheckedNewChannel(checked, EChannelTexture::ERed);
}

void NChannelWidget::GreenClick(bool checked)
{
	CheckedNewChannel(checked, EChannelTexture::EGreen);
}

void NChannelWidget::BlueClick(bool checked)
{
	CheckedNewChannel(checked, EChannelTexture::EBlue);
}

void NChannelWidget::AlphaClick(bool checked)
{
	CheckedNewChannel(checked, EChannelTexture::EAlpha);
}

void NChannelWidget::OpenFile()
{
	QString file_name = QFileDialog::getOpenFileName(this);
	m_nameImage = file_name.toStdString();
	LoadImage(m_nameImage);
	CheckedNewChannel(true, EChannelTexture::ERed);
}

void NChannelWidget::CheckedNewChannel(bool checked, EChannelTexture channel)
{
	if (checked && m_currentChannel != channel)
	{
		m_currentChannel = channel;
		UpdatePreview();

	}
}

byte * NChannelWidget::GetBigPreview()
{
	if (m_bigPreviewImage.GetHeight() != m_sizePreview || m_bigPreviewImage.GetWidth() != m_sizePreview)
	{
		m_bigPreviewImage.Resize(m_sizePreview, m_sizePreview);
	}
	return m_bigPreviewImage.GetChannel(m_currentChannel);
}

void NChannelWidget::UpdatePreview()
{
	SAFE_DELETE(m_dataPreview);

	if (m_mainImage.IsEmpty())
	{
		WARNING("Empty image");
		return;
	}

	if (m_halfPreviewImage.GetHeight() != m_sizeHalfPreview || m_halfPreviewImage.GetWidth() != m_sizeHalfPreview)
	{
		m_halfPreviewImage.Resize(m_sizeHalfPreview, m_sizeHalfPreview);
	}

	m_dataPreview = m_halfPreviewImage.GetChannel(m_currentChannel);
	QImage image_temp(m_dataPreview, m_halfPreviewImage.GetWidth(), m_halfPreviewImage.GetHeight(), QImage::Format::Format_Grayscale8);
	p_imageLabel->setPixmap(QPixmap::fromImage(image_temp));
	emit UpdateChannelSignal(m_id);
}

