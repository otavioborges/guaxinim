/*
 * id3Frame.hpp
 *
 *  Created on: Nov 18, 2017
 *      Author: otavio
 */

#ifndef ID3_ID3FRAME_HPP_
#define ID3_ID3FRAME_HPP_

#include <stdint.h>
#include "id3Data.hpp"

namespace guaxinim{
	namespace id3{
		class ID3Frame{
		private:
			char m_frameID[5];
			uint32_t m_frameSize;
			uint16_t m_frameFlags;
			uint8_t *m_frameStart;
			uint8_t *m_nextFrame;
			static audio_info_t GetFrameType(char *ID);
		public:
			ID3Frame(void);
			void Parse(uint8_t *data, ID3Data *tag);
			uint8_t *NextFrame(void);
			uint32_t FrameFullSize(void);
		};
	}
}

#endif /* ID3_ID3FRAME_HPP_ */
