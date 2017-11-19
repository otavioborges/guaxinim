/*
 * id3Frame.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: otavio
 */

#include <string.h>
#include "id3Frame.hpp"

#define ARTIST_ID	0x54504531
#define ALBUM_ID	0x54414C42
#define TITLE_ID	0x54495432
#define TRACK_ID	0x5452434B
#define IMG_ID		0x41504943

using namespace guaxinim::id3;

audio_info_t ID3Frame::GetFrameType(char *ID){
	uint32_t idInteger = ID[0];
	idInteger = (idInteger << 8) + ID[1];
	idInteger = (idInteger << 8) + ID[2];
	idInteger = (idInteger << 8) + ID[3];

	switch(idInteger){
		case ARTIST_ID:
			return AUDIO_INFO_ARTIST;
		case ALBUM_ID:
			return AUDIO_INFO_ALBUM;
		case TITLE_ID:
			return AUDIO_INFO_TITLE;
		case TRACK_ID:
			return AUDIO_INFO_TRACK_NUM;
		case IMG_ID:
			return AUDIO_INFO_COVER_IMG;
		default:
			return AUDIO_INFO_UNKNOWN;
	}
}

ID3Frame::ID3Frame(void){
	m_frameStart = NULL;
	m_frameFlags = 0;
	m_frameSize = 0;
	m_nextFrame = 0;
}

void ID3Frame::Parse(uint8_t *data, ID3Data *tag){
	m_frameStart = data;

	memcpy(m_frameID, data, 4);
	m_frameID[4] = '\0';
	data += 4;

	m_frameSize = *data;
	data++;
	m_frameSize = (m_frameSize << 7) + *data;
	data++;
	m_frameSize = (m_frameSize << 7) + *data;
	data++;
	m_frameSize = (m_frameSize << 7) + *data;

	data++;
	m_frameFlags = *data;
	data++;
	m_frameFlags = (m_frameFlags << 8) + *data;

	data++;
	m_nextFrame = data + m_frameSize;

	audio_info_t frameType = ID3Frame::GetFrameType(m_frameID);
	if(frameType == AUDIO_INFO_UNKNOWN)
		return; // we don't know how to handle this for now!

	switch(*data){
		case 0x00:
			data++;
			tag->InsertData(frameType, ENCODING_ISO_8859_1, data, m_frameSize - 1);
			break;
		case 0x01:
			data += 3;
			tag->InsertData(frameType, ENCODING_UTF_16_LE, data, m_frameSize - 3);
			break;
		case 0x02:
			data += 3;
			tag->InsertData(frameType, ENCODING_UTF_16_BE, data, m_frameSize - 3);
			break;
		case 0x03:
			data++;
			tag->InsertData(frameType, ENCODING_UTF_8, data, m_frameSize - 1);
			break;
	}
}

uint8_t *ID3Frame::NextFrame(void){
	return m_nextFrame;
}

uint32_t ID3Frame::FrameFullSize(void){
	return m_frameSize + 10u;
}
