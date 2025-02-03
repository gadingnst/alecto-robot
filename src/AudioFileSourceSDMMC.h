#ifndef AUDIO_FILE_SOURCE_SDMMC_H
#define AUDIO_FILE_SOURCE_SDMMC_H

#include <AudioFileSource.h>
#include "SDCard.h"

class AudioFileSourceSDMMC : public AudioFileSource {
protected:
  File file;
  SDCard* sd;

public:
  AudioFileSourceSDMMC(const char* filename, SDCard* sdCard);
  virtual ~AudioFileSourceSDMMC() { if (file) file.close(); }
  
  virtual bool open(const char* filename);
  virtual uint32_t read(void *data, uint32_t len);
  virtual bool seek(int32_t pos, int dir);
  virtual bool close();
  virtual bool isOpen();
  virtual uint32_t getSize();
  virtual uint32_t getPos();
};

#endif