/*
 * id3.hpp
 *
 *  Created on: Nov 18, 2017
 *      Author: otavio
 */

#ifndef ID3_HPP_
#define ID3_HPP_

#include <stdint.h>
#include <stdbool.h>

#include "id3Data.hpp"

namespace guaxinim{
	namespace id3{
		typedef enum{
			ID3_FLAG_UNSYCHRONISATION	= 0x80,
			ID3_FLAG_EXTENDED_HEADER	= 0x40,
			ID3_FLAG_EXPERIMENTAL		= 0x20,
			ID3_FLAG_FOOTER_PRESENT		= 0x10
		}id3_flags_t;

		class ID3Parse{
		private:
			uint8_t *m_dataPointer;
			uint16_t m_version;
			uint8_t m_flags;
			uint32_t m_sizeInBytes;
			uint8_t *m_endOfTag;
			bool m_valid;
			ID3Data m_data;
		public:
			ID3Parse(uint8_t *data);
			ID3Data GetData(void);
			uint8_t *ID3End(void);
		};
	}
}

#endif /* ID3_HPP_ */
