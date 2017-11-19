/*
 * id3.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: otavio
 */

#include "id3.hpp"
#include "id3Frame.hpp"

using namespace guaxinim::id3;

ID3Parse::ID3Parse(uint8_t *data){
	m_dataPointer = data;

	if(m_dataPointer[0] == 'I' && m_dataPointer[1] == 'D' && m_dataPointer[2] == '3'){
		m_dataPointer += 3;

		m_version = *m_dataPointer;
		m_dataPointer++;
		m_version = (m_version << 8) + *m_dataPointer;

		m_dataPointer++;
		m_flags = *m_dataPointer;

		m_dataPointer++;
		m_sizeInBytes = *m_dataPointer;
		m_dataPointer++;
		m_sizeInBytes = (m_sizeInBytes << 7) + *m_dataPointer;
		m_dataPointer++;
		m_sizeInBytes = (m_sizeInBytes << 7) + *m_dataPointer;
		m_dataPointer++;
		m_sizeInBytes = (m_sizeInBytes << 7) + *m_dataPointer;

		m_dataPointer++;
		m_endOfTag = m_dataPointer;
		m_endOfTag += m_sizeInBytes;
		if((m_flags & ID3_FLAG_FOOTER_PRESENT) != 0)
			m_endOfTag += 10u;

		if((m_flags & ID3_FLAG_EXTENDED_HEADER) != 0){
			// TODO: parse extended header
			uint32_t extendedHeaderEnd = *m_dataPointer;
			m_dataPointer++;
			extendedHeaderEnd = (extendedHeaderEnd << 7) + *m_dataPointer;
			m_dataPointer++;
			extendedHeaderEnd = (extendedHeaderEnd << 7) + *m_dataPointer;
			m_dataPointer++;
			extendedHeaderEnd = (extendedHeaderEnd << 7) + *m_dataPointer;

			m_dataPointer += (extendedHeaderEnd - 4); // ignore 32bit header size
		}

		// at the first frame!
		ID3Frame frame;

		frame.Parse(m_dataPointer, &m_data);
		m_sizeInBytes -= frame.FrameFullSize();
		m_dataPointer = frame.NextFrame();

		while(m_dataPointer < m_endOfTag){
			frame.Parse(m_dataPointer, &m_data);
			m_sizeInBytes -= frame.FrameFullSize();
			m_dataPointer = frame.NextFrame();
		}

		m_valid = true;
	}else{
		m_valid = false;
	}
}

ID3Data ID3Parse::GetData(void){
	return m_data;
}

uint8_t *ID3Parse::ID3End(void){
	return m_endOfTag;
}
