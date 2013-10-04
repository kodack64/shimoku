#include "jpeg.h"

JPEG::JPEG(char *FileName){
	Data=NULL;
	cinfo.err = jpeg_std_error( &jerr );
	jpeg_create_decompress( &cinfo );
	Load(FileName);
	TexSet();
}
JPEG::~JPEG(){
	if(Data!=NULL){
		free(Data);
	}
}

bool JPEG::Load(char *FileName) {
	FILE *File;
	fopen_s(&File,FileName, "rb");
	if (File==NULL){
		printf("ファイルがありません");
		return false;
	}
	jpeg_stdio_src( &cinfo, File );
	jpeg_read_header( &cinfo, TRUE );
	sizeX=cinfo.image_width;
	sizeY=cinfo.image_height;
	jpeg_start_decompress( &cinfo );
	// イメージを保持するメモリ領域の確保と初期化
	Data = (char *) malloc(sizeY*(sizeX*3));
	img = (JSAMPARRAY)malloc( sizeof( JSAMPROW ) * cinfo.image_height );
	for ( int i = 0; (unsigned)i < cinfo.image_height; i++ ) {
		img[i] = (JSAMPROW)calloc( sizeof( JSAMPLE ), 3 * cinfo.image_width );
	}
	// 全イメージデータを取得 
	while( cinfo.output_scanline < cinfo.output_height ) {
		jpeg_read_scanlines( &cinfo,img + cinfo.output_scanline,cinfo.output_height - cinfo.output_scanline );
	}
	for(int i=0;(unsigned)i<sizeY;i++){
		for(int j=0;(unsigned)j<sizeX*3;j++){
			Data[i*sizeX*3+j] = (char)img[sizeY-i-1][j];
		}
	}
	jpeg_finish_decompress( &cinfo );
	jpeg_destroy_decompress( &cinfo );
 
	fclose( File );
	// イメージデータを保持するメモリ領域を開放
	for ( int i = 0; (unsigned)i < sizeY; i++ )
		free( img[i] );
	free( img );
	return true;
}

void JPEG::TexSet()
{
	glEnable( GL_TEXTURE_2D );
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, 3, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, Data );
	glBindTexture( GL_TEXTURE_2D, 0 );
}