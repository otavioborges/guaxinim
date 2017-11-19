/*
 * mp3decoder.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: otavio
 */

#include <string.h>
#include "mp3decoder.hpp"
#include "id3.hpp"

using namespace guaxinim;
using namespace guaxinim::id3;

Mp3Decoder::Mp3Decoder(uint8_t *data){
	char auxString[10];

	m_currentDataPointer = data;

	memcpy(auxString, m_currentDataPointer, 3);
	auxString[3] = '\0';

	if(strcmp(auxString, "ID3") == 0){
		ID3Parse parse(m_currentDataPointer);

		m_id3Data = parse.GetData();
		m_currentDataPointer = parse.ID3End();
	}else{
		m_validFile = false;
	}
}

ID3Data *Mp3Decoder::GetID3Data(void){
	return &m_id3Data;
}
