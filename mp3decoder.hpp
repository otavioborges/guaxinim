/*
 * mp3decoder.hpp
 *
 *  Created on: Nov 18, 2017
 *      Author: otavio
 */

#ifndef MP3DECODER_HPP_
#define MP3DECODER_HPP_

#include <stdint.h>
#include <stdbool.h>

#include "id3Data.hpp"

namespace guaxinim{
	class Mp3Decoder{
	private:
		uint8_t *m_currentDataPointer;
		id3::ID3Data m_id3Data;
		bool m_validFile;
	public:
		Mp3Decoder(uint8_t *data);
		id3::ID3Data *GetID3Data(void);
	};
}

#endif /* MP3DECODER_HPP_ */
