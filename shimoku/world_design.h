#ifndef _WORLD_DESIGN_H
#define _WORLD_DESIGN_H

#define BALL_SIZE		2.0		//ボールの半径
#define BAR_DEPTH_DIFF	BALL_SIZE*2.1	//ボールが刺さる間隔

#define BAR_SIZE		BALL_SIZE*0.2			//円柱の半径
#define BAR_WIDTH_DIFF	BALL_SIZE*2.4		//バーの配置間隔
#define BAR_HEIGHT		BAR_DEPTH_DIFF*3+BALL_SIZE*2	//バーの高さ

#define BASE_WIDTH_DOWN	BAR_WIDTH_DIFF*4.3	//土台底面の幅
#define BASE_WIDTH_UP	BAR_WIDTH_DIFF*4	//土台上面の幅
#define BASE_DEPTH		BALL_SIZE*0.8	//土台の高さ

#endif _WORLD_DESIGN_H