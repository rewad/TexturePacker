#ifndef TEXTUREPACKER_H
#define TEXTUREPACKER_H

#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "qlabel.h"
#include "ui_texturepacker.h"
#include"NChannelWidget.h"
#include "qfiledialog.h"



class TexturePacker : public QMainWindow
{
	Q_OBJECT

public:
	TexturePacker(QWidget *parent = 0);
	~TexturePacker();

	void UpdateImage();

private:
	Ui::TexturePackerClass ui;

	QHBoxLayout *p_mainApplicationLayout;

	QLabel *p_imageLabel;
	QVBoxLayout *p_channelsLayout;
	QPushButton *p_saveButton;

	void CreatePreview();

	NChannelWidget *p_textures[4];

	NImage m_imagePreview;
	NImage m_imageMain;
	 
	static uint32 m_notifyChangeChannel;
	uint32 m_numChannels;
	byte *p_dataPreview;
public slots:
	void NotifyUpdateChannel(uint32 channel);	
	void SaveFile();
};

#endif // TEXTUREPACKER_H
