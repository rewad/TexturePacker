#pragma once
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qwidget.h>
#include <qradiobutton.h>
#include <qlabel.h>
#include "NImage.h"
#include "qpushbutton.h"
#include "memory.h"

class NChannelWidget : public QWidget
{
	Q_OBJECT
public:
	explicit  NChannelWidget(QWidget *parent = 0);
	~NChannelWidget();

	void SetText(const QString &title);

	EChannelTexture GetChannedlActive() const;	 
	
	void LoadImage(string file_name);
	void SetID(uint32 id) { m_id = id; }

	int32 GetWidth()const { return m_mainImage.GetWidth(); }
	int32 GetHeight()const { return m_mainImage.GetHeight(); }
	int32 GetNumChannels()const { return m_mainImage.GetChannels(); }
	unsigned char *GetByte() { return m_mainImage.GetChannel(m_currentChannel); }

private:
	QHBoxLayout *p_mainLayout;
	QLabel *p_imageLabel;

	QPushButton *p_openImage;

	QVBoxLayout *p_channelLayout;
	QRadioButton *p_redChannel;
	QRadioButton *p_greenChannel;
	QRadioButton *p_blueChannel;
	QRadioButton *p_alphaChannel;
	
	QLabel *p_nameLabel;
	EChannelTexture m_currentChannel;
	uint32 m_id;

public:


	void CheckedNewChannel(bool checked, EChannelTexture channel);
	
	byte *GetBigPreview();
	byte *GetImageChannel();

	void UpdatePreview(); 
	
	uint32 m_sizeHalfPreview;
	uint32 m_sizePreview;

	NImage m_halfPreviewImage;
	NImage m_bigPreviewImage;
	NImage m_mainImage;
	string m_nameImage;
	byte* m_dataPreview;

public slots:
	void RedClick(bool checked);
	void GreenClick(bool checked);
	void BlueClick(bool checked);
	void AlphaClick(bool checked);
	void OpenFile();


	signals :
	void UpdateChannelSignal(uint32 channel);
};

