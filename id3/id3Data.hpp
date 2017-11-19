/*
 * id3Data.hpp
 *
 *  Created on: Nov 18, 2017
 *      Author: otavio
 */

#ifndef ID3_ID3DATA_HPP_
#define ID3_ID3DATA_HPP_

#include <stdint.h>

namespace guaxinim{
	namespace id3{
		typedef enum{
			AUDIO_INFO_ARTIST,
			AUDIO_INFO_ALBUM,
			AUDIO_INFO_TITLE,
			AUDIO_INFO_TRACK_NUM,
			AUDIO_INFO_COVER_IMG,
			AUDIO_INFO_UNKNOWN
		}audio_info_t;

		typedef enum{
			ENCODING_ISO_8859_1,
			ENCODING_UTF_16_BE,
			ENCODING_UTF_16_LE,
			ENCODING_UTF_8,
			ENCODING_NOT_STRING
		}data_encoding_t;

		class ID3Data{
		private:
			char *m_artist;
			char *m_album;
			char *m_title;
			uint8_t m_trackNum;
			uint8_t *m_coverImgStart;
			uint32_t m_coverImgBytes;

		public:
			ID3Data(void);
			~ID3Data(void);
			void InsertData(audio_info_t field, data_encoding_t encoding, uint8_t *data, uint32_t bytes);

			// GET Methods
			char *GetArtist(void);
			char *GetAlbum(void);
			char *GetTitle(void);
			uint8_t GetTrackNumber(void);
			uint8_t *GetCoverBuffer(void);
			uint32_t GetCoverBytes(void);
		};
	}
}

#endif /* ID3_ID3DATA_HPP_ */
