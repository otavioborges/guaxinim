/*
 * id3Data.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: otavio
 */

#include <stdlib.h>
#include <string.h>
#include "id3Data.hpp"

using namespace guaxinim::id3;

ID3Data::ID3Data(void){
	m_artist = NULL;
	m_album = NULL;
	m_title = NULL;
	m_trackNum = NULL;
	m_coverImgStart = NULL;
	m_coverImgBytes = 0;
}

ID3Data::~ID3Data(void){
	if(m_artist != NULL)
		delete m_artist;
	if(m_album != NULL)
		delete m_album;
	if(m_title != NULL)
		delete m_title;
}

void ID3Data::InsertData(audio_info_t field, data_encoding_t encoding, uint8_t *data, uint32_t bytes){
	if(field != AUDIO_INFO_COVER_IMG){
		char *parsed;
		uint16_t position = 0;

		if((encoding == ENCODING_ISO_8859_1) || (encoding == ENCODING_UTF_8)){
			parsed = new char[bytes+1];

			for(uint16_t idx = 0; idx < bytes; idx++){
				parsed[idx] = data[idx];
			}
			position = bytes;
		}else{
			parsed = new char[(bytes >> 1) + 1];

			for(uint16_t idx = 0; idx < bytes; idx += 2){
				if(encoding == ENCODING_UTF_16_BE)
					parsed[position] = data[idx+1];
				else
					parsed[position] = data[idx];

				position++;
			}
		}

		// check if parsed ended with \0
		parsed[position] = 0x00;


		switch(field){
			case AUDIO_INFO_ARTIST:
				m_artist = parsed;
				break;
			case AUDIO_INFO_ALBUM:
				m_album = parsed;
				break;
			case AUDIO_INFO_TITLE:
				m_title = parsed;
				break;
			case AUDIO_INFO_TRACK_NUM:
				m_trackNum = atoi(parsed);
				break;
		}
	}else{
		uint8_t *auxFile;
		uint16_t mimeSize = 0;

		auxFile = data;
		while(*auxFile != 0x00){
			mimeSize++;
			auxFile++;
		}
		char *mimeType = new char[mimeSize + 1];
		memcpy(mimeType, data, mimeSize);

		auxFile++;
		if(strcmp(mimeType, "image/jpeg") == 0){
			if(*auxFile == 0x03){
				auxFile += 2;
				m_coverImgStart = auxFile;
				m_coverImgBytes = bytes - (mimeSize - 3);
			}
		}

		delete mimeType;
	}
}

char *ID3Data::GetArtist(void){
	return m_artist;
}
char *ID3Data::GetAlbum(void){
	return m_album;
}
char *ID3Data::GetTitle(void){
	return m_title;
}
uint8_t ID3Data::GetTrackNumber(void){
	return m_trackNum;
}
uint8_t *ID3Data::GetCoverBuffer(void){
	return m_coverImgStart;
}
uint32_t ID3Data::GetCoverBytes(void){
	return m_coverImgBytes;
}
