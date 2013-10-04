
#pragma once
#include "common.h"

class JPEG
{
public:
	JSAMPARRAY img;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	unsigned long sizeX;  //��
	unsigned long sizeY; //�c
	char *Data;  //�摜�f�[�^�i�[
	bool Load(char *filename);
	GLuint texture;
	void TexSet();
	JPEG(char *FileName);
	virtual ~JPEG();
};